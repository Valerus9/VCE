#pragma once

#include "gui_common_elements.hpp"
#include "element/gui_element_types.hpp"
#include "gui_unit_panel_subwindow.hpp"
#include "text.hpp"
#include "prng.hpp"
#include "tooltip/gui_leader_tooltip.hpp"
#include "gui_leader_select.hpp"
#include "gui_unit_grid_box.hpp"
#include "pdqsort.h"

namespace ui {

enum class unitpanel_action : uint8_t { close, reorg, split, disband, changeleader, temp };

	class unit_selection_close_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
		send(state, parent, element_selection_wrapper<unitpanel_action>{unitpanel_action{ unitpanel_action::close }});
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "deselect_unit");
		}
	};

	class unit_selection_new_unit_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
		send(state, parent, element_selection_wrapper<unitpanel_action>{unitpanel_action::reorg});
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "new_unit");
		}
	};

	template<class T>
	class unit_selection_split_in_half_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				command::evenly_split_army(state, state.local_player_nation, content);
			} else {
				command::evenly_split_navy(state, state.local_player_nation, content);
			}
			state.select(content); //deselect original
		}

		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				disabled = !command::can_evenly_split_army(state, state.local_player_nation, content);
			} else {
				disabled = !command::can_evenly_split_navy(state, state.local_player_nation, content);
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "splitinhalf");
		}
	};

	template<class T>
	class unit_selection_disband_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				command::delete_army(state, state.local_player_nation, content);
			} else {
				command::delete_navy(state, state.local_player_nation, content);
			}
		send(state, parent, element_selection_wrapper<unitpanel_action>{unitpanel_action{ unitpanel_action::close }});
		}

		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				disabled = !command::can_delete_army(state, state.local_player_nation, content);
			} else {
				disabled = !command::can_delete_navy(state, state.local_player_nation, content);
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "disband_unit");
		}
	};

	class unit_selection_disband_too_small_button : public tinted_button_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			disabled = !command::can_disband_undermanned_regiments(state, state.local_player_nation, retrieve<dcon::army_id>(state, parent));
			color = sys::pack_color(255, 196, 196);
			if(state.user_settings.color_blind_mode == sys::color_blind_mode::deutan || state.user_settings.color_blind_mode == sys::color_blind_mode::protan) {
				color = sys::pack_color(255, 255, 255); //remap to blue
			}
		}
		void button_action(sys::state& state) noexcept override {
			 command::disband_undermanned_regiments(state, state.local_player_nation, retrieve<dcon::army_id>(state, parent));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "disband_too_small_unit");
		}
	};

	template<typename T>
	class unit_selection_unit_name_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			set_text(state, std::string(state.to_string_view(dcon::fatten(state.world, content).get_name())));
		}
	};

	template<typename T>
	class unit_selection_leader_name : public simple_text_element_base {
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				auto fat = dcon::fatten(state.world, content);
				set_text(state, std::string(state.to_string_view(fat.get_general_from_army_leadership().get_name())));
			} else {
				auto fat = dcon::fatten(state.world, content);
				set_text(state, std::string(state.to_string_view(fat.get_admiral_from_navy_leadership().get_name())));
			}
		}
	};

	template<class T>
	class unit_selection_change_leader_button : public button_element_base {
		public:

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return  tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto unit = retrieve<T>(state, parent);
			dcon::leader_id lid;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				lid = state.world.army_get_general_from_army_leadership(unit);
			} else {
				lid = state.world.navy_get_admiral_from_navy_leadership(unit);
			}
			if(lid)
			display_leader_full(state, lid, contents, 0);
		}
	

		void button_action(sys::state& state) noexcept override {
			auto unit = retrieve<T>(state, parent);
			auto location = get_absolute_non_mirror_location(state, *this);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				if(command::can_change_general(state, state.local_player_nation, unit, dcon::leader_id{}))
					open_leader_selection(state, unit, dcon::navy_id{}, location.x, location.y);
			} else {
				if(command::can_change_admiral(state, state.local_player_nation, unit, dcon::leader_id{}))
					open_leader_selection(state, dcon::army_id{}, unit, location.x, location.y);
			}
		}
		void button_right_action(sys::state& state) noexcept override {
			auto unit = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				command::change_general(state, state.local_player_nation, unit, dcon::leader_id{});
			} else {
				command::change_admiral(state, state.local_player_nation, unit, dcon::leader_id{});
			}
		}
	};

	template<class T>
	class unit_selection_leader_image : public button_element_base {
		public:
		dcon::gfx_object_id default_img;

		void on_update(sys::state& state) noexcept override {
			if(!default_img) {
				if(base_data.get_element_type() == ui::element_type::image)
				default_img = base_data.data.image.gfx_object;
				else if(base_data.get_element_type() == ui::element_type::button)
				default_img = base_data.data.button.button_image;
			}

			auto unit = retrieve<T>(state, parent);
			dcon::leader_id lid;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				lid = state.world.army_get_general_from_army_leadership(unit);
			disabled = !command::can_change_general(state, state.local_player_nation, unit, dcon::leader_id{});
			} else {
				lid = state.world.navy_get_admiral_from_navy_leadership(unit);
			disabled = !command::can_change_admiral(state, state.local_player_nation, unit, dcon::leader_id{});
			}

			auto pculture = state.world.nation_get_primary_culture(state.local_player_nation);
			auto ltype = pculture.get_group_from_culture_group_membership().get_leader();

			if(ltype && lid) {
				auto admiral = state.world.leader_get_is_admiral(lid);
				if(admiral) {
					auto arange = ltype.get_admirals();
					if(arange.size() > 0) {
						auto rval = rng::get_random(state, uint32_t(state.world.leader_get_since(lid).value), uint32_t(lid.value));
						auto in_range = rng::reduce(uint32_t(rval), arange.size());
						if(base_data.get_element_type() == ui::element_type::image)
						base_data.data.image.gfx_object = arange[in_range];
						else if(base_data.get_element_type() == ui::element_type::button)
						base_data.data.button.button_image = arange[in_range];
					}
				} else {
					auto grange = ltype.get_generals();
					if(grange.size() > 0) {
						auto rval = rng::get_random(state, uint32_t(state.world.leader_get_since(lid).value), uint32_t(lid.value));
						auto in_range = rng::reduce(uint32_t(rval), grange.size());
						if(base_data.get_element_type() == ui::element_type::image)
						base_data.data.image.gfx_object = grange[in_range];
						else if(base_data.get_element_type() == ui::element_type::button)
						base_data.data.button.button_image = grange[in_range];
					}
				}
			} else {
				if(base_data.get_element_type() == ui::element_type::image)
				base_data.data.image.gfx_object = default_img;
				else if(base_data.get_element_type() == ui::element_type::button)
				base_data.data.button.button_image = default_img;
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return  tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto unit = retrieve<T>(state, parent);
			dcon::leader_id lid;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				lid = state.world.army_get_general_from_army_leadership(unit);
			} else {
				lid = state.world.navy_get_admiral_from_navy_leadership(unit);
			}
			if(lid)
			display_leader_full(state, lid, contents, 0);
		}


		void button_action(sys::state& state) noexcept override {
			auto unit = retrieve<T>(state, parent);
			auto location = get_absolute_non_mirror_location(state, *this);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				open_leader_selection(state, unit, dcon::navy_id{}, location.x + base_data.size.x, location.y);
			} else {
				open_leader_selection(state, dcon::army_id{}, unit, location.x + base_data.size.x, location.y);
			}
		}
		void button_right_action(sys::state& state) noexcept override {
			auto unit = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				command::change_general(state, state.local_player_nation, unit, dcon::leader_id{});
			} else {
				command::change_admiral(state, state.local_player_nation, unit, dcon::leader_id{});
			}
		}
	};

	template<class T>
	class unit_selection_unit_location_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				set_text(state, text::produce_simple_string(state, dcon::fatten(state.world, content).get_location_from_army_location().get_name()));
			} else {
				set_text(state, text::produce_simple_string(state, dcon::fatten(state.world, content).get_location_from_navy_location().get_name()));
			}
		}
	};
	template<class T>
	class unit_selection_unit_location_button : public button_element_base {
		public:
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "uw_loc_iro");
		}
		void button_action(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				auto p = dcon::fatten(state.world, content).get_location_from_army_location();
				state.map_state.center_map_on_province(state, p);
			} else {
				auto p = dcon::fatten(state.world, content).get_location_from_navy_location();
				state.map_state.center_map_on_province(state, p);
			}
		}
	};

	template<class T>
	class unit_selection_str_bar : public vertical_progress_bar {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);

			float total_strength = 0.0f;
			int32_t unit_count = 0;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id nmid) {
					auto regiment = dcon::fatten(state.world, state.world.army_membership_get_regiment(nmid));
					total_strength += regiment.get_strength();
					++unit_count;
				});
			} else {
				state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
					auto ship = dcon::fatten(state.world, state.world.navy_membership_get_ship(nmid));
					total_strength += ship.get_strength();
					++unit_count;
				});
			}
			total_strength /= static_cast<float>(unit_count);
			progress = total_strength;
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto content = retrieve<T>(state, parent);
			float total_strength = 0.0f;
			int32_t unit_count = 0;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id nmid) {
					auto regiment = dcon::fatten(state.world, state.world.army_membership_get_regiment(nmid));
					total_strength += regiment.get_strength();
					++unit_count;
				});
			} else {
				state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
					auto ship = dcon::fatten(state.world, state.world.navy_membership_get_ship(nmid));
					total_strength += ship.get_strength();
					++unit_count;
				});
			}
			total_strength /= static_cast<float>(unit_count);

			auto box = text::open_layout_box(contents, 0);
			text::localised_format_box(state, contents, box, std::string_view("curr_comb_str"));
		text::add_to_layout_box(state, contents, box, text::fp_percentage{ total_strength }, text::text_color::yellow);
			text::close_layout_box(contents, box);
		}
	};

	template<class T>
	class unit_selection_org_bar : public vertical_progress_bar {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);

			float total_org = 0.0f;
			int32_t unit_count = 0;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id nmid) {
					auto regiment = dcon::fatten(state.world, state.world.army_membership_get_regiment(nmid));
					total_org += regiment.get_org();
					++unit_count;
				});
			} else {
				state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
					auto ship = dcon::fatten(state.world, state.world.navy_membership_get_ship(nmid));
					total_org += ship.get_org();
					++unit_count;
				});
			}
			total_org /= static_cast<float>(unit_count);
			progress = total_org;
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto content = retrieve<T>(state, parent);
			float total_org = 0.0f;
			int32_t unit_count = 0;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id nmid) {
					auto regiment = dcon::fatten(state.world, state.world.army_membership_get_regiment(nmid));
					total_org += regiment.get_org();
					++unit_count;
				});
			} else {
				state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
					auto ship = dcon::fatten(state.world, state.world.navy_membership_get_ship(nmid));
					total_org += ship.get_org();
					++unit_count;
				});
			}
			total_org /= static_cast<float>(unit_count);

			auto box = text::open_layout_box(contents, 0);
			text::localised_format_box(state, contents, box, std::string_view("curr_comb_org"));
		text::add_to_layout_box(state, contents, box, text::fp_percentage{ total_org }, text::text_color::yellow);
			text::close_layout_box(contents, box);

			if constexpr(std::is_same_v<T, dcon::army_id>) {
				ui::active_modifiers_description(state, contents, state.local_player_nation, 0, sys::national_mod_offsets::land_organisation, true);
			} else {
				ui::active_modifiers_description(state, contents, state.local_player_nation, 0, sys::national_mod_offsets::naval_organisation, true);
			}
		}
	};

	template<class T>
	class unit_selection_total_str_text : public simple_text_element_base {
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);

			int32_t total_strength = 0;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id nmid) {
					auto regiment = dcon::fatten(state.world, state.world.army_membership_get_regiment(nmid));
					total_strength += int32_t(regiment.get_strength() * state.defines.pop_size_per_regiment);
				});
			} else {
				state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
					auto ship = dcon::fatten(state.world, state.world.navy_membership_get_ship(nmid));
					++total_strength;
				});
			}

			set_text(state, text::prettify(total_strength));
		}
	};

	template<class T>
	class unit_selection_attrition_icon : public image_element_base {
		public:
		bool visible = false;
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			visible = military::attrition_amount(state, content) > 0.f;
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			image_element_base::render(state, x, y);
		}
	};

	template<class T>
	class unit_selection_attrition_amount : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			auto amount = military::attrition_amount(state, content);
			set_text(state, amount > 0.f ? "?R" + text::format_percentage(amount * 0.01f, 1) : std::string(""));
		}
	};

	template<class T>
	class unit_selection_panel : public window_element_base {
	dcon::gfx_object_id disband_gfx{};
		unit_selection_disband_too_small_button* disband_too_small_btn = nullptr;
		public:
		window_element_base* combat_window = nullptr;
		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			if(disband_too_small_btn && disband_gfx) {
				disband_too_small_btn->base_data.data.button.button_image = disband_gfx;
			}
		}

		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "unitpanel_bg") {
				return make_element_by_type<opaque_element_base>(state, id);
			} else if(name == "leader_prestige_icon") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "leader_prestige_bar") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "prestige_bar_frame") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "unitname") {
				auto ptr = make_element_by_type<unit_selection_unit_name_text<T>>(state, id);
				ptr->base_data.position.x += 9;
				ptr->base_data.position.y += 4;
				return ptr;
			} else if(name == "only_unit_from_selection_button") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "remove_unit_from_selection_button") {
				return make_element_by_type<unit_selection_close_button>(state, id);
			} else if(name == "newunitbutton") {
				return make_element_by_type<unit_selection_new_unit_button>(state, id);
			} else if(name == "splitinhalf") {
				return make_element_by_type<unit_selection_split_in_half_button<T>>(state, id);
			} else if(name == "disbandbutton") {
				auto ptr = make_element_by_type<unit_selection_disband_button<T>>(state, id);
				disband_gfx = ptr->base_data.data.button.button_image;
				return ptr;
			} else if(name == "disbandtoosmallbutton") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					auto ptr = make_element_by_type<unit_selection_disband_too_small_button>(state, id);
					disband_too_small_btn = ptr.get();
					return ptr;
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "str_bar") {
				return make_element_by_type<unit_selection_str_bar<T>>(state, id);
			} else if(name == "org_bar") {
				return make_element_by_type<unit_selection_org_bar<T>>(state, id);
			} else if(name == "unitattrition_icon") {
				return make_element_by_type<unit_selection_attrition_icon<T>>(state, id);
			} else if(name == "unitattrition") {
				return make_element_by_type<unit_selection_attrition_amount<T>>(state, id);
			} else if(name == "unitstrength") {
				return make_element_by_type<unit_selection_total_str_text<T>>(state, id);
			} else if(name == "unitlocation") {
				return make_element_by_type<unit_selection_unit_location_text<T>>(state, id);
			} else if(name == "unit_location_button") {
				return make_element_by_type<unit_selection_unit_location_button<T>>(state, id);
			} else if(name == "unitleader") {
				return make_element_by_type<unit_selection_leader_name<T>>(state, id);
			} else if(name == "leader_button") {
				return make_element_by_type<unit_selection_change_leader_button<T>>(state, id);
			} else if(name == "unit_activity") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "leader_photo") {
				return make_element_by_type<unit_selection_leader_image<T>>(state, id);
			} else {
				return nullptr;
			}
		}

		message_result get(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<element_selection_wrapper<unitpanel_action>>()) {
				auto action = any_cast<element_selection_wrapper<unitpanel_action>>(payload).data;
				switch(action) {
					case unitpanel_action::close: {
						// Bucket Carry, we dont handle this, but the parent does
						parent->impl_get(state, payload);
						// Tell reorg window to clean up after itself
				Cyto::Any cpayload = element_selection_wrapper<reorg_win_action>{reorg_win_action{reorg_win_action::close}};
						auto* reorg_window = std::is_same_v<T, dcon::army_id>
						? state.ui_state.army_reorg_window
						: state.ui_state.navy_reorg_window;
						reorg_window->impl_get(state, cpayload);
						break;
					}
					case unitpanel_action::reorg: {
						auto* reorg_window = std::is_same_v<T, dcon::army_id>
						? state.ui_state.army_reorg_window
						: state.ui_state.navy_reorg_window;
						bool keep_shown = false;
						if constexpr(std::is_same_v<T, dcon::army_id>) {
							auto u = retrieve<T>(state, parent);
							auto* win = static_cast<unit_reorg_window<T, dcon::regiment_id>*>(state.ui_state.army_reorg_window);
							keep_shown = win->unit_to_reorg != u && win->is_visible();
							win->unit_to_reorg = u;
							if(u) {
								reorg_window->set_visible(state, !reorg_window->is_visible() || keep_shown);
								reorg_window->impl_on_update(state);
							}
						} else {
							auto u = retrieve<T>(state, parent);
							auto* win = static_cast<unit_reorg_window<T, dcon::ship_id>*>(state.ui_state.navy_reorg_window);
							keep_shown = win->unit_to_reorg != u && win->is_visible();
							win->unit_to_reorg = u;
							if(u) {
								reorg_window->set_visible(state, !reorg_window->is_visible() || keep_shown);
								reorg_window->impl_on_update(state);
							}
						}
						break;
					}
					case unitpanel_action::changeleader: {
				
						break;
					}
					default: {
						break;
					}
				}
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};

	template<class T, std::size_t N>
	class unit_details_type_item : public window_element_base {
		private:
		simple_text_element_base* unitamount_text = nullptr;
		simple_text_element_base* unitstrength_text = nullptr;
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "unit_amount") {
				auto ptr = make_element_by_type<simple_text_element_base>(state, id);
				unitamount_text = ptr.get();
				return ptr;
			} else if(name == "unit_strength") {
				auto ptr = make_element_by_type<simple_text_element_base>(state, id);
				unitstrength_text = ptr.get();
				return ptr;
			} else if(name == "unit_icon") {
				auto ptr = make_element_by_type<image_element_base>(state, id);
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					ptr->frame = N;
				} else {
					ptr->frame = 3 + N;
				}
				return ptr;
			} else {
				return nullptr;
			}
		}

		void on_update(sys::state& state) noexcept override {
			if(parent) {
			Cyto::Any payload = T{};
				parent->impl_get(state, payload);
				auto content = any_cast<T>(payload);
				auto fat = dcon::fatten(state.world, content);

				if constexpr(std::is_same_v<T, dcon::army_id>) {
					unitstrength_text->set_visible(state, true);

					uint16_t totalunits = 0;
					uint32_t totalpops = 0;
					for(auto n : fat.get_army_membership()) {
						dcon::unit_type_id utid = n.get_regiment().get_type();
						auto result = utid ? state.military_definitions.unit_base_definitions[utid].type : military::unit_type::infantry;
						if constexpr(N == 0) {
							if(result == military::unit_type::infantry) {
								totalunits++;
								totalpops += uint32_t(state.world.regiment_get_strength(n.get_regiment().id) * state.defines.pop_size_per_regiment);
							}
						} else if constexpr(N == 1) {
							if(result == military::unit_type::cavalry) {
								totalunits++;
								totalpops += uint32_t(state.world.regiment_get_strength(n.get_regiment().id) * state.defines.pop_size_per_regiment);
							}
						} else if constexpr(N == 2) {
							if(result == military::unit_type::support || result == military::unit_type::special) {
								totalunits++;
								totalpops += uint32_t(state.world.regiment_get_strength(n.get_regiment().id) * state.defines.pop_size_per_regiment);
							}
						}
					}
					unitamount_text->set_text(state, text::format_float(totalunits, 0));
					unitstrength_text->set_text(state, text::format_wholenum(totalpops));
				} else {
					unitstrength_text->set_visible(state, false);
					uint16_t total = 0;
					for(auto n : fat.get_navy_membership()) {
						dcon::unit_type_id utid = n.get_ship().get_type();
						auto result = utid ? state.military_definitions.unit_base_definitions[utid].type : military::unit_type::infantry;
						if constexpr(N == 0) {
							if(result == military::unit_type::big_ship) {
								total++;
							}
						} else if constexpr(N == 1) {
							if(result == military::unit_type::light_ship) {
								total++;
							}
						} else if constexpr(N == 2) {
							if(result == military::unit_type::transport) {
								total++;
							}
						}
					}
					unitamount_text->set_text(state, text::format_float(total, 0));
				}
			}
		}
	};

	template<typename T>
	class subunit_experience_bar : public image_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			float exp = 0.f;
			if constexpr(std::is_same_v<T, dcon::regiment_id>) {
				exp = state.world.regiment_get_experience(content);
			} else {
				exp = state.world.ship_get_experience(content);
			}
			frame = int32_t(std::ceil(exp * 10.f));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto content = retrieve<T>(state, parent);
			float exp = 0.f;
			if constexpr(std::is_same_v<T, dcon::regiment_id>) {
				exp = state.world.regiment_get_experience(content);
			} else {
				exp = state.world.ship_get_experience(content);
			}
		text::add_line(state, contents, "unit_experience", text::variable_type::x, text::fp_two_places{ exp * 100.f });
		}
	};

	class subunit_details_entry_regiment : public listbox_row_element_base<dcon::regiment_id> {
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "select") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "select_naval") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "sunit_icon") {
				return make_element_by_type<subunit_details_type_icon<dcon::regiment_id>>(state, id);
			} else if(name == "subunit_name") {
				return make_element_by_type<subunit_details_name<dcon::regiment_id>>(state, id);
			} else if(name == "subunit_type") {
				return make_element_by_type<subunit_details_type_text<dcon::regiment_id>>(state, id);
			} else if(name == "subunit_amount") {
				return make_element_by_type<subunit_details_regiment_amount>(state, id);
			} else if(name == "subunit_amount_naval") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "connected_pop") {
				return make_element_by_type<regiment_pop_icon>(state, id);
			} else if(name == "rebel_faction") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "unit_experience") {
				return make_element_by_type<subunit_experience_bar<dcon::regiment_id>>(state, id);
			} else if(name == "org_bar") {
				return make_element_by_type<subunit_organisation_progress_bar<dcon::regiment_id>>(state, id);
			} else if(name == "str_bar") {
				return make_element_by_type<subunit_strength_progress_bar<dcon::regiment_id>>(state, id);
			} else {
				return nullptr;
			}
		}
	};

	class subunit_details_entry_ship : public listbox_row_element_base<dcon::ship_id> {
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "select") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "select_naval") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "sunit_icon") {
				return make_element_by_type<subunit_details_type_icon<dcon::ship_id>>(state, id);
			} else if(name == "subunit_name") {
				return make_element_by_type<subunit_details_name<dcon::ship_id>>(state, id);
			} else if(name == "subunit_type") {
				return make_element_by_type<subunit_details_type_text<dcon::ship_id>>(state, id);
			} else if(name == "subunit_amount") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "subunit_amount_naval") {
				return make_element_by_type<subunit_details_ship_amount>(state, id);
			} else if(name == "connected_pop") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "rebel_faction") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "unit_experience") {
				return make_element_by_type<subunit_experience_bar<dcon::ship_id>>(state, id);
			} else if(name == "org_bar") {
				return make_element_by_type<subunit_organisation_progress_bar<dcon::ship_id>>(state, id);
			} else if(name == "str_bar") {
				return make_element_by_type<subunit_strength_progress_bar<dcon::ship_id>>(state, id);
			} else {
				return nullptr;
			}
		}

		void on_update(sys::state& state) noexcept override { 
		}
	};

	class unit_details_army_listbox : public listbox_element_base<subunit_details_entry_regiment, dcon::regiment_id> {
		protected:
		std::string_view get_row_element_name() override {
			return "subunit_entry";
		}

		public:
		void on_create(sys::state& state) noexcept override {
			base_data.size.y += state.ui_defs.gui[state.ui_state.defs_by_name.find(state.lookup_key("subunit_entry"))->second.definition].size.y; //nudge - allows for the extra element in the lb
			listbox_element_base<subunit_details_entry_regiment, dcon::regiment_id>::on_create(state);
		}

		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::army_id>(state, parent);
			row_contents.clear();
			state.world.army_for_each_army_membership_as_army(content, [&](dcon::army_membership_id amid) {
				auto rid = state.world.army_membership_get_regiment(amid);
				row_contents.push_back(rid);
			});
			auto it = std::unique(row_contents.begin(), row_contents.end(), [&](auto a, auto b) {
				return a.index() == b.index();
			});
			row_contents.erase(it, row_contents.end());
			sys::merge_sort(row_contents.begin(), row_contents.end(), [&](dcon::regiment_id a, dcon::regiment_id b) {
				auto au = state.world.regiment_get_type(a);
				auto bu = state.world.regiment_get_type(b);
				auto av = uint8_t(state.military_definitions.unit_base_definitions[au].type);
				auto bv = uint8_t(state.military_definitions.unit_base_definitions[bu].type);
				if(av != bv)
					return av < bv;
				if(au != bu)
					return au.index() < bu.index();
				return a.index() < b.index();
			});
			update(state);
		}
	};
	class unit_details_navy_listbox : public listbox_element_base<subunit_details_entry_ship, dcon::ship_id> {
		protected:
		std::string_view get_row_element_name() override {
			return "subunit_entry";
		}

		public:
		void on_create(sys::state& state) noexcept override {
			base_data.size.y += state.ui_defs.gui[state.ui_state.defs_by_name.find(state.lookup_key("subunit_entry"))->second.definition].size.y; //nudge - allows for the extra element in the lb
			listbox_element_base<subunit_details_entry_ship, dcon::ship_id>::on_create(state);
		}

		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::navy_id>(state, parent);
			row_contents.clear();
			state.world.navy_for_each_navy_membership_as_navy(content, [&](dcon::navy_membership_id nmid) {
				auto sid = state.world.navy_membership_get_ship(nmid);
				row_contents.push_back(sid);
			});
			auto it = std::unique(row_contents.begin(), row_contents.end(), [&](auto a, auto b) {
				return a.index() == b.index();
			});
			row_contents.erase(it, row_contents.end());
			sys::merge_sort(row_contents.begin(), row_contents.end(), [&](dcon::ship_id a, dcon::ship_id b) {
				auto au = state.world.ship_get_type(a);
				auto bu = state.world.ship_get_type(b);
				auto av = uint8_t(state.military_definitions.unit_base_definitions[au].type);
				auto bv = uint8_t(state.military_definitions.unit_base_definitions[bu].type);
				if(av != bv)
					return av < bv;
				if(au != bu)
					return au.index() < bu.index();
				return a.index() < b.index();
			});
			update(state);
		}
	};

	class unit_details_load_army_button : public button_element_base {
		public:
		bool visible = false;

		void on_create(sys::state& state) noexcept override {
			button_element_base::on_create(state);
			if(base_data.data.button.shortcut == sys::virtual_key::NONE) {
				base_data.data.button.shortcut = sys::virtual_key::A;
			}
		}
		void button_action(sys::state& state) noexcept override {
			auto a = retrieve<dcon::army_id>(state, parent);
			auto p = state.world.army_get_location_from_army_location(a);
			int32_t max_cap = 0;
			for(auto n : state.world.province_get_navy_location(p)) {
				if(n.get_navy().get_controller_from_navy_control() == state.local_player_nation &&
				!bool(n.get_navy().get_battle_from_navy_battle_participation())) {
					max_cap = std::max(military::free_transport_capacity(state, n.get_navy()), max_cap);
				}
			}
			if(!military::can_embark_onto_sea_tile(state, state.local_player_nation, p, a)
			&& max_cap > 0) { //require splitting
				auto regs = state.world.army_get_army_membership(a);
				int32_t army_cap = int32_t(regs.end() - regs.begin());
				int32_t to_split = army_cap - max_cap;
				//can mark 10 regiments to be split at a time
				std::array<dcon::regiment_id, command::num_packed_units> data;
				int32_t i = 0;
			data.fill(dcon::regiment_id{});
				for(auto reg : state.world.army_get_army_membership(a)) {
					if(to_split == 0)
					break;
					//
					data[i] = reg.get_regiment();
					++i;
					if(i >= int32_t(command::num_packed_units)) { //reached max allowed
						command::mark_regiments_to_split(state, state.local_player_nation, data);
					data.fill(dcon::regiment_id{});
						i = 0;
					}
					//
					--to_split;
				}
				if(i > 0) { //leftovers
					command::mark_regiments_to_split(state, state.local_player_nation, data);
				}
				command::split_army(state, state.local_player_nation, a);
				command::embark_army(state, state.local_player_nation, a);
			} else { //no split
				command::embark_army(state, state.local_player_nation, a);
			}
		}
		void on_update(sys::state& state) noexcept override {
			auto a = retrieve<dcon::army_id>(state, parent);
			auto p = state.world.army_get_location_from_army_location(a);
			visible = !bool(state.world.army_get_navy_from_army_transport(a)); //not already in ship
			disabled = true;
			frame = 0;
			if(visible) {
				int32_t max_cap = 0;
				for(auto n : state.world.province_get_navy_location(p)) {
					if(n.get_navy().get_controller_from_navy_control() == state.local_player_nation &&
					!bool(n.get_navy().get_battle_from_navy_battle_participation())) {
						max_cap = std::max(military::free_transport_capacity(state, n.get_navy()), max_cap);
					}
				}
				disabled = max_cap <= 0;
				//require splitting
				if(!military::can_embark_onto_sea_tile(state, state.local_player_nation, p, a)
				&& max_cap > 0) {
					frame = 1;
				}
			}
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::army_id>(state, parent);
			auto loc = state.world.army_get_location_from_army_location(n);

			text::add_line(state, contents, "uw_load_is_valid");
			text::add_line_with_condition(state, contents, "unit_load_or_unload_1", military::can_embark_onto_sea_tile(state, state.local_player_nation, loc, n));
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			button_element_base::render(state, x, y);
		}
		message_result test_mouse(sys::state& state, int32_t x, int32_t y, mouse_probe_type t) noexcept override {
			if(visible)
			return button_element_base::test_mouse(state, x, y, t);
			return message_result::unseen;
		}
	};
	class unit_details_unload_army_button : public button_element_base {
		public:
		bool visible = false;

		void on_create(sys::state& state) noexcept override {
			button_element_base::on_create(state);
			if(base_data.data.button.shortcut == sys::virtual_key::NONE) {
				base_data.data.button.shortcut = sys::virtual_key::D;
			}
		}
		void button_action(sys::state& state) noexcept override {
			auto n = retrieve<dcon::army_id>(state, parent);
			command::embark_army(state, state.local_player_nation, n);
		}
		void on_update(sys::state& state) noexcept override {
			auto n = retrieve<dcon::army_id>(state, parent);
			auto tprted = state.world.army_get_navy_from_army_transport(n);
			auto loc = state.world.army_get_location_from_army_location(n);

			visible = bool(tprted);

			if(loc.index() >= state.province_definitions.first_sea_province.index()) {
				disabled = true;
			} else {
				disabled = false;
			}
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::army_id>(state, parent);
			auto tprted = state.world.army_get_navy_from_army_transport(n);
			auto loc = state.world.army_get_location_from_army_location(n);

			text::add_line(state, contents, "uw_unload_valid");
			text::add_line_with_condition(state, contents, "unit_load_or_unload_2", bool(tprted));
			text::add_line_with_condition(state, contents, "unit_load_or_unload_3", loc.index() < state.province_definitions.first_sea_province.index());
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			button_element_base::render(state, x, y);
		}
		message_result test_mouse(sys::state& state, int32_t x, int32_t y, mouse_probe_type t) noexcept override {
			if(visible)
			return button_element_base::test_mouse(state, x, y, t);
			return message_result::unseen;
		}
	};
	class unit_details_unload_navy_button : public button_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			button_element_base::on_create(state);
			if(base_data.data.button.shortcut == sys::virtual_key::NONE) {
				base_data.data.button.shortcut = sys::virtual_key::D;
			}
		}
		void button_action(sys::state& state) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);
			auto tprted = state.world.navy_get_army_transport(n);
			std::vector<dcon::army_id> tmp;
			for(auto t : tprted)
			tmp.push_back(t.get_army());
			for(auto a : tmp)
			command::embark_army(state, state.local_player_nation, a);
		}

		void on_update(sys::state& state) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);
			auto tprted = state.world.navy_get_army_transport(n);
			auto loc = state.world.navy_get_location_from_navy_location(n);

			if(tprted.begin() == tprted.end() || loc.index() >= state.province_definitions.first_sea_province.index()) {
				disabled = true;
			} else {
				disabled = false;
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);
			auto tprted = state.world.navy_get_army_transport(n);
			auto loc = state.world.navy_get_location_from_navy_location(n);

			text::add_line(state, contents, "unload_all_armies_of_fleet");
			text::add_line_with_condition(state, contents, "unit_load_or_unload_4", tprted.begin() != tprted.end());
			text::add_line_with_condition(state, contents, "unit_load_or_unload_5", loc.index() < state.province_definitions.first_sea_province.index());
		}
	};

	class unit_details_select_loaded_army : public button_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			button_element_base::on_create(state);
			if(base_data.data.button.shortcut == sys::virtual_key::NONE) {
				base_data.data.button.shortcut = sys::virtual_key::A;
			}
		}
		void button_action(sys::state& state) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);
			auto tprted = state.world.navy_get_army_transport(n);

			state.selected_armies.clear();
			state.selected_navies.clear();
			for(auto t : tprted)
			state.select(t.get_army());
		}

		void on_update(sys::state& state) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);
			auto tprted = state.world.navy_get_army_transport(n);
			disabled = tprted.begin() == tprted.end();
		}
	};

	class navy_transport_text : public simple_text_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			base_data.position.x -= int16_t(50);
			simple_text_element_base::on_create(state);
		}
		void on_update(sys::state& state) noexcept override {
			auto n = retrieve<dcon::navy_id>(state, parent);

			auto tcap = military::transport_capacity(state, n);
			auto tfree = military::free_transport_capacity(state, n);
			text::substitution_map sub;
			if(tcap != tfree) {
				auto txt = std::to_string(tfree) + " (" + std::to_string(tcap) + ")";
				text::add_to_substitution_map(sub, text::variable_type::num, std::string_view(txt));
				set_text(state, text::resolve_string_substitution(state, std::string_view("load_capacity_label"), sub));
			} else {
				text::add_to_substitution_map(sub, text::variable_type::num, tcap);
				set_text(state, text::resolve_string_substitution(state, std::string_view("load_capacity_label"), sub));
			}
		}

	};

	class unit_details_hunt_rebels : public button_element_base {
		public:
		bool visible = false;
		void on_update(sys::state& state) noexcept override {
			auto a = retrieve<dcon::army_id>(state, parent);
			visible = !state.world.army_get_is_rebel_hunter(a);
		}
		message_result test_mouse(sys::state& state, int32_t x, int32_t y, mouse_probe_type type) noexcept override {
			if(visible)
			return button_element_base::test_mouse(state, x, y, type);
			return message_result::unseen;
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "unit_enable_rebel_hunt");
		}
		void button_action(sys::state& state) noexcept override {
			command::toggle_rebel_hunting(state, state.local_player_nation, retrieve<dcon::army_id>(state, parent));
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			button_element_base::render(state, x, y);
		}
	};
	class unit_details_dont_hunt_rebels : public button_element_base {
		public:
		bool visible = false;
		void on_update(sys::state& state) noexcept override {
			auto a = retrieve<dcon::army_id>(state, parent);
			visible = state.world.army_get_is_rebel_hunter(a);
		}
		message_result test_mouse(sys::state& state, int32_t x, int32_t y, mouse_probe_type type) noexcept override {
			if(visible)
			return button_element_base::test_mouse(state, x, y, type);
			return message_result::unseen;
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "vce_unit_disable_rebel_hunt");
		}
		void button_action(sys::state& state) noexcept override {
			command::toggle_rebel_hunting(state, state.local_player_nation, retrieve<dcon::army_id>(state, parent));
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			button_element_base::render(state, x, y);
		}
	};
	class unit_details_ai_controlled : public checkbox_button {
		public:
		bool is_active(sys::state& state) noexcept override {
			return state.world.army_get_is_ai_controlled(retrieve<dcon::army_id>(state, parent));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "vce_ai_controlled_unit");
		}
		void button_action(sys::state& state) noexcept override {
			auto a = retrieve<dcon::army_id>(state, parent);
			command::toggle_unit_ai_control(state, state.local_player_nation, a);
		}
	};

	class unit_supply_bar : public progress_bar {
		public:
		void on_update(sys::state& state) noexcept override {
			auto army = retrieve<dcon::army_id>(state, parent);
			auto navy = retrieve<dcon::navy_id>(state, parent);

			economy::commodity_set commodities;

			auto owner = state.local_player_nation;

			float spending_level = .0f;

			if(army) {
				commodities = military::get_required_supply(state, state.local_player_nation, army);
				spending_level = float(state.world.nation_get_land_spending(owner)) / 100.0f;
			} else if(navy) {
				commodities = military::get_required_supply(state, state.local_player_nation, navy);
				spending_level = float(state.world.nation_get_naval_spending(owner)) / 100.0f;
			}

		
			uint32_t total_commodities = state.world.commodity_size();

			float max_supply = 0.0f;
			float actual_supply = 0.0f;


			auto nations_commodity_spending = state.world.nation_get_spending_level(owner);

			for(uint32_t i = 0; i < total_commodities; ++i) {
				if(!commodities.commodity_type[i]) {
					break;
				}

			dcon::commodity_id c{ dcon::commodity_id::value_base_t(i) };

				auto satisfaction = state.world.nation_get_demand_satisfaction(owner, c);
				auto val = commodities.commodity_type[i];

				max_supply += commodities.commodity_amounts[i];
				actual_supply += commodities.commodity_amounts[i] * satisfaction * nations_commodity_spending * spending_level;
			}

			float median_supply = max_supply > 0.0f ? actual_supply / max_supply : 0.0f;

			progress = median_supply;
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto army = retrieve<dcon::army_id>(state, parent);
			auto navy = retrieve<dcon::navy_id>(state, parent);
			economy::commodity_set commodities;

			float spending_level = .0f;
			auto owner = state.local_player_nation;

			if(army) {
				commodities = military::get_required_supply(state, state.local_player_nation, army);
				spending_level = float(state.world.nation_get_land_spending(owner)) / 100.0f;
			} else if(navy) {
				commodities = military::get_required_supply(state, state.local_player_nation, navy);
				spending_level = float(state.world.nation_get_naval_spending(owner)) / 100.0f;
			}
		
		
			uint32_t total_commodities = state.world.commodity_size();

			float max_supply = 0.0f;
			float actual_supply = 0.0f;

			auto nations_commodity_spending = state.world.nation_get_spending_level(owner);
			for(uint32_t i = 0; i < total_commodities; ++i) {
				if(!commodities.commodity_type[i]) {
					break;
				}
			dcon::commodity_id c{ dcon::commodity_id::value_base_t(i) };

				auto satisfaction = state.world.nation_get_demand_satisfaction(owner, c);
				auto val = commodities.commodity_type[i];

				max_supply += commodities.commodity_amounts[i];
				actual_supply += commodities.commodity_amounts[i] * satisfaction * nations_commodity_spending * spending_level;			
			}

			float median_supply = max_supply > 0.0f ? actual_supply / max_supply : 0.0f;
			text::add_line(state, contents, "unit_current_supply", text::variable_type::val, int16_t(median_supply * 100.f));
			text::add_line_break_to_layout(state, contents);
			for(uint32_t i = 0; i < economy::commodity_set::set_size; ++i) {
				if(commodities.commodity_type[i] && commodities.commodity_amounts[i] > 0) {
				dcon::commodity_id c{ dcon::commodity_id::value_base_t(i) };
					float satisfaction = state.world.nation_get_demand_satisfaction(owner, c);
					float wanted_commodity = commodities.commodity_amounts[i];
					float actual_commodity = commodities.commodity_amounts[i] * satisfaction * nations_commodity_spending * spending_level;

					int32_t display_satisfaction = int32_t(satisfaction * 100);

					if(satisfaction == 1 || satisfaction >= 0.95) {
					text::add_line(state, contents, "unit_current_supply_high", text::variable_type::what, state.world.commodity_get_name(commodities.commodity_type[i]), text::variable_type::val, text::fp_three_places{ actual_commodity }, text::variable_type::value, text::fp_three_places{ wanted_commodity }, text::variable_type::total, display_satisfaction);
					} else if (satisfaction < 0.95 && satisfaction >= 0.5) {
					text::add_line(state, contents, "unit_current_supply_mid", text::variable_type::what, state.world.commodity_get_name(commodities.commodity_type[i]), text::variable_type::val, text::fp_three_places{ actual_commodity }, text::variable_type::value, text::fp_three_places{ wanted_commodity }, text::variable_type::total, display_satisfaction);
					} else {
					text::add_line(state, contents, "unit_current_supply_low", text::variable_type::what, state.world.commodity_get_name(commodities.commodity_type[i]), text::variable_type::val, text::fp_three_places{ actual_commodity }, text::variable_type::value, text::fp_three_places{ wanted_commodity }, text::variable_type::total, display_satisfaction);
					}
				}
			}
		}
	};

	template<class T>
	class unit_details_buttons : public window_element_base {
		private:
		simple_text_element_base* navytransport_text = nullptr;
		public:
		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				auto ptr = make_element_by_type<unit_details_ai_controlled>(state, "vce_enable_ai_controlled");
				add_child_to_front(std::move(ptr));
			}
		}

		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "load_button" && std::is_same_v<T, dcon::army_id>) {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_details_load_army_button>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "unload_button") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_details_unload_army_button>(state, id);
				} else {
					return make_element_by_type<unit_details_unload_navy_button>(state, id);
				}
			} else if(name == "enable_rebel_button") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_details_hunt_rebels>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "disable_rebel_button") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_details_dont_hunt_rebels>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "select_land") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<invisible_element>(state, id);
				} else {
					auto ptr = make_element_by_type<unit_details_select_loaded_army>(state, id);
					ptr->base_data.position.x -= 48;
					return ptr;
				}
			} else if(name == "attach_unit_button" || name == "detach_unit_button") {
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "header") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<invisible_element>(state, id);
				} else {
					return make_element_by_type<navy_transport_text>(state, id);
				}
			} else {
				return nullptr;
			}
		}
	};

	template<class T>
	class unit_speed_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<T>(state, parent);
			text::substitution_map sub;
			if constexpr(std::is_same_v<T, dcon::navy_id>) {
				text::add_to_substitution_map(sub, text::variable_type::val, uint16_t(military::effective_navy_speed(state, content)));
			} else if constexpr(std::is_same_v<T, dcon::army_id>) {
				text::add_to_substitution_map(sub, text::variable_type::val, uint16_t(military::effective_army_speed(state, content)));
			}
			set_text(state, text::resolve_string_substitution(state, std::string_view("speed"), sub));
		}
	};

	class unit_recon_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::army_id>(state, parent);
			float max_recon = 0.f;
			for(const auto r : state.world.army_get_army_membership(content)) {
				auto type = r.get_regiment().get_type();
				if(!type)
				continue;
				auto value = state.military_definitions.unit_base_definitions[type].reconnaissance_or_fire_range;
				max_recon = std::max(value, max_recon);
			}
			set_text(state, text::format_percentage(max_recon));
		}
	};

	class unit_siege_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::army_id>(state, parent);
			float max_siege = 0.f;
			for(const auto r : state.world.army_get_army_membership(content)) {
				auto type = r.get_regiment().get_type();
				if(!type)
				continue;
				auto value = state.military_definitions.unit_base_definitions[type].siege_or_torpedo_attack;
				max_siege = std::max(value, max_siege);
			}
			set_text(state, text::format_percentage(max_siege));
		}
	};

	template<class T>
	class unit_details_window : public window_element_base {
		progress_bar* unitsupply_bar = nullptr;
		image_element_base* unitdugin_icon = nullptr;
		unit_selection_panel<T>* unit_selection_win = nullptr;
		public:
		T unit_id;

		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			base_data.position.y = 250;

			xy_pair base_position = {20,
				0}; // state.ui_defs.gui[state.ui_state.defs_by_name.find("unittype_item_start")->second.definition].position;
			xy_pair base_offset = state.ui_defs.gui[state.ui_state.defs_by_name.find(state.lookup_key("unittype_item_offset"))->second.definition].position;

			{
				auto win = make_element_by_type<unit_details_type_item<T, 0>>(state, state.ui_state.defs_by_name.find(state.lookup_key("unittype_item"))->second.definition);
				win->base_data.position.x = base_position.x + (0 * base_offset.x); // Flexnudge
				win->base_data.position.y = base_position.y + (0 * base_offset.y); // Flexnudge
				add_child_to_front(std::move(win));
			}
			{
				auto win = make_element_by_type<unit_details_type_item<T, 1>>(state, state.ui_state.defs_by_name.find(state.lookup_key("unittype_item"))->second.definition);
				win->base_data.position.x = base_position.x + (1 * base_offset.x); // Flexnudge
				win->base_data.position.y = base_position.y + (1 * base_offset.y); // Flexnudge
				add_child_to_front(std::move(win));
			}
			{
				auto win = make_element_by_type<unit_details_type_item<T, 2>>(state, state.ui_state.defs_by_name.find(state.lookup_key("unittype_item"))->second.definition);
				win->base_data.position.x = base_position.x + (2 * base_offset.x); // Flexnudge
				win->base_data.position.y = base_position.y + (2 * base_offset.y); // Flexnudge
				add_child_to_front(std::move(win));
			}

			const xy_pair item_offset = state.ui_defs.gui[state.ui_state.defs_by_name.find(state.lookup_key("unittype_item"))->second.definition].position;
			if constexpr(std::is_same_v<T, dcon::army_id>) {
				auto ptr = make_element_by_type<unit_details_army_listbox>(state, state.ui_state.defs_by_name.find(state.lookup_key("sup_subunits"))->second.definition);
				ptr->base_data.position.y = base_position.y + item_offset.y + (3 * base_offset.y) + 72 - 32;
				ptr->base_data.size.y += 32;
				add_child_to_front(std::move(ptr));
			} else {
				auto ptr = make_element_by_type<unit_details_navy_listbox>(state, state.ui_state.defs_by_name.find(state.lookup_key("sup_subunits"))->second.definition);
				ptr->base_data.position.y = base_position.y + item_offset.y + (3 * base_offset.y) + 72 - 32;
				ptr->base_data.size.y += 32;
				add_child_to_front(std::move(ptr));
			}

			{
				auto ptr = make_element_by_type<unit_details_buttons<T>>(state,
					state.ui_state.defs_by_name.find(state.lookup_key("sup_buttons_window"))->second.definition);
				ptr->base_data.position.y = base_data.size.y; // Nudge
				add_child_to_front(std::move(ptr));
			}

			{
				auto ptr = make_element_by_type<unit_selection_panel<T>>(state, state.ui_state.defs_by_name.find(state.lookup_key("unitpanel"))->second.definition);
				unit_selection_win = ptr.get();
				ptr->base_data.position.y = -80;
				add_child_to_front(std::move(ptr));
			}
		}

		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "unit_bottom_bg") {
				return make_element_by_type<opaque_element_base>(state, id);
			} else if(name == "icon_speed") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "speed") {
				return make_element_by_type<unit_speed_text<T>>(state, id);
			} else if(name == "icon_recon") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<image_element_base>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "recon") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_recon_text>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "icon_engineer") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<image_element_base>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "engineer") {
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					return make_element_by_type<unit_siege_text>(state, id);
				} else {
					return make_element_by_type<invisible_element>(state, id);
				}
			} else if(name == "icon_supplies_small") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "supply_status") {
				auto ptr = make_element_by_type<unit_supply_bar>(state, id);
				unitsupply_bar = ptr.get();
				return ptr;
			} else if(name == "unitstatus_dugin") {
				auto ptr = make_element_by_type<image_element_base>(state, id);
				unitdugin_icon = ptr.get();
				return ptr;
			} else {
				return nullptr;
			}
		}

		message_result get(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<T>()) {
				payload.emplace<T>(unit_id);
				return message_result::consumed;
			} else if(payload.holds_type<element_selection_wrapper<T>>()) {
				unit_id = any_cast<element_selection_wrapper<T>>(payload).data;
				impl_on_update(state);
				return message_result::consumed;
			} else if(payload.holds_type<element_selection_wrapper<dcon::leader_id>>()) {
				auto content = any_cast<element_selection_wrapper<dcon::leader_id>>(payload).data;
				if constexpr(std::is_same_v<T, dcon::army_id>) {
					command::change_general(state, state.local_player_nation, unit_id, content);
				} else {
					command::change_admiral(state, state.local_player_nation, unit_id, content);
				}
				return message_result::consumed;
			} else if(payload.holds_type<element_selection_wrapper<unitpanel_action>>()) {
				auto content = any_cast<element_selection_wrapper<unitpanel_action>>(payload).data;
				switch(content) {
					case unitpanel_action::close:
					{
				Cyto::Any cpayload = element_selection_wrapper<reorg_win_action>{reorg_win_action{reorg_win_action::close}};
						state.ui_state.army_reorg_window->impl_get(state, cpayload);
						state.ui_state.navy_reorg_window->impl_get(state, cpayload);
						state.selected_armies.clear();
						state.selected_navies.clear();
						set_visible(state, false);
						state.game_state_updated.store(true, std::memory_order_release);
						break;
					}
					default: 
					break;
				};
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};

	class unit_row_panel_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				state.selected_armies.clear();
				state.selected_navies.clear();
				state.select(std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				state.selected_armies.clear();
				state.selected_navies.clear();
				state.select(std::get<dcon::navy_id>(foru));
			}
		}
		void button_shift_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				state.deselect(std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				state.deselect(std::get<dcon::navy_id>(foru));
			}
		}
	};

	class unit_row_strength : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			float total = 0.0f;
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					total += r.get_regiment().get_strength() * state.defines.pop_size_per_regiment;
				}
				set_text(state, text::format_wholenum(int32_t(total)));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					total += r.get_ship().get_strength();
				}
				set_text(state, text::format_float(total, 1));
			}
		}
	};

	class unit_row_attrition_text : public simple_text_element_base {
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			float value = 0.f;
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				value = military::attrition_amount(state, a);
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				value = military::attrition_amount(state, a);
			}
			set_text(state, (value > 0.f ? "?R" : "") + text::format_percentage(value * 0.01f));
		}
	};

	class unit_row_attrition_icon : public image_element_base {
		bool visible = false;
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				visible = military::attrition_amount(state, a) > 0.f;
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				visible = military::attrition_amount(state, a) > 0.f;
			} else {
				visible = false;
			}
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			image_element_base::render(state, x, y);
		}
	};

	class unit_row_org_bar : public vertical_progress_bar {
		void on_update(sys::state& state) noexcept override {
			float current = 0.0f;
			float total = 0.0f;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					current += r.get_regiment().get_org();
					total += 1.0f;
				}
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					current += r.get_ship().get_org();
					total += 1.0f;
				}
			}
			progress = total > 0.0f ? current / total : 0.0f;
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, text::format_percentage(progress));
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				ui::active_modifiers_description(state, contents, state.local_player_nation, 0, sys::national_mod_offsets::land_organisation, true);
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				ui::active_modifiers_description(state, contents, state.local_player_nation, 0, sys::national_mod_offsets::naval_organisation, true);
			}
		}
	};

	class unit_row_str_bar : public vertical_progress_bar {
		void on_update(sys::state& state) noexcept override {
			float current = 0.0f;
			float total = 0.0f;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					current += r.get_regiment().get_strength();
					total += 1.0f;
				}
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					current += r.get_ship().get_strength();
					total += 1.0f;
				}
			}
			progress = total > 0.0f ? current / total : 0.0f;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, text::format_percentage(progress));
		}
	};

	class unit_row_disband : public button_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				disabled = !command::can_delete_army(state, state.local_player_nation, std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				disabled = !command::can_delete_navy(state, state.local_player_nation, std::get<dcon::navy_id>(foru));
			}
		}
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				command::delete_army(state, state.local_player_nation, std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				command::delete_navy(state, state.local_player_nation, std::get<dcon::navy_id>(foru));
			}
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "disband_unit");
		}
	};

	class unit_row_remove : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				state.deselect(std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				state.deselect(std::get<dcon::navy_id>(foru));
			}
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "deselect_unit");
		}
	};

	class unit_row_split : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				command::evenly_split_army(state, state.local_player_nation, std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				command::evenly_split_navy(state, state.local_player_nation, std::get<dcon::navy_id>(foru));
			}
		}

		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				disabled = !command::can_evenly_split_army(state, state.local_player_nation, std::get<dcon::army_id>(foru));
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				disabled = !command::can_evenly_split_navy(state, state.local_player_nation, std::get<dcon::navy_id>(foru));
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "splitinhalf");
		}
	};

	class unit_row_new : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			auto* reorg_window = std::holds_alternative<dcon::army_id>(foru)
			? state.ui_state.army_reorg_window
			: state.ui_state.navy_reorg_window;
			bool keep_shown = false;
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto u = std::get<dcon::army_id>(foru);
				auto* win = static_cast<unit_reorg_window<dcon::army_id, dcon::regiment_id>*>(state.ui_state.army_reorg_window);
				keep_shown = win->unit_to_reorg != u && win->is_visible();
				win->unit_to_reorg = u;
				if(u) {
					reorg_window->set_visible(state, !reorg_window->is_visible() || keep_shown);
					reorg_window->impl_on_update(state);
				}
			} else {
				auto u = std::get<dcon::navy_id>(foru);
				auto* win = static_cast<unit_reorg_window<dcon::navy_id, dcon::ship_id>*>(state.ui_state.navy_reorg_window);
				keep_shown = win->unit_to_reorg != u && win->is_visible();
				win->unit_to_reorg = u;
				if(u) {
					reorg_window->set_visible(state, !reorg_window->is_visible() || keep_shown);
					reorg_window->impl_on_update(state);
				}
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "new_unit");
		}
	};

	template<int16_t A, int16_t B>
	class unit_row_unit_icon : public image_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				frame = A;
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				frame = B;
			}
		}
	};

	template<military::unit_type A, military::unit_type B>
	class unit_row_type_count : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			int32_t total = 0;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					auto type = state.military_definitions.unit_base_definitions[r.get_regiment().get_type()].type;
					if(type == A || (type == military::unit_type::special && A == military::unit_type::support)) {
						++total;
					}
				}
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					auto type = state.military_definitions.unit_base_definitions[r.get_ship().get_type()].type;
					if(type == B) {
						++total;
					}
				}
			}
			set_text(state, std::to_string(total));
		}
	};

	class unit_row_cav_count : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			int32_t total = 0;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					if(state.military_definitions.unit_base_definitions[r.get_regiment().get_type()].type == military::unit_type::cavalry) {
						++total;
					}
				}
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					if(state.military_definitions.unit_base_definitions[r.get_ship().get_type()].type == military::unit_type::light_ship) {
						++total;
					}
				}
			}

			set_text(state, std::to_string(total));
		}
	};

	class unit_row_art_count : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			int32_t total = 0;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				for(auto r : state.world.army_get_army_membership(a)) {
					if(state.military_definitions.unit_base_definitions[r.get_regiment().get_type()].type == military::unit_type::support || state.military_definitions.unit_base_definitions[r.get_regiment().get_type()].type == military::unit_type::special) {
						++total;
					}
				}
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				for(auto r : state.world.navy_get_navy_membership(a)) {
					if(state.military_definitions.unit_base_definitions[r.get_ship().get_type()].type == military::unit_type::transport) {
						++total;
					}
				}
			}
			set_text(state, std::to_string(total));
		}
	};

	class unit_row_location : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			dcon::province_id loc;
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				loc = state.world.army_get_location_from_army_location(a);
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				loc = state.world.navy_get_location_from_navy_location(a);
			}
			set_text(state, text::produce_simple_string(state, state.world.province_get_name(loc)));
		}
	};

	class unit_row_location_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			state.selected_armies.clear();
			state.selected_navies.clear();
			dcon::province_id loc;
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				loc = state.world.army_get_location_from_army_location(a);
				state.select(a);
				state.map_state.center_map_on_province(state, loc);
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				auto a = std::get<dcon::navy_id>(foru);
				loc = state.world.navy_get_location_from_navy_location(a);
				state.select(a);
				state.map_state.center_map_on_province(state, loc);
			}
		}
	};

	class unit_row_leader_image : public button_element_base {
		public:
		dcon::gfx_object_id default_img;

		void on_update(sys::state& state) noexcept override {
			if(!default_img) {
				if(base_data.get_element_type() == ui::element_type::image)
					default_img = base_data.data.image.gfx_object;
				else if(base_data.get_element_type() == ui::element_type::button)
					default_img = base_data.data.button.button_image;
			}

			auto foru = retrieve<unit_var>(state, parent);
			dcon::leader_id lid = retrieve<dcon::leader_id>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				disabled = !command::can_change_general(state, state.local_player_nation, std::get<dcon::army_id>(foru), dcon::leader_id{});
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
				disabled = !command::can_change_admiral(state, state.local_player_nation, std::get<dcon::navy_id>(foru), dcon::leader_id{});
			}

			auto pculture = state.world.nation_get_primary_culture(state.local_player_nation);
			auto ltype = pculture.get_group_from_culture_group_membership().get_leader();

			if(ltype && lid) {
				auto admiral = state.world.leader_get_is_admiral(lid);
				if(admiral) {
					auto arange = ltype.get_admirals();
					if(arange.size() > 0) {
						auto rval = rng::get_random(state, uint32_t(state.world.leader_get_since(lid).value), uint32_t(lid.value));
						auto in_range = rng::reduce(uint32_t(rval), arange.size());

						if(base_data.get_element_type() == ui::element_type::image)
							base_data.data.image.gfx_object = arange[in_range];
						else if(base_data.get_element_type() == ui::element_type::button)
							base_data.data.button.button_image = arange[in_range];
					}
				} else {
					auto grange = ltype.get_generals();
					if(grange.size() > 0) {
						auto rval = rng::get_random(state, uint32_t(state.world.leader_get_since(lid).value), uint32_t(lid.value));
						auto in_range = rng::reduce(uint32_t(rval), grange.size());

						if(base_data.get_element_type() == ui::element_type::image)
							base_data.data.image.gfx_object = grange[in_range];
						else if(base_data.get_element_type() == ui::element_type::button)
							base_data.data.button.button_image = grange[in_range];
					}
				}
			} else {
				if(base_data.get_element_type() == ui::element_type::image)
					base_data.data.image.gfx_object = default_img;
				else if(base_data.get_element_type() == ui::element_type::button)
					base_data.data.button.button_image = default_img;
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			dcon::leader_id lid = retrieve<dcon::leader_id>(state, parent);
			if(lid)
				display_leader_full(state, lid, contents, 0);
		}

		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			auto location = get_absolute_non_mirror_location(state, *this);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				open_leader_selection(state, std::get<dcon::army_id>(foru), dcon::navy_id{}, location.x + base_data.size.x, location.y);
			} else {
				open_leader_selection(state, dcon::army_id{}, std::get<dcon::navy_id>(foru), location.x + base_data.size.x, location.y);
			}
		}
		void button_right_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				command::change_general(state, state.local_player_nation, std::get<dcon::army_id>(foru), dcon::leader_id{});
			} else {
				command::change_admiral(state, state.local_player_nation, std::get<dcon::navy_id>(foru), dcon::leader_id{});
			}
		}
	};

	class unit_row_leader_button : public button_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			dcon::leader_id lid = retrieve<dcon::leader_id>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
			disabled = !command::can_change_general(state, state.local_player_nation, std::get<dcon::army_id>(foru), dcon::leader_id{});
			} else if(std::holds_alternative<dcon::navy_id>(foru)) {
			disabled = !command::can_change_admiral(state, state.local_player_nation, std::get<dcon::navy_id>(foru), dcon::leader_id{});
			}
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			dcon::leader_id lid = retrieve<dcon::leader_id>(state, parent);
			if(lid)
			display_leader_full(state, lid, contents, 0);
		}

		void button_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			auto location = get_absolute_non_mirror_location(state, *this);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				open_leader_selection(state, std::get<dcon::army_id>(foru), dcon::navy_id{}, location.x + base_data.size.x, location.y);
			} else {
				open_leader_selection(state, dcon::army_id{}, std::get<dcon::navy_id>(foru), location.x + base_data.size.x, location.y);
			}
		}
		void button_right_action(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				command::change_general(state, state.local_player_nation, std::get<dcon::army_id>(foru), dcon::leader_id{});
			} else {
				command::change_admiral(state, state.local_player_nation, std::get<dcon::navy_id>(foru), dcon::leader_id{});
			}
		}
	};
	class unit_row_leader_name : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			dcon::leader_id lid = retrieve<dcon::leader_id>(state, parent);
			auto name = state.to_string_view(state.world.leader_get_name(lid));
			set_text(state, std::string(name));
		}
	};

	class unit_row_select_only : public button_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			set_button_text(state, text::produce_simple_string(state, "unit_select_only"));
		}
		void button_action(sys::state& state) noexcept override {
			auto content = retrieve<unit_var>(state, parent);
			state.selected_armies.clear();
			state.selected_navies.clear();
			if(std::holds_alternative<dcon::army_id>(content)) {
				state.select(std::get<dcon::army_id>(content));
			} else if(std::holds_alternative<dcon::navy_id>(content)) {
				state.select(std::get<dcon::navy_id>(content));
			}
		}
	};

	class unit_row_leader_prestige_bar : public vertical_progress_bar {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::leader_id>(state, parent);
			progress = state.world.leader_get_prestige(content);
		}
	};

	class unit_row_name : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto foru = retrieve<unit_var>(state, parent);
			if(std::holds_alternative<dcon::army_id>(foru)) {
				auto a = std::get<dcon::army_id>(foru);
				auto name = state.to_string_view(state.world.army_get_name(a));
				set_text(state, std::string(name));
			} else {
				auto a = std::get<dcon::navy_id>(foru);
				auto name = state.to_string_view(state.world.navy_get_name(a));
				set_text(state, std::string(name));
			}
		}
	};

	class selected_unit_item : public listbox_row_element_base<unit_var> {
		public:
		void on_create(sys::state& state) noexcept override {
			base_data.size.y -= 20;
			listbox_row_element_base<unit_var>::on_create(state);
		}
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "unitpanel_bg") {
				return make_element_by_type<unit_row_panel_button>(state, id);
			} else if(name == "leader_photo") {
				return make_element_by_type<unit_row_leader_image>(state, id);
			} else if(name == "leader_button") {
				return make_element_by_type<unit_row_leader_button>(state, id);
			} else if(name == "unitleader") {
				return make_element_by_type<unit_row_leader_name>(state, id);
			} else if(name == "leader_prestige_bar") {
				return make_element_by_type<unit_row_leader_prestige_bar>(state, id);
			} else if(name == "unitstrength") {
				return make_element_by_type<unit_row_strength>(state, id);
			} else if(name == "unitattrition") {
				return make_element_by_type<unit_row_attrition_text>(state, id);
			} else if(name == "unitattrition_icon") {
				return make_element_by_type<unit_row_attrition_icon>(state, id);
			} else if(name == "org_bar") {
				return make_element_by_type<unit_row_org_bar>(state, id);
			} else if(name == "str_bar") {
				return make_element_by_type<unit_row_str_bar>(state, id);
			} else if(name == "disbandbutton") {
				return make_element_by_type<unit_row_disband>(state, id);
			} else if(name == "splitinhalf") {
				return make_element_by_type<unit_row_split>(state, id);
			} else if(name == "newunitbutton") {
				return make_element_by_type<unit_row_new>(state, id);
			} else if(name == "only_unit_from_selection_button") {
				return make_element_by_type<unit_row_select_only>(state, id);
			} else if(name == "remove_unit_from_selection_button") {
				return make_element_by_type<unit_row_remove>(state, id);
			} else if(name == "unit_inf") {
				return make_element_by_type<unit_row_unit_icon<0, 3>>(state, id);
			} else if(name == "unit_inf_count") {
				return make_element_by_type<unit_row_type_count<military::unit_type::infantry, military::unit_type::big_ship>>(state, id);
			} else if(name == "unit_cav") {
				return make_element_by_type<unit_row_unit_icon<1, 4>>(state, id);
			} else if(name == "unit_cav_count") {
				return make_element_by_type<unit_row_type_count<military::unit_type::cavalry, military::unit_type::light_ship>>(state, id);
			} else if(name == "unit_art") {
				return make_element_by_type<unit_row_unit_icon<2, 5>>(state, id);
			} else if(name == "unit_art_count") {
				return make_element_by_type<unit_row_type_count<military::unit_type::support, military::unit_type::transport>>(state, id);
			} else if(name == "unit_location_button") {
				return make_element_by_type<unit_row_location_button>(state, id);
			} else if(name == "unitlocation") {
				return make_element_by_type<unit_row_location>(state, id);
			} else if(name == "unitname") {
				return make_element_by_type<unit_row_name>(state, id);
			} else {
				return nullptr;
			}
		}
		message_result get(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<dcon::leader_id>()) {
				dcon::leader_id lid;
				if(std::holds_alternative<dcon::army_id>(content)) {
					lid = state.world.army_get_general_from_army_leadership(std::get<dcon::army_id>(content));
				} else if(std::holds_alternative<dcon::navy_id>(content)) {
					lid = state.world.navy_get_admiral_from_navy_leadership(std::get<dcon::navy_id>(content));
				}
				payload.emplace<dcon::leader_id>(lid);
				return message_result::consumed;
			}
			return listbox_row_element_base<unit_var>::get(state, payload);
		}
	};

	class multi_unit_selected_unit_list : public listbox_element_base<selected_unit_item, unit_var> {
		public:
		std::string_view get_row_element_name() override {
			return "unitpanel";
		}
		void on_update(sys::state& state) noexcept override {
			row_contents.clear();
			for(auto i : state.selected_armies)
			row_contents.push_back(i);
			for(auto i : state.selected_navies)
			row_contents.push_back(i);
			update(state);
		}
	};

	class multi_unit_details_ai_controlled : public checkbox_button {
		bool visible = true;
		public:
		bool is_active(sys::state& state) noexcept override {
			for(auto i : state.selected_armies) {
				if(state.world.army_get_is_ai_controlled(i) == false)
				return false;
			}
			return true;
		}
		void on_update(sys::state& state) noexcept override {
			checkbox_button::on_update(state);
			visible = state.selected_navies.empty();
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "vce_ai_controlled_unit");
		}
		void button_action(sys::state& state) noexcept override {
			bool all_on = true;
			for(auto i : state.selected_armies) {
				if(state.world.army_get_is_ai_controlled(i) == false) {
					all_on = false;
					break;
				}
			}
			for(auto a : state.selected_armies) {
				if(all_on) { //all on -> turn all off
					command::toggle_unit_ai_control(state, state.local_player_nation, a);
				} else { //some on -> turn all that are off into on, all off -> turn all on
					if(!state.world.army_get_is_ai_controlled(a)) {
						command::toggle_unit_ai_control(state, state.local_player_nation, a);
					}
				}
			}
		}
		void render(sys::state& state, int32_t x, int32_t y) noexcept override {
			if(visible)
			checkbox_button::render(state, x, y);
		}
	};
	class multi_unit_selected_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			text::substitution_map m;
			text::add_to_substitution_map(m, text::variable_type::x, int64_t(state.selected_armies.size() + state.selected_navies.size()));
			set_text(state, text::resolve_string_substitution(state, "multiunit_header", m));
		}
	};
	class multi_unit_merge_all_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			if(state.selected_armies.size() > 0) {
				auto first = state.selected_armies[0];
				for(uint32_t i = 1; i < state.selected_armies.size(); ++i) {
					command::merge_armies(state, state.local_player_nation, first, state.selected_armies[i]);
				}
			}
			if(state.selected_navies.size() > 0) {
				auto first = state.selected_navies[0];
				for(uint32_t i = 1; i < state.selected_navies.size(); ++i) {
					command::merge_navies(state, state.local_player_nation, first, state.selected_navies[i]);
				}
			}
		}
		void on_update(sys::state& state) noexcept override {
			disabled = true;
			if(state.selected_armies.size() > 0) {
				auto first = state.selected_armies[0];
				for(uint32_t i = 1; i < state.selected_armies.size(); ++i) {
					if(command::can_merge_armies(state, state.local_player_nation, first, state.selected_armies[i])) {
						disabled = false;
						break;
					}
				}
			}
			if(state.selected_navies.size() > 0) {
				auto first = state.selected_navies[0];
				for(uint32_t i = 1; i < state.selected_navies.size(); ++i) {
					if(command::can_merge_navies(state, state.local_player_nation, first, state.selected_navies[i])) {
						disabled = false;
						break;
					}
				}
			}
		}
	};
	class multi_unit_deselect_all_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			state.selected_armies.clear();
			state.selected_navies.clear();
			state.game_state_updated.store(true, std::memory_order_release);
		}
	};
	class multi_unit_disband_all_button : public button_element_base {
		public:
		void button_action(sys::state& state) noexcept override {
			for(auto a : state.selected_armies) {
				command::delete_army(state, state.local_player_nation, a);
			}
			for(auto a : state.selected_navies) {
				command::delete_navy(state, state.local_player_nation, a);
			}
		}
		void on_update(sys::state& state) noexcept override {
			disabled = true;
			if(state.selected_armies.size() > 0) {
				for(uint32_t i = 1; i < state.selected_armies.size(); ++i) {
					if(command::can_delete_army(state, state.local_player_nation, state.selected_armies[i])) {
						disabled = false;
						break;
					}
				}
			}
			if(state.selected_navies.size() > 0) {
				for(uint32_t i = 1; i < state.selected_navies.size(); ++i) {
					if(command::can_delete_navy(state, state.local_player_nation, state.selected_navies[i])) {
						disabled = false;
						break;
					}
				}
			}
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			text::add_line(state, contents, "disband_all");
		}
	};
	class mulit_unit_selection_panel : public window_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			auto lb = make_element_by_type<multi_unit_selected_unit_list>(state, "unit_listbox");
			add_child_to_front(std::move(lb));
		}

		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "desc") {
				return make_element_by_type<multi_unit_selected_text>(state, id);
			} else if(name == "mergebutton") {
				return make_element_by_type<multi_unit_merge_all_button>(state, id);
			} else if(name == "reorganizebutton") {
				//TODO: implement
				return make_element_by_type<invisible_element>(state, id);
			} else if(name == "close_multiunit") {
				return make_element_by_type<multi_unit_deselect_all_button>(state, id);
			} else if(name == "disband_multiunit") {
				return make_element_by_type<multi_unit_disband_all_button>(state, id);
			} else if(name == "multiunit_slider") {
				return make_element_by_type<invisible_element>(state, id);
			} else {
				return nullptr;
			}
		}
	};

} // namespace ui
