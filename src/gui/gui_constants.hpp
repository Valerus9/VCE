#pragma once
#include <stdint.h>

namespace ui {
	enum class production_sort_order {
		name, factories, primary_workers, secondary_workers, owners, infrastructure, focus
	};
	enum class production_window_tab : uint8_t {
		factories = 0x0, investments = 0x1, projects = 0x2, goods = 0x3
	};
	enum class politics_window_tab : uint8_t {
		reforms = 0x0, movements = 0x1, decisions = 0x2, releasables = 0x3
	};
	enum class politics_issue_sort_order : uint8_t {
		name, popular_support, voter_support
	};
	constexpr inline uint32_t max_chat_message_len = 42;
}
