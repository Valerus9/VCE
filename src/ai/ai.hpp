#pragma once
#include "dcon.hpp"

#include "container_types.hpp" 
#include "economy_container_types.hpp" 
#include "culture_container_types.hpp" 
#include "system/system_container_types.hpp"

#include "text.hpp"

namespace ai {
	enum class fleet_activity {
		unspecified = 0,		// ai hasn't run on this unit yet
		boarding = 1,			// waiting for troops to arrive
		transporting = 2,		// moving or waiting for troops to disembark
		returning_to_base = 3,	// moving back to home port
		attacking = 4,			// trying to attack another fleet
		merging = 5,			// moving to main base to merge up
		idle = 6,				// sitting in main base with no order
		unloading = 7,			// transport arrived, waiting for units to get off
		failed_transport = 8,
	};

	enum class army_activity {
		unspecified = 0,
		on_guard = 1,			// hold in place
		attacking = 2,
		merging = 3,
		transport_guard = 4,
		transport_attack = 5,
		// attack_finished = 6,
		attack_gathered = 7,
		attack_transport = 8,
	};

	struct ClassifiedProvince {
		dcon::province_id id;
		float weight;
	};

	struct CrisisStrength {
		float attacker = 0.0f;
		float defender = 0.0f;
	};

	struct PossibleCasusBeli {
		dcon::nation_id target;
		dcon::nation_id secondary_nation;
		dcon::national_identity_id associated_tag;
		dcon::state_definition_id state_def;
		dcon::cb_type_id cb;
	};

	void add_free_ai_cbs_to_war(sys::state& state, dcon::nation_id n, dcon::war_id w);
	void add_gw_goals(sys::state& state);
	void add_wg_to_great_war(sys::state& state, dcon::nation_id n, dcon::war_id w);
	bool ai_will_accept_alliance(sys::state& state, dcon::nation_id target, dcon::nation_id from);
	bool ai_will_grant_access(sys::state& state, dcon::nation_id target, dcon::nation_id from);

	void build_ships(sys::state& state);

	bool can_add_unjustified_cbs(sys::state& state, dcon::nation_id n, bool is_gw);
	bool can_go_war_with(sys::state& state, dcon::nation_id n, dcon::nation_id real_target, dcon::nation_id other);
	void civilize(sys::state& state);

	void daily_cleanup(sys::state& state);
	void distribute_guards_add_province(sys::state& state, dcon::nation_id n, dcon::province_id p, std::vector<ClassifiedProvince>& provinces);

	float estimate_army_defensive_strength(sys::state& state, dcon::army_id a);
	float estimate_army_offensive_strength(sys::state& state, dcon::army_id a);
	float estimate_balanced_composition_factor(sys::state& state, dcon::army_id a);
	float estimate_enemy_defensive_force(sys::state& state, dcon::province_id target, dcon::nation_id by);
	float estimate_friendly_offensive_force(sys::state& state, dcon::province_id target, dcon::nation_id by);
	float estimate_rebel_strength(sys::state& state, dcon::province_id p);
	float estimate_strength_self(sys::state& state, dcon::nation_id n);
	float estimateDefensiveStrength(sys::state& state, dcon::nation_id nation);
	float estimateStrength(sys::state& state, dcon::nation_id nation);
	void explain_ai_access_reasons(sys::state& state, dcon::nation_id target, text::layout_base& contents, int32_t indent);
	void explain_ai_alliance_reasons(sys::state& state, dcon::nation_id target, text::layout_base& contents, int32_t indent);

	void form_alliances(sys::state& state);

	void gather_to_battle(sys::state& state, dcon::nation_id n, dcon::province_id p);
	void general_ai_unit_tick(sys::state& state);
	void get_desired_factory_types(sys::state& state, dcon::nation_id nid, std::vector<dcon::factory_type_id>& desired_types);
	bool get_is_desirable_factory_type(sys::state& state, dcon::nation_id n, dcon::factory_type_id ft);
	bool get_is_ideal_tws(sys::state& state, dcon::nation_id n, dcon::war_id war, dcon::cb_type_id cb, dcon::state_definition_id sd,
		dcon::nation_id target, dcon::nation_id secondary_nation,
		dcon::national_identity_id associated_tag, military::war_role role);

	void identify_focuses(sys::state& state);
	static void internal_get_alliance_targets(sys::state& state, dcon::nation_id n,
		std::vector<dcon::nation_id, common_types::cache_aligned_allocator<dcon::nation_id>>& alliance_targets);
	static void internal_get_alliance_targets_by_adjacency(sys::state& state, dcon::nation_id n, dcon::nation_id adj,
		std::vector<dcon::nation_id, common_types::cache_aligned_allocator<dcon::nation_id>>& alliance_targets);

	void make_attacks(sys::state& state);
	void make_defense(sys::state& state);
	void make_peace_offers(sys::state& state);
	void make_war_decs(sys::state& state);
	void move_gathered_attackers(sys::state& state);
	void move_idle_guards(sys::state& state);

	bool naval_advantage(sys::state& state, dcon::nation_id n);
	bool naval_supremacy(sys::state& state, dcon::nation_id n, dcon::nation_id target);
	void new_units_and_merging(sys::state& state);

	void place_instance_in_result(sys::state& state, std::vector<PossibleCasusBeli>& result, dcon::nation_id n, dcon::nation_id target,
		dcon::cb_type_id cb, std::vector<dcon::state_instance_id> const& target_states);
	void place_instance_in_result_war(sys::state& state, std::vector<PossibleCasusBeli>& result, dcon::nation_id n,
		dcon::nation_id target, dcon::war_id w, dcon::cb_type_id cb, std::vector<dcon::state_instance_id> const& target_states);
	void perform_cycling(sys::state& state);
	void perform_foreign_investments(sys::state& state);
	void perform_influence_actions(sys::state& state);
	dcon::cb_type_id pick_fabrication_type(sys::state& state, dcon::nation_id from, dcon::nation_id target);
	dcon::cb_type_id pick_gw_extra_cb_type(sys::state& state, dcon::nation_id from, dcon::nation_id target);
	dcon::nation_id pick_gw_target(sys::state& state, dcon::nation_id from, dcon::war_id w, bool is_attacker);
	void pickup_idle_ships(sys::state& state);
	float province_supply_usage(sys::state& state, dcon::nation_id n, dcon::province_id p);
	void prune_alliances(sys::state& state);

	void refresh_home_ports(sys::state& state);
	void remove_ai_data(sys::state& state, dcon::nation_id n);

	void send_fleet_home(sys::state& state, dcon::navy_id n,
		fleet_activity moving_status = fleet_activity::returning_to_base, fleet_activity at_base = fleet_activity::idle);
	bool set_fleet_target(sys::state& state, dcon::nation_id n, dcon::province_id start, dcon::navy_id for_navy);
	void sort_available_declaration_cbs(std::vector<PossibleCasusBeli>& result, sys::state& state,
		dcon::nation_id n, dcon::nation_id target);
	void sort_cbs_for_war(std::vector<PossibleCasusBeli>& result, sys::state& state, dcon::nation_id n,
		dcon::war_id w, bool add_unjustified);
	void state_target_list(std::vector<dcon::state_instance_id>& result, sys::state& state,
		dcon::nation_id for_nation, dcon::nation_id within);

	void take_ai_decisions(sys::state& state);
	void take_reforms(sys::state& state);
	bool target_in_sphere_potential_war_target(sys::state& state, dcon::nation_id n, dcon::nation_id t);

	bool unit_on_ai_control(sys::state& state, dcon::army_id a);
	void unload_units_from_transport(sys::state& state, dcon::navy_id n);
	void upgrade_colonies(sys::state& state);
	void update_ai_colonial_investment(sys::state& state);
	void update_ai_colony_starting(sys::state& state);
	void update_ai_econ_construction(sys::state& state);
	void update_ai_general_status(sys::state& state);
	void update_ai_research(sys::state& state);
	void update_ai_ruling_party(sys::state& state);
	void update_budget(sys::state& state);
	void update_cb_fabrication(sys::state& state);
	void update_crisis_leaders(sys::state& state);
	void update_focuses(sys::state& state);	
	void update_influence_priorities(sys::state& state);
	void update_naval_transport(sys::state& state);
	void update_land_constructions(sys::state& state);
	void update_ships(sys::state& state);
	void update_war_intervention(sys::state& state);

	bool valid_construction_target(sys::state& state, dcon::nation_id from, dcon::nation_id target);

	float war_harshness_factor(int32_t war_duration, bool is_great_war);
	float war_willingness_factor(int32_t war_duration, bool is_great_war);
	float war_weight_potential_target(sys::state& state, dcon::nation_id n, dcon::nation_id target, float base_strength);
	bool will_accept_crisis_peace_offer(sys::state& state, dcon::nation_id to, dcon::peace_offer_id peace);
	bool will_accept_crisis_peace_offer(sys::state& state, dcon::nation_id to, bool is_concession, bool missing_wg);
	bool will_accept_peace_offer(sys::state& state, dcon::nation_id n, dcon::nation_id from, dcon::peace_offer_id p);
	bool will_accept_peace_offer_value(sys::state& state,
	dcon::nation_id n, dcon::nation_id from,
	dcon::nation_id prime_attacker, dcon::nation_id prime_defender,
	float primary_warscore, float scoreagainst_me,
	bool offer_from_attacker, bool concession,
	int32_t overall_po_value, int32_t my_po_target,
	int32_t target_personal_po_value, int32_t potential_peace_score_against,
	int32_t my_side_against_target, int32_t my_side_peace_cost,
	int32_t war_duration, bool contains_sq);
	bool will_be_crisis_primary_attacker(sys::state& state, dcon::nation_id n);
	bool will_be_crisis_primary_defender(sys::state& state, dcon::nation_id n);
	bool will_join_war(sys::state& state, dcon::nation_id, dcon::war_id, bool as_attacker);
	bool will_join_crisis_with_offer(sys::state& state, dcon::nation_id n, sys::crisis_join_offer const& offer);
	bool would_surrender_evaluate(sys::state& state, dcon::nation_id n, dcon::war_id w);
}
