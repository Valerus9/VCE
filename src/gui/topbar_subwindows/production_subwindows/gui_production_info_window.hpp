#prgama once

#include "element/gui_element_types.hpp"

namespace ui {
	class production_info_window : public window_element_base {
	public:
		std::unique_ptr<element_base> make_child(sys::state& state, std::string_view name, dcon::gui_def_id id) noexcept override { }
	};

} // namespace ui
