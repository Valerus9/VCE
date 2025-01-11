#pragma once

#include "dcon.hpp"

namespace culture {
struct scripted_flag_type {
	dcon::trigger_key trigger; //2
	dcon::flag_type_id flag_type; //1
	uint8_t padding = 0;
};
static_assert(sizeof(scripted_flag_type) ==
	sizeof(scripted_flag_type::flag_type)
	+ sizeof(scripted_flag_type::trigger)
	+ sizeof(scripted_flag_type::padding));
}
