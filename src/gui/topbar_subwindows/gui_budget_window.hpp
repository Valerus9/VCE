#pragma once

#include "color.hpp"
#include "commands.hpp"
#include "culture.hpp"
#include "dcon.hpp"
#include "gui_common_elements.hpp"
#include "gui_element_types.hpp"
#include "nations.hpp"
#include "system_state.hpp"
#include "text.hpp"
#include "economy_estimations.hpp"

namespace ui {
	class nation_gold_income_text : public simple_text_element_base {
	public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, text::format_money(economy_estimations::estimate_gold_income(state, state.local_player_nation)));
		}
	};

	class nation_loan_spending_text : public simple_text_element_base {
	public:
		void on_update(sys::state& state) noexcept override;
	};

	class nation_diplomatic_balance_text : public simple_text_element_base {
	public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, text::format_money(economy_estimations::estimate_diplomatic_balance(state, state.local_player_nation)));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override;
	};

	class nation_subsidy_spending_text : public simple_text_element_base {
	public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, text::format_money(economy_estimations::estimate_subsidy_spending(state, state.local_player_nation)));
		}
	};

	class nation_administrative_efficiency_text : public simple_text_element_base {
	public:
		void on_update(sys::state& state) noexcept override {
			set_text(state, text::format_percentage(state.world.nation_get_administrative_efficiency(state.local_player_nation)));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override;
	};

	enum class budget_slider_target : uint8_t {
		poor_tax,
		middle_tax,
		rich_tax,
		army_stock,
		navy_stock,
		construction_stock,
		education,
		admin,
		social,
		military,
		tariffs,
		domestic_investment,
		raw,
		//
		overseas,
		stockpile_filling,
		diplomatic_interest,
		interest,
		subsidies,
		gold_income,
		//
		target_count
	};

	enum class slider_scaling : uint8_t {
		linear,
		quadratic
	};

	struct budget_slider_signal {
		budget_slider_target target = budget_slider_target::poor_tax;
		float amount = 0.f;
	};

	template<budget_slider_target SliderTarget, slider_scaling SliderDisplayScaling>
	class budget_slider : public scrollbar {
		public:

		void on_create(sys::state& state) noexcept final {
			if(base_data.get_element_type() == element_type::scrollbar) {
				auto step = base_data.data.scrollbar.get_step_size();
				settings.scaling_factor = 1;
				switch(step) {
					case step_size::twenty_five:
					break;
					case step_size::two:
					break;
					case step_size::one:
					break;
					case step_size::one_tenth:
					settings.scaling_factor = 10;
					break;
					case step_size::one_hundredth:
					settings.scaling_factor = 100;
					break;
					case step_size::one_thousandth:
					settings.scaling_factor = 1000;
					break;
				}
				settings.lower_value = 0;
				settings.upper_value = base_data.data.scrollbar.max_value * settings.scaling_factor;
				settings.lower_limit = 0;
				settings.upper_limit = settings.upper_value;

				settings.vertical = !base_data.data.scrollbar.is_horizontal();
				stored_value = settings.lower_value;

				auto first_child = base_data.data.scrollbar.first_child;
				auto num_children = base_data.data.scrollbar.num_children;

				if(num_children >= 6) {
					auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(5 + first_child.index()));
					auto ch_res = make_element_by_type<image_element_base>(state, child_tag);
					right_limit = ch_res.get();
					right_limit->set_visible(state, false);
					add_child_to_back(std::move(ch_res));
				}
				if(num_children >= 5) {
					auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(4 + first_child.index()));
					auto ch_res = make_element_by_type<image_element_base>(state, child_tag);
					left_limit = ch_res.get();
					left_limit->set_visible(state, false);
					add_child_to_back(std::move(ch_res));
				}

				if(num_children >= 4) {
					{
						auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(2 + first_child.index()));
						auto ch_res = make_element_by_type<scrollbar_slider>(state, child_tag);
						slider = ch_res.get();
						add_child_to_back(std::move(ch_res));
					}
					{
						auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(0 + first_child.index()));
						auto ch_res = make_element_by_type<scrollbar_left>(state, child_tag);
						left = ch_res.get();
						add_child_to_back(std::move(ch_res));

						settings.buttons_size = settings.vertical ? left->base_data.size.y : left->base_data.size.x;
						if(step_size::twenty_five == step)
						left->step_size = 25;
						else if(step_size::two == step)
						left->step_size = 2;
						else
						left->step_size = 1;
					}
					{
						auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(1 + first_child.index()));
						auto ch_res = make_element_by_type<scrollbar_right>(state, child_tag);
						//ui::element_base* test = ch_res.get();
						right = ch_res.get();
						add_child_to_back(std::move(ch_res));

						if(step_size::twenty_five == step)
						right->step_size = 25;
						else if(step_size::two == step)
						right->step_size = 2;
						else
						right->step_size = 1;
					}
					{
						auto child_tag = dcon::gui_def_id(dcon::gui_def_id::value_base_t(3 + first_child.index()));
						auto ch_res = make_element_by_type<scrollbar_track>(state, child_tag);
						track = ch_res.get();
						add_child_to_back(std::move(ch_res));

						settings.track_size = settings.vertical ? track->base_data.size.y : track->base_data.size.x;
					}
					left->base_data.position.x = 0;
					left->base_data.position.y = 0;
					if(settings.vertical) {
						track->base_data.position.y = int16_t(settings.buttons_size);
						slider->base_data.position.y = int16_t(settings.buttons_size);
						right->base_data.position.y = int16_t(settings.track_size + settings.buttons_size);
						// track->base_data.position.x = 0;
						slider->base_data.position.x = 0;
						right->base_data.position.x = 0;
					} else {
						track->base_data.position.x = int16_t(settings.buttons_size);
						slider->base_data.position.x = int16_t(settings.buttons_size);
						right->base_data.position.x = int16_t(settings.track_size + settings.buttons_size);
						// track->base_data.position.y = 0;
						slider->base_data.position.y = 0;
						right->base_data.position.y = 0;
					}
				}
			}
		}
		void on_value_change(sys::state& state, int32_t v) noexcept final {
			if(parent) {
				float amount = float(v) / 100.0f;
				switch(SliderDisplayScaling) {
					case ui::slider_scaling::linear:
					break;
					case ui::slider_scaling::quadratic:
					amount = amount * amount;
					break;
					default:
					break;
				}
			send(state, parent, budget_slider_signal{ SliderTarget, amount });
			}
			if(state.ui_state.drag_target != slider)
			commit_changes(state);
		}

		void on_update(sys::state& state) noexcept final {
			auto n = state.local_player_nation;
			switch(SliderTarget) {
				case budget_slider_target::poor_tax:
				case budget_slider_target::middle_tax:
				case budget_slider_target::rich_tax: {
					auto min_tax = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::min_tax));
					auto max_tax = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_tax));
					min_tax = std::max(min_tax, 0);
					max_tax = std::max(min_tax, max_tax <= 0 ? 100 : max_tax);

					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_tax, 0, 100);
					new_settings.upper_limit = std::clamp(max_tax, 0, 100);
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::social: {
					auto min_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::min_social_spending));
					auto max_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_social_spending));
					min_spend = std::max(min_spend, 0);
					max_spend = std::max(min_spend, max_spend <= 0 ? 100 : max_spend);

					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spend, 0, 100);
					new_settings.upper_limit = std::clamp(max_spend, 0, 100);
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::military: {
					auto min_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::min_military_spending));
					auto max_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_military_spending));
					min_spend = std::max(min_spend, 0);
					max_spend = std::max(min_spend, max_spend <= 0 ? 100 : max_spend);

					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spend, 0, 100);
					new_settings.upper_limit = std::clamp(max_spend, 0, 100);
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::tariffs: {
					auto min_tariff = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::min_tariff));
					auto max_tariff = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_tariff));
					min_tariff = std::max(min_tariff, 0);
					max_tariff = std::max(min_tariff, max_tariff <= 0 ? 100 : max_tariff);

					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_tariff, 0, 100);
					new_settings.upper_limit = std::clamp(max_tariff, 0, 100);
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::domestic_investment:
				{
					auto min_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::min_domestic_investment));
					auto max_spend = int32_t(100.0f * state.world.nation_get_modifier_values(n, sys::national_mod_offsets::max_domestic_investment));
					min_spend = std::max(min_spend, 0);
					max_spend = std::max(min_spend, max_spend <= 0 ? 100 : max_spend);

					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spend, 0, 100);
					new_settings.upper_limit = std::clamp(max_spend, 0, 100);
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::construction_stock:
				{
					auto min_spending = int32_t(100.0f * state.defines.trade_cap_low_limit_constructions);
					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spending, 0, 100);
					new_settings.upper_limit = 100;
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::army_stock:
				{
					auto min_spending = int32_t(100.0f * state.defines.trade_cap_low_limit_land);
					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spending, 0, 100);
					new_settings.upper_limit = 100;
					change_settings(state, new_settings);
				} break;
				case budget_slider_target::navy_stock:
				{
					auto min_spending = int32_t(100.0f * state.defines.trade_cap_low_limit_naval);
					mutable_scrollbar_settings new_settings;
					new_settings.lower_value = 0;
					new_settings.upper_value = 100;
					new_settings.using_limits = true;
					new_settings.lower_limit = std::clamp(min_spending, 0, 100);
					new_settings.upper_limit = 100;
					change_settings(state, new_settings);
				} break;
				default:
				break;
			}

			int32_t v = 0;
			if(state.ui_state.drag_target == slider) {
				v = int32_t(scaled_value());
			} else {
				v = get_true_value(state);
				update_raw_value(state, v);
			}

			if(parent) {
				float amount = float(v) / 100.f;
				switch(SliderDisplayScaling) {
					case ui::slider_scaling::linear:
					break;
					case ui::slider_scaling::quadratic:
					amount = amount * amount;
					break;
					default:
					break;
				}
			Cyto::Any payload = budget_slider_signal{SliderTarget, amount};
				parent->impl_set(state, payload);
			}
		}

		virtual int32_t get_true_value(sys::state& state) noexcept {
			return 0;
		}

		void on_drag_finish(sys::state& state) noexcept override {
			commit_changes(state);
		}

		private:
		void commit_changes(sys::state& state) noexcept {
			auto budget_settings = command::make_empty_budget_settings();
			update_budget_settings(budget_settings);
			command::change_budget_settings(state, state.local_player_nation, budget_settings);
		}

		void update_budget_settings(command::budget_settings_data& budget_settings) noexcept {
			auto new_val = int8_t(scaled_value());
			switch(SliderTarget) {
				case budget_slider_target::poor_tax:
				budget_settings.poor_tax = new_val;
				break;
				case budget_slider_target::middle_tax:
				budget_settings.middle_tax = new_val;
				break;
				case budget_slider_target::rich_tax:
				budget_settings.rich_tax = new_val;
				break;
				case budget_slider_target::army_stock:
				budget_settings.land_spending = new_val;
				break;
				case budget_slider_target::navy_stock:
				budget_settings.naval_spending = new_val;
				break;
				case budget_slider_target::construction_stock:
				budget_settings.construction_spending = new_val;
				break;
				case budget_slider_target::education:
				budget_settings.education_spending = new_val;
				break;
				case budget_slider_target::admin:
				budget_settings.administrative_spending = new_val;
				break;
				case budget_slider_target::social:
				budget_settings.social_spending = new_val;
				break;
				case budget_slider_target::military:
				budget_settings.military_spending = new_val;
				break;
				case budget_slider_target::tariffs:
				budget_settings.tariffs = new_val;
				break;
				case budget_slider_target::domestic_investment:
				budget_settings.domestic_investment = new_val;
				break;
				case budget_slider_target::overseas:
				budget_settings.overseas = new_val;
				break;
				default:
				break;
			}
		}
	};


	class budget_poor_tax_slider : public budget_slider<budget_slider_target::poor_tax, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_poor_tax(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);

			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::tax_efficiency, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_tax, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_tax, true);
		}
	};

	class budget_middle_tax_slider : public budget_slider<budget_slider_target::middle_tax, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_middle_tax(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);

			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::tax_efficiency, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_tax, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_tax, true);
		}
	};

	class budget_rich_tax_slider : public budget_slider<budget_slider_target::rich_tax, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_rich_tax(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
			text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);

			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::tax_efficiency, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_tax, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_tax, true);
		}
	};

	class budget_army_stockpile_slider : public budget_slider<budget_slider_target::army_stock, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_land_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			{
				auto box = text::open_layout_box(contents, 0);
				text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
				text::close_layout_box(contents, box);
			}
			uint32_t total_commodities = state.world.commodity_size();
			for(uint32_t i = 1; i < total_commodities; ++i) {
				dcon::commodity_id cid{ dcon::commodity_id::value_base_t(i) };
				auto cost = state.world.commodity_get_current_price(cid);
				auto amount = state.world.nation_get_army_demand(n, cid);
				if(amount > 0.f) {
					text::substitution_map m;
					text::add_to_substitution_map(m, text::variable_type::name, state.world.commodity_get_name(cid));
					text::add_to_substitution_map(m, text::variable_type::val, text::fp_currency{ cost });
					text::add_to_substitution_map(m, text::variable_type::need, text::fp_four_places{ amount });
					text::add_to_substitution_map(m, text::variable_type::cost, text::fp_currency{ cost * amount });
					auto box = text::open_layout_box(contents, 0);
					text::localised_format_box(state, contents, box, "vce_spending_commodity", m);
					text::close_layout_box(contents, box);
				}
			}
		}
	};

	class budget_navy_stockpile_slider : public budget_slider<budget_slider_target::navy_stock, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_naval_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			{
				auto box = text::open_layout_box(contents, 0);
				text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
				text::close_layout_box(contents, box);
			}
			uint32_t total_commodities = state.world.commodity_size();
			for(uint32_t i = 1; i < total_commodities; ++i) {
				dcon::commodity_id cid{ dcon::commodity_id::value_base_t(i) };
				auto cost = state.world.commodity_get_current_price(cid);
				auto amount = state.world.nation_get_navy_demand(n, cid);
				if(amount > 0.f) {
					text::substitution_map m;
					text::add_to_substitution_map(m, text::variable_type::name, state.world.commodity_get_name(cid));
					text::add_to_substitution_map(m, text::variable_type::val, text::fp_currency{ cost });
					text::add_to_substitution_map(m, text::variable_type::need, text::fp_four_places{ amount });
					text::add_to_substitution_map(m, text::variable_type::cost, text::fp_currency{ cost * amount });
					auto box = text::open_layout_box(contents, 0);
					text::localised_format_box(state, contents, box, "vce_spending_commodity", m);
					text::close_layout_box(contents, box);
				}
			}
		}
	};

	class budget_construction_stockpile_slider : public budget_slider<budget_slider_target::construction_stock, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_construction_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			{
				auto box = text::open_layout_box(contents, 0);
				text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
				text::close_layout_box(contents, box);
			}
			uint32_t total_commodities = state.world.commodity_size();
			for(uint32_t i = 1; i < total_commodities; ++i) {
				dcon::commodity_id cid{ dcon::commodity_id::value_base_t(i) };
				auto cost = economy::commodity_effective_price(state, n, cid);
				auto amount = state.world.nation_get_construction_demand(n, cid);
				if(amount > 0.f) {
					text::substitution_map m;
					text::add_to_substitution_map(m, text::variable_type::name, state.world.commodity_get_name(cid));
					text::add_to_substitution_map(m, text::variable_type::val, text::fp_currency{ cost });
					text::add_to_substitution_map(m, text::variable_type::need, text::fp_four_places{ amount });
					text::add_to_substitution_map(m, text::variable_type::cost, text::fp_currency{ cost * amount });
					auto box = text::open_layout_box(contents, 0);
					text::localised_format_box(state, contents, box, "vce_spending_commodity", m);
					text::close_layout_box(contents, box);
				}
			}
		}
	};

	class budget_education_slider : public budget_slider<budget_slider_target::education, slider_scaling::quadratic> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_education_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);
		}
	};

	class budget_administration_slider : public budget_slider<budget_slider_target::admin, slider_scaling::quadratic> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_administrative_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);
		}
	};

	class budget_social_spending_slider : public budget_slider<budget_slider_target::social, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_social_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_social_spending, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_social_spending, true);
		}
	};

	class budget_military_spending_slider : public budget_slider<budget_slider_target::military, slider_scaling::quadratic> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_military_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_military_spending, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_military_spending, true);
		}
	};

	class budget_tariff_slider : public budget_slider<budget_slider_target::tariffs, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_tariffs(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::close_layout_box(contents, box);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::tariff_efficiency_modifier, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::min_tariff, true);
			active_modifiers_description(state, contents, n, 0, sys::national_mod_offsets::max_tariff, true);
		}
	};

	class budget_scaled_monetary_value_text : public color_text_element {
		private:
		std::array<float, size_t(budget_slider_target::target_count)> values;
		std::array<float, size_t(budget_slider_target::target_count)> multipliers;

		public:
		bool expense = false;

	virtual void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept { }

		void on_create(sys::state& state) noexcept override {
			color_text_element::on_create(state);
			color = text::text_color::black;
			for(uint8_t i = 0; i < uint8_t(budget_slider_target::target_count); ++i) {
				values[i] = 0.f;
				multipliers[i] = 1.f;
			}
		}

		void apply_multipliers(sys::state& state) noexcept {
			auto total = 0.f;
			for(uint8_t i = 0; i < uint8_t(budget_slider_target::target_count); ++i)
			total += values[i] * multipliers[i];

			if(expense)
			total = -total;

			if(total < 0.0f) {
				color = text::text_color::dark_red;
				set_text(state, text::format_money(total)); //automatically adds a - when negative
			} else if(total > 0.0f) {
				color = text::text_color::dark_green;
				set_text(state, text::format_money(total));
			} else {
				color = text::text_color::black;
				set_text(state, text::format_money(total));
			}
		}

		void on_update(sys::state& state) noexcept override {
			put_values(state, values);
			apply_multipliers(state);
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);

			float total = 0.f;
			float total_exp = 0.f;
			float total_inc = 0.f;
			for(uint8_t i = 0; i < uint8_t(budget_slider_target::target_count); ++i) {
				float v = values[i] * multipliers[i];
				if(expense)
				v = -v;
				if(v < 0.f)
				total_exp += v;
				else
				total_inc += v;
				total += v;
			}
			if(total_inc != 0.f) {
			text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_inc", text::variable_type::value, text::fp_currency{ total_inc });
				text::add_line_break_to_layout_box(state, contents, box);
				for(uint8_t i = 0; i < uint8_t(budget_slider_target::target_count); ++i) {
					float v = values[i] * multipliers[i];
					if(expense)
					v = -v;
					if(v > 0.f) {
						switch(budget_slider_target(i)) {
							case budget_slider_target::poor_tax:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_1", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::middle_tax:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_2", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::rich_tax:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_3", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::tariffs:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_4", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::gold_income:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_17", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::diplomatic_interest:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_16", text::variable_type::value, text::fp_currency{ v });
							break;
							default:
							break;
						}
						text::add_line_break_to_layout_box(state, contents, box);
					}
				}
			}
			if(total_exp != 0.f) {
			text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_exp", text::variable_type::value, text::fp_currency{ total_exp });
				text::add_line_break_to_layout_box(state, contents, box);
				for(uint8_t i = 0; i < uint8_t(budget_slider_target::target_count); ++i) {
					float v = values[i] * multipliers[i];
					if(expense)
					v = -v;
					if(v < 0.f) {
						switch(budget_slider_target(i)) {
							case budget_slider_target::army_stock:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_5", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::navy_stock:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_6", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::construction_stock:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_7", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::education:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_8", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::admin:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_9", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::social:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_10", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::military:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_11", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::domestic_investment:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_12", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::overseas:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_13", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::stockpile_filling:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_14", text::variable_type::value, text::fp_currency{ v });
							break;
							case budget_slider_target::subsidies:
						text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_15", text::variable_type::value, text::fp_currency{ v });
							break;
							default:
							break;
						}
						text::add_line_break_to_layout_box(state, contents, box);
					}
				}
			}
			if(total != 0.f) {
			text::localised_single_sub_box(state, contents, box, "vce_budget_scaled_net", text::variable_type::value, text::fp_currency{ total });
				text::add_line_break_to_layout_box(state, contents, box);
			}
			text::close_layout_box(contents, box);
		}

		message_result set(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<budget_slider_signal>()) {
				auto sig = any_cast<budget_slider_signal>(payload);
				multipliers[uint8_t(sig.target)] = sig.amount;
				if(values[uint8_t(sig.target)] != 0.f)
				apply_multipliers(state);
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};

	class budget_actual_stockpile_spending_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::stockpile_filling)] =
			economy_estimations::estimate_stockpile_filling_spending(state, state.local_player_nation);
		}
	};

	class budget_estimated_stockpile_spending_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::construction_stock)] = economy_estimations::estimate_construction_spending(state, state.local_player_nation);
			vals[uint8_t(budget_slider_target::army_stock)] = economy_estimations::estimate_land_spending(state, state.local_player_nation);
			vals[uint8_t(budget_slider_target::navy_stock)] = economy_estimations::estimate_naval_spending(state, state.local_player_nation);
		}
	};

	class budget_military_spending_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::army_stock)] = economy_estimations::estimate_land_spending(state, state.local_player_nation);
			vals[uint8_t(budget_slider_target::navy_stock)] = economy_estimations::estimate_naval_spending(state, state.local_player_nation);
		}
	};

	class budget_overseas_spending_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::overseas)] =
			economy_estimations::estimate_overseas_penalty_spending(state, state.local_player_nation);
		}
	};

	class budget_tariff_income_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::tariffs)] = economy_estimations::estimate_tariff_income(state, state.local_player_nation);
		}
	};

	template<culture::pop_strata Strata, budget_slider_target BudgetTarget>
	class budget_stratified_tax_income_text : public budget_scaled_monetary_value_text {
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(BudgetTarget)] = economy_estimations::estimate_tax_income_by_strata(state, state.local_player_nation, Strata);
		}
	};

	template<culture::income_type IncomeType, budget_slider_target BudgetTarget>
	class budget_expenditure_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(BudgetTarget)] = economy_estimations::estimate_pop_payouts_by_income_type(state, state.local_player_nation, IncomeType);
		}
	};

	class budget_social_spending_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::social)] = economy_estimations::estimate_social_spending(state, state.local_player_nation);
		}
	};

	class budget_income_projection_text : public budget_scaled_monetary_value_text {
		public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override {
			vals[uint8_t(budget_slider_target::poor_tax)] =
				economy_estimations::estimate_tax_income_by_strata(state, state.local_player_nation, culture::pop_strata::poor);
			vals[uint8_t(budget_slider_target::middle_tax)] =
				economy_estimations::estimate_tax_income_by_strata(state, state.local_player_nation, culture::pop_strata::middle);
			vals[uint8_t(budget_slider_target::rich_tax)] =
				economy_estimations::estimate_tax_income_by_strata(state, state.local_player_nation, culture::pop_strata::rich);
			vals[uint8_t(budget_slider_target::gold_income)] = economy_estimations::estimate_gold_income(state, state.local_player_nation);
		}
	};

	class budget_expenditure_projection_text : public budget_scaled_monetary_value_text {
	public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override;
	};

	class budget_balance_projection_text : public budget_scaled_monetary_value_text {
	public:
		void put_values(sys::state& state, std::array<float, size_t(budget_slider_target::target_count)>& vals) noexcept override;
	};

	class budget_take_loan_button : public button_element_base {
	public:
		void button_action(sys::state& state) noexcept override {
			if(parent) {
				Cyto::Any payload = element_selection_wrapper<bool>{bool{true}};
				parent->impl_get(state, payload);
			}
		}
	};

	// NOTE for simplicity sake we use a payload with bool{true} for taking loan window and a payload with bool{false} for repaying
	// loan window
	class budget_repay_loan_button : public button_element_base {
	public:
		void button_action(sys::state& state) noexcept override {
			if(parent) {
			Cyto::Any payload = element_selection_wrapper<bool>{bool{false}};
				parent->impl_get(state, payload);
			}
		}
	};

	class budget_take_loan_window : public window_element_base {
	public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "bg") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "take_loan_label") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "ok") {
				return make_element_by_type<button_element_base>(state, id);
			} else if(name == "cancel") {
				return make_element_by_type<generic_close_button>(state, id);
			} else if(name == "money_value") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} /*else if(name == "money_slider") {
				return nullptr;
			}*/
			else {
				return nullptr;
			}
		}
	};

	class budget_repay_loan_window : public window_element_base {
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "bg") {
				return make_element_by_type<image_element_base>(state, id);
			} else if(name == "repay_loan_label") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} else if(name == "ok") {
				return make_element_by_type<button_element_base>(state, id);
			} else if(name == "cancel") {
				return make_element_by_type<generic_close_button>(state, id);
			} else if(name == "money_value") {
				return make_element_by_type<simple_text_element_base>(state, id);
			} /*else if(name == "money_slider") {
				return nullptr;
			}*/
			else {
				return nullptr;
			}
		}
	};

	class tax_list_pop_type_icon : public opaque_element_base {
	public:
		dcon::pop_type_id type{};
		void set_type(sys::state& state, dcon::pop_type_id t) {
			type = t;
			frame = int32_t(state.world.pop_type_get_sprite(t) - 1);
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void on_update(sys::state& state) noexcept override {
			auto total_pop = state.world.nation_get_demographics(state.local_player_nation, demographics::to_key(state, type));
			disabled = total_pop < 1.0f;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override;
	};

	class budget_pop_list_item : public window_element_base {
	private:
		tax_list_pop_type_icon* pop_type_icon = nullptr;
	public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "pop") {
				auto ptr = make_element_by_type<tax_list_pop_type_icon>(state, id);
				pop_type_icon = ptr.get();
				return ptr;
			} else {
				return nullptr;
			}
		}

		message_result get(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<wrapped_listbox_row_content<dcon::pop_type_id>>()) {
				auto pop_type_id = any_cast<wrapped_listbox_row_content<dcon::pop_type_id>>(payload).content;
				pop_type_icon->set_type(state, pop_type_id);
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};

	template<culture::pop_strata Strata>
	class budget_pop_tax_list : public overlapping_listbox_element_base<budget_pop_list_item, dcon::pop_type_id> {
		protected:
		std::string_view get_row_element_name() override {
			return "pop_listitem";
		}

		public:
		void on_create(sys::state& state) noexcept override {
			overlapping_listbox_element_base<budget_pop_list_item, dcon::pop_type_id>::on_create(state);
			state.world.for_each_pop_type([&](dcon::pop_type_id pt) {
				if(state.world.pop_type_get_strata(pt) == uint8_t(Strata)) {
					row_contents.push_back(pt);
				}
			});
			update(state);
		}
	};

	template<culture::income_type Income>
	class budget_pop_income_list : public overlapping_listbox_element_base<budget_pop_list_item, dcon::pop_type_id> {
		protected:
		std::string_view get_row_element_name() override {
			return "pop_listitem";
		}

		public:
		void on_create(sys::state& state) noexcept override {
			overlapping_listbox_element_base<budget_pop_list_item, dcon::pop_type_id>::on_create(state);
			state.world.for_each_pop_type([&](dcon::pop_type_id pt) {
				if(state.world.pop_type_get_life_needs_income_type(pt) == uint8_t(Income) ||
					state.world.pop_type_get_everyday_needs_income_type(pt) == uint8_t(Income) ||
					state.world.pop_type_get_luxury_needs_income_type(pt) == uint8_t(Income)) {
					row_contents.push_back(pt);
				}
			});
			update(state);
		}
	};

	template<culture::income_type Income>
	class budget_small_pop_income_list : public budget_pop_income_list<Income> {
		protected:
		std::string_view get_row_element_name() override {
			return "pop_listitem_small";
		}
	};

	class budget_tariff_percentage_text : public simple_text_element_base {
		public:
		message_result set(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<budget_slider_signal>()) {
				auto sig = any_cast<budget_slider_signal>(payload);
				if(sig.target == budget_slider_target::tariffs) {
					set_text(state, text::format_percentage(sig.amount));
				}
				return message_result::consumed;
			}
			return message_result::unseen;
		}

		void on_update(sys::state& state) noexcept override {
			auto nation_id = retrieve<dcon::nation_id>(state, parent);
			set_text(state, text::format_percentage(float(state.world.nation_get_tariffs(nation_id)) / 100.0f));
		}
	};

	class debt_piechart : public piechart<dcon::nation_id> {
		public:
		void on_update(sys::state& state) noexcept override {
			distribution.clear();
			auto t = state.world.nation_get_stockpiles(state.local_player_nation, economy::money);

			if(t < 0.0f) {
				int32_t num_gp = 7;
				if(t <= 1000.0f) {
					num_gp = 1;
				} else if(t <= 2000.0f) {
					num_gp = 2;
				} else if(t <= 4000.0f) {
					num_gp = 4;
				}

				float share = 10.0f;
				for(auto n : state.nations_by_rank) {
					if(state.world.nation_get_is_great_power(n) && n != state.local_player_nation) {
						distribution.emplace_back(n, share);
						share -= 1.0f;

						--num_gp;
						if(num_gp <= 0)
						break;
					}
				}
			}
			update_chart(state);
		}
	};

	struct debt_item_data {
		dcon::nation_id n;
		float amount;

		bool operator==(debt_item_data o) const noexcept {
			return n == o.n && amount == o.amount;
		}
		bool operator!=(debt_item_data o) const noexcept {
			return !(*this == o);
		}
	};

	class debtor_name : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			debt_item_data dat = retrieve< debt_item_data>(state, parent);
			set_text(state, text::produce_simple_string(state, text::get_name(state, dat.n)));
		}
	};

	class debtor_amount : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			debt_item_data dat = retrieve< debt_item_data>(state, parent);
			set_text(state, text::format_money(dat.amount));
		}
	};


	class debt_item : public listbox_row_element_base<debt_item_data> {
		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "who") {
				return make_element_by_type<debtor_name>(state, id);
			} else if(name == "debt") {
				return make_element_by_type<debtor_amount>(state, id);
			} else {
				return nullptr;
			}
		}
	};

	class debt_listbox : public listbox_element_base<debt_item, debt_item_data> {
		protected:
		std::string_view get_row_element_name() override {
			return "debt_listitem";
		}

		public:
		void on_update(sys::state& state) noexcept override {
			row_contents.clear();

			auto t = state.world.nation_get_stockpiles(state.local_player_nation, economy::money);

			if(t < 0.0f) {
				int32_t num_gp = 7;
				if(t <= 1000.0f) {
					num_gp = 1;
				} else if(t <= 2000.0f) {
					num_gp = 2;
				} else if(t <= 4000.0f) {
					num_gp = 4;
				}

				float share = 10.0f;
				float total_shares = 0.0f;
				for(auto n : state.nations_by_rank) {
					if(state.world.nation_get_is_great_power(n) && n != state.local_player_nation) {
					row_contents.push_back(debt_item_data{n, share});
						total_shares += share;
						share -= 1.0f;

						--num_gp;
						if(num_gp <= 0)
						break;
					}
				}

				for(auto& r : row_contents) {
					r.amount = -t * r.amount / total_shares;
				}
			}

			update(state);
		}
	};

	class enable_debt_toggle : public button_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			frame = state.world.nation_get_is_debt_spending(state.local_player_nation) ? 1 : 0;
			disabled = false;

			auto last_br = state.world.nation_get_bankrupt_until(state.local_player_nation);
			if(last_br && state.current_date < last_br) {
				disabled = true;
			}
			if(economy::max_loan(state, state.local_player_nation) <= 0.0f) {
				disabled = true;
			}
		}
		void button_action(sys::state& state) noexcept override {
			command::enable_debt(state, state.local_player_nation);
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto last_br = state.world.nation_get_bankrupt_until(state.local_player_nation);
			if(last_br && state.current_date < last_br) {
				text::add_line(state, contents, "vce_currently_bankrupt", text::variable_type::x, last_br);
			} else if(economy::max_loan(state, state.local_player_nation) <= 0.0f) {
				text::add_line(state, contents, "vce_no_loans_possible");
			} else {
				text::add_line(state, contents, "vce_debt_spending");
				text::add_line_break_to_layout(state, contents);
			text::add_line(state, contents, "vce_loan_size", text::variable_type::x, text::fp_currency{ economy::max_loan(state, state.local_player_nation) });
			}
		}
	};

	class domestic_investment_slider : public budget_slider<budget_slider_target::domestic_investment, slider_scaling::quadratic> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_domestic_investment_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
		text::localised_single_sub_box(state, contents, box, "vce_budget_setting_percent", text::variable_type::perc, text::int_percentage{ stored_value });
			text::add_line_break_to_layout_box(state, contents, box);
			text::close_layout_box(contents, box);

		text::add_line(state, contents, "domestic_investment_pops", text::variable_type::x, text::pretty_integer{ int32_t(state.world.nation_get_demographics(n, demographics::to_key(state, state.culture_definitions.capitalists)) + state.world.nation_get_demographics(n, demographics::to_key(state, state.culture_definitions.aristocrat))) });
		text::add_line(state, contents, "domestic_investment_needs", text::variable_type::x, text::fp_currency{ state.world.nation_get_luxury_needs_costs(n, state.culture_definitions.capitalists) });
		}
	};
	class domestic_investment_estimated_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			float value = state.world.nation_get_domestic_investment_spending(state.local_player_nation) / 100.0f;
			set_text(state, text::format_money(economy_estimations::estimate_domestic_investment(state, state.local_player_nation) * value * value));
		}
	};

	// overseas_maintenance


	class overseas_maintenance_slider : public budget_slider<budget_slider_target::overseas, slider_scaling::linear> {
		int32_t get_true_value(sys::state& state) noexcept override {
			return int32_t(state.world.nation_get_overseas_spending(state.local_player_nation));
		}
		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}
		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto n = retrieve<dcon::nation_id>(state, parent);
			auto box = text::open_layout_box(contents, 0);
			text::close_layout_box(contents, box);
		}
	};
	class overseas_maintenance_estimated_text : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			float value = state.world.nation_get_overseas_spending(state.local_player_nation) / 100.0f;
			set_text(state, text::format_money(economy_estimations::estimate_overseas_penalty_spending(state, state.local_player_nation) * value));
		}
	};

	class budget_window : public window_element_base {
	private:
		budget_take_loan_window* budget_take_loan_win = nullptr;
		budget_repay_loan_window* budget_repay_loan_win = nullptr;
	public:
		void on_create(sys::state& state) noexcept override;
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override;
		message_result get(sys::state& state, Cyto::Any& payload) noexcept override;
	};

} // namespace ui
