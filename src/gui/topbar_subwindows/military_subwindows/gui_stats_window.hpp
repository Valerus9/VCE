#pragma once

#include "element/gui_element_types.hpp"

namespace ui {

	class statswin_warexhaustion : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			auto fat = dcon::fatten(state.world, n);
			return (text::format_float(fat.get_war_exhaustion()) + "/" + text::format_float(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_war_exhaustion)));
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::war_exhaustion, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_war_exhaustion, true);
		}
	};

	class statswin_supplyconsumption : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::supply_consumption) + 1.0f);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::supply_consumption, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::supply_limit, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::supply_range, true);
		}
	};

	class statswin_orgregain : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::org_regain) + 1.0f);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::org_regain, false);
		}
	};

	class statswin_armyorg : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::land_organisation) + 1.0f);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::land_organisation, false);
		}
	};

	class statswin_navyorg : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::naval_organisation) + 1.0f);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::naval_organisation, false);
		}
	};

	class statswin_unitexperience : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			auto r_exp = state.world.nation_get_modifier_values(n, sys::national_mod_offsets::regular_experience_level);
			auto l_exp = state.world.nation_get_modifier_values(n, sys::national_mod_offsets::land_unit_start_experience);
			auto n_exp = state.world.nation_get_modifier_values(n, sys::national_mod_offsets::naval_unit_start_experience);
			return text::format_float(r_exp + l_exp) + "/" + text::format_float(r_exp + n_exp);
		}
		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::regular_experience_level, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::land_unit_start_experience, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::naval_unit_start_experience, true);
		}
	};

	class statswin_recruittime : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::reinforce_speed) + 1.0f);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::reinforce_speed, false);
		}
	};

	class statswin_combatwidth : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return std::to_string(int16_t(state.defines.base_combat_width + int16_t(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::combat_width))));
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::combat_width, false);
		}
	};

	class statswin_digincap : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return std::to_string(int16_t(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::dig_in_cap)));
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::dig_in_cap, false);
		}
	};

	class statswin_tactics : public simple_text_element_base {
		protected:
		std::string get_text(sys::state& state, dcon::nation_id n) noexcept {
			return text::format_percentage(state.world.nation_get_modifier_values(n, sys::national_mod_offsets::military_tactics) + state.defines.base_military_tactics);
		}

		public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, get_text(state, state.local_player_nation));
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::military_tactics, false);
		}
	};

	class stats_window : public window_element_base {
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "war_exhaustion_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "war_exhaustion_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "supply_consumption_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "supply_consumption_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "org_regain_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "org_regain_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "army_org_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "army_org_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "navy_org_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "navy_org_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "unit_experience_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "unit_experience_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "recruit_time_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "recruit_time_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "combat_width_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "combat_width_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "digin_cap_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "digin_cap_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "tactics_level_icon") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "tactics_level_desc") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "war_exhaustion") {
				return make_element_by_type<statswin_warexhaustion>(state, id);
			} else if(name == "supply_consumption") {
				return make_element_by_type<statswin_supplyconsumption>(state, id);
			} else if(name == "org_regain") {
				return make_element_by_type<statswin_orgregain>(state, id);
			} else if(name == "army_org") {
				return make_element_by_type<statswin_armyorg>(state, id);
			} else if(name == "navy_org") {
				return make_element_by_type<statswin_navyorg>(state, id);
			} else if(name == "unit_experience") {
				return make_element_by_type<statswin_unitexperience>(state, id);
			} else if(name == "recruit_time") {
				return make_element_by_type<statswin_recruittime>(state, id);
			} else if(name == "combat_width") {
				return make_element_by_type<statswin_combatwidth>(state, id);
			} else if(name == "digin_cap") {
				return make_element_by_type<statswin_digincap>(state, id);
			} else if(name == "tactics_level") {
				return make_element_by_type<statswin_tactics>(state, id);
			} else {
				return nullptr;
			}
		}
	};

} // namespace ui
