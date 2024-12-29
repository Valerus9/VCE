#pragma once
#include "dcon.hpp"
#include "common_types.hpp"
#include "events.hpp"
#include "diplomatic_messages.hpp"

namespace command {

	void c_switch_nation(sys::state& state, dcon::nation_id source, dcon::national_identity_id t);
	bool can_c_switch_nation(sys::state& state, dcon::nation_id source, dcon::national_identity_id t);
	void c_change_diplo_points(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_change_money(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_westernize(sys::state& state, dcon::nation_id source);
	void c_unwesternize(sys::state& state, dcon::nation_id source);
	void c_change_research_points(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_change_cb_progress(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_change_infamy(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_force_crisis(sys::state& state, dcon::nation_id source);
	void c_change_national_militancy(sys::state& state, dcon::nation_id source, float value);
	void c_change_prestige(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void c_end_game(sys::state& state, dcon::nation_id source);
	void c_event(sys::state& state, dcon::nation_id source, int32_t id);
	void c_event_as(sys::state& state, dcon::nation_id source, dcon::nation_id as, int32_t id);
	void c_force_ally(sys::state& state, dcon::nation_id source, dcon::nation_id target);
	void c_toggle_ai(sys::state& state, dcon::nation_id source, dcon::nation_id target);
	void c_complete_constructions(sys::state& state, dcon::nation_id source);
	void c_change_owner(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id new_owner);
	void c_change_controller(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id new_controller);
	void c_instant_research(sys::state& state, dcon::nation_id source);
	void c_add_population(sys::state& state, dcon::nation_id source, int32_t ammount);
	void c_instant_army(sys::state& state, dcon::nation_id source);
	void c_instant_navy(sys::state& state, dcon::nation_id source);
	void c_instant_industry(sys::state& state, dcon::nation_id source);
	void c_innovate(sys::state& state, dcon::nation_id source, dcon::invention_id invention);
	void c_toggle_core(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id n);
	void c_always_allow_wargoals(sys::state& state, dcon::nation_id source);
	void c_always_allow_reforms(sys::state& state, dcon::nation_id source);
	void c_always_accept_deals(sys::state& state, dcon::nation_id source);
	void c_set_auto_choice_all(sys::state& state, dcon::nation_id source);
	void c_clear_auto_choice_all(sys::state& state, dcon::nation_id source);
	void c_always_allow_decisions(sys::state& state, dcon::nation_id source);
	void c_always_potential_decisions(sys::state& state, dcon::nation_id source);
	void c_add_year(sys::state& state, dcon::nation_id source, int32_t amount);

	void execute_c_switch_nation(sys::state& state, dcon::nation_id source, dcon::national_identity_id t);
	void execute_c_change_diplo_points(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_change_money(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_westernize(sys::state& state, dcon::nation_id source);
	void execute_c_unwesternize(sys::state& state, dcon::nation_id source);
	void execute_c_change_research_points(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_change_cb_progress(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_change_infamy(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_force_crisis(sys::state& state, dcon::nation_id source);
	void execute_c_change_national_militancy(sys::state& state, dcon::nation_id source, float value);
	void execute_c_change_prestige(sys::state& state, dcon::nation_id source, float value, dcon::nation_id n);
	void execute_c_end_game(sys::state& state, dcon::nation_id source);
	void execute_c_event(sys::state& state, dcon::nation_id source, int32_t id);
	void execute_c_event_as(sys::state& state, dcon::nation_id source, dcon::nation_id as, int32_t id);
	void execute_c_force_ally(sys::state& state, dcon::nation_id source, dcon::nation_id target);
	void execute_c_toggle_ai(sys::state& state, dcon::nation_id source, dcon::nation_id target);
	void execute_c_complete_constructions(sys::state& state, dcon::nation_id source);
	void execute_c_change_owner(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id new_owner);
	void execute_c_change_controller(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id new_controller);
	void execute_c_instant_research(sys::state& state, dcon::nation_id source);
	void execute_c_add_population(sys::state& state, dcon::nation_id source, int32_t ammount);
	void execute_c_instant_army(sys::state& state, dcon::nation_id source);
	void execute_c_instant_navy(sys::state& state, dcon::nation_id source);
	void execute_c_instant_industry(sys::state& state, dcon::nation_id source);
	void execute_c_innovate(sys::state& state, dcon::nation_id source, dcon::invention_id invention);
	void execute_c_toggle_core(sys::state& state, dcon::nation_id source, dcon::province_id p, dcon::nation_id n);
	void execute_c_always_allow_wargoals(sys::state& state, dcon::nation_id source);
	void execute_c_always_allow_reforms(sys::state& state, dcon::nation_id source);
	void execute_c_always_accept_deals(sys::state& state, dcon::nation_id source);
	void execute_c_set_auto_choice_all(sys::state& state, dcon::nation_id source);
	void execute_c_clear_auto_choice_all(sys::state& state, dcon::nation_id source);
	void execute_c_always_allow_decisions(sys::state& state, dcon::nation_id source);
	void execute_c_always_potential_decisions(sys::state& state, dcon::nation_id source);
	void execute_c_add_year(sys::state& state, dcon::nation_id source, int32_t amount);

} // namespace command
