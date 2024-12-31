#include <string_view>
#include "system_state.hpp"
#include "commands.hpp"
#include "SPSCQueue.h"
#include "network.hpp"
#include "serialization.hpp"
#include "gui_error_window.hpp"
#include "reports.hpp"

#define ZSTD_STATIC_LINKING_ONLY
#define XXH_NAMESPACE ZSTD_
#include "zstd.h"

//
// platform specific
//
#ifdef _WIN32
#include "network_win.cpp"
#else
#include "network_nix.cpp"
#endif

namespace network {
	void socket_add_to_send_queue(std::vector<char>& buffer, const void *data, size_t n) {
		buffer.resize(buffer.size() + n);
		std::memcpy(buffer.data() + buffer.size() - n, data, n);
	}

	//
	// non-platform specific
	//

	static dcon::nation_id get_temp_nation(sys::state& state) {
		// give the client a "joining" nation, basically a temporal nation choosen
		// "randomly" that is tied to the client iself
		for(auto n : state.nations_by_rank)
		if(!state.world.nation_get_is_player_controlled(n) && state.world.nation_get_owned_province_count(n) > 0) {
			bool is_taken = false;
			for(auto& client : state.network_state.clients) {
				if(client.playing_as == n) {
					is_taken = true;
					break;
				}
			}
			if(!is_taken) {
				return n;
			}
		}
		return dcon::nation_id{ };
	}

	void init(sys::state& state) {
		if(state.network_mode == sys::network_mode_type::single_player) {
			return; // Do nothing in singleplayer
		}

		state.network_state.finished = false;
		if(state.network_mode == sys::network_mode_type::host) {
			state.network_state.socket_fd = socket_init_server(state.network_state.as_v6, state.network_state.address);
		} else {
			assert(state.network_state.ip_address.size() > 0);
			state.network_state.socket_fd = socket_init_client(state.network_state.as_v6, state.network_state.address, state.network_state.ip_address.c_str());
		}

		// Host must have an already selected nation, to prevent issues...
		if(state.network_mode == sys::network_mode_type::host) {
			state.local_player_nation = get_temp_nation(state);
			assert(bool(state.local_player_nation));
			/* Materialize it into a command we send to new clients who connect and have to replay everything... */
			command::payload c{};
			c.type = command::command_type::notify_player_joins;
			c.source = state.local_player_nation;
			c.data.player_name = state.network_state.nickname;
			state.network_state.outgoing_commands.push(c);
		}
	}

	static void disconnect_client(sys::state& state, client_data& client, bool graceful) {
		if(command::can_notify_player_leaves(state, client.playing_as, graceful)) {
			command::notify_player_leaves(state, client.playing_as, graceful);
		}
		socket_shutdown(client.socket_fd);
		client.socket_fd = 0;
		client.send_buffer.clear();
		client.early_send_buffer.clear();
		client.total_sent_bytes = 0;
		client.save_stream_size = 0;
		client.save_stream_offset = 0;
		client.playing_as = dcon::nation_id{};
		client.recv_count = 0;
		client.handshake = true;
	}

	static uint8_t* write_network_compressed_section(uint8_t* ptr_out, uint8_t const* ptr_in, uint32_t uncompressed_size) {
		uint32_t decompressed_length = uncompressed_size;
		uint32_t section_length = uint32_t(ZSTD_compress(ptr_out + sizeof(uint32_t) * 2, ZSTD_compressBound(uncompressed_size), ptr_in,
		uncompressed_size, ZSTD_maxCLevel())); // write compressed data
		std::memcpy(ptr_out, &section_length, sizeof(uint32_t));
		std::memcpy(ptr_out + sizeof(uint32_t), &decompressed_length, sizeof(uint32_t));
		return ptr_out + sizeof(uint32_t) * 2 + section_length;
	}

	template<typename T>
	static uint8_t const* with_network_decompressed_section(uint8_t const* ptr_in, T const& function) {
		uint32_t section_length = 0;
		uint32_t decompressed_length = 0;
		std::memcpy(&section_length, ptr_in, sizeof(uint32_t));
		std::memcpy(&decompressed_length, ptr_in + sizeof(uint32_t), sizeof(uint32_t));
		auto temp_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[decompressed_length]);
		ZSTD_decompress(temp_buffer.get(), decompressed_length, ptr_in + sizeof(uint32_t) * 2, section_length);
		function(temp_buffer.get(), decompressed_length);
		return ptr_in + sizeof(uint32_t) * 2 + section_length;
	}

	bool client_data::is_banned(sys::state& state) const {
		if(state.network_state.as_v6) {
			auto sa = (struct sockaddr_in6 const*)&address;
			return std::find_if(state.network_state.v6_banlist.begin(), state.network_state.v6_banlist.end(), [&](auto const& a) {
				return std::memcmp(&sa->sin6_addr, &a, sizeof(a)) == 0;
			}) != state.network_state.v6_banlist.end();
		} else {
			auto sa = (struct sockaddr_in const*)&address;
			return std::find_if(state.network_state.v4_banlist.begin(), state.network_state.v4_banlist.end(), [&](auto const& a) {
				return std::memcmp(&sa->sin_addr, &a, sizeof(a)) == 0;
			}) != state.network_state.v4_banlist.end();
		}
	}

	static void send_post_handshake_commands(sys::state& state, network::client_data& client) {
		std::vector<char> tmp = client.send_buffer;
		client.send_buffer.clear();
		if(state.current_scene.starting_scene) {
			/* Send the savefile to the newly connected client (if not a new game) */
			if(!state.network_state.is_new_game) {
				command::payload c{};
				c.type = command::command_type::notify_save_loaded;
				c.source = state.local_player_nation;
				c.data.notify_save_loaded.target = client.playing_as;
				network::broadcast_save_to_clients(state, c, state.network_state.current_save_buffer.get(), state.network_state.current_save_length, state.network_state.current_save_checksum);
			}
			{ /* Tell this client about every other client */
				command::payload c{};
				c.type = command::command_type::notify_player_joins;
				//send join for our own nation
				c.source = state.local_player_nation;
				c.data.player_name = state.network_state.map_of_player_names[state.local_player_nation.index()];
				socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
				for(const auto& other : state.network_state.clients) {
					if(!other.is_active())
					continue;
					if(other.playing_as == client.playing_as) {
						c.source = client.playing_as;
						c.data.player_name = client.hshake_buffer.nickname;
						broadcast_to_clients(state, c);
						command::execute_command(state, c);
					} else {
						c.source = other.playing_as;
						c.data.player_name = state.network_state.map_of_player_names[other.playing_as.index()];
						socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
					}
				}
			}
		} else if(state.current_scene.game_in_progress) { //hotjoin
			{ /* Tell this client about every other client */
				command::payload c{};
				c.type = command::command_type::notify_player_joins;
				//send join for our own nation
				c.source = state.local_player_nation;
				c.data.player_name = state.network_state.map_of_player_names[state.local_player_nation.index()];
				//socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
				broadcast_to_clients(state, c);
				command::execute_command(state, c);
				for(const auto& other : state.network_state.clients) {
					if(!other.is_active())
					continue;
					if(other.playing_as == client.playing_as) {
						c.source = client.playing_as;
						c.data.player_name = client.hshake_buffer.nickname;
						broadcast_to_clients(state, c);
						command::execute_command(state, c);
					} else {
						c.source = other.playing_as;
						c.data.player_name = state.network_state.map_of_player_names[other.playing_as.index()];
						//socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
						broadcast_to_clients(state, c);
						command::execute_command(state, c);
					}
				}
			}
			{ /* "Start" the game - for this client */
				command::payload c{};
				c.type = command::command_type::notify_start_game;
				c.source = state.local_player_nation;
				broadcast_to_clients(state, c);
				command::execute_command(state, c);
				//socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
			}
			state.network_state.save_slock.store(true, std::memory_order::release);
			/* Reload clients */
			std::vector<dcon::nation_id> players;
			for(const auto n : state.world.in_nation)
				if(state.world.nation_get_is_player_controlled(n))
					players.push_back(n);
			dcon::nation_id old_local_player_nation = state.local_player_nation;
			state.local_player_nation = dcon::nation_id{ };
			network::write_network_save(state);
			/* Then reload as if we loaded the save data */
			state.preload();
			with_network_decompressed_section(state.network_state.current_save_buffer.get(), [&state](uint8_t const* ptr_in, uint32_t length) {
				read_save_section(ptr_in, ptr_in + length, state);
			});
			//network::write_network_save(state);
			state.fill_unsaved_data();
			for(const auto n : players)
				state.world.nation_set_is_player_controlled(n, true);
			state.local_player_nation = old_local_player_nation;
			assert(state.world.nation_get_is_player_controlled(state.local_player_nation));
			#if 0
			{ /* Reload all the other clients except the newly connected one */
				command::payload c{};
				c.type = command::command_type::notify_reload;
				c.source = state.local_player_nation;
				c.data.notify_reload.checksum = state.get_save_checksum();
				for(auto& other_client : state.network_state.clients) {
					if(other_client.playing_as != client.playing_as) {
						socket_add_to_send_queue(other_client.send_buffer, &c, command::get_size(c.type));
					}
				}
			}
			#endif
			{ /* Send the savefile to the newly connected client (if not a new game) */
				command::payload c{};
				c.type = command::command_type::notify_save_loaded;
				c.source = state.local_player_nation;
				//c.data.notify_save_loaded.target = client.playing_as;
				network::broadcast_save_to_clients(state, c, state.network_state.current_save_buffer.get(), state.network_state.current_save_length, state.network_state.current_save_checksum);
			}
			assert(state.network_state.save_slock.load(std::memory_order::acquire) == true);
			state.network_state.save_slock.store(false, std::memory_order::release);
		}
		auto old_size = client.send_buffer.size();
		client.send_buffer.resize(old_size + tmp.size());
		std::memcpy(client.send_buffer.data() + old_size, tmp.data(), tmp.size());
	}

	static void receive_from_clients(sys::state& state) {
		for(auto& client : state.network_state.clients) {
			if(!client.is_active())
			continue;
			int r = 0;
			if(client.handshake) {
				r = socket_recv(client.socket_fd, &client.hshake_buffer, sizeof(client.hshake_buffer), &client.recv_count, [&]() {
					if(std::memcmp(client.hshake_buffer.password, state.network_state.password, sizeof(state.network_state.password)) != 0) {
						reports::write_debug("host:disconnect: incorrect password\n");
						disconnect_client(state, client, false);
						return;
					}
					send_post_handshake_commands(state, client);
					/* Exit from handshake mode */
					client.handshake = false;
					client.wait_for_header = true;
					state.game_state_updated.store(true, std::memory_order::release);
				});
			} else if(client.wait_for_header) { //expect header
				assert(!client.handshake);
				r = socket_recv(client.socket_fd, &client.recv_buffer_header, sizeof(client.recv_buffer_header), &client.recv_count, [&]() {
					//received header, go into 
					client.wait_for_header = false;
				});
			} else if(!client.wait_for_header) { //expect body
				auto cmd_size = command::get_size(client.recv_buffer_header.type) - sizeof(client.recv_buffer_header);
				r = socket_recv(client.socket_fd, &client.recv_buffer_body, cmd_size, &client.recv_count, [&]() {
					//next command is a header!
					client.wait_for_header = true;
					switch(client.recv_buffer_header.type) {
					case command::command_type::invalid:
					case command::command_type::notify_player_ban:
					case command::command_type::notify_player_kick:
					case command::command_type::notify_save_loaded:
					case command::command_type::notify_reload:
					case command::command_type::advance_tick:
					case command::command_type::notify_start_game:
					case command::command_type::notify_stop_game:
					//case command::command_type::notify_pause_game:
					case command::command_type::notify_player_joins:
					case command::command_type::save_game:
						break; // has to be valid/sendable by client
					default:
						/* Has to be from the nation of the client proper - and early
						discard invalid commands */
						if(client.recv_buffer_header.source == client.playing_as) {
							command::payload tmp;
							tmp.type = client.recv_buffer_header.type;
							tmp.source = client.recv_buffer_header.source;
							tmp.data = client.recv_buffer_body;
							if(command::can_perform_command(state, tmp)) {
								state.network_state.outgoing_commands.push(tmp);
							}
						}
						break;
					}
					reports::write_debug("host:recv:client_cmd: " + std::to_string(uint32_t(client.recv_buffer_header.type)) + "\n");
				});
			}
			if(r != 0) { // error
				reports::write_debug("host:disconnect: in-receive err=" + std::to_string(int32_t(r)) + "::" + get_last_error_msg() + "\n");
				network::disconnect_client(state, client, false);
			}
		}
	}

	void write_network_save(sys::state& state) {
		/* A save lock will be set when we load a save, naturally loading a save implies
		that we have done preload/fill_unsaved so we will skip doing that again, to save a
		bit of sanity on our miserable CPU */
		size_t length = sizeof_save_section(state);
		auto save_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[length]);
		/* Clear the player nation */
	assert(state.local_player_nation == dcon::nation_id{ });
		write_save_section(save_buffer.get(), state); //writeoff data
		// this is an upper bound, since compacting the data may require less space
		state.network_state.current_save_buffer.reset(new uint8_t[ZSTD_compressBound(length) + sizeof(uint32_t) * 2]);
		auto buffer_position = write_network_compressed_section(state.network_state.current_save_buffer.get(), save_buffer.get(), uint32_t(length));
		state.network_state.current_save_length = uint32_t(buffer_position - state.network_state.current_save_buffer.get());
		state.network_state.current_save_checksum = state.get_save_checksum();
	}

	void broadcast_save_to_clients(sys::state& state, command::payload& c, uint8_t const* buffer, uint32_t length, sys::checksum_key const& k) {
		assert(length > 0);
		assert(c.type == command::command_type::notify_save_loaded);
		c.data.notify_save_loaded.checksum = k;
		for(auto& client : state.network_state.clients) {
			if(!client.is_active())
			continue;
			bool send_full = (client.playing_as == c.data.notify_save_loaded.target) || (!c.data.notify_save_loaded.target);
			if(send_full) {
				/* Reset date for lag detection */
				client.last_game_date = state.current_date;
				/* And then we have to first send the command payload itself */
				client.save_stream_size = size_t(length);
				c.data.notify_save_loaded.length = size_t(length);
				socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
				/* And then the bulk payload! */
				client.save_stream_offset = client.total_sent_bytes + client.send_buffer.size();
				socket_add_to_send_queue(client.send_buffer, buffer, size_t(length));
				reports::write_debug("host:send:save: " + std::to_string(uint32_t(length)) + "\n");
			}
		}
	}

	void broadcast_to_clients(sys::state& state, command::payload& c) {
		if(c.type == command::command_type::save_game)
		return;
		assert(c.type != command::command_type::notify_save_loaded);
		/* Propagate to all the clients */
		for(auto& client : state.network_state.clients) {
			if(client.is_active()) {
				socket_add_to_send_queue(client.send_buffer, &c, command::get_size(c.type));
			}
		}
	}

	static void accept_new_clients(sys::state& state) {
		/* Check if any new clients are to join us */
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(state.network_state.socket_fd, &rfds);
	struct timeval tv{};
		tv.tv_sec = 0;
		tv.tv_usec = 1000;
		if(select(socket_t(int(state.network_state.socket_fd) + 1), &rfds, nullptr, nullptr, &tv) <= 0)
		return;
	
		// Find available slot for client
		for(auto& client : state.network_state.clients) {
			if(client.is_active())
				continue;
			socklen_t addr_len = state.network_state.as_v6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);
			client.socket_fd = accept(state.network_state.socket_fd, (struct sockaddr*)&client.address, &addr_len);
			if(client.is_banned(state)) {
				reports::write_debug("host:reject: Banned client attempted connection\n");
				disconnect_client(state, client, false);
				break;
			}
			if(state.current_scene.final_scene) {
				reports::write_debug("host:reject: game ended, client wanted to connect\n");
				disconnect_client(state, client, false);
				break;
			}
			/* Send it data so she is in sync with everyone else! */
			client.playing_as = get_temp_nation(state);
			client.last_game_date = state.current_date; /* It'd be the current date (for lag detection) */
			assert(client.playing_as);
			{ /* Tell the client their assigned nation */
				server_handshake_data hshake;
				hshake.seed = state.game_seed;
				hshake.assigned_nation = client.playing_as;
				hshake.scenario_checksum = state.scenario_checksum;
				hshake.save_checksum = state.get_save_checksum();
				socket_add_to_send_queue(client.early_send_buffer, &hshake, sizeof(hshake));
			}
			reports::write_debug("host:send:cmd: handshake -> " + std::to_string(client.playing_as.index()) + "\n");
			return;
		}
	}

	void send_and_receive_commands(sys::state& state) {
		if(state.network_state.finished)
		return;

		bool command_executed = false;
		if(state.network_mode == sys::network_mode_type::host) {
			receive_from_clients(state); // receive new commands
			// send the commands of the server to all the clients
			auto* c = state.network_state.outgoing_commands.front();
			while(c) {
				// Clients can't send console commands, but we can
				if(!command::is_console_command(c->type)
				|| c->source == state.local_player_nation) {
					// Generate checksum on the spot
					if(c->type == command::command_type::advance_tick) {
						if(state.current_date.to_ymd(state.start_date).day == 1 || state.cheat_data.daily_oos_check) {
							c->data.advance_tick.checksum = state.get_save_checksum();
						}
					}
					broadcast_to_clients(state, *c);
					command::execute_command(state, *c);
					command_executed = true;
					reports::write_debug("host:receive:cmd: " + std::to_string(uint32_t(c->type)) + "\n");
				}
				state.network_state.outgoing_commands.pop();
				c = state.network_state.outgoing_commands.front();
			}

			//accept should be after the commands are processed!
			//otherwise someone joining fast enough will have the same nation!
			accept_new_clients(state); // accept new connections
			for(auto& client : state.network_state.clients) {
				if(client.is_active()) {
					if(client.handshake) {
						if(client.early_send_buffer.size() > 0) {
							size_t old_size = client.early_send_buffer.size();
							int r = socket_send(client.socket_fd, client.early_send_buffer);
							if(r != 0) { // error
								reports::write_debug("host:disconnect: in-send-EARLY err=" + std::to_string(int32_t(r)) + "::" + get_last_error_msg() + "\n");
								disconnect_client(state, client, false);
								continue;
							}
							client.total_sent_bytes += old_size - client.early_send_buffer.size();
							if(old_size != client.early_send_buffer.size()) {
								reports::write_debug("host:send:stats: [EARLY] " + std::to_string(uint32_t(client.total_sent_bytes)) + " bytes\n");
							}
						}
					} else {
						if(client.send_buffer.size() > 0) {
							size_t old_size = client.send_buffer.size();
							int r = socket_send(client.socket_fd, client.send_buffer);
							if(r != 0) { // error
								reports::write_debug("host:disconnect: in-send-INGAME err=" + std::to_string(int32_t(r)) + "::" + get_last_error_msg() + "\n");
								disconnect_client(state, client, false);
								continue;
							}
							client.total_sent_bytes += old_size - client.send_buffer.size();
							if(old_size != client.send_buffer.size()) {
								reports::write_debug("host:send:stats: [SEND] " + std::to_string(uint32_t(client.total_sent_bytes)) + " bytes\n");
							}
						}
					}
				}
			}
		} else if(state.network_mode == sys::network_mode_type::client) {
			if(state.network_state.handshake) {
				/* Send our client's handshake */
				int r = socket_recv(state.network_state.socket_fd, &state.network_state.s_hshake, sizeof(state.network_state.s_hshake), &state.network_state.recv_count, [&]() {
					reports::write_debug("client:recv:handshake: OK\n");
					if(!state.scenario_checksum.is_equal(state.network_state.s_hshake.scenario_checksum)) {
						bool found_match = false;
						// Find a scenario with a matching checksum
						auto dir = simple_fs::get_or_create_scenario_directory();
						for(const auto& uf : simple_fs::list_files(dir, NATIVE(".bin"))) {
							if(auto f = simple_fs::open_file(uf); f) {
								auto contents = simple_fs::view_contents(*f);
								sys::scenario_header scen_header;
								if(contents.file_size > sizeof(sys::scenario_header)) {
									sys::read_scenario_header(reinterpret_cast<const uint8_t*>(contents.data), scen_header);
									if(scen_header.version == sys::scenario_file_version
									&& scen_header.checksum.is_equal(state.network_state.s_hshake.scenario_checksum)) {
										if(sys::try_read_scenario_and_save_file(state, simple_fs::get_file_name(uf))) {
											state.fill_unsaved_data();
											found_match = true;
											break;
										}
									}
								}
							}
						}
						if(!found_match) {
							std::string msg = "Could not find a scenario with a matching checksum!\n"
								"Just ask the host for their scenario file and it should work.\n"
								"Host should give you the scenario from:\n"
								"'My Documents\\Victoria Community's Engine\\scenarios\\<Most recent scenario>'"
								"And you place it on that same directory as well.\n";
							window::emit_error_message(msg.c_str(), true);
						}
					}
					state.session_host_checksum = state.network_state.s_hshake.save_checksum;
					state.game_seed = state.network_state.s_hshake.seed;
					state.local_player_nation = state.network_state.s_hshake.assigned_nation;
					state.world.nation_set_is_player_controlled(state.local_player_nation, true);
					/* Send our client handshake back */
					client_handshake_data hshake;
					hshake.nickname = state.network_state.nickname;
					std::memcpy(hshake.password, state.network_state.password, sizeof(hshake.password));
					socket_add_to_send_queue(state.network_state.send_buffer, &hshake, sizeof(hshake));
					state.network_state.handshake = false;
					state.network_state.wait_for_header = true;
					//update map
					state.map_state.set_selected_province(dcon::province_id{});
					state.map_state.unhandled_province_selection = true;
				});
				if(r != 0) { // error
					ui::popup_error_window(state, "Network Error", "Network client handshake receive error: " + get_last_error_msg());
					network::finish(state, false);
					return;
				}
			} else if(state.network_state.save_stream) {
				int r = socket_recv(state.network_state.socket_fd, state.network_state.save_data.data(), state.network_state.save_data.size(), &state.network_state.recv_count, [&]() {
					reports::write_debug("client:recv:save: len=" + std::to_string(uint32_t(state.network_state.save_data.size())) + "\n");
					std::vector<dcon::nation_id> players;
					for(const auto n : state.world.in_nation) {
						if(state.world.nation_get_is_player_controlled(n)) {
							players.push_back(n);
						}
					}
					dcon::nation_id old_local_player_nation = state.local_player_nation;
					//
					state.network_state.save_slock.store(true, std::memory_order::release);
					state.preload();
					with_network_decompressed_section(state.network_state.save_data.data(), [&state](uint8_t const* ptr_in, uint32_t length) {
						read_save_section(ptr_in, ptr_in + length, state);
					});
				state.local_player_nation = dcon::nation_id{ };
					state.fill_unsaved_data();
					assert(state.network_state.save_slock.load(std::memory_order::acquire) == true);
					state.network_state.save_slock.store(false, std::memory_order::release);
					//
					for(const auto n : players)
					state.world.nation_set_is_player_controlled(n, true);
					state.local_player_nation = old_local_player_nation;
					assert(state.world.nation_get_is_player_controlled(state.local_player_nation));
					#ifndef NDEBUG
					auto save_checksum = state.get_save_checksum();
					assert(save_checksum.is_equal(state.session_host_checksum));
					#endif
					state.railroad_built.store(true, std::memory_order::release);
					state.game_state_updated.store(true, std::memory_order::release);
					state.province_ownership_changed.store(true, std::memory_order::release);
					state.province_name_changed.store(true, std::memory_order::release);
					state.network_state.save_data.clear();
					state.network_state.save_stream = false; // go back to normal command loop stuff
				});
				if(r != 0) { // error
					ui::popup_error_window(state, "Network Error", "Network client save stream receive error: " + get_last_error_msg());
					network::finish(state, false);
					return;
				}
			} else if(state.network_state.wait_for_header) {
				int r = socket_recv(state.network_state.socket_fd, &state.network_state.recv_buffer_header, sizeof(state.network_state.recv_buffer_header), &state.network_state.recv_count, [&]() {
					//got header, now listen for bodies
					state.network_state.wait_for_header = false;
				});
				if(r != 0) { // error
					ui::popup_error_window(state, "Network Error", "Network client command receive error: " + get_last_error_msg());
					network::finish(state, false);
					return;
				}
			} else if(!state.network_state.wait_for_header) {
				// receive commands from the server and immediately execute them
				auto cmd_size = command::get_size(state.network_state.recv_buffer_header.type) - sizeof(state.network_state.recv_buffer_header);
				int r = socket_recv(state.network_state.socket_fd, &state.network_state.recv_buffer_body, cmd_size, &state.network_state.recv_count, [&]() {
					state.network_state.wait_for_header = true;
					{
						command::payload tmp;
						tmp.type = state.network_state.recv_buffer_header.type;
						tmp.source = state.network_state.recv_buffer_header.source;
						tmp.data = state.network_state.recv_buffer_body;
						command::execute_command(state, tmp);
					}
					command_executed = true;
					// start save stream!
					if(state.network_state.recv_buffer_header.type == command::command_type::notify_save_loaded) {
						uint32_t save_size = state.network_state.recv_buffer_body.notify_save_loaded.length;
						state.network_state.save_stream = true;
						assert(save_size > 0);
						if(save_size >= 32 * 1000 * 1000) { // 32 MB
							ui::popup_error_window(state, "Network Error", "Network save stream too big: " + get_last_error_msg());
							network::finish(state, false);
							return;
						}
						state.network_state.save_data.resize(static_cast<size_t>(save_size));
					}
					reports::write_debug("client:recv:cmd: " + std::to_string(uint32_t(state.network_state.recv_buffer_header.type)) + "\n");
				});
				if(r != 0) { // error
					ui::popup_error_window(state, "Network Error", "Network client command receive error: " + get_last_error_msg());
					network::finish(state, false);
					return;
				}
			}

			if(!state.network_state.handshake && !state.network_state.save_stream) {
				// send the outgoing commands to the server and flush the entire queue
				auto* c = state.network_state.outgoing_commands.front();
				while(c) {
					reports::write_debug("client:send:cmd: " + std::to_string(uint32_t(c->type)) + "\n");
					if(c->type == command::command_type::save_game) {
						command::execute_command(state, *c);
						command_executed = true;
					} else {
						socket_add_to_send_queue(state.network_state.send_buffer, c, command::get_size(c->type));
					}
					state.network_state.outgoing_commands.pop();
					c = state.network_state.outgoing_commands.front();
				}
			}

			/* Do not send commands while we're on save stream mode! */
			if(!state.network_state.save_stream) {
				if(socket_send(state.network_state.socket_fd, state.network_state.send_buffer) != 0) { // error
					ui::popup_error_window(state, "Network Error", "Network client command send error: " + get_last_error_msg());
					network::finish(state, false);
					return;
				}
			}
			assert(state.network_state.early_send_buffer.empty()); //do not use the early send buffer
		}

		if(command_executed) {
			if(state.network_state.out_of_sync && !state.network_state.reported_oos) {
				command::notify_player_oos(state, state.local_player_nation);
				state.network_state.reported_oos = true;
			}
			state.game_state_updated.store(true, std::memory_order::release);
		}
	}

	void finish(sys::state& state, bool notify_host) {
		if(state.network_mode == sys::network_mode_type::single_player) {
			return; // Do nothing in singleplayer
		}

		state.network_state.finished = true;
		if(notify_host && state.network_mode == sys::network_mode_type::client) {
			if(!state.network_state.save_stream) {
				// send the outgoing commands to the server and flush the entire queue
				{
					auto* c = state.network_state.outgoing_commands.front();
					while(c) {
						if(c->type == command::command_type::save_game) {
							command::execute_command(state, *c);
						} else {
							socket_add_to_send_queue(state.network_state.send_buffer, c, command::get_size(c->type));
						}
						state.network_state.outgoing_commands.pop();
						c = state.network_state.outgoing_commands.front();
					}
				}
				command::payload c{};
				c.type = command::command_type::notify_player_leaves;
				c.source = state.local_player_nation;
				c.data.notify_leave.make_ai = true;
				socket_add_to_send_queue(state.network_state.send_buffer, &c, command::get_size(c.type));
				while(state.network_state.send_buffer.size() > 0) {
					if(socket_send(state.network_state.socket_fd, state.network_state.send_buffer) != 0) { // error
						//ui::popup_error_window(state, "Network Error", "Network client command send error: " + get_last_error_msg());
						break;
					}
				}
			}
		}
	
		socket_shutdown(state.network_state.socket_fd);
#ifdef _WIN32
		WSACleanup();
#endif
	}

	void ban_player(sys::state& state, client_data& client) {
		if(client.is_active()) {
			socket_shutdown(client.socket_fd);
			client.socket_fd = 0;
			if(state.network_state.as_v6) {
				auto sa = (struct sockaddr_in6*)&client.address;
				state.network_state.v6_banlist.push_back(sa->sin6_addr);
			} else {
				auto sa = (struct sockaddr_in*)&client.address;
				state.network_state.v4_banlist.push_back(sa->sin_addr);
			}
		}
	}

	void kick_player(sys::state& state, client_data& client) {
		if(client.is_active()) {
			socket_shutdown(client.socket_fd);
			client.socket_fd = 0;
		}
	}

	void switch_player(sys::state& state, dcon::nation_id new_n, dcon::nation_id old_n) {
		state.network_state.map_of_player_names.insert_or_assign(new_n.index(), state.network_state.map_of_player_names[old_n.index()]);
		if(state.network_mode == sys::network_mode_type::host) {
			for(auto& client : state.network_state.clients) {
				if(client.is_active() && client.playing_as == old_n) {
					client.playing_as = new_n;
				}
			}
		}
	}

}
