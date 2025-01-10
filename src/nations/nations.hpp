#pragma once
#include "dcon.hpp"
#include "culture.hpp"
#include "military.hpp"

namespace nations {

	bool national_focus_is_unoptimal(sys::state& state, dcon::nation_id source, dcon::state_instance_id target_state, dcon::national_focus_id nfid);
	bool can_overwrite_national_focus(sys::state& state, dcon::nation_id source, dcon::state_instance_id target_state, dcon::national_focus_id focus);

	inline uint32_t tag_to_int(char first, char second, char third) {
		return (uint32_t(first) << 16) | (uint32_t(second) << 8) | (uint32_t(third) << 0);
	}
	inline std::string int_to_tag(uint32_t v) {
		char values[] = { char((v >> 16) & 0xFF), char((v >> 8) & 0xFF), char((v >> 0) & 0xFF) };
		return std::string(values, values + 3);
	}

	struct triggered_modifier {
		dcon::modifier_id linked_modifier;
		dcon::trigger_key trigger_condition;
	};

	struct fixed_event {
		int16_t chance; //0,2
		dcon::national_event_id id; //2,2
		dcon::trigger_key condition; //4,2
		uint16_t padding = 0; //6,2
	};
	struct fixed_election_event {
		int16_t chance; //0,2
		dcon::national_event_id id; //2,2
		dcon::trigger_key condition; //4,2
		dcon::issue_id issue_group; //6,1
		uint8_t padding = 0; //7,1
	};
	struct fixed_province_event {
		int16_t chance; //0,2
		dcon::provincial_event_id id; //2,2
		dcon::trigger_key condition; //4,2
		uint16_t padding = 0; //6,2
	};

	enum class focus_type : uint8_t {
		unknown = 0,
		rail_focus = 1,
		immigration_focus = 2,
		diplomatic_focus = 3,
		promotion_focus = 4,
		production_focus = 5,
		party_loyalty_focus = 6,
		//non-vanilla
		policy_focus,
		tier_1_focus,
		tier_2_focus,
		tier_3_focus,
		tier_4_focus,
		tier_5_focus,
		tier_6_focus,
		tier_7_focus,
		tier_8_focus,
		building_focus,
		population_focus,
		heavy_industry_focus,
		consumer_goods_focus,
		military_goods_focus,
		immigration_colonization_focus,
		small_promotion_focus,
		large_promotion_focus,
		massive_promotion_focus
	};

	enum class static_modifier : uint8_t {
		very_easy_player,
		easy_player,
		hard_player,
		very_hard_player,
		very_easy_ai,
		easy_ai,
		hard_ai,
		very_hard_ai,
		// provincial
		overseas,
		coastal,
		non_coastal,
		coastal_sea,
		sea_zone,
		land_province,
		blockaded,
		no_adjacent_controlled,
		core,
		has_siege,
		occupied,
		nationalism,
		infrastructure,
		// national
		base_values,
		war,
		peace,
		disarming,
		war_exhaustion,
		badboy,
		debt_default_to,
		bad_debter,
		great_power,
		second_power,
		civ_nation,
		unciv_nation,
		average_literacy,
		plurality,
		generalised_debt_default,
		total_occupation,
		total_blockaded,
		in_bankrupcy,
		count
	};

	struct global_national_state {
		std::vector<triggered_modifier> triggered_modifiers;
		std::vector<common_types::bitfield_type> global_flag_variables;
		std::vector<dcon::nation_id> nations_by_rank;

		tagged_vector<dcon::text_key, dcon::national_flag_id> flag_variable_names;
		tagged_vector<dcon::text_key, dcon::global_flag_id> global_flag_variable_names;
		tagged_vector<dcon::text_key, dcon::national_variable_id> variable_names;

		dcon::national_identity_id rebel_id;

		sys::static_game_rule_s static_game_rules[uint8_t(sys::static_game_rule::count)];
		dcon::modifier_id static_modifiers[uint8_t(static_modifier::count)];

		int32_t num_allocated_national_variables = 0;
		int32_t num_allocated_national_flags = 0;
		int32_t num_allocated_global_flags = 0;

		dcon::national_focus_id flashpoint_focus;
		dcon::national_focus_id clergy_focus;
		dcon::national_focus_id soldier_focus;
		dcon::national_focus_id aristocrat_focus;
		dcon::national_focus_id capitalist_focus;
		dcon::national_focus_id primary_factory_worker_focus;
		dcon::national_focus_id secondary_factory_worker_focus;

		float flashpoint_amount = 0.15f;

		std::vector<fixed_event> on_yearly_pulse;
		std::vector<fixed_event> on_quarterly_pulse;
		std::vector<fixed_province_event> on_battle_won;
		std::vector<fixed_province_event> on_battle_lost;
		std::vector<fixed_event> on_surrender;
		std::vector<fixed_event> on_new_great_nation;
		std::vector<fixed_event> on_lost_great_nation;
		std::vector<fixed_election_event> on_election_tick;
		std::vector<fixed_event> on_colony_to_state;
		std::vector<fixed_event> on_state_conquest;
		std::vector<fixed_event> on_colony_to_state_free_slaves;
		std::vector<fixed_event> on_debtor_default;
		std::vector<fixed_event> on_debtor_default_small;
		std::vector<fixed_event> on_debtor_default_second;
		std::vector<fixed_event> on_civilize;
		std::vector<fixed_event> on_my_factories_nationalized;
		std::vector<fixed_event> on_crisis_declare_interest;
		std::vector<fixed_event> on_election_started;
		std::vector<fixed_event> on_election_finished;

		bool gc_pending = false;

		bool is_global_flag_variable_set(dcon::global_flag_id id) const;
		void set_global_flag_variable(dcon::global_flag_id id, bool state);
	};

	namespace influence {

		constexpr inline uint8_t level_mask = uint8_t(0x07);
		constexpr inline uint8_t level_neutral = uint8_t(0x00);
		constexpr inline uint8_t level_opposed = uint8_t(0x01);
		constexpr inline uint8_t level_hostile = uint8_t(0x02);
		constexpr inline uint8_t level_cordial = uint8_t(0x03);
		constexpr inline uint8_t level_friendly = uint8_t(0x04);
		constexpr inline uint8_t level_in_sphere = uint8_t(0x05);

		constexpr inline uint8_t priority_mask = uint8_t(0x18);
		constexpr inline uint8_t priority_zero = uint8_t(0x00);
		constexpr inline uint8_t priority_one = uint8_t(0x08);
		constexpr inline uint8_t priority_two = uint8_t(0x10);
		constexpr inline uint8_t priority_three = uint8_t(0x18);

		// constexpr inline uint8_t is_expelled = uint8_t(0x20); // <-- didn't need this; free bit
		constexpr inline uint8_t is_discredited = uint8_t(0x40);
		constexpr inline uint8_t is_banned = uint8_t(0x80);

		inline uint8_t increase_level(uint8_t v) {
			switch(v & level_mask) {
				case level_neutral:
				return uint8_t((v & ~level_mask) | level_cordial);
				case level_opposed:
				return uint8_t((v & ~level_mask) | level_neutral);
				case level_hostile:
				return uint8_t((v & ~level_mask) | level_opposed);
				case level_cordial:
				return uint8_t((v & ~level_mask) | level_friendly);
				case level_friendly:
				return uint8_t((v & ~level_mask) | level_in_sphere);
				case level_in_sphere:
				return v;
				default:
				return v;
			}
		}
		inline uint8_t decrease_level(uint8_t v) {
			switch(v & level_mask) {
				case level_neutral:
				return uint8_t((v & ~level_mask) | level_opposed);
				case level_opposed:
				return uint8_t((v & ~level_mask) | level_hostile);
				case level_hostile:
				return v;
				case level_cordial:
				return uint8_t((v & ~level_mask) | level_neutral);
				case level_friendly:
				return uint8_t((v & ~level_mask) | level_cordial);
				case level_in_sphere:
				return uint8_t((v & ~level_mask) | level_friendly);
				default:
				return v;
			}
		}
		inline uint8_t increase_priority(uint8_t v) {
			if((v & priority_mask) != priority_three) {
				return uint8_t(v + priority_one);
			} else {
				return v;
			}
		}
		inline uint8_t decrease_priority(uint8_t v) {
			if((v & priority_mask) != priority_zero) {
				return uint8_t(v - priority_one);
			} else {
				return v;
			}
		}
		inline bool is_influence_level_greater(int32_t l, int32_t r) {
			switch(l) {
				case level_hostile:
				return false;
				case level_opposed:
				return r == level_hostile;
				case level_neutral:
				return r == level_hostile || r == level_opposed;
				case level_cordial:
				return r <= 2;
				case level_friendly:
				return r <= 3;
				case level_in_sphere:
				return r <= 4;
				default:
				return false;
			}
		}
		inline bool is_influence_level_greater_or_equal(int32_t l, int32_t r) {
			return l == r || is_influence_level_greater(l, r);
		}
		int32_t get_level(sys::state& state, dcon::nation_id gp, dcon::nation_id target);

	} // namespace influence

	dcon::nation_id get_nth_great_power(sys::state const& state, uint16_t n);

	dcon::nation_id owner_of_pop(sys::state const& state, dcon::pop_id pop_ids);

	bool can_release_as_vassal(sys::state const& state, dcon::nation_id n, dcon::national_identity_id releasable);
	bool identity_has_holder(sys::state const& state, dcon::national_identity_id ident);
	dcon::nation_id get_relationship_partner(sys::state const& state, dcon::diplomatic_relation_id rel_id, dcon::nation_id query);

	void update_cached_values(sys::state& state);
	void restore_unsaved_values(sys::state& state);
	void restore_state_instances(sys::state& state);
	void generate_initial_state_instances(sys::state& state);

	dcon::text_key name_from_tag(sys::state& state, dcon::national_identity_id tag);

	void update_administrative_efficiency(sys::state& state);

	float daily_research_points(sys::state& state, dcon::nation_id n);
	void update_research_points(sys::state& state);

	void update_industrial_scores(sys::state& state);
	void update_military_scores(sys::state& state);
	void update_rankings(sys::state& state);
	void update_ui_rankings(sys::state& state);

	bool is_great_power(sys::state const& state, dcon::nation_id n);
	float prestige_score(sys::state const& state, dcon::nation_id n);

enum class status : uint8_t { great_power, secondary_power, civilized, westernizing, uncivilized, primitive };
	status get_status(sys::state& state, dcon::nation_id n);

	sys::date get_research_end_date(sys::state& state, dcon::technology_id, dcon::nation_id);
	dcon::technology_id current_research(sys::state const& state, dcon::nation_id n);
	float suppression_points(sys::state const& state, dcon::nation_id n);

	float diplomatic_points(sys::state const& state, dcon::nation_id n);
	float monthly_diplomatic_points(sys::state const& state, dcon::nation_id n);

	float leadership_points(sys::state const& state, dcon::nation_id n);
	float get_treasury(sys::state& state, dcon::nation_id n);
	float get_bank_funds(sys::state& state, dcon::nation_id n);
	float get_debt(sys::state& state, dcon::nation_id n);
	float tariff_efficiency(sys::state& state, dcon::nation_id n);
	float tax_efficiency(sys::state& state, dcon::nation_id n);
	float colonial_points_from_naval_bases(sys::state& state, dcon::nation_id n);
	float colonial_points_from_ships(sys::state& state, dcon::nation_id n);
	float colonial_points_from_technology(sys::state& state, dcon::nation_id n);
	float used_colonial_points(sys::state& state, dcon::nation_id n);
	int32_t free_colonial_points(sys::state& state, dcon::nation_id n);
	int32_t max_colonial_points(sys::state& state, dcon::nation_id n);
	uint32_t get_total_pop_in_owned_provinces(sys::state& state, dcon::nation_id n);

	bool has_political_reform_available(sys::state& state, dcon::nation_id n);
	bool has_social_reform_available(sys::state& state, dcon::nation_id n);
	bool has_reform_available(sys::state& state, dcon::nation_id n);
	bool has_decision_available(sys::state& state, dcon::nation_id n);
	int32_t max_national_focuses(sys::state& state, dcon::nation_id n);
	int32_t national_focuses_in_use(sys::state& state, dcon::nation_id n);
	bool can_expand_colony(sys::state& state, dcon::nation_id n);
	bool is_losing_colonial_race(sys::state& state, dcon::nation_id n);
	bool sphereing_progress_is_possible(sys::state& state, dcon::nation_id n); // can increase opinion or add to sphere
	bool is_involved_in_crisis(sys::state const& state, dcon::nation_id n);
	bool is_committed_in_crisis(sys::state const& state, dcon::nation_id n);
	bool can_put_flashpoint_focus_in_state(sys::state& state, dcon::state_instance_id s, dcon::nation_id fp_nation);
	float get_monthly_pop_increase_of_nation(sys::state& state, dcon::nation_id n);
	bool can_accumulate_influence_with(sys::state& state, dcon::nation_id gp, dcon::nation_id target, dcon::gp_relationship_id rel);
	bool are_allied(sys::state& state, dcon::nation_id a, dcon::nation_id b);
	bool is_landlocked(sys::state& state, dcon::nation_id n);

	bool nth_crisis_war_goal_is_for_attacker(sys::state& state, int32_t index);
	military::full_wg get_nth_crisis_war_goal(sys::state& state, int32_t index);
	int32_t num_crisis_wargoals(sys::state& state);

	void get_active_political_parties(sys::state& state, dcon::nation_id n, std::vector<dcon::political_party_id>& parties);

	void update_monthly_points(sys::state& state);

	// may create a relationship DO NOT call in a context where two or more such functions may run in parallel
	void adjust_relationship(sys::state& state, dcon::nation_id a, dcon::nation_id b, float delta);
	// used for creating a "new" nation when it is released
	void create_nation_based_on_template(sys::state& state, dcon::nation_id n, dcon::nation_id base);
	// call after a nation loses its last province
	void cleanup_nation(sys::state& state, dcon::nation_id n);

	void adjust_prestige(sys::state& state, dcon::nation_id n, float delta);
	void adjust_prestige_no_modifier(sys::state& state, dcon::nation_id n, float delta);

	void destroy_diplomatic_relationships(sys::state& state, dcon::nation_id n);
	void release_vassal(sys::state& state, dcon::overlord_id rel);
	void make_vassal(sys::state& state, dcon::nation_id subject, dcon::nation_id overlord);
	void make_substate(sys::state& state, dcon::nation_id subject, dcon::nation_id overlord);
	void break_alliance(sys::state& state, dcon::diplomatic_relation_id rel);
	void break_alliance(sys::state& state, dcon::nation_id a, dcon::nation_id b);
	void make_alliance(sys::state& state, dcon::nation_id a, dcon::nation_id b);
	void adjust_influence(sys::state& state, dcon::nation_id great_power, dcon::nation_id target, float delta);
	void adjust_influence_with_overflow(sys::state& state, dcon::nation_id great_power, dcon::nation_id target, float delta);
	void adjust_foreign_investment(sys::state& state, dcon::nation_id great_power, dcon::nation_id target, float delta);
	void enact_issue(sys::state& state, dcon::nation_id source, dcon::issue_option_id i);
	void enact_reform(sys::state& state, dcon::nation_id source, dcon::reform_option_id i);

	float get_foreign_investment(sys::state& state, dcon::nation_id n);
	float get_foreign_investment_as_gp(sys::state& state, dcon::nation_id n);
	float get_base_shares(sys::state& state, dcon::gp_relationship_id gp, float total_gain, int32_t total_influence_shares);
	bool has_sphere_neighbour(sys::state& state, dcon::nation_id n, dcon::nation_id target);

	void update_great_powers(sys::state& state);
	void update_influence(sys::state& state);
	void update_revanchism(sys::state& state);

	void monthly_flashpoint_update(sys::state& state);
	void daily_update_flashpoint_tension(sys::state& state);
	void update_crisis(sys::state& state);

	void add_as_primary_crisis_defender(sys::state& state, dcon::nation_id n);
	void add_as_primary_crisis_attacker(sys::state& state, dcon::nation_id n);
	void reject_crisis_participation(sys::state& state);
	void cleanup_crisis(sys::state& state);
	void cleanup_crisis_peace_offer(sys::state& state, dcon::peace_offer_id peace);
	void accept_crisis_peace_offer(sys::state& state, dcon::nation_id from, dcon::nation_id to, dcon::peace_offer_id peace);

	void update_pop_acceptance(sys::state& state, dcon::nation_id n);
	void liberate_nation_from(sys::state& state, dcon::national_identity_id liberated, dcon::nation_id from);
	void release_nation_from(sys::state& state, dcon::national_identity_id liberated,
		dcon::nation_id from); // difference from liberate: only non-cores can be lost with release
	void remove_cores_from_owned(sys::state& state, dcon::nation_id n, dcon::national_identity_id tag);
	void perform_nationalization(sys::state& state, dcon::nation_id n);

	float get_yesterday_income(sys::state& state, dcon::nation_id n);

	void make_civilized(sys::state& state, dcon::nation_id n);
	void make_uncivilized(sys::state& state, dcon::nation_id n);

	void run_gc(sys::state& state);

	bool has_core_in_nation(sys::state& state, dcon::national_identity_id nid, dcon::nation_id m);

	void inherit_nation(sys::state& state, dcon::nation_id n, dcon::nation_id who);
	void annex_to_nation(sys::state& state, dcon::nation_id n, dcon::nation_id who);
	void add_treasury(sys::state& state, dcon::nation_id n, float v);

	bool has_country_modifier(sys::state& state, dcon::nation_id n, dcon::modifier_id m);

	void cleanup_dead_gps(sys::state& state);
} // namespace nations
