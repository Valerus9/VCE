#include "system/system_state.hpp"
#include "commands.hpp"
#include "demographics.hpp"
#include "economy_factory_templates.hpp"
#include "effects.hpp"
#include "serialization.hpp"
#include "nations.hpp"
#include "nations_templates.hpp"
#include "politics.hpp"
#include "province_templates.hpp"
#include "rebels.hpp"
#include "triggers.hpp"
#include "cheats.hpp"
#include "ai.hpp"

#include "gui_event.hpp"
#include "gui_error_window.hpp"

namespace command {

	#define GS_COMMAND_LIST \
	GS_COMMAND_LIST_ENTRY(invalid, no_data) \
	GS_COMMAND_LIST_ENTRY(set_rally_point, rally_point) \
	GS_COMMAND_LIST_ENTRY(save_game, save_game) \
	GS_COMMAND_LIST_ENTRY(change_nat_focus, nat_focus) \
	GS_COMMAND_LIST_ENTRY(start_research, start_research) \
	GS_COMMAND_LIST_ENTRY(make_leader, make_leader) \
	GS_COMMAND_LIST_ENTRY(war_subsidies, diplo_action) \
	GS_COMMAND_LIST_ENTRY(cancel_war_subsidies, diplo_action) \
	GS_COMMAND_LIST_ENTRY(increase_relations, diplo_action) \
	GS_COMMAND_LIST_ENTRY(decrease_relations, diplo_action) \
	GS_COMMAND_LIST_ENTRY(begin_province_building_construction, start_province_building) \
	GS_COMMAND_LIST_ENTRY(cancel_factory_building_construction, start_factory_building) \
	GS_COMMAND_LIST_ENTRY(begin_factory_building_construction, start_factory_building) \
	GS_COMMAND_LIST_ENTRY(begin_naval_unit_construction, naval_unit_construction) \
	GS_COMMAND_LIST_ENTRY(begin_land_unit_construction, land_unit_construction) \
	GS_COMMAND_LIST_ENTRY(cancel_naval_unit_construction, naval_unit_construction) \
	GS_COMMAND_LIST_ENTRY(cancel_land_unit_construction, land_unit_construction) \
	GS_COMMAND_LIST_ENTRY(delete_factory, factory) \
	GS_COMMAND_LIST_ENTRY(change_factory_settings, factory) \
	GS_COMMAND_LIST_ENTRY(make_vassal, tag_target) \
	GS_COMMAND_LIST_ENTRY(release_and_play_nation, tag_target) \
	GS_COMMAND_LIST_ENTRY(change_budget, budget_data) \
	GS_COMMAND_LIST_ENTRY(start_election, no_data) \
	GS_COMMAND_LIST_ENTRY(change_influence_priority, influence_priority) \
	GS_COMMAND_LIST_ENTRY(discredit_advisors, influence_action) \
	GS_COMMAND_LIST_ENTRY(expel_advisors, influence_action) \
	GS_COMMAND_LIST_ENTRY(ban_embassy, influence_action) \
	GS_COMMAND_LIST_ENTRY(increase_opinion, influence_action) \
	GS_COMMAND_LIST_ENTRY(decrease_opinion, influence_action) \
	GS_COMMAND_LIST_ENTRY(add_to_sphere, influence_action) \
	GS_COMMAND_LIST_ENTRY(remove_from_sphere, influence_action) \
	GS_COMMAND_LIST_ENTRY(upgrade_colony_to_state, generic_location) \
	GS_COMMAND_LIST_ENTRY(invest_in_colony, generic_location) \
	GS_COMMAND_LIST_ENTRY(abandon_colony, generic_location) \
	GS_COMMAND_LIST_ENTRY(finish_colonization, generic_location) \
	GS_COMMAND_LIST_ENTRY(intervene_in_war, war_target) \
	GS_COMMAND_LIST_ENTRY(suppress_movement, movement) \
	GS_COMMAND_LIST_ENTRY(civilize_nation, no_data) \
	GS_COMMAND_LIST_ENTRY(appoint_ruling_party, political_party) \
	GS_COMMAND_LIST_ENTRY(change_reform_option, reform_selection) \
	GS_COMMAND_LIST_ENTRY(change_issue_option, issue_selection) \
	GS_COMMAND_LIST_ENTRY(become_interested_in_crisis, no_data) \
	GS_COMMAND_LIST_ENTRY(take_sides_in_crisis, crisis_join) \
	GS_COMMAND_LIST_ENTRY(change_stockpile_settings, stockpile_settings) \
	GS_COMMAND_LIST_ENTRY(take_decision, decision) \
	GS_COMMAND_LIST_ENTRY(make_n_event_choice, pending_human_n_event) \
	GS_COMMAND_LIST_ENTRY(make_f_n_event_choice, pending_human_f_n_event) \
	GS_COMMAND_LIST_ENTRY(make_p_event_choice, pending_human_p_event) \
	GS_COMMAND_LIST_ENTRY(make_f_p_event_choice, pending_human_f_p_event) \
	GS_COMMAND_LIST_ENTRY(fabricate_cb, cb_fabrication) \
	GS_COMMAND_LIST_ENTRY(cancel_cb_fabrication, no_data) \
	GS_COMMAND_LIST_ENTRY(ask_for_military_access, diplo_action) \
	GS_COMMAND_LIST_ENTRY(give_military_access, diplo_action) \
	GS_COMMAND_LIST_ENTRY(ask_for_alliance, diplo_action) \
	GS_COMMAND_LIST_ENTRY(state_transfer, state_transfer) \
	GS_COMMAND_LIST_ENTRY(call_to_arms, call_to_arms) \
	GS_COMMAND_LIST_ENTRY(respond_to_diplomatic_message, message) \
	GS_COMMAND_LIST_ENTRY(cancel_military_access, diplo_action) \
	GS_COMMAND_LIST_ENTRY(cancel_given_military_access, diplo_action) \
	GS_COMMAND_LIST_ENTRY(cancel_alliance, diplo_action) \
	GS_COMMAND_LIST_ENTRY(declare_war, new_war) \
	GS_COMMAND_LIST_ENTRY(add_war_goal, new_war_goal) \
	GS_COMMAND_LIST_ENTRY(start_peace_offer, new_offer) \
	GS_COMMAND_LIST_ENTRY(start_crisis_peace_offer, new_offer) \
	GS_COMMAND_LIST_ENTRY(add_peace_offer_term, offer_wargoal) \
	GS_COMMAND_LIST_ENTRY(add_wargoal_to_crisis_offer, crisis_invitation) \
	GS_COMMAND_LIST_ENTRY(send_peace_offer, no_data) \
	GS_COMMAND_LIST_ENTRY(send_crisis_peace_offer, no_data) \
	GS_COMMAND_LIST_ENTRY(move_army, army_movement) \
	GS_COMMAND_LIST_ENTRY(move_navy, navy_movement) \
	GS_COMMAND_LIST_ENTRY(embark_army, army_movement) \
	GS_COMMAND_LIST_ENTRY(merge_armies, merge_army) \
	GS_COMMAND_LIST_ENTRY(merge_navies, merge_navy) \
	GS_COMMAND_LIST_ENTRY(disband_undermanned, army_movement) \
	GS_COMMAND_LIST_ENTRY(toggle_hunt_rebels, army_movement) \
	GS_COMMAND_LIST_ENTRY(toggle_unit_ai_control, army_movement) \
	GS_COMMAND_LIST_ENTRY(toggle_mobilized_is_ai_controlled, no_data) \
	GS_COMMAND_LIST_ENTRY(release_subject, diplo_action) \
	GS_COMMAND_LIST_ENTRY(even_split_army, army_movement) \
	GS_COMMAND_LIST_ENTRY(even_split_navy, navy_movement) \
	GS_COMMAND_LIST_ENTRY(split_army, army_movement) \
	GS_COMMAND_LIST_ENTRY(split_navy, navy_movement) \
	GS_COMMAND_LIST_ENTRY(delete_army, army_movement) \
	GS_COMMAND_LIST_ENTRY(delete_navy, navy_movement) \
	GS_COMMAND_LIST_ENTRY(change_general, new_general) \
	GS_COMMAND_LIST_ENTRY(change_admiral, new_admiral) \
	GS_COMMAND_LIST_ENTRY(designate_split_regiments, split_regiments) \
	GS_COMMAND_LIST_ENTRY(designate_split_ships, split_ships) \
	GS_COMMAND_LIST_ENTRY(naval_retreat, naval_battle) \
	GS_COMMAND_LIST_ENTRY(land_retreat, land_battle) \
	GS_COMMAND_LIST_ENTRY(invite_to_crisis, crisis_invitation) \
	GS_COMMAND_LIST_ENTRY(toggle_mobilization, no_data) \
	GS_COMMAND_LIST_ENTRY(enable_debt, no_data) \
	GS_COMMAND_LIST_ENTRY(pbutton_script, pbutton) \
	GS_COMMAND_LIST_ENTRY(nbutton_script, nbutton) \
	GS_COMMAND_LIST_ENTRY(chat_message, chat_message) \
	GS_COMMAND_LIST_ENTRY(notify_player_joins, player_name) \
	GS_COMMAND_LIST_ENTRY(notify_player_leaves, notify_leave) \
	GS_COMMAND_LIST_ENTRY(notify_player_ban, nation_pick) \
	GS_COMMAND_LIST_ENTRY(notify_player_kick, nation_pick) \
	GS_COMMAND_LIST_ENTRY(notify_player_picks_nation, nation_pick) \
	GS_COMMAND_LIST_ENTRY(notify_player_oos, no_data) \
	GS_COMMAND_LIST_ENTRY(notify_advanced_tick, no_data) \
	GS_COMMAND_LIST_ENTRY(advance_tick, advance_tick) \
	GS_COMMAND_LIST_ENTRY(notify_save_loaded, notify_save_loaded) \
	GS_COMMAND_LIST_ENTRY(notify_reload, no_data) \
	GS_COMMAND_LIST_ENTRY(notify_start_game, no_data) \
	GS_COMMAND_LIST_ENTRY(notify_stop_game, no_data) \
	GS_COMMAND_LIST_ENTRY(notify_pause_game, no_data) \
	GS_COMMAND_LIST_ENTRY(toggle_auto_create_generals, no_data) \
	GS_COMMAND_LIST_ENTRY(toggle_auto_assign_leaders, no_data) \
	GS_COMMAND_LIST_ENTRY(toggle_auto_assign_single_leader, leader) \

	uint32_t get_size(command_type t) {
		//return sizeof(command::payload);
		uint32_t sz = 0;
		switch(t) {
			#define GS_COMMAND_LIST_ENTRY(type_name, data_type) \
			case command_type::type_name: sz = sizeof(command::payload::dtype::data_type); break;
			GS_COMMAND_LIST
			#undef GS_COMMAND_LIST_ENTRY
			#undef GS_COMMAND_LIST
			default:
			sz = sizeof(command::payload::dtype);
			break;
		}
		return sizeof(command::payload::source)
		+ sizeof(command::payload::padding)
		+ sizeof(command::payload::type)
		+ sz;
	}

	bool is_console_command(command_type t) {
		return uint8_t(t) >= 0x80;
	}

	void add_to_command_queue(sys::state& state, payload& p) {
		//assert(command::can_perform_command(state, p));

		switch(p.type) {
		case command_type::notify_player_joins:
		case command_type::notify_player_leaves:
		case command_type::notify_player_picks_nation:
		case command_type::notify_player_ban:
		case command_type::notify_player_kick:
		case command_type::notify_save_loaded:
		case command_type::notify_reload:
		case command_type::notify_start_game:
		case command_type::notify_stop_game:
		case command_type::notify_player_oos:
		case command_type::notify_pause_game:
		case command_type::chat_message:
			// Notifications can be sent because it's an-always do thing
			break;
		default:
			// Normal commands are discarded iff we are not in the game
			if(!state.current_scene.game_in_progress)
				return;
			state.network_state.is_new_game = false;
			break;
		}

		switch(state.network_mode) {
			case sys::network_mode_type::single_player:
			{
				bool b = state.incoming_commands.try_push(p);
				break;
			}
			case sys::network_mode_type::client:
			case sys::network_mode_type::host:
			{
				state.network_state.outgoing_commands.push(p);
				break;
			}
			default:
			break;
		}
	}

	void set_rally_point(sys::state& state, dcon::nation_id source, dcon::province_id location, bool naval, bool enable) {
		payload p{};
		p.type = command_type::set_rally_point;
		p.source = source;
		p.data.rally_point.location = location;
		p.data.rally_point.naval = naval;
		p.data.rally_point.enable = enable;
		add_to_command_queue(state, p);
	}

	void execute_set_rally_point(sys::state& state, dcon::nation_id source, dcon::province_id location, bool naval, bool enable) {
		if(state.world.province_get_nation_from_province_ownership(location) != source)
		return;
		if(naval) {
			if(state.world.province_get_is_coast(location))
			state.world.province_set_naval_rally_point(location, enable);
		} else {
			state.world.province_set_land_rally_point(location, enable);
		}
	}

	void save_game(sys::state& state, dcon::nation_id source, bool and_quit) {
		payload p{};
		p.type = command_type::save_game;
		p.source = source;
		p.data.save_game.and_quit = and_quit;
		add_to_command_queue(state, p);
	}

	void execute_save_game(sys::state& state, dcon::nation_id source, bool and_quit) {
		sys::write_save_file(state);

		if(and_quit) {
			window::close_window(state);
		}
	}

	void set_national_focus(sys::state& state, dcon::nation_id source, dcon::state_instance_id target_state,
		dcon::national_focus_id focus) {
		payload p{};
		p.type = command_type::change_nat_focus;
		p.source = source;
		p.data.nat_focus.focus = focus;
		p.data.nat_focus.target_state = target_state;
		add_to_command_queue(state, p);
	}

	bool can_set_national_focus(sys::state& state, dcon::nation_id source, dcon::state_instance_id target_state,
		dcon::national_focus_id focus) {
		if(!focus)
		return true;
		if(!nations::can_overwrite_national_focus(state, source, target_state, focus))
		return false;

		auto num_focuses_set = nations::national_focuses_in_use(state, source);
		auto num_focuses_total = nations::max_national_focuses(state, source);

		auto state_owner = state.world.state_instance_get_nation_from_state_ownership(target_state);
		if(state_owner == source) {
			return num_focuses_set < num_focuses_total || bool(state.world.state_instance_get_owner_focus(target_state));
		}
		return num_focuses_set < num_focuses_total || bool(state.world.nation_get_state_from_flashpoint_focus(source));
	}

	void execute_set_national_focus(sys::state& state, dcon::nation_id source, dcon::state_instance_id target_state, dcon::national_focus_id focus) {
		if(state.world.state_instance_get_nation_from_state_ownership(target_state) == source) {
			state.world.state_instance_set_owner_focus(target_state, focus);
		} else {
			if(focus)
			state.world.nation_set_state_from_flashpoint_focus(source, target_state);
			else
			state.world.nation_set_state_from_flashpoint_focus(source, dcon::state_instance_id{});
		}
	}

	void start_research(sys::state& state, dcon::nation_id source, dcon::technology_id tech) {
		payload p{};
		p.type = command_type::start_research;
		p.source = source;
		p.data.start_research.tech = tech;
		add_to_command_queue(state, p);
	}

	bool can_start_research(sys::state& state, dcon::nation_id source, dcon::technology_id tech) {
		/* Nations can only start researching technologies if, they are not uncivilized, the tech
			activation date is past by, and all the previous techs (if any) of the same folder index
			are already researched fully. And they are not already researched. */
		if(!tech)
			return false;
		if(state.world.nation_get_active_technologies(source, tech))
			return false; // Already researched
		if(nations::current_research(state, source) == tech)
			return false; // Already being researched
		if(!state.world.nation_get_is_civilized(source))
			return false; // Must be civilized
		if(state.current_date.to_ymd(state.start_date).year >= state.world.technology_get_year(tech)) {
			// Find previous technology before this one
			dcon::technology_id prev_tech = dcon::technology_id(dcon::technology_id::value_base_t(tech.index() - 1));
			// Previous technology is from the same folder so we have to check that we have researched it beforehand
			if(tech.index() != 0 && state.world.technology_get_folder_index(prev_tech) == state.world.technology_get_folder_index(tech)) {
				// Only allow if all previously researched techs are researched
				return state.world.nation_get_active_technologies(source, prev_tech);
			}
			return true; // First technology on folder can always be researched
		}
		return false;
	}

	void execute_start_research(sys::state& state, dcon::nation_id source, dcon::technology_id tech) {
		if(state.world.nation_get_current_research(source))
		state.world.nation_set_research_points(source, 0.0f);
		state.world.nation_set_current_research(source, tech);
	}

	void make_leader(sys::state& state, dcon::nation_id source, bool general) {
		payload p{};
		p.type = command_type::make_leader;
		p.source = source;
		p.data.make_leader.is_general = general;
		add_to_command_queue(state, p);
	}
	bool can_make_leader(sys::state& state, dcon::nation_id source, bool general) {
		return state.world.nation_get_leadership_points(source) >= state.defines.leader_recruit_cost;
	}
	void execute_make_leader(sys::state& state, dcon::nation_id source, bool general) {
		military::make_new_leader(state, source, general);
	}


	void give_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::war_subsidies;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_give_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		/* Can only perform if, the nations are not at war, the nation isn't already being given war subsidies, and there is
			* defines:WARSUBSIDY_DIPLOMATIC_COST diplomatic points available. And the target isn't equal to the sender. */
		if(source == target)
		return false; // Can't negotiate with self
		if(military::are_at_war(state, source, target))
		return false; // Can't be at war
		if(!state.world.nation_get_is_at_war(target))
		return false; // target must be at war
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(rel && state.world.unilateral_relationship_get_war_subsidies(rel))
		return false; // Can't already be giving war subsidies

		if(state.world.nation_get_is_player_controlled(source))
		return state.world.nation_get_diplomatic_points(source) >= state.defines.warsubsidy_diplomatic_cost; // Enough diplomatic points
		return true;
	}
	void execute_give_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		nations::adjust_relationship(state, source, target, state.defines.warsubsidy_relation_on_accept);
		state.world.nation_get_diplomatic_points(source) -= state.defines.warsubsidy_diplomatic_cost;
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(!rel)
		rel = state.world.force_create_unilateral_relationship(target, source);

		state.world.unilateral_relationship_set_war_subsidies(rel, true);

		notification::post(state, notification::message{
			[source, target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_wsub_start_1", text::variable_type::x, source, text::variable_type::y, target);
			},
			"msg_wsub_start_title",
		source, target, dcon::nation_id{},
			sys::message_base_type::war_subsidies_start
		});
	}


	void cancel_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::cancel_war_subsidies;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_cancel_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		/* Can only perform if, the nations are not at war, the nation is already being given war subsidies, and there is
			* defines:CANCELWARSUBSIDY_DIPLOMATIC_COST diplomatic points available. And the target isn't equal to the sender. */
		if(source == target)
		return false; // Can't negotiate with self
		if(military::are_at_war(state, source, target))
		return false; // Can't be at war
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(rel && !state.world.unilateral_relationship_get_war_subsidies(rel))
		return false; // Must already be giving war subsidies
		if(state.world.nation_get_is_player_controlled(source))
		return state.world.nation_get_diplomatic_points(source) >= state.defines.cancelwarsubsidy_diplomatic_cost; // Enough diplomatic points
		return true;
	}
	void execute_cancel_war_subsidies(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		nations::adjust_relationship(state, source, target, state.defines.cancelwarsubsidy_relation_on_accept);
		state.world.nation_get_diplomatic_points(source) -= state.defines.cancelwarsubsidy_diplomatic_cost;
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(rel) {
			state.world.unilateral_relationship_set_war_subsidies(rel, false);
		}
		if(source != state.local_player_nation) {
			notification::post(state, notification::message{
				[source, target](sys::state& state, text::layout_base& contents) {
					text::add_line(state, contents, "msg_wsub_end_1", text::variable_type::x, source, text::variable_type::y, target);
				},
				"msg_wsub_end_title",
				source, target, dcon::nation_id{},
				sys::message_base_type::war_subsidies_end
			});
		}
	}

	void increase_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::increase_relations;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_increase_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		/* Can only perform if, the nations are not at war, the relation value isn't maxed out at 200, and has
			* defines:INCREASERELATION_DIPLOMATIC_COST diplomatic points. And the target can't be the same as the sender. */

		if(source == target)
		return false; // Can't negotiate with self

		if(military::are_at_war(state, source, target))
		return false; // Can't be at war

		auto rel = state.world.get_diplomatic_relation_by_diplomatic_pair(source, target);
		if(state.world.diplomatic_relation_get_value(rel) >= 200.f)
		return false; // Maxed out

		if(state.world.nation_get_is_player_controlled(source))
		return state.world.nation_get_diplomatic_points(source) >= state.defines.increaserelation_diplomatic_cost; // Enough diplomatic points
		return true;
	}
	void execute_increase_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		nations::adjust_relationship(state, source, target, state.defines.increaserelation_relation_on_accept);
		state.world.nation_get_diplomatic_points(source) -= state.defines.increaserelation_diplomatic_cost;

		notification::post(state, notification::message{
			[source, target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_inc_rel_1", text::variable_type::x, source, text::variable_type::y, target);
			},
			"msg_inc_rel_title",
			source, target, dcon::nation_id{},
			sys::message_base_type::increase_relation
		});
	}

	void decrease_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::decrease_relations;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_decrease_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		/* Can only perform if, the nations are not at war, the relation value isn't maxxed out at -200, and has
			* defines:DECREASERELATION_DIPLOMATIC_COST diplomatic points. And not done to self. */
		if(source == target)
		return false; // Can't negotiate with self
		if(military::are_at_war(state, source, target))
		return false; // Can't be at war
		auto rel = state.world.get_diplomatic_relation_by_diplomatic_pair(source, target);
		if(rel && state.world.diplomatic_relation_get_value(rel) <= -200.f)
		return false; // Maxxed out
		if(state.world.nation_get_is_player_controlled(source))
		return state.world.nation_get_diplomatic_points(source) >= state.defines.decreaserelation_diplomatic_cost; // Enough diplomatic points
		return true;
	}
	void execute_decrease_relations(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		nations::adjust_relationship(state, source, target, state.defines.decreaserelation_relation_on_accept);
		state.world.nation_get_diplomatic_points(source) -= state.defines.decreaserelation_diplomatic_cost;

		notification::post(state, notification::message{
			[source, target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_dec_rel_1", text::variable_type::x, source, text::variable_type::y, target);
			},
			"msg_dec_rel_title",
		source, target, dcon::nation_id{},
			sys::message_base_type::decrease_relation
		});
	}

	void begin_province_building_construction(sys::state& state, dcon::nation_id source, dcon::province_id prov, dcon::province_building_type_id type) {
		payload p{};
		p.type = command_type::begin_province_building_construction;
		p.source = source;
		p.data.start_province_building.location = prov;
		p.data.start_province_building.type = type;
		add_to_command_queue(state, p);
	}
	bool can_begin_province_building_construction(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::province_building_type_id type) {
		if(type == state.economy_definitions.railroad_building) {
			return province::can_build_railroads(state, p, source);
		} else if(type == state.economy_definitions.fort_building) {
			return province::can_build_fort(state, p, source);
		} else if(type == state.economy_definitions.naval_base_building) {
			return province::can_build_naval_base(state, p, source);
		}
		return province::can_build_province_building(state, p, source, type);
	}
	void execute_begin_province_building_construction(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::province_building_type_id type) {
		if(type == state.economy_definitions.naval_base_building) {
			auto si = state.world.province_get_state_membership(p);
			if(si) {
				si.set_naval_base_is_taken(true);
			}
		}

		// foreign investment
		if(source != state.world.province_get_nation_from_province_ownership(p)) {
			if(type != state.economy_definitions.fort_building && type != state.economy_definitions.naval_base_building) {
				auto amount = 0.0f;
				auto const& base_cost = state.world.province_building_type_get_cost(type);
				for(uint32_t j = 0; j < economy::commodity_set::set_size; ++j) {
					if(base_cost.commodity_type[j]) {
						amount += base_cost.commodity_amounts[j] * state.world.commodity_get_cost(base_cost.commodity_type[j]); //base cost
					} else {
						break;
					}
				}
				nations::adjust_foreign_investment(state, source, state.world.province_get_nation_from_province_ownership(p), amount);
			}
		}

		auto new_rr = fatten(state.world, state.world.force_create_province_building_construction(p, source));
		new_rr.set_remaining_construction_time(state.world.province_building_type_get_time(type));
		new_rr.set_is_pop_project(false);
		new_rr.set_type(type);
	}


	void cancel_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type) {
		payload p{};
		p.type = command_type::cancel_factory_building_construction;
		p.source = source;
		p.data.start_factory_building.location = location;
		p.data.start_factory_building.type = type;
		add_to_command_queue(state, p);
	}
	bool can_cancel_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type) {
		auto rules = state.world.nation_get_combined_issue_rules(source);
		for(auto c : state.world.state_instance_get_state_building_construction(location)) {
			if(c.get_type() == type) {
				if(c.get_nation() != source)
				return false;
				if(!c.get_is_upgrade())
				return (rules & issue_rule::destroy_factory) != 0;
				return true;
			}
		}
		return false;
	}
	void execute_cancel_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type) {
		for(auto c : state.world.state_instance_get_state_building_construction(location)) {
			if(c.get_type() == type) {
				// TODO: do some shit when it's a pop project!
				if(c.get_nation() != source)
				return;
				state.world.delete_state_building_construction(c);
				return;
			}
		}
	}
	void begin_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type, bool is_upgrade) {
		payload p{};
		p.type = command_type::begin_factory_building_construction;
		p.source = source;
		p.data.start_factory_building.location = location;
		p.data.start_factory_building.type = type;
		p.data.start_factory_building.is_upgrade = is_upgrade;
		add_to_command_queue(state, p);
	}

	bool can_begin_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type, bool is_upgrade) {

		auto owner = state.world.state_instance_get_nation_from_state_ownership(location);

		/*
		The factory building must be unlocked by the nation.
		Factories cannot be built in a colonial state.
		*/
		if(state.world.nation_get_active_building(source, type) == false && !state.world.factory_type_get_is_available_from_start(type))
			return false;

		if(state.world.province_get_is_colonial(state.world.state_instance_get_capital(location)))
			return false;

		/* There can't be duplicate factories... */
		if(!is_upgrade) {
			if(economy_factory::state_contains_factory(state, location, type)) {
				return false;
			}
		}

		if(state.world.nation_get_is_civilized(source) == false) {
			return false;
		}

		if(owner != source) {
			/*
			For foreign investment: the target nation must allow foreign investment, the nation doing the investing must be a great
			power while the target is not a great power, and the nation doing the investing must not be at war with the target nation.
			The nation being invested in must be civilized.
			*/
			if(state.world.nation_get_is_great_power(source) == false || state.world.nation_get_is_great_power(owner) == true)
				return false;
			if(state.world.nation_get_is_civilized(owner) == false)
				return false;

			auto rules = state.world.nation_get_combined_issue_rules(owner);
			if((rules & issue_rule::allow_foreign_investment) == 0)
				return false;

			if(military::are_at_war(state, source, owner))
				return false;
		} else {
			/*
			The nation must have the rule set to allow building / upgrading if this is a domestic target.
			*/
			auto rules = state.world.nation_get_combined_issue_rules(owner);
			if(is_upgrade) {
				if((rules & issue_rule::expand_factory) == 0)
					return false;
			} else {
				if((rules & issue_rule::build_factory) == 0)
					return false;
			}
		}

		if(is_upgrade) {
			// no double upgrade
			for(auto p : state.world.state_instance_get_state_building_construction(location)) {
				if(p.get_type() == type) {
					return false;
				}
			}
			// must already exist as a factory
			// For upgrades: no upgrading past max level.
			auto d = state.world.state_instance_get_definition(location);
			for(auto p : state.world.state_definition_get_abstract_state_membership(d)) {
				if(p.get_province().get_nation_from_province_ownership() == owner) {
					for(auto const f : p.get_province().get_factory_location()) {
						if(f.get_factory().get_building_type() == type
						&& f.get_factory().get_level() <= f.get_factory().get_building_type().get_max_level()) {
							return true;
						}
					}
				}
			}
			return false;
		} else {
			// coastal factories must be built on coast
			if(state.world.factory_type_get_is_coastal(type)) {
				if(!province::state_is_coastal(state, location)) {
					return false;
				}
			}
			int32_t num_factories = economy_factory::state_factory_count(state, location);
			return num_factories < int32_t(state.defines.factories_per_state);
		}
	}

	void execute_begin_factory_building_construction(sys::state& state, dcon::nation_id source, dcon::state_instance_id location, dcon::factory_type_id type, bool is_upgrade) {
		auto new_up = fatten(state.world, state.world.force_create_state_building_construction(location, source));
		new_up.set_remaining_construction_time(state.world.factory_type_get_construction_time(type));
		new_up.set_is_pop_project(false);
		new_up.set_is_upgrade(is_upgrade);
		new_up.set_type(type);

		if(source != state.world.state_instance_get_nation_from_state_ownership(location)) {
			float amount = 0.0f;
			auto& base_cost = state.world.factory_type_get_construction_costs(type);
			for(uint32_t j = 0; j < economy::commodity_set::set_size; ++j) {
				if(base_cost.commodity_type[j]) {
					amount += base_cost.commodity_amounts[j] * state.world.commodity_get_cost(base_cost.commodity_type[j]); //base cost
				} else {
					break;
				}
			}
			nations::adjust_foreign_investment(state, source, state.world.state_instance_get_nation_from_state_ownership(location), amount);
		}
	}

	void start_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type, dcon::province_id template_province) {
		payload p{};
		p.type = command_type::begin_naval_unit_construction;
		p.source = source;
		p.data.naval_unit_construction.location = location;
		p.data.naval_unit_construction.type = type;
		p.data.naval_unit_construction.template_province = template_province;
		add_to_command_queue(state, p);
	}

	bool can_start_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type, dcon::province_id template_province) {
		/*
		The province must be owned and controlled by the building nation, without an ongoing siege.
		The unit type must be available from start / unlocked by the nation
		*/

		if(state.world.province_get_nation_from_province_ownership(location) != source)
		return false;
		if(state.world.province_get_nation_from_province_control(location) != source)
		return false;
		if(state.world.nation_get_active_unit(source, type) == false &&
			state.military_definitions.unit_base_definitions[type].active == false)
		return false;
		auto disarm = state.world.nation_get_disarmed_until(source);
		if(disarm && state.current_date < disarm)
		return false;

		if(state.military_definitions.unit_base_definitions[type].is_land) {
			return false;
		} else {
			/*
			The province must be coastal
			The province must have a naval base of sufficient level, depending on the unit type
			The province may not be overseas for some unit types
			Some units have a maximum number per port where they can built that must be respected
			*/
			if(!state.world.province_get_is_coast(location))
			return false;

			auto overseas_allowed = state.military_definitions.unit_base_definitions[type].can_build_overseas;
			auto level_req = state.military_definitions.unit_base_definitions[type].min_port_level;

			if(state.world.province_get_building_level(location, state.economy_definitions.naval_base_building) < level_req)
			return false;

			if(!overseas_allowed && province::is_overseas(state, location))
			return false;

			return true;
		}
	}

	void execute_start_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type, dcon::province_id template_province) {
		auto c = fatten(state.world, state.world.try_create_province_naval_construction(location, source));
		c.set_remaining_construction_time(state.military_definitions.unit_base_definitions[type].build_time);
		c.set_type(type);
		c.set_template_province(template_province);
	}

	void start_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type, dcon::province_id template_province) {
		payload p{};
		p.type = command_type::begin_land_unit_construction;
		p.source = source;
		p.data.land_unit_construction.location = location;
		p.data.land_unit_construction.type = type;
		p.data.land_unit_construction.pop_culture = soldier_culture;
		p.data.land_unit_construction.template_province = template_province;
		add_to_command_queue(state, p);
	}
	bool can_start_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type, dcon::province_id template_province) {
		/*
		The province must be owned and controlled by the building nation, without an ongoing siege.
		The unit type must be available from start / unlocked by the nation
		*/

		if(state.world.province_get_nation_from_province_ownership(location) != source)
		return false;
		if(state.world.province_get_nation_from_province_control(location) != source)
		return false;
		if(state.world.nation_get_active_unit(source, type) == false && state.military_definitions.unit_base_definitions[type].active == false)
		return false;
		if(state.military_definitions.unit_base_definitions[type].primary_culture && soldier_culture != state.world.nation_get_primary_culture(source) && state.world.nation_get_accepted_cultures(source, soldier_culture) == false) {
			return false;
		}
		auto disarm = state.world.nation_get_disarmed_until(source);
		if(disarm && state.current_date < disarm)
		return false;

		if(state.military_definitions.unit_base_definitions[type].is_land) {
			/*
			Each soldier pop can only support so many regiments (including under construction and rebel regiments)
			If the unit is culturally restricted, there must be an available primary culture/accepted culture soldier pop with space
			*/
			auto soldier = military::find_available_soldier(state, location, soldier_culture);
			return bool(soldier);
		} else {
			return false;
		}
	}
	void execute_start_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type, dcon::province_id template_province) {
		auto soldier = military::find_available_soldier(state, location, soldier_culture);

		auto c = fatten(state.world, state.world.try_create_province_land_construction(soldier, source));
		c.set_remaining_construction_time(state.military_definitions.unit_base_definitions[type].build_time);
		c.set_type(type);
		c.set_template_province(template_province);
	}

	void cancel_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type) {
		payload p{};
		p.type = command_type::cancel_naval_unit_construction;
		p.source = source;
		p.data.naval_unit_construction.location = location;
		p.data.naval_unit_construction.type = type;
		add_to_command_queue(state, p);
	}

	bool can_cancel_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type) {
		return state.world.province_get_nation_from_province_ownership(location) == source;
	}

	void execute_cancel_naval_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::unit_type_id type) {
		dcon::province_naval_construction_id c;
		for(auto lc : state.world.province_get_province_naval_construction(location)) {
			if(lc.get_type() == type) {
				c = lc.id;
			}
		}
		state.world.delete_province_naval_construction(c);
	}

	void cancel_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type) {
		payload p{};
		p.type = command_type::cancel_land_unit_construction;
		p.source = source;
		p.data.land_unit_construction.location = location;
		p.data.land_unit_construction.type = type;
		p.data.land_unit_construction.pop_culture = soldier_culture;
		add_to_command_queue(state, p);
	}
	bool can_cancel_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type) {
		return state.world.province_get_nation_from_province_ownership(location) == source;
	}
	void execute_cancel_land_unit_construction(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::culture_id soldier_culture, dcon::unit_type_id type) {
		dcon::province_land_construction_id c;
		for(auto pop : state.world.province_get_pop_location(location)) {
			for(auto lc : pop.get_pop().get_province_land_construction()) {
				if(lc.get_type() == type) {
					c = lc.id;
				}
			}
		}
		state.world.delete_province_land_construction(c);
	}

	void delete_factory(sys::state& state, dcon::nation_id source, dcon::factory_id f) {
		payload p{};
		p.type = command_type::delete_factory;
		p.source = source;
		p.data.factory.location = state.world.factory_get_province_from_factory_location(f);
		p.data.factory.type = state.world.factory_get_building_type(f);
		add_to_command_queue(state, p);
	}
	bool can_delete_factory(sys::state& state, dcon::nation_id source, dcon::factory_id f) {
		auto loc = state.world.factory_get_province_from_factory_location(f);
		if(state.world.province_get_nation_from_province_ownership(loc) != source)
			return false;
		auto rules = state.world.nation_get_combined_issue_rules(source);
		if((rules & issue_rule::destroy_factory) == 0)
			return false;
		return true;
	}
	void execute_delete_factory(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::factory_type_id type) {
		for(auto sc : state.world.state_instance_get_state_building_construction(state.world.province_get_state_membership(location))) {
			if(sc.get_type() == type) {
				state.world.delete_state_building_construction(sc);
				break;
			}
		}
		for(auto f : state.world.province_get_factory_location(location)) {
			if(f.get_factory().get_building_type() == type) {
				state.world.delete_factory(f.get_factory());
				return;
			}
		}
	}

	void change_factory_settings(sys::state& state, dcon::nation_id source, dcon::factory_id f, uint8_t priority, bool subsidized) {
		payload p{};
		p.type = command_type::change_factory_settings;
		p.source = source;
		p.data.factory.location = state.world.factory_get_province_from_factory_location(f);
		p.data.factory.type = state.world.factory_get_building_type(f);
		p.data.factory.priority = priority;
		p.data.factory.subsidize = subsidized;
		add_to_command_queue(state, p);
	}
	bool can_change_factory_settings(sys::state& state, dcon::nation_id source, dcon::factory_id f, uint8_t priority, bool subsidized) {
		auto loc = state.world.factory_get_province_from_factory_location(f);
		if(state.world.province_get_nation_from_province_ownership(loc) != source)
		return false;

		auto rules = state.world.nation_get_combined_issue_rules(source);

		auto current_priority = economy_factory::factory_priority(state, f);
		if(priority >= 4)
		return false;

		if(current_priority != priority) {
			if((rules & issue_rule::factory_priority) == 0)
			return false;
		}

		if(subsidized && (rules & issue_rule::can_subsidise) == 0) {
			return false;
		}

		return true;
	}
	void execute_change_factory_settings(sys::state& state, dcon::nation_id source, dcon::province_id location, dcon::factory_type_id type, uint8_t priority, bool subsidized) {

		if(state.world.province_get_nation_from_province_ownership(location) != source)
		return;

		auto rules = state.world.nation_get_combined_issue_rules(source);

		if(subsidized && (rules & issue_rule::can_subsidise) == 0) {
			return;
		}

		for(auto f : state.world.province_get_factory_location(location)) {
			if(f.get_factory().get_building_type() == type) {
				auto current_priority = economy_factory::factory_priority(state, f.get_factory());
				if(current_priority != priority) {
					if((rules & issue_rule::factory_priority) == 0)
					return;
					economy_factory::set_factory_priority(state, f.get_factory(), priority);
				}
				if(subsidized && !f.get_factory().get_subsidized()) {
					auto& scale = f.get_factory().get_production_scale();
					scale = std::max(scale, 0.5f);
				}
				f.get_factory().set_subsidized(subsidized);
				return;
			}
		}
	}

	void make_vassal(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		payload p{};
		p.type = command_type::make_vassal;
		p.source = source;
		p.data.tag_target.ident = t;
		add_to_command_queue(state, p);
	}
	bool can_make_vassal(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		return nations::can_release_as_vassal(state, source, t);
	}
	void execute_make_vassal(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		nations::liberate_nation_from(state, t, source);
		auto holder = state.world.national_identity_get_nation_from_identity_holder(t);
		state.world.force_create_overlord(holder, source);
		if(state.world.nation_get_is_great_power(source)) {
			auto sr = state.world.force_create_gp_relationship(holder, source);
			auto& flags = state.world.gp_relationship_get_status(sr);
			flags = uint8_t((flags & ~nations::influence::level_mask) | nations::influence::level_in_sphere);
			state.world.nation_set_in_sphere_of(holder, source);
		}
		nations::remove_cores_from_owned(state, holder, state.world.nation_get_identity_from_identity_holder(source));
		auto& inf = state.world.nation_get_infamy(source);
		inf = std::max(0.0f, inf + state.defines.release_nation_infamy);
		nations::adjust_prestige(state, source, state.defines.release_nation_prestige);
	}

	void release_and_play_as(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		payload p{};
		p.type = command_type::release_and_play_nation;
		p.source = source;
		p.data.tag_target.ident = t;
		add_to_command_queue(state, p);
	}
	bool can_release_and_play_as(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		return nations::can_release_as_vassal(state, source, t);
	}
	void execute_release_and_play_as(sys::state& state, dcon::nation_id source, dcon::national_identity_id t) {
		nations::liberate_nation_from(state, t, source);
		auto holder = state.world.national_identity_get_nation_from_identity_holder(t);
		nations::remove_cores_from_owned(state, holder, state.world.nation_get_identity_from_identity_holder(source));

		if(state.world.nation_get_is_player_controlled(source)) {
			network::switch_player(state, holder, source);
		} else if(state.world.nation_get_is_player_controlled(holder)) {
			network::switch_player(state, source, holder);
		}

		auto old_controller = state.world.nation_get_is_player_controlled(holder);
		state.world.nation_set_is_player_controlled(holder, state.world.nation_get_is_player_controlled(source));
		state.world.nation_set_is_player_controlled(source, old_controller);

		if(state.world.nation_get_is_player_controlled(holder))
			ai::remove_ai_data(state, holder);
		if(state.world.nation_get_is_player_controlled(source))
			ai::remove_ai_data(state, source);

		if(state.local_player_nation == source) {
			state.local_player_nation = holder;
		} else if(state.local_player_nation == holder) {
			state.local_player_nation = source;
		}

		for(auto p : state.world.nation_get_province_ownership(holder)) {
			auto pid = p.get_province();
			state.world.province_set_is_colonial(pid, false);
		}
	}

	inline bool can_change_budget_settings(sys::state& state, dcon::nation_id source, budget_settings_data const& values) {
		return true;
	}

	void change_budget_settings(sys::state& state, dcon::nation_id source, budget_settings_data const& values) {
		payload p{};
		p.type = command_type::change_budget;
		p.source = source;
		p.data.budget_data = values;
		add_to_command_queue(state, p);
	}
	void execute_change_budget_settings(sys::state& state, dcon::nation_id source, budget_settings_data const& values) {
		if(values.administrative_spending != int8_t(-127)) {
			state.world.nation_set_administrative_spending(source, std::clamp(values.administrative_spending, int8_t(0), int8_t(100)));
		}
		if(values.construction_spending != int8_t(-127)) {
			state.world.nation_set_construction_spending(source, std::clamp(values.construction_spending, int8_t(0), int8_t(100)));
		}
		if(values.education_spending != int8_t(-127)) {
			state.world.nation_set_education_spending(source, std::clamp(values.education_spending, int8_t(0), int8_t(100)));
		}
		if(values.land_spending != int8_t(-127)) {
			state.world.nation_set_land_spending(source, std::clamp(values.land_spending, int8_t(0), int8_t(100)));
		}
		if(values.middle_tax != int8_t(-127)) {
			state.world.nation_set_middle_tax(source, std::clamp(values.middle_tax, int8_t(0), int8_t(100)));
		}
		if(values.poor_tax != int8_t(-127)) {
			state.world.nation_set_poor_tax(source, std::clamp(values.poor_tax, int8_t(0), int8_t(100)));
		}
		if(values.rich_tax != int8_t(-127)) {
			state.world.nation_set_rich_tax(source, std::clamp(values.rich_tax, int8_t(0), int8_t(100)));
		}
		if(values.military_spending != int8_t(-127)) {
			state.world.nation_set_military_spending(source, std::clamp(values.military_spending, int8_t(0), int8_t(100)));
		}
		if(values.naval_spending != int8_t(-127)) {
			state.world.nation_set_naval_spending(source, std::clamp(values.naval_spending, int8_t(0), int8_t(100)));
		}
		if(values.social_spending != int8_t(-127)) {
			state.world.nation_set_social_spending(source, std::clamp(values.social_spending, int8_t(0), int8_t(100)));
		}
		if(values.tariffs != int8_t(-127)) {
			state.world.nation_set_tariffs(source, std::clamp(values.tariffs, int8_t(-100), int8_t(100)));
		}
		if(values.domestic_investment != int8_t(-127)) {
			state.world.nation_set_domestic_investment_spending(source, std::clamp(values.domestic_investment, int8_t(0), int8_t(100)));
		}
		if(values.overseas != int8_t(-127)) {
			state.world.nation_set_overseas_spending(source, std::clamp(values.overseas, int8_t(0), int8_t(100)));
		}
		economy::bound_budget_settings(state, source);
	}

	void start_election(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::start_election;
		p.source = source;
		add_to_command_queue(state, p);
	}
	bool can_start_election(sys::state& state, dcon::nation_id source) {
		auto type = state.world.nation_get_government_type(source);
		return state.world.government_type_get_has_elections(type) && !politics::is_election_ongoing(state, source);
	}
	void execute_start_election(sys::state& state, dcon::nation_id source) {
		politics::start_election(state, source);
	}

	void change_influence_priority(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, uint8_t priority) {
		payload p{};
		p.type = command_type::change_influence_priority;
		p.source = source;
		p.data.influence_priority.influence_target = influence_target;
		p.data.influence_priority.priority = priority;
		add_to_command_queue(state, p);
	}
	bool can_change_influence_priority(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, uint8_t priority) {
		// The source must be a great power, while the target must not be a great power.
		// And the embassy can't be banned
		auto const gprel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(gprel && (state.world.gp_relationship_get_status(gprel) & nations::influence::is_banned) != 0)
			return false;
		if(military::are_at_war(state, source, influence_target))
			return false;
		return state.world.nation_get_is_great_power(source) && !state.world.nation_get_is_great_power(influence_target);
	}
	void execute_change_influence_priority(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, uint8_t priority) {
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel) {
			rel = state.world.force_create_gp_relationship(influence_target, source);
		}
		auto& flags = state.world.gp_relationship_get_status(rel);
		switch(priority) {
		case 0:
			flags = (flags & ~nations::influence::priority_mask) | nations::influence::priority_zero;
			break;
		case 1:
			flags = (flags & ~nations::influence::priority_mask) | nations::influence::priority_one;
			break;
		case 2:
			flags = (flags & ~nations::influence::priority_mask) | nations::influence::priority_two;
			break;
		case 3:
			flags = (flags & ~nations::influence::priority_mask) | nations::influence::priority_three;
			break;
		default:
			break;
		}
	}

	void discredit_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		payload p{};
		p.type = command_type::discredit_advisors;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		p.data.influence_action.gp_target = affected_gp;
		add_to_command_queue(state, p);
	}
	bool can_discredit_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		The source must be a great power. The source must have define:DISCREDIT_INFLUENCE_COST influence points. The source may not be
		currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power can be a
		secondary target for this action. To discredit a nation, you must have an opinion of at least "opposed" with the influenced
		nation and you must have a an equal or better opinion level with the influenced nation than the nation you are discrediting
		does.
		*/
		if(!state.world.nation_get_is_great_power(source) || !state.world.nation_get_is_great_power(affected_gp) ||
			state.world.nation_get_is_great_power(influence_target))
		return false;

		if(source == affected_gp)
		return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
		return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.discredit_influence_cost)
		return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
		return false;

		if(military::are_at_war(state, source, influence_target))
		return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel == nations::influence::level_hostile)
		return false;

		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);
		if((state.world.gp_relationship_get_status(orel) & nations::influence::is_banned) != 0)
		return false;

		return nations::influence::is_influence_level_greater_or_equal(clevel,
			nations::influence::get_level(state, affected_gp, influence_target));
	}
	void execute_discredit_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		A nation is discredited for define:DISCREDIT_DAYS. Being discredited twice does not add these durations together; it just
		resets the timer from the current day. Discrediting a nation "increases" your relationship with them by
		define:DISCREDIT_RELATION_ON_ACCEPT. Discrediting costs define:DISCREDIT_INFLUENCE_COST influence points.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);
		if(!orel)
		orel = state.world.force_create_gp_relationship(influence_target, affected_gp);

		state.world.gp_relationship_get_influence(rel) -= state.defines.discredit_influence_cost;
		nations::adjust_relationship(state, source, affected_gp, state.defines.discredit_relation_on_accept);
		state.world.gp_relationship_get_status(orel) |= nations::influence::is_discredited;
		state.world.gp_relationship_set_penalty_expires_date(orel, state.current_date + int32_t(state.defines.discredit_days));

		notification::post(state, notification::message{
			[source, influence_target, affected_gp, enddate = state.current_date + int32_t(state.defines.discredit_days)](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_discredit_1", text::variable_type::x, source, text::variable_type::y, influence_target, text::variable_type::val, affected_gp);
				text::add_line(state, contents, "msg_discredit_2", text::variable_type::x, enddate);
			},
			"msg_discredit_title",
			source, affected_gp, influence_target,
			sys::message_base_type::discredit
		});
	}

	void expel_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		payload p{};
		p.type = command_type::expel_advisors;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		p.data.influence_action.gp_target = affected_gp;
		add_to_command_queue(state, p);
	}
	bool can_expel_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		The source must be a great power. The source must have define:EXPELADVISORS_INFLUENCE_COST influence points. The source may
		not be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power
		can be a secondary target for this action. To expel advisors you must have at least neutral opinion with the influenced nation
		and an equal or better opinion level than that of the nation you are expelling.
		*/
		if(!state.world.nation_get_is_great_power(source) || !state.world.nation_get_is_great_power(affected_gp) ||
			state.world.nation_get_is_great_power(influence_target))
		return false;

		if(source == affected_gp)
		return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
		return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.expeladvisors_influence_cost)
		return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
		return false;

		if(military::are_at_war(state, source, influence_target))
		return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel == nations::influence::level_hostile || clevel == nations::influence::level_opposed)
		return false;

		return nations::influence::is_influence_level_greater_or_equal(clevel,
			nations::influence::get_level(state, affected_gp, influence_target));
	}
	void execute_expel_advisors(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		Expelling a nation's advisors "increases" your relationship with them by define:EXPELADVISORS_RELATION_ON_ACCEPT. This action
		costs define:EXPELADVISORS_INFLUENCE_COST influence points. Being expelled cancels any ongoing discredit effect. Being
		expelled reduces your influence to zero.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);

		state.world.gp_relationship_get_influence(rel) -= state.defines.expeladvisors_influence_cost;
		nations::adjust_relationship(state, source, affected_gp, state.defines.expeladvisors_relation_on_accept);

		if(orel) {
			state.world.gp_relationship_set_influence(orel, 0.0f);
			state.world.gp_relationship_get_status(orel) &= ~nations::influence::is_discredited;
		}

		notification::post(state, notification::message{
			[source, influence_target, affected_gp](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_expel_1", text::variable_type::x, source, text::variable_type::y, influence_target, text::variable_type::val, affected_gp);
			},
			"msg_expel_title",
			source, affected_gp, influence_target,
			sys::message_base_type::expell
		});
	}

	void ban_embassy(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		payload p{};
		p.type = command_type::ban_embassy;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		p.data.influence_action.gp_target = affected_gp;
		add_to_command_queue(state, p);
	}
	bool can_ban_embassy(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		The source must be a great power. The source must have define:BANEMBASSY_INFLUENCE_COST influence points. The source may not
		be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power can
		be a secondary target for this action. To ban a nation you must be at least friendly with the influenced nation and have an
		equal or better opinion level than that of the nation you are expelling.
		*/

		if(!state.world.nation_get_is_great_power(source) || !state.world.nation_get_is_great_power(affected_gp) ||
			state.world.nation_get_is_great_power(influence_target))
		return false;

		if(source == affected_gp)
		return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
		return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.banembassy_influence_cost)
		return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
		return false;

		if(military::are_at_war(state, source, influence_target))
		return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel != nations::influence::level_friendly && clevel != nations::influence::level_in_sphere)
		return false;

		return nations::influence::is_influence_level_greater_or_equal(clevel,
			nations::influence::get_level(state, affected_gp, influence_target));
	}
	void execute_ban_embassy(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		Banning a nation's embassy "increases" your relationship with them by define:BANEMBASSY_RELATION_ON_ACCEPT. This action costs
		define:BANEMBASSY_INFLUENCE_COST influence points. The ban embassy effect lasts for define:BANEMBASSY_DAYS. If you are already
		banned, being banned again simply restarts the timer. Being banned cancels out any ongoing discredit effect.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);
		if(!orel)
		orel = state.world.force_create_gp_relationship(influence_target, affected_gp);

		state.world.gp_relationship_get_influence(rel) -= state.defines.banembassy_influence_cost;
		nations::adjust_relationship(state, source, affected_gp, state.defines.banembassy_relation_on_accept);
		state.world.gp_relationship_get_status(orel) |= nations::influence::is_banned;
		state.world.gp_relationship_set_influence(orel, 0.0f);
		state.world.gp_relationship_set_penalty_expires_date(orel, state.current_date + int32_t(state.defines.banembassy_days));

		notification::post(state, notification::message{
			[source, influence_target, affected_gp, enddate = state.current_date + int32_t(state.defines.banembassy_days)](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_ban_1", text::variable_type::x, source, text::variable_type::y, influence_target, text::variable_type::val, affected_gp);
				text::add_line(state, contents, "msg_ban_2", text::variable_type::x, enddate);
			},
			"msg_ban_title",
			source, affected_gp, influence_target,
			sys::message_base_type::ban
		});
	}

	void increase_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		payload p{};
		p.type = command_type::increase_opinion;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		add_to_command_queue(state, p);
	}
	bool can_increase_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		/*
		The source must be a great power. The source must have define:INCREASEOPINION_INFLUENCE_COST influence points. The source may
		not be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power
		can be a secondary target for this action. Your current opinion must be less than friendly
		*/
		if(!state.world.nation_get_is_great_power(source) || state.world.nation_get_is_great_power(influence_target))
			return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
			return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.increaseopinion_influence_cost)
			return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
			return false;

		if(military::are_at_war(state, source, influence_target))
			return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel == nations::influence::level_friendly || clevel == nations::influence::level_in_sphere)
			return false;

		return true;
	}
	void execute_increase_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		/*
		Increasing the opinion of a nation costs define:INCREASEOPINION_INFLUENCE_COST influence points. Opinion can be increased to a
		maximum of friendly.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);

		state.world.gp_relationship_get_influence(rel) -= state.defines.increaseopinion_influence_cost;
		auto& l = state.world.gp_relationship_get_status(rel);
		l = nations::influence::increase_level(l);

		notification::post(state, notification::message{
			[source, influence_target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_op_inc_1", text::variable_type::x, source, text::variable_type::y, influence_target);
			},
			"msg_op_inc_title",
		source, influence_target, dcon::nation_id{},
			sys::message_base_type::increase_opinion
		});
	}

	void decrease_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		payload p{};
		p.type = command_type::decrease_opinion;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		p.data.influence_action.gp_target = affected_gp;
		add_to_command_queue(state, p);
	}
	bool can_decrease_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		The source must be a great power. The source must have define:DECREASEOPINION_INFLUENCE_COST influence points. The source may
		not be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power
		can be a secondary target for this action. Decreasing the opinion of another nation requires that you have an opinion of at
		least "opposed" with the influenced nation and you must have a an equal or better opinion level with the influenced nation
		than the nation you are lowering their opinion of does. The secondary target must neither have the influenced nation in sphere
		nor may it already be at hostile opinion with them.
		*/
		if(!state.world.nation_get_is_great_power(source) || !state.world.nation_get_is_great_power(affected_gp) ||
			state.world.nation_get_is_great_power(influence_target))
			return false;

		if(source == affected_gp)
			return false;

		if(state.world.nation_get_in_sphere_of(influence_target) == affected_gp)
			return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
			return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.decreaseopinion_influence_cost)
			return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
			return false;

		if(military::are_at_war(state, source, influence_target))
			return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel == nations::influence::level_hostile)
			return false;

		if((nations::influence::level_mask & state.world.gp_relationship_get_status(state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp))) == nations::influence::level_hostile)
			return false;

		return nations::influence::is_influence_level_greater_or_equal(clevel,
			nations::influence::get_level(state, affected_gp, influence_target));
	}
	void execute_decrease_opinion(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		Decreasing the opinion of a nation "increases" your relationship with them by define:DECREASEOPINION_RELATION_ON_ACCEPT. This
		actions costs define:DECREASEOPINION_INFLUENCE_COST influence points. Opinion of the influenced nation of the secondary target
		decreases by one step.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);
		if(!orel)
		orel = state.world.force_create_gp_relationship(influence_target, affected_gp);

		state.world.gp_relationship_get_influence(rel) -= state.defines.decreaseopinion_influence_cost;
		nations::adjust_relationship(state, source, affected_gp, state.defines.decreaseopinion_relation_on_accept);

		auto& l = state.world.gp_relationship_get_status(orel);
		l = nations::influence::decrease_level(l);

		notification::post(state, notification::message{
			[source, influence_target, affected_gp](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_op_dec_1", text::variable_type::x, source, text::variable_type::y, influence_target, text::variable_type::val, affected_gp);
			},
			"msg_op_dec_title",
			source, affected_gp, influence_target,
			sys::message_base_type::decrease_opinion
		});
	}

	void add_to_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		payload p{};
		p.type = command_type::add_to_sphere;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		add_to_command_queue(state, p);
	}
	bool can_add_to_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		/*
		The source must be a great power. The source must have define:ADDTOSPHERE_INFLUENCE_COST influence points. The source may not
		be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power can
		be a secondary target for this action. The nation must have a friendly opinion of you and my not be in the sphere of another
		nation.
		*/
		if(!state.world.nation_get_is_great_power(source) || state.world.nation_get_is_great_power(influence_target))
		return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
		return false;

		if(state.world.gp_relationship_get_influence(rel) < state.defines.addtosphere_influence_cost)
		return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
		return false;

		if(military::are_at_war(state, source, influence_target))
		return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel != nations::influence::level_friendly)
		return false;

		if(state.world.nation_get_in_sphere_of(influence_target))
		return false;

		return true;
	}
	void execute_add_to_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target) {
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);

		state.world.gp_relationship_get_influence(rel) -= state.defines.addtosphere_influence_cost;
		auto& l = state.world.gp_relationship_get_status(rel);
		l = nations::influence::increase_level(l);

		state.world.nation_set_in_sphere_of(influence_target, source);

		notification::post(state, notification::message{
			[source, influence_target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_add_sphere_1", text::variable_type::x, source, text::variable_type::y, influence_target);
			},
			"msg_add_sphere_title",
		source, influence_target, dcon::nation_id{},
			sys::message_base_type::add_to_sphere
		});
	}

	void remove_from_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		payload p{};
		p.type = command_type::remove_from_sphere;
		p.source = source;
		p.data.influence_action.influence_target = influence_target;
		p.data.influence_action.gp_target = affected_gp;
		add_to_command_queue(state, p);
	}
	bool can_remove_from_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		The source must be a great power. The source must have define:REMOVEFROMSPHERE_INFLUENCE_COST influence points. The source may
		not be currently banned with the direct target or currently on the opposite side of a war involving them. Only a great power
		can be a secondary target for this action. To preform this action you must have an opinion level of friendly with the nation
		you are removing from a sphere.
		*/
		if(!state.world.nation_get_is_great_power(source) || !state.world.nation_get_is_great_power(affected_gp) || state.world.nation_get_is_great_power(influence_target))
			return false;

		if(state.world.nation_get_in_sphere_of(influence_target) != affected_gp)
			return false;

		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		if(!rel)
			return false;

		if(source != affected_gp && state.world.gp_relationship_get_influence(rel) < state.defines.removefromsphere_influence_cost)
			return false;

		if((state.world.gp_relationship_get_status(rel) & nations::influence::is_banned) != 0)
			return false;

		if(military::are_at_war(state, source, influence_target))
			return false;

		auto clevel = (nations::influence::level_mask & state.world.gp_relationship_get_status(rel));
		if(clevel != nations::influence::level_friendly && clevel != nations::influence::level_in_sphere)
			return false;

		return true;
	}
	void execute_remove_from_sphere(sys::state& state, dcon::nation_id source, dcon::nation_id influence_target, dcon::nation_id affected_gp) {
		/*
		Removing a nation from a sphere costs define:REMOVEFROMSPHERE_INFLUENCE_COST influence points. If you remove a nation from
		your own sphere you lose define:REMOVEFROMSPHERE_PRESTIGE_COST prestige and gain define:REMOVEFROMSPHERE_INFAMY_COST infamy.
		Removing a nation from the sphere of another nation "increases" your relationship with the former sphere leader by
		define:REMOVEFROMSPHERE_RELATION_ON_ACCEPT points. The removed nation then becomes friendly with its former sphere leader.
		*/
		auto rel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, source);
		state.world.nation_set_in_sphere_of(influence_target, dcon::nation_id{});

		auto orel = state.world.get_gp_relationship_by_gp_influence_pair(influence_target, affected_gp);
		auto& l = state.world.gp_relationship_get_status(orel);
		l = nations::influence::decrease_level(l);

		if(source != affected_gp) {
			state.world.gp_relationship_get_influence(rel) -= state.defines.removefromsphere_influence_cost;
			nations::adjust_relationship(state, source, affected_gp, state.defines.removefromsphere_relation_on_accept);
		} else {
			state.world.nation_get_infamy(source) += state.defines.removefromsphere_infamy_cost;
			nations::adjust_prestige(state, source, -state.defines.removefromsphere_prestige_cost);
		}

		notification::post(state, notification::message{
			[source, influence_target, affected_gp](sys::state& state, text::layout_base& contents) {
				if(source == affected_gp)
				text::add_line(state, contents, "msg_rem_sphere_1", text::variable_type::x, source, text::variable_type::y, influence_target);
				else
				text::add_line(state, contents, "msg_rem_sphere_2", text::variable_type::x, source, text::variable_type::y, influence_target, text::variable_type::val, affected_gp);
			},
			"msg_rem_sphere_title",
			source, affected_gp, influence_target,
			sys::message_base_type::rem_sphere
		});
	}

	void upgrade_colony_to_state(sys::state& state, dcon::nation_id source, dcon::state_instance_id si) {
		payload p{};
		p.type = command_type::upgrade_colony_to_state;
		p.source = source;
		p.data.generic_location.prov = state.world.state_instance_get_capital(si);
		add_to_command_queue(state, p);
	}
	bool can_upgrade_colony_to_state(sys::state& state, dcon::nation_id source, dcon::state_instance_id si) {
		return state.world.state_instance_get_nation_from_state_ownership(si) == source && province::can_integrate_colony(state, si);
	}
	void execute_upgrade_colony_to_state(sys::state& state, dcon::nation_id source, dcon::state_instance_id si) {
		province::upgrade_colonial_state(state, source, si);
	}

	void invest_in_colony(sys::state& state, dcon::nation_id source, dcon::province_id pr) {
		payload p{};
		p.type = command_type::invest_in_colony;
		p.source = source;
		p.data.generic_location.prov = pr;
		add_to_command_queue(state, p);
	}
	bool can_invest_in_colony(sys::state& state, dcon::nation_id source, dcon::province_id p) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(p);
		if(!province::is_colonizing(state, source, state_def))
		return province::can_start_colony(state, source, state_def);
		else
		return province::can_invest_in_colony(state, source, state_def);
	}
	void execute_invest_in_colony(sys::state& state, dcon::nation_id source, dcon::province_id pr) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(pr);
		if(province::is_colonizing(state, source, state_def)) {
			province::increase_colonial_investment(state, source, state_def);
		} else {
			bool adjacent = [&]() {
				for(auto p : state.world.state_definition_get_abstract_state_membership(state_def)) {
					if(!p.get_province().get_nation_from_province_ownership()) {
						for(auto adj : p.get_province().get_province_adjacency()) {
							auto indx = adj.get_connected_provinces(0) != p.get_province() ? 0 : 1;
							auto o = adj.get_connected_provinces(indx).get_nation_from_province_ownership();
							if(o == source)
							return true;
							if(o.get_overlord_as_subject().get_ruler() == source)
							return true;
						}
					}
				}
				return false;
			}();

			auto new_rel = fatten(state.world, state.world.force_create_colonization(state_def, source));
			new_rel.set_level(uint8_t(1));
			new_rel.set_last_investment(state.current_date);
			new_rel.set_points_invested(uint16_t(state.defines.colonization_interest_cost_initial + (adjacent ? state.defines.colonization_interest_cost_neighbor_modifier : 0.0f)));

			state.world.state_definition_set_colonization_stage(state_def, uint8_t(1));
		}
	}

	void abandon_colony(sys::state& state, dcon::nation_id source, dcon::province_id pr) {
		payload p{};
		p.type = command_type::abandon_colony;
		p.source = source;
		p.data.generic_location.prov = pr;
		add_to_command_queue(state, p);
	}

	bool can_abandon_colony(sys::state& state, dcon::nation_id source, dcon::province_id pr) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(pr);
		return province::is_colonizing(state, source, state_def);
	}

	void execute_abandon_colony(sys::state& state, dcon::nation_id source, dcon::province_id p) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(p);

		for(auto rel : state.world.state_definition_get_colonization(state_def)) {
			if(rel.get_colonizer() == source) {
				state.world.delete_colonization(rel);
			}
		}
	}

	void finish_colonization(sys::state& state, dcon::nation_id source, dcon::province_id pr) {
		payload p{};
		p.type = command_type::finish_colonization;
		p.source = source;
		p.data.generic_location.prov = pr;
		add_to_command_queue(state, p);
	}
	bool can_finish_colonization(sys::state& state, dcon::nation_id source, dcon::province_id p) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(p);
		if(state.world.state_definition_get_colonization_stage(state_def) != 3)
		return false;
		auto rng = state.world.state_definition_get_colonization(state_def);
		if(rng.begin() == rng.end())
		return false;
		return (*rng.begin()).get_colonizer() == source;
	}
	void execute_finish_colonization(sys::state& state, dcon::nation_id source, dcon::province_id p) {
		auto state_def = state.world.province_get_state_from_abstract_state_membership(p);

		for(auto pr : state.world.state_definition_get_abstract_state_membership(state_def)) {
			if(!pr.get_province().get_nation_from_province_ownership()) {
				province::change_province_owner(state, pr.get_province(), source);
			}
		}

		state.world.state_definition_set_colonization_temperature(state_def, 0.0f);
		state.world.state_definition_set_colonization_stage(state_def, uint8_t(0));

		auto rng = state.world.state_definition_get_colonization(state_def);

		while(rng.begin() != rng.end()) {
			state.world.delete_colonization(*rng.begin());
		}
	}

	void intervene_in_war(sys::state& state, dcon::nation_id source, dcon::war_id w, bool for_attacker) {
		payload p{};
		p.type = command_type::intervene_in_war;
		p.source = source;
		p.data.war_target.war = w;
		p.data.war_target.for_attacker = for_attacker;
		add_to_command_queue(state, p);
	}
	bool can_intervene_in_war(sys::state& state, dcon::nation_id source, dcon::war_id w, bool for_attacker) {
		/*
		Must be a great power. Must not be involved in or interested in a crisis. Must be at least define:MIN_MONTHS_TO_INTERVENE
		since the war started.
		*/
		if(!nations::is_great_power(state, source))
		return false;
		if(nations::is_involved_in_crisis(state, source))
		return false;
		if(state.current_date < state.world.war_get_start_date(w) + int32_t(30.0f * state.defines.min_months_to_intervene))
		return false;

		/*
		Standard war-joining conditions: can't join if you are already at war against any attacker or defender. Can't join a war
		against your sphere leader or overlord (doesn't apply here obviously). Can't join a crisis war prior to great wars being
		invented (i.e. you have to be in the crisis). Can't join as an attacker against someone you have a truce with.
		*/
		if(!military::joining_war_does_not_violate_constraints(state, source, w, for_attacker))
		return false;
		if(state.world.war_get_is_crisis_war(w) && !state.world.war_get_is_great(w))
		return false;
		if(for_attacker && military::joining_as_attacker_would_break_truce(state, source, w))
		return false;
		if(!for_attacker && military::has_truce_with(state, source, state.world.war_get_primary_attacker(w)))
		return false;

		if(!state.world.war_get_is_great(w)) {
			/*
			If it is not a great war:
			Must be at least friendly with the primary defender. May only join on the defender's side. Defenders must either have no
			wargoals or only status quo. Primary defender must be at defines:MIN_WARSCORE_TO_INTERVENE or less.
			*/

			if(for_attacker)
			return false;
			if(military::defenders_have_non_status_quo_wargoal(state, w))
			return false;

			auto defender = state.world.war_get_primary_defender(w);
			auto rel_w_defender = state.world.get_gp_relationship_by_gp_influence_pair(defender, source);
			auto inf = state.world.gp_relationship_get_status(rel_w_defender) & nations::influence::level_mask;
			if(inf != nations::influence::level_friendly && inf != nations::influence::level_in_sphere)
			return false;

			if(military::primary_warscore(state, w) < -state.defines.min_warscore_to_intervene)
			return false;
		} else {
			/*
			If the war is a great war:
			It is then possible to join the attacking side as well.
			Must have define:GW_INTERVENE_MIN_RELATIONS with the primary defender/attacker to intervene, must have at most
			define:GW_INTERVENE_MAX_EXHAUSTION war exhaustion. Can't join if any nation in your sphere is on the other side Can't join
			if you are allied to any allied to any nation on the other side Can't join if you have units within a nation on the other
			side
			*/
			if(state.world.nation_get_war_exhaustion(source) >= state.defines.gw_intervene_max_exhaustion)
			return false;

			auto primary_on_side = for_attacker ? state.world.war_get_primary_attacker(w) : state.world.war_get_primary_defender(w);
			auto rel = state.world.get_diplomatic_relation_by_diplomatic_pair(primary_on_side, source);
			if(state.world.diplomatic_relation_get_value(rel) < state.defines.gw_intervene_min_relations)
			return false;

			for(auto p : state.world.war_get_war_participant(w)) {
				if(p.get_is_attacker() != for_attacker) { // scan nations on other side
					if(p.get_nation().get_in_sphere_of() == source)
					return false;

					auto irel = state.world.get_diplomatic_relation_by_diplomatic_pair(p.get_nation(), source);
					if(state.world.diplomatic_relation_get_are_allied(irel))
					return false;

					for(auto prov : p.get_nation().get_province_ownership()) {
						for(auto arm : prov.get_province().get_army_location()) {
							if(arm.get_army().get_controller_from_army_control() == source)
							return false;
						}
					}
				}
			}
		}
		return true;
	}
	void execute_intervene_in_war(sys::state& state, dcon::nation_id source, dcon::war_id w, bool for_attacker) {
		if(!state.world.war_get_is_great(w)) {
			bool status_quo_added = false;
			for(auto wg : state.world.war_get_wargoals_attached(w)) {
				if(military::is_defender_wargoal(state, w, wg.get_wargoal()) &&
					(wg.get_wargoal().get_type().get_type_bits() & military::cb_flag::po_status_quo) != 0) {
					status_quo_added = true;
					break;
				}
			}
			if(!status_quo_added) {
			military::add_wargoal(state, w, source, state.world.war_get_primary_attacker(w), state.military_definitions.standard_status_quo, dcon::state_definition_id{},
					dcon::national_identity_id{}, dcon::nation_id{});
			}
		}

		military::add_to_war(state, w, source, for_attacker);
	}

	void suppress_movement(sys::state& state, dcon::nation_id source, dcon::movement_id m) {
		payload p{};
		p.type = command_type::suppress_movement;
		p.source = source;
		p.data.movement.iopt = state.world.movement_get_associated_issue_option(m);
		p.data.movement.tag = state.world.movement_get_associated_independence(m);
		add_to_command_queue(state, p);
	}
	bool can_suppress_movement(sys::state& state, dcon::nation_id source, dcon::movement_id m) {
		if(state.world.movement_get_nation_from_movement_within(m) != source)
		return false;
		if(state.world.movement_get_pop_movement_membership(m).begin() == state.world.movement_get_pop_movement_membership(m).end())
		return false;
		return state.world.nation_get_suppression_points(source) >= rebel::get_suppression_point_cost(state, m);
	}
	void execute_suppress_movement(sys::state& state, dcon::nation_id source, dcon::issue_option_id iopt,
		dcon::national_identity_id tag) {
		dcon::movement_id m;
		if(iopt) {
			m = rebel::get_movement_by_position(state, source, iopt);
		} else if(tag) {
			m = rebel::get_movement_by_independence(state, source, tag);
		}
		if(!m)
		return;
		state.world.nation_get_suppression_points(source) -= rebel::get_suppression_point_cost(state, m);
		rebel::suppress_movement(state, source, m);
	}

	void civilize_nation(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::civilize_nation;
		p.source = source;
		add_to_command_queue(state, p);
	}
	bool can_civilize_nation(sys::state& state, dcon::nation_id source) {
		return state.world.nation_get_modifier_values(source, sys::national_mod_offsets::civilization_progress_modifier) >= 1.0f && !state.world.nation_get_is_civilized(source);
	}
	void execute_civilize_nation(sys::state& state, dcon::nation_id source) {
		nations::make_civilized(state, source);
	}

	void appoint_ruling_party(sys::state& state, dcon::nation_id source, dcon::political_party_id pa) {
		payload p{};
		p.type = command_type::appoint_ruling_party;
		p.source = source;
		p.data.political_party.p = pa;
		add_to_command_queue(state, p);
	}
	bool can_appoint_ruling_party(sys::state& state, dcon::nation_id source, dcon::political_party_id p) {
		/*
		The ideology of the ruling party must be permitted by the government form. There can't be an ongoing election. It can't be the
		current ruling party. The government must allow the player to set the ruling party. The ruling party can manually be changed
		at most once per year.
		*/
		if(state.world.nation_get_ruling_party(source) == p)
			return false;
		if(!politics::political_party_is_active(state, source, p))
			return false;
		if(!politics::can_appoint_ruling_party(state, source))
			return false;
		auto last_change = state.world.nation_get_ruling_party_last_appointed(source);
		if(last_change && state.current_date < last_change + 365)
			return false;
		if(politics::is_election_ongoing(state, source))
			return false;

		auto gov = state.world.nation_get_government_type(source);
		auto new_ideology = state.world.political_party_get_ideology(p);
		if((state.world.government_type_get_ideologies_allowed(gov) & ::culture::to_bits(new_ideology)) == 0) {
			return false;
		}
		return true;
	}

	void execute_appoint_ruling_party(sys::state& state, dcon::nation_id source, dcon::political_party_id p) {
		politics::appoint_ruling_party(state, source, p);
	}

	void enact_reform(sys::state& state, dcon::nation_id source, dcon::reform_option_id r) {
		payload p{};
		p.type = command_type::change_reform_option;
		p.source = source;
		p.data.reform_selection.r = r;
		add_to_command_queue(state, p);
	}
	bool can_enact_reform(sys::state& state, dcon::nation_id source, dcon::reform_option_id r) {
		if(state.world.nation_get_is_player_controlled(source) && state.cheat_data.always_allow_reforms)
			return true;
		bool is_military = state.world.reform_get_reform_type(state.world.reform_option_get_parent_reform(r)) == uint8_t(culture::issue_category::military);
		return is_military ? politics::can_enact_military_reform(state, source, r) : politics::can_enact_economic_reform(state, source, r);
	}
	void execute_enact_reform(sys::state& state, dcon::nation_id source, dcon::reform_option_id r) {
		nations::enact_reform(state, source, r);
		event::update_future_events(state);
	}

	void enact_issue(sys::state& state, dcon::nation_id source, dcon::issue_option_id i) {
		payload p{};
		p.type = command_type::change_issue_option;
		p.source = source;
		p.data.issue_selection.r = i;
		add_to_command_queue(state, p);
	}
	bool can_enact_issue(sys::state& state, dcon::nation_id source, dcon::issue_option_id i) {
		if(state.world.nation_get_is_player_controlled(source) && state.cheat_data.always_allow_reforms)
			return true;

		auto type = state.world.issue_get_issue_type(state.world.issue_option_get_parent_issue(i));
		if(type == uint8_t(culture::issue_type::political)) {
			return politics::can_enact_political_reform(state, source, i);
		} else if(type == uint8_t(culture::issue_type::social)) {
			return politics::can_enact_social_reform(state, source, i);
		}
		return false;
	}
	void execute_enact_issue(sys::state& state, dcon::nation_id source, dcon::issue_option_id i) {
		nations::enact_issue(state, source, i);
		event::update_future_events(state);
	}

	void become_interested_in_crisis(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::become_interested_in_crisis;
		p.source = source;
		add_to_command_queue(state, p);
	}
	bool can_become_interested_in_crisis(sys::state& state, dcon::nation_id source) {
		/*
		Not already interested in the crisis. Is a great power. Not at war. The crisis must have already gotten its initial backers.
		*/
		if(!nations::is_great_power(state, source))
		return false;

		if(state.world.nation_get_is_at_war(source))
		return false;

		if(state.world.nation_get_disarmed_until(source) && state.current_date < state.world.nation_get_disarmed_until(source))
		return false;

		if(state.current_crisis_mode != sys::crisis_mode::heating_up)
		return false;

		for(auto& i : state.crisis_participants) {
			if(i.id == source)
			return false;
			if(!i.id)
			return true;
		}

		return true;
	}
	void execute_become_interested_in_crisis(sys::state& state, dcon::nation_id source) {
		for(auto& i : state.crisis_participants) {
			if(!i.id) {
				i.id = source;
				i.merely_interested = true;
				return;
			}
		}
	}

	void take_sides_in_crisis(sys::state& state, dcon::nation_id source, bool join_attacker) {
		payload p{};
		p.type = command_type::take_sides_in_crisis;
		p.source = source;
		p.data.crisis_join.join_attackers = join_attacker;
		add_to_command_queue(state, p);
	}
	bool can_take_sides_in_crisis(sys::state& state, dcon::nation_id source, bool join_attacker) {
		/*
		Must not be involved in the crisis already. Must be interested in the crisis. Must be a great power. Must not be disarmed. The
		crisis must have already gotten its initial backers.
		*/

		if(state.current_crisis_mode != sys::crisis_mode::heating_up)
		return false;

		for(auto& i : state.crisis_participants) {
			if(i.id == source)
			return i.merely_interested == true;
			if(!i.id)
			return false;
		}
		return false;
	}
	void execute_take_sides_in_crisis(sys::state& state, dcon::nation_id source, bool join_attacker) {
		for(auto& i : state.crisis_participants) {
			if(i.id == source) {
				i.merely_interested = false;
				i.supports_attacker = join_attacker;

				notification::post(state, notification::message{
					[source, join_attacker](sys::state& state, text::layout_base& contents) {
						text::add_line(state, contents, join_attacker ? "msg_crisis_vol_join_1" : "msg_crisis_vol_join_2", text::variable_type::x, source);
					},
					"msg_crisis_vol_join_title",
					source, dcon::nation_id{}, dcon::nation_id{},
					sys::message_base_type::crisis_voluntary_join
				});

				return;
			}
			if(!i.id)
			return;
		}
	}

	bool can_change_stockpile_settings(sys::state& state, dcon::nation_id source, dcon::commodity_id c, float target_amount,
		bool draw_on_stockpiles) {
		return true;
	}

	void change_stockpile_settings(sys::state& state, dcon::nation_id source, dcon::commodity_id c, float target_amount,
		bool draw_on_stockpiles) {
		payload p{};
		p.type = command_type::change_stockpile_settings;
		p.source = source;
		p.data.stockpile_settings.amount = target_amount;
		p.data.stockpile_settings.c = c;
		p.data.stockpile_settings.draw_on_stockpiles = draw_on_stockpiles;
		add_to_command_queue(state, p);
	}

	void execute_change_stockpile_settings(sys::state& state, dcon::nation_id source, dcon::commodity_id c, float target_amount,
		bool draw_on_stockpiles) {
		state.world.nation_set_stockpile_targets(source, c, target_amount);
		state.world.nation_set_drawing_on_stockpiles(source, c, draw_on_stockpiles);
	}

	void take_decision(sys::state& state, dcon::nation_id source, dcon::decision_id d) {
		payload p{};
		p.type = command_type::take_decision;
		p.source = source;
		p.data.decision.d = d;
		add_to_command_queue(state, p);
	}
	bool can_take_decision(sys::state& state, dcon::nation_id source, dcon::decision_id d) {
		if(!(state.world.nation_get_is_player_controlled(source) && state.cheat_data.always_potential_decisions)) {
			auto condition = state.world.decision_get_potential(d);
			if(condition && !trigger::evaluate(state, condition, trigger::to_generic(source), trigger::to_generic(source), 0))
			return false;
		}
		if(!(state.world.nation_get_is_player_controlled(source) && state.cheat_data.always_allow_decisions)) {
			auto condition = state.world.decision_get_allow(d);
			if(condition && !trigger::evaluate(state, condition, trigger::to_generic(source), trigger::to_generic(source), 0))
			return false;
		}
		return true;
	}
	void execute_take_decision(sys::state& state, dcon::nation_id source, dcon::decision_id d) {
		if(auto e = state.world.decision_get_effect(d); e) {
			effect::execute(state, e, trigger::to_generic(source), trigger::to_generic(source), 0, uint32_t(state.current_date.value),
				uint32_t(source.index() << 4 ^ d.index()));
			event::update_future_events(state);
		}

		notification::post(state, notification::message{
			[source, d, when = state.current_date](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_decision_1", text::variable_type::x, source, text::variable_type::y, state.world.decision_get_name(d));
				if(auto e = state.world.decision_get_effect(d); e) {
					text::add_line(state, contents, "msg_decision_2");
					ui::effect_description(state, contents, e, trigger::to_generic(source), trigger::to_generic(source), 0, uint32_t(when.value),
					uint32_t(source.index() << 4 ^ d.index()));
				}
			},
			"msg_decision_title",
		source, dcon::nation_id{}, dcon::nation_id{},
			sys::message_base_type::decision
		});
	}

	void make_event_choice(sys::state& state, event::pending_human_n_event const& e, uint8_t option_id) {
		payload p{};
		p.type = command_type::make_n_event_choice;
		p.source = e.n;
		p.data.pending_human_n_event.date = e.date;
		p.data.pending_human_n_event.e = e.e;
		p.data.pending_human_n_event.from_slot = e.from_slot;
		p.data.pending_human_n_event.ft = e.ft;
		p.data.pending_human_n_event.opt_choice = option_id;
		p.data.pending_human_n_event.primary_slot = e.primary_slot;
		p.data.pending_human_n_event.pt = e.pt;
		p.data.pending_human_n_event.r_hi = e.r_hi;
		p.data.pending_human_n_event.r_lo = e.r_lo;
		add_to_command_queue(state, p);
	}
	void make_event_choice(sys::state& state, event::pending_human_f_n_event const& e, uint8_t option_id) {
		payload p{};
		p.type = command_type::make_f_n_event_choice;
		p.source = e.n;
		p.data.pending_human_f_n_event.date = e.date;
		p.data.pending_human_f_n_event.e = e.e;
		p.data.pending_human_f_n_event.opt_choice = option_id;
		p.data.pending_human_f_n_event.r_hi = e.r_hi;
		p.data.pending_human_f_n_event.r_lo = e.r_lo;
		add_to_command_queue(state, p);
	}
	void make_event_choice(sys::state& state, event::pending_human_p_event const& e, uint8_t option_id) {
		payload p{};
		p.type = command_type::make_p_event_choice;
		p.source = state.world.province_get_nation_from_province_ownership(e.p);
		p.data.pending_human_p_event.date = e.date;
		p.data.pending_human_p_event.e = e.e;
		p.data.pending_human_p_event.p = e.p;
		p.data.pending_human_p_event.from_slot = e.from_slot;
		p.data.pending_human_p_event.ft = e.ft;
		p.data.pending_human_p_event.opt_choice = option_id;
		p.data.pending_human_p_event.r_hi = e.r_hi;
		p.data.pending_human_p_event.r_lo = e.r_lo;
		add_to_command_queue(state, p);
	}
	void make_event_choice(sys::state& state, event::pending_human_f_p_event const& e, uint8_t option_id) {
		payload p{};
		p.type = command_type::make_f_p_event_choice;
		p.source = state.world.province_get_nation_from_province_ownership(e.p);
		p.data.pending_human_f_p_event.date = e.date;
		p.data.pending_human_f_p_event.e = e.e;
		p.data.pending_human_f_p_event.p = e.p;
		p.data.pending_human_f_p_event.opt_choice = option_id;
		p.data.pending_human_f_p_event.r_hi = e.r_hi;
		p.data.pending_human_f_p_event.r_lo = e.r_lo;
		add_to_command_queue(state, p);
	}
	void execute_make_event_choice(sys::state& state, dcon::nation_id source, pending_human_n_event_data const& e) {
		event::take_option(state,
			event::pending_human_n_event {e.r_lo, e.r_hi, e.primary_slot, e.from_slot, e.date, e.e, source, e.pt, e.ft}, e.opt_choice);
		event::update_future_events(state);
	}
	void execute_make_event_choice(sys::state& state, dcon::nation_id source, pending_human_f_n_event_data const& e) {
	event::take_option(state, event::pending_human_f_n_event {e.r_lo, e.r_hi, e.date, e.e, source}, e.opt_choice);
		event::update_future_events(state);
	}
	void execute_make_event_choice(sys::state& state, dcon::nation_id source, pending_human_p_event_data const& e) {
		if(source != state.world.province_get_nation_from_province_ownership(e.p))
		return;

	event::take_option(state, event::pending_human_p_event {e.r_lo, e.r_hi, e.from_slot, e.date, e.e, e.p, e.ft}, e.opt_choice);
		event::update_future_events(state);
	}
	void execute_make_event_choice(sys::state& state, dcon::nation_id source, pending_human_f_p_event_data const& e) {
		if(source != state.world.province_get_nation_from_province_ownership(e.p))
		return;

	event::take_option(state, event::pending_human_f_p_event {e.r_lo, e.r_hi, e.date, e.e, e.p}, e.opt_choice);
		event::update_future_events(state);
	}

	void fabricate_cb(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id type) {
		payload p{};
		p.type = command_type::fabricate_cb;
		p.source = source;
		p.data.cb_fabrication.target = target;
		p.data.cb_fabrication.type = type;
		add_to_command_queue(state, p);
	}
	bool can_fabricate_cb(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id type) {
		if(source == target)
			return false;

		if(state.world.nation_get_constructing_cb_type(source))
			return false;

		/*
		Can't fabricate on someone you are at war with. Can't fabricate on anyone except your overlord if you are a vassal. Requires
		defines:MAKE_CB_DIPLOMATIC_COST diplomatic points. Can't fabricate on your sphere members
		*/

		auto ol = state.world.nation_get_overlord_as_subject(source);
		if(state.world.overlord_get_ruler(ol) && state.world.overlord_get_ruler(ol) != target)
			return false;

		if(state.world.nation_get_in_sphere_of(target) == source)
			return false;

		if(state.world.nation_get_diplomatic_points(source) < state.defines.make_cb_diplomatic_cost)
			return false;

		if(military::are_at_war(state, target, source))
			return false;

		if(military::has_truce_with(state, source, target))
			return false;

		/*
		must be able to fabricate cb
		*/

		auto bits = state.world.cb_type_get_type_bits(type);
		if((bits & (military::cb_flag::always | military::cb_flag::is_not_constructing_cb)) != 0)
			return false;

		if(!military::cb_conditions_satisfied(state, source, target, type))
			return false;

		return true;
	}

	void execute_fabricate_cb(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id type) {
		state.world.nation_set_constructing_cb_target(source, target);
		state.world.nation_set_constructing_cb_type(source, type);
		state.world.nation_get_diplomatic_points(source) -= state.defines.make_cb_diplomatic_cost;
	}

	bool can_cancel_cb_fabrication(sys::state& state, dcon::nation_id source) {
		if(!state.world.nation_get_constructing_cb_target(source))
		return false;
		return true;
	}

	void cancel_cb_fabrication(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::cancel_cb_fabrication;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_cancel_cb_fabrication(sys::state& state, dcon::nation_id source) {
	state.world.nation_set_constructing_cb_target(source, dcon::nation_id{});
		state.world.nation_set_constructing_cb_is_discovered(source, false);
		state.world.nation_set_constructing_cb_progress(source, 0.0f);
	state.world.nation_set_constructing_cb_type(source, dcon::cb_type_id{});
	}

	void ask_for_military_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		payload p{};
		p.type = command_type::ask_for_military_access;
		p.source = asker;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_ask_for_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		/*
		Must have defines:ASKMILACCESS_DIPLOMATIC_COST diplomatic points. Must not be at war against each other. Must not already have
		military access.
		*/
		if(asker == target)
		return false;

		if(state.world.nation_get_diplomatic_points(asker) < state.defines.askmilaccess_diplomatic_cost)
		return false;

		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, asker);
		if(state.world.unilateral_relationship_get_military_access(rel))
		return false;

		if(military::are_at_war(state, asker, target))
		return false;

		return true;
	}
	void execute_ask_for_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		state.world.nation_get_diplomatic_points(asker) -= state.defines.askmilaccess_diplomatic_cost;

		diplomatic_message::message m{};
		m.to = target;
		m.from = asker;
		m.type = diplomatic_message::type::access_request;

		diplomatic_message::post(state, m);
	}

	void give_military_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		payload p{};
		p.type = command_type::give_military_access;
		p.source = asker;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_give_military_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		if(asker == target)
		return false;

		if(state.world.nation_get_diplomatic_points(asker) < state.defines.givemilaccess_diplomatic_cost)
		return false;

		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(asker, target);
		if(state.world.unilateral_relationship_get_military_access(rel))
		return false;

		if(military::are_at_war(state, asker, target))
		return false;

		return true;
	}
	void execute_give_military_access(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		state.world.nation_get_diplomatic_points(asker) -= state.defines.givemilaccess_diplomatic_cost;

		auto urel = state.world.get_unilateral_relationship_by_unilateral_pair(asker, target);
		if(!urel) {
			urel = state.world.force_create_unilateral_relationship(asker, target);
		}
		state.world.unilateral_relationship_set_military_access(urel, true);
		nations::adjust_relationship(state, asker, target, state.defines.givemilaccess_relation_on_accept);
	}

	void ask_for_alliance(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		payload p{};
		p.type = command_type::ask_for_alliance;
		p.source = asker;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_ask_for_alliance(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		/*
		Must not have an alliance. Must not be in a war against each other. Costs defines:ALLIANCE_DIPLOMATIC_COST diplomatic points.
		Great powers may not form an alliance while there is an active crisis. Vassals and substates may only form an alliance with
		their overlords.
		*/
		if(asker == target)
		return false;

		if(state.world.nation_get_diplomatic_points(asker) < state.defines.alliance_diplomatic_cost)
		return false;

		auto rel = state.world.get_diplomatic_relation_by_diplomatic_pair(target, asker);
		if(state.world.diplomatic_relation_get_are_allied(rel))
		return false;

		if(state.world.nation_get_is_great_power(asker) && state.world.nation_get_is_great_power(target) &&
			state.current_crisis != sys::crisis_type::none) {
			return false;
		}

		auto ol = state.world.nation_get_overlord_as_subject(asker);
		if(state.world.overlord_get_ruler(ol))
		return false;
		auto ol2 = state.world.nation_get_overlord_as_subject(target);
		if(state.world.overlord_get_ruler(ol2))
		return false;

		if(military::are_at_war(state, asker, target))
		return false;
		return true;
	}
	void execute_ask_for_alliance(sys::state& state, dcon::nation_id asker, dcon::nation_id target) {
		if(!can_ask_for_alliance(state, asker, target))
		return;

		state.world.nation_get_diplomatic_points(asker) -= state.defines.alliance_diplomatic_cost;

		diplomatic_message::message m{};
		m.to = target;
		m.from = asker;
		m.type = diplomatic_message::type::alliance_request;

		diplomatic_message::post(state, m);
	}

	void state_transfer(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::state_definition_id sid) {
		payload p{};
		p.type = command_type::state_transfer;
		p.source = asker;
		p.data.state_transfer.target = target;
		p.data.state_transfer.state = sid;
		add_to_command_queue(state, p);
	}
	bool can_state_transfer(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::state_definition_id sid) {
		/* (No state specified) To state transfer: Can't be same asker into target, both must be players. If any are great powers,
		they can't state transfer when a crisis occurs. They can't be subjects. They can't be in a state of war */
		if(asker == target)
		return false;
		if(!state.world.nation_get_is_player_controlled(asker) || !state.world.nation_get_is_player_controlled(target))
		return false;
		if(state.current_crisis != sys::crisis_type::none)
		return false;
		auto ol = state.world.nation_get_overlord_as_subject(asker);
		if(state.world.overlord_get_ruler(ol))
		return false;
		auto ol2 = state.world.nation_get_overlord_as_subject(target);
		if(state.world.overlord_get_ruler(ol2))
		return false;
		if(state.world.nation_get_is_at_war(asker) || state.world.nation_get_is_at_war(target))
		return false;
		//Redundant, if we're at war already, we will return false:
		//if(military::are_at_war(state, asker, target))
		//	return false;
		// "Asker gives to target"
		for(const auto ab : state.world.state_definition_get_abstract_state_membership(sid)) {
			if(ab.get_province().get_province_ownership().get_nation() == asker) {
				// Must be controlled by us (if not, it means there are rebels, and we don't allow
				// state transfers on states with rebels)
				if(ab.get_province().get_province_control().get_nation() != asker)
				return false;
			}
		}
		if(state.world.nation_get_owned_state_count(asker) == 1)
		return false;
		return true;
	}
	void execute_state_transfer(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::state_definition_id sid) {
		if(!can_state_transfer(state, asker, target, sid))
		return;

		diplomatic_message::message m{};
		m.to = target;
		m.from = asker;
		m.type = diplomatic_message::type::state_transfer;
		m.data.state = sid;
		diplomatic_message::post(state, m);
	}

	void call_to_arms(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::war_id w) {
		payload p{};
		p.type = command_type::call_to_arms;
		p.source = asker;
		p.data.call_to_arms.target = target;
		p.data.call_to_arms.war = w;
		add_to_command_queue(state, p);
	}
	bool can_call_to_arms(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::war_id w) {
		if(asker == target)
		return false;

		if(state.world.nation_get_diplomatic_points(asker) < state.defines.callally_diplomatic_cost)
		return false;

		if(!nations::are_allied(state, asker, target) && !(state.world.war_get_primary_defender(w) == asker && state.world.nation_get_in_sphere_of(asker) == target))
		return false;

		if(military::is_civil_war(state, w))
		return false;

		if(!military::standard_war_joining_is_possible(state, w, target, military::is_attacker(state, w, asker)))
		return false;

		if(state.world.war_get_is_crisis_war(w) && !state.military_definitions.great_wars_enabled)
		return false;

		return true;
	}
	void execute_call_to_arms(sys::state& state, dcon::nation_id asker, dcon::nation_id target, dcon::war_id w) {
		state.world.nation_get_diplomatic_points(asker) -= state.defines.callally_diplomatic_cost;

		diplomatic_message::message m{};
		m.to = target;
		m.from = asker;
		m.data.war = w;
		m.type = diplomatic_message::type::call_ally_request;

		diplomatic_message::post(state, m);
	}

	void respond_to_diplomatic_message(sys::state& state, dcon::nation_id source, dcon::nation_id from, diplomatic_message::type type,
		bool accept) {
		payload p{};
		p.type = command_type::respond_to_diplomatic_message;
		p.source = source;
		p.data.message.accept = accept;
		p.data.message.from = from;
		p.data.message.type = type;
		add_to_command_queue(state, p);
	}
	void execute_respond_to_diplomatic_message(sys::state& state, dcon::nation_id source, dcon::nation_id from,
		diplomatic_message::type type, bool accept) {
		for(auto& m : state.pending_messages) {
			if(m.type == type && m.from == from && m.to == source) {

				if(accept)
				diplomatic_message::accept(state, m);
				else
				diplomatic_message::decline(state, m);

				m.type = diplomatic_message::type::none;

				return;
			}
		}
	}

	void cancel_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::cancel_military_access;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_cancel_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target)
		return false;
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(state.world.nation_get_diplomatic_points(source) < state.defines.cancelaskmilaccess_diplomatic_cost)
		return false;
		return bool(state.world.unilateral_relationship_get_military_access(rel));
	}
	void execute_cancel_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(target, source);
		if(rel)
		state.world.unilateral_relationship_set_military_access(rel, false);

		state.world.nation_get_diplomatic_points(source) -= state.defines.cancelaskmilaccess_diplomatic_cost;
		nations::adjust_relationship(state, source, target, state.defines.cancelaskmilaccess_relation_on_accept);

		notification::post(state, notification::message{
			[source, target](sys::state& state, text::layout_base& contents) {
				text::add_line(state, contents, "msg_access_canceled_a_1", text::variable_type::x, source, text::variable_type::y, target);
			},
			"msg_access_canceled_a_title",
		source, target, dcon::nation_id{},
			sys::message_base_type::mil_access_end
		});
	}

	void cancel_given_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::cancel_given_military_access;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_cancel_given_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target)
		return false;
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(source, target);
		if(state.world.nation_get_diplomatic_points(source) < state.defines.cancelgivemilaccess_diplomatic_cost)
		return false;
		return bool(state.world.unilateral_relationship_get_military_access(rel));
	}
	void execute_cancel_given_military_access(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		auto rel = state.world.get_unilateral_relationship_by_unilateral_pair(source, target);
		if(rel)
		state.world.unilateral_relationship_set_military_access(rel, false);

		state.world.nation_get_diplomatic_points(source) -= state.defines.cancelgivemilaccess_diplomatic_cost;
		nations::adjust_relationship(state, source, target, state.defines.cancelgivemilaccess_relation_on_accept);

		if(source != state.local_player_nation) {
			notification::post(state, notification::message{
				[source, target](sys::state& state, text::layout_base& contents) {
					text::add_line(state, contents, "msg_access_canceled_b_1", text::variable_type::x, source, text::variable_type::y, target);
				},
				"msg_access_canceled_b_title",
				source, target, dcon::nation_id{},
				sys::message_base_type::mil_access_end
			});
		}
	}

	void cancel_alliance(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::cancel_alliance;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_cancel_alliance(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target)
			return false;

		if(state.world.nation_get_diplomatic_points(source) < state.defines.cancelalliance_diplomatic_cost)
			return false;

		auto rel = state.world.get_diplomatic_relation_by_diplomatic_pair(target, source);
		if(!state.world.diplomatic_relation_get_are_allied(rel))
			return false;

		//if(military::are_allied_in_war(state, source, target))
		//	return false;

		auto ol = state.world.nation_get_overlord_as_subject(source);
		if(state.world.overlord_get_ruler(ol) == target)
			return false;
		return true;
	}
	void execute_cancel_alliance(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		state.world.nation_get_diplomatic_points(source) -= state.defines.cancelalliance_diplomatic_cost;
		nations::adjust_relationship(state, source, target, state.defines.cancelalliance_relation_on_accept);

		nations::break_alliance(state, source, target);
	}

	void declare_war(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id primary_cb,
		dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation, bool call_attacker_allies) {

		payload p{};
		p.type = command_type::declare_war;
		p.source = source;
		p.data.new_war.target = target;
		p.data.new_war.primary_cb = primary_cb;
		p.data.new_war.cb_state = cb_state;
		p.data.new_war.cb_tag = cb_tag;
		p.data.new_war.cb_secondary_nation = cb_secondary_nation;
		p.data.new_war.call_attacker_allies = call_attacker_allies;
		add_to_command_queue(state, p);
	}

	bool can_declare_war(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id primary_cb,
		dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation) {
		dcon::nation_id real_target = target;

		auto target_ol_rel = state.world.nation_get_overlord_as_subject(target);
		if(state.world.overlord_get_ruler(target_ol_rel)) {
			real_target = state.world.overlord_get_ruler(target_ol_rel);
		}

		if(source == target || source == real_target)
			return false;

		if(state.world.nation_get_owned_province_count(target) == 0 || state.world.nation_get_owned_province_count(real_target) == 0)
			return false;

		if(military::are_allied_in_war(state, source, real_target) || military::are_at_war(state, source, real_target))
			return false;

		if(nations::are_allied(state, real_target, source))
			return false;

		auto source_ol_rel = state.world.nation_get_overlord_as_subject(source);
		if(state.world.overlord_get_ruler(source_ol_rel) && state.world.overlord_get_ruler(source_ol_rel) != real_target)
			return false;

		if(state.world.nation_get_in_sphere_of(real_target) == source)
			return false;

		if(state.world.nation_get_diplomatic_points(source) < state.defines.declarewar_diplomatic_cost)
			return false;

		// check CB validity
		if(!military::cb_instance_conditions_satisfied(state, source, target, primary_cb, cb_state, cb_tag, cb_secondary_nation))
			return false;

		//no armies on nation
		for(auto const pc : state.world.nation_get_province_ownership(target)) {
			for(auto const al : pc.get_province().get_army_location()) {
				if(al.get_army().get_controller_from_army_control() == source) {
					return false;
				}
			}
		}
		return true;
	}

	void execute_declare_war(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::cb_type_id primary_cb,
		dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation, bool call_attacker_allies) {
		state.world.nation_get_diplomatic_points(source) -= state.defines.declarewar_diplomatic_cost;
		nations::adjust_relationship(state, source, target, state.defines.declarewar_relation_on_accept);

		dcon::nation_id real_target = target;

		auto target_ol_rel = state.world.nation_get_overlord_as_subject(target);
		if(state.world.overlord_get_ruler(target_ol_rel))
		real_target = state.world.overlord_get_ruler(target_ol_rel);

		if(military::has_truce_with(state, source, real_target)) {
			auto cb_infamy = military::truce_break_cb_infamy(state, primary_cb);
			auto cb_militancy = military::truce_break_cb_militancy(state, primary_cb);
			auto cb_prestige_loss = military::truce_break_cb_prestige_cost(state, primary_cb);

			state.world.nation_get_infamy(source) += cb_infamy;
			nations::adjust_prestige(state, source, cb_prestige_loss);

			for(auto prov : state.world.nation_get_province_ownership(source)) {
				for(auto pop : prov.get_province().get_pop_location()) {
					auto& mil = pop.get_pop().get_militancy();
					mil = std::min(mil + cb_militancy, 10.0f);
				}
			}
		}

		// remove used cb
		auto current_cbs = state.world.nation_get_available_cbs(source);
		for(uint32_t i = current_cbs.size(); i-- > 0;) {
			if(current_cbs[i].cb_type == primary_cb && current_cbs[i].target == target) {
				current_cbs.remove_at(i);
				break;
			}
		}

		auto war = military::create_war(state, source, target, primary_cb, cb_state, cb_tag, cb_secondary_nation);
		military::call_defender_allies(state, war);
		if(call_attacker_allies) {
			military::call_attacker_allies(state, war);
		}
	}

	void add_war_goal(sys::state& state, dcon::nation_id source, dcon::war_id w, dcon::nation_id target, dcon::cb_type_id cb_type,
		dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation) {
		payload p{};
		p.type = command_type::add_war_goal;
		p.source = source;
		p.data.new_war_goal.target = target;
		p.data.new_war_goal.cb_type = cb_type;
		p.data.new_war_goal.cb_state = cb_state;
		p.data.new_war_goal.cb_tag = cb_tag;
		p.data.new_war_goal.cb_secondary_nation = cb_secondary_nation;
		p.data.new_war_goal.war = w;
		add_to_command_queue(state, p);
	}
	bool can_add_war_goal(sys::state& state, dcon::nation_id source, dcon::war_id w, dcon::nation_id target, dcon::cb_type_id cb_type, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation) {
		/*
		The nation adding the war goal must have positive war score against the target of the war goal (see below). And the nation
		must be already able to use the CB in question (e.g. it as fabricated previously) or it must be a constructible CB and the
		nation adding the war goal must have overall jingoism support >= defines:WARGOAL_JINGOISM_REQUIREMENT (x
		defines:GW_JINGOISM_REQUIREMENT_MOD in a great war).
		*/
		if(source == target)
			return false;

		if(state.world.nation_get_is_player_controlled(source) && state.cheat_data.always_allow_wargoals)
			return true;

		if(state.world.nation_get_diplomatic_points(source) < state.defines.addwargoal_diplomatic_cost)
			return false;

		bool is_attacker = military::is_attacker(state, w, source);
		bool target_in_war = false;
		for(auto par : state.world.war_get_war_participant(w)) {
			if(par.get_nation() == target) {
				if(par.get_is_attacker() == is_attacker)
					return false;
				target_in_war = true;
				break;
			}
		}
		if(!target_in_war)
			return false;
		if((!is_attacker && military::defenders_have_status_quo_wargoal(state, w))
		|| (is_attacker && military::attackers_have_status_quo_wargoal(state, w)))
			return false;

		// prevent duplicate war goals
		if(military::war_goal_would_be_duplicate(state, source, w, target, cb_type, cb_state, cb_tag, cb_secondary_nation))
			return false;

		if((state.world.cb_type_get_type_bits(cb_type) & military::cb_flag::always) == 0) {
			bool cb_fabbed = false;
			for(auto const& fab_cb : state.world.nation_get_available_cbs(source)) {
				if(fab_cb.cb_type == cb_type && fab_cb.target == target) {
					cb_fabbed = true;
					break;
				}
			}
			if(!cb_fabbed) {
				if((state.world.cb_type_get_type_bits(cb_type) & military::cb_flag::is_not_constructing_cb) != 0)
					return false; // can only add a constructable cb this way
				auto const total_pop = state.world.nation_get_demographics(source, demographics::total);
				auto const total_jingo = state.world.nation_get_demographics(source, demographics::to_key(state, state.culture_definitions.jingoism));
				auto jingoism_perc = total_pop > 0.f ? total_jingo / total_pop : 0.0f;
				if(state.world.war_get_is_great(w)) {
					if(jingoism_perc < state.defines.wargoal_jingoism_requirement * state.defines.gw_wargoal_jingoism_requirement_mod)
						return false;
				} else {
					if(jingoism_perc < state.defines.wargoal_jingoism_requirement)
						return false;
				}
			}
		}
		return military::cb_instance_conditions_satisfied(state, source, target, cb_type, cb_state, cb_tag, cb_secondary_nation);
	}
	
	void execute_add_war_goal(sys::state& state, dcon::nation_id source, dcon::war_id w, dcon::nation_id target, dcon::cb_type_id cb_type, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag, dcon::nation_id cb_secondary_nation) {
		if(!can_add_war_goal(state, source, w, target, cb_type, cb_state, cb_tag, cb_secondary_nation))
			return;

		state.world.nation_get_diplomatic_points(source) -= state.defines.addwargoal_diplomatic_cost;
		nations::adjust_relationship(state, source, target, state.defines.addwargoal_relation_on_accept);

		float infamy = military::cb_addition_infamy_cost(state, w, cb_type, source, target);
		state.world.nation_get_infamy(source) += infamy;

		military::add_wargoal(state, w, source, target, cb_type, cb_state, cb_tag, cb_secondary_nation);
	}

	void start_peace_offer(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::war_id war, bool is_concession) {
		payload p{};
		p.type = command_type::start_peace_offer;
		p.source = source;
		p.data.new_offer.target = target;
		p.data.new_offer.war = war;
		p.data.new_offer.is_concession = is_concession;
		add_to_command_queue(state, p);
	}
	bool can_start_peace_offer(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::war_id war, bool is_concession) {
		assert(source);
		assert(target);
		{
			auto ol = state.world.nation_get_overlord_as_subject(source);
			if(state.world.overlord_get_ruler(ol) && !(state.world.war_get_primary_attacker(war) == source || state.world.war_get_primary_defender(war) == source))
			return false;
		}
		{
			auto ol = state.world.nation_get_overlord_as_subject(target);
			if(state.world.overlord_get_ruler(ol) && !(state.world.war_get_primary_attacker(war) == target || state.world.war_get_primary_defender(war) == target))
			return false;
		}

		if(state.world.war_get_primary_attacker(war) == source) {
			if(military::get_role(state, war, target) != military::war_role::defender)
			return false;
		} else if(state.world.war_get_primary_defender(war) == source) {
			if(military::get_role(state, war, target) != military::war_role::attacker)
			return false;
		} else if(state.world.war_get_primary_attacker(war) == target) {
			if(military::get_role(state, war, source) != military::war_role::defender)
			return false;
		} else if(state.world.war_get_primary_defender(war) == target) {
			if(military::get_role(state, war, source) != military::war_role::attacker)
			return false;
		} else {
			return false;
		}

		if(state.world.war_get_is_crisis_war(war)) {
			if((state.world.war_get_primary_attacker(war) != source || state.world.war_get_primary_defender(war) != target) &&
				(state.world.war_get_primary_attacker(war) != target || state.world.war_get_primary_defender(war) != source)) {

				return false; // no separate peace
			}
		}

		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		return !pending;
	}
	void execute_start_peace_offer(sys::state& state, dcon::nation_id source, dcon::nation_id target, dcon::war_id war, bool is_concession) {
		auto offer = fatten(state.world, state.world.create_peace_offer());
		offer.set_target(target);
		offer.set_war_from_war_settlement(war);
		offer.set_is_concession(is_concession);
		offer.set_nation_from_pending_peace_offer(source);
	}

	void start_crisis_peace_offer(sys::state& state, dcon::nation_id source, bool is_concession) {
		payload p{};
		p.type = command_type::start_crisis_peace_offer;
		p.source = source;
		p.data.new_offer.is_concession = is_concession;
		add_to_command_queue(state, p);
	}
	bool can_start_crisis_peace_offer(sys::state& state, dcon::nation_id source, bool is_concession) {
		if(source != state.primary_crisis_attacker && source != state.primary_crisis_defender)
			return false;
		if(state.current_crisis_mode != sys::crisis_mode::heating_up)
			return false;

		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		return !pending;
	}
	void execute_start_crisis_peace_offer(sys::state& state, dcon::nation_id source, bool is_concession) {
		auto offer = fatten(state.world, state.world.create_peace_offer());
		offer.set_is_concession(is_concession);
		offer.set_nation_from_pending_peace_offer(source);
		offer.set_is_crisis_offer(true);

		if(state.current_crisis == sys::crisis_type::liberation) {
			if((source == state.primary_crisis_attacker && !is_concession) ||
				(source != state.primary_crisis_attacker && is_concession)) {
				auto new_wg = fatten(state.world, state.world.create_wargoal());
				new_wg.set_added_by(state.primary_crisis_attacker);
				new_wg.set_associated_state(state.world.state_instance_get_definition(state.crisis_state));
				new_wg.set_associated_tag(state.crisis_liberation_tag);
				new_wg.set_peace_offer_from_peace_offer_item(offer);
				new_wg.set_target_nation(state.world.state_instance_get_nation_from_state_ownership(state.crisis_state));
				new_wg.set_type(state.military_definitions.crisis_liberate);
			}
		} else { // colonial
			auto colonizers = state.world.state_definition_get_colonization(state.crisis_colony);

			if((colonizers.end() - colonizers.begin()) >= 2) {
				auto attacking_colonizer = (*colonizers.begin()).get_colonizer();
				auto defending_colonizer = (*(colonizers.begin() + 1)).get_colonizer();

				if((source == state.primary_crisis_attacker && !is_concession) ||
					(source != state.primary_crisis_attacker && is_concession)) {
					auto new_wg = fatten(state.world, state.world.create_wargoal());
					new_wg.set_added_by(attacking_colonizer);
					new_wg.set_associated_state(state.crisis_colony);
					new_wg.set_peace_offer_from_peace_offer_item(offer);
					new_wg.set_target_nation(defending_colonizer);
					new_wg.set_type(state.military_definitions.crisis_colony);
				} else {
					auto new_wg = fatten(state.world, state.world.create_wargoal());
					new_wg.set_added_by(defending_colonizer);
					new_wg.set_associated_state(state.crisis_colony);
					new_wg.set_peace_offer_from_peace_offer_item(offer);
					new_wg.set_target_nation(attacking_colonizer);
					new_wg.set_type(state.military_definitions.crisis_colony);
				}
			}
		}
	}

	void add_to_peace_offer(sys::state& state, dcon::nation_id source, dcon::wargoal_id goal) {
		payload p{};
		p.type = command_type::add_peace_offer_term;
		p.source = source;
		p.data.offer_wargoal.wg = goal;
		add_to_command_queue(state, p);
	}
	bool can_add_to_peace_offer(sys::state& state, dcon::nation_id source, dcon::wargoal_id goal) {
		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		if(!pending)
		return false;

		auto war = state.world.peace_offer_get_war_from_war_settlement(pending);
		auto wg = fatten(state.world, goal);
		auto target = state.world.peace_offer_get_target(pending);

		if(!war)
		return false;
		if(wg.get_war_from_wargoals_attached() != war)
		return false;

		//int32_t total = military::cost_of_peace_offer(state, pending);
		//int32_t new_wg_cost = military::peace_cost(state, war, wg.get_type(), wg.get_added_by(), wg.get_target_nation(), wg.get_secondary_nation(), wg.get_associated_state(), wg.get_associated_tag());
		//if(total + new_wg_cost > 100)
		//	return false;

		if(state.world.war_get_primary_attacker(war) == source && state.world.war_get_primary_defender(war) == target)
		return true;
		if(state.world.war_get_primary_attacker(war) == target && state.world.war_get_primary_defender(war) == source)
		return true;

		if(state.world.peace_offer_get_is_concession(pending)) {
			if(state.world.war_get_primary_attacker(war) == source || state.world.war_get_primary_defender(war) == source) {
				if(wg.get_added_by() == target)
				return true;
				if(wg.get_added_by().get_overlord_as_subject().get_ruler() == target)
				return true;
			} else {
				if(wg.get_target_nation() == source)
				return true;
				if(wg.get_target_nation().get_overlord_as_subject().get_ruler() == source)
				return true;
			}
		} else {
			if(state.world.war_get_primary_attacker(war) == source || state.world.war_get_primary_defender(war) == source) {
				if(wg.get_target_nation() == target)
				return true;
				if(wg.get_target_nation().get_overlord_as_subject().get_ruler() == target)
				return true;
			} else {
				if(wg.get_added_by() == target)
				return true;
				if(wg.get_added_by().get_overlord_as_subject().get_ruler() == target)
				return true;
			}
		}
		return false;
	}
	void execute_add_to_peace_offer(sys::state& state, dcon::nation_id source, dcon::wargoal_id goal) {
		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		state.world.force_create_peace_offer_item(pending, goal);
	}

	void add_to_crisis_peace_offer(sys::state& state, dcon::nation_id source, dcon::nation_id wargoal_from, dcon::nation_id target,
		dcon::cb_type_id primary_cb, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag,
		dcon::nation_id cb_secondary_nation) {
		payload p{};
		p.type = command_type::add_wargoal_to_crisis_offer;
		p.source = source;
		p.data.crisis_invitation.invited = wargoal_from;
		p.data.crisis_invitation.target = target;
		p.data.crisis_invitation.cb_type = primary_cb;
		p.data.crisis_invitation.cb_state = cb_state;
		p.data.crisis_invitation.cb_tag = cb_tag;
		p.data.crisis_invitation.cb_secondary_nation = cb_secondary_nation;
		add_to_command_queue(state, p);
	}
	bool can_add_to_crisis_peace_offer(sys::state& state, dcon::nation_id source, dcon::nation_id wargoal_from,
		dcon::nation_id target, dcon::cb_type_id primary_cb, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag,
		dcon::nation_id cb_secondary_nation) {

		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		if(!pending)
			return false;

		auto war = state.world.peace_offer_get_war_from_war_settlement(pending);
		if(war)
			return false;

		bool found = [&]() {
			for(auto& par : state.crisis_participants) {
				if(!par.id) {
					return false; // not in crisis
				}
				if(par.id == wargoal_from) {
					if(cb_state == par.joined_with_offer.wargoal_state && cb_tag == par.joined_with_offer.wargoal_tag &&
						cb_secondary_nation == par.joined_with_offer.wargoal_secondary_nation && target == par.joined_with_offer.target &&
						primary_cb == par.joined_with_offer.wargoal_type)
						return true;
					else
						return false;
				}
			}
			return false;
		}();

		if(!found)
			return false;

		// no duplicates
		for(auto wg : state.world.peace_offer_get_peace_offer_item(pending)) {
			if(wg.get_wargoal().get_added_by() == wargoal_from)
				return false;
		}
		return true;
	}
	void execute_add_to_crisis_peace_offer(sys::state& state, dcon::nation_id source, crisis_invitation_data const& data) {
		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);

		auto wg = fatten(state.world, state.world.create_wargoal());
		wg.set_peace_offer_from_peace_offer_item(pending);
		wg.set_added_by(data.invited);
		wg.set_associated_state(data.cb_state);
		wg.set_associated_tag(data.cb_tag);
		wg.set_secondary_nation(data.cb_secondary_nation);
		wg.set_target_nation(data.target);
		wg.set_type(data.cb_type);
	}

	void send_peace_offer(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::send_peace_offer;
		p.source = source;
		add_to_command_queue(state, p);
	}
	bool can_send_peace_offer(sys::state& state, dcon::nation_id source) {
		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		if(!pending || !state.world.peace_offer_get_war_from_war_settlement(pending))
			return false;
		return true;
	}
	void execute_send_peace_offer(sys::state& state, dcon::nation_id source) {
		auto pending_offer = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		auto in_war = state.world.peace_offer_get_war_from_war_settlement(pending_offer);

		if(!in_war) {
			return;
		}

		auto target = state.world.peace_offer_get_target(pending_offer);
		// A peace offer must be accepted when war score reaches 100.
		if(military::directed_warscore(state, in_war, source, target) >= 100.0f && (!target.get_is_player_controlled() || !state.world.peace_offer_get_is_concession(pending_offer)) && military::cost_of_peace_offer(state, pending_offer) <= 100) {
			military::implement_peace_offer(state, pending_offer);
		} else {
			diplomatic_message::message m{};
			m.to = target;
			m.from = source;
			m.data.peace = pending_offer;
			m.type = diplomatic_message::type::peace_offer;
			diplomatic_message::post(state, m);
		}
	}

	void send_crisis_peace_offer(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::send_crisis_peace_offer;
		p.source = source;
		add_to_command_queue(state, p);
	}
	bool can_send_crisis_peace_offer(sys::state& state, dcon::nation_id source) {
		auto pending = state.world.nation_get_peace_offer_from_pending_peace_offer(source);
		if(!pending || state.world.peace_offer_get_war_from_war_settlement(pending))
			return false;
		if(source != state.primary_crisis_attacker && source != state.primary_crisis_defender)
			return false;
		if(state.current_crisis_mode != sys::crisis_mode::heating_up)
			return false;
		return true;
	}
	void execute_send_crisis_peace_offer(sys::state& state, dcon::nation_id source) {
		auto pending_offer = state.world.nation_get_peace_offer_from_pending_peace_offer(source);

		if(!can_send_crisis_peace_offer(state, source)) {
			if(pending_offer) {
				if(!state.world.peace_offer_get_war_from_war_settlement(pending_offer))
					nations::cleanup_crisis_peace_offer(state, pending_offer);
				else
					state.world.delete_peace_offer(pending_offer);
			}
			return;
		}

		auto target = state.primary_crisis_attacker == source ? state.primary_crisis_defender : state.primary_crisis_attacker;

		diplomatic_message::message m{};
		m.to = target;
		m.from = source;
		m.data.peace = pending_offer;
		m.type = diplomatic_message::type::crisis_peace_offer;

		diplomatic_message::post(state, m);
	}

	void move_army(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::province_id dest, bool reset) {
		payload p{};
		p.type = command_type::move_army;
		p.source = source;
		p.data.army_movement.a = a;
		p.data.army_movement.dest = dest;
		p.data.army_movement.reset = reset;
		add_to_command_queue(state, p);
	}

	bool can_partial_retreat_from(sys::state& state, dcon::land_battle_id b) {
		if(b && !military::can_retreat_from_battle(state, b))
			return false;
		return true;
	}
	bool can_partial_retreat_from(sys::state& state, dcon::naval_battle_id b) {
		if(b && !military::can_retreat_from_battle(state, b))
			return false;
		return true;
	}

	std::vector<dcon::province_id> can_move_army(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::province_id dest) {
		if(source != state.world.army_get_controller_from_army_control(a))
			return std::vector<dcon::province_id>{};
		if(state.world.army_get_is_retreating(a))
			return std::vector<dcon::province_id>{};
		if(!dest)
			return std::vector<dcon::province_id>{}; // stop movement

		auto last_province = state.world.army_get_location_from_army_location(a);
		auto movement = state.world.army_get_path(a);
		if(movement.size() > 0) {
			last_province = movement.at(0);
		}

		if(last_province == dest)
			return std::vector<dcon::province_id>{};

		if(!can_partial_retreat_from(state, state.world.army_get_battle_from_army_battle_participation(a)))
			return std::vector<dcon::province_id>{};

		if(dest.index() < state.province_definitions.first_sea_province.index()) {
			if(state.world.army_get_black_flag(a)) {
				return province::make_unowned_land_path(state, last_province, dest);
			} else if(province::has_access_to_province(state, source, dest)) {
				return province::make_land_path(state, last_province, dest, source, a);
			} else {
				return std::vector<dcon::province_id>{};
			}
		} else {
			if(!military::can_embark_onto_sea_tile(state, source, dest, a))
				return std::vector<dcon::province_id>{};
			if(state.world.army_get_black_flag(a)) {
				return province::make_unowned_land_path(state, last_province, dest);
			} else {
				return province::make_land_path(state, last_province, dest, source, a);
			}
		}
	}

	void execute_move_army(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::province_id dest, bool reset) {
		if(source != state.world.army_get_controller_from_army_control(a))
			return;
		if(state.world.army_get_is_retreating(a))
			return;

		auto battle = state.world.army_get_battle_from_army_battle_participation(a);
		if(dest.index() < state.province_definitions.first_sea_province.index()) {
			/* Case for land destinations */
			if(battle && !province::has_naval_access_to_province(state, source, dest)) {
				return;
			}
		} else {
			/* Case for naval destinations, we check the land province adjacent henceforth */
			if(battle && !military::can_embark_onto_sea_tile(state, source, dest, a)) {
				return;
			}
		}

		auto existing_path = state.world.army_get_path(a);
		if(!dest) {
			existing_path.clear();
			state.world.army_set_arrival_time(a, sys::date{});
			return;
		}

		auto old_first_prov = existing_path.size() > 0 ? existing_path.at(existing_path.size() - 1) : dcon::province_id{};
		if(reset) {
			existing_path.clear();
		}

		auto path = can_move_army(state, source, a, dest);

		if(path.size() > 0) {
			auto append_size = uint32_t(path.size());
			auto old_size = existing_path.size();
			auto new_size = old_size + append_size;
			existing_path.resize(new_size);

			for(uint32_t i = old_size; i-- > 0; ) {
				existing_path.at(append_size + i) = existing_path.at(i);
			}
			for(uint32_t i = 0; i < append_size; ++i) {
				existing_path.at(i) = path[i];
			}

			if(existing_path.at(new_size - 1) != old_first_prov) {
				state.world.army_set_arrival_time(a, military::arrival_time_to(state, a, path.back()));
			}
			state.world.army_set_dig_in(a, 0);
			state.world.army_set_is_rebel_hunter(a, false);
		} else if(reset) {
			state.world.army_set_arrival_time(a, sys::date{});
		}
		state.world.army_set_moving_to_merge(a, false);

		if(battle) {
			state.world.army_set_is_retreating(a, true);
			state.world.army_set_battle_from_army_battle_participation(a, dcon::land_battle_id{});
			for(auto reg : state.world.army_get_army_membership(a)) {
				{
					auto& line = state.world.land_battle_get_attacker_front_line(battle);
					for(auto& lr : line) {
						if(lr == reg.get_regiment())
							lr = dcon::regiment_id{};
					}
				}
				{
					auto& line = state.world.land_battle_get_attacker_back_line(battle);
					for(auto& lr : line) {
						if(lr == reg.get_regiment())
							lr = dcon::regiment_id{};
					}
				}
				{
					auto& line = state.world.land_battle_get_defender_front_line(battle);
					for(auto& lr : line) {
						if(lr == reg.get_regiment())
							lr = dcon::regiment_id{};
					}
				}
				{
					auto& line = state.world.land_battle_get_defender_back_line(battle);
					for(auto& lr : line) {
						if(lr == reg.get_regiment())
							lr = dcon::regiment_id{};
					}
				}
				auto res = state.world.land_battle_get_reserves(battle);
				for(uint32_t i = res.size(); i-- > 0;) {
					if(res[i].regiment == reg.get_regiment()) {
						res[i] = res[res.size() - 1];
						res.pop_back();
					}
				}
			}
			//update leaders
			military::update_battle_leaders(state, battle);
		}
	}

	void move_navy(sys::state& state, dcon::nation_id source, dcon::navy_id n, dcon::province_id dest, bool reset) {
		payload p{};
		p.type = command_type::move_navy;
		p.source = source;
		p.data.navy_movement.n = n;
		p.data.navy_movement.dest = dest;
		p.data.navy_movement.reset = reset;
		add_to_command_queue(state, p);
	}
	std::vector<dcon::province_id> can_move_navy(sys::state& state, dcon::nation_id source, dcon::navy_id n, dcon::province_id dest) {
		if(source != state.world.navy_get_controller_from_navy_control(n))
			return std::vector<dcon::province_id>{};
		if(state.world.navy_get_is_retreating(n))
			return std::vector<dcon::province_id>{};
		if(!dest)
			return std::vector<dcon::province_id>{}; // stop movement

		auto last_province = state.world.navy_get_location_from_navy_location(n);
		auto movement = state.world.navy_get_path(n);
		if(movement.size() > 0) {
			last_province = movement.at(0);
		}

		if(last_province == dest)
			return std::vector<dcon::province_id>{};

		if(!can_partial_retreat_from(state, state.world.navy_get_battle_from_navy_battle_participation(n)))
			return std::vector<dcon::province_id>{};

		if(dest.index() >= state.province_definitions.first_sea_province.index()) {
			return province::make_naval_path(state, last_province, dest);
		} else {
			if(!state.world.province_get_is_coast(dest))
				return std::vector<dcon::province_id>{};
			if(!province::has_naval_access_to_province(state, source, dest))
				return std::vector<dcon::province_id>{};
			return province::make_naval_path(state, last_province, dest);
		}
	}
	void execute_move_navy(sys::state& state, dcon::nation_id source, dcon::navy_id n, dcon::province_id dest, bool reset) {
		if(source != state.world.navy_get_controller_from_navy_control(n))
			return;
		if(state.world.navy_get_is_retreating(n))
			return;

		auto battle = state.world.navy_get_battle_from_navy_battle_participation(n);
		if(battle && dest.index() < state.province_definitions.first_sea_province.index() && !province::has_naval_access_to_province(state, source, dest)) {
			return;
		}

		auto existing_path = state.world.navy_get_path(n);

		if(!dest) {
			existing_path.clear();
			state.world.navy_set_arrival_time(n, sys::date{});
			return;
		}

		auto old_first_prov = existing_path.size() > 0 ? existing_path.at(existing_path.size() - 1) : dcon::province_id{};
		if(reset) {
			existing_path.clear();
		}

		auto path = can_move_navy(state, source, n, dest);
		if(path.size() > 0) {
			auto append_size = uint32_t(path.size());
			auto old_size = existing_path.size();
			auto new_size = old_size + append_size;
			existing_path.resize(new_size);

			for(uint32_t i = old_size; i-- > 0; ) {
				existing_path.at(append_size + i) = existing_path.at(i);
			}
			for(uint32_t i = 0; i < append_size; ++i) {
				existing_path.at(i) = path[i];
			}

			if(existing_path.at(new_size - 1) != old_first_prov) {
				state.world.navy_set_arrival_time(n, military::arrival_time_to(state, n, path.back()));
			}
		} else if(reset) {
			state.world.navy_set_arrival_time(n, sys::date{});
		}
		state.world.navy_set_moving_to_merge(n, false);

		if(battle) {
			state.world.navy_set_is_retreating(n, true);
			state.world.navy_set_battle_from_navy_battle_participation(n, dcon::naval_battle_id{});
			for(auto shp : state.world.navy_get_navy_membership(n)) {
				for(auto& s : state.world.naval_battle_get_slots(battle)) {
					if(s.ship == shp.get_ship()) {
						s.ship = dcon::ship_id{};
						s.flags &= ~s.mode_mask;
						s.flags |= s.mode_retreated;
					}
				}
			}
			//update leaders
			military::update_battle_leaders(state, battle);
		}
	}

	void embark_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::embark_army;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}

	bool can_embark_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		if(source != state.world.army_get_controller_from_army_control(a))
			return false;
		if(state.world.army_get_is_retreating(a))
			return false;

		auto location = state.world.army_get_location_from_army_location(a);
		if(location.index() >= state.province_definitions.first_sea_province.index())
			return false;

		if(state.world.army_get_battle_from_army_battle_participation(a))
			return false;

		if(state.world.army_get_navy_from_army_transport(a)) {
			return true;
		} else {
			return military::can_embark_onto_sea_tile(state, source, location, a);
		}
	}

	void execute_embark_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		if(source != state.world.army_get_controller_from_army_control(a))
			return;
		if(state.world.army_get_is_retreating(a))
			return;

		if(state.world.army_get_battle_from_army_battle_participation(a))
			return;

		auto location = state.world.army_get_location_from_army_location(a);
		if(location.index() >= state.province_definitions.first_sea_province.index())
			return;

		if(state.world.army_get_navy_from_army_transport(a)) {
			state.world.army_set_navy_from_army_transport(a, dcon::navy_id{});
			military::army_arrives_in_province(state, a, location, military::crossing_type::none);
		} else {
			auto to_navy = military::find_embark_target(state, source, location, a);
			if(to_navy) {
				state.world.army_set_navy_from_army_transport(a, to_navy);
				state.world.army_set_black_flag(a, false);
			}
		}
		state.world.army_set_is_rebel_hunter(a, false);
		state.world.army_set_dig_in(a, 0);
	}

	void merge_armies(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::army_id b) {
		payload p{};
		p.type = command_type::merge_armies;
		p.source = source;
		p.data.merge_army.a = a;
		p.data.merge_army.b = b;
		add_to_command_queue(state, p);
	}
	bool can_merge_armies(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::army_id b) {
		if(state.world.army_get_controller_from_army_control(a) != source)
		return false;
		if(state.world.army_get_controller_from_army_control(b) != source)
		return false;
		if(state.world.army_get_is_retreating(a) || state.world.army_get_is_retreating(b))
		return false;
		if(state.world.army_get_navy_from_army_transport(a))
		return false;
		if(state.world.army_get_navy_from_army_transport(b))
		return false;

		if(state.world.army_get_location_from_army_location(a) != state.world.army_get_location_from_army_location(b))
		return false;

		if(state.world.army_get_battle_from_army_battle_participation(a) ||
			state.world.army_get_battle_from_army_battle_participation(b))
		return false;

		return true;
	}

	void execute_merge_armies(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::army_id b) {
		// take leader
		auto a_leader = state.world.army_get_general_from_army_leadership(a);
		auto b_leader = state.world.army_get_general_from_army_leadership(b);
		if(!a_leader && b_leader) {
			state.world.army_set_general_from_army_leadership(a, b_leader);
		}

		// stop movement
		state.world.army_get_path(a).clear();
	state.world.army_set_arrival_time(a, sys::date{});

		auto regs = state.world.army_get_army_membership(b);
		while(regs.begin() != regs.end()) {
			auto reg = (*regs.begin()).get_regiment();
			reg.set_army_from_army_membership(a);
		}

		if(source == state.local_player_nation && state.is_selected(b)) {
			state.deselect(b);
		}
		military::cleanup_army(state, b);
	}

	void merge_navies(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::navy_id b) {
		payload p{};
		p.type = command_type::merge_navies;
		p.source = source;
		p.data.merge_navy.a = a;
		p.data.merge_navy.b = b;
		add_to_command_queue(state, p);
	}
	bool can_merge_navies(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::navy_id b) {
		if(state.world.navy_get_controller_from_navy_control(a) != source)
		return false;
		if(state.world.navy_get_controller_from_navy_control(b) != source)
		return false;
		if(state.world.navy_get_is_retreating(a) || state.world.navy_get_is_retreating(b))
		return false;

		if(state.world.navy_get_location_from_navy_location(a) != state.world.navy_get_location_from_navy_location(b))
		return false;

		if(state.world.navy_get_battle_from_navy_battle_participation(a) ||
			state.world.navy_get_battle_from_navy_battle_participation(b))
		return false;

		return true;
	}
	void execute_merge_navies(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::navy_id b) {
		// take leader
		auto a_leader = state.world.navy_get_admiral_from_navy_leadership(a);
		auto b_leader = state.world.navy_get_admiral_from_navy_leadership(b);
		if(!a_leader && b_leader) {
			state.world.navy_set_admiral_from_navy_leadership(a, b_leader);
		}

		// stop movement
		state.world.navy_get_path(a).clear();
	state.world.navy_set_arrival_time(a, sys::date{});

		auto regs = state.world.navy_get_navy_membership(b);
		while(regs.begin() != regs.end()) {
			auto reg = (*regs.begin()).get_ship();
			reg.set_navy_from_navy_membership(a);
		}

		auto transported = state.world.navy_get_army_transport(b);
		while(transported.begin() != transported.end()) {
			auto arm = (*transported.begin()).get_army();
			arm.set_navy_from_army_transport(a);
		}

		if(source == state.local_player_nation && state.is_selected(b)) {
			state.deselect(b);
		}
		military::cleanup_navy(state, b);
	}

	void disband_undermanned_regiments(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::disband_undermanned;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	bool can_disband_undermanned_regiments(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		return state.world.army_get_controller_from_army_control(a) == source && !state.world.army_get_is_retreating(a) &&
		!bool(state.world.army_get_battle_from_army_battle_participation(a));
	}
	void execute_disband_undermanned_regiments(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		std::vector<dcon::regiment_id> regs;
		for(auto r : state.world.army_get_army_membership(a)) {
			auto pop = r.get_regiment().get_pop_from_regiment_source();
			if(!pop || pop.get_size() < state.defines.pop_min_size_for_regiment)
			regs.push_back(r.get_regiment());
		}
		for(auto r : regs)
		state.world.delete_regiment(r);
	}

	void toggle_rebel_hunting(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::toggle_hunt_rebels;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	void execute_toggle_rebel_hunting(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		auto owner = state.world.army_get_controller_from_army_control(a);
		if(owner != source)
		return;

		auto current_state = state.world.army_get_is_rebel_hunter(a);
		if(current_state) {
			state.world.army_set_is_rebel_hunter(a, false);
		} else {
			auto path = state.world.army_get_path(a);
			if(path.size() > 0) {
				state.world.army_set_ai_province(a, path.at(0));
			} else {
				state.world.army_set_ai_province(a, state.world.army_get_location_from_army_location(a));
				if(!state.world.army_get_battle_from_army_battle_participation(a)
				&& !state.world.army_get_navy_from_army_transport(a)) {

					military::send_rebel_hunter_to_next_province(state, a, state.world.army_get_location_from_army_location(a));
				}
			}
			state.world.army_set_is_rebel_hunter(a, true);
		}
	}

	void toggle_unit_ai_control(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::toggle_unit_ai_control;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	void execute_toggle_unit_ai_control(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		auto owner = state.world.army_get_controller_from_army_control(a);
		if(owner != source)
		return;
		auto current_state = state.world.army_get_is_ai_controlled(a);
		if(current_state) {
			state.world.army_set_ai_activity(a, 0);
			state.world.army_set_is_ai_controlled(a, false);
		} else {
			//turn off rebel control
			state.world.army_set_is_rebel_hunter(a, false);
			auto path = state.world.army_get_path(a);
			if(path.size() > 0) {
				state.world.army_set_ai_province(a, path.at(0));
			} else {
				state.world.army_set_ai_province(a, state.world.army_get_location_from_army_location(a));
				if(!state.world.army_get_battle_from_army_battle_participation(a)
				&& !state.world.army_get_navy_from_army_transport(a)) {

					military::send_rebel_hunter_to_next_province(state, a, state.world.army_get_location_from_army_location(a));
				}
			}
			state.world.army_set_ai_activity(a, 0);
			state.world.army_set_is_ai_controlled(a, true);
		}
	}

	void toggle_mobilized_is_ai_controlled(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::toggle_mobilized_is_ai_controlled;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_toggle_mobilized_is_ai_controlled(sys::state& state, dcon::nation_id source) {
		state.world.nation_set_mobilized_is_ai_controlled(source, !state.world.nation_get_mobilized_is_ai_controlled(source));
	}

	void release_subject(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::release_subject;
		p.source = source;
		p.data.diplo_action.target = target;
		add_to_command_queue(state, p);
	}
	bool can_release_subject(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		return state.world.overlord_get_ruler(state.world.nation_get_overlord_as_subject(target)) == source;
	}
	void execute_release_subject(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(!can_release_subject(state, source, target))
			return;
		nations::release_vassal(state, state.world.nation_get_overlord_as_subject(target));
	}

	void evenly_split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::even_split_army;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	bool can_evenly_split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		return can_split_army(state, source, a);
	}
	void execute_evenly_split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		bool inf_split = false;
		bool cav_split = false;
		bool art_split = false;

		static std::vector<dcon::regiment_id> to_transfer;
		to_transfer.clear();

		for(auto t : state.world.army_get_army_membership(a)) {
			auto type = state.military_definitions.unit_base_definitions[t.get_regiment().get_type()].type;
			if(type == military::unit_type::infantry) {
				if(inf_split) {
					to_transfer.push_back(t.get_regiment());
				}
				inf_split = !inf_split;
			} else if(type == military::unit_type::cavalry) {
				if(cav_split) {
					to_transfer.push_back(t.get_regiment());
				}
				cav_split = !cav_split;
			} else if(type == military::unit_type::support || type == military::unit_type::special) {
				if(art_split) {
					to_transfer.push_back(t.get_regiment());
				}
				art_split = !art_split;
			}
		}

		if(to_transfer.size() > 0) {
			auto new_u = fatten(state.world, state.world.create_army());
			new_u.set_controller_from_army_control(source);
			new_u.set_location_from_army_location(state.world.army_get_location_from_army_location(a));
			new_u.set_black_flag(state.world.army_get_black_flag(a));

			for(auto t : to_transfer) {
				state.world.regiment_set_army_from_army_membership(t, new_u);
			}

			if(source == state.local_player_nation && state.is_selected(a)) {
				state.deselect(a);
				state.select(new_u);
			}
		}
	}

	void evenly_split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		payload p{};
		p.type = command_type::even_split_navy;
		p.source = source;
		p.data.navy_movement.n = a;
		add_to_command_queue(state, p);
	}
	bool can_evenly_split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		return can_split_navy(state, source, a);
	}
	void execute_evenly_split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		static std::vector<dcon::ship_id> to_transfer;
		to_transfer.clear();

		bool big_split = false;
		bool sm_split = false;
		bool tra_split = false;

		for(auto t : state.world.navy_get_navy_membership(a)) {
			auto type = state.military_definitions.unit_base_definitions[t.get_ship().get_type()].type;
			if(type == military::unit_type::big_ship) {
				if(big_split) {
					to_transfer.push_back(t.get_ship());
				}
				big_split = !big_split;
			} else if(type == military::unit_type::light_ship) {
				if(sm_split) {
					to_transfer.push_back(t.get_ship());
				}
				sm_split = !sm_split;
			} else if(type == military::unit_type::transport) {
				if(tra_split) {
					to_transfer.push_back(t.get_ship());
				}
				tra_split = !tra_split;
			}
		}

		if(to_transfer.size() > 0) {
			auto new_u = fatten(state.world, state.world.create_navy());
			new_u.set_controller_from_navy_control(source);
			new_u.set_location_from_navy_location(state.world.navy_get_location_from_navy_location(a));

			for(auto t : to_transfer) {
				state.world.ship_set_navy_from_navy_membership(t, new_u);
			}

			if(source == state.local_player_nation && state.is_selected(a)) {
				state.deselect(a);
				state.select(new_u);
			}
		}
	}

	void split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::split_army;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	bool can_split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		return state.world.army_get_controller_from_army_control(a) == source && !state.world.army_get_is_retreating(a) && !state.world.army_get_navy_from_army_transport(a) &&
		!bool(state.world.army_get_battle_from_army_battle_participation(a));
	}
	void execute_split_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		static std::vector<dcon::regiment_id> to_transfer;
		to_transfer.clear();

		for(auto t : state.world.army_get_army_membership(a)) {
			if(t.get_regiment().get_pending_split()) {
				t.get_regiment().set_pending_split(false);
				to_transfer.push_back(t.get_regiment().id);
			}
		}

		if(to_transfer.size() > 0) {
			auto new_u = fatten(state.world, state.world.create_army());
			new_u.set_controller_from_army_control(source);
			new_u.set_location_from_army_location(state.world.army_get_location_from_army_location(a));
			new_u.set_black_flag(state.world.army_get_black_flag(a));

			for(auto t : to_transfer) {
				state.world.regiment_set_army_from_army_membership(t, new_u);
			}

			if(source == state.local_player_nation && state.is_selected(a)) {
				state.select(new_u);
			}

			auto old_regs = state.world.army_get_army_membership(a);
			if(old_regs.begin() == old_regs.end()) {
				state.world.leader_set_army_from_army_leadership(state.world.army_get_general_from_army_leadership(a), new_u);

				if(source == state.local_player_nation) {
					state.deselect(a);
				}
				military::cleanup_army(state, a);
			}
		}
	}

	void split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		payload p{};
		p.type = command_type::split_navy;
		p.source = source;
		p.data.navy_movement.n = a;
		add_to_command_queue(state, p);
	}
	bool can_split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		auto embarked = state.world.navy_get_army_transport(a);
		return state.world.navy_get_controller_from_navy_control(a) == source && !state.world.navy_get_is_retreating(a) &&
		!bool(state.world.navy_get_battle_from_navy_battle_participation(a)) && embarked.begin() == embarked.end();
	}
	void execute_split_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		static std::vector<dcon::ship_id> to_transfer;
		to_transfer.clear();

		for(auto t : state.world.navy_get_navy_membership(a)) {
			if(t.get_ship().get_pending_split()) {
				t.get_ship().set_pending_split(false);
				to_transfer.push_back(t.get_ship().id);
			}
		}

		if(to_transfer.size() > 0) {
			auto new_u = fatten(state.world, state.world.create_navy());
			new_u.set_controller_from_navy_control(source);
			new_u.set_location_from_navy_location(state.world.navy_get_location_from_navy_location(a));

			for(auto t : to_transfer) {
				state.world.ship_set_navy_from_navy_membership(t, new_u);
			}

			if(source == state.local_player_nation && state.is_selected(a))
			state.select(new_u);

			auto old_regs = state.world.navy_get_navy_membership(a);
			if(old_regs.begin() == old_regs.end()) {
				state.world.leader_set_navy_from_navy_leadership(state.world.navy_get_admiral_from_navy_leadership(a), new_u);
				if(source == state.local_player_nation) {
					state.deselect(a);
				}
				military::cleanup_navy(state, a);
			}
		}
	}

	void delete_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		payload p{};
		p.type = command_type::delete_army;
		p.source = source;
		p.data.army_movement.a = a;
		add_to_command_queue(state, p);
	}
	bool can_delete_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		return state.world.army_get_controller_from_army_control(a) == source && !state.world.army_get_is_retreating(a) &&
		!bool(state.world.army_get_battle_from_army_battle_participation(a)) &&
		province::has_naval_access_to_province(state, source, state.world.army_get_location_from_army_location(a));
	}
	void execute_delete_army(sys::state& state, dcon::nation_id source, dcon::army_id a) {
		if(source == state.local_player_nation) {
			state.deselect(a);
		}
		military::cleanup_army(state, a);
	}

	void delete_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		payload p{};
		p.type = command_type::delete_navy;
		p.source = source;
		p.data.navy_movement.n = a;
		add_to_command_queue(state, p);
	}

	bool can_delete_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		auto embarked = state.world.navy_get_army_transport(a);
		return state.world.navy_get_controller_from_navy_control(a) == source && !state.world.navy_get_is_retreating(a) &&
		embarked.begin() == embarked.end() && !bool(state.world.navy_get_battle_from_navy_battle_participation(a)) &&
		province::has_naval_access_to_province(state, source, state.world.navy_get_location_from_navy_location(a));
	}
	void execute_delete_navy(sys::state& state, dcon::nation_id source, dcon::navy_id a) {
		if(source == state.local_player_nation) {
			state.deselect(a);
		}
		military::cleanup_navy(state, a);
	}

	void change_general(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::leader_id l) {
		payload p{};
		p.type = command_type::change_general;
		p.source = source;
		p.data.new_general.a = a;
		p.data.new_general.l = l;
		add_to_command_queue(state, p);
	}
	bool can_change_general(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::leader_id l) {
		return state.world.army_get_controller_from_army_control(a) == source && !state.world.army_get_is_retreating(a) &&
		!bool(state.world.army_get_battle_from_army_battle_participation(a)) &&
		province::has_naval_access_to_province(state, source, state.world.army_get_location_from_army_location(a)) &&
		(!l || state.world.leader_get_nation_from_leader_loyalty(l) == source);
	}
	void execute_change_general(sys::state& state, dcon::nation_id source, dcon::army_id a, dcon::leader_id l) {
		state.world.army_set_general_from_army_leadership(a, l);
	}

	void change_admiral(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::leader_id l) {
		payload p{};
		p.type = command_type::change_admiral;
		p.source = source;
		p.data.new_admiral.a = a;
		p.data.new_admiral.l = l;
		add_to_command_queue(state, p);
	}
	bool can_change_admiral(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::leader_id l) {
		return state.world.navy_get_controller_from_navy_control(a) == source && !state.world.navy_get_is_retreating(a) &&
		!bool(state.world.navy_get_battle_from_navy_battle_participation(a)) &&
		province::has_naval_access_to_province(state, source, state.world.navy_get_location_from_navy_location(a)) &&
		(!l || state.world.leader_get_nation_from_leader_loyalty(l) == source);
	}
	void execute_change_admiral(sys::state& state, dcon::nation_id source, dcon::navy_id a, dcon::leader_id l) {
		state.world.navy_set_admiral_from_navy_leadership(a, l);
	}

	void mark_regiments_to_split(sys::state& state, dcon::nation_id source,
		std::array<dcon::regiment_id, num_packed_units> const& list) {

		payload p{};
		p.type = command_type::designate_split_regiments;
		p.source = source;
		std::copy_n(list.data(), num_packed_units, p.data.split_regiments.regs);
		add_to_command_queue(state, p);
	}
	void execute_mark_regiments_to_split(sys::state& state, dcon::nation_id source, dcon::regiment_id const* regs) {
		for(uint32_t i = 0; i < num_packed_units; ++i) {
			if(regs[i]) {
				if(source ==
					state.world.army_get_controller_from_army_control(state.world.regiment_get_army_from_army_membership(regs[i]))) {
					state.world.regiment_set_pending_split(regs[i], !state.world.regiment_get_pending_split(regs[i]));
				}
			}
		}
	}

	void mark_ships_to_split(sys::state& state, dcon::nation_id source, std::array<dcon::ship_id, num_packed_units> const& list) {
		payload p{};
		p.type = command_type::designate_split_ships;
		p.source = source;
		std::copy_n(list.data(), num_packed_units, p.data.split_ships.ships);
		add_to_command_queue(state, p);

	}
	void execute_mark_ships_to_split(sys::state& state, dcon::nation_id source, dcon::ship_id const* regs) {
		for(uint32_t i = 0; i < num_packed_units; ++i) {
			if(regs[i]) {
				if(source == state.world.navy_get_controller_from_navy_control(state.world.ship_get_navy_from_navy_membership(regs[i]))) {
					state.world.ship_set_pending_split(regs[i], !state.world.ship_get_pending_split(regs[i]));
				}
			}
		}
	}

	void retreat_from_naval_battle(sys::state& state, dcon::nation_id source, dcon::naval_battle_id b) {
		payload p{};
		p.type = command_type::naval_retreat;
		p.source = source;
		p.data.naval_battle.b = b;
		add_to_command_queue(state, p);
	}
	bool can_retreat_from_naval_battle(sys::state& state, dcon::nation_id source, dcon::naval_battle_id b) {
		if(!military::can_retreat_from_battle(state, b))
		return false;
		if(source != military::get_naval_battle_lead_attacker(state, b) && source != military::get_naval_battle_lead_defender(state, b))
		return false;

		return true;
	}
	void execute_retreat_from_naval_battle(sys::state& state, dcon::nation_id source, dcon::naval_battle_id b) {
		if(!military::can_retreat_from_battle(state, b))
		return;

		if(source == military::get_naval_battle_lead_attacker(state, b)) {
			military::end_battle(state, b, military::battle_result::defender_won);
		} else if(source == military::get_naval_battle_lead_defender(state, b)) {
			military::end_battle(state, b, military::battle_result::attacker_won);
		}
	}

	void retreat_from_land_battle(sys::state& state, dcon::nation_id source, dcon::land_battle_id b) {
		payload p{};
		p.type = command_type::land_retreat;
		p.source = source;
		p.data.land_battle.b = b;
		add_to_command_queue(state, p);
	}

	bool can_retreat_from_land_battle(sys::state& state, dcon::nation_id source, dcon::land_battle_id b) {
		if(!military::can_retreat_from_battle(state, b))
		return false;
		if(source != military::get_land_battle_lead_attacker(state, b) && source != military::get_land_battle_lead_defender(state, b))
		return false;

		return true;
	}
	void execute_retreat_from_land_battle(sys::state& state, dcon::nation_id source, dcon::land_battle_id b) {
		if(!military::can_retreat_from_battle(state, b))
		return;

		if(source == military::get_land_battle_lead_attacker(state, b)) {
			military::end_battle(state, b, military::battle_result::defender_won);
		} else if(source == military::get_land_battle_lead_defender(state, b)) {
			military::end_battle(state, b, military::battle_result::attacker_won);
		}
	}

	void invite_to_crisis(sys::state& state, dcon::nation_id source, dcon::nation_id invitation_to, dcon::nation_id target,
		dcon::cb_type_id primary_cb, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag,
		dcon::nation_id cb_secondary_nation) {
		payload p{};
		p.type = command_type::invite_to_crisis;
		p.source = source;
		p.data.crisis_invitation.invited = invitation_to;
		p.data.crisis_invitation.target = target;
		p.data.crisis_invitation.cb_type = primary_cb;
		p.data.crisis_invitation.cb_state = cb_state;
		p.data.crisis_invitation.cb_tag = cb_tag;
		p.data.crisis_invitation.cb_secondary_nation = cb_secondary_nation;
		add_to_command_queue(state, p);
	}
	bool can_invite_to_crisis(sys::state& state, dcon::nation_id source, dcon::nation_id invitation_to, dcon::nation_id target,
		dcon::cb_type_id primary_cb, dcon::state_definition_id cb_state, dcon::national_identity_id cb_tag,
		dcon::nation_id cb_secondary_nation) {

		if(state.world.nation_get_is_player_controlled(source) && state.world.nation_get_diplomatic_points(source) < 1.0f)
		return false;

		if(state.current_crisis_mode != sys::crisis_mode::heating_up)
		return false;
		if(source != state.primary_crisis_attacker && source != state.primary_crisis_defender)
		return false;

		if(invitation_to == target || source == target)
		return false;

		// to must be merely interested participant
		for(auto& par : state.crisis_participants) {
			if(!par.id) {
				return false; // not in crisis
			}
			if(par.id == invitation_to) {
				if(par.merely_interested == false)
				return false; // already in crisis
				break;
			}
		}

		// target must be in crisis
		for(auto& par : state.crisis_participants) {
			if(!par.id) {
				return false; // not in crisis
			}
			if(par.id == target) {
				if(par.merely_interested)
				return false;
				if(par.supports_attacker && source == state.primary_crisis_attacker)
				return false;
				if(!par.supports_attacker && source == state.primary_crisis_defender)
				return false;

				break;
			}
		}

		auto cb_type = state.world.cb_type_get_type_bits(primary_cb);
		if((cb_type & military::cb_flag::always) == 0 && (cb_type & military::cb_flag::is_not_constructing_cb) != 0)
		return false;

		if(!military::cb_instance_conditions_satisfied(state, invitation_to, target, primary_cb, cb_state, cb_tag, cb_secondary_nation)) {
			return false;
		}

		return true;
	}
	void execute_invite_to_crisis(sys::state& state, dcon::nation_id source, crisis_invitation_data const& data) {
		if(state.world.nation_get_is_player_controlled(source) && state.world.nation_get_diplomatic_points(source) < 1.0f)
		return;

		state.world.nation_get_diplomatic_points(source) -= 1.0f;

		diplomatic_message::message m{};
		m.to = data.invited;
		m.from = source;
		m.data.crisis_offer.target = data.target;
		m.data.crisis_offer.wargoal_secondary_nation = data.cb_secondary_nation;
		m.data.crisis_offer.wargoal_state = data.cb_state;
		m.data.crisis_offer.wargoal_tag = data.cb_tag;
		m.data.crisis_offer.wargoal_type = data.cb_type;

		m.type = diplomatic_message::type::take_crisis_side_offer;

		diplomatic_message::post(state, m);
	}

	void toggle_mobilization(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::toggle_mobilization;
		p.source = source;
		add_to_command_queue(state, p);
	}

	void execute_toggle_mobilization(sys::state& state, dcon::nation_id source) {
		if(state.world.nation_get_is_mobilized(source)) {
			military::end_mobilization(state, source);
		} else {
			military::start_mobilization(state, source);
		}
	}

	void toggle_auto_create_generals(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::toggle_auto_create_generals;
		p.source = source;
		add_to_command_queue(state, p);
	}

	void execute_toggle_auto_create_generals(sys::state& state, dcon::nation_id source) {
		state.world.nation_set_auto_create_admirals(source, !state.world.nation_get_auto_create_admirals(source));
	}

	void toggle_auto_assign_leaders(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::toggle_auto_assign_leaders;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_toggle_auto_assign_leaders(sys::state& state, dcon::nation_id source) {
		state.world.nation_set_auto_assign_leaders(source, !state.world.nation_get_auto_assign_leaders(source));
	}

	void toggle_auto_assign_single_leader(sys::state& state, dcon::nation_id source, dcon::leader_id l) {
		payload p{};
		p.type = command_type::toggle_auto_assign_single_leader;
		p.source = source;
		p.data.leader.l = l;
		add_to_command_queue(state, p);
	}
	void execute_toggle_auto_assign_single_leader(sys::state& state, dcon::nation_id source, dcon::leader_id l) {
		state.world.leader_set_auto_assign(l, !state.world.leader_get_auto_assign(l));
	}

	void enable_debt(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::enable_debt;
		p.source = source;
		add_to_command_queue(state, p);
	}

	void execute_enable_debt(sys::state& state, dcon::nation_id source) {
		state.world.nation_set_is_debt_spending(source, !state.world.nation_get_is_debt_spending(source));
	}

	void use_province_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::province_id i) {
		payload p{};
		p.type = command_type::pbutton_script;
		p.source = source;
		p.data.pbutton.button = d;
		p.data.pbutton.id = i;
		add_to_command_queue(state, p);
	}
	bool can_use_province_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::province_id p) {
		auto& def = state.ui_defs.gui[d];
		if(def.get_element_type() != ui::element_type::button)
		return false;
		if(def.data.button.get_button_scripting() != ui::button_scripting::province)
		return false;
		if(!def.data.button.scriptable_enable)
		return true;
		return trigger::evaluate(state, def.data.button.scriptable_enable, trigger::to_generic(p), trigger::to_generic(p), trigger::to_generic(source));
	}
	void execute_use_province_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::province_id p) {
		auto & def = state.ui_defs.gui[d];
		if(def.data.button.scriptable_effect)
		effect::execute(state, def.data.button.scriptable_effect, trigger::to_generic(p), trigger::to_generic(p), trigger::to_generic(source), uint32_t(state.current_date.value), uint32_t(p.index() ^ (d.index() << 4)));
	}

	void use_nation_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::nation_id n) {
		payload p{};
		p.type = command_type::nbutton_script;
		p.source = source;
		p.data.nbutton.button = d;
		p.data.nbutton.id = n;
		add_to_command_queue(state, p);
	}
	bool can_use_nation_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::nation_id n) {
		auto& def = state.ui_defs.gui[d];
		if(def.get_element_type() != ui::element_type::button)
		return false;
		if(def.data.button.get_button_scripting() != ui::button_scripting::nation)
		return false;
		if(!def.data.button.scriptable_enable)
		return true;
		return trigger::evaluate(state, def.data.button.scriptable_enable, trigger::to_generic(n), trigger::to_generic(n), trigger::to_generic(source));
	}
	void execute_use_nation_button(sys::state& state, dcon::nation_id source, dcon::gui_def_id d, dcon::nation_id n) {
		auto& def = state.ui_defs.gui[d];
		if(def.data.button.scriptable_effect)
		effect::execute(state, def.data.button.scriptable_effect, trigger::to_generic(n), trigger::to_generic(n), trigger::to_generic(source), uint32_t(state.current_date.value), uint32_t(n.index() ^ (d.index() << 4)));
	}

	void post_chat_message(sys::state& state, ui::chat_message& m) {
		// Private message
		bool can_see = true;
		if(bool(m.target)) {
			can_see = state.local_player_nation == m.source || state.local_player_nation == m.target;
		}
		if(can_see) {
			state.ui_state.chat_messages[state.ui_state.chat_messages_index++] = m;
			if(state.ui_state.chat_messages_index >= state.ui_state.chat_messages.size())
			state.ui_state.chat_messages_index = 0;
			notification::post(state, notification::message{
				[m](sys::state& state, text::layout_base& contents) {
					text::add_line(state, contents, "msg_chat_message_1", text::variable_type::x, m.source);
					text::add_line(state, contents, "msg_chat_message_2", text::variable_type::x, m.body);
				},
				"msg_chat_message_title",
			m.source, dcon::nation_id{}, dcon::nation_id{},
				sys::message_base_type::chat_message
			});
		}
	}

	void chat_message(sys::state& state, dcon::nation_id source, std::string_view body, dcon::nation_id target) {
		payload p{};
		p.type = command_type::chat_message;
		p.source = source;
		p.data.chat_message.target = target;
		std::memcpy(p.data.chat_message.body, std::string(body).c_str(), std::min<size_t>(body.length() + 1, size_t(ui::max_chat_message_len)));
		p.data.chat_message.body[ui::max_chat_message_len - 1] = '\0';
		add_to_command_queue(state, p);
	}
	bool can_chat_message(sys::state& state, dcon::nation_id source, std::string_view body, dcon::nation_id target) {
		// TODO: bans, kicks, mutes?
		return true;
	}
	void execute_chat_message(sys::state& state, dcon::nation_id source, std::string_view body, dcon::nation_id target) {
	ui::chat_message m{};
		m.source = source;
		m.target = target;
		m.body = std::string(body);
		post_chat_message(state, m);
	}

	void notify_player_joins(sys::state& state, dcon::nation_id source, sys::player_name& name) {
		payload p{};
		p.type = command_type::notify_player_joins;
		p.source = source;
		p.data.player_name = name;
		add_to_command_queue(state, p);
	}
	bool can_notify_player_joins(sys::state& state, dcon::nation_id source, sys::player_name& name) {
		// TODO: bans, kicks, mutes?
		return true;
	}
	void execute_notify_player_joins(sys::state& state, dcon::nation_id source, sys::player_name& name) {
		state.world.nation_set_is_player_controlled(source, true);
		state.network_state.map_of_player_names.insert_or_assign(source.index(), name);
		/* Hotjoin */
		if(state.current_scene.game_in_progress)
			ai::remove_ai_data(state, source);

		ui::chat_message m{};
		m.source = source;
		text::substitution_map sub{};
		text::add_to_substitution_map(sub, text::variable_type::playername, name.to_string_view());
		m.body = text::resolve_string_substitution(state, "chat_player_joins", sub);
		post_chat_message(state, m);
	}

	void notify_player_leaves(sys::state& state, dcon::nation_id source, bool make_ai) {
		payload p{};
		p.type = command_type::notify_player_leaves;
		p.source = source;
		p.data.notify_leave.make_ai = make_ai;
		add_to_command_queue(state, p);
	}
	bool can_notify_player_leaves(sys::state& state, dcon::nation_id source, bool make_ai) {
		return state.world.nation_get_is_player_controlled(source);
	}
	void execute_notify_player_leaves(sys::state& state, dcon::nation_id source, bool make_ai) {
		if(make_ai) {
			state.world.nation_set_is_player_controlled(source, false);
		}

		ui::chat_message m{};
		m.source = source;
		text::substitution_map sub{};
		text::add_to_substitution_map(sub, text::variable_type::playername, state.network_state.map_of_player_names[source.index()].to_string_view());
		m.body = text::resolve_string_substitution(state, "chat_player_leaves", sub);
		post_chat_message(state, m);
	}

	void notify_player_ban(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::notify_player_ban;
		p.source = source;
		p.data.nation_pick.target = target;
		add_to_command_queue(state, p);
	}
	bool can_notify_player_ban(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target) // can't perform on self
			return false;
		return true;
	}
	void execute_notify_player_ban(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(state.network_mode == sys::network_mode_type::host) {
			for(auto& client : state.network_state.clients) {
				if(client.is_active() && client.playing_as == target) {
					network::ban_player(state, client);
				}
			}
		}
		state.world.nation_set_is_player_controlled(target, false);

		ui::chat_message m{};
		m.source = source;
		text::substitution_map sub{};
		text::add_to_substitution_map(sub, text::variable_type::playername, state.network_state.map_of_player_names[target.index()].to_string_view());
		m.body = text::resolve_string_substitution(state, "chat_player_ban", sub);
		post_chat_message(state, m);
	}

	void notify_player_kick(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::notify_player_kick;
		p.source = source;
		p.data.nation_pick.target = target;
		add_to_command_queue(state, p);
	}
	bool can_notify_player_kick(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target) // can't perform on self
			return false;
		return true;
	}
	void execute_notify_player_kick(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(state.network_mode == sys::network_mode_type::host) {
			for(auto& client : state.network_state.clients) {
				if(client.is_active() && client.playing_as == target) {
					network::kick_player(state, client);
				}
			}
		}
		state.world.nation_set_is_player_controlled(target, false);

		ui::chat_message m{};
		m.source = source;
		text::substitution_map sub{};
		text::add_to_substitution_map(sub, text::variable_type::playername, state.network_state.map_of_player_names[target.index()].to_string_view());
		m.body = text::resolve_string_substitution(state, "chat_player_kick", sub);
		post_chat_message(state, m);
	}

	void notify_player_picks_nation(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		payload p{};
		p.type = command_type::notify_player_picks_nation;
		p.source = source;
		p.data.nation_pick.target = target;
		add_to_command_queue(state, p);
	}
	bool can_notify_player_picks_nation(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		if(source == target) //redundant
			return false;
		if(!bool(target) || target == state.world.national_identity_get_nation_from_identity_holder(state.national_definitions.rebel_id)) //Invalid OR rebel nation
			return false;
		// TODO: Support Co-op (one day)
		return state.world.nation_get_is_player_controlled(target) == false;
	}
	void execute_notify_player_picks_nation(sys::state& state, dcon::nation_id source, dcon::nation_id target) {
		assert(source && source != state.world.national_identity_get_nation_from_identity_holder(state.national_definitions.rebel_id));
		network::switch_player(state, target, source);
		state.world.nation_set_is_player_controlled(source, false);
		state.world.nation_set_is_player_controlled(target, true);

		if(state.local_player_nation == source) {
			state.local_player_nation = target;
		}
		// We will also re-assign all chat messages from this nation to the new one
		for(auto& msg : state.ui_state.chat_messages)
			if(bool(msg.source) && msg.source == source)
				msg.source = target;

		// Update map
		state.map_state.unhandled_province_selection = true;
	}

	void notify_player_oos(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command_type::notify_player_oos;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_notify_player_oos(sys::state& state, dcon::nation_id source) {
		state.actual_game_speed = 0; //pause host immediately
		state.debug_save_oos_dump();

		ui::chat_message m{};
		m.source = source;
		text::substitution_map sub{};
		text::add_to_substitution_map(sub, text::variable_type::playername, state.network_state.map_of_player_names[source.index()].to_string_view());
		m.body = text::resolve_string_substitution(state, "chat_player_oos", sub);
		post_chat_message(state, m);
	}

	void notify_advanced_tick(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_advanced_tick;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_notify_advanced_tick(sys::state& state, dcon::nation_id source) {
		if(state.network_mode == sys::network_mode_type::host) {
			for(auto& client : state.network_state.clients) {
				if(client.is_active() && client.playing_as == source) {
					client.last_game_date += 1;
				}
			}
		}
	}

	void advance_tick(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::advance_tick;
		p.source = source;
		// Postponed until it is sent!
		//p.data.advance_tick.checksum = state.get_save_checksum();
		p.data.advance_tick.speed = state.actual_game_speed.load(std::memory_order::acquire);
		add_to_command_queue(state, p);
	}

	void execute_advance_tick(sys::state& state, dcon::nation_id source, sys::checksum_key& k, int32_t speed) {
		if(state.network_mode == sys::network_mode_type::client) {
			if(!state.network_state.out_of_sync) {
				if(state.current_date.to_ymd(state.start_date).day == 1 || state.cheat_data.daily_oos_check) {
					sys::checksum_key current = state.get_save_checksum();
					if(!current.is_equal(k)) {
						state.network_state.out_of_sync = true;
						state.debug_save_oos_dump();
					}
				}
			}
			state.actual_game_speed = speed;
			/* Notify server that we advnaced a tick */
			command::notify_advanced_tick(state, state.local_player_nation);
		}
		state.single_game_tick();
	}

	void notify_save_loaded(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_save_loaded;
		p.source = source;
		p.data.notify_save_loaded.target = dcon::nation_id{};
		add_to_command_queue(state, p);
	}

	void execute_notify_save_loaded(sys::state& state, dcon::nation_id source, sys::checksum_key& k) {
		state.session_host_checksum = k;
		/* Reset OOS state, and for host, advise new clients with a save stream so they can hotjoin!
			Additionally we will clear the new client sending queue, since the state is no longer
			"replayable" without heavy bandwidth costs */
		state.network_state.is_new_game = false;
		state.network_state.out_of_sync = false;
		state.network_state.reported_oos = false;

		ui::chat_message m;
		m.source = source;
		m.body = text::produce_simple_string(state, "save_transfer_begin");
		post_chat_message(state, m);
	}

	void notify_reload(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_reload;
		p.source = source;
		add_to_command_queue(state, p);
	}
	void execute_notify_reload(sys::state& state, dcon::nation_id source, sys::checksum_key& k) {
		state.network_state.save_slock.store(true, std::memory_order::release);

		state.session_host_checksum = k;
		/* Reset OOS state, and for host, advise new clients with a save stream so they can hotjoin!
			Additionally we will clear the new client sending queue, since the state is no longer
			"replayable" without heavy bandwidth costs */
		state.network_state.is_new_game = false;
		state.network_state.out_of_sync = false;
		state.network_state.reported_oos = false;

		std::vector<dcon::nation_id> players;
		for(const auto n : state.world.in_nation)
			if(state.world.nation_get_is_player_controlled(n))
				players.push_back(n);
		dcon::nation_id old_local_player_nation = state.local_player_nation;
		state.local_player_nation = dcon::nation_id{ };
		/* Save the buffer before we fill the unsaved data */
		size_t length = sizeof_save_section(state);
		auto save_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[length]);
		sys::write_save_section(save_buffer.get(), state);
		/* Then reload as if we loaded the save data */
		state.preload();
		sys::read_save_section(save_buffer.get(), save_buffer.get() + length, state);
		for(const auto n : players)
			state.world.nation_set_is_player_controlled(n, true);
		state.local_player_nation = old_local_player_nation;
		assert(state.world.nation_get_is_player_controlled(state.local_player_nation));
		state.fill_unsaved_data();
		assert(state.network_state.save_slock.load(std::memory_order::acquire) == true);
		state.network_state.save_slock.store(false, std::memory_order::release);
		//
		assert(state.session_host_checksum.is_equal(state.get_save_checksum()));

		ui::chat_message m;
		m.source = source;
		m.body = text::produce_simple_string(state, "multiplayer_notify_reload");
		post_chat_message(state, m);
	}

	void execute_notify_start_game(sys::state& state, dcon::nation_id source) {
		assert(state.world.nation_get_is_player_controlled(state.local_player_nation));
		state.selected_armies.clear();
		state.selected_navies.clear();
		for(auto& v : state.ctrl_armies) {
			v.clear();
		}
		for(auto& v : state.ctrl_navies) {
			v.clear();
		}
		/* And clear the save stuff */
		state.network_state.current_save_buffer.reset();
		state.network_state.current_save_length = 0;

		/* Clear AI data */
		for(const auto n : state.world.in_nation) {
			if(state.world.nation_get_is_player_controlled(n)) {
				ai::remove_ai_data(state, n);
			}
		}
		ai::take_ai_decisions(state);
		//economy::daily_update(state);

		game_scene::switch_scene(state, game_scene::scene_id::in_game_basic);
		state.map_state.set_selected_province(dcon::province_id{});
		state.map_state.unhandled_province_selection = true;
	}

	void notify_start_game(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_start_game;
		p.source = source;
		add_to_command_queue(state, p);
	}

	void execute_notify_stop_game(sys::state& state, dcon::nation_id source) {
		game_scene::switch_scene(state, game_scene::scene_id::pick_nation);
		state.map_state.set_selected_province(dcon::province_id{});
		state.map_state.unhandled_province_selection = true;
	}

	void notify_stop_game(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_stop_game;
		p.source = source;
		add_to_command_queue(state, p);
	}

	void execute_notify_pause_game(sys::state& state, dcon::nation_id source) {
		if(state.actual_game_speed <= 0) {
			state.actual_game_speed = state.ui_state.held_game_speed;
		} else {
			state.ui_state.held_game_speed = state.actual_game_speed.load();
			state.actual_game_speed = 0;
		}
		state.last_nation_that_paused = source;
	}

	void notify_pause_game(sys::state& state, dcon::nation_id source) {
		payload p{};
		p.type = command::command_type::notify_pause_game;
		p.source = source;
		add_to_command_queue(state, p);
	}

	bool can_perform_command(sys::state& state, payload& c) {
		switch(c.type) {
		case command_type::change_nat_focus:
			return can_set_national_focus(state, c.source, c.data.nat_focus.target_state, c.data.nat_focus.focus);

		case command_type::start_research:
			return can_start_research(state, c.source, c.data.start_research.tech);

		case command_type::make_leader:
			return can_make_leader(state, c.source, c.data.make_leader.is_general);

		case command_type::begin_province_building_construction:
			return can_begin_province_building_construction(state, c.source, c.data.start_province_building.location,
				c.data.start_province_building.type);

		case command_type::war_subsidies:
			return can_give_war_subsidies(state, c.source, c.data.diplo_action.target);

		case command_type::cancel_war_subsidies:
			return can_cancel_war_subsidies(state, c.source, c.data.diplo_action.target);

		case command_type::increase_relations:
			return can_increase_relations(state, c.source, c.data.diplo_action.target);

		case command_type::decrease_relations:
			return can_decrease_relations(state, c.source, c.data.diplo_action.target);

		case command_type::begin_factory_building_construction:
			return can_begin_factory_building_construction(state, c.source, c.data.start_factory_building.location,
				c.data.start_factory_building.type, c.data.start_factory_building.is_upgrade);

		case command_type::begin_naval_unit_construction:
			return can_start_naval_unit_construction(state, c.source, c.data.naval_unit_construction.location,
				c.data.naval_unit_construction.type, c.data.naval_unit_construction.template_province);

		case command_type::cancel_naval_unit_construction:
			return can_cancel_naval_unit_construction(state, c.source, c.data.naval_unit_construction.location,
				c.data.naval_unit_construction.type);

		case command_type::begin_land_unit_construction:
			return can_start_land_unit_construction(state, c.source, c.data.land_unit_construction.location,
				c.data.land_unit_construction.pop_culture, c.data.land_unit_construction.type, c.data.land_unit_construction.template_province);

		case command_type::cancel_land_unit_construction:
			return can_cancel_land_unit_construction(state, c.source, c.data.land_unit_construction.location,
				c.data.land_unit_construction.pop_culture, c.data.land_unit_construction.type);

		case command_type::delete_factory:
			return true; //can_delete_factory(state, c.source, c.data.factory.location, c.data.factory.type);

		case command_type::change_factory_settings:
			return true; //can_change_factory_settings(state, c.source, c.data.factory.location, c.data.factory.type, c.data.factory.priority, c.data.factory.subsidize);

		case command_type::make_vassal:
			return can_make_vassal(state, c.source, c.data.tag_target.ident);

		case command_type::release_and_play_nation:
			return can_release_and_play_as(state, c.source, c.data.tag_target.ident);

		case command_type::change_budget:
			return can_change_budget_settings(state, c.source, c.data.budget_data);

		case command_type::start_election:
			return can_start_election(state, c.source);

		case command_type::change_influence_priority:
			return can_change_influence_priority(state, c.source, c.data.influence_priority.influence_target,
				c.data.influence_priority.priority);

		case command_type::expel_advisors:
			return can_expel_advisors(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);

		case command_type::ban_embassy:
			return can_ban_embassy(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);

		case command_type::discredit_advisors:
			return can_discredit_advisors(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);

		case command_type::decrease_opinion:
			return can_decrease_opinion(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);

		case command_type::remove_from_sphere:
			return can_remove_from_sphere(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);

		case command_type::increase_opinion:
			return can_increase_opinion(state, c.source, c.data.influence_action.influence_target);

		case command_type::add_to_sphere:
			return can_add_to_sphere(state, c.source, c.data.influence_action.influence_target);

		case command_type::upgrade_colony_to_state:
			return can_upgrade_colony_to_state(state, c.source, state.world.province_get_state_membership(c.data.generic_location.prov));

		case command_type::invest_in_colony:
			return can_invest_in_colony(state, c.source, c.data.generic_location.prov);

		case command_type::abandon_colony:
			return can_abandon_colony(state, c.source, c.data.generic_location.prov);

		case command_type::finish_colonization:
			return can_finish_colonization(state, c.source, c.data.generic_location.prov);

		case command_type::intervene_in_war:
			return can_intervene_in_war(state, c.source, c.data.war_target.war, c.data.war_target.for_attacker);

		case command_type::suppress_movement:
			return true; //can_suppress_movement(state, c.source, c.data.movement.iopt);

		case command_type::civilize_nation:
			return can_civilize_nation(state, c.source);

		case command_type::appoint_ruling_party:
			return can_appoint_ruling_party(state, c.source, c.data.political_party.p);

		case command_type::change_issue_option:
			return can_enact_issue(state, c.source, c.data.issue_selection.r);

		case command_type::change_reform_option:
			return can_enact_reform(state, c.source, c.data.reform_selection.r);

		case command_type::become_interested_in_crisis:
			return can_become_interested_in_crisis(state, c.source);

		case command_type::take_sides_in_crisis:
			return can_take_sides_in_crisis(state, c.source, c.data.crisis_join.join_attackers);

		case command_type::change_stockpile_settings:
			return can_change_stockpile_settings(state, c.source, c.data.stockpile_settings.c, c.data.stockpile_settings.amount,
				c.data.stockpile_settings.draw_on_stockpiles);

		case command_type::take_decision:
			return can_take_decision(state, c.source, c.data.decision.d);

		case command_type::make_n_event_choice:
			return true; //can_make_event_choice(state, c.source, c.data.pending_human_n_event);

		case command_type::make_f_n_event_choice:
			return true; // can_make_event_choice(state, c.source, c.data.pending_human_f_n_event);

		case command_type::make_p_event_choice:
			return true; // can_make_event_choice(state, c.source, c.data.pending_human_p_event);

		case command_type::make_f_p_event_choice:
			return true; // can_make_event_choice(state, c.source, c.data.pending_human_f_p_event);

		case command_type::cancel_cb_fabrication:
			return can_cancel_cb_fabrication(state, c.source);

		case command_type::fabricate_cb:
			return can_fabricate_cb(state, c.source, c.data.cb_fabrication.target, c.data.cb_fabrication.type);

		case command_type::ask_for_military_access:
			return can_ask_for_access(state, c.source, c.data.diplo_action.target);

		case command_type::ask_for_alliance:
			return can_ask_for_alliance(state, c.source, c.data.diplo_action.target);

		case command_type::call_to_arms:
			return can_call_to_arms(state, c.source, c.data.call_to_arms.target, c.data.call_to_arms.war);

		case command_type::respond_to_diplomatic_message:
			return true; //can_respond_to_diplomatic_message(state, c.source, c.data.message.from, c.data.message.type, c.data.message.accept);

		case command_type::cancel_military_access:
			return can_cancel_military_access(state, c.source, c.data.diplo_action.target);

		case command_type::cancel_alliance:
			return can_cancel_alliance(state, c.source, c.data.diplo_action.target);

		case command_type::cancel_given_military_access:
			return can_cancel_given_military_access(state, c.source, c.data.diplo_action.target);

		case command_type::declare_war:
			return can_declare_war(state, c.source, c.data.new_war.target, c.data.new_war.primary_cb, c.data.new_war.cb_state,
				c.data.new_war.cb_tag, c.data.new_war.cb_secondary_nation);

		case command_type::add_war_goal:
			return can_add_war_goal(state, c.source, c.data.new_war_goal.war, c.data.new_war_goal.target, c.data.new_war_goal.cb_type,
				c.data.new_war_goal.cb_state, c.data.new_war_goal.cb_tag, c.data.new_war_goal.cb_secondary_nation);

		case command_type::start_peace_offer:
			return can_start_peace_offer(state, c.source, c.data.new_offer.target, c.data.new_offer.war,
				c.data.new_offer.is_concession);

		case command_type::add_peace_offer_term:
			return can_add_to_peace_offer(state, c.source, c.data.offer_wargoal.wg);

		case command_type::send_peace_offer:
			return can_send_peace_offer(state, c.source);

		case command_type::move_army:
			return can_move_army(state, c.source, c.data.army_movement.a, c.data.army_movement.dest).size() != 0;

		case command_type::move_navy:
			return can_move_navy(state, c.source, c.data.navy_movement.n, c.data.navy_movement.dest).size() != 0;

		case command_type::embark_army:
			return can_embark_army(state, c.source, c.data.army_movement.a);

		case command_type::merge_armies:
			return can_merge_armies(state, c.source, c.data.merge_army.a, c.data.merge_army.b);

		case command_type::merge_navies:
			return can_merge_navies(state, c.source, c.data.merge_navy.a, c.data.merge_navy.b);

		case command_type::split_army:
			return can_split_army(state, c.source, c.data.army_movement.a);

		case command_type::split_navy:
			return can_split_navy(state, c.source, c.data.navy_movement.n);

		case command_type::delete_army:
			return can_delete_army(state, c.source, c.data.army_movement.a);

		case command_type::delete_navy:
			return can_delete_navy(state, c.source, c.data.navy_movement.n);

		case command_type::designate_split_regiments:
			return true; //can_mark_regiments_to_split(state, c.source, c.data.split_regiments.regs);

		case command_type::designate_split_ships:
			return true; //can_mark_ships_to_split(state, c.source, c.data.split_ships.ships);

		case command_type::naval_retreat:
			return can_retreat_from_naval_battle(state, c.source, c.data.naval_battle.b);

		case command_type::land_retreat:
			return can_retreat_from_land_battle(state, c.source, c.data.land_battle.b);

		case command_type::start_crisis_peace_offer:
			return can_start_crisis_peace_offer(state, c.source, c.data.new_offer.is_concession);

		case command_type::invite_to_crisis:
			return true; // can_invite_to_crisis(state, c.source, c.data.crisis_invitation);

		case command_type::add_wargoal_to_crisis_offer:
			return true; // can_add_to_crisis_peace_offer(state, c.source, c.data.crisis_invitation);

		case command_type::send_crisis_peace_offer:
			return can_send_crisis_peace_offer(state, c.source);

		case command_type::change_admiral:
			return can_change_admiral(state, c.source, c.data.new_admiral.a, c.data.new_admiral.l);

		case command_type::change_general:
			return can_change_general(state, c.source, c.data.new_general.a, c.data.new_general.l);

		case command_type::toggle_mobilization:
			return true; //can_toggle_mobilization(state, c.source);
		case command_type::toggle_auto_create_generals:
			return true;
		case command_type::toggle_auto_assign_leaders:
			return true;
		case command_type::toggle_auto_assign_single_leader:
			return true;
		case command_type::give_military_access:
			return can_give_military_access(state, c.source, c.data.diplo_action.target);

		case command_type::set_rally_point:
			return true; //can_set_rally_point(state, c.source, c.data.rally_point.location, c.data.rally_point.naval, c.data.rally_point.enable);

		case command_type::save_game:
			return true; //can_save_game(state, c.source, c.data.save_game.and_quit);

		case command_type::cancel_factory_building_construction:
			return can_cancel_factory_building_construction(state, c.source, c.data.start_factory_building.location, c.data.start_factory_building.type);

		case command_type::disband_undermanned:
			return can_disband_undermanned_regiments(state, c.source, c.data.army_movement.a);

		case command_type::even_split_army:
			return can_evenly_split_army(state, c.source, c.data.army_movement.a);

		case command_type::even_split_navy:
			return can_evenly_split_navy(state, c.source, c.data.navy_movement.n);

		case command_type::toggle_hunt_rebels:
			return true; //can_toggle_rebel_hunting(state, c.source, c.data.army_movement.a);

		case command_type::state_transfer:
			return can_state_transfer(state, c.source, c.data.state_transfer.target, c.data.state_transfer.state);

		case command_type::enable_debt:
			return true;
		case command_type::toggle_unit_ai_control:
			return true;
		case command_type::toggle_mobilized_is_ai_controlled:
			return true;
		case command_type::pbutton_script:
			return can_use_province_button(state, c.source, c.data.pbutton.button, c.data.pbutton.id);
		case command_type::nbutton_script:
			return can_use_nation_button(state, c.source, c.data.nbutton.button, c.data.nbutton.id);

			// common mp commands
		case command_type::chat_message:
		{
			size_t count = 0;
			for(count = 0; count < sizeof(c.data.chat_message.body); count++)
				if(c.data.chat_message.body[count] == '\0')

					std::string_view sv(c.data.chat_message.body, c.data.chat_message.body + count);
			return can_chat_message(state, c.source, c.data.chat_message.body, c.data.chat_message.target);

		}
		case command_type::notify_player_ban:
			return can_notify_player_ban(state, c.source, c.data.nation_pick.target);

		case command_type::notify_player_kick:
			return can_notify_player_kick(state, c.source, c.data.nation_pick.target);

		case command_type::notify_player_joins:
			return can_notify_player_joins(state, c.source, c.data.player_name);

		case command_type::notify_player_leaves:
			return can_notify_player_leaves(state, c.source, c.data.notify_leave.make_ai);

		case command_type::notify_player_picks_nation:
			return can_notify_player_picks_nation(state, c.source, c.data.nation_pick.target);

		case command_type::notify_player_oos:
			return true; //return can_notify_player_oos(state, c.source);
		case command_type::notify_advanced_tick:
			return true;
		case command_type::advance_tick:
			return true; //return can_advance_tick(state, c.source, c.data.advance_tick.checksum, c.data.advance_tick.speed);
		case command_type::notify_save_loaded:
			return true; //return can_notify_save_loaded(state, c.source, c.data.notify_save_loaded.seed, c.data.notify_save_loaded.checksum);
		case command_type::notify_reload:
			return true;
		case command_type::notify_start_game:
			return true; //return can_notify_start_game(state, c.source);
		case command_type::notify_stop_game:
			return true; //return can_notify_stop_game(state, c.source);
		case command_type::notify_pause_game:
			return true; //return can_notify_pause_game(state, c.source);
		case command_type::release_subject:
			return can_release_subject(state, c.source, c.data.diplo_action.target);

			// console commands
		case command_type::c_switch_nation:
			return can_c_switch_nation(state, c.source, c.data.tag_target.ident);

		case command_type::c_change_diplo_points:
		case command_type::c_change_money:
		case command_type::c_westernize:
		case command_type::c_unwesternize:
		case command_type::c_change_controller:
		case command_type::c_change_owner:
		case command_type::c_change_research_points:
		case command_type::c_change_cb_progress:
		case command_type::c_change_infamy:
		case command_type::c_force_crisis:
		case command_type::c_change_national_militancy:
		case command_type::c_change_prestige:
		case command_type::c_end_game:
		case command_type::c_event:
		case command_type::c_event_as:
		case command_type::c_force_ally:
		case command_type::c_toggle_ai:
		case command_type::c_complete_constructions:
		case command_type::c_instant_research:
		case command_type::c_add_population:
		case command_type::c_instant_army:
		case command_type::c_instant_navy:
		case command_type::c_instant_industry:
		case command_type::c_innovate:
		case command_type::c_toggle_core:
		case command_type::c_always_accept_deals:
		case command_type::c_always_allow_reforms:
		case command_type::c_always_allow_wargoals:
		case command_type::c_set_auto_choice_all:
		case command_type::c_clear_auto_choice_all:
		case command_type::c_always_allow_decisions:
		case command_type::c_always_potential_decisions:
		case command_type::c_add_year:
			return true;
			//invalid commands
		case command_type::invalid:
		default:
			assert(false); // invalid command
			break;
		}
		return false;
	}

	void execute_command(sys::state& state, payload& c) {
		if(!can_perform_command(state, c))
			return;
		switch(c.type) {
		case command_type::invalid:
			// invalid command
			break;
		case command_type::change_nat_focus:
			execute_set_national_focus(state, c.source, c.data.nat_focus.target_state, c.data.nat_focus.focus);
			break;
		case command_type::start_research:
			execute_start_research(state, c.source, c.data.start_research.tech);
			break;
		case command_type::make_leader:
			execute_make_leader(state, c.source, c.data.make_leader.is_general);
			break;
		case command_type::begin_province_building_construction:
			execute_begin_province_building_construction(state, c.source, c.data.start_province_building.location,
				c.data.start_province_building.type);
			break;
		case command_type::war_subsidies:
			execute_give_war_subsidies(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::cancel_war_subsidies:
			execute_cancel_war_subsidies(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::increase_relations:
			execute_increase_relations(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::decrease_relations:
			execute_decrease_relations(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::begin_factory_building_construction:
			execute_begin_factory_building_construction(state, c.source, c.data.start_factory_building.location,
				c.data.start_factory_building.type, c.data.start_factory_building.is_upgrade);
			break;
		case command_type::begin_naval_unit_construction:
			execute_start_naval_unit_construction(state, c.source, c.data.naval_unit_construction.location,
				c.data.naval_unit_construction.type, c.data.naval_unit_construction.template_province);
			break;
		case command_type::cancel_naval_unit_construction:
			execute_cancel_naval_unit_construction(state, c.source, c.data.naval_unit_construction.location,
				c.data.naval_unit_construction.type);
			break;
		case command_type::begin_land_unit_construction:
			execute_start_land_unit_construction(state, c.source, c.data.land_unit_construction.location,
				c.data.land_unit_construction.pop_culture, c.data.land_unit_construction.type, c.data.land_unit_construction.template_province);
			break;
		case command_type::cancel_land_unit_construction:
			execute_cancel_land_unit_construction(state, c.source, c.data.land_unit_construction.location,
				c.data.land_unit_construction.pop_culture, c.data.land_unit_construction.type);
			break;
		case command_type::delete_factory:
			execute_delete_factory(state, c.source, c.data.factory.location, c.data.factory.type);
			break;
		case command_type::change_factory_settings:
			execute_change_factory_settings(state, c.source, c.data.factory.location, c.data.factory.type, c.data.factory.priority,
				c.data.factory.subsidize);
			break;
		case command_type::make_vassal:
			execute_make_vassal(state, c.source, c.data.tag_target.ident);
			break;
		case command_type::release_and_play_nation:
			execute_release_and_play_as(state, c.source, c.data.tag_target.ident);
			break;
		case command_type::change_budget:
			execute_change_budget_settings(state, c.source, c.data.budget_data);
			break;
		case command_type::start_election:
			execute_start_election(state, c.source);
			break;
		case command_type::change_influence_priority:
			execute_change_influence_priority(state, c.source, c.data.influence_priority.influence_target,
				c.data.influence_priority.priority);
			break;
		case command_type::expel_advisors:
			execute_expel_advisors(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);
			break;
		case command_type::ban_embassy:
			execute_ban_embassy(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);
			break;
		case command_type::discredit_advisors:
			execute_discredit_advisors(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);
			break;
		case command_type::decrease_opinion:
			execute_decrease_opinion(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);
			break;
		case command_type::remove_from_sphere:
			execute_remove_from_sphere(state, c.source, c.data.influence_action.influence_target, c.data.influence_action.gp_target);
			break;
		case command_type::increase_opinion:
			execute_increase_opinion(state, c.source, c.data.influence_action.influence_target);
			break;
		case command_type::add_to_sphere:
			execute_add_to_sphere(state, c.source, c.data.influence_action.influence_target);
			break;
		case command_type::upgrade_colony_to_state:
			execute_upgrade_colony_to_state(state, c.source, state.world.province_get_state_membership(c.data.generic_location.prov));
			break;
		case command_type::invest_in_colony:
			execute_invest_in_colony(state, c.source, c.data.generic_location.prov);
			break;
		case command_type::abandon_colony:
			execute_abandon_colony(state, c.source, c.data.generic_location.prov);
			break;
		case command_type::finish_colonization:
			execute_finish_colonization(state, c.source, c.data.generic_location.prov);
			break;
		case command_type::intervene_in_war:
			execute_intervene_in_war(state, c.source, c.data.war_target.war, c.data.war_target.for_attacker);
			break;
		case command_type::suppress_movement:
			execute_suppress_movement(state, c.source, c.data.movement.iopt, c.data.movement.tag);
			break;
		case command_type::civilize_nation:
			execute_civilize_nation(state, c.source);
			break;
		case command_type::appoint_ruling_party:
			execute_appoint_ruling_party(state, c.source, c.data.political_party.p);
			break;
		case command_type::change_issue_option:
			execute_enact_issue(state, c.source, c.data.issue_selection.r);
			break;
		case command_type::change_reform_option:
			execute_enact_reform(state, c.source, c.data.reform_selection.r);
			break;
		case command_type::become_interested_in_crisis:
			execute_become_interested_in_crisis(state, c.source);
			break;
		case command_type::take_sides_in_crisis:
			execute_take_sides_in_crisis(state, c.source, c.data.crisis_join.join_attackers);
			break;
		case command_type::change_stockpile_settings:
			execute_change_stockpile_settings(state, c.source, c.data.stockpile_settings.c, c.data.stockpile_settings.amount,
				c.data.stockpile_settings.draw_on_stockpiles);
			break;
		case command_type::take_decision:
			execute_take_decision(state, c.source, c.data.decision.d);
			break;
		case command_type::make_n_event_choice:
			execute_make_event_choice(state, c.source, c.data.pending_human_n_event);
			break;
		case command_type::make_f_n_event_choice:
			execute_make_event_choice(state, c.source, c.data.pending_human_f_n_event);
			break;
		case command_type::make_p_event_choice:
			execute_make_event_choice(state, c.source, c.data.pending_human_p_event);
			break;
		case command_type::make_f_p_event_choice:
			execute_make_event_choice(state, c.source, c.data.pending_human_f_p_event);
			break;
		case command_type::cancel_cb_fabrication:
			execute_cancel_cb_fabrication(state, c.source);
			break;
		case command_type::fabricate_cb:
			execute_fabricate_cb(state, c.source, c.data.cb_fabrication.target, c.data.cb_fabrication.type);
			break;
		case command_type::ask_for_military_access:
			execute_ask_for_access(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::ask_for_alliance:
			execute_ask_for_alliance(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::call_to_arms:
			execute_call_to_arms(state, c.source, c.data.call_to_arms.target, c.data.call_to_arms.war);
			break;
		case command_type::respond_to_diplomatic_message:
			execute_respond_to_diplomatic_message(state, c.source, c.data.message.from, c.data.message.type, c.data.message.accept);
			break;
		case command_type::cancel_military_access:
			execute_cancel_military_access(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::cancel_alliance:
			execute_cancel_alliance(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::cancel_given_military_access:
			execute_cancel_given_military_access(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::declare_war:
			execute_declare_war(state, c.source, c.data.new_war.target, c.data.new_war.primary_cb, c.data.new_war.cb_state,
				c.data.new_war.cb_tag, c.data.new_war.cb_secondary_nation, c.data.new_war.call_attacker_allies);
			break;
		case command_type::add_war_goal:
			execute_add_war_goal(state, c.source, c.data.new_war_goal.war, c.data.new_war_goal.target, c.data.new_war_goal.cb_type,
				c.data.new_war_goal.cb_state, c.data.new_war_goal.cb_tag, c.data.new_war_goal.cb_secondary_nation);
			break;
		case command_type::start_peace_offer:
			execute_start_peace_offer(state, c.source, c.data.new_offer.target, c.data.new_offer.war,
				c.data.new_offer.is_concession);
			break;
		case command_type::add_peace_offer_term:
			execute_add_to_peace_offer(state, c.source, c.data.offer_wargoal.wg);
			break;
		case command_type::send_peace_offer:
			execute_send_peace_offer(state, c.source);
			break;
		case command_type::move_army:
			execute_move_army(state, c.source, c.data.army_movement.a, c.data.army_movement.dest, c.data.army_movement.reset);
			break;
		case command_type::move_navy:
			execute_move_navy(state, c.source, c.data.navy_movement.n, c.data.navy_movement.dest, c.data.navy_movement.reset);
			break;
		case command_type::embark_army:
			execute_embark_army(state, c.source, c.data.army_movement.a);
			break;
		case command_type::merge_armies:
			execute_merge_armies(state, c.source, c.data.merge_army.a, c.data.merge_army.b);
			break;
		case command_type::merge_navies:
			execute_merge_navies(state, c.source, c.data.merge_navy.a, c.data.merge_navy.b);
			break;
		case command_type::split_army:
			execute_split_army(state, c.source, c.data.army_movement.a);
			break;
		case command_type::split_navy:
			execute_split_navy(state, c.source, c.data.navy_movement.n);
			break;
		case command_type::delete_army:
			execute_delete_army(state, c.source, c.data.army_movement.a);
			break;
		case command_type::delete_navy:
			execute_delete_navy(state, c.source, c.data.navy_movement.n);
			break;
		case command_type::designate_split_regiments:
			execute_mark_regiments_to_split(state, c.source, c.data.split_regiments.regs);
			break;
		case command_type::designate_split_ships:
			execute_mark_ships_to_split(state, c.source, c.data.split_ships.ships);
			break;
		case command_type::naval_retreat:
			execute_retreat_from_naval_battle(state, c.source, c.data.naval_battle.b);
			break;
		case command_type::land_retreat:
			execute_retreat_from_land_battle(state, c.source, c.data.land_battle.b);
			break;
		case command_type::start_crisis_peace_offer:
			execute_start_crisis_peace_offer(state, c.source, c.data.new_offer.is_concession);
			break;
		case command_type::invite_to_crisis:
			execute_invite_to_crisis(state, c.source, c.data.crisis_invitation);
			break;
		case command_type::add_wargoal_to_crisis_offer:
			execute_add_to_crisis_peace_offer(state, c.source, c.data.crisis_invitation);
			break;
		case command_type::send_crisis_peace_offer:
			execute_send_crisis_peace_offer(state, c.source);
			break;
		case command_type::change_admiral:
			execute_change_admiral(state, c.source, c.data.new_admiral.a, c.data.new_admiral.l);
			break;
		case command_type::change_general:
			execute_change_general(state, c.source, c.data.new_general.a, c.data.new_general.l);
			break;
		case command_type::toggle_mobilization:
			execute_toggle_mobilization(state, c.source);
			break;
		case command_type::toggle_auto_create_generals:
			execute_toggle_auto_create_generals(state, c.source);
			break;
		case command_type::toggle_auto_assign_leaders:
			execute_toggle_auto_assign_leaders(state, c.source);
			break;
		case command_type::toggle_auto_assign_single_leader:
			execute_toggle_auto_assign_single_leader(state, c.source, c.data.leader.l);
			break;
		case command_type::give_military_access:
			execute_give_military_access(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::set_rally_point:
			execute_set_rally_point(state, c.source, c.data.rally_point.location, c.data.rally_point.naval, c.data.rally_point.enable);
			break;
		case command_type::save_game:
			execute_save_game(state, c.source, c.data.save_game.and_quit);
			break;
		case command_type::cancel_factory_building_construction:
			execute_cancel_factory_building_construction(state, c.source, c.data.start_factory_building.location, c.data.start_factory_building.type);
			break;
		case command_type::disband_undermanned:
			execute_disband_undermanned_regiments(state, c.source, c.data.army_movement.a);
			break;
		case command_type::even_split_army:
			execute_evenly_split_army(state, c.source, c.data.army_movement.a);
			break;
		case command_type::even_split_navy:
			execute_evenly_split_navy(state, c.source, c.data.navy_movement.n);
			break;
		case command_type::toggle_hunt_rebels:
			execute_toggle_rebel_hunting(state, c.source, c.data.army_movement.a);
			break;
		case command_type::state_transfer:
			execute_state_transfer(state, c.source, c.data.state_transfer.target, c.data.state_transfer.state);
			break;
		case command_type::release_subject:
			execute_release_subject(state, c.source, c.data.diplo_action.target);
			break;
		case command_type::enable_debt:
			execute_enable_debt(state, c.source);
			break;
		case command_type::toggle_unit_ai_control:
			execute_toggle_unit_ai_control(state, c.source, c.data.army_movement.a);
			break;
		case command_type::toggle_mobilized_is_ai_controlled:
			execute_toggle_mobilized_is_ai_controlled(state, c.source);
			break;
		case command_type::pbutton_script:
			execute_use_province_button(state, c.source, c.data.pbutton.button, c.data.pbutton.id);
			break;
		case command_type::nbutton_script:
			execute_use_nation_button(state, c.source, c.data.nbutton.button, c.data.nbutton.id);
			break;
			// common mp commands
		case command_type::chat_message:
		{
			size_t count = 0;
			for(count = 0; count < sizeof(c.data.chat_message.body); count++)
				if(c.data.chat_message.body[count] == '\0')
					break;
			std::string_view sv(c.data.chat_message.body, c.data.chat_message.body + count);
			execute_chat_message(state, c.source, c.data.chat_message.body, c.data.chat_message.target);
			break;
		}
		case command_type::notify_player_ban:
			execute_notify_player_ban(state, c.source, c.data.nation_pick.target);
			break;
		case command_type::notify_player_kick:
			execute_notify_player_kick(state, c.source, c.data.nation_pick.target);
			break;
		case command_type::notify_player_joins:
			execute_notify_player_joins(state, c.source, c.data.player_name);
			break;
		case command_type::notify_player_leaves:
			execute_notify_player_leaves(state, c.source, c.data.notify_leave.make_ai);
			break;
		case command_type::notify_player_picks_nation:
			execute_notify_player_picks_nation(state, c.source, c.data.nation_pick.target);
			break;
		case command_type::notify_player_oos:
			execute_notify_player_oos(state, c.source);
			break;
		case command_type::notify_advanced_tick:
			execute_notify_advanced_tick(state, c.source);
			break;
		case command_type::advance_tick:
			execute_advance_tick(state, c.source, c.data.advance_tick.checksum, c.data.advance_tick.speed);
			break;
		case command_type::notify_save_loaded:
			execute_notify_save_loaded(state, c.source, c.data.notify_save_loaded.checksum);
			break;
		case command_type::notify_reload:
			execute_notify_reload(state, c.source, c.data.notify_reload.checksum);
			break;
		case command_type::notify_start_game:
			execute_notify_start_game(state, c.source);
			break;
		case command_type::notify_stop_game:
			execute_notify_stop_game(state, c.source);
			break;
		case command_type::notify_pause_game:
			execute_notify_pause_game(state, c.source);
			break;

			// console commands
		case command_type::c_switch_nation:
			execute_c_switch_nation(state, c.source, c.data.tag_target.ident);
			break;
		case command_type::c_change_diplo_points:
			execute_c_change_diplo_points(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_change_money:
			execute_c_change_money(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_westernize:
			execute_c_westernize(state, c.source);
			break;
		case command_type::c_unwesternize:
			execute_c_unwesternize(state, c.source);
			break;
		case command_type::c_change_owner:
			execute_c_change_owner(state, c.source, c.data.cheat_location.prov, c.data.cheat_location.n);
			break;
		case command_type::c_change_controller:
			execute_c_change_controller(state, c.source, c.data.cheat_location.prov, c.data.cheat_location.n);
			break;
		case command_type::c_change_research_points:
			execute_c_change_research_points(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_change_cb_progress:
			execute_c_change_cb_progress(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_change_infamy:
			execute_c_change_infamy(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_force_crisis:
			execute_c_force_crisis(state, c.source);
			break;
		case command_type::c_change_national_militancy:
			execute_c_change_national_militancy(state, c.source, c.data.cheat.value);
			break;
		case command_type::c_change_prestige:
			execute_c_change_prestige(state, c.source, c.data.cheat.value, c.data.cheat.target);
			break;
		case command_type::c_end_game:
			execute_c_end_game(state, c.source);
			break;
		case command_type::c_event:
			execute_c_event(state, c.source, c.data.cheat_int.value);
			break;
		case command_type::c_event_as:
			execute_c_event_as(state, c.source, c.data.cheat_event.as, c.data.cheat_event.value);
			break;
		case command_type::c_force_ally:
			execute_c_force_ally(state, c.source, c.data.nation_pick.target);
			break;
		case command_type::c_toggle_ai:
			execute_c_toggle_ai(state, c.source, c.data.nation_pick.target);
			break;
		case command_type::c_complete_constructions:
			execute_c_complete_constructions(state, c.source);
			break;
		case command_type::c_instant_research:
			execute_c_instant_research(state, c.source);
			break;
		case command_type::c_add_population:
			execute_c_add_population(state, c.source, c.data.cheat_int.value);
			break;
		case command_type::c_instant_army:
			execute_c_instant_army(state, c.source);
			break;
		case command_type::c_instant_navy:
			execute_c_instant_navy(state, c.source);
			break;
		case command_type::c_instant_industry:
			execute_c_instant_industry(state, c.source);
			break;
		case command_type::c_innovate:
			execute_c_innovate(state, c.source, c.data.cheat_invention_data.invention);
			break;
		case command_type::c_toggle_core:
			execute_c_toggle_core(state, c.source, c.data.cheat_location.prov, c.data.cheat_location.n);
			break;
		case command_type::c_always_accept_deals:
			execute_c_always_accept_deals(state, c.source);
			break;
		case command_type::c_always_allow_reforms:
			execute_c_always_allow_reforms(state, c.source);
			break;
		case command_type::c_always_allow_wargoals:
			execute_c_always_allow_wargoals(state, c.source);
			break;
		case command_type::c_set_auto_choice_all:
			execute_c_set_auto_choice_all(state, c.source);
			break;
		case command_type::c_clear_auto_choice_all:
			execute_c_clear_auto_choice_all(state, c.source);
			break;
		case command_type::c_always_allow_decisions:
			execute_c_always_allow_decisions(state, c.source);
			break;
		case command_type::c_always_potential_decisions:
			execute_c_always_potential_decisions(state, c.source);
			break;
		case command_type::c_add_year:
			execute_c_add_year(state, c.source, c.data.cheat_int.value);
			break;
		}
	}

	void execute_pending_commands(sys::state& state) {
		auto* c = state.incoming_commands.front();
		bool command_executed = false;
		while(c) {
			command_executed = true;
			execute_command(state, *c);
			state.incoming_commands.pop();
			c = state.incoming_commands.front();
		}

		if(command_executed) {
			province::update_connected_regions(state);
			province::update_cached_values(state);
			nations::update_cached_values(state);
			state.game_state_updated.store(true, std::memory_order::release);
		}
	}

	void load_savefile(sys::state& state, native_string file_name, bool is_new_game) {
		window::change_cursor(state, window::cursor_type::busy); //show busy cursor so player doesn't question

		std::vector<dcon::nation_id> players;
		for(const auto n : state.world.in_nation)
		if(state.world.nation_get_is_player_controlled(n))
			players.push_back(n);
		dcon::nation_id old_local_player_nation = state.local_player_nation;
		state.preload();
		bool loaded = false;
		if(is_new_game) {
			if(!sys::try_read_scenario_as_save_file(state, state.loaded_scenario_file)) {
				auto msg = std::string("Scenario file ") + text::native_to_utf8(state.loaded_scenario_file) + " could not be loaded.";
				ui::popup_error_window(state, "Scenario Error", msg);
			} else {
				loaded = true;
			}
		} else {
			if(!sys::try_read_save_file(state, file_name)) {
				auto msg = std::string("Save file ") + text::native_to_utf8(file_name) + " could not be loaded.";
				ui::popup_error_window(state, "Save Error", msg);
				state.save_list_updated.store(true, std::memory_order::release); //update savefile list
				//try loading save from scenario so we atleast have something to work on
				if(!sys::try_read_scenario_as_save_file(state, state.loaded_scenario_file)) {
					auto msg2 = std::string("Scenario file ") + text::native_to_utf8(state.loaded_scenario_file) + " could not be loaded.";
					ui::popup_error_window(state, "Scenario Error", msg2);
				} else {
					loaded = true;
				}
			} else {
				loaded = true;
			}
		}
		if(loaded) {
			/* Updating this flag lets the network state know that we NEED to send the
			savefile data, otherwise it is safe to assume the client has its own data
			friendly reminder that, scenario loading and reloading ends up with different outcomes */
			state.network_state.is_new_game = false;
			if(state.network_mode == sys::network_mode_type::host) {
				/* Save the buffer before we fill the unsaved data */
				state.local_player_nation = dcon::nation_id{ };
				network::write_network_save(state);
				state.fill_unsaved_data();
				for(const auto n : players)
					state.world.nation_set_is_player_controlled(n, true);
				state.local_player_nation = old_local_player_nation;
				assert(state.world.nation_get_is_player_controlled(state.local_player_nation));
				/* Now send the saved buffer before filling the unsaved data to the clients
				henceforth. */
				command::payload c{};
				c.type = command::command_type::notify_save_loaded;
				c.source = state.local_player_nation;
				c.data.notify_save_loaded.target = dcon::nation_id{};
				network::broadcast_save_to_clients(state, c, state.network_state.current_save_buffer.get(), state.network_state.current_save_length, state.network_state.current_save_checksum);
			} else {
				state.fill_unsaved_data();
			}
		}
		/* Savefiles might load with new railroads, so for responsiveness we
			update whenever one is loaded. */
		state.map_state.set_selected_province(dcon::province_id{});
		state.map_state.unhandled_province_selection = true;
		state.railroad_built.store(true, std::memory_order::release);
		state.province_ownership_changed.store(true, std::memory_order::release);
		state.province_name_changed.store(true, std::memory_order::release);
		state.game_state_updated.store(true, std::memory_order_release);

		window::change_cursor(state, window::cursor_type::normal); //normal cursor now
	}

} // namespace command
