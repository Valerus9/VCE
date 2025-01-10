#include <algorithm>
#include <functional>
#include <thread>
#include "system_state.hpp"
#include "constants.hpp"
#include "dcon.hpp"
#include "map_modes.hpp"
#include "opengl_wrapper.hpp"
#include "window.hpp"
#include "parsers_declarations.hpp"
#include "map_tooltip.hpp"
#include "demographics.hpp"
#include "rebels.hpp"
#include "ai.hpp"
#include "effects.hpp"
#include "prng.hpp"
#include "blake2.h"
#include "reports.hpp"
#include "serialization.hpp"

#include "gui_element_base.hpp"
#include "gui_element_templates.hpp"
#include "gui_leader_select.hpp"
#include "gui_diplomacy_request_window.hpp"
#include "gui_console.hpp"
#include "gui_message_window.hpp"
#include "gui_event.hpp"
#include "gui_message_settings_window.hpp"
#include "gui_chat_window.hpp"
#include "gui_error_window.hpp"
#include "gui_diplomacy_request_topbar.hpp"
#include "gui_production_window.hpp"
#include "gui_diplomacy_window.hpp"
#include "gui_technology_window.hpp"
#include "gui_politics_window.hpp"
#include "gui_budget_window.hpp"
#include "gui_trade_window.hpp"
#include "gui_population_window.hpp"
#include "gui_military_window.hpp"
#include "gui_naval_combat.hpp"
#include "gui_land_combat.hpp"
#include "gui_nation_picker.hpp"
#include "gui_state_select.hpp"
#include "gui_minimap.hpp"
#include "gui_unit_panel.hpp"
#include "gui_topbar.hpp"
#include "gui_province_window.hpp"
#include "gui_outliner_window.hpp"
#include "gui_leader_tooltip.hpp"
#include "gui_end_window.hpp"
#include "gui_map_legend.hpp"
#include "gui_map_icons.hpp"

namespace sys {
	void state::start_state_selection(state_selection_data& data) {
		if(state_selection) {
			state_selection->on_cancel(*this);
		}	
		state_selection = data;

		game_scene::switch_scene(*this, game_scene::scene_id::in_game_state_selector);

		if(ui_state.select_states_legend) {
			ui_state.select_states_legend->impl_on_update(*this);
		}
	}
	void state::finish_state_selection() {
		game_scene::switch_scene(*this, game_scene::scene_id::in_game_basic);
	}

	void state::state_select(dcon::state_definition_id sdef) {
		assert(state_selection);
		if(std::find(state_selection->selectable_states.begin(), state_selection->selectable_states.end(), sdef) != state_selection->selectable_states.end()) {
			if(state_selection->single_state_select) {
				state_selection->on_select(*this, sdef);
				finish_state_selection();
			} else {
				/*auto it = std::find(state.selected_states.begin(), state.selected_states.end(), sdef);
				if(it == state.selected_states.end()) {
					on_select(sdef);
				} else {
					state.selected_states.erase(std::remove(state.selected_states.begin(), state.selected_states.end(), sdef), state.selected_states.end());
				}*/
				reports::write_debug("Invalid state selector state\n");
				std::abort();
			}
		}
		map_state.update(*this);
	}

	//
	// window event functions
	//

	void state::on_rbutton_down(int32_t x, int32_t y, key_modifiers mod) {
		game_scene::on_rbutton_down(*this, x, y, mod);
	}

	void state::on_mbutton_down(int32_t x, int32_t y, key_modifiers mod) {
		// Lose focus on text
		ui_state.edit_target = nullptr;
		map_state.on_mbuttom_down(x, y, x_size, y_size, mod);
	}

	void state::on_lbutton_down(int32_t x, int32_t y, key_modifiers mod) {
		game_scene::on_lbutton_down(*this, x, y, mod);
	}

	void state::on_rbutton_up(int32_t x, int32_t y, key_modifiers mod) {

	}

	void state::on_mbutton_up(int32_t x, int32_t y, key_modifiers mod) {
		map_state.on_mbuttom_up(x, y, mod);
	}
	void state::on_lbutton_up(int32_t x, int32_t y, key_modifiers mod) {
		game_scene::on_lbutton_up(*this, x, y, mod);
	}
	void state::on_mouse_move(int32_t x, int32_t y, key_modifiers mod) {
		map_state.on_mouse_move(x, y, x_size, y_size, mod);
		if(map_state.is_dragging) {
			if(ui_state.mouse_sensitive_target) {
				ui_state.mouse_sensitive_target->set_visible(*this, false);
				ui_state.mouse_sensitive_target = nullptr;
			}
		} else if(ui_state.under_mouse != nullptr) {
			auto r = ui_state.under_mouse->impl_on_mouse_move(*this, ui_state.relative_mouse_location.x,
				ui_state.relative_mouse_location.y, mod);
		}
		if(ui_state.mouse_sensitive_target) {
			auto mx = int32_t(x / user_settings.ui_scale);
			auto my = int32_t(y / user_settings.ui_scale);
			if(mx < ui_state.target_ul_bounds.x || mx > ui_state.target_lr_bounds.x || my < ui_state.target_ul_bounds.y || my > ui_state.target_lr_bounds.y) {
				ui_state.mouse_sensitive_target->set_visible(*this, false);
				ui_state.mouse_sensitive_target = nullptr;
			}
		}
	}
	void state::on_mouse_drag(int32_t x, int32_t y, key_modifiers mod) { // called when the left button is held down
		is_dragging = true;
		if(ui_state.drag_target) {
			ui_state.drag_target->on_drag(*this, int32_t(mouse_x_position / user_settings.ui_scale),
			int32_t(mouse_y_position / user_settings.ui_scale), int32_t(x / user_settings.ui_scale),
			int32_t(y / user_settings.ui_scale), mod);
		}
	}
	void state::on_drag_finished(int32_t x, int32_t y, key_modifiers mod) { // called when the left button is released after one or more drag events
		if(ui_state.drag_target) {
			ui_state.drag_target->on_drag_finish(*this);
			ui_state.drag_target = nullptr;
		}
	}
	void state::on_resize(int32_t x, int32_t y, window::window_state win_state) {
		ogl::deinitialize_msaa(*this);
		ogl::initialize_msaa(*this, x, y);

		if(win_state != window::window_state::minimized) {
			ui_state.root->base_data.size.x = int16_t(x / user_settings.ui_scale);
			ui_state.root->base_data.size.y = int16_t(y / user_settings.ui_scale);
			if(ui_state.outliner_window) {
				ui_state.outliner_window->impl_on_update(*this);
			}
		}
	}

	void state::on_mouse_wheel(int32_t x, int32_t y, key_modifiers mod, float amount) { // an amount of 1.0 is one "click" of the wheel
		//update en demand
		ui::element_base* root_elm = current_scene.get_root(*this);
		if(root_elm) {
			ui_state.scroll_target = root_elm->impl_probe_mouse(*this,
			int32_t(mouse_x_position / user_settings.ui_scale),
			int32_t(mouse_y_position / user_settings.ui_scale),
			ui::mouse_probe_type::scroll).under_mouse;
			auto belongs_on_map = [&](ui::element_base* b) {
				while(b != nullptr) {
					if(b == ui_state.units_root.get()
					|| b == ui_state.colonizations_root.get()
					|| b == ui_state.rgos_root.get())
						return true;
					b = b->parent;
				}
				return false;
			};
			if(ui_state.scroll_target != nullptr) {
				ui_state.scroll_target->impl_on_scroll(*this, ui_state.relative_mouse_location.x, ui_state.relative_mouse_location.y, amount, mod);
			} else if(ui_state.under_mouse == nullptr || belongs_on_map(ui_state.under_mouse)) {
				map_state.on_mouse_wheel(x, y, x_size, y_size, mod, amount);
				if(ui_state.mouse_sensitive_target) {
					ui_state.mouse_sensitive_target->set_visible(*this, false);
					ui_state.mouse_sensitive_target = nullptr;
				}
			}
		}
	}
	void state::on_key_down(virtual_key keycode, key_modifiers mod) {
		if(keycode == virtual_key::CONTROL)
		ui_state.ctrl_held_down = true;

		game_scene::on_key_down(*this, keycode, mod);
	}

	void state::on_key_up(virtual_key keycode, key_modifiers mod) {
		if(keycode == virtual_key::CONTROL)
		ui_state.ctrl_held_down = false;

		//TODO: move to according scenes
		if(user_settings.wasd_for_map_movement) {
			switch(keycode) {
			case sys::virtual_key::W:
				keycode = sys::virtual_key::UP;
				break;
			case sys::virtual_key::A:
				keycode = sys::virtual_key::LEFT;
				break;
			case sys::virtual_key::S:
				keycode = sys::virtual_key::DOWN;
				break;
			case sys::virtual_key::D:
				keycode = sys::virtual_key::RIGHT;
				break;
			}
		}
		map_state.on_key_up(keycode, mod);
	}
	void state::on_text(char32_t c) { // c is win1250 codepage value
		if(ui_state.edit_target) {
			ui_state.edit_target->on_text(*this, c);
		}
	}

	inline constexpr int32_t tooltip_width = 400;

	void state::update_tech_queue() {
		if(!ui_state.tech_queue.empty()) {
			if(!world.nation_get_current_research(local_player_nation)) {
				for(auto it = ui_state.tech_queue.begin(); it != ui_state.tech_queue.end(); it++) {
					if(world.nation_get_active_technologies(local_player_nation, *it)) {
						ui_state.tech_queue.erase(it);
						break;
					}
					if(command::can_start_research(*this, local_player_nation, *it)) {
						// can research, so research it
						command::start_research(*this, local_player_nation, *it);
						ui_state.tech_queue.erase(it);
						break;
					}
				}
			}
		}
	}

	void state::update_render() {
		auto game_state_was_updated = game_state_updated.exchange(false, std::memory_order::acq_rel);
		if(game_state_was_updated && !current_scene.starting_scene && !ui_state.lazy_load_in_game) {
			window::change_cursor(*this, window::cursor_type::busy);
			ui::create_in_game_windows(*this);
			window::change_cursor(*this, window::cursor_type::normal);
		}
		auto ownership_update = province_ownership_changed.exchange(false, std::memory_order::acq_rel);
		if(ownership_update) {
			if(user_settings.map_label != sys::map_label_mode::none) {
				map::update_text_lines(*this, map_state.map_data);
			}
		}
		auto name_change_update = province_name_changed.exchange(false, std::memory_order::acq_rel);
		if(name_change_update) {
			if(user_settings.map_label != sys::map_label_mode::none) {
				map::update_province_text_lines(*this, map_state.map_data);
			}
		}
		// Update next frame
		if(game_state_was_updated) {
			map_state.map_data.update_fog_of_war(*this);
		}

		if(game_state_was_updated) {
			update_tech_queue();
			current_scene.on_game_state_update(*this);
			nations::update_ui_rankings(*this);
			// Processing of (gamestate <=> ui) queues
			if(current_scene.accept_events) {
				// National events
				auto* c1 = new_n_event.front();
				while(c1) {
					auto auto_choice = world.national_event_get_auto_choice(c1->e);
					if(auto_choice == 0) {
						ui::new_event_window(*this, *c1);
						if(world.national_event_get_is_major(c1->e)) {
							sound::play_effect(*this, sound::get_major_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
						} else {
							sound::play_effect(*this, sound::get_major_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
						}
					} else {
						command::make_event_choice(*this, *c1, uint8_t(auto_choice - 1));
					}
					new_n_event.pop();
					c1 = new_n_event.front();
				}
				// Free national events
				auto* c2 = new_f_n_event.front();
				while(c2) {
					auto auto_choice = world.free_national_event_get_auto_choice(c2->e);
					if(auto_choice == 0) {
						ui::new_event_window(*this, *c2);
						if(world.free_national_event_get_is_major(c2->e)) {
							sound::play_effect(*this, sound::get_major_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
						} else {
							sound::play_effect(*this, sound::get_major_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
						}
					} else {
						command::make_event_choice(*this, *c2, uint8_t(auto_choice - 1));
					}
					new_f_n_event.pop();
					c2 = new_f_n_event.front();
				}
				// Provincial events
				auto* c3 = new_p_event.front();
				while(c3) {
					auto auto_choice = world.provincial_event_get_auto_choice(c3->e);
					if(auto_choice == 0) {
						ui::new_event_window(*this, *c3);
						sound::play_effect(*this, sound::get_minor_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
					} else {
						command::make_event_choice(*this, *c3, uint8_t(auto_choice - 1));
					}
					new_p_event.pop();
					c3 = new_p_event.front();
				}
				// Free provincial events
				auto* c4 = new_f_p_event.front();
				while(c4) {
					auto auto_choice = world.free_provincial_event_get_auto_choice(c4->e);
					if(auto_choice == 0) {
						ui::new_event_window(*this, *c4);
						sound::play_effect(*this, sound::get_minor_event_sound(*this), user_settings.effects_volume * user_settings.master_volume);
					} else {
						command::make_event_choice(*this, *c4, uint8_t(auto_choice - 1));
					}
					new_f_p_event.pop();
					c4 = new_f_p_event.front();
				}
				// land battle reports
				{
					auto* lr = land_battle_reports.front();
					while(lr) {
						if(local_player_nation) {
							if(lr->player_on_winning_side == true && (!lr->attacking_nation || !lr->defending_nation)) {
								if(user_settings.notify_rebels_defeat) {
									ui::land_combat_end_popup::make_new_report(*this, *lr);
								} else {
									//do not pester user with defeat of rebels
								}
							} else {
								ui::land_combat_end_popup::make_new_report(*this, *lr);
							}
						}
						land_battle_reports.pop();
						lr = land_battle_reports.front();
					}
				}
				// naval battle reports
				{
					auto* lr = naval_battle_reports.front();
					while(lr) {
						ui::naval_combat_end_popup::make_new_report(*this, *lr);
						naval_battle_reports.pop();
						lr = naval_battle_reports.front();
					}
				}
				// Diplomatic messages
				auto* c5 = new_requests.front();
				bool had_diplo_msg = false;
				while(c5) {
					if(user_settings.diplomatic_message_popup) {
						static_cast<ui::diplomacy_request_window*>(ui_state.request_window)->messages.push_back(*c5);
					} else {
						static_cast<ui::diplomatic_message_topbar_listbox*>(ui_state.request_topbar_listbox)->messages.push_back(*c5);
					}
					had_diplo_msg = true;
					new_requests.pop();
					c5 = new_requests.front();
				}
				if(had_diplo_msg) {
					sound::play_effect(*this, sound::get_diplomatic_request_sound(*this), user_settings.interface_volume * user_settings.master_volume);
				}

				// Log messages
				auto* c6 = new_messages.front();
				while(c6) {
					{
						auto ymd = current_date.to_ymd(start_date);
						auto source_tag = c6->source ? nations::int_to_tag(world.national_identity_get_identifying_int(world.nation_get_identity_from_identity_holder(c6->source))) : std::string("___");
						auto target_tag = c6->target ? nations::int_to_tag(world.national_identity_get_identifying_int(world.nation_get_identity_from_identity_holder(c6->target))) : std::string("___");
						auto third_tag = c6->third ? nations::int_to_tag(world.national_identity_get_identifying_int(world.nation_get_identity_from_identity_holder(c6->third))) : std::string("___");
						auto date_str = std::to_string(ymd.year) + "." + std::to_string(ymd.month) + "." + std::to_string(ymd.day);
						reports::write_debug(date_str + "> " + source_tag + "," + target_tag + "," + third_tag + ": " + std::string(c6->title) + "\n");
					}

					auto base_type = c6->type;
					auto setting_types = sys::message_setting_map[int32_t(base_type)];
					uint8_t settings_bits = 0;
					if(setting_types.source != sys::message_setting_type::count) {
						if(c6->source == local_player_nation) {
							settings_bits |= user_settings.self_message_settings[int32_t(setting_types.source)];
						} else if(notification::nation_is_interesting(*this, c6->source)) {
							settings_bits |= user_settings.interesting_message_settings[int32_t(setting_types.source)];
						} else {
							settings_bits |= user_settings.other_message_settings[int32_t(setting_types.source)];
						}
					}
					if(setting_types.target != sys::message_setting_type::count) {
						if(c6->target == local_player_nation) {
							settings_bits |= user_settings.self_message_settings[int32_t(setting_types.target)];
						} else if(notification::nation_is_interesting(*this, c6->target)) {
							settings_bits |= user_settings.interesting_message_settings[int32_t(setting_types.target)];
						} else {
							settings_bits |= user_settings.other_message_settings[int32_t(setting_types.target)];
						}
					}
					if(setting_types.third != sys::message_setting_type::count) {
						if(c6->third == local_player_nation) {
							settings_bits |= user_settings.self_message_settings[int32_t(setting_types.third)];
						} else if(notification::nation_is_interesting(*this, c6->third)) {
							settings_bits |= user_settings.interesting_message_settings[int32_t(setting_types.third)];
						} else {
							settings_bits |= user_settings.other_message_settings[int32_t(setting_types.third)];
						}
					}

					if((settings_bits & message_response::log) && ui_state.msg_log_window) {
						static_cast<ui::message_log_window*>(ui_state.msg_log_window)->messages.push_back(*c6);
					}
					if((settings_bits & message_response::popup) != 0) {
						if(c6->source == local_player_nation && (base_type == message_base_type::major_event || base_type == message_base_type::national_event || base_type == message_base_type::province_event)) {
							// do nothing -- covered by event window logic
						} else {
							if(ui_state.msg_window) {
								static_cast<ui::message_window*>(ui_state.msg_window)->messages.push_back(*c6);
							}
							if((settings_bits & message_response::pause) != 0 && network_mode == sys::network_mode_type::single_player) {
								ui_pause.store(true, std::memory_order_release);
							}
						}
					}

					// Sound effects(tm)
					if(settings_bits != 0 && local_player_nation && (c6->source == local_player_nation || c6->target == local_player_nation)) {
						switch(base_type) {
						case message_base_type::war:
							sound::play_effect(*this, sound::get_declaration_of_war_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::peace_accepted:
							sound::play_effect(*this, sound::get_peace_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::tech:
							sound::play_effect(*this, sound::get_technology_finished_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::factory_complete:
							sound::play_effect(*this, sound::get_factory_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::fort_complete:
							sound::play_effect(*this, sound::get_fort_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::rr_complete:
							sound::play_effect(*this, sound::get_railroad_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::naval_base_complete:
							sound::play_effect(*this, sound::get_naval_base_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::electionstart:
						case message_base_type::electiondone:
							sound::play_effect(*this, sound::get_election_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::revolt:
							sound::play_effect(*this, sound::get_revolt_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::army_built:
							sound::play_effect(*this, sound::get_army_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::navy_built:
							sound::play_effect(*this, sound::get_navy_built_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::alliance_declined:
						case message_base_type::ally_called_declined:
						case message_base_type::crisis_join_offer_declined:
						case message_base_type::crisis_resolution_declined:
						case message_base_type::mil_access_declined:
						case message_base_type::peace_rejected:
							sound::play_effect(*this, sound::get_decline_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::alliance_starts:
						case message_base_type::ally_called_accepted:
						case message_base_type::crisis_join_offer_accepted:
						case message_base_type::crisis_resolution_accepted:
						case message_base_type::mil_access_start:
							sound::play_effect(*this, sound::get_accept_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::chat_message:
							sound::play_interface_sound(*this, sound::get_chat_message_sound(*this), user_settings.effects_volume * user_settings.master_volume);
							break;
						case message_base_type::province_event:
						case message_base_type::national_event:
						case message_base_type::major_event:
							//Sound effect is played on above logic (free/non-free loop events above)
							break;
						default:
							break;
						}
					}

					new_messages.pop();
					c6 = new_messages.front();
				}
				// Naval Combat Reports
				auto* c7 = naval_battle_reports.front();
				while(c7) {
					if(ui_state.endof_navalcombat_windows.size() == 0) {
						ui_state.endof_navalcombat_windows.push_back(ui::make_element_by_type<ui::naval_combat_end_popup>(*this, "endofnavalcombatpopup"));
					}
					//static_cast<ui::naval_combat_window*>(ui_state.navalcombat_windows.back().get())->messages.push_back(*c7);
					static_cast<ui::naval_combat_end_popup*>(ui_state.endof_navalcombat_windows.back().get())->report = *c7;
					ui_state.root->add_child_to_front(std::move(ui_state.endof_navalcombat_windows.back()));
					ui_state.endof_navalcombat_windows.pop_back();
					naval_battle_reports.pop();
					c7 = naval_battle_reports.front();
				}
				if(ui_state.request_window
				&& !static_cast<ui::diplomacy_request_window*>(ui_state.request_window)->messages.empty()) {
					ui_state.request_window->set_visible(*this, true);
					ui_state.root->move_child_to_front(ui_state.request_window);
				}
				if(ui_state.msg_window
				&& !static_cast<ui::message_window*>(ui_state.msg_window)->messages.empty()) {
					ui_state.msg_window->set_visible(*this, true);
					ui_state.root->move_child_to_front(ui_state.msg_window);
				}
			}

			ui::element_base* root_elm = current_scene.get_root(*this);
			auto mouse_probe = root_elm->impl_probe_mouse(*this, int32_t(mouse_x_position / user_settings.ui_scale),
			int32_t(mouse_y_position / user_settings.ui_scale), ui::mouse_probe_type::click);
			auto tooltip_probe = root_elm->impl_probe_mouse(*this, int32_t(mouse_x_position / user_settings.ui_scale),
			int32_t(mouse_y_position / user_settings.ui_scale), ui::mouse_probe_type::tooltip);
			if(!mouse_probe.under_mouse && map_state.get_zoom() > map::zoom_close) {
				mouse_probe = current_scene.recalculate_mouse_probe(*this, mouse_probe, tooltip_probe);
				tooltip_probe = current_scene.recalculate_tooltip_probe(*this, mouse_probe, tooltip_probe);
			}

			root_elm->impl_on_update(*this);
			current_scene.on_game_state_update_update_ui(*this);
			if(ui_state.last_tooltip && ui_state.tooltip->is_visible()) {
				auto type = ui_state.last_tooltip->has_tooltip(*this);
				if(type == ui::tooltip_behavior::variable_tooltip || type == ui::tooltip_behavior::position_sensitive_tooltip) {
					auto container = text::create_columnar_layout(*this, ui_state.tooltip->internal_layout,
						text::layout_parameters{ 0, 0, tooltip_width, int16_t(root_elm->base_data.size.y - 20), ui_state.tooltip_font, 0,
								text::alignment::left,
								text::text_color::white, true },
							10);
					ui_state.last_tooltip->update_tooltip(*this, tooltip_probe.relative_location.x, tooltip_probe.relative_location.y,
						container);
					populate_shortcut_tooltip(*this, *ui_state.last_tooltip, container);
					if(container.native_rtl == text::layout_base::rtl_status::rtl) {
						container.used_width = -container.used_width;
						for(auto& t : container.base_layout.contents) {
							t.x += 16 + container.used_width;
							t.y += 16;
						}
					} else {
						for(auto& t : container.base_layout.contents) {
							t.x += 16;
							t.y += 16;
						}
					}
					ui_state.tooltip->base_data.size.x = int16_t(container.used_width + 32);
					ui_state.tooltip->base_data.size.y = int16_t(container.used_height + 32);
					ui_state.tooltip->set_visible(*this, container.used_width > 0);
				}
			}
		}
	}

	void state::render() { // called to render the frame may (and should) delay returning until the frame is rendered, including
		// waiting for vsync
		if(!current_scene.get_root)
			return;

		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		if(ui_state.last_render_time == std::chrono::time_point<std::chrono::steady_clock>{}) {
			ui_state.last_render_time = now;
		}
		if(ui_state.fps_timer > 20) {
			auto microseconds_since_last_render = std::chrono::duration_cast<std::chrono::microseconds>(now - ui_state.last_render_time);
			auto frames_per_second = 1.f / float(microseconds_since_last_render.count() / 1e6);
			ui_state.last_fps = frames_per_second;
			ui_state.fps_timer = 0;
			ui_state.last_render_time = now;
		}
		ui_state.fps_timer += 1;

		if(ui_state.scrollbar_timer > 500 * (ui_state.last_fps / 60)) {
			ui_state.scrollbar_continuous_movement = true;
			if(ui_state.left_mouse_hold_target != nullptr) {
			Cyto::Any payload = ui::scrollbar_settings{};
				ui_state.left_mouse_hold_target->impl_set(*this, payload);
			}
		}

		if(ui_state.left_mouse_hold_target != nullptr) {
			ui_state.scrollbar_timer += 1;
		}

		current_scene.clean_up(*this);

		ui::element_base* root_elm = current_scene.get_root(*this);
		root_elm->base_data.size.x = ui_state.root->base_data.size.x;
		root_elm->base_data.size.y = ui_state.root->base_data.size.y;

		auto mouse_probe = root_elm->impl_probe_mouse(*this, int32_t(mouse_x_position / user_settings.ui_scale),
		int32_t(mouse_y_position / user_settings.ui_scale), ui::mouse_probe_type::click);
		auto tooltip_probe = root_elm->impl_probe_mouse(*this, int32_t(mouse_x_position / user_settings.ui_scale),
		int32_t(mouse_y_position / user_settings.ui_scale), ui::mouse_probe_type::tooltip);
		if(!mouse_probe.under_mouse && map_state.get_zoom() > map::zoom_close) {
			mouse_probe = current_scene.recalculate_mouse_probe(*this, mouse_probe, tooltip_probe);
			tooltip_probe = current_scene.recalculate_tooltip_probe(*this, mouse_probe, tooltip_probe);
		}

		ui::display_pending_error_window(*this);

		// Do not update state sensitive updates!
		if(network_state.save_slock.load(std::memory_order::acquire) == false) {
			update_render();
		}

		if(ui_state.last_tooltip != tooltip_probe.under_mouse) {
			ui_state.last_tooltip = tooltip_probe.under_mouse;

			if(tooltip_probe.under_mouse) {
				//if(tooltip_probe.under_mouse->base_data.get_element_type() == ui::element_type::button) {
					//	sound::play_interface_sound(*this, sound::get_hover_sound(*this), user_settings.interface_volume * user_settings.master_volume);
				//}
				auto type = ui_state.last_tooltip->has_tooltip(*this);
				if(type != ui::tooltip_behavior::no_tooltip) {
					auto container = text::create_columnar_layout(*this, ui_state.tooltip->internal_layout,
					text::layout_parameters{ 0, 0, tooltip_width,int16_t(root_elm->base_data.size.y - 20), ui_state.tooltip_font, 0,
					text::alignment::left, text::text_color::white, true }, 10);
					ui_state.last_tooltip->update_tooltip(*this, tooltip_probe.relative_location.x, tooltip_probe.relative_location.y,
						container);
					populate_shortcut_tooltip(*this, *ui_state.last_tooltip, container);
					if(container.native_rtl == text::layout_base::rtl_status::rtl) {
						container.used_width = -container.used_width;
						for(auto& t : container.base_layout.contents) {
							t.x += 16 + container.used_width;
							t.y += 16;
						}
					} else {
						for(auto& t : container.base_layout.contents) {
							t.x += 16;
							t.y += 16;
						}
					}
					ui_state.tooltip->base_data.size.x = int16_t(container.used_width + 32);
					ui_state.tooltip->base_data.size.y = int16_t(container.used_height + 32);
					ui_state.tooltip->set_visible(*this, container.used_width > 0);
				} else {
					ui_state.tooltip->set_visible(*this, false);
				}
			} else {
				ui_state.tooltip->set_visible(*this, false);
			}
		} else if(ui_state.last_tooltip && ui_state.last_tooltip->has_tooltip(*this) == ui::tooltip_behavior::position_sensitive_tooltip) {
			auto container = text::create_columnar_layout(*this, ui_state.tooltip->internal_layout,
			text::layout_parameters{ 0, 0, tooltip_width, int16_t(root_elm->base_data.size.y - 20), ui_state.tooltip_font, 0,
			text::alignment::left, text::text_color::white, true }, 10);
			ui_state.last_tooltip->update_tooltip(*this, tooltip_probe.relative_location.x, tooltip_probe.relative_location.y, container);
			populate_shortcut_tooltip(*this, *ui_state.last_tooltip, container);
			if(container.native_rtl == text::layout_base::rtl_status::rtl) {
				container.used_width = -container.used_width;
				for(auto& t : container.base_layout.contents) {
					t.x += 16 + container.used_width;
					t.y += 16;
				}
			} else {
				for(auto& t : container.base_layout.contents) {
					t.x += 16;
					t.y += 16;
				}
			}
			ui_state.tooltip->base_data.size.x = int16_t(container.used_width + 32);
			ui_state.tooltip->base_data.size.y = int16_t(container.used_height + 32);
			ui_state.tooltip->set_visible(*this, container.used_width > 0);
		}

		if(ui_state.last_tooltip && ui_state.tooltip->is_visible()) {
			// reposition tooltip
			auto target_location = ui::get_absolute_location(*this, *ui_state.last_tooltip);
			if(ui_state.tooltip->base_data.size.y <= root_elm->base_data.size.y - (target_location.y + ui_state.last_tooltip->base_data.size.y)) {
				ui_state.tooltip->base_data.position.y = int16_t(target_location.y + ui_state.last_tooltip->base_data.size.y);
				ui_state.tooltip->base_data.position.x = std::clamp(
					int16_t(target_location.x + (ui_state.last_tooltip->base_data.size.x / 2) - (ui_state.tooltip->base_data.size.x / 2)),
					int16_t(0), int16_t(std::max(root_elm->base_data.size.x - ui_state.tooltip->base_data.size.x, 0)));
			} else if(ui_state.tooltip->base_data.size.x <= root_elm->base_data.size.x - (target_location.x + ui_state.last_tooltip->base_data.size.x)) {
				ui_state.tooltip->base_data.position.x = int16_t(target_location.x + ui_state.last_tooltip->base_data.size.x);
				ui_state.tooltip->base_data.position.y = std::clamp(
					int16_t(target_location.y + (ui_state.last_tooltip->base_data.size.y / 2) - (ui_state.tooltip->base_data.size.y / 2)),
					int16_t(0),
					int16_t(std::max(root_elm->base_data.size.y - ui_state.tooltip->base_data.size.y, 0)));
			} else if(ui_state.tooltip->base_data.size.x <= target_location.x) {
				ui_state.tooltip->base_data.position.x = int16_t(target_location.x - ui_state.tooltip->base_data.size.x);
				ui_state.tooltip->base_data.position.y = std::clamp(
					int16_t(target_location.y + (ui_state.last_tooltip->base_data.size.y / 2) - (ui_state.tooltip->base_data.size.y / 2)),
					int16_t(0), int16_t(std::max(root_elm->base_data.size.y - ui_state.tooltip->base_data.size.y, 0)));
			} else if(ui_state.tooltip->base_data.size.y <= target_location.y) {
				ui_state.tooltip->base_data.position.y = int16_t(target_location.y - ui_state.tooltip->base_data.size.y);
				ui_state.tooltip->base_data.position.x = std::clamp(
					int16_t(target_location.x + (ui_state.last_tooltip->base_data.size.x / 2) - (ui_state.tooltip->base_data.size.x / 2)),
					int16_t(0), int16_t(std::max(root_elm->base_data.size.x - ui_state.tooltip->base_data.size.x, 0)));
			} else {
				ui_state.tooltip->base_data.position.x = std::clamp(
					int16_t(target_location.x + (ui_state.last_tooltip->base_data.size.x / 2) - (ui_state.tooltip->base_data.size.x / 2)),
					int16_t(0), int16_t(std::max(root_elm->base_data.size.x - ui_state.tooltip->base_data.size.x, 0)));
				ui_state.tooltip->base_data.position.y = std::clamp(
					int16_t(target_location.y + (ui_state.last_tooltip->base_data.size.y / 2) - (ui_state.tooltip->base_data.size.y / 2)),
					int16_t(0), int16_t(std::max(root_elm->base_data.size.y - ui_state.tooltip->base_data.size.y, 0)));
			}
		}

		if(current_scene.based_on_map && !mouse_probe.under_mouse && !tooltip_probe.under_mouse) {
			dcon::province_id prov = map_state.get_province_under_mouse(*this, int32_t(mouse_x_position), int32_t(mouse_y_position), x_size, y_size);
			if(map_state.get_zoom() <= map::zoom_close)
			prov = dcon::province_id{};
			if(prov) {
				if(!drag_selecting && (selected_armies.size() > 0 || selected_navies.size() > 0)) {
					bool fail = false;
					for(auto a : selected_armies) {
						if(command::can_move_army(*this, local_player_nation, a, prov).empty()) {
							fail = true;
							break;
						}
					}
					for(auto a : selected_navies) {
						if(command::can_move_navy(*this, local_player_nation, a, prov).empty()) {
							fail = true;
							break;
						}
					}
					if(!fail) {
						auto c = world.province_get_nation_from_province_control(prov);
						if(c != local_player_nation && military::are_at_war(*this, c, local_player_nation)) {
							window::change_cursor(*this, window::cursor_type::hostile_move);
						} else {
							window::change_cursor(*this, window::cursor_type::friendly_move);
						}
					} else {
						window::change_cursor(*this, window::cursor_type::no_move);
					}
				}
			}
		}

		// Have to have the map tooltip down here, and we must check both of the probes
		// Not doing this causes the map tooltip to override some of the regular tooltips (namely the score tooltips)
		if(current_scene.based_on_map && !mouse_probe.under_mouse && !tooltip_probe.under_mouse) {
			dcon::province_id prov = map_state.get_province_under_mouse(*this, int32_t(mouse_x_position), int32_t(mouse_y_position), x_size, y_size);
			if(((map_state.active_map_mode == map_mode::mode::political && !current_scene.overwrite_map_tooltip)
				|| map_state.active_map_mode == map_mode::mode::terrain) && map_state.get_zoom() <= map::zoom_close) {
				prov = dcon::province_id{};
			}
			if(prov) {
				auto container = text::create_columnar_layout(*this, ui_state.tooltip->internal_layout,
				text::layout_parameters{ 0, 0, tooltip_width, int16_t(ui_state.root->base_data.size.y - 20), ui_state.tooltip_font, 0, text::alignment::left, text::text_color::white, true },
				20);
				ui::populate_map_tooltip(*this, container, prov);
				if(container.native_rtl == text::layout_base::rtl_status::rtl) {
					container.used_width = -container.used_width;
					for(auto& t : container.base_layout.contents) {
						t.x += 16 + container.used_width;
						t.y += 16;
					}
				} else {
					for(auto& t : container.base_layout.contents) {
						t.x += 16;
						t.y += 16;
					}
				}
				ui_state.tooltip->base_data.size.x = int16_t(container.used_width + 32);
				ui_state.tooltip->base_data.size.y = int16_t(container.used_height + 32);
				if(container.used_width > 0) {
					// This block positions the tooltip somewhat under the province centroid
					auto mid_point = world.province_get_mid_point(prov);
					auto map_pos = map_state.normalize_map_coord(mid_point);
					auto screen_size =
						glm::vec2{ float(x_size / user_settings.ui_scale), float(y_size / user_settings.ui_scale) };
					glm::vec2 screen_pos;
					if(!map_state.map_to_screen(*this, map_pos, screen_size, screen_pos)) {
						ui_state.tooltip->set_visible(*this, false);
					} else {
						ui_state.tooltip->base_data.position =
							ui::xy_pair{ int16_t(screen_pos.x - container.used_width / 2 - 8), int16_t(screen_pos.y + 3.5f * map_state.get_zoom()) };
						ui_state.tooltip->set_visible(*this, true);
					}
					// Alternatively: just make it visible
					// ui_state.tooltip->set_visible(*this, true);
				} else {
					ui_state.tooltip->set_visible(*this, false);
				}
			} else {
				ui_state.tooltip->set_visible(*this, false);
			}
		}

		if(current_scene.based_on_map) {
			current_scene.render_map(*this);
		} else {
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		//UI rendering
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUseProgram(open_gl.ui_shader_program);
		glUniform1i(open_gl.ui_shader_texture_sampler_uniform, 0);
		glUniform1i(open_gl.ui_shader_secondary_texture_sampler_uniform, 1);
		glUniform1f(open_gl.ui_shader_screen_width_uniform, float(x_size) / user_settings.ui_scale);
		glUniform1f(open_gl.ui_shader_screen_height_uniform, float(y_size) / user_settings.ui_scale);
		glUniform1f(open_gl.ui_shader_gamma_uniform, user_settings.gamma);
		glViewport(0, 0, x_size, y_size);
		glDepthRange(-1.0f, 1.0f);
		//consistently kept state throughought the entire UI rendering
		glActiveTexture(GL_TEXTURE0);

		ui_state.under_mouse = mouse_probe.under_mouse;
		ui_state.relative_mouse_location = mouse_probe.relative_location;
		current_scene.render_ui(*this);
		root_elm->impl_render(*this, 0, 0);

		if(ui_state.tooltip->is_visible()) {
			//floating by mouse
			if(user_settings.bind_tooltip_mouse) {
				int32_t aim_x = int32_t(mouse_x_position / user_settings.ui_scale) + 10;
				int32_t aim_y = int32_t(mouse_y_position / user_settings.ui_scale) + 10;
				int32_t wsize_x = int32_t(x_size / user_settings.ui_scale);
				int32_t wsize_y = int32_t(y_size / user_settings.ui_scale);
				//this only works if the tooltip isnt bigger than the entire window, wont crash though
				if(aim_x + ui_state.tooltip->base_data.size.x > wsize_x) {
					aim_x = wsize_x - ui_state.tooltip->base_data.size.x;
				}
				if(aim_y + ui_state.tooltip->base_data.size.y > wsize_y) {
					aim_y = wsize_y - ui_state.tooltip->base_data.size.y;
				}
				ui_state.tooltip->impl_render(*this, aim_x, aim_y);
			} else {//tooltip centered over ui element
				ui_state.tooltip->impl_render(*this, ui_state.tooltip->base_data.position.x, ui_state.tooltip->base_data.position.y);
			}
		} else { //if there is no tooltip to display, reset tooltip_timer
			tooltip_timer = std::chrono::steady_clock::now();
		}
		glDisable(GL_BLEND);
	}

	void state::on_create() {
		// Clear "center" property so they don't look messed up!
		reports::write_debug("Creating game state\n");
		{
			static const std::string_view elem_names[] = {
				"state_info",
				"production_goods_name",
				"factory_info",
				"new_factory_option",
				"ledger_legend_entry",
				"project_info"
			};
			for(const auto& elem_name : elem_names) {
				auto it = ui_state.defs_by_name.find(lookup_key(elem_name));
				if(it != ui_state.defs_by_name.end()) {
					auto& gfx_def = ui_defs.gui[it->second.definition];
					gfx_def.flags &= ~ui::element_data::orientation_mask;
				}
			}
			// fix for CWE-fan-fork
			// we have to override the upper-right property to upper left, always
			for(auto& gfx_def : ui_defs.gui) {
				if(to_string_view(gfx_def.name) == "country_modifier_overlappingbox") {
					gfx_def.flags &= ~ui::element_data::orientation_mask;
					break;
				}
			}
		}
		// Allow user to drag some windows, and only the ones that make sense
		{
			static const std::string_view elem_names[] = {
				"pop_details_win",
				"trade_flow",
				"event_election_window",
				"invest_project_window",
				"ledger",
				"province_view",
				"releaseconfirm",
				"build_factory",
				"defaultdiplomacydialog",
				"gpselectdiplomacydialog",
				"makecbdialog",
				"declarewardialog",
				"setuppeacedialog",
				"setupcrisisbackdowndialog",
				"endofnavalcombatpopup",
				"endoflandcombatpopup",
				"ingame_lobby_window",
			};
			for(const auto& elem_name : elem_names) {
				auto it = ui_state.defs_by_name.find(lookup_key(elem_name));
				if(it != ui_state.defs_by_name.end()) {
					auto& gfx_def = ui_defs.gui[it->second.definition];
					if(gfx_def.get_element_type() == ui::element_type::window) {
						gfx_def.data.window.flags |= ui::window_data::is_moveable_mask;
					}
				}
			}
		}
		{ // Nudge, overriden by V2 to be 0 always
			auto it = ui_state.defs_by_name.find(lookup_key("decision_entry"));
			if(it == ui_state.defs_by_name.end()) {
				it = ui_state.defs_by_name.find(lookup_key("decision_window"));
			}
			if(it != ui_state.defs_by_name.end()) {
				ui_defs.gui[it->second.definition].position = ui::xy_pair{ 0, 0 };
			}
		}
		{ // Find the object id for the main_bg displayed (so we display it before the map)
			auto it = ui_state.defs_by_name.find(lookup_key("bg_main_menus"));
			if(it != ui_state.defs_by_name.end()) {
				ui_state.bg_gfx_id = ui_defs.gui[it->second.definition].data.image.gfx_object;
			}
		}

		ui_state.nation_picker = ui::make_element_by_type<ui::nation_picker_container>(*this, "lobby");
		{
			auto window = ui::make_element_by_type<ui::console_window>(*this, "console_wnd");
			if(window.get()) {
				ui_state.console_window_r = window.get();
				window->set_visible(*this, false);
				ui_state.nation_picker->add_child_to_front(std::move(window));
			}
		}
		{ // One on the lobby
			auto new_elm = ui::make_element_by_type<ui::chat_window>(*this, "ingame_lobby_window");
			if(new_elm.get()) {
				ui_state.r_chat_window = new_elm.get();
				new_elm->set_visible(*this, !(network_mode == sys::network_mode_type::single_player)); // Hidden in singleplayer by default
				ui_state.nation_picker->add_child_to_front(std::move(new_elm));
			}
		}
		map_mode::set_map_mode(*this, map_mode::mode::political);
		ui_state.tooltip_font = text::name_into_font_id(*this, "ToolTip_Font");

		reports::write_debug("Finished creating game state\n");
	}
	//
	// string pool functions
	//

	std::string_view state::to_string_view(dcon::text_key tag) const {
		if(tag) {
			if(size_t(tag.index()) >= key_data.size()) {
				// TODO: this is because UI code can reference OOB data due to data races
				return std::string_view();
			}
			auto start_position = key_data.data() + tag.index();
			auto data_size = key_data.size();
			auto end_position = start_position;
			for(; end_position < key_data.data() + data_size; ++end_position) {
				if(*end_position == 0)
					break;
			}
			return std::string_view(key_data.data() + tag.index(), size_t(end_position - start_position));
		}
		return std::string_view();
	}

	std::string_view state::locale_string_view(uint32_t tag) const {
		if(size_t(tag) >= locale_text_data.size()) {
			// TODO: this is because UI code can reference OOB data due to data races
			return std::string_view();
		}
		auto start_position = locale_text_data.data() + tag;
		auto data_size = locale_text_data.size();
		auto end_position = start_position;
		for(; end_position < locale_text_data.data() + data_size; ++end_position) {
			if(*end_position == 0) {
				break;
			}
		}
		return std::string_view(locale_text_data.data() + tag, size_t(end_position - start_position));
	}

	void state::reset_locale_pool() {
		locale_text_data.clear();
		locale_key_to_text_sequence.clear();
		locale_text_data.push_back(0);
	}

	void state::load_locale_strings(std::string_view locale_name) {
		auto root_dir = get_root(common_fs);
		auto assets_dir = open_directory(root_dir, NATIVE("assets"));
		auto localisation_dir = open_directory(assets_dir, NATIVE("localisation"));

		uint32_t column = 0;
		if(locale_name.starts_with("en")) {
			column = 1;
		} else if(locale_name.starts_with("fr")) {
			column = 2;
		} else if(locale_name.starts_with("de")) {
			column = 3;
		} else if(locale_name.starts_with("pl")) {
			column = 4;
		} else if(locale_name.starts_with("es")) {
			column = 5;
		} else if(locale_name.starts_with("it")) {
			column = 6;
		} else if(locale_name.starts_with("sv")) {
			column = 7;
		} else if(locale_name.starts_with("cs")) {
			column = 8;
		} else if(locale_name.starts_with("hu")) {
			column = 9;
		} else if(locale_name.starts_with("nl")) {
			column = 10;
		} else if(locale_name.starts_with("pt")) {
			column = 11;
		} else if(locale_name.starts_with("ru")) {
			column = 12;
		} else if(locale_name.starts_with("fi")) {
			column = 13;
		}
		if(column) { //base game files
			auto text_dir = open_directory(root_dir, NATIVE("localisation"));
			for(auto& file : list_files(text_dir, NATIVE(".csv"))) {
				if(auto ofile = open_file(file); ofile) {
					auto content = view_contents(*ofile);
					text::consume_csv_file(*this, content.data, content.file_size, column, false);
				}
			}
			for(auto& file : list_files(localisation_dir, NATIVE(".csv"))) {
				if(auto ofile = open_file(file); ofile) {
					auto content = view_contents(*ofile);
					text::consume_csv_file(*this, content.data, content.file_size, column, false);
				}
			}
		}
		//new files
		auto locale_dir = open_directory(localisation_dir, text::utf8_to_native(locale_name));
		for(auto& file : list_files(locale_dir, NATIVE(".csv"))) {
			if(auto ofile = open_file(file); ofile) {
				auto content = view_contents(*ofile);
				text::consume_csv_file(*this, content.data, content.file_size, 1, true);
			}
		}
	}

	bool state::key_is_localized(dcon::text_key tag) const {
		if(tag) {
			if(size_t(tag.index()) >= key_data.size()) {
				// TODO: this is because UI code can reference OOB data due to data races
				return false;
			}
			return locale_key_to_text_sequence.find(tag) != locale_key_to_text_sequence.end();
		}
		return false;
	}
	bool state::key_is_localized(std::string_view key) const {
		return locale_key_to_text_sequence.find(key) != locale_key_to_text_sequence.end();
	}
	dcon::text_key state::lookup_key(std::string_view text) const {
		if(auto it = untrans_key_to_text_sequence.find(text); it != untrans_key_to_text_sequence.end()) {
			return *it;
		}
		return dcon::text_key{};
	}

	dcon::text_key state::add_key_win1252(std::string const& text) {
		return add_key_win1252(std::string_view(text));
	}
	dcon::text_key state::add_key_win1252(std::string_view text) {
		return add_key_utf8(text::win1250_to_utf8(text));
	}
	dcon::text_key state::add_key_utf8(std::string const& new_text) {
		return add_key_utf8(std::string_view(new_text.data()));
	}
	dcon::text_key state::add_key_utf8(std::string_view new_text) {
		auto ekey = lookup_key(new_text);
		if(ekey) {
			return ekey;
		}
		auto start = key_data.size();
		auto length = new_text.length();
		if(length > 0) {
			key_data.resize(start + length + 1, char(0));
			std::copy_n(new_text.data(), length, key_data.data() + start);
			key_data.back() = 0;
			auto ret = dcon::text_key(dcon::text_key::value_base_t(start));
			untrans_key_to_text_sequence.insert(ret);
			return ret;
		}
		return dcon::text_key();
	}
	uint32_t state::add_locale_data_win1252(std::string const& text) {
		return add_locale_data_win1252(std::string_view(text));
	}
	uint32_t state::add_locale_data_win1252(std::string_view text) {
		auto start = locale_text_data.size();
		auto tmp = text::win1250_to_utf8(text);
		for(const auto c : tmp) {
			locale_text_data.push_back(c);
		}
		locale_text_data.push_back(0);
		return uint32_t(start);
	}
	uint32_t state::add_locale_data_utf8(std::string const& new_text) {
		return add_locale_data_utf8(std::string_view(new_text));
	}
	uint32_t state::add_locale_data_utf8(std::string_view new_text) {
		auto start = locale_text_data.size();
		auto length = new_text.length();
		if(length > 0) {
			locale_text_data.resize(start + length + 1, char(0));
			std::copy_n(new_text.data(), length, locale_text_data.data() + start);
			locale_text_data.back() = 0;
			return uint32_t(start);
		}
		return 0;
	}

	dcon::unit_name_id state::add_unit_name(std::string_view text) {
		std::string temp = text::win1250_to_utf8(text);
		if(temp.size() > 0) {
			auto start = unit_names.size();
			unit_names.resize(start + temp.length() + 1, char(0));
			std::copy_n(temp.data(), temp.length(), unit_names.data() + start);
			unit_names.back() = 0;
			unit_names_indices.push_back(int32_t(start));
			return dcon::unit_name_id(dcon::unit_name_id::value_base_t(unit_names_indices.size() - 1));
		}
		return dcon::unit_name_id();
	}
	std::string_view state::to_string_view(dcon::unit_name_id tag) const {
		if(tag) {
			if(size_t(tag.index()) >= unit_names_indices.size()) {
				// TODO: this is because UI code can reference OOB data due to data races
				return std::string_view();
			}
			auto start_position = unit_names.data() + unit_names_indices[tag.index()];
			auto data_size = unit_names.size();
			auto end_position = start_position;
			for(; end_position < unit_names.data() + data_size; ++end_position) {
				if(*end_position == 0) {
					break;
				}
			}
			return std::string_view(unit_names.data() + unit_names_indices[tag.index()], size_t(end_position - start_position));
		}
		return std::string_view();
	}

	dcon::trigger_key state::commit_trigger_data(std::vector<uint16_t> data) {
		if(trigger_data_indices.empty()) { // Create placeholder for invalid triggers
			trigger_data_indices.push_back(0);
			trigger_data.push_back(uint16_t(trigger::always | trigger::no_payload | trigger::association_ne));
		}

		if(data.empty()) {
			return dcon::trigger_key();
		}

		auto search_result = std::search(trigger_data.data() + 1, trigger_data.data() + trigger_data.size(), std::boyer_moore_horspool_searcher(data.data(), data.data() + data.size()));
		if(search_result != trigger_data.data() + trigger_data.size()) {
			auto const start = search_result - trigger_data.data();
			auto it = std::find(trigger_data_indices.begin(), trigger_data_indices.end(), int32_t(start));
			if(it != trigger_data_indices.end()) {
				auto d = std::distance(trigger_data_indices.begin(), it);
				return dcon::trigger_key(dcon::trigger_key::value_base_t(d - 1));
			} else {
				trigger_data_indices.push_back(int32_t(start));
				assert(trigger_data_indices.size() <= std::numeric_limits<uint16_t>::max());
				return dcon::trigger_key(dcon::trigger_key::value_base_t(trigger_data_indices.size() - 1 - 1));
			}
		} else {
			auto start = trigger_data.size();
			auto size = data.size();
			trigger_data.resize(start + size, uint16_t(0));
			std::copy_n(data.data(), size, trigger_data.data() + start);
			trigger_data_indices.push_back(int32_t(start));
			assert(trigger_data_indices.size() <= std::numeric_limits<uint16_t>::max());
			return dcon::trigger_key(dcon::trigger_key::value_base_t(trigger_data_indices.size() - 1 - 1));
		}
	}

	dcon::effect_key state::commit_effect_data(std::vector<uint16_t> data) {
		if(effect_data_indices.empty()) { // Create placeholder for invalid effects
			effect_data_indices.push_back(0);
			effect_data.push_back(uint16_t(effect::no_payload));
		}

		if(data.empty()) {
			return dcon::effect_key();
		}

		auto search_result = std::search(effect_data.data() + 1, effect_data.data() + effect_data.size(), std::boyer_moore_horspool_searcher(data.data(), data.data() + data.size()));
		if(search_result != effect_data.data() + effect_data.size()) {
			auto const start = search_result - effect_data.data();
			auto it = std::find(effect_data_indices.begin(), effect_data_indices.end(), int32_t(start));
			if(it != effect_data_indices.end()) {
				auto d = std::distance(effect_data_indices.begin(), it);
				return dcon::effect_key(dcon::effect_key::value_base_t(d - 1));
			} else {
				effect_data_indices.push_back(int32_t(start));
				assert(effect_data_indices.size() <= std::numeric_limits<uint16_t>::max());
				return dcon::effect_key(dcon::effect_key::value_base_t(effect_data_indices.size() - 1 - 1));
			}
		} else {
			auto start = effect_data.size();
			auto size = data.size();
			effect_data.resize(start + size, uint16_t(0));
			std::copy_n(data.data(), size, effect_data.data() + start);
			effect_data_indices.push_back(int32_t(start));
			assert(effect_data_indices.size() <= std::numeric_limits<uint16_t>::max());
			return dcon::effect_key(dcon::effect_key::value_base_t(effect_data_indices.size() - 1 - 1));
		}
	}

	void state::save_user_settings() const {
		auto settings_location = simple_fs::get_or_create_settings_directory();

		char buffer[sizeof(user_settings_s)];
		char* ptr = &buffer[0];

#define US_SAVE(x) \
		std::memcpy(ptr, &user_settings.x, sizeof(user_settings.x)); \
		ptr += sizeof(user_settings.x);

		US_SAVE(ui_scale);
		US_SAVE(master_volume);
		US_SAVE(music_volume);
		US_SAVE(effects_volume);
		US_SAVE(interface_volume);
		US_SAVE(prefer_fullscreen);
		US_SAVE(map_is_globe);
		US_SAVE(autosaves);
		US_SAVE(bind_tooltip_mouse);
		US_SAVE(use_classic_fonts);
		US_SAVE(outliner_views);
		US_SAVE(self_message_settings);
		US_SAVE(interesting_message_settings);
		US_SAVE(other_message_settings);
		US_SAVE(fow_enabled);
		US_SAVE(map_label);
		US_SAVE(antialias_level);
		US_SAVE(gaussianblur_level);
		US_SAVE(gamma);
		US_SAVE(railroads_enabled);
		US_SAVE(rivers_enabled);
		US_SAVE(zoom_mode);
		US_SAVE(vassal_color);
		US_SAVE(left_mouse_click_hold_and_release);
		US_SAVE(render_models);
		US_SAVE(mouse_edge_scrolling);
		US_SAVE(black_map_font);
		US_SAVE(spoilers);
		US_SAVE(zoom_speed);
		US_SAVE(mute_on_focus_lost);
		US_SAVE(diplomatic_message_popup);
		US_SAVE(wasd_for_map_movement);
		US_SAVE(notify_rebels_defeat);
		US_SAVE(color_blind_mode);
		US_SAVE(UNUSED_UINT32_T);
		US_SAVE(locale);
		US_SAVE(map_counter_factor);
		US_SAVE(vassal_names);
#undef US_SAVE
		simple_fs::write_file(settings_location, NATIVE("user_settings.dat"), &buffer[0], uint32_t(ptr - buffer));
	}

	void state::load_user_settings() {
		auto settings_location = simple_fs::get_or_create_settings_directory();
		if(auto settings_file = open_file(settings_location, NATIVE("user_settings.dat")); settings_file) {
			auto content = view_contents(*settings_file);
			auto ptr = content.data;

#define US_LOAD(x) \
			if(ptr > content.data + content.file_size - sizeof(user_settings.x)) break; \
			std::memcpy(&user_settings.x, ptr, sizeof(user_settings.x)); \
			ptr += sizeof(user_settings.x);

			do {
				US_LOAD(ui_scale);
				US_LOAD(master_volume);
				US_LOAD(music_volume);
				US_LOAD(effects_volume);
				US_LOAD(interface_volume);
				US_LOAD(prefer_fullscreen);
				US_LOAD(map_is_globe);
				US_LOAD(autosaves);
				US_LOAD(bind_tooltip_mouse);
				US_LOAD(use_classic_fonts);
				US_LOAD(outliner_views);
				US_LOAD(self_message_settings);
				US_LOAD(interesting_message_settings);
				US_LOAD(other_message_settings);
				US_LOAD(fow_enabled);
				US_LOAD(map_label);
				US_LOAD(antialias_level);
				US_LOAD(gaussianblur_level);
				US_LOAD(gamma);
				US_LOAD(railroads_enabled);
				US_LOAD(rivers_enabled);
				US_LOAD(zoom_mode);
				US_LOAD(vassal_color);
				US_LOAD(left_mouse_click_hold_and_release);
				US_LOAD(render_models);
				US_LOAD(mouse_edge_scrolling);
				US_LOAD(black_map_font);
				US_LOAD(spoilers);
				US_LOAD(zoom_speed);
				US_LOAD(mute_on_focus_lost);
				US_LOAD(diplomatic_message_popup);
				US_LOAD(wasd_for_map_movement);
				US_LOAD(notify_rebels_defeat);
				US_LOAD(color_blind_mode);
				US_LOAD(UNUSED_UINT32_T);
				US_LOAD(locale);
				US_LOAD(map_counter_factor);
				US_LOAD(vassal_names);
#undef US_LOAD
			} while(false);

			//NaN will not get clamped, so use special std::isfinite test to set to reasonable values
			if(!std::isfinite(user_settings.interface_volume)) user_settings.interface_volume = 0.0f;
			user_settings.interface_volume = std::clamp(user_settings.interface_volume, 0.0f, 1.0f);

			if(!std::isfinite(user_settings.music_volume)) user_settings.music_volume = 0.0f;
			user_settings.music_volume = std::clamp(user_settings.music_volume, 0.0f, 1.0f);

			if(!std::isfinite(user_settings.effects_volume)) user_settings.effects_volume = 0.0f;
			user_settings.effects_volume = std::clamp(user_settings.effects_volume, 0.0f, 1.0f);

			if(!std::isfinite(user_settings.master_volume)) user_settings.master_volume = 0.0f;
			user_settings.master_volume = std::clamp(user_settings.master_volume, 0.0f, 1.0f);

			if(user_settings.antialias_level > 16) user_settings.antialias_level = 0;

			if(!std::isfinite(user_settings.gaussianblur_level)) user_settings.gaussianblur_level = 1.0f;
			user_settings.gaussianblur_level = std::clamp(user_settings.gaussianblur_level, 1.0f, 1.5f);

			if(!std::isfinite(user_settings.gamma)) user_settings.gamma = 0.5f;
			user_settings.gamma = std::clamp(user_settings.gamma, 0.5f, 2.5f);

			if(!std::isfinite(user_settings.zoom_speed)) user_settings.zoom_speed = 15.0f;
			user_settings.zoom_speed = std::clamp(user_settings.zoom_speed, 15.f, 25.f);
		}

		// find most recent autosave

		auto saves = simple_fs::get_or_create_save_game_directory();
		uint64_t max_timestamp = 0;
		for(int32_t i = 0; i < sys::max_autosaves; ++i) {
			auto asfile = simple_fs::open_file(saves, native_string(NATIVE("autosave_")) + text::utf8_to_native(std::to_string(i)) + native_string(NATIVE(".bin")));
			if(asfile) {
				auto content = simple_fs::view_contents(*asfile);
				save_header header;
				if(content.file_size > sizeof_save_header(header)) {
					read_save_header((uint8_t const*)(content.data), header);
					if(header.timestamp > max_timestamp) {
						max_timestamp = header.timestamp;
						autosave_counter = (i + 1) % sys::max_autosaves;
					}
				}
			}
		}

		user_settings.locale[15] = 0;
		std::string lname(user_settings.locale);
		bool locale_loaded = false;

		auto rt = get_root(common_fs);
		auto assets = simple_fs::open_directory(rt, NATIVE("assets"));
		auto loc = simple_fs::open_directory(assets, NATIVE("localisation"));
		for(auto& ld : simple_fs::list_subdirectories(loc)) {
			auto def_file = simple_fs::open_file(ld, NATIVE("locale.txt"));
			if(def_file) {
				auto contents = simple_fs::view_contents(*def_file);
				auto ld_name = simple_fs::get_full_name(ld);
				auto dir_lname = ld_name.substr(ld_name.find_last_of(NATIVE_DIR_SEPARATOR) + 1);
				parsers::add_locale(*this, text::native_to_utf8(dir_lname), contents.data, contents.data + contents.file_size);
			}
		}

		for(auto l : world.in_locale) {
			auto ln = l.get_locale_name();
			auto ln_sv = std::string_view{ (char const*)ln.begin(), ln.size() };
			if(ln_sv == lname) {
				font_collection.change_locale(*this, l);
				locale_loaded = true;
				break;
			}
		}

		if(!locale_loaded) {
			for(auto l : world.in_locale) {
				auto ln = l.get_locale_name();
				auto ln_sv = std::string_view{ (char const*)ln.begin(), ln.size() };
				if(ln_sv == "en-US" || ln_sv == "en_US") {
					font_collection.change_locale(*this, l);
					locale_loaded = true;
					break;
				}
			}
		}

		if(!locale_loaded) {
			font_collection.change_locale(*this, dcon::locale_id{ 0 });
		}
	}

	void state::update_ui_scale(float new_scale) {
		user_settings.ui_scale = new_scale;
		ui_state.root->base_data.size.x = int16_t(x_size / user_settings.ui_scale);
		ui_state.root->base_data.size.y = int16_t(y_size / user_settings.ui_scale);
		if(ui_state.outliner_window) {
			ui_state.outliner_window->impl_on_update(*this);
		}
		// TODO move windows
	}

	void list_pop_types(sys::state& state, parsers::scenario_building_context& context) {
		auto root = get_root(state.common_fs);
		auto poptypes = open_directory(root, NATIVE("poptypes"));

		for(auto& file : simple_fs::list_files(poptypes, NATIVE(".txt"))) {
			auto full_name = get_full_name(file);
			auto last = full_name.c_str() + full_name.length();
			auto first = full_name.c_str();
			for(; last > first; --last) {
				if(*last == NATIVE('.'))
				break;
			}
			auto start_of_name = last;
			for(; start_of_name >= first; --start_of_name) {
				if(*start_of_name == NATIVE('\\') || *start_of_name == NATIVE('/')) {
					++start_of_name;
					break;
				}
			}
			auto utf8typename = text::native_to_utf8(native_string_view(start_of_name, last - start_of_name));

			auto name_id = text::find_or_add_key(context.state, utf8typename, true);
			auto type_id = state.world.create_pop_type();
			state.world.pop_type_set_name(type_id, name_id);
			context.map_of_poptypes.insert_or_assign(std::string(utf8typename), type_id);
		}
	}

	void state::open_technology() {
		if(!ui_state.technology_subwindow) {
			auto tab = ui::make_element_by_type<ui::technology_window>(*this, "country_technology");
			ui_state.technology_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.technology_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.technology_subwindow;
			ui_state.technology_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.technology_subwindow);
		}
	}

	void state::open_budget() {
		if(!ui_state.budget_subwindow) {
			auto tab = ui::make_element_by_type<ui::budget_window>(*this, "country_budget");
			ui_state.budget_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.budget_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.budget_subwindow;
			ui_state.budget_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.budget_subwindow);
		}
	}

	void state::open_production() {
		if(!ui_state.production_subwindow) {
			auto tab = ui::make_element_by_type<ui::production_window>(*this, "country_production");
			ui_state.production_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.production_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.production_subwindow;
			ui_state.production_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.production_subwindow);
		}
	}

	void state::open_military() {
		if(!ui_state.military_subwindow) {
			auto tab = ui::make_element_by_type<ui::military_window>(*this, "country_military");
			ui_state.military_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.military_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.military_subwindow;
			ui_state.military_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.military_subwindow);
		}
	}

	void state::open_politics() {
		if(!ui_state.politics_subwindow) {
			auto tab = ui::make_element_by_type<ui::politics_window>(*this, "country_politics");
			ui_state.politics_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.politics_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.politics_subwindow;
			ui_state.politics_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.politics_subwindow);
		}
	}

	void state::open_trade() {
		if(!ui_state.trade_subwindow) {
			auto tab = ui::make_element_by_type<ui::trade_window>(*this, "country_trade");
			ui_state.trade_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.trade_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.trade_subwindow;
			ui_state.trade_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.trade_subwindow);
		}
	}

	void state::open_population() {
		if(!ui_state.population_subwindow) {
			auto tab = ui::make_element_by_type<ui::population_window>(*this, "country_pop");
			ui_state.population_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.population_subwindow) {
			if(ui_state.topbar_subwindow)
			ui_state.topbar_subwindow->set_visible(*this, false);
			ui_state.topbar_subwindow = ui_state.population_subwindow;
			ui_state.population_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.population_subwindow);
		}
	}

	void state::open_diplomacy(dcon::nation_id target) {
		if(!ui_state.diplomacy_subwindow) {
			auto tab = ui::make_element_by_type<ui::diplomacy_window>(*this, "country_diplomacy");
			ui_state.diplomacy_subwindow = tab.get();
			ui_state.root->add_child_to_back(std::move(tab));
		}
		if(ui_state.diplomacy_subwindow) {
			if(ui_state.topbar_subwindow) {
				ui_state.topbar_subwindow->set_visible(*this, false);
			}
			ui_state.topbar_subwindow = ui_state.diplomacy_subwindow;
			ui_state.diplomacy_subwindow->set_visible(*this, true);
			ui_state.root->move_child_to_front(ui_state.diplomacy_subwindow);
			if(target)
			send(*this, ui_state.diplomacy_subwindow, ui::element_selection_wrapper<dcon::nation_id>{ target });
		}
	}

	void state::load_scenario_data(parsers::error_handler& err, sys::year_month_day bookmark_date) {
		auto root = get_root(common_fs);
		auto common = open_directory(root, NATIVE("common"));

		parsers::scenario_building_context context(*this);
		if(cheat_data.extension_use_vanilla_parser) {
			context.use_extensions = false;
		}
		
		// UI doesn't affect checksum, however, when using scripted UI, it will
		ui::load_fixed_gui_definitions(*this, context.gfx_context, err);
		if(cheat_data.extension_use_scripted_ui) {
			ui::load_text_gui_definitions(*this, context.gfx_context, err);
		}

		auto map = open_directory(root, NATIVE("map"));
		// parse default.map
		{
			auto def_map_file = open_file(map, NATIVE("default.map"));
			if(def_map_file) {
				auto content = view_contents(*def_map_file);
				err.file_name = "default.map";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_default_map_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/default.map could not be opened\n";
			}
		}
		// parse definition.csv
		{
			auto def_csv_file = open_file(map, NATIVE("definition.csv"));
			if(def_csv_file) {
				auto content = view_contents(*def_csv_file);
				err.file_name = "definition.csv";
				parsers::read_map_colors(content.data, content.data + content.file_size, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/definition.csv could not be opened\n";
			}
		}

		{
			err.file_name = "adjacencies.csv";
			auto adj_csv_file = open_file(map, NATIVE("adjacencies.csv"));
			if(adj_csv_file) {
				auto adj_content = view_contents(*adj_csv_file);
				parsers::read_map_adjacency(adj_content.data, adj_content.data + adj_content.file_size, err, context);
			}
		}

		/*
		240,208,1 Tsushima --> 240,208,0 Nagasaki
		128,65,97 Fehmarn--> 128,65,96 Kiel
		*/

		if(auto it = context.map_color_to_province_id.find(sys::pack_color(240, 208, 0));
			it != context.map_color_to_province_id.end() &&
			context.map_color_to_province_id.find(sys::pack_color(240, 208, 1)) == context.map_color_to_province_id.end()) {
			context.map_color_to_province_id.insert_or_assign(sys::pack_color(240, 208, 1), it->second);
		}
		if(auto it = context.map_color_to_province_id.find(sys::pack_color(128, 65, 96));
			it != context.map_color_to_province_id.end() &&
			context.map_color_to_province_id.find(sys::pack_color(128, 65, 97)) == context.map_color_to_province_id.end()) {
			context.map_color_to_province_id.insert_or_assign(sys::pack_color(128, 65, 97), it->second);
		}

		/*
		// DO NOT RESTORE
		// 1, 222, 200 --> 51, 221, 251 -- randomly misplaced sea
		// Apparently this color is not just found in the corner of the map, but scattered around it as well
		// thus substituting a valid province color for it causes the sea tile to connect to all sorts of place
		// (a very undesirable behavior
		if(auto it = context.map_color_to_province_id.find(sys::pack_color(51, 221, 251));
			it != context.map_color_to_province_id.end() &&
			context.map_color_to_province_id.find(sys::pack_color(1, 222, 200)) == context.map_color_to_province_id.end()) {
			context.map_color_to_province_id.insert_or_assign(sys::pack_color(1, 222, 200), it->second);
		}
		*/

		// 94, 53, 41 --> 89, 202, 202 -- random dots in the sea tiles
		// 247, 248, 245 -- > 89, 202, 202


		if(auto it = context.map_color_to_province_id.find(sys::pack_color(89, 202, 202));
			it != context.map_color_to_province_id.end() &&
			context.map_color_to_province_id.find(sys::pack_color(94, 53, 41)) == context.map_color_to_province_id.end()) {
			context.map_color_to_province_id.insert_or_assign(sys::pack_color(94, 53, 41), it->second);
		}
		if(auto it = context.map_color_to_province_id.find(sys::pack_color(89, 202, 202));
			it != context.map_color_to_province_id.end() &&
			context.map_color_to_province_id.find(sys::pack_color(247, 248, 245)) == context.map_color_to_province_id.end()) {
			context.map_color_to_province_id.insert_or_assign(sys::pack_color(247, 248, 245), it->second);
		}


	std::thread map_loader([&]() { map_state.load_map_data(context); });

		parsers::make_leader_images(context);

		// Read national tags from countries.txt
		{
			if(auto countries = open_file(common, NATIVE("countries.txt")); countries) {
				auto content = view_contents(*countries);
				err.file_name = "countries.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_national_identity_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/countries.txt could not be opened\n";
			}
			auto countries_dir = open_directory(common, NATIVE("extra_countries"));
			for(auto countries : simple_fs::list_files(countries_dir, NATIVE(".txt"))) {
				auto opened_file = open_file(countries);
				if(opened_file) {
					auto content = view_contents(*opened_file);
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_national_identity_file(gen, err, context);
				}
			}
		}
		// read religions from religion.txt
		{
			auto religion = open_file(common, NATIVE("religion.txt"));
			if(religion) {
				auto content = view_contents(*religion);
				err.file_name = "religion.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_religion_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/religion.txt could not be opened\n";
			}
		}
		// read cultures from cultures.txt
		{
			auto cultures = open_file(common, NATIVE("cultures.txt"));
			if(cultures) {
				auto content = view_contents(*cultures);
				err.file_name = "cultures.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_culture_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/cultures.txt could not be opened\n";
			}
		}
		// read commodities from goods.txt
		{
			// FIRST: make sure that we have a money good
			if(world.commodity_size() == 0) {
				// create money
				auto money_id = world.create_commodity();
				assert(money_id.index() == 0);
			}
			auto goods = open_file(common, NATIVE("goods.txt"));
			if(goods) {
				auto content = view_contents(*goods);
				err.file_name = "goods.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_goods_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/goods.txt could not be opened\n";
			}
		}
		// read buildings.text
		// world.factory_type_resize_construction_costs(world.commodity_size());
		{
			auto buildings = open_file(common, NATIVE("buildings.txt"));
			if(buildings) {
				auto content = view_contents(*buildings);
				err.file_name = "buildings.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_building_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/buildings.txt could not be opened\n";
			}
		}
		// pre parse ideologies.txt
		{
			context.ideologies_file = open_file(common, NATIVE("ideologies.txt"));
			if(context.ideologies_file) {
				auto content = view_contents(*context.ideologies_file);
				err.file_name = "ideologies.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_ideology_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/ideologies.txt could not be opened\n";
			}
		}
		// pre parse issues.txt
		{
			context.issues_file = open_file(common, NATIVE("issues.txt"));
			if(context.issues_file) {
				auto content = view_contents(*context.issues_file);
				err.file_name = "issues.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_issues_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/ideologies.txt could not be opened\n";
			}
		}
		for(auto i : culture_definitions.party_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::party));
		}
		for(auto i : culture_definitions.military_issues) {
			world.reform_set_reform_type(i, uint8_t(culture::issue_type::military));
		}
		for(auto i : culture_definitions.economic_issues) {
			world.reform_set_reform_type(i, uint8_t(culture::issue_type::economic));
		}
		for(auto i : culture_definitions.social_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::social));
		}
		for(auto i : culture_definitions.political_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::political));
		}
		// parse governments.txt
		{
			auto governments = open_file(common, NATIVE("governments.txt"));
			if(governments) {
				auto content = view_contents(*governments);
				err.file_name = "governments.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_governments_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/governments.txt could not be opened\n";
			}
		}
		// pre parse cb_types.txt
		{
			context.cb_types_file = open_file(common, NATIVE("cb_types.txt"));
			if(context.cb_types_file) {
				auto content = view_contents(*context.cb_types_file);
				err.file_name = "cb_types.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_cb_types_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/cb_types.txt could not be opened\n";
			}
		}
		// parse traits.txt
		{
			auto traits = open_file(common, NATIVE("traits.txt"));
			if(traits) {
				auto content = view_contents(*traits);
				err.file_name = "traits.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_traits_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/traits.txt could not be opened\n";
			}
		}
		// pre parse crimes.txt
		{
			context.crimes_file = open_file(common, NATIVE("crime.txt"));
			if(context.crimes_file) {
				auto content = view_contents(*context.crimes_file);
				err.file_name = "crime.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_crimes_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/crime.txt could not be opened\n";
			}
		}
		// pre parse triggered_modifiers.txt
		{
			context.triggered_modifiers_file = open_file(common, NATIVE("triggered_modifiers.txt"));
			if(context.triggered_modifiers_file) {
				auto content = view_contents(*context.triggered_modifiers_file);
				err.file_name = "triggered_modifiers.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_triggered_modifiers_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/triggered_modifiers.txt could not be opened\n";
			}
		}
		// parse nationalvalues.txt
		{
			auto nv_file = open_file(common, NATIVE("nationalvalues.txt"));
			if(nv_file) {
				auto content = view_contents(*nv_file);
				err.file_name = "nationalvalues.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_national_values_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/nationalvalues.txt could not be opened\n";
			}
		}
		// parse static_modifiers.txt
		{
			auto sm_file = open_file(common, NATIVE("static_modifiers.txt"));
			if(sm_file) {
				auto content = view_contents(*sm_file);
				err.file_name = "static_modifiers.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_static_modifiers_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/static_modifiers.txt could not be opened\n";
			}
		}
		// parse event_modifiers.txt
		{
			if(auto em_file = open_file(common, NATIVE("event_modifiers.txt")); em_file) {
				auto content = view_contents(*em_file);
				err.file_name = "event_modifiers.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_event_modifiers_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/event_modifiers.txt could not be opened\n";
			}
			auto event_modifiers = open_directory(common, NATIVE("event_modifiers"));
			for(auto em_file : simple_fs::list_files(event_modifiers, NATIVE(".txt"))) {
				auto opened_file = open_file(em_file);
				if(opened_file) {
					auto content = view_contents(*opened_file);
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_event_modifiers_file(gen, err, context);
				}
			}
		}
		// read *.lua, not being able to read the defines isn't fatal per se
		{
			// Default vanilla dates used if ones are not defined
			start_date = sys::absolute_time_point(sys::year_month_day{ 1836, 1, 1 });
			end_date = sys::absolute_time_point(sys::year_month_day{ 1935, 12, 31 });
			for(auto defines_file : simple_fs::list_files(common, NATIVE(".lua"))) {
				auto opened_file = open_file(defines_file);
				if(opened_file) {
					auto content = view_contents(*opened_file);
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					defines.parse_file(*this, std::string_view(content.data, content.data + content.file_size), err);
				}
			}
			current_date = sys::date(bookmark_date, start_date); //relative to start date
		}
		// gather names of poptypes
		list_pop_types(*this, context);
		// pre parse rebel_types.txt
		{
			context.rebel_types_file = open_file(common, NATIVE("rebel_types.txt"));
			if(context.rebel_types_file) {
				auto content = view_contents(*context.rebel_types_file);
				err.file_name = "rebel_types.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_rebel_types_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/rebel_types.txt could not be opened\n";
			}
		}

		// parse terrain.txt
		{
			auto terrain_file = open_file(map, NATIVE("terrain.txt"));
			if(terrain_file) {
				auto content = view_contents(*terrain_file);
				err.file_name = "terrain.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_terrain_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/terrain.txt could not be opened\n";
			}
		}
		// parse region.txt
		{
			auto region_file = open_file(map, NATIVE("region.txt"));
			if(region_file) {
				auto content = view_contents(*region_file);
				err.file_name = "region.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_region_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/region.txt could not be opened\n";
			}
		}
		// parse region_sea.txt
		{
			auto region_file = open_file(map, NATIVE("region_sea.txt"));
			if(region_file) {
				auto content = view_contents(*region_file);
				err.file_name = "region_sea.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_region_file(gen, err, context);
			} else {
				// OK for this file to be missing
			}
		}
		// parse super_region.txt
		{
			auto super_region_file = open_file(map, NATIVE("super_region.txt"));
			if(super_region_file) {
				auto content = view_contents(*super_region_file);
				err.file_name = "super_region.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_region_file(gen, err, context);
			} else {
				// OK for this file to be missing
			}
		}
		// parse continent.txt
		{
			auto continent_file = open_file(map, NATIVE("continent.txt"));
			if(continent_file) {
				auto content = view_contents(*continent_file);
				err.file_name = "continent.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_continent_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/continent.txt could not be opened\n";
			}
		}
		// parse climate.txt
		{
			auto climate_file = open_file(map, NATIVE("climate.txt"));
			if(climate_file) {
				auto content = view_contents(*climate_file);
				err.file_name = "climate.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_climate_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File map/climate.txt could not be opened\n";
			}
		}
		// parse positions.txt
		{
			auto positions_file = open_file(map, NATIVE("positions.txt"));
			if(positions_file) {
				auto content = view_contents(*positions_file);
				err.file_name = "positions.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_positions_file(gen, err, context);
			} else {
				//err.fatal = true;
				err.accumulated_errors += "File map/positions.txt could not be opened\n";
			}
		}
		// parse technology.txt
		{
			auto tech_file = open_file(common, NATIVE("technology.txt"));
			if(tech_file) {
				auto content = view_contents(*tech_file);
				err.file_name = "technology.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_technology_main_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/technology.txt could not be opened\n";
			}
		}
		// pre parse inventions
		{
			auto inventions = open_directory(root, NATIVE("inventions"));
			for(auto& invf : simple_fs::list_files(inventions, NATIVE(".txt"))) {
				culture::tech_category cat = culture::tech_category::unknown;
				if(simple_fs::get_file_name(invf) == NATIVE("army_inventions.txt")) {
					cat = culture::tech_category::army;
				} else if(simple_fs::get_file_name(invf) == NATIVE("navy_inventions.txt")) {
					cat = culture::tech_category::navy;
				} else if(simple_fs::get_file_name(invf) == NATIVE("commerce_inventions.txt")) {
					cat = culture::tech_category::commerce;
				} else if(simple_fs::get_file_name(invf) == NATIVE("culture_inventions.txt")) {
					cat = culture::tech_category::culture;
				} else if(simple_fs::get_file_name(invf) == NATIVE("industry_inventions.txt")) {
					cat = culture::tech_category::industry;
				}
				//non vanilla tech categories not accounted for

				parsers::tech_group_context invention_context{ context, cat };
				if(auto i_file = open_file(invf); i_file) {
					auto content = view_contents(*i_file);
					err.file_name = text::native_to_utf8(simple_fs::get_file_name(invf));
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_inventions_file(gen, err, invention_context);
					context.tech_and_invention_files.emplace_back(std::move(*i_file));
				}
			}
		}
		// load unit type definitions
		{
			parsers::make_base_units(context);

			auto units = open_directory(root, NATIVE("units"));
			for(auto unit_file : simple_fs::list_files(units, NATIVE(".txt"))) {
				auto opened_file = open_file(unit_file);
				if(opened_file) {
					auto content = view_contents(*opened_file);
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_unit_file(gen, err, context);
				}
			}

			if(!bool(military_definitions.infantry)) {
				err.accumulated_errors += "No infantry (or equivalent unit type) found\n";
			}
			if(!bool(military_definitions.irregular)) {
				err.accumulated_errors += "No irregular (or equivalent unit type) found\n";
			}
			if(!bool(military_definitions.artillery)) {
				err.accumulated_errors += "No artillery (or equivalent unit type) found\n";
			}
		}
		// make space in arrays

		world.national_identity_resize_unit_names_count(uint32_t(military_definitions.unit_base_definitions.size()));
		world.national_identity_resize_unit_names_first(uint32_t(military_definitions.unit_base_definitions.size()));

		world.political_party_resize_party_issues(world.issue_size());

		world.province_resize_party_loyalty(world.ideology_size());
		world.province_resize_building_level(economy::max_building_types);

		world.pop_type_resize_everyday_needs(world.commodity_size());
		world.pop_type_resize_luxury_needs(world.commodity_size());
		world.pop_type_resize_life_needs(world.commodity_size());
		world.pop_type_resize_ideology(world.ideology_size());
		world.pop_type_resize_issues(world.issue_option_size());
		world.pop_type_resize_promotion(world.pop_type_size());

		world.national_focus_resize_production_focus(world.commodity_size());

		world.technology_resize_activate_building(world.factory_type_size());
		world.technology_resize_activate_unit(uint32_t(military_definitions.unit_base_definitions.size()));
		world.technology_resize_increase_building(uint32_t(economy::max_building_types));
		world.invention_resize_increase_building(uint32_t(economy::max_building_types));

		world.invention_resize_activate_building(world.factory_type_size());
		world.invention_resize_activate_unit(uint32_t(military_definitions.unit_base_definitions.size()));
		world.invention_resize_activate_crime(uint32_t(culture_definitions.crimes.size()));

		world.rebel_type_resize_government_change(world.government_type_size());

		world.nation_resize_max_building_level(economy::max_building_types);
		world.nation_resize_active_inventions(world.invention_size());
		world.nation_resize_active_technologies(world.technology_size());
		world.nation_resize_upper_house(world.ideology_size());

		world.national_identity_resize_government_flag_type(world.government_type_size());
		world.national_identity_resize_government_name(world.government_type_size());
		world.national_identity_resize_government_adjective(world.government_type_size());
		world.national_identity_resize_government_ruler_name(world.government_type_size());
		world.national_identity_resize_government_color(world.government_type_size());

		// add special names
		for(auto ident : world.in_national_identity) {
			auto const tag = nations::int_to_tag(ident.get_identifying_int());
			for(auto const& named_gov : context.map_of_governments) {
				auto const name = tag + "_" + named_gov.first;
				auto name_k = add_key_win1252(name);
				ident.set_government_name(named_gov.second, name_k);
				auto const adj = tag + "_" + named_gov.first + "_ADJ";
				auto adj_k = add_key_win1252(adj);
				ident.set_government_adjective(named_gov.second, adj_k);
				auto const ruler = tag + "_" + named_gov.first + "_ruler";
				auto ruler_k = add_key_win1252(ruler);
				ident.set_government_ruler_name(named_gov.second, ruler_k);
			}
		}

		// load scripted triggers
		auto stdir = open_directory(root, NATIVE("scripted triggers"));
		for(auto st_file : simple_fs::list_files(stdir, NATIVE(".txt"))) {
			auto opened_file = open_file(st_file);
			if(opened_file) {
				auto content = view_contents(*opened_file);
				err.file_name = text::native_to_utf8(get_full_name(*opened_file));
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_scripted_trigger_file(gen, err, context);
			}
		}

		// load country files
		world.for_each_national_identity([&](dcon::national_identity_id i) {
			auto country_file = open_file(common, text::win1250_to_native(context.file_names_for_idents[i]));
			if(country_file) {
				parsers::country_file_context c_context{ context, i };
				auto content = view_contents(*country_file);
				err.file_name = context.file_names_for_idents[i];
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_country_file(gen, err, c_context);
			}
		});

		// load province history files
		auto history = open_directory(root, NATIVE("history"));
		{
			auto prov_history = open_directory(history, NATIVE("provinces"));
			for(auto subdir : list_subdirectories(prov_history)) {
				// Modding extension:
				for(auto province_file : list_files(subdir, NATIVE(".csv"))) {
					auto opened_file = open_file(province_file);
					if(opened_file) {
						err.file_name = text::native_to_utf8(get_full_name(*opened_file));
						auto content = view_contents(*opened_file);
						parsers::parse_csv_province_history_file(*this, content.data, content.data + content.file_size, err, context);
					}
				}

				for(auto prov_file : list_files(subdir, NATIVE(".txt"))) {
					auto file_name = text::native_to_utf8(get_file_name(prov_file));
					auto name_start = file_name.c_str();
					auto name_end = name_start + file_name.length();
					// exclude files starting with "~" for example
					if(name_start < name_end && !isdigit(*name_start))
						continue;

					auto value_start = name_start;
					for(; value_start < name_end; ++value_start) {
						if(isdigit(*value_start))
							break;
					}
					auto value_end = value_start;
					for(; value_end < name_end; ++value_end) {
						if(!isdigit(*value_end))
							break;
					}

					err.file_name = text::native_to_utf8(get_full_name(prov_file));
					auto province_id = parsers::parse_int(std::string_view(value_start, value_end), 0, err);
					if(province_id > 0 && uint32_t(province_id) < context.original_id_to_prov_id_map.size()) {
						auto opened_file = open_file(prov_file);
						if(opened_file) {
							auto pid = context.original_id_to_prov_id_map[province_id];
							parsers::province_file_context pf_context{ context, pid };
							auto content = view_contents(*opened_file);
							parsers::token_generator gen(content.data, content.data + content.file_size);
							parsers::parse_province_history_file(gen, err, pf_context);
							//ordered execute -- errors streamed to dummy
							std::stable_sort(pf_context.history_blocks.begin(), pf_context.history_blocks.end(), [](const auto& a, const auto& b) {
								return a.first < b.first;
							});
							for(auto& block : pf_context.history_blocks) {
								parsers::province_file_context tpf_context{ context, pid };
								parsers::parse_province_history_file(block.second, err, tpf_context);
							}
						}
					}
				}
			}
		}
		culture::set_default_issue_and_reform_options(*this);
		// load pop history files
		{
			auto pop_history = open_directory(history, NATIVE("pops"));
			//
			std::vector<native_string> date_directories;
			native_string closest_bd_dir;
			for(const auto& closest_dir : simple_fs::list_subdirectories(pop_history)) {
				auto fname = simple_fs::get_full_name(closest_dir);
				// TODO: very naive way to obtain the directory... smh
				if(fname[fname.size() - 1] == NATIVE('\\')
				|| fname[fname.size() - 1] == NATIVE('/')) {
					fname.pop_back();
				}
				if(auto pos = fname.find_last_of(NATIVE("/\\")); pos != std::string::npos) {
					fname = fname.substr(pos + 1);
				}
				// End of naive thing
				auto ymd = parsers::parse_date(text::native_to_utf8(fname), 0, err);
				if(ymd.year <= bookmark_date.year && ymd.month <= bookmark_date.month && ymd.day <= bookmark_date.day) {
					closest_bd_dir = fname;
				}
			}
			if(closest_bd_dir.empty()) { //for eu4 converters jfc
				closest_bd_dir = NATIVE("1836.1.1");
			}
			//
			auto date_directory = open_directory(pop_history, closest_bd_dir);
			for(auto pop_file : list_files(date_directory, NATIVE(".txt"))) {
				auto opened_file = open_file(pop_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_pop_history_file(gen, err, context);
				}
			}
			// Modding extension:
			// Support loading pops from a CSV file, this to condense them better and allow
			// for them to load faster and better ordered, editable with a spreadsheet program
			for(auto pop_file : list_files(date_directory, NATIVE(".csv"))) {
				auto opened_file = open_file(pop_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::parse_csv_pop_history_file(*this, content.data, content.data + content.file_size, err, context);
				}
			}
		}

		// load poptype definitions
		{
			auto poptypes = open_directory(root, NATIVE("poptypes"));
			for(auto pr : context.map_of_poptypes) {
				auto opened_file = open_file(poptypes, text::utf8_to_native(pr.first + ".txt"));
				if(opened_file) {
					err.file_name = pr.first + ".txt";
					auto content = view_contents(*opened_file);
				parsers::poptype_context inner_context{ context, pr.second };
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_poptype_file(gen, err, inner_context);
				}
			}
		}

		// load ideology contents
		{
			err.file_name = "ideologies.txt";
			for(auto& pr : context.map_of_ideologies) {
			parsers::individual_ideology_context new_context{ context, pr.second.id };
				parsers::parse_individual_ideology(pr.second.generator_state, err, new_context);
			}
		}
		if(!culture_definitions.conservative) {
			if(auto it = context.map_of_ideologies.find("conservative"); it != context.map_of_ideologies.end()) {
				culture_definitions.conservative = it->second.id;
				err.accumulated_warnings += "conservative ideology lacks \"can_reduce_militancy = 1\" key\n";
			}
			if(!culture_definitions.conservative) {
				err.accumulated_errors += "NO CONSERVATIVE IDEOLOGY (fatal error)\n";
				err.fatal = true;
			}
		}
		// triggered modifier contents
		{
			err.file_name = "triggered_modifiers.txt";
			for(auto& r : context.set_of_triggered_modifiers) {
				national_definitions.triggered_modifiers[r.index].trigger_condition =
				parsers::read_triggered_modifier_condition(r.generator_state, err, context);
			}
		}
		// cb contents
		{
			err.file_name = "cb_types.txt";
			for(auto& r : context.map_of_cb_types) {
			parsers::individual_cb_context new_context{ context, r.second.id };
				parsers::parse_cb_body(r.second.generator_state, err, new_context);
			}
		}
		// pending crimes
		{
			err.file_name = "crime.txt";
			for(auto& r : context.map_of_crimes) {
				parsers::read_pending_crime(r.second.id, r.second.generator_state, err, context);
			}
		}
		world.issue_option_resize_support_modifiers(world.issue_option_size());
		// pending issue options
		{
			err.file_name = "issues.txt";
			for(auto& r : context.map_of_ioptions) {
				parsers::read_pending_option(r.second.id, r.second.generator_state, err, context);
			}
		}
		// pending reform options
		{
			err.file_name = "issues.txt";
			for(auto& r : context.map_of_roptions) {
				parsers::read_pending_reform(r.second.id, r.second.generator_state, err, context);
			}
		}
		// parse national_focus.txt
		{
			auto nat_focus = open_file(common, NATIVE("national_focus.txt"));
			if(nat_focus) {
				auto content = view_contents(*nat_focus);
				err.file_name = "national_focus.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_national_focus_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/national_focus.txt could not be opened\n";
			}
		}
		// load pop_types.txt
		{
			auto pop_types_file = open_file(common, NATIVE("pop_types.txt"));
			if(pop_types_file) {
				auto content = view_contents(*pop_types_file);
				err.file_name = "pop_types.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_main_pop_type_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/pop_types.txt could not be opened\n";
			}
		}
		// read pending techs
		{
			err.file_name = "technology file";
			for(auto& r : context.map_of_technologies) {
				parsers::read_pending_technology(r.second.id, r.second.generator_state, err, context);
			}
		}
		// read pending inventions
		{
			err.file_name = "inventions file";
			for(auto& r : context.map_of_inventions) {
				parsers::read_pending_invention(r.second.id, r.second.generator_state, err, context);
			}

			// fix invention tech category
			for(auto inv : world.in_invention) {
				if(inv.get_technology_type() == uint8_t(culture::tech_category::unknown)) {
					auto lim_trigger = inv.get_limit();
					if(lim_trigger) {
						trigger::recurse_over_triggers(trigger_data.data() + trigger_data_indices[lim_trigger.index() + 1],
						[&](uint16_t* tval) {
							if((tval[0] & trigger::code_mask) == trigger::technology) {
								auto findex = this->world.technology_get_folder_index(trigger::payload(tval[1]).tech_id);
								inv.set_technology_type(uint8_t(this->culture_definitions.tech_folders[findex].category));
							}
						});
					}
				}
				if(inv.get_technology_type() == uint8_t(culture::tech_category::unknown)) {
					err.accumulated_warnings += "failed to find a technology category for invention ";
					err.accumulated_warnings += text::produce_simple_string(*this, inv.get_name()) + "\n";
				}
			}
		}
		// parse on_actions.txt
		{
			auto on_action = open_file(common, NATIVE("on_actions.txt"));
			if(on_action) {
				auto content = view_contents(*on_action);
				err.file_name = "on_actions.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_on_action_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/on_actions.txt could not be opened\n";
			}
		}
		// parse production_types.txt
		{
			auto prod_types = open_file(common, NATIVE("production_types.txt"));
			if(prod_types) {
				auto content = view_contents(*prod_types);
				err.file_name = "production_types.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);

			parsers::production_context new_context{ context };
				parsers::parse_production_types_file(gen, err, new_context);

				for(const auto ft : world.in_factory_type) {
					if(!bool(world.factory_type_get_output(ft))) {
						err.accumulated_errors += "No output defined for factory " + std::string(text::produce_simple_string(*this, world.factory_type_get_name(ft))) + " (" + err.file_name + ")\n";
					}
				}
				if(!new_context.found_worker_types) {
					err.fatal = true;
					err.accumulated_errors += "Unable to identify factory worker types from production_types.txt\n";
				}
				if(!culture_definitions.primary_factory_worker) {
					err.fatal = true;
					err.accumulated_errors += "No primary factory worker!\n";
				}
				if(!culture_definitions.secondary_factory_worker) {
					err.accumulated_errors += "No primary factory worker!\n";
				}
			} else {
				err.fatal = true;
				err.accumulated_errors += "File common/production_types.txt could not be opened\n";
			}
		}
		// read pending rebel types
		{
			err.file_name = "rebel_types.txt";
			for(auto& r : context.map_of_rebeltypes) {
				parsers::read_pending_rebel_type(r.second.id, r.second.generator_state, err, context);
			}
		}
		// load decisions
		{
			auto decisions = open_directory(root, NATIVE("decisions"));
			for(auto decision_file : list_files(decisions, NATIVE(".txt"))) {
				auto opened_file = open_file(decision_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_decision_file(gen, err, context);
				}
			}
		}
		// load events
		{
			auto events = open_directory(root, NATIVE("events"));
			std::vector<simple_fs::file> held_open_files;
			for(auto event_file : list_files(events, NATIVE(".txt"))) {
				auto opened_file = open_file(event_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_event_file(gen, err, context);
					held_open_files.emplace_back(std::move(*opened_file));
				}
			}
			err.file_name = "pending events";
			parsers::commit_pending_events(err, context);
		}
		// load news
		{
			auto news_dir = open_directory(root, NATIVE("news"));
			for(auto news_file : list_files(news_dir, NATIVE(".txt"))) {
				auto opened_file = open_file(news_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(simple_fs::get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_news_file(gen, err, parsers::news_context{ context });
				}
			}
		}
		// load tutorial
		{
			auto tutorial_dir = open_directory(root, NATIVE("tutorial"));
			for(auto tutorial_file : list_files(tutorial_dir, NATIVE(".txt"))) {
				auto opened_file = open_file(tutorial_file);
				if(opened_file) {
					err.file_name = text::native_to_utf8(simple_fs::get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_tutorial_file(gen, err, context);
				}
			}
		}
		// load battleplan settings
		{
			auto bp_dir = open_directory(root, NATIVE("battleplans"));
			for(auto file : list_files(bp_dir, NATIVE(".txt"))) {
				if(auto f = open_file(file); f) {
					err.file_name = text::native_to_utf8(simple_fs::get_full_name(*f));
					auto content = view_contents(*f);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_battleplan_settings_file(gen, err, context);
				}
			}
		}

		// parse diplomacy history
		{
			auto diplomacy_dir = open_directory(history, NATIVE("diplomacy"));
			for(auto dip_file : list_files(diplomacy_dir, NATIVE(".txt"))) {
				auto opened_file = open_file(dip_file);
				if(opened_file) {
					auto content = view_contents(*opened_file);
					err.file_name = text::native_to_utf8(simple_fs::get_full_name(*opened_file));
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_diplomacy_file(gen, err, context);
				}
			}
		}

		// !!!! yes, I know
		world.province_resize_flag_variables(uint32_t(province_definitions.num_allocated_provincial_flags));
		world.nation_resize_flag_variables(uint32_t(national_definitions.num_allocated_national_flags));
	national_definitions.global_flag_variables.resize((national_definitions.num_allocated_global_flags + 7) / 8, common_types::bitfield_type{ 0 });
		world.nation_resize_accepted_cultures(world.culture_size());

		std::vector<std::pair<dcon::nation_id, dcon::decision_id>> pending_decisions;
		// load country history
		{
			auto country_dir = open_directory(history, NATIVE("countries"));
			for(auto country_file : list_files(country_dir, NATIVE(".txt"))) {
				auto file_name = get_full_name(country_file);

				auto last = file_name.c_str() + file_name.length();
				auto first = file_name.c_str();
				auto start_of_name = last;
				for(; start_of_name >= first; --start_of_name) {
					if(*start_of_name == NATIVE('\\') || *start_of_name == NATIVE('/')) {
						++start_of_name;
						break;
					}
				}
				if(last - start_of_name >= 6) {
					auto utf8name = text::native_to_utf8(native_string_view(start_of_name, last - start_of_name));

					if(auto it = context.map_of_ident_names.find(nations::tag_to_int(utf8name[0], utf8name[1], utf8name[2]));
						it != context.map_of_ident_names.end()) {
						auto holder = context.state.world.national_identity_get_nation_from_identity_holder(it->second);

						if(!holder) {
							holder = world.create_nation();
							world.nation_set_diplomatic_points(holder, 1.0f);
							world.try_create_identity_holder(holder, it->second);
						}

					parsers::country_history_context new_context{ context, it->second, holder, pending_decisions };

						auto opened_file = open_file(country_file);
						if(opened_file) {
							err.file_name = utf8name;
							auto content = view_contents(*opened_file);
							parsers::token_generator gen(content.data, content.data + content.file_size);
							parsers::parse_country_history_file(gen, err, new_context);
						}

					} else {
						err.accumulated_warnings += "invalid tag " + utf8name.substr(0, 3) + " encountered while scanning country history files\n";
					}
				}
			}
		}
		// load oob
		{
			auto oob_dir = open_directory(history, NATIVE("units"));
			for(auto oob_file_name : context.map_of_oob_files_per_nation) {
				auto fname = text::utf8_to_native(oob_file_name.second);
				assert(!fname.empty());
				if(fname[0] == '/' || fname[0] == '\\')
				fname.erase(0, 1);
				fname = simple_fs::correct_slashes(fname);
				auto oob_file = simple_fs::peek_file(oob_dir, fname);
				if(oob_file) {
					auto nat_id = dcon::national_identity_id(dcon::national_identity_id::value_base_t(oob_file_name.first));
					auto holder = context.state.world.national_identity_get_nation_from_identity_holder(nat_id);
					if(holder) {
					parsers::oob_file_context new_context{ context, holder };
						auto opened_file = simple_fs::open_file(*oob_file);
						if(opened_file) {
							err.file_name = text::native_to_utf8(fname);
							auto content = view_contents(*opened_file);
							parsers::token_generator gen(content.data, content.data + content.file_size);
							parsers::parse_oob_file(gen, err, new_context);
						}
					} else {
						err.accumulated_warnings += "dead tag '" + oob_file_name.second + "' encountered while scanning oob files\n";
					}
				} else {
					err.accumulated_warnings += "dead file '" + oob_file_name.second + "' encountered while scanning oob files\n";
				}
			}
		}

		// load war history
		{
			auto country_dir = open_directory(history, NATIVE("wars"));
			for(auto war_file : list_files(country_dir, NATIVE(".txt"))) {
				auto opened_file = open_file(war_file);
				if(opened_file) {
				parsers::war_history_context new_context{ context };

					err.file_name = text::native_to_utf8(simple_fs::get_full_name(*opened_file));
					auto content = view_contents(*opened_file);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					parsers::parse_war_history_file(gen, err, new_context);
				}
			}
		}

		// misc touch ups
		nations::generate_initial_state_instances(*this);
		world.nation_resize_stockpiles(world.commodity_size());
		world.nation_resize_variables(uint32_t(national_definitions.num_allocated_national_variables));
		world.pop_resize_demographics(pop_demographics::size(*this));
	national_definitions.global_flag_variables.resize((national_definitions.num_allocated_global_flags + 7) / 8, common_types::bitfield_type{ 0 });

		// add dummy nations for unheld tags
		world.for_each_national_identity([&](dcon::national_identity_id id) {
			if(!world.national_identity_get_nation_from_identity_holder(id)) {
				auto new_nation = world.create_nation();
				world.try_create_identity_holder(new_nation, id);
			}
		});

		world.nation_resize_modifier_values(sys::national_mod_offsets::count);
		world.nation_resize_rgo_goods_output(world.commodity_size());
		world.nation_resize_factory_goods_output(world.commodity_size());
		world.nation_resize_factory_goods_throughput(world.commodity_size());
		world.nation_resize_rgo_size(world.commodity_size());
		world.nation_resize_rebel_org_modifier(world.rebel_type_size());
		world.nation_resize_active_unit(uint32_t(military_definitions.unit_base_definitions.size()));
		world.nation_resize_active_crime(uint32_t(culture_definitions.crimes.size()));
		world.nation_resize_active_building(world.factory_type_size());
		world.nation_resize_unit_stats(uint32_t(military_definitions.unit_base_definitions.size()));
		world.nation_resize_max_building_level(economy::max_building_types);
		world.province_resize_modifier_values(provincial_mod_offsets::count);
		world.nation_resize_demographics(demographics::size(*this));
		world.state_instance_resize_demographics(demographics::size(*this));

		world.province_resize_demographics(demographics::size(*this));
		world.province_resize_rgo_profit_per_good(world.commodity_size());
		world.province_resize_rgo_actual_production_per_good(world.commodity_size());
		world.province_resize_rgo_employment_per_good(world.commodity_size());
		world.province_resize_rgo_target_employment_per_good(world.commodity_size());

		world.nation_resize_domestic_market_pool(world.commodity_size());
		world.nation_resize_real_demand(world.commodity_size());
		world.nation_resize_stockpile_targets(world.commodity_size());
		world.nation_resize_drawing_on_stockpiles(world.commodity_size());
		world.nation_resize_life_needs_costs(world.pop_type_size());
		world.nation_resize_everyday_needs_costs(world.pop_type_size());
		world.nation_resize_luxury_needs_costs(world.pop_type_size());
		world.nation_resize_imports(world.commodity_size());
		world.nation_resize_army_demand(world.commodity_size());
		world.nation_resize_navy_demand(world.commodity_size());
		world.nation_resize_construction_demand(world.commodity_size());
		world.nation_resize_private_construction_demand(world.commodity_size());
		world.nation_resize_demand_satisfaction(world.commodity_size());
		world.commodity_resize_price_record(economy::price_history_length);

		nations_by_rank.resize(2000); // TODO: take this value directly from the data container: max number of nations
		nations_by_industrial_score.resize(2000);
		nations_by_military_score.resize(2000);
		nations_by_prestige_score.resize(2000);
		crisis_participants.resize(2000);

		for(auto t : world.in_technology) {
			for(auto n : world.in_nation) {
				if(n.get_active_technologies(t)) {
					culture::apply_technology(*this, n, t);
				}
			}
		}
		for(auto t : world.in_invention) {
			for(auto n : world.in_nation) {
				if(trigger::evaluate(*this, t.get_limit(), trigger::to_generic(n), trigger::to_generic(n), -1)
				&& trigger::evaluate_additive_modifier(*this, t.get_chance(), trigger::to_generic(n), trigger::to_generic(n), -1) > 0.f) {
					n.set_active_inventions(t, true);
				}
				if(n.get_active_inventions(t)) {
					culture::apply_invention(*this, n, t);
				}
			}
		}

		// TODO: default diplo points is 9, why?
		for(auto n : world.in_nation) {
			n.set_diplomatic_points(9.f);
		}

		map_loader.join();

		// touch up adjacencies
		world.for_each_province_adjacency([&](dcon::province_adjacency_id id) {
			auto frel = fatten(world, id);
			auto prov_a = frel.get_connected_provinces(0);
			auto prov_b = frel.get_connected_provinces(1);
			if(prov_a.id.index() < province_definitions.first_sea_province.index() && prov_b.id.index() >= province_definitions.first_sea_province.index()) {
				frel.get_type() |= province::border::coastal_bit;
			} else if(prov_a.id.index() >= province_definitions.first_sea_province.index() && prov_b.id.index() < province_definitions.first_sea_province.index()) {
				frel.get_type() |= province::border::coastal_bit;
			}
			if(prov_a.get_state_from_abstract_state_membership() != prov_b.get_state_from_abstract_state_membership()) {
				frel.get_type() |= province::border::state_bit;
			}
			if(prov_a.get_nation_from_province_ownership() != prov_b.get_nation_from_province_ownership()) {
				frel.get_type() |= province::border::national_bit;
			}
		});

		// fill in the terrain type

		for(int32_t i = 0; i < province_definitions.first_sea_province.index(); ++i) {
		dcon::province_id id{ dcon::province_id::value_base_t(i) };
			if(!world.province_get_terrain(id)) { // don't overwrite if set by the history file
				auto terrain_type = map_state.map_data.median_terrain_type[province::to_map_id(id)];
				if(terrain_type < 64) {
					auto modifier = context.modifier_by_terrain_index[terrain_type];
					world.province_set_terrain(id, modifier);
				}
			}
		}
		for(int32_t i = province_definitions.first_sea_province.index(); i < int32_t(world.province_size()); ++i) {
			dcon::province_id id{ dcon::province_id::value_base_t(i) };
			world.province_set_terrain(id, context.ocean_terrain);
		}

		/*
		Lake removal
		-- this is basically using the connected region algorithm on the water provinces
		*/
		{
		world.for_each_province([&](dcon::province_id id) { world.province_set_connected_region_id(id, 0); });

			std::vector<dcon::province_id> to_fill_list;
			std::vector<int32_t> region_sizes;

			uint16_t current_fill_id = 0;
			province_definitions.connected_region_is_coastal.clear();

			to_fill_list.reserve(world.province_size());

			for(int32_t i = int32_t(world.province_size()); i-- > province_definitions.first_sea_province.index();) {
			dcon::province_id id{ dcon::province_id::value_base_t(i) };

				if(world.province_get_connected_region_id(id) == 0) {
					++current_fill_id;

					region_sizes.push_back(0);
					to_fill_list.push_back(id);

					while(!to_fill_list.empty()) {
						auto current_id = to_fill_list.back();
						to_fill_list.pop_back();
						region_sizes.back() += 1;

						world.province_set_connected_region_id(current_id, current_fill_id);
						for(auto rel : world.province_get_province_adjacency(current_id)) {
							if((rel.get_type() & (province::border::coastal_bit | province::border::impassible_bit)) == 0) { // not leaving sea, not impassible
								if(rel.get_connected_provinces(0).get_connected_region_id() == 0)
								to_fill_list.push_back(rel.get_connected_provinces(0));
								if(rel.get_connected_provinces(1).get_connected_region_id() == 0)
								to_fill_list.push_back(rel.get_connected_provinces(1));
							}
						}
					}

					to_fill_list.clear();
				}
			}

			int32_t max = 0;
			for(int32_t i = 0; i < int32_t(region_sizes.size()); ++i) {
				if(region_sizes[max] < region_sizes[i])
				max = i;
			}

			if(!region_sizes.empty()) {
				for(auto k = uint32_t(context.state.province_definitions.first_sea_province.index()); k < context.state.world.province_size(); ++k) {
				dcon::province_id p{ dcon::province_id::value_base_t(k) };
					if(world.province_get_connected_region_id(p) != int16_t(max + 1)) {
						world.province_set_is_coast(p, false);
					world.province_set_port_to(p, dcon::province_id{});
						for(auto adj : context.state.world.province_get_province_adjacency(p)) {
							auto other = adj.get_connected_provinces(0) != p ? adj.get_connected_provinces(0) : adj.get_connected_provinces(1);
							other.set_is_coast(false);
						other.set_port_to(dcon::province_id{});
							adj.get_type() |= province::border::impassible_bit;
						}
					}
				}
			}
		}

		for(auto ip : context.special_impassible) {
			for(auto adj : world.province_get_province_adjacency(ip)) {
				adj.get_type() |= province::border::impassible_bit;
			}
		}

		// make ports
		province::for_each_land_province(*this, [&](dcon::province_id p) {
			for(auto adj : world.province_get_province_adjacency(p)) {
				auto other = adj.get_connected_provinces(0) != p ? adj.get_connected_provinces(0) : adj.get_connected_provinces(1);
				auto bits = adj.get_type();
				if(other && (bits & province::border::coastal_bit) != 0 && (bits & province::border::impassible_bit) == 0) {
					world.province_set_port_to(p, other.id);
					world.province_set_is_coast(p, true);
					return;
				}
			}
		});

		// fix worker types
		province::for_each_land_province(*this, [&](dcon::province_id p) {
			bool is_mine = world.commodity_get_is_mine(world.province_get_rgo(p));
			// fix pop types
			for(auto pop : world.province_get_pop_location(p)) {
				if(is_mine && pop.get_pop().get_poptype() == culture_definitions.farmers) {
					pop.get_pop().set_poptype(culture_definitions.laborers);
				}
				if(!is_mine && pop.get_pop().get_poptype() == culture_definitions.laborers) {
					pop.get_pop().set_poptype(culture_definitions.farmers);
				}
			}
		});

		bool gov_error = false;
		for(auto n : world.in_nation) {
			auto g = n.get_government_type();
			if(!g && n.get_owned_province_count() != 0) {
				auto name = nations::int_to_tag(n.get_identity_from_identity_holder().get_identifying_int());
				err.accumulated_errors += name + " exists but has no governmentnt (This will result in a crash)\n";
				gov_error = true;
			}
		}
		if(gov_error)
		return;

		//
		// make ui scripts
		//
		for(auto& s : context.gfx_context.nation_buttons_allow) {
			if(s.button_element) {
				err.file_name = s.original_file;
			parsers::trigger_building_context t_context{ context, trigger::slot_contents::nation, trigger::slot_contents::nation, trigger::slot_contents::nation };
				ui_defs.gui[s.button_element].data.button.scriptable_enable = make_trigger(s.generator_state, err, t_context);
				ui_defs.gui[s.button_element].data.button.flags |= uint16_t(ui::button_scripting::nation);
			}
		}
		for(auto& s : context.gfx_context.nation_buttons_effect) {
			if(s.button_element) {
				err.file_name = s.original_file;
			parsers::effect_building_context t_context{ context, trigger::slot_contents::nation, trigger::slot_contents::nation, trigger::slot_contents::nation };
				ui_defs.gui[s.button_element].data.button.scriptable_effect = make_effect(s.generator_state, err, t_context);
				ui_defs.gui[s.button_element].data.button.flags |= uint16_t(ui::button_scripting::nation);
			}
		}
		for(auto& s : context.gfx_context.province_buttons_allow) {
			if(s.button_element) {
				err.file_name = s.original_file;
				auto existing_scripting = ui_defs.gui[s.button_element].data.button.get_button_scripting();
				if(existing_scripting == ui::button_scripting::nation) {
					err.accumulated_errors += std::string("Button ") + std::string(to_string_view(ui_defs.gui[s.button_element].name)) + "in " + err.file_name + " has both province and nation scripting set\n";
				} else {
				parsers::trigger_building_context t_context{ context, trigger::slot_contents::province, trigger::slot_contents::province, trigger::slot_contents::nation };
					ui_defs.gui[s.button_element].data.button.scriptable_enable = make_trigger(s.generator_state, err, t_context);
					ui_defs.gui[s.button_element].data.button.flags |= uint16_t(ui::button_scripting::province);
				}
			}
		}
		for(auto& s : context.gfx_context.province_buttons_effect) {
			if(s.button_element) {
				err.file_name = s.original_file;
				auto existing_scripting = ui_defs.gui[s.button_element].data.button.get_button_scripting();
				if(existing_scripting == ui::button_scripting::nation) {
					err.accumulated_errors += std::string("Button ") + std::string(to_string_view(ui_defs.gui[s.button_element].name)) + "in " + err.file_name + " has both province and nation scripting set\n";
				} else {
					parsers::effect_building_context t_context{ context, trigger::slot_contents::province, trigger::slot_contents::province, trigger::slot_contents::nation };
					ui_defs.gui[s.button_element].data.button.scriptable_effect = make_effect(s.generator_state, err, t_context);
					ui_defs.gui[s.button_element].data.button.flags |= uint16_t(ui::button_scripting::province);
				}
			}
		}

		// Terrain gfx also needs to be loaded separatedly -- but only after terrain has been loaded
		if(cheat_data.extension_use_scripted_ui) {
			ui::load_terrain_gfx(*this, context.gfx_context, err);
		}

		// Sanity checking navies & armies
		for(auto n : world.in_navy) {
			auto p = n.get_navy_location().get_location();
			if(p.id.index() >= province_definitions.first_sea_province.index()) {
				//...
			} else { //land province
				auto pp = world.province_get_port_to(p);
				auto adj = world.get_province_adjacency_by_province_pair(p, pp);
				if(!pp || !adj) {
					err.accumulated_errors += "Navy defined in " + text::produce_simple_string(*this, p.get_name()) + "; but said province isn't connected to a sea province\n";
				}
			}
		}
		for(auto a : world.in_army) {
			auto p = a.get_army_location().get_location();
			if(p.id.index() >= province_definitions.first_sea_province.index()) {
				err.accumulated_errors += "Army defined in " + text::produce_simple_string(*this, p.get_name()) + " which is a sea province\n";
			}
		}

		//sanity flags, but only as a warning
		{
			auto gfx_dir = open_directory(root, NATIVE("gfx"));
			auto flags_dir = open_directory(gfx_dir, NATIVE("flags"));
			for(auto nid : world.in_national_identity) {
				native_string tag_native = text::win1250_to_native(nations::int_to_tag(nid.get_identifying_int()));
				if(auto f = simple_fs::peek_file(flags_dir, tag_native + NATIVE(".tga")); !f) {
					err.accumulated_warnings += "Flag missing " + text::native_to_utf8(tag_native) + ".tga\n";
				}
				std::vector<bool> has_reported(flag_type_names.size() + 1, false);
				for(auto g : world.in_government_type) {
					if(!has_reported[g.get_flag_type().index() + 1]) {
						native_string file_str = tag_native;
						file_str += ogl::flag_type_to_name(*this, g.get_flag_type());
						file_str += NATIVE(".tga");
						if(auto f = simple_fs::peek_file(flags_dir, file_str); !f) {
							err.accumulated_warnings += "Flag missing " + text::native_to_utf8(file_str) + "\n";
						}
						has_reported[g.get_flag_type().index() + 1] = true;
					}
				}
			}
		}

		//Fixup armies defined on a different place
		for(auto p : world.in_pop_location) {
			for(const auto src : p.get_pop().get_regiment_source()) {
				if(src.get_regiment().get_army_from_army_membership().get_controller_from_army_control() == p.get_province().get_nation_from_province_ownership() || src.get_regiment().get_army_from_army_membership().get_controller_from_army_control() == world.national_identity_get_nation_from_identity_holder(national_definitions.rebel_id))
				continue;
				err.accumulated_warnings += "Army defined in " + text::produce_simple_string(*this, p.get_province().get_name()) + "; but regiment comes from a province owned by someone else\n";
				src.get_regiment().set_strength(0.f);
				/*if(!src.get_regiment().get_army_from_army_membership().get_is_retreating()
				&& !src.get_regiment().get_army_from_army_membership().get_navy_from_army_transport()
				&& !src.get_regiment().get_army_from_army_membership().get_battle_from_army_battle_participation()
				&& !src.get_regiment().get_army_from_army_membership().get_controller_from_army_rebel_control()) {
					auto new_u = world.create_army();
					world.army_set_controller_from_army_control(new_u, p.get_province().get_nation_from_province_ownership());
					src.get_regiment().set_army_from_army_membership(new_u);
					military::army_arrives_in_province(*this, new_u, p.get_province(), military::crossing_type::none);
				} else {
					src.get_regiment().set_strength(0.f);
				}*/
			}
		}

		nations::update_revanchism(*this);
		fill_unsaved_data(); // we need this to run triggers

		for(auto n : world.in_nation) {
			auto g = n.get_government_type();
			auto name = nations::int_to_tag(n.get_identity_from_identity_holder().get_identifying_int());
			if(!(n.get_owned_province_count() == 0 || world.government_type_is_valid(g))) {
				err.accumulated_errors += "Government for '" + text::produce_simple_string(*this, text::get_name(*this, n)) + "' (" + name + ") is not valid\n";
			}
		}
		for(auto g : world.in_government_type) {
			for(auto rt : world.in_rebel_type) {
				auto ng = rt.get_government_change(g);
				if(!(!ng || uint32_t(ng.id.index()) < world.government_type_size())) {
					err.accumulated_errors += "Government change for rebel type '" + text::produce_simple_string(*this, rt.get_name()) + "' with government '" + text::produce_simple_string(*this, g.get_name()) + "' is not valid\n";
				}
			}
		}

		for(auto p : world.in_province) {
			if(!p.get_state_membership()
			&& (p.get_nation_from_province_ownership() || p.get_nation_from_province_control())) {
				err.accumulated_errors += "Ownership of a province " + std::to_string(context.prov_id_to_original_id_map[p].id) + " without an assigned state\n";
				/*
				world.delete_province_ownership(p.get_province_ownership());
				if(p.get_province_control()) {
					world.delete_province_control(p.get_province_control());
				}
				*/
			}
		}

		demographics::regenerate_from_pop_data_full(*this);
		economy::initialize(*this);

		culture::create_initial_ideology_and_issues_distribution(*this);
		demographics::regenerate_from_pop_data_full(*this);

		military::reinforce_regiments(*this);
		military::repair_ships(*this);

		nations::update_administrative_efficiency(*this);
		military::regenerate_land_unit_average(*this);
		military::regenerate_ship_scores(*this);
		nations::update_industrial_scores(*this);
		military::update_naval_supply_points(*this);
		economy_rgo::update_rgo_employment(*this);
		economy_factory::update_factory_employment(*this);
		nations::update_military_scores(*this); // depends on ship score, land unit average
		nations::update_rankings(*this);		// depends on industrial score, military scores

		assert(great_nations.size() == 0);
		for(uint32_t i = 0; i < nations_by_rank.size() && i < uint32_t(defines.great_nations_count); ++i) {
			if(nations_by_rank[i]) {
				great_nations.push_back(great_nation{ sys::date{0}, nations_by_rank[i] });
				world.nation_set_is_great_power(nations_by_rank[i], true);
			}
		}

		// fix slaves in non-slave owning nations
		for(auto p : world.in_province) {
			culture::fix_slaves_in_province(*this, p.get_nation_from_province_ownership(), p);
		}

		province::for_each_land_province(*this, [&](dcon::province_id p) {
			if(auto rgo = world.province_get_rgo(p); !rgo) {
				auto name = world.province_get_name(p);
				err.accumulated_errors += std::string("province ") + text::produce_simple_string(*this, name) + " is missing an rgo\n";
				world.province_set_rgo(p, economy::money);
			}
		});

		// parse game_rules.txt
		{
			auto assets_dir = simple_fs::open_directory(root, NATIVE("assets"));
			if(auto f = open_file(assets_dir, NATIVE("game_rules.txt")); f) {
				auto content = view_contents(*f);
				err.file_name = "game_rules.txt";
				parsers::token_generator gen(content.data, content.data + content.file_size);
				parsers::parse_game_rules_file(gen, err, context);
			} else {
				err.fatal = true;
				err.accumulated_errors += "File assets/game_rules.txt could not be opened\n";
			}
		}

		/* run pending triggers and effects */
		for(auto pending_decision : pending_decisions) {
			dcon::nation_id n = pending_decision.first;
			dcon::decision_id d = pending_decision.second;
			if(auto e = world.decision_get_effect(d); e) {
				effect::execute(*this, e, trigger::to_generic(n), trigger::to_generic(n), 0, uint32_t(current_date.value), uint32_t(n.index() << 4 ^ d.index()));
			}
		}

		economy::presimulate(*this);

		ai::identify_focuses(*this);
		// ai::update_ai_research(*this);
		ai::update_influence_priorities(*this);
		ai::update_focuses(*this);

		economy::initialize(*this);
		military::recover_org(*this);
		military::set_initial_leaders(*this);
		military::run_gc(*this);
		for(auto r : world.in_army) {
			auto nation = world.army_control_get_controller(r.get_army_control());
			//armies defined as "rebels" will be assigned to the nearest rebellion
			if(nation == world.national_identity_get_nation_from_identity_holder(national_definitions.rebel_id)) {
				world.delete_army_control(r.get_army_control());
				dcon::rebel_faction_id rf;
				auto owner = r.get_location_from_army_location().get_nation_from_province_ownership();
				auto lrw = owner.get_rebellion_within();
				if(lrw.begin() != lrw.end()) {
					world.force_create_army_rebel_control(r, (*lrw.begin()).get_rebels());
				}
			} else if(world.nation_get_owned_province_count(nation) == 0) {
				military::cleanup_army(*this,r);
			}
		}
		for(auto r : world.in_navy) {
			auto nation = world.navy_control_get_controller(r.get_navy_control());
			if(world.nation_get_owned_province_count(nation) == 0) {			
				military::cleanup_navy(*this, r);
			}
		}
	}

	void state::preload() {
		adjacency_data_out_of_date = true;
		for(auto si : world.in_state_instance) {
			si.set_naval_base_is_taken(false);
			si.set_capital(dcon::province_id{});
		}
		for(auto n : world.in_nation) {
			n.set_combined_issue_rules(0);
			n.set_is_at_war(false);
			n.set_allies_count(0);
			n.set_vassals_count(0);
			n.set_substates_count(0);
			n.set_administrative_efficiency(0.0f);
			n.set_is_target_of_some_cb(false);
			n.set_in_sphere_of(dcon::nation_id{});
			n.set_is_player_controlled(false);
			n.set_is_great_power(false);
			n.set_is_colonial_nation(false);
			n.set_has_flash_point_state(false);
			n.set_ai_is_threatened(false);
			n.set_ai_home_port(dcon::province_id{});
		}
		for(auto p : world.in_pop) {
			p.set_political_reform_desire(0);
			p.set_social_reform_desire(0);
			p.set_is_primary_or_accepted_culture(false);
		}
		for(auto p : world.in_province) {
		p.set_state_membership(dcon::state_instance_id{});
			p.set_is_owner_core(false);
			p.set_is_blockaded(false);
		}
		for(auto m : world.in_movement) {
			m.set_pop_support(0.0f);
			m.set_radicalism(0.0f);
		}
		for(auto s : world.in_ship) {
			s.set_pending_split(false);
		}
		for(auto r : world.in_regiment) {
			r.set_pending_split(false);
		}
	}

	void state::fill_unsaved_data() { // reconstructs derived values that are not directly saved after a save has been loaded
		#ifndef NDEBUG
		trigger_eval_is_ub = true;
		#endif
		great_nations.reserve(int32_t(defines.great_nations_count));

		world.nation_resize_modifier_values(sys::national_mod_offsets::count);
		world.nation_resize_rgo_goods_output(world.commodity_size());
		world.nation_resize_factory_goods_output(world.commodity_size());
		world.nation_resize_factory_goods_throughput(world.commodity_size());
		world.nation_resize_rgo_size(world.commodity_size());
		world.nation_resize_rebel_org_modifier(world.rebel_type_size());
		world.nation_resize_active_unit(uint32_t(military_definitions.unit_base_definitions.size()));
		world.nation_resize_active_crime(uint32_t(culture_definitions.crimes.size()));
		world.nation_resize_active_building(world.factory_type_size());
		world.nation_resize_unit_stats(uint32_t(military_definitions.unit_base_definitions.size()));
		world.nation_resize_max_building_level(economy::max_building_types);

		world.province_resize_modifier_values(provincial_mod_offsets::count);

		world.nation_resize_demographics(demographics::size(*this));
		world.state_instance_resize_demographics(demographics::size(*this));
		world.province_resize_demographics(demographics::size(*this));

		province::restore_distances(*this);

		world.for_each_nation([&](dcon::nation_id id) { politics::update_displayed_identity(*this, id); });

		nations_by_rank.resize(2000); // TODO: take this value directly from the data container: max number of nations
		nations_by_industrial_score.resize(2000);
		nations_by_military_score.resize(2000);
		nations_by_prestige_score.resize(2000);
		crisis_participants.resize(2000);

		world.for_each_issue([&](dcon::issue_id id) {
			for(auto& opt : world.issue_get_options(id)) {
				if(opt) {
					world.issue_option_set_parent_issue(opt, id);
				}
			}
		});
		world.for_each_reform([&](dcon::reform_id id) {
			for(auto& opt : world.reform_get_options(id)) {
				if(opt) {
					world.reform_option_set_parent_reform(opt, id);
				}
			}
		});
		for(auto i : culture_definitions.party_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::party));
		}
		for(auto i : culture_definitions.military_issues) {
			world.reform_set_reform_type(i, uint8_t(culture::issue_type::military));
		}
		for(auto i : culture_definitions.economic_issues) {
			world.reform_set_reform_type(i, uint8_t(culture::issue_type::economic));
		}
		for(auto i : culture_definitions.social_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::social));
		}
		for(auto i : culture_definitions.political_issues) {
			world.issue_set_issue_type(i, uint8_t(culture::issue_type::political));
		}

		military::reset_unit_stats(*this);
		culture::clear_existing_tech_effects(*this);
		culture::repopulate_technology_effects(*this);
		culture::repopulate_invention_effects(*this);
		military::apply_base_unit_stat_modifiers(*this);

		province::update_connected_regions(*this);
		province::restore_unsaved_values(*this);

		culture::update_all_nations_issue_rules(*this);
		culture::restore_unsaved_values(*this);
		nations::restore_state_instances(*this);
		demographics::regenerate_from_pop_data_full(*this);

		sys::repopulate_modifier_effects(*this);
		military::restore_unsaved_values(*this);
		nations::restore_unsaved_values(*this);

		pop_demographics::regenerate_is_primary_or_accepted(*this);
		nations::update_administrative_efficiency(*this);
		rebel::update_movement_values(*this);

		economy::regenerate_unsaved_values(*this);

		military::regenerate_land_unit_average(*this);
		military::regenerate_ship_scores(*this);
		nations::update_industrial_scores(*this);
		nations::update_military_scores(*this);
		nations::update_rankings(*this);
		nations::update_ui_rankings(*this);

		province::update_cached_values(*this);
		diplomatic_cached_values_out_of_date = true;
		nations::update_cached_values(*this);
		#ifndef NDEBUG
		trigger_eval_is_ub = false; //done, triggers can now be evaluated
		#endif
		nations::monthly_flashpoint_update(*this);
		military_definitions.pending_blackflag_update = true;
		military::update_blackflag_status(*this);

		//
		// clear any pending messages from previously loaded saves
		//

		new_n_event.~SPSCQueue();
		new (&new_n_event) rigtorp::SPSCQueue<event::pending_human_n_event>(1024);
		new_f_n_event.~SPSCQueue();
		new (&new_f_n_event) rigtorp::SPSCQueue<event::pending_human_f_n_event>(1024);
		new_p_event.~SPSCQueue();
		new (&new_p_event) rigtorp::SPSCQueue<event::pending_human_p_event>(1024);
		new_f_p_event.~SPSCQueue();
		new (&new_f_p_event) rigtorp::SPSCQueue<event::pending_human_f_p_event>(1024);

		new_requests.~SPSCQueue();
		new (&new_requests) rigtorp::SPSCQueue<diplomatic_message::message>(256);

		if(local_player_nation) {
			world.nation_set_is_player_controlled(local_player_nation, true);
			// reshow pending events, messages, etc
			for(auto const& e : pending_n_event) {
				if(e.n == local_player_nation) {
					auto auto_choice = world.national_event_get_auto_choice(e.e);
					if(auto_choice == 0)
					auto b = new_n_event.try_push(e);
					else
					command::make_event_choice(*this, e, uint8_t(auto_choice - 1));
				}
			}
			for(auto const& e : pending_f_n_event) {
				if(e.n == local_player_nation) {
					auto auto_choice = world.free_national_event_get_auto_choice(e.e);
					if(auto_choice == 0)
					auto b = new_f_n_event.try_push(e);
					else
					command::make_event_choice(*this, e, uint8_t(auto_choice - 1));
				}
			}
			for(auto const& e : pending_p_event) {
				if(world.province_get_nation_from_province_ownership(e.p) == local_player_nation) {
					auto auto_choice = world.provincial_event_get_auto_choice(e.e);
					if(auto_choice == 0)
					auto b = new_p_event.try_push(e);
					else
					command::make_event_choice(*this, e, uint8_t(auto_choice - 1));
				}
			}
			for(auto const& e : pending_f_p_event) {
				if(world.province_get_nation_from_province_ownership(e.p) == local_player_nation) {
					auto auto_choice = world.free_provincial_event_get_auto_choice(e.e);
					if(auto_choice == 0)
					auto b = new_f_p_event.try_push(e);
					else
					command::make_event_choice(*this, e, uint8_t(auto_choice - 1));
				}
			}
			for(auto const& m : pending_messages) {
				if(m.to == local_player_nation && m.type != diplomatic_message::type::none) {
					auto b = new_requests.try_push(m);
				}
			}
		}
		ui_date = current_date;

		ai::identify_focuses(*this);
		ai::update_ai_general_status(*this);
		ai::refresh_home_ports(*this);

		for(auto p : world.in_pop) {
			float total = 0.0f;
			for(auto i : world.in_ideology) {
				auto& val = p.get_demographics(pop_demographics::to_key(*this, i));
				if(0.0 <= val && val <= 1.0f) {
					total += val;
				} else {
					val = 0.0f;
				}
			}
			if(total > 0.0f) {
				for(auto i : world.in_ideology) {
					auto& val = p.get_demographics(pop_demographics::to_key(*this, i));
					val = val / total;
				}
			}
		}
		military::run_gc(*this);
		for(auto a : world.in_army) {
			if(a.get_arrival_time() && a.get_arrival_time() <= current_date) {
				a.set_arrival_time(current_date + 1);
			}
		}
		// fix invalid unit types
		for(auto reg : world.in_regiment) {
			assert(reg.get_army_from_army_membership());
			assert(reg.get_type());		
			if(!reg.get_type()) { //correct invalid units
				reg.set_type(military_definitions.irregular);
			}
		}
		for(auto plc : world.in_province_land_construction) {
			assert(plc.get_type());		
			if(!plc.get_type()) { //correct invalid units
				plc.set_type(military_definitions.irregular);
			}
		}
		//
		for(auto a : world.in_navy) {
			if(a.get_arrival_time() && a.get_arrival_time() <= current_date) {
				a.set_arrival_time(current_date + 1);
			}
		}

		dcon::unit_type_id first_ship_type;
		for(dcon::unit_type_id::value_base_t i = 0; i < military_definitions.unit_base_definitions.size(); i++) {
			auto const utid = dcon::unit_type_id(i);
			auto const& ut = military_definitions.unit_base_definitions[utid];
			if(!ut.is_land && ut.active) {
				first_ship_type = utid;
				break;
			}
		}
		for(auto const shp : world.in_ship) {
			assert(shp.get_navy_from_navy_membership());
			if(!shp.get_type()) {
				shp.set_type(first_ship_type);
			}
			assert(shp.get_type());
		}

		std::vector<dcon::ship_id> sin_battle;
		for(auto b : world.in_naval_battle) {
			for(auto slot : b.get_slots()) {
				if((slot.flags & military::ship_in_battle::mode_mask) != military::ship_in_battle::mode_retreated
				&& (slot.flags & military::ship_in_battle::mode_mask) != military::ship_in_battle::mode_sunk) {

					assert(world.ship_is_valid(slot.ship));
					auto it = std::find(sin_battle.begin(), sin_battle.end(), slot.ship);
					assert(it == sin_battle.end());
					sin_battle.push_back(slot.ship);
				}
			}
		}

		if(local_player_nation) {
			for(uint32_t i = 0; i < 32; i++) {
				player_data_cache.treasury_record[i] = nations::get_treasury(*this, local_player_nation);
				player_data_cache.population_record[i] = world.nation_get_demographics(local_player_nation, demographics::total);
			}
		}

		game_state_updated.store(true, std::memory_order::release);
	}

	void state::single_game_tick() {
		// do update logic
		current_date += 1;
		if(!is_playable_date(current_date, start_date, end_date)) {
			game_scene::switch_scene(*this, game_scene::scene_id::end_screen);
			game_state_updated.store(true, std::memory_order::release);
			return;
		}

		auto ymd_date = current_date.to_ymd(start_date);

		diplomatic_message::update_pending(*this);

		auto month_start = sys::year_month_day{ ymd_date.year, ymd_date.month, uint16_t(1) };
		auto next_month_start = ymd_date.month != 12 ? sys::year_month_day{ ymd_date.year, uint16_t(ymd_date.month + 1), uint16_t(1) } : sys::year_month_day{ ymd_date.year + 1, uint16_t(1), uint16_t(1) };
		auto const days_in_month = uint32_t(sys::days_difference(month_start, next_month_start));

		// pop update:
		static demographics::ideology_buffer idbuf(*this);
		static demographics::issues_buffer isbuf(*this);
		static demographics::promotion_buffer pbuf;
		static demographics::assimilation_buffer abuf;
		static demographics::conversion_buffer rbuf;
		static demographics::migration_buffer mbuf;
		static demographics::migration_buffer cmbuf;
		static demographics::migration_buffer imbuf;

		// calculate complex changes in parallel where we can, but don't actually apply the results
		// instead, the changes are saved to be applied only after all triggers have been evaluated
		concurrency::parallel_for(0, 8, [&](int32_t index) {
			switch(index) {
			case 0:
			{
				auto o = uint32_t(ymd_date.day);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_ideologies(*this, o, days_in_month, idbuf);
				break;
			}
			case 1:
			{
				auto o = uint32_t(ymd_date.day + 1);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_issues(*this, o, days_in_month, isbuf);
				break;
			}
			case 2:
			{
				auto o = uint32_t(ymd_date.day + 6);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_type_changes(*this, o, days_in_month, pbuf);
				break;
			}
			case 3:
			{
				auto o = uint32_t(ymd_date.day + 7);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_assimilation(*this, o, days_in_month, abuf);
				break;
			}
			case 4:
			{
				auto o = uint32_t(ymd_date.day + 8);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_internal_migration(*this, o, days_in_month, mbuf);
				break;
			}
			case 5:
			{
				auto o = uint32_t(ymd_date.day + 9);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_colonial_migration(*this, o, days_in_month, cmbuf);
				break;
			}
			case 6:
			{
				auto o = uint32_t(ymd_date.day + 10);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_immigration(*this, o, days_in_month, imbuf);
				break;
			}
			case 7:
			{
				auto o = uint32_t(ymd_date.day + 11);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_conversion(*this, o, days_in_month, rbuf);
				break;
			}
			}
		});

		// apply in parallel where we can
		concurrency::parallel_for(0, 8, [&](int32_t index) {
			switch(index) {
			case 0:
			{
				auto o = uint32_t(ymd_date.day + 0);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::apply_ideologies(*this, o, days_in_month, idbuf);
				break;
			}
			case 1:
			{
				auto o = uint32_t(ymd_date.day + 1);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::apply_issues(*this, o, days_in_month, isbuf);
				break;
			}
			case 2:
			{
				auto o = uint32_t(ymd_date.day + 2);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_militancy(*this, o, days_in_month);
				break;
			}
			case 3:
			{
				auto o = uint32_t(ymd_date.day + 3);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_consciousness(*this, o, days_in_month);
				break;
			}
			case 4:
			{
				auto o = uint32_t(ymd_date.day + 4);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_literacy(*this, o, days_in_month);
				break;
			}
			case 5:
			{
				auto o = uint32_t(ymd_date.day + 5);
				if(o >= days_in_month)
					o -= days_in_month;
				demographics::update_growth(*this, o, days_in_month);
				break;
			}
			case 6:
				province::ve_for_each_land_province(*this,
				[&](auto ids) { world.province_set_daily_net_migration(ids, ve::fp_vector{}); });
				break;
			case 7:
				province::ve_for_each_land_province(*this,
				[&](auto ids) { world.province_set_daily_net_immigration(ids, ve::fp_vector{}); });
				break;
			}
		});

		// because they may add pops, these changes must be applied sequentially
		{
			auto o = uint32_t(ymd_date.day + 6);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_type_changes(*this, o, days_in_month, pbuf);
		}
		{
			auto o = uint32_t(ymd_date.day + 7);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_assimilation(*this, o, days_in_month, abuf);
		}
		{
			auto o = uint32_t(ymd_date.day + 8);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_internal_migration(*this, o, days_in_month, mbuf);
		}
		{
			auto o = uint32_t(ymd_date.day + 9);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_colonial_migration(*this, o, days_in_month, cmbuf);
		}
		{
			auto o = uint32_t(ymd_date.day + 10);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_immigration(*this, o, days_in_month, imbuf);
		}
		{
			auto o = uint32_t(ymd_date.day + 11);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::apply_conversion(*this, o, days_in_month, rbuf);
		}

		demographics::remove_size_zero_pops(*this);

		// basic repopulation of demographics derived values
		demographics::regenerate_from_pop_data_daily(*this);

		// values updates pass 1 (mostly trivial things, can be done in parallel)
		concurrency::parallel_for(0, 17, [&](int32_t index) {
			switch(index) {
			case 0:
				ai::refresh_home_ports(*this);
				break;
			case 1:
				// Instant research cheat
				for(auto n : this->cheat_data.instant_research_nations) {
					auto tech = this->world.nation_get_current_research(n);
					if(tech.is_valid()) {
						float points = culture::effective_technology_cost(*this, this->current_date.to_ymd(this->start_date).year, n, tech);
						this->world.nation_set_research_points(n, points);
					}
				}
				nations::update_research_points(*this);
				break;
			case 2:
				military::regenerate_land_unit_average(*this);
				break;
			case 3:
				military::regenerate_ship_scores(*this);
				break;
			case 4:
				nations::update_industrial_scores(*this);
				break;
			case 5:
				military::update_naval_supply_points(*this);
				break;
			case 6:
				military::update_all_recruitable_regiments(*this);
				break;
			case 7:
				military::regenerate_total_regiment_counts(*this);
				break;
			case 8:
				economy_rgo::update_rgo_employment(*this);
				break;
			case 9:
				economy_factory::update_factory_employment(*this);
				break;
			case 10:
				nations::update_administrative_efficiency(*this);
				rebel::daily_update_rebel_organization(*this);
				break;
			case 11:
				military::daily_leaders_update(*this);
				break;
			case 12:
				politics::daily_party_loyalty_update(*this);
				break;
			case 13:
				nations::daily_update_flashpoint_tension(*this);
				break;
			case 14:
				military::update_ticking_war_score(*this);
				break;
			case 15:
				military::increase_dig_in(*this);
				break;
			case 16:
				military::update_blockade_status(*this);
				break;
			}
		});

		economy::daily_update(*this);

		military::recover_org(*this);
		military::update_siege_progress(*this);
		military::update_movement(*this);
		military::update_naval_battles(*this);
		military::update_land_battles(*this);

		military::advance_mobilizations(*this);

		province::update_colonization(*this);
		military::update_cbs(*this); // may add/remove cbs to a nation

		event::update_events(*this);

		culture::update_research(*this, uint32_t(ymd_date.year));

		nations::update_military_scores(*this); // depends on ship score, land unit average
		nations::update_rankings(*this);				// depends on industrial score, military scores
		nations::update_great_powers(*this);		// depends on rankings
		nations::update_influence(*this);				// depends on rankings, great powers

		nations::update_crisis(*this);
		politics::update_elections(*this);

		//
		if(current_date.value % 4 == 0) {
			ai::update_ai_colonial_investment(*this);
		}

		ai::make_defense(*this);
		ai::make_attacks(*this);
		ai::update_ships(*this);

		// Once per month updates, spread out over the month
		switch(ymd_date.day) {
		case 1:
			nations::update_monthly_points(*this);
			economy_factory::prune_factories(*this);
			military::reinforce_regiments(*this);
			break;
		case 2:
			province::update_blockaded_cache(*this);
			sys::update_modifier_effects(*this);
			break;
		case 3:
			military::monthly_leaders_update(*this);
			ai::add_gw_goals(*this);
			break;
		case 4:
			ai::take_ai_decisions(*this);
			break;
		case 5:
			rebel::update_movements(*this);
			rebel::update_factions(*this);
			break;
		case 6:
			ai::form_alliances(*this);
			break;
		case 7:
			ai::update_ai_general_status(*this);
			break;
		case 8:
			military::apply_attrition(*this);
			break;
		case 9:
			military::repair_ships(*this);
			break;
		case 10:
			province::update_crimes(*this);
			break;
		case 11:
			province::update_nationalism(*this);
			break;
		case 12:
			ai::update_ai_research(*this);
			rebel::update_armies(*this);
			rebel::rebel_hunting_check(*this);
			break;
		case 13:
			ai::perform_influence_actions(*this);
			break;
		case 14:
			ai::update_focuses(*this);
			if(uint8_t(difficulty) >= uint8_t(sys::difficulty_level::hard)) {
				ai::perform_foreign_investments(*this);
			}
			break;
		case 15:
			culture::discover_inventions(*this);
			break;
		case 16:
			ai::build_ships(*this);
			break;
		case 17:
			ai::update_land_constructions(*this);
			break;
		case 18:
			ai::update_ai_econ_construction(*this);
			break;
		case 19:
			ai::update_budget(*this);
			break;
		case 20:
			nations::monthly_flashpoint_update(*this);
			break;
		case 21:
			ai::update_ai_colony_starting(*this);
			break;
		case 22:
			ai::take_reforms(*this);
			break;
		case 23:
			ai::civilize(*this);
			ai::make_war_decs(*this);
			break;
		case 24:
			rebel::execute_rebel_victories(*this);
			rebel::update_armies(*this);
			rebel::rebel_hunting_check(*this);
			break;
		case 25:
			rebel::execute_province_defections(*this);
			break;
		case 26:
			ai::make_peace_offers(*this);
			break;
		case 27:
			ai::update_crisis_leaders(*this);
			break;
		case 28:
			rebel::rebel_risings_check(*this);
			break;
		case 29:
			ai::update_war_intervention(*this);
			break;
		case 30:
			rebel::update_armies(*this);
			rebel::rebel_hunting_check(*this);
			break;
		case 31:
			ai::update_cb_fabrication(*this);
			ai::update_ai_ruling_party(*this);
			break;
		default:
			break;
		}

		military::apply_regiment_damage(*this);

		if(ymd_date.day == 1) {
			if(ymd_date.month == 1) {
				// yearly update : redo the upper house
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() != 0)
						politics::recalculate_upper_house(*this, n);
				}

				ai::update_influence_priorities(*this);
			}
			if(ymd_date.month == 2) {
				ai::upgrade_colonies(*this);
			}
			if(ymd_date.month == 3 && !national_definitions.on_quarterly_pulse.empty()) {
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() > 0) {
						event::fire_fixed_event(*this, national_definitions.on_quarterly_pulse, trigger::to_generic(n.id), event::slot_type::nation, n.id, -1, event::slot_type::none);
					}
				}
			}
			if(ymd_date.month == 4 && ymd_date.year % 2 == 0) { // the purge
				demographics::remove_small_pops(*this);
			}
			if(ymd_date.month == 5) {
				ai::prune_alliances(*this);
			}
			if(ymd_date.month == 6 && !national_definitions.on_quarterly_pulse.empty()) {
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() > 0) {
						event::fire_fixed_event(*this, national_definitions.on_quarterly_pulse, trigger::to_generic(n.id), event::slot_type::nation, n.id, -1, event::slot_type::none);
					}
				}
			}
			if(ymd_date.month == 7) {
				ai::update_influence_priorities(*this);
			}
			if(ymd_date.month == 9 && !national_definitions.on_quarterly_pulse.empty()) {
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() > 0) {
						event::fire_fixed_event(*this, national_definitions.on_quarterly_pulse, trigger::to_generic(n.id), event::slot_type::nation, n.id, -1, event::slot_type::none);
					}
				}
			}
			if(ymd_date.month == 10 && !national_definitions.on_yearly_pulse.empty()) {
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() > 0) {
						event::fire_fixed_event(*this, national_definitions.on_yearly_pulse, trigger::to_generic(n.id), event::slot_type::nation, n.id, -1, event::slot_type::none);
					}
				}
			}
			if(ymd_date.month == 11) {
				ai::prune_alliances(*this);
			}
			if(ymd_date.month == 12 && !national_definitions.on_quarterly_pulse.empty()) {
				for(auto n : world.in_nation) {
					if(n.get_owned_province_count() > 0) {
						event::fire_fixed_event(*this, national_definitions.on_quarterly_pulse, trigger::to_generic(n.id), event::slot_type::nation, n.id, -1, event::slot_type::none);
					}
				}
			}
		}

		ai::general_ai_unit_tick(*this);

		military::run_gc(*this);
		nations::run_gc(*this);
		military::update_blackflag_status(*this);
		ai::daily_cleanup(*this);

		province::update_connected_regions(*this);
		province::update_cached_values(*this);
		nations::update_cached_values(*this);
		/*
		 * END OF DAY: update cached data
		 */

		player_data_cache.treasury_record[current_date.value % 32] = nations::get_treasury(*this, local_player_nation);
		player_data_cache.population_record[current_date.value % 32] = world.nation_get_demographics(local_player_nation, demographics::total);
		if((current_date.value % 16) == 0) {
			auto index = economy::most_recent_price_record_index(*this);
			for(auto c : world.in_commodity) {
				c.set_price_record(index, c.get_current_price());
			}
		}

		ui_date = current_date;

		game_state_updated.store(true, std::memory_order::release);

		switch(user_settings.autosaves) {
		case autosave_frequency::none:
			break;
		case autosave_frequency::daily:
			write_save_file(*this, sys::save_type::autosave);
			break;
		case autosave_frequency::monthly:
			if(ymd_date.day == 1)
				write_save_file(*this, sys::save_type::autosave);
			break;
		case autosave_frequency::sixmonthly:
			if((ymd_date.month == 7 || ymd_date.month == 1) && ymd_date.day == 1)
				write_save_file(*this, sys::save_type::autosave);
			break;
		case autosave_frequency::yearly:
			if(ymd_date.month == 1 && ymd_date.day == 1)
				write_save_file(*this, sys::save_type::autosave);
			break;
		default:
			break;
		}
	}

	sys::checksum_key state::get_save_checksum() {
		dcon::load_record loaded = world.make_serialize_record_store_save();
		auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size_t(world.serialize_size(loaded))]);
		std::byte* start = reinterpret_cast<std::byte*>(buffer.get());
		world.serialize(start, loaded);

		auto buffer_position = reinterpret_cast<uint8_t*>(start);
		int32_t total_size_used = static_cast<int32_t>(buffer_position - buffer.get());

		checksum_key key;
		blake2b(&key, sizeof(key), buffer.get(), total_size_used, nullptr, 0);
		return key;
	}

	void state::debug_save_oos_dump() {
		auto sdir = simple_fs::get_or_create_oos_directory();
		{
			// save for further inspection
			dcon::load_record loaded = world.make_serialize_record_store_save();
			auto save_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size_t(world.serialize_size(loaded))]);
			auto buffer_position = reinterpret_cast<std::byte*>(save_buffer.get());
			world.serialize(buffer_position, loaded);
			size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - save_buffer.get();
			simple_fs::write_file(sdir, NATIVE("save.bin"), reinterpret_cast<const char*>(save_buffer.get()), uint32_t(total_size_used));
		}
		{
			auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[sys::sizeof_save_section(*this)]);
			auto buffer_position = sys::write_save_section(buffer.get(), *this);
			size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - buffer.get();
			simple_fs::write_file(sdir, NATIVE("all_save.bin"), reinterpret_cast<const char*>(buffer.get()), uint32_t(total_size_used));
		}
	}

	void state::debug_scenario_oos_dump() {
		auto sdir = simple_fs::get_or_create_oos_directory();
		{
			// save for further inspection
			dcon::load_record loaded = world.make_serialize_record_store_scenario();
			auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size_t(world.serialize_size(loaded))]);
			auto buffer_position = reinterpret_cast<std::byte*>(buffer.get());
			world.serialize(buffer_position, loaded);
			size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - buffer.get();
			simple_fs::write_file(sdir, NATIVE("scen.bin"), reinterpret_cast<char*>(buffer.get()), uint32_t(total_size_used));
		}
		{
			auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size_t(sys::sizeof_scenario_section(*this).total_size)]);
			auto buffer_position = sys::write_scenario_section(buffer.get(), *this);
			size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - buffer.get();
			simple_fs::write_file(sdir, NATIVE("all_scen.bin"), reinterpret_cast<char*>(buffer.get()), uint32_t(total_size_used));
		}
	}

	void state::debug_unsaved_oos_dump() {
		auto sdir = simple_fs::get_or_create_oos_directory();
		{
			// save for further inspection
			dcon::load_record loaded = world.make_serialize_record_store_unsaved();
			auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[size_t(world.serialize_size(loaded))]);
			auto buffer_position = reinterpret_cast<std::byte*>(buffer.get());
			world.serialize(buffer_position, loaded);
			size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - buffer.get();
			simple_fs::write_file(sdir, NATIVE("unsaved.bin"), reinterpret_cast<char*>(buffer.get()), uint32_t(total_size_used));
		}
	}

	void state::game_loop() {
		static int32_t game_speed[] = {
			0,		// speed 0
			2000, // speed 1 -- 2 seconds
			750, // speed 2 -- 0.75 seconds
			250, // speed 3 -- 0.25 seconds
			125, // speed 4 -- 0.125 seconds
		};
		game_speed[1] = int32_t(defines.vce_speed_1);
		game_speed[2] = int32_t(defines.vce_speed_2);
		game_speed[3] = int32_t(defines.vce_speed_3);
		game_speed[4] = int32_t(defines.vce_speed_4);

		while(quit_signaled.load(std::memory_order::acquire) == false) {
			/* An issue that arose in multiplayer is that the UI was loading the savefile
			directly, while the game state loop was running, this was fine with the
			assumption that commands weren't executed while the save was being loaded
			HOWEVER in multiplayer this is often the case, so we have to block all
			commands until the savefile is finished loading
			This way, we're able to effectively and safely queue commands until we
			can receive them AFTER loading the savefile. */
			if(network_state.save_slock.load(std::memory_order::acquire) == true) {
				command::load_savefile(*this, load_file_name, load_is_new_game);
				network_state.save_slock.store(false, std::memory_order::release);
			}

			network::send_and_receive_commands(*this);
			command::execute_pending_commands(*this);
			if(network_mode == sys::network_mode_type::client) {
				std::this_thread::sleep_for(std::chrono::milliseconds(15));
			} else {
				auto speed = actual_game_speed.load(std::memory_order::acquire);
				auto upause = ui_pause.load(std::memory_order::acquire);
				if(network_mode == sys::network_mode_type::host) {
					for(auto client : network_state.clients) {
						if(client.is_active()) {
							//more than 1 month before
							upause = std::abs(client.last_game_date.to_raw_value() - current_date.to_raw_value()) >= 3;
						}
					}
				} else { // prevent host from pausing the game with open event windows
					upause = upause || ui::events_pause_test(*this);
				}

				if(speed <= 0 || upause || internally_paused || current_scene.enforced_pause) {
					std::this_thread::sleep_for(std::chrono::milliseconds(15));
				} else {
					auto entry_time = std::chrono::steady_clock::now();
					auto ms_count = std::chrono::duration_cast<std::chrono::milliseconds>(entry_time - last_update).count();
					if(speed >= 5 || ms_count >= game_speed[speed]) { /*enough time has passed*/
						last_update = entry_time;

						if(network_mode == sys::network_mode_type::host) {
							command::advance_tick(*this, local_player_nation);
						} else {
							single_game_tick();
						}
					} else {
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
				}
			}
		}
	}

	void state::console_log(std::string_view message) {
		current_scene.console_log(*this, message);
	}

	bool state::is_selected(dcon::army_id a) {
		return std::find(selected_armies.begin(), selected_armies.end(), a) != selected_armies.end();
	}
	bool state::is_selected(dcon::navy_id a) {
		return std::find(selected_navies.begin(), selected_navies.end(), a) != selected_navies.end();
	}
	void state::select(dcon::army_id a) {
		if(!is_selected(a)) {
			selected_armies.push_back(a);
			game_state_updated.store(true, std::memory_order_release);
			sound::play_effect(*this, sound::get_army_select_sound(*this), user_settings.master_volume * user_settings.effects_volume);
		}
	}
	void state::select(dcon::navy_id a) {
		if(!is_selected(a)) {
			selected_navies.push_back(a);
			game_state_updated.store(true, std::memory_order_release);
			sound::play_effect(*this, sound::get_navy_select_sound(*this), user_settings.master_volume * user_settings.effects_volume);
		}
	}
	void state::deselect(dcon::army_id a) {
		for(size_t i = selected_armies.size(); i-- > 0;) {
			if(selected_armies[i] == a) {
				selected_armies[i] = selected_armies.back();
				selected_armies.pop_back();
				game_state_updated.store(true, std::memory_order_release);
				return;
			}
		}
	}
	void state::deselect(dcon::navy_id a) {
		for(size_t i = selected_navies.size(); i-- > 0;) {
			if(selected_navies[i] == a) {
				selected_navies[i] = selected_navies.back();
				selected_navies.pop_back();
				game_state_updated.store(true, std::memory_order_release);
				return;
			}
		}
	}

} // namespace sys
