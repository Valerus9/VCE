#pragma once
#include <stdint.h>

namespace province {
	namespace border {
		constexpr inline uint8_t state_bit = 0x01;
		constexpr inline uint8_t national_bit = 0x02;
		constexpr inline uint8_t coastal_bit = 0x04;
		constexpr inline uint8_t impassible_bit = 0x08;
		constexpr inline uint8_t non_adjacent_bit = 0x10;
		constexpr inline uint8_t river_crossing_bit = 0x20;
		constexpr inline uint8_t test_bit = 0x40;
	} // namespace border
} // namespace province
