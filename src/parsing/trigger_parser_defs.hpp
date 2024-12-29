#include "parsers.hpp"

namespace parsers {
template<typename C>
tr_diplomatic_influence parse_tr_diplomatic_influence(token_generator& gen, error_handler& err, C&& context) {
	tr_diplomatic_influence cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 3:
					// who
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6877 && (cur.content[2] | 0x20 ) == 0x6F)) {
						cobj.who = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_party_loyalty parse_tr_party_loyalty(token_generator& gen, error_handler& err, C&& context) {
	tr_party_loyalty cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// ideology
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79676F6C6F656469))) {
						cobj.ideology = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// province_id
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x697F && (cur.content[10] | 0x20 ) == 0x64)) {
						cobj.province_id = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_unemployment_by_type parse_tr_unemployment_by_type(token_generator& gen, error_handler& err, C&& context) {
	tr_unemployment_by_type cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 4:
					// type
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
						cobj.type = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_upper_house parse_tr_upper_house(token_generator& gen, error_handler& err, C&& context) {
	tr_upper_house cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// ideology
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79676F6C6F656469))) {
						cobj.ideology = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_check_variable parse_tr_check_variable(token_generator& gen, error_handler& err, C&& context) {
	tr_check_variable cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x76:
						// value
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.value(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// which
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68636968))) {
							cobj.which = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_relation parse_tr_relation(token_generator& gen, error_handler& err, C&& context) {
	tr_relation cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 3:
					// who
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6877 && (cur.content[2] | 0x20 ) == 0x6F)) {
						cobj.who = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_pop_unemployment parse_tr_pop_unemployment(token_generator& gen, error_handler& err, C&& context) {
	tr_pop_unemployment cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 4:
					// type
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
						cobj.type = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_can_build_in_province parse_tr_can_build_in_province(token_generator& gen, error_handler& err, C&& context) {
	tr_can_build_in_province cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 8:
					// building
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E69646C697562))) {
						cobj.building = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 29:
					// limit_to_world_greatest_level
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F74696D696C) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x677F646C726F777F) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F74736574616572) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6576656C) && (cur.content[28] | 0x20 ) == 0x6C)) {
						cobj.limit_to_world_greatest_level = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_can_build_fort_in_capital parse_tr_can_build_fort_in_capital(token_generator& gen, error_handler& err, C&& context) {
	tr_can_build_fort_in_capital cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 22:
					// in_whole_capital_state
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6F68777F6E69) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6174697061637F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6174737F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6574)) {
						cobj.in_whole_capital_state = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 29:
					// limit_to_world_greatest_level
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F74696D696C) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x677F646C726F777F) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F74736574616572) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6576656C) && (cur.content[28] | 0x20 ) == 0x6C)) {
						cobj.limit_to_world_greatest_level = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_can_build_railway_in_capital parse_tr_can_build_railway_in_capital(token_generator& gen, error_handler& err, C&& context) {
	tr_can_build_railway_in_capital cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 22:
					// in_whole_capital_state
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6F68777F6E69) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6174697061637F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6174737F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6574)) {
						cobj.in_whole_capital_state = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 29:
					// limit_to_world_greatest_level
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F74696D696C) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x677F646C726F777F) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F74736574616572) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6576656C) && (cur.content[28] | 0x20 ) == 0x6C)) {
						cobj.limit_to_world_greatest_level = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_work_available parse_tr_work_available(token_generator& gen, error_handler& err, C&& context) {
	tr_work_available cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 6:
					// worker
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6B726F77) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.worker(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_party_name parse_tr_party_name(token_generator& gen, error_handler& err, C&& context) {
	tr_party_name cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// ideology
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79676F6C6F656469))) {
						cobj.ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_party_position parse_tr_party_position(token_generator& gen, error_handler& err, C&& context) {
	tr_party_position cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x69:
						// ideology
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
tr_news_data_parameters parse_tr_news_data_parameters(token_generator& gen, error_handler& err, C&& context) {
	tr_news_data_parameters cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_group_key(cur); gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			cobj.free_value(parse_text(cur.content, cur.line, err), err, cur.line, context);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
trigger_body parse_trigger_body(token_generator& gen, error_handler& err, C&& context) {
	trigger_body cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				case 2:
					// or
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x726F)) {
						tr_scope_or(gen, err, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 3:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// and
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x646E)) {
							tr_scope_and(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6E:
						// not
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x746F)) {
							tr_scope_not(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// from
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F72 && (cur.content[3] | 0x20 ) == 0x6D)) {
							tr_scope_from(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x73)) {
							tr_scope_this(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 5:
					// owner
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E776F) && (cur.content[4] | 0x20 ) == 0x72)) {
						tr_scope_owner(gen, err, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_pop
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F707F6C) && (cur.content[6] | 0x20 ) == 0x70)) {
								tr_scope_all_pop(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_pop
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F707F79) && (cur.content[6] | 0x20 ) == 0x70)) {
								tr_scope_any_pop(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x63:
						// country
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7972)) {
							tr_scope_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_eq
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F736761) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7165)) {
							cobj.tags_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F6C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								tr_scope_all_core(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								tr_scope_any_core(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// dates_eq
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73657461) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x657F && (cur.content[7] | 0x20 ) == 0x71)) {
							cobj.dates_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							tr_scope_location(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// overlord
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C726576) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x726F && (cur.content[7] | 0x20 ) == 0x64)) {
							tr_scope_overlord(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// relation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74616C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.relation(parse_tr_relation(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// sea_zone
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7A7F6165) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E6F && (cur.content[7] | 0x20 ) == 0x65)) {
							tr_scope_sea_zone(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_state
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x74737F6C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7461 && (cur.content[8] | 0x20 ) == 0x65)) {
								tr_scope_all_state(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_state
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x74737F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7461 && (cur.content[8] | 0x20 ) == 0x65)) {
								tr_scope_any_state(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x76:
						// values_eq
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x71657F7365756C61))) {
							cobj.values_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// controller
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6C6F72746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							tr_scope_controller(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F79747261) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.party_name(parse_tr_party_name(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_eq
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F73676E697274) && (cur.content[9] | 0x20 ) == 0x71)) {
							cobj.strings_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6374616D7F736761) && (cur.content[9] | 0x20 ) == 0x68)) {
							cobj.tags_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F796E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7972)) {
							tr_scope_any_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// dates_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616D7F73657461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6863)) {
							cobj.dates_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F63737F65746174) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							tr_state_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// upper_house
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F687F72657070) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6573)) {
							cobj.upper_house(parse_tr_upper_house(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F6C) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								tr_scope_all_substate(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F79) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								tr_scope_any_substate(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							tr_scope_independence(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// sphere_owner
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x776F7F6572656870) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x656E && (cur.content[11] | 0x20 ) == 0x72)) {
							tr_scope_sphere_owner(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616572677F736761) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6574 && (cur.content[11] | 0x20 ) == 0x72)) {
							cobj.tags_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616D7F7365756C61) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6374 && (cur.content[11] | 0x20 ) == 0x68)) {
							cobj.values_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// capital_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F6C6174697061) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65706F63))) {
							tr_capital_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// dates_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6572677F73657461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72657461))) {
							cobj.dates_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x65:
						// every_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F79726576) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x7972746E))) {
							tr_scope_every_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_loyalty
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C7F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746C61))) {
							cobj.party_loyalty(parse_tr_party_loyalty(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x68637461))) {
							cobj.strings_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6F637F736761) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x736E6961))) {
							cobj.tags_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x77:
						// war_countries
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73656972))) {
							tr_scope_war_countries(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// check_variable
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697261767F6B6365) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x656C6261))) {
								cobj.check_variable(parse_tr_check_variable(gen, err, context), err, cur.line, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x75:
							// cultural_union
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F6C617275746C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F696E))) {
								tr_scope_cultural_union(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// dates_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F637F73657461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696174) && (cur.content[13] | 0x20 ) == 0x73)) {
							cobj.dates_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// length_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F6874676E65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65746165) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.length_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736F707F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697469) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.party_position(parse_tr_party_position(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F7365756C61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65746165) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.values_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x77:
						// work_available
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696176617F6B726F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C62616C) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.work_available(parse_tr_work_available(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x73:
						// strings_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x677F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x74616572) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7265)) {
							cobj.strings_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F7365756C61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6961746E) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x736E)) {
							cobj.values_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x70:
						// pop_unemployment
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706D656E757F706F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6D796F6C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E65 && (cur.content[15] | 0x20 ) == 0x74)) {
							cobj.pop_unemployment(parse_tr_pop_unemployment(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61746E6F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E69 && (cur.content[15] | 0x20 ) == 0x73)) {
							cobj.strings_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 17:
					// A
					// running -  A
					if((true && (cur.content[0] | 0x20 ) == 0x61)) {
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// ALL_
							// running -  L_
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7F6C)) {
								switch(0x20 | int32_t(cur.content[4])) {
								case 0x67:
									// all_greater_power
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										tr_scope_all_greater_power(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x73:
									// all_sphere_member
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D7F6572656870) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265626D))) {
										tr_scope_all_sphere_member(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x77:
									// all_war_countries
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7261) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x73656972))) {
										tr_scope_all_war_countries(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						case 0x6E:
							// ANY_
							// running -  Y_
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7F79)) {
								switch(0x20 | int32_t(cur.content[4])) {
								case 0x67:
									// any_greater_power
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										tr_scope_any_greater_power(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x73:
									// any_sphere_member
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D7F6572656870) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265626D))) {
										tr_scope_any_sphere_member(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
					} else {
						tr_scope_variable(cur.content, gen, err, context);
						}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_owned_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64656E776F7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x636E69766F72707F) && (cur.content[17] | 0x20 ) == 0x65)) {
							tr_scope_any_owned_province(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// crisis_state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F657461) && (cur.content[17] | 0x20 ) == 0x65)) {
							tr_crisis_state_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_neighbor_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656E7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F726F62) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7274 && (cur.content[19] | 0x20 ) == 0x79)) {
							tr_scope_any_neighbor_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// diplomatic_influence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756C666E697F63) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x636E && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.diplomatic_influence(parse_tr_diplomatic_influence(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// flashpoint_tag_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6761747F74) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x706F && (cur.content[19] | 0x20 ) == 0x65)) {
							tr_flashpoint_tag_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// unemployment_by_type
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D796F6C706D656E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F79627F746E65) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7079 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.unemployment_by_type(parse_tr_unemployment_by_type(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656E7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F726F62) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x65636E69))) {
							tr_scope_any_neighbor_province(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_build_in_province
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F646C6975627F6E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F6E69) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x65)) {
								cobj.can_build_in_province(parse_tr_can_build_in_province(gen, err, context), err, cur.line, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x72:
							// CRISIS_
							// running -  ISIS_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x73697369) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// crisis_attacker_scope
									if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F72656B63617474) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x706F6373) && (cur.content[20] | 0x20 ) == 0x65)) {
										tr_crisis_attacker_scope(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x64:
									// crisis_defender_scope
									if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7265646E656665) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x706F6373) && (cur.content[20] | 0x20 ) == 0x65)) {
										tr_crisis_defender_scope(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 25:
					// can_build_fort_in_capital
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F74726F667F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174697061637F6E) && (cur.content[24] | 0x20 ) == 0x6C)) {
						cobj.can_build_fort_in_capital(parse_tr_can_build_fort_in_capital(gen, err, context), err, cur.line, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 28:
					// can_build_railway_in_capital
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61776C6961727F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F6E697F79) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6C617469))) {
						cobj.can_build_railway_in_capital(parse_tr_can_build_railway_in_capital(gen, err, context), err, cur.line, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				default:
					tr_scope_variable(cur.content, gen, err, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 2:
					// ai
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6961)) {
						cobj.ai(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 3:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x74:
						// tag
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6761)) {
							cobj.tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7261)) {
							cobj.war(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// base
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6F:
						// owns
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E77 && (cur.content[3] | 0x20 ) == 0x73)) {
							cobj.owns(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// port
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x726F && (cur.content[3] | 0x20 ) == 0x74)) {
							cobj.port(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rank
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E61 && (cur.content[3] | 0x20 ) == 0x6B)) {
							cobj.rank(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// test
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7473)) {
								cobj.test(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x79:
							// type
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x6570)) {
								cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x79:
						// year
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6165 && (cur.content[3] | 0x20 ) == 0x72)) {
							cobj.year(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// empty
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7974706D))) {
							cobj.empty(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MON
						// running -  ON
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x65:
								// money
								if((true && (cur.content[4] | 0x20 ) == 0x79)) {
									cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// month
								if((true && (cur.content[4] | 0x20 ) == 0x68)) {
									cobj.month(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// always
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7961776C) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.always(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x62:
						// badboy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F626461) && (cur.content[5] | 0x20 ) == 0x79)) {
							cobj.badboy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// exists
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74736978) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.exists(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x66:
						// factor
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F746361) && (cur.content[5] | 0x20 ) == 0x72)) {
							cobj.factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// region
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F696765) && (cur.content[5] | 0x20 ) == 0x6E)) {
							cobj.region(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// strata
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74617274) && (cur.content[5] | 0x20 ) == 0x61)) {
							cobj.strata(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// capital
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x61746970) && (cur.content[6] | 0x20 ) == 0x6C)) {
								cobj.capital(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// culture
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[6] | 0x20 ) == 0x65)) {
								cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x69:
						// is_core
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F73) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6572)) {
							cobj.is_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// low_tax
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x747F776F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7861)) {
							cobj.poor_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// terrain
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61727265) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E69)) {
							cobj.terrain(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// blockade
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6B636F6C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6461 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.blockade(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// controls
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72746E6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C6F && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.controls(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// election
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.election(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// is_slave
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C737F73) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7661 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.is_slave(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// literacy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72657469) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6361 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.literacy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neighbor
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68676965) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F62 && (cur.content[7] | 0x20 ) == 0x72)) {
							cobj.neighbour(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6F:
						// owned_by
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x627F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.owned_by(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6F:
								// poor_tax
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x61747F72) && (cur.content[7] | 0x20 ) == 0x78)) {
									cobj.poor_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// pop_type
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7079747F) && (cur.content[7] | 0x20 ) == 0x65)) {
									cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x72:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// prestige
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x67697473) && (cur.content[7] | 0x20 ) == 0x65)) {
									cobj.prestige(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// produces
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x65637564) && (cur.content[7] | 0x20 ) == 0x73)) {
									cobj.produces(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// religion
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6967696C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E6F)) {
								cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x69:
							// rich_tax
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x747F6863) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7861)) {
								cobj.rich_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x73:
						// state_id
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65746174) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x697F && (cur.content[7] | 0x20 ) == 0x64)) {
							cobj.state_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// treasury
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73616572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7275 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_with
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x777F7261) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.war_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// civilized
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x696C6976) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x657A && (cur.content[8] | 0x20 ) == 0x64)) {
								cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// continent
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6E69746E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E65 && (cur.content[8] | 0x20 ) == 0x74)) {
								cobj.continent(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// has_crime
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6972637F7361))) {
							cobj.has_crime(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x76:
								// invention
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x69746E65) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E6F)) {
									cobj.invention(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x7F:
								// in_sphere
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x65687073) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6572)) {
									cobj.in_sphere(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x73:
							// is_vassal
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7361767F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6173 && (cur.content[8] | 0x20 ) == 0x6C)) {
								cobj.is_vassal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6D:
						// militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
							cobj.militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neighbour
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72756F6268676965))) {
							cobj.neighbour(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// plurality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974696C6172756C))) {
							cobj.plurality(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x76:
						// vassal_of
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x666F7F6C61737361))) {
							cobj.vassal_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_score
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65726F63737F7261))) {
							cobj.war_score(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// corruption
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6974707572726F) && (cur.content[9] | 0x20 ) == 0x6E)) {
							cobj.corruption(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x67:
						// government
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D6E7265766F) && (cur.content[9] | 0x20 ) == 0x74)) {
							cobj.government(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656461656C7F7361) && (cur.content[9] | 0x20 ) == 0x72)) {
							cobj.has_leader(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// in_default
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746C75616665647F))) {
								cobj.in_default(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x63:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x61:
										// is_capital
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61746970) && (cur.content[9] | 0x20 ) == 0x6C)) {
											cobj.is_capital(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x6F:
										// is_coastal
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61747361) && (cur.content[9] | 0x20 ) == 0x6C)) {
											cobj.is_coastal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x75:
										// is_culture
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[9] | 0x20 ) == 0x65)) {
											cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x73:
									// is_subject
									if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x656A6275) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7463)) {
										cobj.is_vassal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6C:
						// life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F656669) && (cur.content[9] | 0x20 ) == 0x73)) {
							cobj.life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MI
						// running -  I
						if((true && (cur.content[1] | 0x20 ) == 0x69)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x64:
								// middle_tax
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7F656C64) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6174 && (cur.content[9] | 0x20 ) == 0x78)) {
									cobj.middle_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// minorities
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7469726F) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6569 && (cur.content[9] | 0x20 ) == 0x73)) {
									cobj.minorities(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x72:
						// revanchism
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736968636E617665) && (cur.content[9] | 0x20 ) == 0x6D)) {
							cobj.revanchism(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// total_pops
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73706F707F6C6174))) {
								cobj.total_pops(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// truce_with
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x687469777F656375))) {
								cobj.truce_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_faction
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69746361667F7361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.has_faction(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x63:
								// is_colonial
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6C6F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6169 && (cur.content[10] | 0x20 ) == 0x6C)) {
									cobj.is_colonial(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x64:
								// is_disarmed
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x72617369) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x656D && (cur.content[10] | 0x20 ) == 0x64)) {
									cobj.is_disarmed(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// is_overseas
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x73726576) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6165 && (cur.content[10] | 0x20 ) == 0x73)) {
									cobj.is_overseas(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_substate
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x74736275) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7461 && (cur.content[10] | 0x20 ) == 0x65)) {
									cobj.is_substate(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6C:
						// life_rating
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461727F656669) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x676E)) {
							cobj.life_rating(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// nationalism
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C616E6F697461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6D73)) {
							cobj.nationalism(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// province_id
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6469)) {
							cobj.province_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// substate_of
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65746174736275) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x666F)) {
							cobj.substate_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// tech_school
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6F6863737F6863) && (cur.content[10] | 0x20 ) == 0x6C)) {
								cobj.tech_school(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// trade_goods
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646F6F677F656461) && (cur.content[10] | 0x20 ) == 0x73)) {
								cobj.trade_goods(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// big_producer
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75646F72707F6769) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563 && (cur.content[11] | 0x20 ) == 0x72)) {
							cobj.big_producer(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// crisis_exist
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x78657F7369736972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7369 && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.crisis_exist(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// HA
						// running -  A
						if((true && (cur.content[1] | 0x20 ) == 0x61)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x73:
								// HAS_
								// running -  _
								if((true && (cur.content[3] | 0x20 ) == 0x7F)) {
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x62:
										// has_building
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x646C6975) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E69 && (cur.content[11] | 0x20 ) == 0x67)) {
											cobj.has_building(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x70:
										// has_pop_type
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x747F706F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
											cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							case 0x76:
								// have_core_in
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F65726F637F65) && (cur.content[11] | 0x20 ) == 0x6E)) {
									cobj.have_core_in(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// is_blockaded
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646564616B636F6C))) {
									cobj.is_blockaded(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6D:
								// is_mobilised
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646573696C69626F))) {
									cobj.is_mobilised(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6C:
						// luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F7972757875) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6465 && (cur.content[11] | 0x20 ) == 0x73)) {
							cobj.luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// num_of_ports
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F666F7F6D75) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x73)) {
							cobj.num_of_ports(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x79)) {
							cobj.ruling_party(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// unemployment
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D796F6C706D656E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E65 && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.unemployment(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// alliance_with
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E61696C6C) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x68746977))) {
							cobj.alliance_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// cash_reserves
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72657365727F6873) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6576 && (cur.content[12] | 0x20 ) == 0x73)) {
								cobj.cash_reserves(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// CON
							// running -  N
							if((true && (cur.content[2] | 0x20 ) == 0x6E)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x73:
									// consciousness
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73656E73756F6963) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x74:
									// controlled_by
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F64656C6C6F72) && (cur.content[12] | 0x20 ) == 0x79)) {
										cobj.controlled_by(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						case 0x75:
							// culture_group
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F657275746C) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x756F && (cur.content[12] | 0x20 ) == 0x70)) {
								cobj.culture_group(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x66:
								// has_factories
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736569726F746361))) {
									cobj.has_factories(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// has_news_flag
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F737765))) {
									cobj.has_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// is_our_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61767F72756F7F73) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C617373))) {
							cobj.is_our_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// lost_national
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616E7F74736F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C616E6F))) {
							cobj.lost_national(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// nationalvalue
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61766C616E6F6974) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x756C && (cur.content[12] | 0x20 ) == 0x65)) {
								cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// NUM_OF_
							// running -  M_OF_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x666F7F6D) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// num_of_allies
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65696C6C) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.num_of_allies(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x63:
									// num_of_cities
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65697469) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.num_of_cities(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// pop_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C696D7F706F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79636E61))) {
							cobj.militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crime_fighting
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6769667F656D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E697468) && (cur.content[13] | 0x20 ) == 0x67)) {
							cobj.administration_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79616479726576) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[13] | 0x20 ) == 0x73)) {
							cobj.everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_flashpoint
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6873616C667F7361) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.has_flashpoint(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// is_banned_from
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72667F64656E6E61) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6D6F)) {
									cobj.is_banned_from(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// is_independant
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61646E657065646E) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x746E)) {
									cobj.is_independant(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// is_next_reform
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6665727F747865) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6D72)) {
									cobj.is_next_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6D:
						// military_score
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x726F6373) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.military_score(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// NUM_OF_
						// running -  UM_OF_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F7F6D75) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F66)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x72:
								// num_of_revolts
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7665) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7374)) {
									cobj.num_of_revolts(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x76:
								// num_of_vassals
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x736C)) {
									cobj.num_of_vassals(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						// part_of_sphere
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F666F7F747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72656870) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.part_of_sphere(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// unit_in_battle
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F6E697F74696E) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C747461) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.unit_in_battle(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_exhaustion
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75616878657F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697473) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.war_exhaustion(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_nationalize
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F6974616E7F6E) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x7A696C61) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.can_nationalize(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// colonial_nation
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616E7F6C61696E6F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
									cobj.colonial_nation(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// constructing_cb
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69746375727473) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x62637F67))) {
									cobj.constructing_cb(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x67:
								// has_global_flag
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C667F6C61626F6C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6761)) {
									cobj.has_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// has_pop_culture
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75746C75637F706F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6572)) {
									cobj.has_pop_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// is_claim_crisis
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D69616C637F73) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73697263) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7369)) {
							cobj.is_claim_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// military_access
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65636361) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7373)) {
							cobj.military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// primary_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F7972616D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x75746C75) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6572)) {
							cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// SOCIAL_
						// running -  OCIAL_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6169636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F6C)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x6D:
								// social_movement
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6D65766F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6E65 && (cur.content[14] | 0x20 ) == 0x74)) {
									cobj.social_movement(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// social_spending
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x646E6570) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6E69 && (cur.content[14] | 0x20 ) == 0x67)) {
									cobj.social_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x75:
						// unit_has_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7361687F74696E) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6461656C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7265)) {
							cobj.unit_has_leader(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// accepted_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7275 && (cur.content[15] | 0x20 ) == 0x65)) {
							cobj.accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x62:
						// brigades_compare
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F73656461676972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x706D6F63) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7261 && (cur.content[15] | 0x20 ) == 0x65)) {
							cobj.brigades_compare(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x63:
								switch(0x20 | int32_t(cur.content[5])) {
								case 0x6F:
									// has_country_flag
									if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C667F7972746E75) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6761)) {
										cobj.has_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x75:
									// has_culture_core
									if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F657275746C) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6572)) {
										cobj.has_culture_core(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
								break;
							case 0x70:
								// has_pop_religion
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67696C65727F706F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6F69 && (cur.content[15] | 0x20 ) == 0x6E)) {
									cobj.has_pop_religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// industrial_score
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61697274737564) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6F63737F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6572)) {
								cobj.industrial_score(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x63:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x61:
										// is_canal_enabled
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62616E657F6C616E) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x656C && (cur.content[15] | 0x20 ) == 0x64)) {
											cobj.is_canal_enabled(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x75:
										// is_culture_group
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F657275746C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x756F && (cur.content[15] | 0x20 ) == 0x70)) {
											cobj.culture_group(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x67:
									// is_greater_power
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										cobj.is_greater_power(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x73:
									// is_state_capital
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F65746174) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6C617469))) {
										cobj.is_state_capital(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6E:
						// NUM
						// running -  UM
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D75)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// number_of_states
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F666F7F7265) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x73657461))) {
									cobj.number_of_states(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x7F:
								// num_of_substates
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74736275737F666F) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x73657461))) {
									cobj.num_of_substates(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x74:
						// total_sunk_by_us
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E75737F6C61746F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79627F6B) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x757F && (cur.content[15] | 0x20 ) == 0x73)) {
							cobj.total_sunk_by_us(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// average_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F656761726576) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
							cobj.average_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// can_build_factory
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646C6975627F6E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726F746361667F))) {
							cobj.can_build_factory(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_province_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F65636E))) {
							cobj.has_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x63:
								// is_cultural_union
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F696E75) && (cur.content[16] | 0x20 ) == 0x6E)) {
									cobj.is_cultural_union(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_state_religion
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65727F65746174) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F696769) && (cur.content[16] | 0x20 ) == 0x6E)) {
									cobj.is_state_religion(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// military_spending
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F79726174696C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x646E6570) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6E69 && (cur.content[16] | 0x20 ) == 0x67)) {
								cobj.military_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// mobilisation_size
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69746173696C6962) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x737F6E6F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x7A69 && (cur.content[16] | 0x20 ) == 0x65)) {
								cobj.mobilisation_size(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						// revolt_percentage
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65707F746C6F7665) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656761746E656372))) {
							cobj.revolt_percentage(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// units_in_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270))) {
							cobj.units_in_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_create_vassals
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574616572637F6E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736C61737361767F))) {
								cobj.can_create_vassals(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// crisis_temperature
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D65747F73697369) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6572757461726570))) {
								cobj.crisis_temperature(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x65:
						// education_spending
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461637564) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69646E6570737F) && (cur.content[17] | 0x20 ) == 0x67)) {
							cobj.education_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x66:
						// flashpoint_tension
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F69736E65747F74) && (cur.content[17] | 0x20 ) == 0x6E)) {
							cobj.flashpoint_tension(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x67:
						// great_wars_enabled
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261777F74616572) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C62616E657F73) && (cur.content[17] | 0x20 ) == 0x64)) {
							cobj.great_wars_enabled(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// involved_in_crisis
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F6465766C6F76) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F6E))) {
								cobj.involved_in_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x70:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x6F:
										// is_possible_vassal
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x767F656C62697373) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (cur.content[17] | 0x20 ) == 0x6C)) {
											cobj.is_possible_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x72:
										// is_primary_culture
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75637F7972616D69) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[17] | 0x20 ) == 0x65)) {
											cobj.is_primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x73:
									// is_secondary_power
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x797261646E6F6365) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x776F707F) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7265)) {
										cobj.is_secondary_power(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// PO
						// running -  O
						if((true && (cur.content[1] | 0x20 ) == 0x6F)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// political_movement
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F6C6163697469) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x6D65766F) && (*(uint16_t const*)(&cur.content[15]) | 0x2020 ) == 0x6E65 && (cur.content[17] | 0x20 ) == 0x74)) {
									cobj.political_movement(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// pop_majority_issue
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469726F6A616D7F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x73697F79) && (*(uint16_t const*)(&cur.content[15]) | 0x2020 ) == 0x7573 && (cur.content[17] | 0x20 ) == 0x65)) {
									cobj.pop_majority_issue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// social_reform_want
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727F6C616963) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E61777F6D726F))) {
								cobj.social_reform_want(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x74:
							// stronger_army_than
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617F7265676E6F72) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6168747F796D72))) {
								cobj.stronger_army_than(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// this_culture_union
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75746C75637F7369) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F696E757F6572))) {
								cobj.this_culture_union(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// total_num_of_ports
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D756E7F6C6174) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7374726F707F666F))) {
								cobj.total_num_of_ports(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x77:
						// world_wars_enabled
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261777F646C726F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C62616E657F73) && (cur.content[17] | 0x20 ) == 0x64)) {
							cobj.world_wars_enabled(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 19:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x63:
								// has_cultural_sphere
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x65687073) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6572)) {
									cobj.has_cultural_sphere(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x75:
								// has_unclaimed_cores
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64656D69616C636E) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x726F637F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7365)) {
									cobj.has_unclaimed_cores(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x61:
								// is_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7275 && (cur.content[18] | 0x20 ) == 0x65)) {
									cobj.is_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// is_ideology_enabled
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79676F6C6F6564) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x62616E65) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x656C && (cur.content[18] | 0x20 ) == 0x64)) {
									cobj.is_ideology_enabled(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// is_overseas_culture
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F73616573726576) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7275 && (cur.content[18] | 0x20 ) == 0x65)) {
									cobj.is_overseas_culture(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_sphere_leader_of
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C7F6572656870) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x72656461) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x6F7F && (cur.content[18] | 0x20 ) == 0x66)) {
									cobj.is_sphere_leader_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6E:
						// news_printing_count
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6972707F737765) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F676E6974) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x746E)) {
							cobj.news_printing_count(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_tax_above_poor
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7861747F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F65766F6261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x726F)) {
							cobj.rich_tax_above_poor(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// CON
						// running -  ON
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x73:
								// constructing_cb_type
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E697463757274) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079747F62637F))) {
									cobj.constructing_cb_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// controlled_by_rebels
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F64656C6C6F72) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736C656265727F79))) {
									cobj.controlled_by_rebels(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x68:
						// has_country_modifier
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6669646F6D7F7972) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6569 && (cur.content[19] | 0x20 ) == 0x72)) {
							cobj.has_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x6C:
								// is_liberation_crisis
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F69746172656269) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F6E))) {
									cobj.is_liberation_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// is_releasable_vassal
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C62617361656C65) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61737361767F65))) {
									cobj.is_releasable_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						// pop_majority_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726F6A616D7F706F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746C75637F797469) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7275 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.pop_majority_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// RE
						// running -  E
						if((true && (cur.content[1] | 0x20 ) == 0x65)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x62:
								// rebel_power_fraction
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265776F707F6C65) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6974636172667F) && (cur.content[19] | 0x20 ) == 0x6E)) {
									cobj.rebel_power_fraction(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// recruited_percentage
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F646574697572) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6761746E65637265) && (cur.content[19] | 0x20 ) == 0x65)) {
									cobj.recruited_percentage(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x74:
						// trade_goods_in_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6F677F65646172) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F6E697F7364) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7461 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.trade_goods_in_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// average_consciousness
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656761726576) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73756F6963736E6F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x7373656E))) {
							cobj.average_consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// civilization_progress
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974617A696C6976) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72676F72707F6E6F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7365 && (cur.content[20] | 0x20 ) == 0x73)) {
								cobj.civilization_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// culture_has_union_tag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61687F657275746C) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E6F696E757F73) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6174 && (cur.content[20] | 0x20 ) == 0x67)) {
								cobj.culture_has_union_tag(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x6E:
								// has_national_minority
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C616E6F697461) && (*(uint64_t const*)(&cur.content[13]) | uint64_t(0x2020202020202020) ) == uint64_t(0x797469726F6E696D))) {
									cobj.has_national_minority(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// has_province_modifier
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[13]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
									cobj.has_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// HAS_RECENT
								// running -  ECENT
								if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x6E656365) && (cur.content[9] | 0x20 ) == 0x74)) {
									switch(0x20 | int32_t(cur.content[10])) {
									case 0x6C:
										// has_recently_lost_war
										if((true && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x777F74736F6C7F79) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x7261)) {
											cobj.has_recently_lost_war(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x7F:
										// has_recent_imigration
										if((true && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974617267696D69) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6E6F)) {
											cobj.has_recent_imigration(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// political_reform_want
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F6C6163697469) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61777F6D726F6665) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x746E)) {
									cobj.political_reform_want(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// poor_strata_militancy
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174617274737F72) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6174696C696D7F) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x7963)) {
									cobj.poor_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// POP_MAJORITY_
								// running -  _MAJORITY_
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469726F6A616D7F) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x7F79)) {
									switch(0x20 | int32_t(cur.content[13])) {
									case 0x69:
										// pop_majority_ideology
										if((true && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x676F && (cur.content[20] | 0x20 ) == 0x79)) {
											cobj.pop_majority_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x72:
										// pop_majority_religion
										if((true && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x67696C65) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6F69 && (cur.content[20] | 0x20 ) == 0x6E)) {
											cobj.pop_majority_religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x72:
							// province_control_days
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F65636E69766F) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F6C6F72746E6F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7961 && (cur.content[20] | 0x20 ) == 0x73)) {
								cobj.province_control_days(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// rich_strata_militancy
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617274737F6863) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174696C696D7F61) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x79)) {
								cobj.rich_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// ruling_party_ideology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261707F676E696C) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6F6564697F7974) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x676F && (cur.content[20] | 0x20 ) == 0x79)) {
								cobj.ruling_party_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x74:
						// total_amount_of_ships
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D617F6C61746F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F666F7F746E75) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x73706968))) {
							cobj.total_amount_of_ships(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 22:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// country_units_in_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F7972746E756F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x74617473) && (cur.content[21] | 0x20 ) == 0x65)) {
							cobj.country_units_in_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6566696C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[21] | 0x20 ) == 0x73)) {
							cobj.poor_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6566696C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[21] | 0x20 ) == 0x73)) {
							cobj.rich_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// administration_spending
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61727473696E696D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6570737F6E6F6974) && (*(uint32_t const*)(&cur.content[18]) | uint32_t(0x20202020) ) == uint32_t(0x6E69646E) && (cur.content[22] | 0x20 ) == 0x67)) {
								cobj.administration_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x67:
							// agree_with_ruling_party
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x687469777F656572) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F676E696C75727F) && (*(uint32_t const*)(&cur.content[18]) | uint32_t(0x20202020) ) == uint32_t(0x74726170) && (cur.content[22] | 0x20 ) == 0x79)) {
								cobj.agree_with_ruling_party(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6D:
						// middle_strata_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C696D7F61746172) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E617469) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7963)) {
							cobj.middle_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 24:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// constructing_cb_progress
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463757274736E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F62637F676E69) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72676F72) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7365 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.constructing_cb_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_empty_adjacent_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6563616A64617F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x74737F74) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7461 && (cur.content[23] | 0x20 ) == 0x65)) {
							cobj.has_empty_adjacent_state(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// middle_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x66696C7F61746172) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F65) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.middle_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727578756C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F79) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.poor_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727578756C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F79) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.rich_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// social_movement_strength
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D7F6C6169636F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F746E656D6576) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E657274) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7467 && (cur.content[23] | 0x20 ) == 0x68)) {
							cobj.social_movement_strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 25:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// country_units_in_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F7972746E756F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270))) {
							cobj.units_in_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// total_amount_of_divisions
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D617F6C61746F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F666F7F746E75) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736E6F6973697669))) {
							cobj.total_amount_of_divisions(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 26:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// constructing_cb_discovered
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463757274736E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F62637F676E69) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657265766F637369) && (cur.content[25] | 0x20 ) == 0x64)) {
							cobj.constructing_cb_discovered(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// middle_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x78756C7F61746172) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F797275) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.middle_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726576657F6174) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F796164) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.poor_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726576657F6174) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F796164) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.rich_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// someone_can_form_union_tag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656E6F656D6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D726F667F6E61) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61747F6E6F696E75) && (cur.content[25] | 0x20 ) == 0x67)) {
							cobj.someone_can_form_union_tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 27:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crime_higher_than_education
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6769687F656D6972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6168747F726568) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461637564657F) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6E6F)) {
							cobj.crime_higher_than_education(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_empty_adjacent_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6563616A64617F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F74) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6563)) {
							cobj.has_empty_adjacent_province(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// national_provinces_occupied
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F6C616E6F6974) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7365636E69766F72) && (*(uint64_t const*)(&cur.content[18]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6569707563636F7F) && (cur.content[26] | 0x20 ) == 0x64)) {
								cobj.national_provinces_occupied(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// num_of_vassals_no_substates
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F666F7F6D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6F6E7F736C6173) && (*(uint64_t const*)(&cur.content[18]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574617473627573) && (cur.content[26] | 0x20 ) == 0x73)) {
								cobj.num_of_vassals_no_substates(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// political_movement_strength
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974696C6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D65766F6D7F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E657274737F74) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6874)) {
							cobj.political_movement_strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 28:
					// middle_strata_everyday_needs
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F656C6464696D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F6174617274) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E7F796164797265) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x73646565))) {
						cobj.middle_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 34:
					// can_build_factory_in_capital_state
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726F746361667F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F6E697F79) && (*(uint64_t const*)(&cur.content[24]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174737F6C617469) && (*(uint16_t const*)(&cur.content[32]) | 0x2020 ) == 0x6574)) {
						cobj.can_build_factory_in_capital_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				default:
					cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
stored_condition parse_stored_condition(token_generator& gen, error_handler& err, C&& context) {
	stored_condition cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				case 2:
					// or
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x726F)) {
						tr_scope_or(gen, err, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 3:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// and
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x646E)) {
							tr_scope_and(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6E:
						// not
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x746F)) {
							tr_scope_not(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// from
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F72 && (cur.content[3] | 0x20 ) == 0x6D)) {
							tr_scope_from(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x73)) {
							tr_scope_this(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 5:
					// owner
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E776F) && (cur.content[4] | 0x20 ) == 0x72)) {
						tr_scope_owner(gen, err, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_pop
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F707F6C) && (cur.content[6] | 0x20 ) == 0x70)) {
								tr_scope_all_pop(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_pop
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F707F79) && (cur.content[6] | 0x20 ) == 0x70)) {
								tr_scope_any_pop(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x63:
						// country
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7972)) {
							tr_scope_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_eq
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F736761) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7165)) {
							cobj.tags_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F6C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								tr_scope_all_core(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								tr_scope_any_core(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// dates_eq
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73657461) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x657F && (cur.content[7] | 0x20 ) == 0x71)) {
							cobj.dates_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							tr_scope_location(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// overlord
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C726576) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x726F && (cur.content[7] | 0x20 ) == 0x64)) {
							tr_scope_overlord(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// relation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74616C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.relation(parse_tr_relation(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// sea_zone
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7A7F6165) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E6F && (cur.content[7] | 0x20 ) == 0x65)) {
							tr_scope_sea_zone(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_state
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x74737F6C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7461 && (cur.content[8] | 0x20 ) == 0x65)) {
								tr_scope_all_state(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_state
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x74737F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7461 && (cur.content[8] | 0x20 ) == 0x65)) {
								tr_scope_any_state(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x76:
						// values_eq
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x71657F7365756C61))) {
							cobj.values_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// controller
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6C6F72746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							tr_scope_controller(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F79747261) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.party_name(parse_tr_party_name(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_eq
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F73676E697274) && (cur.content[9] | 0x20 ) == 0x71)) {
							cobj.strings_eq(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6374616D7F736761) && (cur.content[9] | 0x20 ) == 0x68)) {
							cobj.tags_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F796E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7972)) {
							tr_scope_any_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// dates_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616D7F73657461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6863)) {
							cobj.dates_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F63737F65746174) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							tr_state_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// upper_house
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F687F72657070) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6573)) {
							cobj.upper_house(parse_tr_upper_house(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// all_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F6C) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								tr_scope_all_substate(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F79) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								tr_scope_any_substate(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							tr_scope_independence(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// sphere_owner
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x776F7F6572656870) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x656E && (cur.content[11] | 0x20 ) == 0x72)) {
							tr_scope_sphere_owner(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616572677F736761) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6574 && (cur.content[11] | 0x20 ) == 0x72)) {
							cobj.tags_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616D7F7365756C61) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6374 && (cur.content[11] | 0x20 ) == 0x68)) {
							cobj.values_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// capital_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F6C6174697061) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65706F63))) {
							tr_capital_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// dates_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6572677F73657461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72657461))) {
							cobj.dates_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x65:
						// every_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F79726576) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x7972746E))) {
							tr_scope_every_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_loyalty
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C7F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746C61))) {
							cobj.party_loyalty(parse_tr_party_loyalty(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_match
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x68637461))) {
							cobj.strings_match(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// tags_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6F637F736761) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x736E6961))) {
							cobj.tags_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x77:
						// war_countries
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73656972))) {
							tr_scope_war_countries(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// check_variable
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697261767F6B6365) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x656C6261))) {
								cobj.check_variable(parse_tr_check_variable(gen, err, context), err, cur.line, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x75:
							// cultural_union
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F6C617275746C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F696E))) {
								tr_scope_cultural_union(gen, err, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// dates_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F637F73657461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696174) && (cur.content[13] | 0x20 ) == 0x73)) {
							cobj.dates_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// length_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F6874676E65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65746165) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.length_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736F707F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697469) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.party_position(parse_tr_party_position(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F7365756C61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65746165) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.values_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x77:
						// work_available
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696176617F6B726F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C62616C) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.work_available(parse_tr_work_available(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x73:
						// strings_greater
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x677F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x74616572) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7265)) {
							cobj.strings_greater(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x76:
						// values_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F7365756C61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6961746E) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x736E)) {
							cobj.values_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x70:
						// pop_unemployment
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706D656E757F706F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6D796F6C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E65 && (cur.content[15] | 0x20 ) == 0x74)) {
							cobj.pop_unemployment(parse_tr_pop_unemployment(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// strings_contains
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F73676E697274) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61746E6F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E69 && (cur.content[15] | 0x20 ) == 0x73)) {
							cobj.strings_contains(parse_tr_news_data_parameters(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 17:
					// A
					// running -  A
					if((true && (cur.content[0] | 0x20 ) == 0x61)) {
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6C:
							// ALL_
							// running -  L_
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7F6C)) {
								switch(0x20 | int32_t(cur.content[4])) {
								case 0x67:
									// all_greater_power
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										tr_scope_all_greater_power(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x73:
									// all_sphere_member
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D7F6572656870) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265626D))) {
										tr_scope_all_sphere_member(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x77:
									// all_war_countries
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7261) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x73656972))) {
										tr_scope_all_war_countries(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						case 0x6E:
							// ANY_
							// running -  Y_
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7F79)) {
								switch(0x20 | int32_t(cur.content[4])) {
								case 0x67:
									// any_greater_power
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										tr_scope_any_greater_power(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x73:
									// any_sphere_member
									if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D7F6572656870) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7265626D))) {
										tr_scope_any_sphere_member(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
					} else {
						tr_scope_variable(cur.content, gen, err, context);
						}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_owned_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64656E776F7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x636E69766F72707F) && (cur.content[17] | 0x20 ) == 0x65)) {
							tr_scope_any_owned_province(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// crisis_state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F657461) && (cur.content[17] | 0x20 ) == 0x65)) {
							tr_crisis_state_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_neighbor_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656E7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F726F62) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7274 && (cur.content[19] | 0x20 ) == 0x79)) {
							tr_scope_any_neighbor_country(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						// diplomatic_influence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756C666E697F63) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x636E && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.diplomatic_influence(parse_tr_diplomatic_influence(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// flashpoint_tag_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6761747F74) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x706F && (cur.content[19] | 0x20 ) == 0x65)) {
							tr_flashpoint_tag_scope(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// unemployment_by_type
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D796F6C706D656E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F79627F746E65) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7079 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.unemployment_by_type(parse_tr_unemployment_by_type(gen, err, context), err, cur.line, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656E7F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F726F62) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x65636E69))) {
							tr_scope_any_neighbor_province(gen, err, context);
						} else {
							tr_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_build_in_province
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F646C6975627F6E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F6E69) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x65)) {
								cobj.can_build_in_province(parse_tr_can_build_in_province(gen, err, context), err, cur.line, context);
							} else {
								tr_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x72:
							// CRISIS_
							// running -  ISIS_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x73697369) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// crisis_attacker_scope
									if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F72656B63617474) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x706F6373) && (cur.content[20] | 0x20 ) == 0x65)) {
										tr_crisis_attacker_scope(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x64:
									// crisis_defender_scope
									if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7265646E656665) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x706F6373) && (cur.content[20] | 0x20 ) == 0x65)) {
										tr_crisis_defender_scope(gen, err, context);
									} else {
										tr_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									tr_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								tr_scope_variable(cur.content, gen, err, context);
								}
							break;
						default:
							tr_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						tr_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 25:
					// can_build_fort_in_capital
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F74726F667F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174697061637F6E) && (cur.content[24] | 0x20 ) == 0x6C)) {
						cobj.can_build_fort_in_capital(parse_tr_can_build_fort_in_capital(gen, err, context), err, cur.line, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 28:
					// can_build_railway_in_capital
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61776C6961727F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F6E697F79) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6C617469))) {
						cobj.can_build_railway_in_capital(parse_tr_can_build_railway_in_capital(gen, err, context), err, cur.line, context);
					} else {
						tr_scope_variable(cur.content, gen, err, context);
					}
					break;
				default:
					tr_scope_variable(cur.content, gen, err, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 2:
					// ai
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6961)) {
						cobj.ai(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 3:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x74:
						// tag
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6761)) {
							cobj.tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7261)) {
							cobj.war(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// base
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6F:
						// owns
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E77 && (cur.content[3] | 0x20 ) == 0x73)) {
							cobj.owns(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// port
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x726F && (cur.content[3] | 0x20 ) == 0x74)) {
							cobj.port(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rank
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E61 && (cur.content[3] | 0x20 ) == 0x6B)) {
							cobj.rank(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// test
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7473)) {
								cobj.test(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x79:
							// type
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x6570)) {
								cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x79:
						// year
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6165 && (cur.content[3] | 0x20 ) == 0x72)) {
							cobj.year(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// empty
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7974706D))) {
							cobj.empty(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MON
						// running -  ON
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x65:
								// money
								if((true && (cur.content[4] | 0x20 ) == 0x79)) {
									cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// month
								if((true && (cur.content[4] | 0x20 ) == 0x68)) {
									cobj.month(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// always
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7961776C) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.always(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x62:
						// badboy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F626461) && (cur.content[5] | 0x20 ) == 0x79)) {
							cobj.badboy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// exists
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74736978) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.exists(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x66:
						// factor
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F746361) && (cur.content[5] | 0x20 ) == 0x72)) {
							cobj.factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// region
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F696765) && (cur.content[5] | 0x20 ) == 0x6E)) {
							cobj.region(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// strata
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74617274) && (cur.content[5] | 0x20 ) == 0x61)) {
							cobj.strata(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// capital
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x61746970) && (cur.content[6] | 0x20 ) == 0x6C)) {
								cobj.capital(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// culture
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[6] | 0x20 ) == 0x65)) {
								cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x69:
						// is_core
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F73) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6572)) {
							cobj.is_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// low_tax
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x747F776F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7861)) {
							cobj.poor_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// terrain
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61727265) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E69)) {
							cobj.terrain(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// blockade
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6B636F6C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6461 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.blockade(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// controls
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72746E6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C6F && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.controls(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// election
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.election(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// is_slave
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C737F73) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7661 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.is_slave(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// literacy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72657469) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6361 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.literacy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neighbor
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68676965) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F62 && (cur.content[7] | 0x20 ) == 0x72)) {
							cobj.neighbour(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6F:
						// owned_by
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x627F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.owned_by(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6F:
								// poor_tax
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x61747F72) && (cur.content[7] | 0x20 ) == 0x78)) {
									cobj.poor_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// pop_type
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7079747F) && (cur.content[7] | 0x20 ) == 0x65)) {
									cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x72:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// prestige
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x67697473) && (cur.content[7] | 0x20 ) == 0x65)) {
									cobj.prestige(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// produces
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x65637564) && (cur.content[7] | 0x20 ) == 0x73)) {
									cobj.produces(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// religion
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6967696C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E6F)) {
								cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x69:
							// rich_tax
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x747F6863) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7861)) {
								cobj.rich_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x73:
						// state_id
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65746174) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x697F && (cur.content[7] | 0x20 ) == 0x64)) {
							cobj.state_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// treasury
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73616572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7275 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_with
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x777F7261) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.war_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// civilized
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x696C6976) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x657A && (cur.content[8] | 0x20 ) == 0x64)) {
								cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// continent
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6E69746E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E65 && (cur.content[8] | 0x20 ) == 0x74)) {
								cobj.continent(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// has_crime
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6972637F7361))) {
							cobj.has_crime(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x76:
								// invention
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x69746E65) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E6F)) {
									cobj.invention(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x7F:
								// in_sphere
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x65687073) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6572)) {
									cobj.in_sphere(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x73:
							// is_vassal
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7361767F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6173 && (cur.content[8] | 0x20 ) == 0x6C)) {
								cobj.is_vassal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6D:
						// militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
							cobj.militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neighbour
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72756F6268676965))) {
							cobj.neighbour(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// plurality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974696C6172756C))) {
							cobj.plurality(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x76:
						// vassal_of
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x666F7F6C61737361))) {
							cobj.vassal_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_score
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65726F63737F7261))) {
							cobj.war_score(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// corruption
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6974707572726F) && (cur.content[9] | 0x20 ) == 0x6E)) {
							cobj.corruption(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x67:
						// government
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D6E7265766F) && (cur.content[9] | 0x20 ) == 0x74)) {
							cobj.government(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656461656C7F7361) && (cur.content[9] | 0x20 ) == 0x72)) {
							cobj.has_leader(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// in_default
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746C75616665647F))) {
								cobj.in_default(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x63:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x61:
										// is_capital
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61746970) && (cur.content[9] | 0x20 ) == 0x6C)) {
											cobj.is_capital(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x6F:
										// is_coastal
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61747361) && (cur.content[9] | 0x20 ) == 0x6C)) {
											cobj.is_coastal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x75:
										// is_culture
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[9] | 0x20 ) == 0x65)) {
											cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x73:
									// is_subject
									if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x656A6275) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7463)) {
										cobj.is_vassal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6C:
						// life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F656669) && (cur.content[9] | 0x20 ) == 0x73)) {
							cobj.life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MI
						// running -  I
						if((true && (cur.content[1] | 0x20 ) == 0x69)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x64:
								// middle_tax
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7F656C64) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6174 && (cur.content[9] | 0x20 ) == 0x78)) {
									cobj.middle_tax(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// minorities
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x7469726F) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6569 && (cur.content[9] | 0x20 ) == 0x73)) {
									cobj.minorities(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x72:
						// revanchism
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736968636E617665) && (cur.content[9] | 0x20 ) == 0x6D)) {
							cobj.revanchism(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// total_pops
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73706F707F6C6174))) {
								cobj.total_pops(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// truce_with
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x687469777F656375))) {
								cobj.truce_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_faction
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69746361667F7361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.has_faction(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x63:
								// is_colonial
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6C6F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6169 && (cur.content[10] | 0x20 ) == 0x6C)) {
									cobj.is_colonial(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x64:
								// is_disarmed
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x72617369) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x656D && (cur.content[10] | 0x20 ) == 0x64)) {
									cobj.is_disarmed(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// is_overseas
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x73726576) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6165 && (cur.content[10] | 0x20 ) == 0x73)) {
									cobj.is_overseas(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_substate
								if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x74736275) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7461 && (cur.content[10] | 0x20 ) == 0x65)) {
									cobj.is_substate(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6C:
						// life_rating
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461727F656669) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x676E)) {
							cobj.life_rating(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// nationalism
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C616E6F697461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6D73)) {
							cobj.nationalism(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// province_id
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6469)) {
							cobj.province_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// substate_of
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65746174736275) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x666F)) {
							cobj.substate_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// tech_school
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6F6863737F6863) && (cur.content[10] | 0x20 ) == 0x6C)) {
								cobj.tech_school(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// trade_goods
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646F6F677F656461) && (cur.content[10] | 0x20 ) == 0x73)) {
								cobj.trade_goods(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// big_producer
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75646F72707F6769) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563 && (cur.content[11] | 0x20 ) == 0x72)) {
							cobj.big_producer(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// crisis_exist
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x78657F7369736972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7369 && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.crisis_exist(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// HA
						// running -  A
						if((true && (cur.content[1] | 0x20 ) == 0x61)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x73:
								// HAS_
								// running -  _
								if((true && (cur.content[3] | 0x20 ) == 0x7F)) {
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x62:
										// has_building
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x646C6975) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E69 && (cur.content[11] | 0x20 ) == 0x67)) {
											cobj.has_building(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x70:
										// has_pop_type
										if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x747F706F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
											cobj.has_pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							case 0x76:
								// have_core_in
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F65726F637F65) && (cur.content[11] | 0x20 ) == 0x6E)) {
									cobj.have_core_in(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// is_blockaded
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646564616B636F6C))) {
									cobj.is_blockaded(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6D:
								// is_mobilised
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646573696C69626F))) {
									cobj.is_mobilised(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6C:
						// luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F7972757875) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6465 && (cur.content[11] | 0x20 ) == 0x73)) {
							cobj.luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// num_of_ports
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F666F7F6D75) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x73)) {
							cobj.num_of_ports(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x79)) {
							cobj.ruling_party(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// unemployment
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D796F6C706D656E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E65 && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.unemployment(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// alliance_with
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E61696C6C) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x68746977))) {
							cobj.alliance_with(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// cash_reserves
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72657365727F6873) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6576 && (cur.content[12] | 0x20 ) == 0x73)) {
								cobj.cash_reserves(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// CON
							// running -  N
							if((true && (cur.content[2] | 0x20 ) == 0x6E)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x73:
									// consciousness
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73656E73756F6963) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x74:
									// controlled_by
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F64656C6C6F72) && (cur.content[12] | 0x20 ) == 0x79)) {
										cobj.controlled_by(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						case 0x75:
							// culture_group
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F657275746C) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x756F && (cur.content[12] | 0x20 ) == 0x70)) {
								cobj.culture_group(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x66:
								// has_factories
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736569726F746361))) {
									cobj.has_factories(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// has_news_flag
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F737765))) {
									cobj.has_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// is_our_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61767F72756F7F73) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C617373))) {
							cobj.is_our_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// lost_national
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616E7F74736F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C616E6F))) {
							cobj.lost_national(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// nationalvalue
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61766C616E6F6974) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x756C && (cur.content[12] | 0x20 ) == 0x65)) {
								cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// NUM_OF_
							// running -  M_OF_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x666F7F6D) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// num_of_allies
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65696C6C) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.num_of_allies(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x63:
									// num_of_cities
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65697469) && (cur.content[12] | 0x20 ) == 0x73)) {
										cobj.num_of_cities(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// pop_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C696D7F706F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79636E61))) {
							cobj.militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crime_fighting
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6769667F656D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E697468) && (cur.content[13] | 0x20 ) == 0x67)) {
							cobj.administration_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79616479726576) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[13] | 0x20 ) == 0x73)) {
							cobj.everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x66:
						// from_parameter
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617261707F6D6F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6574656D) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.from_parameter(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_flashpoint
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6873616C667F7361) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.has_flashpoint(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// is_banned_from
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72667F64656E6E61) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6D6F)) {
									cobj.is_banned_from(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// is_independant
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61646E657065646E) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x746E)) {
									cobj.is_independant(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// is_next_reform
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6665727F747865) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6D72)) {
									cobj.is_next_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// main_parameter
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D617261707F6E69) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x72657465))) {
								cobj.main_parameter(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x69:
							// military_score
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F79726174696C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65726F63))) {
								cobj.military_score(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6E:
						// NUM_OF_
						// running -  UM_OF_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F7F6D75) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F66)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x72:
								// num_of_revolts
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7665) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7374)) {
									cobj.num_of_revolts(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x76:
								// num_of_vassals
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x736C)) {
									cobj.num_of_vassals(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						// part_of_sphere
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F666F7F747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72656870) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.part_of_sphere(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// this_parameter
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617261707F736968) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6574656D) && (cur.content[13] | 0x20 ) == 0x72)) {
							cobj.this_parameter(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// unit_in_battle
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F6E697F74696E) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C747461) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.unit_in_battle(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_exhaustion
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75616878657F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697473) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.war_exhaustion(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_nationalize
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F6974616E7F6E) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x7A696C61) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.can_nationalize(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// colonial_nation
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616E7F6C61696E6F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
									cobj.colonial_nation(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6E:
								// constructing_cb
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69746375727473) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x62637F67))) {
									cobj.constructing_cb(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x67:
								// has_global_flag
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C667F6C61626F6C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6761)) {
									cobj.has_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// has_pop_culture
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75746C75637F706F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6572)) {
									cobj.has_pop_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// is_claim_crisis
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D69616C637F73) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73697263) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7369)) {
							cobj.is_claim_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// military_access
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65636361) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7373)) {
							cobj.military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// primary_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F7972616D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x75746C75) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6572)) {
							cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// SOCIAL_
						// running -  OCIAL_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6169636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F6C)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x6D:
								// social_movement
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6D65766F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6E65 && (cur.content[14] | 0x20 ) == 0x74)) {
									cobj.social_movement(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// social_spending
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x646E6570) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6E69 && (cur.content[14] | 0x20 ) == 0x67)) {
									cobj.social_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x75:
						// unit_has_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7361687F74696E) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6461656C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7265)) {
							cobj.unit_has_leader(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// accepted_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7275 && (cur.content[15] | 0x20 ) == 0x65)) {
							cobj.accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x62:
						// brigades_compare
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F73656461676972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x706D6F63) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7261 && (cur.content[15] | 0x20 ) == 0x65)) {
							cobj.brigades_compare(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x63:
								switch(0x20 | int32_t(cur.content[5])) {
								case 0x6F:
									// has_country_flag
									if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C667F7972746E75) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6761)) {
										cobj.has_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x75:
									// has_culture_core
									if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F657275746C) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6572)) {
										cobj.has_culture_core(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
								break;
							case 0x70:
								// has_pop_religion
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67696C65727F706F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6F69 && (cur.content[15] | 0x20 ) == 0x6E)) {
									cobj.has_pop_religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// industrial_score
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61697274737564) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6F63737F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6572)) {
								cobj.industrial_score(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x63:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x61:
										// is_canal_enabled
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62616E657F6C616E) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x656C && (cur.content[15] | 0x20 ) == 0x64)) {
											cobj.is_canal_enabled(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x75:
										// is_culture_group
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F657275746C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x756F && (cur.content[15] | 0x20 ) == 0x70)) {
											cobj.culture_group(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x67:
									// is_greater_power
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726574616572) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x7265776F))) {
										cobj.is_greater_power(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								case 0x73:
									// is_state_capital
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F65746174) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6C617469))) {
										cobj.is_state_capital(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6E:
						// NUM
						// running -  UM
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D75)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x62:
								// number_of_states
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F666F7F7265) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x73657461))) {
									cobj.number_of_states(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x7F:
								// num_of_substates
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74736275737F666F) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x73657461))) {
									cobj.num_of_substates(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x74:
						// total_sunk_by_us
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E75737F6C61746F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79627F6B) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x757F && (cur.content[15] | 0x20 ) == 0x73)) {
							cobj.total_sunk_by_us(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// average_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F656761726576) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
							cobj.average_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// can_build_factory
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646C6975627F6E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726F746361667F))) {
							cobj.can_build_factory(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_province_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F65636E))) {
							cobj.has_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x63:
								// is_cultural_union
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F696E75) && (cur.content[16] | 0x20 ) == 0x6E)) {
									cobj.is_cultural_union(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_state_religion
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65727F65746174) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F696769) && (cur.content[16] | 0x20 ) == 0x6E)) {
									cobj.is_state_religion(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// military_spending
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F79726174696C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x646E6570) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6E69 && (cur.content[16] | 0x20 ) == 0x67)) {
								cobj.military_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// mobilisation_size
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69746173696C6962) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x737F6E6F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x7A69 && (cur.content[16] | 0x20 ) == 0x65)) {
								cobj.mobilisation_size(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						// revolt_percentage
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65707F746C6F7665) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656761746E656372))) {
							cobj.revolt_percentage(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x75:
						// units_in_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270))) {
							cobj.units_in_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// can_create_vassals
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574616572637F6E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736C61737361767F))) {
								cobj.can_create_vassals(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// crisis_temperature
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D65747F73697369) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6572757461726570))) {
								cobj.crisis_temperature(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x65:
						// education_spending
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461637564) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69646E6570737F) && (cur.content[17] | 0x20 ) == 0x67)) {
							cobj.education_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x66:
						// flashpoint_tension
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F69736E65747F74) && (cur.content[17] | 0x20 ) == 0x6E)) {
							cobj.flashpoint_tension(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x67:
						// great_wars_enabled
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261777F74616572) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C62616E657F73) && (cur.content[17] | 0x20 ) == 0x64)) {
							cobj.great_wars_enabled(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6E:
							// involved_in_crisis
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F6465766C6F76) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F6E))) {
								cobj.involved_in_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x73:
							// IS_
							// running -  _
							if((true && (cur.content[2] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x70:
									switch(0x20 | int32_t(cur.content[4])) {
									case 0x6F:
										// is_possible_vassal
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x767F656C62697373) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (cur.content[17] | 0x20 ) == 0x6C)) {
											cobj.is_possible_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x72:
										// is_primary_culture
										if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75637F7972616D69) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[17] | 0x20 ) == 0x65)) {
											cobj.is_primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
									break;
								case 0x73:
									// is_secondary_power
									if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x797261646E6F6365) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x776F707F) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7265)) {
										cobj.is_secondary_power(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
									break;
								default:
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									break;
								}
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// PO
						// running -  O
						if((true && (cur.content[1] | 0x20 ) == 0x6F)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// political_movement
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F6C6163697469) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x6D65766F) && (*(uint16_t const*)(&cur.content[15]) | 0x2020 ) == 0x6E65 && (cur.content[17] | 0x20 ) == 0x74)) {
									cobj.political_movement(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// pop_majority_issue
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469726F6A616D7F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x73697F79) && (*(uint16_t const*)(&cur.content[15]) | 0x2020 ) == 0x7573 && (cur.content[17] | 0x20 ) == 0x65)) {
									cobj.pop_majority_issue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// social_reform_want
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727F6C616963) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E61777F6D726F))) {
								cobj.social_reform_want(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x74:
							// stronger_army_than
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617F7265676E6F72) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6168747F796D72))) {
								cobj.stronger_army_than(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x74:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// this_culture_union
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75746C75637F7369) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F696E757F6572))) {
								cobj.this_culture_union(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// total_num_of_ports
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D756E7F6C6174) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7374726F707F666F))) {
								cobj.total_num_of_ports(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x77:
						// world_wars_enabled
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261777F646C726F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C62616E657F73) && (cur.content[17] | 0x20 ) == 0x64)) {
							cobj.world_wars_enabled(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 19:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x63:
								// has_cultural_sphere
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x65687073) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6572)) {
									cobj.has_cultural_sphere(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x75:
								// has_unclaimed_cores
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64656D69616C636E) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x726F637F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7365)) {
									cobj.has_unclaimed_cores(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x61:
								// is_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7275 && (cur.content[18] | 0x20 ) == 0x65)) {
									cobj.is_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// is_ideology_enabled
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79676F6C6F6564) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x62616E65) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x656C && (cur.content[18] | 0x20 ) == 0x64)) {
									cobj.is_ideology_enabled(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// is_overseas_culture
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F73616573726576) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7275 && (cur.content[18] | 0x20 ) == 0x65)) {
									cobj.is_overseas_culture(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x73:
								// is_sphere_leader_of
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C7F6572656870) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x72656461) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x6F7F && (cur.content[18] | 0x20 ) == 0x66)) {
									cobj.is_sphere_leader_of(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x6E:
						// news_printing_count
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6972707F737765) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F676E6974) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x746E)) {
							cobj.news_printing_count(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_tax_above_poor
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7861747F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F65766F6261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x726F)) {
							cobj.rich_tax_above_poor(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// CON
						// running -  ON
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x73:
								// constructing_cb_type
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E697463757274) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079747F62637F))) {
									cobj.constructing_cb_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// controlled_by_rebels
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F64656C6C6F72) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736C656265727F79))) {
									cobj.controlled_by_rebels(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x68:
						// has_country_modifier
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6669646F6D7F7972) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6569 && (cur.content[19] | 0x20 ) == 0x72)) {
							cobj.has_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// IS_
						// running -  S_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7F73)) {
							switch(0x20 | int32_t(cur.content[3])) {
							case 0x6C:
								// is_liberation_crisis
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F69746172656269) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F6E))) {
									cobj.is_liberation_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// is_releasable_vassal
								if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C62617361656C65) && (*(uint64_t const*)(&cur.content[12]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61737361767F65))) {
									cobj.is_releasable_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						// pop_majority_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726F6A616D7F706F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746C75637F797469) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7275 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.pop_majority_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// RE
						// running -  E
						if((true && (cur.content[1] | 0x20 ) == 0x65)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x62:
								// rebel_power_fraction
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265776F707F6C65) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6974636172667F) && (cur.content[19] | 0x20 ) == 0x6E)) {
									cobj.rebel_power_fraction(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// recruited_percentage
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F646574697572) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6761746E65637265) && (cur.content[19] | 0x20 ) == 0x65)) {
									cobj.recruited_percentage(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x74:
						// trade_goods_in_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6F677F65646172) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F6E697F7364) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7461 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.trade_goods_in_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// average_consciousness
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656761726576) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73756F6963736E6F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x7373656E))) {
							cobj.average_consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// civilization_progress
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974617A696C6976) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72676F72707F6E6F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7365 && (cur.content[20] | 0x20 ) == 0x73)) {
								cobj.civilization_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// culture_has_union_tag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61687F657275746C) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E6F696E757F73) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6174 && (cur.content[20] | 0x20 ) == 0x67)) {
								cobj.culture_has_union_tag(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x68:
						// HAS_
						// running -  AS_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7361 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x6E:
								// has_national_minority
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C616E6F697461) && (*(uint64_t const*)(&cur.content[13]) | uint64_t(0x2020202020202020) ) == uint64_t(0x797469726F6E696D))) {
									cobj.has_national_minority(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// has_province_modifier
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[13]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
									cobj.has_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// HAS_RECENT
								// running -  ECENT
								if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x6E656365) && (cur.content[9] | 0x20 ) == 0x74)) {
									switch(0x20 | int32_t(cur.content[10])) {
									case 0x6C:
										// has_recently_lost_war
										if((true && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x777F74736F6C7F79) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x7261)) {
											cobj.has_recently_lost_war(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x7F:
										// has_recent_imigration
										if((true && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974617267696D69) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6E6F)) {
											cobj.has_recent_imigration(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6C:
								// political_reform_want
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F6C6163697469) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61777F6D726F6665) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x746E)) {
									cobj.political_reform_want(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6F:
								// poor_strata_militancy
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174617274737F72) && (*(uint64_t const*)(&cur.content[11]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6174696C696D7F) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x7963)) {
									cobj.poor_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x70:
								// POP_MAJORITY_
								// running -  _MAJORITY_
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469726F6A616D7F) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x7F79)) {
									switch(0x20 | int32_t(cur.content[13])) {
									case 0x69:
										// pop_majority_ideology
										if((true && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x676F && (cur.content[20] | 0x20 ) == 0x79)) {
											cobj.pop_majority_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									case 0x72:
										// pop_majority_religion
										if((true && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x67696C65) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6F69 && (cur.content[20] | 0x20 ) == 0x6E)) {
											cobj.pop_majority_religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										} else {
											cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										}
										break;
									default:
										cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
										break;
									}
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
									}
								break;
							default:
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								break;
							}
							break;
						case 0x72:
							// province_control_days
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F65636E69766F) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F6C6F72746E6F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7961 && (cur.content[20] | 0x20 ) == 0x73)) {
								cobj.province_control_days(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// rich_strata_militancy
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617274737F6863) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174696C696D7F61) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x79)) {
								cobj.rich_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// ruling_party_ideology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261707F676E696C) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6F6564697F7974) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x676F && (cur.content[20] | 0x20 ) == 0x79)) {
								cobj.ruling_party_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x74:
						// total_amount_of_ships
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D617F6C61746F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F666F7F746E75) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x73706968))) {
							cobj.total_amount_of_ships(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 22:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// country_units_in_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F7972746E756F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x74617473) && (cur.content[21] | 0x20 ) == 0x65)) {
							cobj.country_units_in_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6566696C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[21] | 0x20 ) == 0x73)) {
							cobj.poor_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6566696C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E) && (cur.content[21] | 0x20 ) == 0x73)) {
							cobj.rich_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// administration_spending
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61727473696E696D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6570737F6E6F6974) && (*(uint32_t const*)(&cur.content[18]) | uint32_t(0x20202020) ) == uint32_t(0x6E69646E) && (cur.content[22] | 0x20 ) == 0x67)) {
								cobj.administration_spending(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x67:
							// agree_with_ruling_party
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x687469777F656572) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F676E696C75727F) && (*(uint32_t const*)(&cur.content[18]) | uint32_t(0x20202020) ) == uint32_t(0x74726170) && (cur.content[22] | 0x20 ) == 0x79)) {
								cobj.agree_with_ruling_party(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x6D:
						// middle_strata_militancy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C696D7F61746172) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E617469) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7963)) {
							cobj.middle_strata_militancy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 24:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// constructing_cb_progress
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463757274736E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F62637F676E69) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72676F72) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7365 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.constructing_cb_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_empty_adjacent_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6563616A64617F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x74737F74) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7461 && (cur.content[23] | 0x20 ) == 0x65)) {
							cobj.has_empty_adjacent_state(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// middle_strata_life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x66696C7F61746172) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F65) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.middle_strata_life_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727578756C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F79) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.poor_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727578756C7F6174) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x656E7F79) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6465 && (cur.content[23] | 0x20 ) == 0x73)) {
							cobj.rich_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// social_movement_strength
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D7F6C6169636F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F746E656D6576) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E657274) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7467 && (cur.content[23] | 0x20 ) == 0x68)) {
							cobj.social_movement_strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 25:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// country_units_in_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757F7972746E756F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7374696E) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270))) {
							cobj.units_in_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// total_amount_of_divisions
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D617F6C61746F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F666F7F746E75) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736E6F6973697669))) {
							cobj.total_amount_of_divisions(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 26:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// constructing_cb_discovered
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463757274736E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x647F62637F676E69) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657265766F637369) && (cur.content[25] | 0x20 ) == 0x64)) {
							cobj.constructing_cb_discovered(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// middle_strata_luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x78756C7F61746172) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F797275) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.middle_strata_luxury_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_strata_everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726576657F6174) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F796164) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.poor_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_strata_everyday_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F686369) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726576657F6174) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F796164) && (cur.content[25] | 0x20 ) == 0x73)) {
							cobj.rich_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// someone_can_form_union_tag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656E6F656D6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6D726F667F6E61) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61747F6E6F696E75) && (cur.content[25] | 0x20 ) == 0x67)) {
							cobj.someone_can_form_union_tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 27:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crime_higher_than_education
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6769687F656D6972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6168747F726568) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461637564657F) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6E6F)) {
							cobj.crime_higher_than_education(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x68:
						// has_empty_adjacent_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F7361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6563616A64617F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F74) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6563)) {
							cobj.has_empty_adjacent_province(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// national_provinces_occupied
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F6C616E6F6974) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7365636E69766F72) && (*(uint64_t const*)(&cur.content[18]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6569707563636F7F) && (cur.content[26] | 0x20 ) == 0x64)) {
								cobj.national_provinces_occupied(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x75:
							// num_of_vassals_no_substates
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F666F7F6D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6F6E7F736C6173) && (*(uint64_t const*)(&cur.content[18]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574617473627573) && (cur.content[26] | 0x20 ) == 0x73)) {
								cobj.num_of_vassals_no_substates(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						default:
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							break;
						}
						break;
					case 0x70:
						// political_movement_strength
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974696C6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D65766F6D7F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E657274737F74) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6874)) {
							cobj.political_movement_strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 28:
					// middle_strata_everyday_needs
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F656C6464696D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F6174617274) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E7F796164797265) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x73646565))) {
						cobj.middle_strata_everyday_needs(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 34:
					// can_build_factory_in_capital_state
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6975627F6E6163) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726F746361667F64) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7061637F6E697F79) && (*(uint64_t const*)(&cur.content[24]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174737F6C617469) && (*(uint16_t const*)(&cur.content[32]) | 0x2020 ) == 0x6574)) {
						cobj.can_build_factory_in_capital_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				default:
					cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
scripted_trigger_file parse_scripted_trigger_file(token_generator& gen, error_handler& err, C&& context) {
	scripted_trigger_file cobj;
	for(token_and_type cur = gen.get(); cur.type != token_type::unknown && cur.type != token_type::close_brace; cur = gen.get()) {
		if(cur.type == token_type::open_brace) { 
			err.unhandled_free_group(cur); gen.discard_group();
			continue;
		}
		auto peek_result = gen.next();
		if(peek_result.type == token_type::special_identifier) {
			auto peek2_result = gen.next_next();
			if(peek2_result.type == token_type::open_brace) {
				gen.get(); gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					make_stored_trigger(cur.content, gen, err, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				default:
					err.unhandled_association_key(cur);
					break;
				}
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
}

