#pragma once

#include "culture.hpp"
#include "dcon.hpp"
#include "gui_common_elements.hpp"
#include "element/gui_element_types.hpp"
#include "politics.hpp"
#include "system/system_state.hpp"
#include <cstdint>

namespace ui {
	class unciv_reforms_westernize_button : public standard_nation_button {
		public:
		sound::audio_instance& get_click_sound(sys::state& state) noexcept override {
			return sound::get_enact_sound(state);
		}

		void on_update(sys::state& state) noexcept override {
			auto nation_id = retrieve<dcon::nation_id>(state, parent);
			disabled = !command::can_civilize_nation(state, nation_id);
		}

		void button_action(sys::state& state) noexcept override {
			auto nation_id = retrieve<dcon::nation_id>(state, parent);
			command::civilize_nation(state, nation_id);
		}
	};

	class unciv_reforms_reform_button : public button_element_base {
		public:
		sound::audio_instance& get_click_sound(sys::state& state) noexcept override {
			return sound::get_enact_sound(state);
		}

		void button_action(sys::state& state) noexcept override {
			auto content = retrieve<dcon::reform_option_id>(state, parent);
			command::enact_reform(state, state.local_player_nation, content);
		}

		tooltip_behavior has_tooltip(sys::state& state) noexcept override {
			return tooltip_behavior::variable_tooltip;
		}

		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::reform_option_id>(state, parent);
			disabled = !command::can_enact_reform(state, state.local_player_nation, content);
		}

		void update_tooltip(sys::state& state, int32_t x, int32_t y, text::columnar_layout& contents) noexcept override {
			auto content = retrieve<dcon::reform_option_id>(state, parent);
			reform_description(state, contents, content);
		}
	};

	class unciv_reform_name : public simple_text_element_base {
		public:
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::reform_option_id>(state, parent);
			//Black on black is hard to see - so paint it white
			std::string txt = politics::reform_is_selected(state, state.local_player_nation, content) || command::can_enact_reform(state, state.local_player_nation, content) ? "" : "?W";
			txt += text::produce_simple_string(state, state.world.reform_option_get_name(content));
			set_text(state, txt);
		}
	};

	class unciv_reforms_option : public listbox_row_element_base<dcon::reform_option_id> {
		image_element_base* selected_icon = nullptr;

		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "reform_name") {
				return make_element_by_type<unciv_reform_name>(state, id);
			} else if(name == "selected") {
				auto ptr = make_element_by_type<image_element_base>(state, id);
				selected_icon = ptr.get();
				return ptr;
			} else if(name == "reform_option") {
				return make_element_by_type<unciv_reforms_reform_button>(state, id);
			} else {
				return nullptr;
			}
		}

		void on_update(sys::state& state) noexcept override {
			selected_icon->set_visible(state, politics::reform_is_selected(state, state.local_player_nation, content));
		}
	};

	class unciv_reforms_listbox : public listbox_element_base<unciv_reforms_option, dcon::reform_option_id> {
		protected:
		std::string_view get_row_element_name() override {
			return "reform_option_window";
		}

		public:
		message_result set(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<dcon::reform_id>()) {
				auto reform_id = any_cast<dcon::reform_id>(payload);
				row_contents.clear();
				auto fat_id = dcon::fatten(state.world, reform_id);
				for(auto& option : fat_id.get_options()) {
					if(option) {
						row_contents.push_back(option);
					}
				}
				update(state);
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};


	class reform_name_text : public multiline_text_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			base_data.position.y -= int16_t(7);
			multiline_text_element_base::on_create(state);
		}
		void on_update(sys::state& state) noexcept override {
			auto content = retrieve<dcon::reform_id>(state, parent);
			auto color = multiline_text_element_base::black_text ? text::text_color::black : text::text_color::white;
			auto container = text::create_endless_layout(state, multiline_text_element_base::internal_layout,
				text::layout_parameters{ 0, 0, multiline_text_element_base::base_data.size.x,
						multiline_text_element_base::base_data.size.y, multiline_text_element_base::base_data.data.text.font_handle, -4, text::alignment::left, color, false });
			auto fat_id = dcon::fatten(state.world, content);
			auto box = text::open_layout_box(container);
		text::add_to_layout_box(state, container, box, fat_id.get_name(), text::substitution_map{});
			text::close_layout_box(container, box);
		}
	};

	class unciv_reforms_reform_window : public window_element_base {
	dcon::reform_id reform_id{};

		public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "reform_name") {
				return make_element_by_type<reform_name_text>(state, id);
			} else {
				return nullptr;
			}
		}

		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			auto reforms_listbox = std::make_unique<unciv_reforms_listbox>();
			reforms_listbox->base_data.size.x = 130;
			reforms_listbox->base_data.size.y = 100;
			make_size_from_graphics(state, reforms_listbox->base_data);
			reforms_listbox->on_create(state);
			add_child_to_front(std::move(reforms_listbox));
		}

		message_result get(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<dcon::reform_id>()) {
				payload.emplace<dcon::reform_id>(reform_id);
				return message_result::consumed;
			}
			return message_result::unseen;
		}

		message_result set(sys::state& state, Cyto::Any& payload) noexcept override {
			if(payload.holds_type<dcon::reform_id>()) {
				reform_id = any_cast<dcon::reform_id>(payload);
				return message_result::consumed;
			}
			return message_result::unseen;
		}
	};

	class unciv_reforms_window : public window_element_base {
		public:
		void on_create(sys::state& state) noexcept override {
			window_element_base::on_create(state);
			set_visible(state, false);
		}

		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override {
			if(name == "civ_progress") {
				return make_element_by_type<nation_westernization_progress_bar>(state, id);
			} else if(name == "westernize_button") {
				return make_element_by_type<unciv_reforms_westernize_button>(state, id);
			} else if(name == "research_points_val") {
				return make_element_by_type<nation_research_points_text>(state, id);
			} else if(auto reform_id = politics::get_reform_by_name(state, name); bool(reform_id)) {
				auto ptr = make_element_by_type<unciv_reforms_reform_window>(state, id);
				Cyto::Any payload = reform_id;
				ptr->impl_set(state, payload);
				return ptr;
			} else if(name == "mil_plusminus_icon") {
				return make_element_by_type<nation_military_reform_multiplier_icon>(state, id);
			} else if(name == "eco_plusminus_icon") {
				return make_element_by_type<nation_economic_reform_multiplier_icon>(state, id);
			} else if(name == "eco_main_icon" || name == "mil_main_icon") {
				auto ptr = make_element_by_type<image_element_base>(state, id);
				ptr->frame -= 1;
				return ptr;
			} else {
				return nullptr;
			}
		}
	};

} // namespace ui
