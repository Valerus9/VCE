#pragma once

#include "dcon.hpp"

namespace economy {
	
	struct commodity_set {
		static constexpr uint32_t set_size = 8;
	
		float commodity_amounts[set_size] = { 0.0f };
		dcon::commodity_id commodity_type[set_size] = { dcon::commodity_id{} };
	};
	static_assert(sizeof(commodity_set) ==
	sizeof(commodity_set::commodity_amounts)
	+ sizeof(commodity_set::commodity_type));
	
	struct small_commodity_set {
		static constexpr uint32_t set_size = 6;
	
		float commodity_amounts[set_size] = { 0.0f };
		dcon::commodity_id commodity_type[set_size] = { dcon::commodity_id{} };
		uint16_t padding = 0;
	};
	static_assert(sizeof(small_commodity_set) ==
	sizeof(small_commodity_set::commodity_amounts)
	+ sizeof(small_commodity_set::commodity_type)
	+ sizeof(small_commodity_set::padding));
	
} // namespace economy
