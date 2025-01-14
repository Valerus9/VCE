#include "culture.hpp"
#include "dcon.hpp"
#include "demographics.hpp"
#include "element/gui_element_base.hpp"
#include "prng.hpp"
#include "province_templates.hpp"
#include "system/system_state.hpp"
#include "triggers.hpp"
#include "news.hpp"

namespace culture {

	std::string get_tech_category_name(tech_category t) {
		switch(t) {
		case culture::tech_category::army:
			return "army_tech";
		case culture::tech_category::navy:
			return "navy_tech";
		case culture::tech_category::commerce:
			return "commerce_tech";
		case culture::tech_category::culture:
			return "culture_tech";
		case culture::tech_category::industry:
			return "industry_tech";
			//non-vanilla
		case culture::tech_category::military_theory:
			return "military_theory_tech";
		case culture::tech_category::population:
			return "population_tech";
		case culture::tech_category::diplomacy:
			return "diplomacy_tech";
		case culture::tech_category::flavor:
			return "flavor_tech";
		case culture::tech_category::theory:
			return "theory_tech";
		case culture::tech_category::economic:
			return "economic_tech";
		case culture::tech_category::society:
			return "society_tech";
		case culture::tech_category::naval:
			return "naval_tech";
		case culture::tech_category::production:
			return "production_tech";
		case culture::tech_category::first_century:
			return "first_century_tech";
		case culture::tech_category::second_century:
			return "second_century_tech";
		case culture::tech_category::third_century:
			return "third_century_tech";
		case culture::tech_category::army_techs:
			return "army_techs";
		case culture::tech_category::naval_techs:
			return "naval_techs";
		case culture::tech_category::economic_techs:
			return "economic_techs";
		default:
			break;
		}
		return "none";
	}

	void set_default_issue_and_reform_options(sys::state& state) {
		state.world.nation_resize_issues(state.world.issue_size());
		state.world.for_each_issue([&](dcon::issue_id i) {
			auto def_option = state.world.issue_get_options(i)[0];
			state.world.execute_serial_over_nation([&](auto ids) { state.world.nation_set_issues(ids, i, def_option); });
		});

		state.world.nation_resize_reforms(state.world.reform_size());
		state.world.for_each_reform([&](dcon::reform_id i) {
			auto def_option = state.world.reform_get_options(i)[0];
			state.world.execute_serial_over_nation([&](auto ids) { state.world.nation_set_reforms(ids, i, def_option); });
		});
	}

	void clear_existing_tech_effects(sys::state& state) {
		state.world.for_each_province_building_type([&](dcon::province_building_type_id id) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_max_building_level(nation_indices, id, 0);
			});
		});
		state.world.for_each_factory_type([&](dcon::factory_type_id id) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_active_building(nation_indices, id, ve::vbitfield_type{0});
			});
		});
		for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
			dcon::unit_type_id uid = dcon::unit_type_id{ dcon::unit_type_id::value_base_t(i) };
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_active_unit(nation_indices, uid, ve::vbitfield_type{ 0 });
			});
		}
		for(uint32_t i = 0; i < state.culture_definitions.crimes.size(); ++i) {
			dcon::crime_id uid = dcon::crime_id{ dcon::crime_id::value_base_t(i) };
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_active_crime(nation_indices, uid, ve::vbitfield_type{ 0 });
			});
		}

		for(auto cmod : state.world.in_commodity) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_rgo_goods_output(nation_indices, cmod, 0.0f);
			});
		}
		for(auto cmod : state.world.in_commodity) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_factory_goods_output(nation_indices, cmod, 0.0f);
			});
		}
		for(auto cmod : state.world.in_commodity) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_rgo_size(nation_indices, cmod, 0.0f);
			});
		}
		for(auto cmod : state.world.in_commodity) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_factory_goods_throughput(nation_indices, cmod, 0.0f);
			});
		}
		for(auto cmod : state.world.in_rebel_type) {
			state.world.execute_serial_over_nation([&](auto nation_indices) {
				state.world.nation_set_rebel_org_modifier(nation_indices, cmod, 0.0f);
			});
		}
		state.world.execute_serial_over_nation([&](auto nation_indices) {
		state.world.nation_set_has_gas_attack(nation_indices, ve::vbitfield_type{ 0 });
		});
		state.world.execute_serial_over_nation([&](auto nation_indices) {
		state.world.nation_set_has_gas_defense(nation_indices, ve::vbitfield_type{ 0 });
		});
		military::reset_unit_stats(state);
	}

	void repopulate_technology_effects(sys::state& state) {
		state.world.for_each_technology([&](dcon::technology_id t_id) {
			auto tech_id = fatten(state.world, t_id);
			state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
				if(tech_id.get_increase_building(t)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
						auto old_rr_value = state.world.nation_get_max_building_level(nation_indices, t);
						state.world.nation_set_max_building_level(nation_indices, t, ve::select(has_tech_mask, old_rr_value + 1, old_rr_value));
					});
				}
			});
			state.world.for_each_factory_type([&](dcon::factory_type_id id) {
				if(tech_id.get_activate_building(id)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
						auto old_value = state.world.nation_get_active_building(nation_indices, id);
						state.world.nation_set_active_building(nation_indices, id, old_value | has_tech_mask);
					});
				}
			});
			for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
				if(tech_id.get_activate_unit(uid)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
						auto old_value = state.world.nation_get_active_unit(nation_indices, uid);
						state.world.nation_set_active_unit(nation_indices, uid, old_value | has_tech_mask);
					});
				}
			}
			for(auto cmod : tech_id.get_rgo_goods_output()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
					auto old_value = state.world.nation_get_rgo_goods_output(nation_indices, cmod.type);
					state.world.nation_set_rgo_goods_output(nation_indices, cmod.type,
					ve::select(has_tech_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : tech_id.get_factory_goods_output()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
					auto old_value = state.world.nation_get_factory_goods_output(nation_indices, cmod.type);
					state.world.nation_set_factory_goods_output(nation_indices, cmod.type,
					ve::select(has_tech_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : tech_id.get_rgo_size()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_tech_mask = state.world.nation_get_active_technologies(nation_indices, t_id);
					auto old_value = state.world.nation_get_rgo_size(nation_indices, cmod.type);
					state.world.nation_set_rgo_size(nation_indices, cmod.type, ve::select(has_tech_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto& umod : tech_id.get_modified_units()) {
				state.world.for_each_nation([&](dcon::nation_id nid) {
					if(state.world.nation_get_active_technologies(nid, t_id)) {
						state.world.nation_get_unit_stats(nid, umod.type) += umod;
					}
				});
			}
		});
	}

	void repopulate_invention_effects(sys::state& state) {
		state.world.for_each_invention([&](dcon::invention_id i_id) {
			auto inv_id = fatten(state.world, i_id);
			state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
				if(inv_id.get_increase_building(t)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_tech_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
						auto old_rr_value = state.world.nation_get_max_building_level(nation_indices, t);
						state.world.nation_set_max_building_level(nation_indices, t, ve::select(has_tech_mask, old_rr_value + 1, old_rr_value));
					});
				}
			});
			if(inv_id.get_enable_gas_attack()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_has_gas_attack(nation_indices);
					state.world.nation_set_has_gas_attack(nation_indices, old_value | has_inv_mask);
				});
			}
			if(inv_id.get_enable_gas_defense()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_has_gas_defense(nation_indices);
					state.world.nation_set_has_gas_defense(nation_indices, old_value | has_inv_mask);
				});
			}
			state.world.for_each_factory_type([&](dcon::factory_type_id id) {
				if(inv_id.get_activate_building(id)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
						auto old_value = state.world.nation_get_active_building(nation_indices, id);
						state.world.nation_set_active_building(nation_indices, id, old_value | has_inv_mask);
					});
				}
			});
			for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
			dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
				if(inv_id.get_activate_unit(uid)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
						auto old_value = state.world.nation_get_active_unit(nation_indices, uid);
						state.world.nation_set_active_unit(nation_indices, uid, old_value | has_inv_mask);
					});
				}
			}
			for(uint32_t i = 0; i < state.culture_definitions.crimes.size(); ++i) {
			dcon::crime_id uid = dcon::crime_id{dcon::crime_id::value_base_t(i)};
				if(inv_id.get_activate_crime(uid)) {
					state.world.execute_serial_over_nation([&](auto nation_indices) {
						auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
						auto old_value = state.world.nation_get_active_crime(nation_indices, uid);
						state.world.nation_set_active_crime(nation_indices, uid, old_value | has_inv_mask);
					});
				}
			}
			for(auto cmod : inv_id.get_rgo_goods_output()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_rgo_goods_output(nation_indices, cmod.type);
					state.world.nation_set_rgo_goods_output(nation_indices, cmod.type,
					ve::select(has_inv_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : inv_id.get_rgo_size()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_tech_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_rgo_size(nation_indices, cmod.type);
					state.world.nation_set_rgo_size(nation_indices, cmod.type, ve::select(has_tech_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : inv_id.get_factory_goods_output()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_factory_goods_output(nation_indices, cmod.type);
					state.world.nation_set_factory_goods_output(nation_indices, cmod.type,
					ve::select(has_inv_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : inv_id.get_factory_goods_throughput()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					auto old_value = state.world.nation_get_factory_goods_throughput(nation_indices, cmod.type);
					state.world.nation_set_factory_goods_throughput(nation_indices, cmod.type,
					ve::select(has_inv_mask, old_value + cmod.amount, old_value));
				});
			}
			for(auto cmod : inv_id.get_rebel_org()) {
				state.world.execute_serial_over_nation([&](auto nation_indices) {
					auto has_inv_mask = state.world.nation_get_active_inventions(nation_indices, i_id);
					if(cmod.type) {
						auto old_value = state.world.nation_get_rebel_org_modifier(nation_indices, cmod.type);
						state.world.nation_set_rebel_org_modifier(nation_indices, cmod.type,
						ve::select(has_inv_mask, old_value + cmod.amount, old_value));
					} else if(has_inv_mask.v != 0) {
						state.world.for_each_rebel_type([&](dcon::rebel_type_id rt) {
							auto old_value = state.world.nation_get_rebel_org_modifier(nation_indices, rt);
							state.world.nation_set_rebel_org_modifier(nation_indices, rt,
							ve::select(has_inv_mask, old_value + cmod.amount, old_value));
						});
					}
				});
			}
			for(auto& umod : inv_id.get_modified_units()) {
				state.world.for_each_nation([&](dcon::nation_id nid) {
					if(state.world.nation_get_active_inventions(nid, i_id)) {
						auto& existing_stats = state.world.nation_get_unit_stats(nid, umod.type);
						existing_stats += umod;
					}
				});
			}
		});
	}

	void apply_technology(sys::state& state, dcon::nation_id target_nation, dcon::technology_id t_id) {
		auto tech_id = fatten(state.world, t_id);

		state.world.nation_set_active_technologies(target_nation, t_id, true);

		auto tech_mod = tech_id.get_modifier();
		if(tech_mod) {
			auto& tech_nat_values = tech_mod.get_national_values();
			for(uint32_t i = 0; i < sys::national_modifier_definition::modifier_definition_size; ++i) {
				if(!(tech_nat_values.offsets[i]))
				break; // no more modifier values attached to this tech

				auto fixed_offset = tech_nat_values.offsets[i];
				auto modifier_amount = tech_nat_values.values[i];

				state.world.nation_get_modifier_values(target_nation, fixed_offset) += modifier_amount;
			}
		}

		auto& plur = state.world.nation_get_plurality(target_nation);
		plur = std::clamp(plur + tech_id.get_plurality() * 100.0f, 0.0f, 100.0f);

		state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
			if(tech_id.get_increase_building(t)) {
				state.world.nation_get_max_building_level(target_nation, t) += 1;
			}
		});

		state.world.nation_get_permanent_colonial_points(target_nation) += tech_id.get_colonial_points();
		state.world.for_each_factory_type([&](dcon::factory_type_id id) {
			if(tech_id.get_activate_building(id)) {
				state.world.nation_set_active_building(target_nation, id, true);
			}
		});
		for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
		dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
			if(tech_id.get_activate_unit(uid)) {
				state.world.nation_set_active_unit(target_nation, uid, true);
			}
		}

		for(auto cmod : tech_id.get_rgo_goods_output()) {
			state.world.nation_get_rgo_goods_output(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : tech_id.get_factory_goods_output()) {
			state.world.nation_get_factory_goods_output(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : tech_id.get_rgo_size()) {
			state.world.nation_get_rgo_size(target_nation, cmod.type) += cmod.amount;
		}
		for(auto& umod : tech_id.get_modified_units()) {
			if(umod.type == state.military_definitions.base_army_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) += umod;
					}
				}
			} else if(umod.type == state.military_definitions.base_naval_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(!state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) += umod;
					}
				}
			} else {
				state.world.nation_get_unit_stats(target_nation, umod.type) += umod;
			}
		}
	}

	void remove_technology(sys::state& state, dcon::nation_id target_nation, dcon::technology_id t_id) {
		auto tech_id = fatten(state.world, t_id);

		state.world.nation_set_active_technologies(target_nation, t_id, false);

		auto tech_mod = tech_id.get_modifier();
		if(tech_mod) {
			auto& tech_nat_values = tech_mod.get_national_values();
			for(uint32_t i = 0; i < sys::national_modifier_definition::modifier_definition_size; ++i) {
				if(!(tech_nat_values.offsets[i]))
				break; // no more modifier values attached to this tech

				auto fixed_offset = tech_nat_values.offsets[i];
				auto modifier_amount = tech_nat_values.values[i];

				state.world.nation_get_modifier_values(target_nation, fixed_offset) -= modifier_amount;
			}
		}

		auto& plur = state.world.nation_get_plurality(target_nation);
		plur = std::clamp(plur - tech_id.get_plurality() * 100.0f, 0.0f, 100.0f);

		state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
			if(tech_id.get_increase_building(t)) {
				state.world.nation_get_max_building_level(target_nation, t) -= 1;
			}
		});

		state.world.nation_get_permanent_colonial_points(target_nation) -= tech_id.get_colonial_points();
		state.world.for_each_factory_type([&](dcon::factory_type_id id) {
			if(tech_id.get_activate_building(id)) {
				state.world.nation_set_active_building(target_nation, id, false);
			}
		});
		for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
		dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
			if(tech_id.get_activate_unit(uid)) {
				state.world.nation_set_active_unit(target_nation, uid, false);
			}
		}

		for(auto cmod : tech_id.get_rgo_goods_output()) {
			state.world.nation_get_rgo_goods_output(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : tech_id.get_factory_goods_output()) {
			state.world.nation_get_factory_goods_output(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : tech_id.get_rgo_size()) {
			state.world.nation_get_rgo_size(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto& umod : tech_id.get_modified_units()) {
			if(umod.type == state.military_definitions.base_army_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) -= umod;
					}
				}
			} else if(umod.type == state.military_definitions.base_naval_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(!state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) -= umod;
					}
				}
			} else {
				state.world.nation_get_unit_stats(target_nation, umod.type) -= umod;
			}
		}
	}

	void apply_invention(sys::state& state, dcon::nation_id target_nation, dcon::invention_id i_id) { //  TODO: shared prestige effect
		auto inv_id = fatten(state.world, i_id);

		state.world.nation_set_active_inventions(target_nation, i_id, true);

		// apply modifiers from active inventions
		auto inv_mod = inv_id.get_modifier();
		if(inv_mod) {
			auto& inv_nat_values = inv_mod.get_national_values();
			for(uint32_t i = 0; i < sys::national_modifier_definition::modifier_definition_size; ++i) {
				if(!(inv_nat_values.offsets[i]))
				break; // no more modifier values attached to this tech

				auto fixed_offset = inv_nat_values.offsets[i];
				auto modifier_amount = inv_nat_values.values[i];

				state.world.nation_get_modifier_values(target_nation, fixed_offset) += modifier_amount;
			}
		}

		state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
			if(inv_id.get_increase_building(t)) {
				state.world.nation_get_max_building_level(target_nation, t) += 1;
			}
		});

		state.world.nation_get_permanent_colonial_points(target_nation) += inv_id.get_colonial_points();
		if(inv_id.get_enable_gas_attack()) {
			state.world.nation_set_has_gas_attack(target_nation, true);
		}
		if(inv_id.get_enable_gas_defense()) {
			state.world.nation_set_has_gas_defense(target_nation, true);
		}

		auto& plur = state.world.nation_get_plurality(target_nation);
		plur = std::clamp(plur + inv_id.get_plurality() * 100.0f, 0.0f, 100.0f);

		state.world.for_each_factory_type([&](dcon::factory_type_id id) {
			if(inv_id.get_activate_building(id)) {
				state.world.nation_set_active_building(target_nation, id, true);
			}
		});
		for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
		dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
			if(inv_id.get_activate_unit(uid)) {
				state.world.nation_set_active_unit(target_nation, uid, true);
			}
		}
		for(uint32_t i = 0; i < state.culture_definitions.crimes.size(); ++i) {
		dcon::crime_id uid = dcon::crime_id{dcon::crime_id::value_base_t(i)};
			if(inv_id.get_activate_crime(uid)) {
				state.world.nation_set_active_crime(target_nation, uid, true);
			}
		}

		for(auto cmod : inv_id.get_rgo_goods_output()) {
			state.world.nation_get_rgo_goods_output(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : inv_id.get_rgo_size()) {
			state.world.nation_get_rgo_size(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : inv_id.get_factory_goods_output()) {
			state.world.nation_get_factory_goods_output(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : inv_id.get_factory_goods_throughput()) {
			state.world.nation_get_factory_goods_throughput(target_nation, cmod.type) += cmod.amount;
		}
		for(auto cmod : inv_id.get_rebel_org()) {
			if(cmod.type) {
				state.world.nation_get_rebel_org_modifier(target_nation, cmod.type) += cmod.amount;
			} else {
				state.world.for_each_rebel_type(
					[&](dcon::rebel_type_id rt) { state.world.nation_get_rebel_org_modifier(target_nation, rt) += cmod.amount; });
			}
		}
		for(auto& umod : inv_id.get_modified_units()) {
			if(umod.type == state.military_definitions.base_army_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) += umod;
					}
				}
			} else if(umod.type == state.military_definitions.base_naval_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(!state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) += umod;
					}
				}
			} else {
				state.world.nation_get_unit_stats(target_nation, umod.type) += umod;
			}
		}

		if(auto p = inv_id.get_shared_prestige(); p > 0) {
			int32_t total = 0;
			for(auto n : state.world.in_nation) {
				if(n.get_active_inventions(i_id)) {
					++total;
				}
			}
			nations::adjust_prestige(state, target_nation, p / float(total));
		}
	}

	void remove_invention(sys::state& state, dcon::nation_id target_nation,
		dcon::invention_id i_id) { //  TODO: shared prestige effect
		auto inv_id = fatten(state.world, i_id);

		state.world.nation_set_active_inventions(target_nation, i_id, false);

		// apply modifiers from active inventions
		auto inv_mod = inv_id.get_modifier();
		if(inv_mod) {
			auto& inv_nat_values = inv_mod.get_national_values();
			for(uint32_t i = 0; i < sys::national_modifier_definition::modifier_definition_size; ++i) {
				if(!(inv_nat_values.offsets[i]))
				break; // no more modifier values attached to this tech

				auto fixed_offset = inv_nat_values.offsets[i];
				auto modifier_amount = inv_nat_values.values[i];

				state.world.nation_get_modifier_values(target_nation, fixed_offset) -= modifier_amount;
			}
		}

		state.world.for_each_province_building_type([&](dcon::province_building_type_id t) {
			if(inv_id.get_increase_building(t)) {
				state.world.nation_get_max_building_level(target_nation, t) -= 1;
			}
		});

		state.world.nation_get_permanent_colonial_points(target_nation) -= inv_id.get_colonial_points();
		if(inv_id.get_enable_gas_attack()) {
			state.world.nation_set_has_gas_attack(target_nation, false);
		}
		if(inv_id.get_enable_gas_defense()) {
			state.world.nation_set_has_gas_defense(target_nation, false);
		}

		auto& plur = state.world.nation_get_plurality(target_nation);
		plur = std::clamp(plur - inv_id.get_plurality() * 100.0f, 0.0f, 100.0f);

		state.world.for_each_factory_type([&](dcon::factory_type_id id) {
			if(inv_id.get_activate_building(id)) {
				state.world.nation_set_active_building(target_nation, id, false);
			}
		});
		for(uint32_t i = 0; i < state.military_definitions.unit_base_definitions.size(); ++i) {
		dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
			if(inv_id.get_activate_unit(uid)) {
				state.world.nation_set_active_unit(target_nation, uid, false);
			}
		}
		for(uint32_t i = 0; i < state.culture_definitions.crimes.size(); ++i) {
		dcon::crime_id uid = dcon::crime_id{dcon::crime_id::value_base_t(i)};
			if(inv_id.get_activate_crime(uid)) {
				state.world.nation_set_active_crime(target_nation, uid, false);
			}
		}

		for(auto cmod : inv_id.get_rgo_goods_output()) {
			state.world.nation_get_rgo_goods_output(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : inv_id.get_rgo_size()) {
			state.world.nation_get_rgo_size(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : inv_id.get_factory_goods_output()) {
			state.world.nation_get_factory_goods_output(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : inv_id.get_factory_goods_throughput()) {
			state.world.nation_get_factory_goods_throughput(target_nation, cmod.type) -= cmod.amount;
		}
		for(auto cmod : inv_id.get_rebel_org()) {
			if(cmod.type) {
				state.world.nation_get_rebel_org_modifier(target_nation, cmod.type) -= cmod.amount;
			} else {
				state.world.for_each_rebel_type(
					[&](dcon::rebel_type_id rt) { state.world.nation_get_rebel_org_modifier(target_nation, rt) -= cmod.amount; });
			}
		}
		for(auto& umod : inv_id.get_modified_units()) {
			if(umod.type == state.military_definitions.base_army_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) -= umod;
					}
				}
			} else if(umod.type == state.military_definitions.base_naval_unit) {
				for(uint32_t i = 2; i < state.military_definitions.unit_base_definitions.size(); ++i) {
				dcon::unit_type_id uid = dcon::unit_type_id{dcon::unit_type_id::value_base_t(i)};
					if(!state.military_definitions.unit_base_definitions[uid].is_land) {
						state.world.nation_get_unit_stats(target_nation, uid) -= umod;
					}
				}
			} else {
				state.world.nation_get_unit_stats(target_nation, umod.type) -= umod;
			}
		}

		if(auto p = inv_id.get_shared_prestige(); p > 0) {
			int32_t total = 0;
			for(auto n : state.world.in_nation) {
				if(n.get_active_inventions(i_id)) {
					++total;
				}
			}
			nations::adjust_prestige(state, target_nation, -(p / float(total + 1)));
		}
	}

	dcon::flag_type_id get_current_flag_type(sys::state& state, dcon::nation_id n) {
		// scripted goverment flags
		auto const nid = state.world.nation_get_identity_from_identity_holder(n);
		if(auto const p = state.world.national_identity_get_scripted_flag_type(nid); p.size() > 0) {
			for(const auto sft : p) {
				if(trigger::evaluate(state, sft.trigger, trigger::to_generic(n), trigger::to_generic(n), -1)) {
					return sft.flag_type;
				}
			}
		}
		if(state.world.nation_get_owned_province_count(n) > 0) {
			auto const gov = state.world.nation_get_government_type(n);
			if(gov) {
				// identity specific flag type?
				auto const ft = state.world.national_identity_get_government_flag_type(nid, gov);
				return ft ? ft : state.world.government_type_get_flag_type(gov);
			}
		}
		return dcon::flag_type_id{};
	}

	dcon::flag_type_id get_current_flag_type(sys::state& state, dcon::national_identity_id nid) {
		auto const n = state.world.national_identity_get_nation_from_identity_holder(nid);
		// scripted goverment flags
		if(auto const p = state.world.national_identity_get_scripted_flag_type(nid); p.size() > 0) {
			for(const auto sft : p) {
				if(trigger::evaluate(state, sft.trigger, trigger::to_generic(n), trigger::to_generic(n), -1)) {
					return sft.flag_type;
				}
			}
		}
		return n ? get_current_flag_type(state, n) : dcon::flag_type_id{};
	}
	void fix_slaves_in_province(sys::state& state, dcon::nation_id owner, dcon::province_id p) {
		auto rules = state.world.nation_get_combined_issue_rules(owner);
		if(!owner || (rules & issue_rule::slavery_allowed) == 0) {
			state.world.province_set_is_slave(p, false);
			bool mine = state.world.commodity_get_is_mine(state.world.province_get_rgo(p));
			for(auto pop : state.world.province_get_pop_location(p)) {
				if(pop.get_pop().get_poptype() == state.culture_definitions.slaves) {
					pop.get_pop().set_poptype(mine ? state.culture_definitions.laborers : state.culture_definitions.farmers);
				}
			}
		} else if(state.world.province_get_is_slave(p) == false) { // conversely, could become a slave state if slaves are found
			bool found_slave = false;
			for(auto pop : state.world.province_get_pop_location(p)) {
				if(pop.get_pop().get_poptype() == state.culture_definitions.slaves) {
					found_slave = true;
					break;
				}
			}
			if(found_slave) {
				province::for_each_province_in_state_instance(state, state.world.province_get_state_membership(p), [&](dcon::province_id p2) {
					state.world.province_set_is_slave(p2, true);
				});
			}
		}
	}

	void update_nation_issue_rules(sys::state& state, dcon::nation_id n_id) {
		auto old_rules = state.world.nation_get_combined_issue_rules(n_id);
		uint32_t combined = 0;
		state.world.for_each_issue([&](dcon::issue_id i_id) {
			auto current_opt = state.world.nation_get_issues(n_id, i_id);
			auto rules_for_opt = state.world.issue_option_get_rules(current_opt);
			combined |= rules_for_opt;
		});
		state.world.for_each_reform([&](dcon::reform_id i_id) {
			auto current_opt = state.world.nation_get_reforms(n_id, i_id);
			auto rules_for_opt = state.world.reform_option_get_rules(current_opt);
			combined |= rules_for_opt;
		});
		state.world.nation_set_combined_issue_rules(n_id, combined);

		if((old_rules & issue_rule::slavery_allowed) != 0 && (combined & issue_rule::slavery_allowed) == 0) {

			for(auto p : state.world.nation_get_province_ownership(n_id)) {
				state.world.province_set_is_slave(p.get_province(), false);
				bool mine = state.world.commodity_get_is_mine(state.world.province_get_rgo(p.get_province()));
				for(auto pop : state.world.province_get_pop_location(p.get_province())) {
					if(pop.get_pop().get_poptype() == state.culture_definitions.slaves) {
						pop.get_pop().set_poptype(mine ? state.culture_definitions.laborers : state.culture_definitions.farmers);
					}
				}
			}
		}
		if((old_rules & issue_rule::can_subsidise) != 0 && (combined & issue_rule::can_subsidise) == 0) {
			for(auto p : state.world.nation_get_province_ownership(n_id)) {
				for(auto f : p.get_province().get_factory_location()) {
					f.get_factory().set_subsidized(false);
				}
			}
		}
	}
	void update_all_nations_issue_rules(sys::state& state) {
		state.world.execute_serial_over_nation([&](auto n_id) {
			ve::int_vector combined;
			state.world.for_each_issue([&](dcon::issue_id i_id) {
				auto current_opt = state.world.nation_get_issues(n_id, i_id);
				auto rules_for_opt = state.world.issue_option_get_rules(current_opt);
				combined = combined | rules_for_opt;
			});
			state.world.for_each_reform([&](dcon::reform_id i_id) {
				auto current_opt = state.world.nation_get_reforms(n_id, i_id);
				auto rules_for_opt = state.world.reform_option_get_rules(current_opt);
				combined = combined | rules_for_opt;
			});
			state.world.nation_set_combined_issue_rules(n_id, combined);
		});
	}

	void restore_unsaved_values(sys::state& state) {
		state.world.for_each_pop([&state](dcon::pop_id pid) {
			float total = 0.0f;
			float pol_sup = 0.0f;
			float soc_sup = 0.0f;
			state.world.for_each_issue_option([&](dcon::issue_option_id i) {
				auto sup = state.world.pop_get_demographics(pid, pop_demographics::to_key(state, i));
				total += sup;
				auto par = state.world.issue_option_get_parent_issue(i);
				if(state.world.issue_get_issue_type(par) == uint8_t(culture::issue_type::political)) {
					pol_sup += sup;
				} else if(state.world.issue_get_issue_type(par) == uint8_t(culture::issue_type::social)) {
					soc_sup += sup;
				}
			});
			if(total > 0) {
				state.world.pop_set_political_reform_desire(pid, pol_sup / total);
				state.world.pop_set_social_reform_desire(pid, soc_sup / total);
			}
		});
	}

	void create_initial_ideology_and_issues_distribution(sys::state& state) {
		state.world.for_each_pop([&state](dcon::pop_id pid) {
			auto ptype = state.world.pop_get_poptype(pid);
			auto owner = nations::owner_of_pop(state, pid);
			auto psize = state.world.pop_get_size(pid);
			if(psize <= 0) {
				return;
			}

			{ // ideologies
				auto buf = state.world.ideology_make_vectorizable_float_buffer();
				float total = 0.0f;
				state.world.for_each_ideology([&](dcon::ideology_id iid) {
					buf.set(iid, 0.0f);
					if(state.world.ideology_get_enabled(iid) && (!state.world.ideology_get_is_civilized_only(iid) || state.world.nation_get_is_civilized(owner))) {
						if(auto ptrigger = state.world.pop_type_get_ideology(ptype, iid); ptrigger) {
							auto amount = trigger::evaluate_multiplicative_modifier(state, ptrigger, trigger::to_generic(pid), trigger::to_generic(pid), 0);
							buf.set(iid, amount);
							total += amount;
						}
					}
				});
				if(total > 0.f) {
					float adjustment_factor = 1.0f / total;
					state.world.for_each_ideology([&state, &buf, pid, adjustment_factor](dcon::ideology_id iid) {
						auto normalized_amount = buf.get(iid) * adjustment_factor;
						state.world.pop_set_demographics(pid, pop_demographics::to_key(state, iid), normalized_amount);
					});
				}
			}
			{ // issues
				auto buf = state.world.issue_option_make_vectorizable_float_buffer();
				float total = 0.0f;
				state.world.for_each_issue_option([&](dcon::issue_option_id iid) {
					auto opt = fatten(state.world, iid);
					auto allow = opt.get_allow();
					auto parent_issue = opt.get_parent_issue();
					auto co = state.world.nation_get_issues(owner, parent_issue);
					buf.set(iid, 0.0f);
					if((state.world.nation_get_is_civilized(owner) || state.world.issue_get_issue_type(parent_issue) == uint8_t(issue_type::party))
					&& (state.world.issue_get_is_next_step_only(parent_issue) == false || co.id.index() == iid.index() || co.id.index() + 1 == iid.index() || co.id.index() - 1 == iid.index())) {
						if(auto mtrigger = state.world.pop_type_get_issues(ptype, iid); mtrigger) {
							auto amount = trigger::evaluate_multiplicative_modifier(state, mtrigger, trigger::to_generic(pid), trigger::to_generic(pid), 0);
							buf.set(iid, amount);
							total += amount;
						}
					}
				});
				if(total > 0.f) {
					float adjustment_factor = 1.0f / total;
					state.world.for_each_issue_option([&state, &buf, pid, adjustment_factor](dcon::issue_option_id iid) {
						auto normalized_amount = buf.get(iid) * adjustment_factor;
						state.world.pop_set_demographics(pid, pop_demographics::to_key(state, iid), normalized_amount);
					});
				}
			}
		});
	}

	float effective_technology_cost(sys::state& state, uint32_t current_year, dcon::nation_id target_nation,
		dcon::technology_id tech_id) {
		/*
		The effective amount of research points a tech costs = base-cost x 0v(1 - (current-year - tech-availability-year) /
		define:TECH_YEAR_SPAN) x define:TECH_FACTOR_VASSAL(if your overlord has the tech) / (1 + tech-category-research-modifier)
		*/
		auto base_cost = state.world.technology_get_cost(tech_id);
		auto availability_year = state.world.technology_get_year(tech_id);
		auto folder = state.world.technology_get_folder_index(tech_id);
		auto category = state.culture_definitions.tech_folders[folder].category;
		auto research_mod = [&]() {
			switch(category) {
			case tech_category::army:
				return state.world.nation_get_modifier_values(target_nation, sys::national_mod_offsets::army_tech_research_bonus) + 1.0f;
			case tech_category::navy:
				return state.world.nation_get_modifier_values(target_nation, sys::national_mod_offsets::navy_tech_research_bonus) + 1.0f;
			case tech_category::commerce:
				return state.world.nation_get_modifier_values(target_nation, sys::national_mod_offsets::commerce_tech_research_bonus) + 1.0f;
			case tech_category::culture:
				return state.world.nation_get_modifier_values(target_nation, sys::national_mod_offsets::culture_tech_research_bonus) + 1.0f;
			case tech_category::industry:
				return state.world.nation_get_modifier_values(target_nation, sys::national_mod_offsets::industry_tech_research_bonus) + 1.0f;
				//non vanilla
			// TODO: economic, society, naval, production, first_century, second_century, third_century
			default:
				return 1.0f;
			}
		}();
		auto ol_mod = state.world.nation_get_active_technologies(
										state.world.overlord_get_ruler(state.world.nation_get_overlord_as_subject(target_nation)), tech_id)
										? state.defines.tech_factor_vassal
										: 1.0f;
		return float(base_cost) * ol_mod * (1.0f / research_mod) *
				 (1.0f - std::max(0.0f, float(int32_t(current_year) - availability_year) / state.defines.tech_year_span));
	}

	dcon::technology_id previous_folder_technology(sys::state& state, dcon::technology_id tid) {
		// Find previous technology before this one
		dcon::technology_id prev_tech = dcon::technology_id(dcon::technology_id::value_base_t(tid.index() - 1));
		// Previous technology is from the same folder so we have to check that we have researched it beforehand
		if(tid.index() != 0
		&& state.world.technology_get_folder_index(prev_tech) == state.world.technology_get_folder_index(tid)) {
			return prev_tech;
		}
		return dcon::technology_id{}; // First technology on folder can always be researched
	}

	void update_research(sys::state& state, uint32_t current_year) {
		for(auto n : state.world.in_nation) {
			if(n.get_owned_province_count() != 0 && n.get_current_research()) {
				if(n.get_active_technologies(n.get_current_research())) {
					n.set_current_research(dcon::technology_id{});
				} else {
					auto cost = effective_technology_cost(state, current_year, n, n.get_current_research());
					if(n.get_research_points() >= cost) {
						n.get_research_points() -= cost;
						apply_technology(state, n, n.get_current_research());

						notification::post(state, notification::message{
							[t = n.get_current_research()](sys::state& state, text::layout_base& contents) {
								text::add_line(state, contents, "msg_tech_1", text::variable_type::x, state.world.technology_get_name(t));
								ui::technology_description(state, contents, t);
							},
							"msg_tech_title",
							n, dcon::nation_id{}, dcon::nation_id{},
							sys::message_base_type::tech
						});

						news::news_scope scope;
						scope.type = news::news_generator_type::research_complete;
						scope.tags[0][0] = state.world.nation_get_identity_from_identity_holder(n);
						scope.strings[0][0] = state.world.technology_get_name(n.get_current_research());
						scope.strings[0][1] = state.world.technology_get_name(n.get_current_research());
						scope.dates[0][0] = state.current_date;
						news::collect_news_scope(state, scope);

						n.set_current_research(dcon::technology_id{});
					}
				}
			}
		}
	}

	void discover_inventions(sys::state& state) {
		/*
		Inventions have a chance to be discovered on the 1st of every month. The invention chance modifier is computed additively, and
		the result is the chance out of 100 that the invention will be discovered. When an invention with shared prestige is
		discovered, the discoverer gains that amount of shared prestige / the number of times it has been discovered (including the
		current time).
		*/
		for(auto inv : state.world.in_invention) {
			auto lim = inv.get_limit();
			auto odds = inv.get_chance();
			if(lim) {
				ve::execute_serial_fast<dcon::nation_id>(state.world.nation_size(), [&](auto nids) {
					auto may_discover = !state.world.nation_get_active_inventions(nids, inv)
						&& (state.world.nation_get_owned_province_count(nids) != 0)
						&& trigger::evaluate(state, lim, trigger::to_generic(nids), trigger::to_generic(nids), 0);

					if(ve::compress_mask(may_discover).v != 0) {
						auto chances = odds
							? trigger::evaluate_additive_modifier(state, odds, trigger::to_generic(nids), trigger::to_generic(nids), 0)
							: 1.f;
						ve::apply([&](dcon::nation_id n, float chance, bool allow_discovery) {
							if(allow_discovery) {
								auto random = rng::get_random(state, uint32_t(inv.id.index()) << 5 ^ uint32_t(n.index()));
								if(int32_t(random % 100) < int32_t(chance)) {
									apply_invention(state, n, inv);

									notification::post(state, notification::message{
										[inv](sys::state& state, text::layout_base& contents) {
											text::substitution_map m;
											text::add_to_substitution_map(m, text::variable_type::x, state.world.invention_get_name(inv));
											auto resolved = text::resolve_string_substitution(state, "msg_inv_1", m);
											auto box = text::open_layout_box(contents);
											text::add_unparsed_text_to_layout_box(state, contents, box, resolved);
											text::close_layout_box(contents, box);
											ui::invention_description(state, contents, inv, 0);
										},
										"msg_inv_title",
										n, dcon::nation_id{}, dcon::nation_id{},
										sys::message_base_type::invention
									});
									news::news_scope scope;
									scope.type = news::news_generator_type::invention;
									scope.tags[0][0] = state.world.nation_get_identity_from_identity_holder(n);
									scope.strings[0][0] = state.world.invention_get_name(inv);
									scope.strings[0][1] = state.world.invention_get_name(inv);
									scope.dates[0][0] = state.current_date;
									news::collect_news_scope(state, scope);
								}
							}
						}, nids, chances, may_discover);
					}
				});
			} else {
				ve::execute_serial_fast<dcon::nation_id>(state.world.nation_size(), [&](auto nids) {
					auto may_not_discover =
						state.world.nation_get_active_inventions(nids, inv) || (state.world.nation_get_owned_province_count(nids) == 0);
					if(ve::compress_mask(may_not_discover).v != 0) {
						auto chances = odds
							? trigger::evaluate_additive_modifier(state, odds, trigger::to_generic(nids), trigger::to_generic(nids), 0)
							: 1.f;
						ve::apply([&](dcon::nation_id n, float chance, bool block_discovery) {
							if(!block_discovery) {
								auto random = rng::get_random(state, uint32_t(inv.id.index()) << 5 ^ uint32_t(n.index()));
								if(int32_t(random % 100) < int32_t(chance)) {
									apply_invention(state, n, inv);

									notification::post(state, notification::message{
										[inv](sys::state& state, text::layout_base& contents) {
											text::add_line(state, contents, "msg_inv_1", text::variable_type::x, state.world.invention_get_name(inv));
											ui::invention_description(state, contents, inv, 0);
										},
										"msg_inv_title",
										n, dcon::nation_id{}, dcon::nation_id{},
										sys::message_base_type::invention
									});
									news::news_scope scope;
									scope.type = news::news_generator_type::invention;
									scope.tags[0][0] = state.world.nation_get_identity_from_identity_holder(n);
									scope.strings[0][0] = state.world.invention_get_name(inv);
									scope.strings[0][1] = state.world.invention_get_name(inv);
									scope.dates[0][0] = state.current_date;
									news::collect_news_scope(state, scope);
								}
							}
						}, nids, chances, may_not_discover);
					}
				});
			}
		}
	}

	void replace_cores(sys::state& state, dcon::national_identity_id old_tag, dcon::national_identity_id new_tag) {
		if(new_tag) {
			for(auto cores_of : state.world.national_identity_get_core(old_tag)) {
				state.world.try_create_core(cores_of.get_province(), new_tag);
			}
		}
		auto core_list = state.world.national_identity_get_core(old_tag);
		while(core_list.begin() != core_list.end()) {
			state.world.delete_core((*core_list.begin()).id);
		}
	}

} // namespace culture
