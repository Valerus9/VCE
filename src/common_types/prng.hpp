#pragma once

//Due to forward declaration the following lines are needed (DO NOT REMOVE):
namespace sys {		//Due to forward declaration this line is needed. (DO NOT REMOVE)
	struct state;	//Due to forward declaration this line is needed. (DO NOT REMOVE)
}					//Due to forward declaration this line is needed. (DO NOT REMOVE)
//Due to forward declaration the previous lines are needed (DO NOT REMOVE).

namespace rng {

	struct random_pair {
		uint64_t high;
		uint64_t low;
	};

	uint64_t get_random(sys::state const& state, uint32_t value_in);			 // try to populate as many bits of value_in as you can
	random_pair get_random_pair(sys::state const& state, uint32_t value_in);	// each call natively generates 128 random bits anyways
	uint64_t get_random(sys::state const& state, uint32_t value_in_hi, uint32_t value_in_lo);
	random_pair get_random_pair(sys::state const& state, uint32_t value_in_hi, uint32_t value_in_lo);
	uint32_t reduce(uint32_t value_in, uint32_t upper_bound);

	float get_random_float(sys::state const& state, uint32_t value_in);
	float get_random_float(sys::state const& state, uint32_t value_hi, uint32_t value_lo);
} // namespace rng
