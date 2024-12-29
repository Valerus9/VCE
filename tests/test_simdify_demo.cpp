#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "demographics.hpp"
#include "dcon.hpp"
#include "system_state.hpp"
#include "prng.hpp"
#include "province_templates.hpp"
#include "nations.hpp"
#include "nations_templates.hpp"
#include "triggers.hpp"
#include "ve_scalar_extensions.hpp"

namespace pop_demographics_duplicate {
	dcon::pop_demographics_key to_key(sys::state const& state, dcon::ideology_id v) {
		return dcon::pop_demographics_key(dcon::pop_demographics_key::value_base_t(v.index() + pop_demographics::count_special_keys));
	}
	dcon::pop_demographics_key to_key(sys::state const& state, dcon::issue_option_id v) {
		return dcon::pop_demographics_key(
			dcon::pop_demographics_key::value_base_t(state.world.ideology_size() + v.index() + pop_demographics::count_special_keys));
	}

	uint32_t size(sys::state const& state) {
		return state.world.ideology_size() + state.world.issue_option_size() + pop_demographics::count_special_keys;
	}

	void regenerate_is_primary_or_accepted(sys::state& state) {
		state.world.for_each_pop([&](dcon::pop_id p) {
			state.world.pop_set_is_primary_or_accepted_culture(p, false);
			auto n = nations::owner_of_pop(state, p);
			if(state.world.nation_get_primary_culture(n) == state.world.pop_get_culture(p)) {
				state.world.pop_set_is_primary_or_accepted_culture(p, true);
				return;
			}
			if(state.world.nation_get_accepted_cultures(n, state.world.pop_get_culture(p)) == true) {
				state.world.pop_set_is_primary_or_accepted_culture(p, true);
				return;
			}
		});
	}
} // namespace pop_demographics

namespace demographics_duplicate {
	inline constexpr float ideologies_change_rate = 0.10f;
	inline constexpr float issues_change_rate = 0.10f;
	inline constexpr float small_pop_size = 100.0f;

	dcon::demographics_key to_key(sys::state const& state, dcon::pop_type_id v) {
		return dcon::demographics_key(dcon::pop_demographics_key::value_base_t(
			demographics::count_special_keys + v.index()));
	}
	dcon::demographics_key to_employment_key(sys::state const& state, dcon::pop_type_id v) {
		return dcon::demographics_key(dcon::pop_demographics_key::value_base_t(
		demographics::count_special_keys + state.world.pop_type_size() + v.index()));
	}
	dcon::demographics_key to_key(sys::state const& state, dcon::culture_id v) {
		return dcon::demographics_key(
			dcon::pop_demographics_key::value_base_t(demographics::count_special_keys + state.world.pop_type_size() * 2 + v.index()));
	}
	dcon::demographics_key to_key(sys::state const& state, dcon::ideology_id v) {
		return dcon::demographics_key(dcon::pop_demographics_key::value_base_t(demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size() + v.index()));
	}
	dcon::demographics_key to_key(sys::state const& state, dcon::issue_option_id v) {
		return dcon::demographics_key(dcon::pop_demographics_key::value_base_t(demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size() + state.world.ideology_size() + v.index()));
	}
	dcon::demographics_key to_key(sys::state const& state, dcon::religion_id v) {
		return dcon::demographics_key(dcon::pop_demographics_key::value_base_t(demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size() + state.world.ideology_size() + state.world.issue_option_size() + v.index()));
	}

	uint32_t size(sys::state const& state) {
		return demographics::count_special_keys + state.world.ideology_size() + state.world.issue_option_size() +
				 uint32_t(2) * state.world.pop_type_size() + state.world.culture_size() + state.world.religion_size();
	}
	uint32_t common_size(sys::state const& state) {
		return demographics::count_special_keys + uint32_t(2) * state.world.pop_type_size();
	}

	template<typename F>
	void sum_over_demographics(sys::state& state, dcon::demographics_key key, F const& source) {
		// clear province
		province::ve_for_each_land_province(state, [&](auto pi) {
			state.world.province_set_demographics(pi, key, ve::fp_vector());
		});
		// sum in province
		state.world.for_each_pop([&](dcon::pop_id p) {
			auto location = state.world.pop_get_province_from_pop_location(p);
			state.world.province_get_demographics(location, key) += source(state, p);
		});
		// clear state
		state.world.execute_serial_over_state_instance([&](auto si) {
			state.world.state_instance_set_demographics(si, key, ve::fp_vector());
		});
		// sum in state
		province::for_each_land_province(state, [&](dcon::province_id p) {
			auto location = state.world.province_get_state_membership(p);
			state.world.state_instance_get_demographics(location, key) += state.world.province_get_demographics(p, key);
		});
		// clear nation
		state.world.execute_serial_over_nation([&](auto ni) {
			state.world.nation_set_demographics(ni, key, ve::fp_vector());
		});
		// sum in nation
		state.world.for_each_state_instance([&](dcon::state_instance_id s) {
			auto location = state.world.state_instance_get_nation_from_state_ownership(s);
			state.world.nation_get_demographics(location, key) += state.world.state_instance_get_demographics(s, key);
		});
	}

	inline constexpr uint32_t extra_demo_grouping = 8;

	template<typename F>
	void sum_over_single_nation_demographics(sys::state& state, dcon::demographics_key key, dcon::nation_id n, F const& source) {
		// clear province
		for(auto pc : state.world.nation_get_province_control_as_nation(n)) {
			auto location = pc.get_province();
			state.world.province_set_demographics(location, key, 0.f);
			for(auto pl : pc.get_province().get_pop_location_as_province()) {
				state.world.province_get_demographics(location, key) += source(state, pl.get_pop());
			}
		}
		for(auto sc : state.world.nation_get_state_ownership_as_nation(n)) {
			auto location = sc.get_state();
			state.world.state_instance_set_demographics(location, key, 0.f);
			for(auto sm : sc.get_state().get_definition().get_abstract_state_membership()) {
				state.world.state_instance_get_demographics(location, key) += state.world.province_get_demographics(sm.get_province(), key);
			}
		}
		state.world.nation_set_demographics(n, key, 0.f);
		for(auto sc : state.world.nation_get_state_ownership_as_nation(n)) {
			state.world.nation_get_demographics(n, key) += state.world.state_instance_get_demographics(sc.get_state(), key);
		}
	}

	void regenerate_jingoism_support(sys::state& state, dcon::nation_id n) {
		dcon::demographics_key key = to_key(state, state.culture_definitions.jingoism);
		auto pdemo_key = pop_demographics_duplicate::to_key(state, state.culture_definitions.jingoism);
		sum_over_single_nation_demographics(state, key, n, [pdemo_key](sys::state const& state, dcon::pop_id p) {
			return state.world.pop_get_demographics(p, pdemo_key) * state.world.pop_get_size(p);
		});
	}

	template<bool full>
	void regenerate_from_pop_data_old(sys::state& state) {
		auto const sz = size(state);
		auto const csz = common_size(state);
		auto const extra_size = sz - csz;
		auto const extra_group_size = (extra_size + extra_demo_grouping - 1) / extra_demo_grouping;

		concurrency::parallel_for(uint32_t(0), full ?  sz : csz + extra_group_size, [&](uint32_t base_index) {
			auto index = base_index;
			if constexpr(!full) {
				if(index >= csz) {
					index += extra_group_size * (state.current_date.value % extra_demo_grouping);
					if(index >= sz) {
						return;
					}
				}
			}
			dcon::demographics_key key{dcon::demographics_key::value_base_t(index)};
			if(index < demographics::count_special_keys) {
				switch(index) {
				case 0: // constexpr inline dcon::demographics_key total(0);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_size(p);
					});
					break;
				case 1: // constexpr inline dcon::demographics_key employable(1);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_has_unemployment(state.world.pop_get_poptype(p)) ? state.world.pop_get_size(p) : 0.0f;
					});
					break;
				case 2: // constexpr inline dcon::demographics_key employed(2);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_employment(p);
					});
					break;
				case 3: // constexpr inline dcon::demographics_key consciousness(3);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_consciousness(p) * state.world.pop_get_size(p);
					});
					break;
				case 4: // constexpr inline dcon::demographics_key militancy(4);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_militancy(p) * state.world.pop_get_size(p);
					});
					break;
				case 5: // constexpr inline dcon::demographics_key literacy(5);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_literacy(p) * state.world.pop_get_size(p);
					});
					break;
				case 6: // constexpr inline dcon::demographics_key political_reform_desire(6);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						if(!state.world.province_get_is_colonial(state.world.pop_get_province_from_pop_location(p))) {
							auto movement = state.world.pop_get_movement_from_pop_movement_membership(p);
							if(movement) {
								auto opt = state.world.movement_get_associated_issue_option(movement);
								auto optpar = state.world.issue_option_get_parent_issue(opt);
								if(opt && state.world.issue_get_issue_type(optpar) == uint8_t(culture::issue_type::political)) {
									return state.world.pop_get_size(p);
								}
							}
						}
						return 0.0f;
					});
					break;
				case 7: // constexpr inline dcon::demographics_key social_reform_desire(7);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						if(!state.world.province_get_is_colonial(state.world.pop_get_province_from_pop_location(p))) {
							auto movement = state.world.pop_get_movement_from_pop_movement_membership(p);
							if(movement) {
								auto opt = state.world.movement_get_associated_issue_option(movement);
								auto optpar = state.world.issue_option_get_parent_issue(opt);
								if(opt && state.world.issue_get_issue_type(optpar) == uint8_t(culture::issue_type::social)) {
									return state.world.pop_get_size(p);
								}
							}
						}
						return 0.0f;
					});
					break;
				case 8: // constexpr inline dcon::demographics_key poor_militancy(8);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::poor)
							? state.world.pop_get_militancy(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 9: // constexpr inline dcon::demographics_key middle_militancy(9);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::middle)
							? state.world.pop_get_militancy(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 10: // constexpr inline dcon::demographics_key rich_militancy(10);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::rich)
							? state.world.pop_get_militancy(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 11: // constexpr inline dcon::demographics_key poor_life_needs(11);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::poor)
							? state.world.pop_get_life_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 12: // constexpr inline dcon::demographics_key middle_life_needs(12);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::middle)
							? state.world.pop_get_life_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 13: // constexpr inline dcon::demographics_key rich_life_needs(13);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::rich)
							? state.world.pop_get_life_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 14: // constexpr inline dcon::demographics_key poor_everyday_needs(14);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::poor)
							? state.world.pop_get_everyday_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 15: // constexpr inline dcon::demographics_key middle_everyday_needs(15);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::middle)
							? state.world.pop_get_everyday_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 16: // constexpr inline dcon::demographics_key rich_everyday_needs(16);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::rich)
							? state.world.pop_get_everyday_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 17: // constexpr inline dcon::demographics_key poor_luxury_needs(17);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::poor)
							? state.world.pop_get_luxury_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 18: // constexpr inline dcon::demographics_key middle_luxury_needs(18);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::middle)
							? state.world.pop_get_luxury_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 19: // constexpr inline dcon::demographics_key rich_luxury_needs(19);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::rich)
							? state.world.pop_get_luxury_needs_satisfaction(p) * state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 20: // constexpr inline dcon::demographics_key poor_total(20);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::poor)
							? state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 21: // constexpr inline dcon::demographics_key middle_total(21);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::middle)
							? state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				case 22: // constexpr inline dcon::demographics_key rich_total(22);
					sum_over_demographics(state, key, [](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_type_get_strata(state.world.pop_get_poptype(p)) == uint8_t(culture::pop_strata::rich)
							? state.world.pop_get_size(p)
							: 0.0f;
					});
					break;
				}
				// common - pop type - employment - culture - ideology - issue option - religion
			} else if(key.index() < to_employment_key(state, dcon::pop_type_id(0)).index()) { // pop type
				dcon::pop_type_id pkey{ dcon::pop_type_id::value_base_t(index - (demographics::count_special_keys)) };
				sum_over_demographics(state, key, [pkey](sys::state const& state, dcon::pop_id p) {
					return state.world.pop_get_poptype(p) == pkey ? state.world.pop_get_size(p) : 0.0f;
				});
			} else if(key.index() < to_key(state, dcon::culture_id(0)).index()) { // employment -- per pop
				dcon::pop_type_id pkey{ dcon::pop_type_id::value_base_t(index - (demographics::count_special_keys + state.world.pop_type_size())) };
				if(state.world.pop_type_get_has_unemployment(pkey)) {
					sum_over_demographics(state, key, [pkey](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_poptype(p) == pkey ? state.world.pop_get_employment(p) : 0.0f;
					});
				} else {
					sum_over_demographics(state, key, [pkey](sys::state const& state, dcon::pop_id p) {
						return state.world.pop_get_poptype(p) == pkey ? state.world.pop_get_size(p) : 0.0f;
					});
				}
			} else if(key.index() < to_key(state, dcon::ideology_id(0)).index()) { // culture
				dcon::culture_id pkey{dcon::culture_id::value_base_t(index - (demographics::count_special_keys + state.world.pop_type_size() * 2)) };
				sum_over_demographics(state, key, [pkey](sys::state const& state, dcon::pop_id p) {
					return state.world.pop_get_culture(p) == pkey ? state.world.pop_get_size(p) : 0.0f;
				});
			} else if(key.index() < to_key(state, dcon::issue_option_id(0)).index()) { // ideology
				dcon::ideology_id pkey{dcon::ideology_id::value_base_t(index - (demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size()))};
				auto pdemo_key = pop_demographics_duplicate::to_key(state, pkey);
				sum_over_demographics(state, key, [pdemo_key](sys::state const& state, dcon::pop_id p) {
					return state.world.pop_get_demographics(p, pdemo_key) * state.world.pop_get_size(p);
				});
			} else if(key.index() < to_key(state, dcon::religion_id(0)).index()) { // issue option
				dcon::issue_option_id pkey{dcon::issue_option_id::value_base_t(index - (demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size() + state.world.ideology_size()))};
				auto pdemo_key = pop_demographics_duplicate::to_key(state, pkey);
				sum_over_demographics(state, key, [pdemo_key](sys::state const& state, dcon::pop_id p) {
					return state.world.pop_get_demographics(p, pdemo_key) * state.world.pop_get_size(p);
				});
			} else  { // religion
				dcon::religion_id pkey{dcon::religion_id::value_base_t(index - (demographics::count_special_keys + state.world.pop_type_size() * 2 + state.world.culture_size() + state.world.ideology_size() + state.world.issue_option_size()))};
				sum_over_demographics(state, key, [pkey](sys::state const& state, dcon::pop_id p) {
					return state.world.pop_get_religion(p) == pkey ? state.world.pop_get_size(p) : 0.0f;
				});
			}
		});

		//
		// calculate values derived from demographics
		//
		concurrency::parallel_for(uint32_t(0), uint32_t(17), [&](uint32_t index) {
			switch(index) {
			case 0: {
				static ve::vectorizable_buffer<float, dcon::province_id> max_buffer = state.world.province_make_vectorizable_float_buffer();
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_culture([&](dcon::culture_id c) {
					auto cids = ve::tagged_vector<dcon::culture_id>(c);
					ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()), [&, k = to_key(state, c)](auto p) {
						auto v = state.world.province_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.province_set_dominant_culture(p, ve::select(mask, cids, state.world.province_get_dominant_culture(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 1: {
				static ve::vectorizable_buffer<float, dcon::state_instance_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.state_instance_size();
				if(new_count > old_count) {
					max_buffer = state.world.state_instance_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_state_instance([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_culture([&](dcon::culture_id c) {
					auto cids = ve::tagged_vector<dcon::culture_id>(c);
					state.world.execute_serial_over_state_instance([&, k = to_key(state, c)](auto p) {
						auto v = state.world.state_instance_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.state_instance_set_dominant_culture(p, ve::select(mask, cids, state.world.state_instance_get_dominant_culture(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 2: {
				static ve::vectorizable_buffer<float, dcon::nation_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.nation_size();
				if(new_count > old_count) {
					max_buffer = state.world.nation_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_nation([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_culture([&](dcon::culture_id c) {
					auto cids = ve::tagged_vector<dcon::culture_id>(c);
					state.world.execute_serial_over_nation([&, k = to_key(state, c)](auto p) {
						auto v = state.world.nation_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.nation_set_dominant_culture(p,
						ve::select(mask, cids, state.world.nation_get_dominant_culture(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 3: {
				static ve::vectorizable_buffer<float, dcon::province_id> max_buffer = state.world.province_make_vectorizable_float_buffer();
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_religion([&](dcon::religion_id c) {
					ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()), [&, k = to_key(state, c)](auto p) {
						auto v = state.world.province_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.province_set_dominant_religion(p,
						ve::select(mask, ve::tagged_vector<dcon::religion_id>(c), state.world.province_get_dominant_religion(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 4: {
				static ve::vectorizable_buffer<float, dcon::state_instance_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.state_instance_size();
				if(new_count > old_count) {
					max_buffer = state.world.state_instance_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_state_instance([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_religion([&](dcon::religion_id c) {
					state.world.execute_serial_over_state_instance([&, k = to_key(state, c)](auto p) {
						auto v = state.world.state_instance_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.state_instance_set_dominant_religion(p,
						ve::select(mask, ve::tagged_vector<dcon::religion_id>(c), state.world.state_instance_get_dominant_religion(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 5: {
				static ve::vectorizable_buffer<float, dcon::nation_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.nation_size();
				if(new_count > old_count) {
					max_buffer = state.world.nation_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_nation([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_religion([&](dcon::religion_id c) {
					state.world.execute_serial_over_nation([&, k = to_key(state, c)](auto p) {
						auto v = state.world.nation_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.nation_set_dominant_religion(p,
						ve::select(mask, ve::tagged_vector<dcon::religion_id>(c), state.world.nation_get_dominant_religion(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 6: {
				static ve::vectorizable_buffer<float, dcon::province_id> max_buffer = state.world.province_make_vectorizable_float_buffer();
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_ideology([&](dcon::ideology_id c) {
					ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()), [&, k = to_key(state, c)](auto p) {
						auto v = state.world.province_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.province_set_dominant_ideology(p,
						ve::select(mask, ve::tagged_vector<dcon::ideology_id>(c), state.world.province_get_dominant_ideology(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 7: {
				static ve::vectorizable_buffer<float, dcon::state_instance_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.state_instance_size();
				if(new_count > old_count) {
					max_buffer = state.world.state_instance_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_state_instance([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_ideology([&](dcon::ideology_id c) {
					state.world.execute_serial_over_state_instance([&, k = to_key(state, c)](auto p) {
						auto v = state.world.state_instance_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.state_instance_set_dominant_ideology(p,
						ve::select(mask, ve::tagged_vector<dcon::ideology_id>(c), state.world.state_instance_get_dominant_ideology(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 8: {
				static ve::vectorizable_buffer<float, dcon::nation_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.nation_size();
				if(new_count > old_count) {
					max_buffer = state.world.nation_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_nation([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_ideology([&](dcon::ideology_id c) {
					state.world.execute_serial_over_nation([&, k = to_key(state, c)](auto p) {
						auto v = state.world.nation_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.nation_set_dominant_ideology(p,
						ve::select(mask, ve::tagged_vector<dcon::ideology_id>(c), state.world.nation_get_dominant_ideology(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 9: {
				static ve::vectorizable_buffer<float, dcon::province_id> max_buffer = state.world.province_make_vectorizable_float_buffer();
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_issue_option([&](dcon::issue_option_id c) {
					ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()), [&, k = to_key(state, c)](auto p) {
						auto v = state.world.province_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.province_set_dominant_issue_option(p,
						ve::select(mask, ve::tagged_vector<dcon::issue_option_id>(c), state.world.province_get_dominant_issue_option(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 10: {
				static ve::vectorizable_buffer<float, dcon::state_instance_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.state_instance_size();
				if(new_count > old_count) {
					max_buffer = state.world.state_instance_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_state_instance([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_issue_option([&](dcon::issue_option_id c) {
					state.world.execute_serial_over_state_instance([&, k = to_key(state, c)](auto p) {
						auto v = state.world.state_instance_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.state_instance_set_dominant_issue_option(p, ve::select(mask, ve::tagged_vector<dcon::issue_option_id>(c), state.world.state_instance_get_dominant_issue_option(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 11: {
				static ve::vectorizable_buffer<float, dcon::nation_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.nation_size();
				if(new_count > old_count) {
					max_buffer = state.world.nation_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_nation([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_issue_option([&](dcon::issue_option_id c) {
					state.world.execute_serial_over_nation([&, k = to_key(state, c)](auto p) {
						auto v = state.world.nation_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.nation_set_dominant_issue_option(p,
						ve::select(mask, ve::tagged_vector<dcon::issue_option_id>(c), state.world.nation_get_dominant_issue_option(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 12: {
				static ve::vectorizable_buffer<float, dcon::pop_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.pop_size();
				if(new_count > old_count) {
					max_buffer = state.world.pop_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_pop([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_issue_option([&](dcon::issue_option_id c) {
					state.world.execute_serial_over_pop([&, k = pop_demographics_duplicate::to_key(state, c)](auto p) {
						auto v = state.world.pop_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.pop_set_dominant_issue_option(p,
						ve::select(mask, ve::tagged_vector<dcon::issue_option_id>(c), state.world.pop_get_dominant_issue_option(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 13: {
				static ve::vectorizable_buffer<float, dcon::pop_id> max_buffer(uint32_t(1));
				static uint32_t old_count = 1;
				auto new_count = state.world.pop_size();
				if(new_count > old_count) {
					max_buffer = state.world.pop_make_vectorizable_float_buffer();
					old_count = new_count;
				}
				state.world.execute_serial_over_pop([&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_ideology([&](dcon::ideology_id c) {
					state.world.execute_serial_over_pop([&, k = pop_demographics_duplicate::to_key(state, c)](auto p) {
						auto v = state.world.pop_get_demographics(p, k);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max;
						state.world.pop_set_dominant_ideology(p,
						ve::select(mask, ve::tagged_vector<dcon::ideology_id>(c), state.world.pop_get_dominant_ideology(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			case 14: {
				// clear nation
				state.world.execute_serial_over_nation(
				[&](auto ni) { state.world.nation_set_non_colonial_population(ni, ve::fp_vector()); });
				// sum in nation
				state.world.for_each_state_instance([&](dcon::state_instance_id s) {
					if(!state.world.province_get_is_colonial(state.world.state_instance_get_capital(s))) {
						auto location = state.world.state_instance_get_nation_from_state_ownership(s);
						state.world.nation_get_non_colonial_population(location) +=
						state.world.state_instance_get_demographics(s, demographics::total);
					}
				});
				break;
			}
			case 15: {
				// clear nation
				state.world.execute_serial_over_nation(
				[&](auto ni) { state.world.nation_set_non_colonial_bureaucrats(ni, ve::fp_vector()); });
				// sum in nation
				state.world.for_each_state_instance(
				[&, k = to_key(state, state.culture_definitions.bureaucrat)](dcon::state_instance_id s) {
					if(!state.world.province_get_is_colonial(state.world.state_instance_get_capital(s))) {
						auto location = state.world.state_instance_get_nation_from_state_ownership(s);
						state.world.nation_get_non_colonial_bureaucrats(location) += state.world.state_instance_get_demographics(s, k);
					}
				});
				break;
			}
			case 16:
			{
				static ve::vectorizable_buffer<float, dcon::province_id> max_buffer = state.world.province_make_vectorizable_float_buffer();
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { state.world.province_set_dominant_accepted_culture(p, dcon::culture_id{}); });
				ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()),
				[&](auto p) { max_buffer.set(p, ve::fp_vector()); });
				state.world.for_each_culture([&](dcon::culture_id c) {
					auto cids = ve::tagged_vector<dcon::culture_id>(c);
					ve::execute_serial<dcon::province_id>(uint32_t(state.province_definitions.first_sea_province.index()), [&, key = to_key(state, c)](auto p) {
						auto v = state.world.province_get_demographics(p, key);
						auto old_max = max_buffer.get(p);
						auto mask = v > old_max && nations::nation_accepts_culture(state, state.world.province_get_nation_from_province_ownership(p), c);
						state.world.province_set_dominant_accepted_culture(p, ve::select(mask, cids, state.world.province_get_dominant_accepted_culture(p)));
						max_buffer.set(p, ve::select(mask, v, old_max));
					});
				});
				break;
			}
			default:
				break;
			}
		});
	}
}

//
// TEST CASES
//
sys::state& load_testing_scenario_file();
TEST_CASE("bench_simdify_demo_part") {
	BENCHMARK_ADVANCED("old-demo33")(Catch::Benchmark::Chronometer meter) {
		auto& state = load_testing_scenario_file();
		// buffers
		auto ln_max = state.world.pop_type_make_vectorizable_float_buffer();
		auto en_max = state.world.pop_type_make_vectorizable_float_buffer();
		auto lx_max = state.world.pop_type_make_vectorizable_float_buffer();
		meter.measure([&] {
			demographics_duplicate::regenerate_from_pop_data_old<false>(state);
		});
	};
	BENCHMARK_ADVANCED("new-demo44")(Catch::Benchmark::Chronometer meter) {
		auto& state = load_testing_scenario_file();
		// buffers
		auto ln_max = state.world.pop_type_make_vectorizable_float_buffer();
		auto en_max = state.world.pop_type_make_vectorizable_float_buffer();
		auto lx_max = state.world.pop_type_make_vectorizable_float_buffer();
		meter.measure([&] {
			demographics::regenerate_from_pop_data_daily(state);
		});
	};
}

TEST_CASE("bench_simdify_demo_full") {
	BENCHMARK_ADVANCED("old-demo1")(Catch::Benchmark::Chronometer meter) {
		auto& state = load_testing_scenario_file();
		meter.measure([&] {
			demographics_duplicate::regenerate_from_pop_data_old<true>(state);
		});
	};
	BENCHMARK_ADVANCED("new-demo2")(Catch::Benchmark::Chronometer meter) {
		auto& state = load_testing_scenario_file();
		meter.measure([&] {
			demographics::regenerate_from_pop_data_full(state);
		});
	};
}


TEST_CASE("bench_simdify_demo_issues") {
	BENCHMARK_ADVANCED("issues-demo1")(Catch::Benchmark::Chronometer meter) {
		auto& state = load_testing_scenario_file();
		// buffers
		static demographics::issues_buffer isbuf(state);
		auto ymd_date = state.current_date.to_ymd(state.start_date);
		auto month_start = sys::year_month_day{ ymd_date.year, ymd_date.month, uint16_t(1) };
		auto next_month_start = ymd_date.month != 12 ? sys::year_month_day{ ymd_date.year, uint16_t(ymd_date.month + 1), uint16_t(1) } : sys::year_month_day{ ymd_date.year + 1, uint16_t(1), uint16_t(1) };
		auto const days_in_month = uint32_t(sys::days_difference(month_start, next_month_start));
		meter.measure([&] {
			auto o = uint32_t(ymd_date.day + 1);
			if(o >= days_in_month)
				o -= days_in_month;
			demographics::update_issues(state, o, days_in_month, isbuf);
		});
	};
}
