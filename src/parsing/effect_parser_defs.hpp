#include "parsers.hpp"

namespace parsers {
template<typename C>
ef_trigger_revolt parse_ef_trigger_revolt(token_generator& gen, error_handler& err, C&& context) {
	ef_trigger_revolt cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// culture
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7275 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
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
					case 0x72:
						// religion
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67696C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_diplomatic_influence parse_ef_diplomatic_influence(token_generator& gen, error_handler& err, C&& context) {
	ef_diplomatic_influence cobj;
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
						cobj.value = parse_constant(rh_token.content, rh_token.line, err, context);
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
ef_relation parse_ef_relation(token_generator& gen, error_handler& err, C&& context) {
	ef_relation cobj;
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x74:
						// tag
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6761)) {
							cobj.who = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// who
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F68)) {
							cobj.who = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 4:
					// with
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x68746977))) {
						cobj.who = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value = parse_constant(rh_token.content, rh_token.line, err, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// relation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F6974616C6572))) {
						cobj.value = parse_constant(rh_token.content, rh_token.line, err, context);
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
ef_add_province_modifier parse_ef_add_province_modifier(token_generator& gen, error_handler& err, C&& context) {
	ef_add_province_modifier cobj;
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
					// duration
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461727564))) {
						cobj.duration = parse_int(rh_token.content, rh_token.line, err);
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
ef_add_country_modifier parse_ef_add_country_modifier(token_generator& gen, error_handler& err, C&& context) {
	ef_add_country_modifier cobj;
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
					// duration
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461727564))) {
						cobj.duration = parse_int(rh_token.content, rh_token.line, err);
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
ef_casus_belli parse_ef_casus_belli(token_generator& gen, error_handler& err, C&& context) {
	ef_casus_belli cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// months
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68746E6F) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.months = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// target
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65677261) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.target = parse_text(rh_token.content, rh_token.line, err);
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
ef_add_casus_belli parse_ef_add_casus_belli(token_generator& gen, error_handler& err, C&& context) {
	ef_add_casus_belli cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// months
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68746E6F) && (cur.content[5] | 0x20 ) == 0x73)) {
							cobj.months = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// target
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65677261) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.target = parse_text(rh_token.content, rh_token.line, err);
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
ef_remove_casus_belli parse_ef_remove_casus_belli(token_generator& gen, error_handler& err, C&& context) {
	ef_remove_casus_belli cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// target
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67726174) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7465)) {
						cobj.target = parse_text(rh_token.content, rh_token.line, err);
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
ef_this_remove_casus_belli parse_ef_this_remove_casus_belli(token_generator& gen, error_handler& err, C&& context) {
	ef_this_remove_casus_belli cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// target
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67726174) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7465)) {
						cobj.target = parse_text(rh_token.content, rh_token.line, err);
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
ef_wargoal parse_ef_wargoal(token_generator& gen, error_handler& err, C&& context) {
	ef_wargoal cobj;
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
					// tag
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6174 && (cur.content[2] | 0x20 ) == 0x67)) {
						cobj.country(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// target
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67726174) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7465)) {
						cobj.country(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// country
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6E756F63) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7274 && (cur.content[6] | 0x20 ) == 0x79)) {
						cobj.country(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// casus_belli
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65627F7375736163) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6C6C && (cur.content[10] | 0x20 ) == 0x69)) {
						cobj.casus_belli(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 17:
					// state_province_id
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6574617473) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F65636E69766F) && (cur.content[16] | 0x20 ) == 0x64)) {
						cobj.state_province_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_war parse_ef_war(token_generator& gen, error_handler& err, C&& context) {
	ef_war cobj;
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
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// attacker_goal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F72656B63617474) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C616F67))) {
							cobj.attacker_goal = parse_ef_wargoal(gen, err, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x64:
						// defender_goal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7265646E656665) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C616F67))) {
							cobj.defender_goal = parse_ef_wargoal(gen, err, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
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
					// target
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67726174) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7465)) {
						cobj.target = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					// call_ally
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F6C6C6163) && (cur.content[8] | 0x20 ) == 0x79)) {
						cobj.call_ally = parse_bool(rh_token.content, rh_token.line, err);
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
ef_country_event parse_ef_country_event(token_generator& gen, error_handler& err, C&& context) {
	ef_country_event cobj;
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
				case 2:
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 4:
					// days
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73796164))) {
						cobj.days = parse_int(rh_token.content, rh_token.line, err);
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
ef_province_event parse_ef_province_event(token_generator& gen, error_handler& err, C&& context) {
	ef_province_event cobj;
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
				case 2:
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 4:
					// days
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73796164))) {
						cobj.days = parse_int(rh_token.content, rh_token.line, err);
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
ef_sub_unit parse_ef_sub_unit(token_generator& gen, error_handler& err, C&& context) {
	ef_sub_unit cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value = parse_text(rh_token.content, rh_token.line, err);
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
ef_set_variable parse_ef_set_variable(token_generator& gen, error_handler& err, C&& context) {
	ef_set_variable cobj;
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
							cobj.value = parse_constant(rh_token.content, rh_token.line, err, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// which
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68636968))) {
							cobj.which(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_change_variable parse_ef_change_variable(token_generator& gen, error_handler& err, C&& context) {
	ef_change_variable cobj;
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
							cobj.value = parse_constant(rh_token.content, rh_token.line, err, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// which
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68636968))) {
							cobj.which(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_ideology parse_ef_ideology(token_generator& gen, error_handler& err, C&& context) {
	ef_ideology cobj;
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
						cobj.value(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// factor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636166) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F)) {
						cobj.factor = parse_float(rh_token.content, rh_token.line, err);
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
ef_dominant_issue parse_ef_dominant_issue(token_generator& gen, error_handler& err, C&& context) {
	ef_dominant_issue cobj;
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
						cobj.value(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// factor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636166) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F)) {
						cobj.factor = parse_float(rh_token.content, rh_token.line, err);
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
ef_upper_house parse_ef_upper_house(token_generator& gen, error_handler& err, C&& context) {
	ef_upper_house cobj;
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
						cobj.value = parse_float(rh_token.content, rh_token.line, err);
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
ef_scaled_militancy parse_ef_scaled_militancy(token_generator& gen, error_handler& err, C&& context) {
	ef_scaled_militancy cobj;
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
					case 0x69:
						// issue
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65757373))) {
							cobj.issue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x76:
						// value
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.factor = parse_float(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 6:
					// factor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636166) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F)) {
						cobj.factor = parse_float(rh_token.content, rh_token.line, err);
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
				case 12:
					// unemployment
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C706D656E75) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x746E656D))) {
						cobj.unemployment = parse_float(rh_token.content, rh_token.line, err);
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
ef_scaled_consciousness parse_ef_scaled_consciousness(token_generator& gen, error_handler& err, C&& context) {
	ef_scaled_consciousness cobj;
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
					case 0x69:
						// issue
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65757373))) {
							cobj.issue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x76:
						// value
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.factor = parse_float(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 6:
					// factor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636166) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F)) {
						cobj.factor = parse_float(rh_token.content, rh_token.line, err);
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
				case 12:
					// unemployment
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C706D656E75) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x746E656D))) {
						cobj.unemployment = parse_float(rh_token.content, rh_token.line, err);
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
ef_define_general parse_ef_define_general(token_generator& gen, error_handler& err, C&& context) {
	ef_define_general cobj;
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
						cobj.name = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// background
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F72676B636162) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x646E)) {
						cobj.background(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// personality
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616E6F73726570) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7469 && (cur.content[10] | 0x20 ) == 0x79)) {
						cobj.personality(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_define_admiral parse_ef_define_admiral(token_generator& gen, error_handler& err, C&& context) {
	ef_define_admiral cobj;
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
						cobj.name = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// background
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F72676B636162) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x646E)) {
						cobj.background(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// personality
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616E6F73726570) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7469 && (cur.content[10] | 0x20 ) == 0x79)) {
						cobj.personality(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_add_war_goal parse_ef_add_war_goal(token_generator& gen, error_handler& err, C&& context) {
	ef_add_war_goal cobj;
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
				case 11:
					// casus_belli
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65627F7375736163) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6C6C && (cur.content[10] | 0x20 ) == 0x69)) {
						cobj.casus_belli(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_move_issue_percentage parse_ef_move_issue_percentage(token_generator& gen, error_handler& err, C&& context) {
	ef_move_issue_percentage cobj;
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
				case 2:
					// to
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6F74)) {
						cobj.to(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 4:
					// from
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6D6F7266))) {
						cobj.from(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// value
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.value = parse_float(rh_token.content, rh_token.line, err);
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
ef_party_loyalty parse_ef_party_loyalty(token_generator& gen, error_handler& err, C&& context) {
	ef_party_loyalty cobj;
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
					// ideology
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79676F6C6F656469))) {
						cobj.ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// province_id
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x697F && (cur.content[10] | 0x20 ) == 0x64)) {
						cobj.province_id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 13:
					// loyalty_value
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79746C61796F6C) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x756C6176) && (cur.content[12] | 0x20 ) == 0x65)) {
						cobj.loyalty_value = parse_float(rh_token.content, rh_token.line, err);
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
ef_build_railway_in_capital parse_ef_build_railway_in_capital(token_generator& gen, error_handler& err, C&& context) {
	ef_build_railway_in_capital cobj;
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
ef_build_fort_in_capital parse_ef_build_fort_in_capital(token_generator& gen, error_handler& err, C&& context) {
	ef_build_fort_in_capital cobj;
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
ef_build_bank_in_capital parse_ef_build_bank_in_capital(token_generator& gen, error_handler& err, C&& context) {
	ef_build_bank_in_capital cobj;
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
ef_build_university_in_capital parse_ef_build_university_in_capital(token_generator& gen, error_handler& err, C&& context) {
	ef_build_university_in_capital cobj;
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
ef_random_list parse_ef_random_list(token_generator& gen, error_handler& err, C&& context) {
	ef_random_list cobj;
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
					cobj.any_group(cur.content, add_to_random_list(cur.content, gen, err, context), err, cur.line, context);
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
template<typename C>
ef_clear_news_scopes parse_ef_clear_news_scopes(token_generator& gen, error_handler& err, C&& context) {
	ef_clear_news_scopes cobj;
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
				case 5:
					// limit
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x696D696C) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.limit(ef_limit(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
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
ef_change_party_name parse_ef_change_party_name(token_generator& gen, error_handler& err, C&& context) {
	ef_change_party_name cobj;
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
ef_change_party_position parse_ef_change_party_position(token_generator& gen, error_handler& err, C&& context) {
	ef_change_party_position cobj;
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
ef_trigger_crisis parse_ef_trigger_crisis(token_generator& gen, error_handler& err, C&& context) {
	ef_trigger_crisis cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// colony
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F6C6F63) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x796E)) {
						cobj.colony = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					// overwrite
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746972777265766F) && (cur.content[8] | 0x20 ) == 0x65)) {
						cobj.overwrite = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 14:
					// liberation_tag
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461726562696C) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x747F6E6F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6761)) {
						cobj.liberation_tag = parse_text(rh_token.content, rh_token.line, err);
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
ef_add_or_create_pop parse_ef_add_or_create_pop(token_generator& gen, error_handler& err, C&& context) {
	ef_add_or_create_pop cobj;
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// amount
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x756F6D61) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x746E)) {
						cobj.amount = parse_float(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// culture
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7275 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// religion
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F6967696C6572))) {
						cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
effect_body parse_effect_body(token_generator& gen, error_handler& err, C&& context) {
	effect_body cobj;
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
					// if
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6669)) {
						ef_scope_if(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 3:
					// war
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6177 && (cur.content[2] | 0x20 ) == 0x72)) {
						cobj.war(parse_ef_war(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// else
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x736C && (cur.content[3] | 0x20 ) == 0x65)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F72 && (cur.content[3] | 0x20 ) == 0x6D)) {
							ef_scope_from(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x73)) {
							ef_scope_this(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// limit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74696D69))) {
							cobj.limit(ef_limit(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// owner
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72656E77))) {
							ef_scope_owner(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 6:
					// random
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x646E6172) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6D6F)) {
						ef_scope_random(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x707F796E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x706F)) {
							ef_scope_any_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// country
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7972)) {
							ef_scope_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x65:
						// else_if
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65736C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6669)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
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
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// ideology
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.ideology(parse_ef_ideology(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							ef_scope_location(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// overlord
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C726576) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x726F && (cur.content[7] | 0x20 ) == 0x64)) {
							ef_scope_overlord(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// relation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74616C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// sea_zone
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F7A7F61) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x656E)) {
								ef_scope_sea_zone(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x75:
							// sub_unit
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6E757F62) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7469)) {
								cobj.sub_unit(parse_ef_sub_unit(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 9:
					// ANY_
					// running -  ANY_
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7F796E61))) {
						switch(0x20 | int32_t(cur.content[4])) {
						case 0x6F:
							// any_owned
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
								ef_scope_any_owned(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x73:
							// any_state
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
								ef_scope_any_state(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
					} else {
						ef_scope_variable(cur.content, gen, err, context);
						}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// controller
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6C6F72746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							ef_scope_controller(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6D6F646E61) && (cur.content[9] | 0x20 ) == 0x70)) {
							ef_scope_random_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F796E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7972)) {
							ef_scope_any_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(parse_ef_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F6D6F72) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_from_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// poor_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6174)) {
							ef_scope_poor_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_list
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73696C7F6D6F646E) && (cur.content[10] | 0x20 ) == 0x74)) {
								ef_scope_random_list(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x69:
							// rich_strata
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617274737F6863) && (cur.content[10] | 0x20 ) == 0x61)) {
								ef_scope_rich_strata(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x73:
						// state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F63737F65746174) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							ef_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F736968) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_this_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// upper_house
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F687F72657070) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6573)) {
							cobj.upper_house(parse_ef_upper_house(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_war_goal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F677F7261777F64) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6C61)) {
								cobj.add_war_goal(parse_ef_add_war_goal(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F79) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								ef_scope_any_substate(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							ef_scope_independence(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// loop_bounded
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F706F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6564 && (cur.content[11] | 0x20 ) == 0x64)) {
							ef_scope_loop_bounded(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// RANDOM_
						// running -  ANDOM_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F646E61) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F6D)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x6F:
								// random_owned
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
									ef_scope_random_owned(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x73:
								// random_state
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
									ef_scope_random_state(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_variable
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6261697261767F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x656C)) {
								cobj.set_variable(parse_ef_set_variable(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x70:
							// sphere_owner
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E776F7F65726568) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x7265)) {
								ef_scope_sphere_owner(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// capital_scope
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6C61746970) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x706F && (cur.content[12] | 0x20 ) == 0x65)) {
								ef_capital_scope(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6F:
							// country_event
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6E65 && (cur.content[12] | 0x20 ) == 0x74)) {
								cobj.country_event(parse_ef_country_event(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x6D:
						// middle_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61746172))) {
							ef_scope_middle_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_loyalty
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C7F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746C61))) {
							cobj.party_loyalty(parse_ef_party_loyalty(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// cultural_union
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F696E75) && (cur.content[13] | 0x20 ) == 0x6E)) {
							ef_scope_cultural_union(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// DEFINE_
							// running -  FINE_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x656E6966) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// define_admiral
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72696D64) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_admiral(parse_ef_define_admiral(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x67:
									// define_general
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72656E65) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_general(parse_ef_define_general(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									ef_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								ef_scope_variable(cur.content, gen, err, context);
								}
							break;
						case 0x6F:
							// dominant_issue
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F746E616E696D) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65757373))) {
								cobj.dominant_issue(parse_ef_dominant_issue(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x68:
						// hidden_tooltip
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F6E65646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69746C6F) && (cur.content[13] | 0x20 ) == 0x70)) {
							ef_scope_hidden_tooltip(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(parse_ef_province_event(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72746E75) && (cur.content[13] | 0x20 ) == 0x79)) {
							ef_scope_random_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// TRIGGER_
						// running -  RIGGER_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67676972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7265 && (cur.content[7] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[8])) {
							case 0x63:
								// trigger_crisis
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69736972) && (cur.content[13] | 0x20 ) == 0x73)) {
									cobj.trigger_crisis(parse_ef_trigger_crisis(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x72:
								// trigger_revolt
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7665) && (cur.content[13] | 0x20 ) == 0x74)) {
									cobj.trigger_revolt(parse_ef_trigger_revolt(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6464) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x696C)) {
							cobj.add_casus_belli(parse_ef_add_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// change_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61767F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x62616972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x656C)) {
							cobj.change_variable(parse_ef_change_variable(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// modify_relation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F796669646F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6974616C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E6F)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6563)) {
							ef_scope_random_owned(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 16:
					// scaled_militancy
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F64656C616373) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
						cobj.scaled_militancy(parse_ef_scaled_militancy(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616572677F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265776F707F7265))) {
							ef_scope_any_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_party_name
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E7F7974) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6D61 && (cur.content[16] | 0x20 ) == 0x65)) {
								cobj.change_party_name(parse_ef_change_party_name(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6C:
							// clear_news_scopes
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7377656E7F726165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6F63737F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6570 && (cur.content[16] | 0x20 ) == 0x73)) {
								gen.discard_group();
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crisis_state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F657461) && (cur.content[17] | 0x20 ) == 0x65)) {
							ef_crisis_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_by_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79627F6D6F646E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
								ef_random_by_modifier(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x65:
							// remove_casus_belli
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361637F65766F6D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C6C65627F7375))) {
								cobj.remove_casus_belli(parse_ef_remove_casus_belli(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 19:
					// any_defined_country
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696665647F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F64656E) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7274 && (cur.content[18] | 0x20 ) == 0x79)) {
						ef_scope_any_defined_country(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_country_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72746E756F637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696669646F6D7F79) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7265)) {
								cobj.add_country_modifier(parse_ef_add_country_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_country
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7972)) {
								ef_scope_any_neighbor_country(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// diplomatic_influence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756C666E697F63) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x636E && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.diplomatic_influence(parse_ef_diplomatic_influence(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// flashpoint_tag_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6761747F74) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x706F && (cur.content[19] | 0x20 ) == 0x65)) {
							ef_flashpoint_tag_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_country_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6E65 && (cur.content[19] | 0x20 ) == 0x74)) {
							lambda_country_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F7265746165) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6577 && (cur.content[19] | 0x20 ) == 0x72)) {
							ef_scope_random_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// scaled_consciousness
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F64656C6163) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E73756F6963736E) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7365 && (cur.content[19] | 0x20 ) == 0x73)) {
							cobj.scaled_consciousness(parse_ef_scaled_consciousness(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_province_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6669646F6D7F6563) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6569 && (cur.content[20] | 0x20 ) == 0x72)) {
								cobj.add_province_modifier(parse_ef_add_province_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_province
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x65)) {
								ef_scope_any_neighbor_province(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x62:
						// BUILD_
						// running -  UILD_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x646C6975) && (cur.content[5] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x62:
								// build_bank_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F6B6E61) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_bank_in_capital(parse_ef_build_bank_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x66:
								// build_fort_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F74726F) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_fort_in_capital(parse_ef_build_fort_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x63:
						// change_party_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69736F707F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
							cobj.change_party_position(parse_ef_change_party_position(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F65636E69766F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E6576))) {
							lambda_province_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// move_issue_percentage
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757373697F65766F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65637265707F65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x65676174))) {
							cobj.move_issue_percentage(parse_ef_move_issue_percentage(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x72:
						// random_neighbor_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7972)) {
							ef_scope_random_neighbor_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_remove_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D65727F736968) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6576) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x696C)) {
							cobj.this_remove_casus_belli(parse_ef_this_remove_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 24:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_railway_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6961727F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7961776C) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69706163) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6174 && (cur.content[23] | 0x20 ) == 0x6C)) {
							cobj.build_railway_in_capital(parse_ef_build_railway_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69766F72) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x636E && (cur.content[23] | 0x20 ) == 0x65)) {
							ef_scope_random_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 27:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_empty_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F62686769656E7F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6563)) {
							ef_scope_any_empty_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x62:
						// build_university_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696E757F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79746973726576) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74697061637F6E69) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6C61)) {
							cobj.build_university_in_capital(parse_ef_build_university_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 30:
					// random_empty_neighbor_province
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F6D6F646E6172) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69656E7F7974706D) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F726F626867) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[28]) | 0x2020 ) == 0x6563)) {
						ef_scope_random_empty_neighbor_province(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 34:
					// any_existing_country_except_scoped
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736978657F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F676E6974) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6378657F7972746E) && (*(uint64_t const*)(&cur.content[24]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F747065) && (*(uint16_t const*)(&cur.content[32]) | 0x2020 ) == 0x6465)) {
						ef_scope_any_existing_country_except_scoped(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				default:
					ef_scope_variable(cur.content, gen, err, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 5:
					// money
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E6F6D) && (cur.content[4] | 0x20 ) == 0x79)) {
						cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// badboy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F626461) && (cur.content[5] | 0x20 ) == 0x79)) {
							cobj.badboy(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// chance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x636E6168) && (cur.content[5] | 0x20 ) == 0x65)) {
							cobj.chance = parse_int(rh_token.content, rh_token.line, err);
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
						// capital
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C61)) {
							cobj.capital(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// end_war
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x777F646E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7261)) {
							cobj.end_war(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// inherit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7265686E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469)) {
							cobj.inherit(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61656C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6573)) {
							cobj.release(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F64) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								cobj.add_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// annex_to
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7F78656E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6F74)) {
								cobj.annex_to(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// election
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.election(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6D:
						// move_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65766F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F70 && (cur.content[7] | 0x20 ) == 0x70)) {
							cobj.move_pop(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// pop_type
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x79747F70) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6570)) {
								cobj.pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// prestige
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69747365) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6567)) {
								cobj.prestige(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x65:
							// religion
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6967696C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E6F)) {
								cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x67:
							// rgo_size
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69737F6F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x657A)) {
								cobj.rgo_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// treasury
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73616572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7275 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.treasury(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// add_crime
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6972637F6464))) {
							cobj.add_crime(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// civilized
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64657A696C697669))) {
							cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x70:
						// plurality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974696C6172756C))) {
							cobj.plurality(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// assimilate
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616C696D697373) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.assimilate(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// change_tag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61747F65676E6168) && (cur.content[9] | 0x20 ) == 0x67)) {
							cobj.change_tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6C:
						// leadership
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6968737265646165) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.leadership(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neutrality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C6172747565) && (cur.content[9] | 0x20 ) == 0x79)) {
							cobj.neutrality(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// reduce_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6563756465) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.reduce_pop(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6B:
						// kill_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461656C7F6C6C69) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7265)) {
							cobj.kill_leader(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalize
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C616E6F697461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x657A)) {
							cobj.nationalize(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_core
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F65766F6D65) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6572)) {
							cobj.remove_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// enable_canal
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656C62616E65) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C616E61))) {
						cobj.enable_canal(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6E:
								// consciousness
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E73756F696373) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x7373)) {
									cobj.consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x75:
								// country_event
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6576657F7972746E) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x746E)) {
									cobj.country_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_vassal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F65746165) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6173 && (cur.content[12] | 0x20 ) == 0x6C)) {
								cobj.create_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalvalue
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766C616E6F697461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_crisis
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72637F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73697369))) {
							cobj.remove_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_news_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x667F7377656E7F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x616C && (cur.content[12] | 0x20 ) == 0x67)) {
								cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// social_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727F6C616963) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x726F && (cur.content[12] | 0x20 ) == 0x6D)) {
								cobj.social_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// change_terrain
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69617272) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.change_terrain(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// leave_alliance
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65766165) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.leave_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x767F657361656C65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (cur.content[13] | 0x20 ) == 0x6C)) {
							cobj.release_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_exhaustion
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75616878657F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697473) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.war_exhaustion(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x68:
							// change_pop_size
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x7A69737F) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.change_pop_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// clear_news_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7377656E7F7261) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// clr_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_alliance
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65746165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.create_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// economic_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F63696D6F6E6F) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
								cobj.economic_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// enable_ideology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6564697F656C6261) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x676F6C6F) && (cur.content[14] | 0x20 ) == 0x79)) {
								cobj.enable_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// loop_iterations
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726574697F706F6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697461) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x736E)) {
							cobj.loop_iterations = parse_int(rh_token.content, rh_token.line, err);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MILITARY_
						// running -  ILITARY_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69))) {
							switch(0x20 | int32_t(cur.content[9])) {
							case 0x61:
								// military_access
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x73656363) && (cur.content[14] | 0x20 ) == 0x73)) {
									cobj.military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// military_reform
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
									cobj.military_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// PR
						// running -  R
						if((true && (cur.content[1] | 0x20 ) == 0x72)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// prestige_factor
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61667F6567697473) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x726F7463))) {
									cobj.prestige_factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// primary_culture
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C75637F7972616D) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65727574))) {
									cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// research_points
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F68637261657365) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7374)) {
							cobj.research_points(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// SE
						// running -  E
						if((true && (cur.content[1] | 0x20 ) == 0x65)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x63:
								// secede_province
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F656465) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65636E69))) {
									cobj.secede_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// set_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.set_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// clr_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726C) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// political_reform
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974696C6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6665727F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x726F && (cur.content[15] | 0x20 ) == 0x6D)) {
							cobj.political_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7465) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_controller
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F637F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7274) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x656C && (cur.content[16] | 0x20 ) == 0x72)) {
								cobj.change_controller(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							// clr_province_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x667F6563) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x616C && (cur.content[16] | 0x20 ) == 0x67)) {
								cobj.clr_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// set_province_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F65636E))) {
							cobj.set_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x79:
						// years_of_research
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F666F7F73726165) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6863726165736572))) {
							cobj.years_of_research(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// change_region_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F6E6F6967) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.change_region_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x64:
						// decrement_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D65726365) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.decrement_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// increment_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D6572636E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.increment_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// activate_technology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F657461766974) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6F6E686365) && (cur.content[18] | 0x20 ) == 0x79)) {
								cobj.activate_technology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x64:
							// add_crisis_interest
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73657265746E697F) && (cur.content[18] | 0x20 ) == 0x74)) {
								cobj.add_crisis_interest(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// end_military_access
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C696D7F646E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656363617F797261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7373)) {
							cobj.end_military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// ADD_
						// running -  DD_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6464 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x61:
								// add_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7275 && (cur.content[19] | 0x20 ) == 0x65)) {
									cobj.add_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// add_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6569 && (cur.content[19] | 0x20 ) == 0x72)) {
									cobj.add_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						// change_province_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E7F65636E69766F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6D61 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.change_province_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// masquerade_as_nation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461726575717361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616E7F73617F65) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6F69 && (cur.content[19] | 0x20 ) == 0x6E)) {
							cobj.masquerade_as_nation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_variable_to_zero
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61697261767F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7A7F6F747F656C62) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7265 && (cur.content[19] | 0x20 ) == 0x6F)) {
							cobj.set_variable_to_zero(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// add_province_modifier
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69646F6D7F65636E) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72656966))) {
							cobj.add_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party_ideology
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6564697F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x79676F6C))) {
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
				case 22:
					// add_crisis_temperature
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736972637F646461) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65706D65747F7369) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x75746172) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6572)) {
						cobj.add_crisis_temperature(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_tax_relative_income
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F7861747F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65766974616C65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6F636E69) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x656D)) {
							cobj.add_tax_relative_income(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_
						// running -  EMOVE_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x766F6D65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F65)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x61:
								// remove_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x7275 && (cur.content[22] | 0x20 ) == 0x65)) {
									cobj.remove_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// remove_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6569 && (cur.content[22] | 0x20 ) == 0x72)) {
									cobj.remove_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 24:
					// remove_province_modifier
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F65766F6D6572) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
						cobj.remove_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 25:
					// change_tag_no_core_switch
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F65676E616863) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6F6E7F6761) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63746977737F6572) && (cur.content[24] | 0x20 ) == 0x68)) {
						cobj.change_tag_no_core_switch(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 30:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_factory_in_capital_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6361667F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F79726F74) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617469706163) && (*(uint32_t const*)(&cur.content[25]) | uint32_t(0x20202020) ) == uint32_t(0x74617473) && (cur.content[29] | 0x20 ) == 0x65)) {
							cobj.build_factory_in_capital_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_RANDOM_
						// running -  EMOVE_RANDOM_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61727F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6D6F646E) && (cur.content[13] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[14])) {
							case 0x65:
								// remove_random_economic_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F63696D6F6E6F63) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_economic_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6D:
								// remove_random_military_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_military_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
ef_scope_random_by_modifier parse_ef_scope_random_by_modifier(token_generator& gen, error_handler& err, C&& context) {
	ef_scope_random_by_modifier cobj;
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
					// if
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6669)) {
						ef_scope_if(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 3:
					// war
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6177 && (cur.content[2] | 0x20 ) == 0x72)) {
						cobj.war(parse_ef_war(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// else
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x736C && (cur.content[3] | 0x20 ) == 0x65)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F72 && (cur.content[3] | 0x20 ) == 0x6D)) {
							ef_scope_from(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x73)) {
							ef_scope_this(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// limit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74696D69))) {
							cobj.limit(ef_limit(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// owner
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72656E77))) {
							ef_scope_owner(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// chance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x636E6168) && (cur.content[5] | 0x20 ) == 0x65)) {
							cobj.chance_modifier = read_chance_modifier(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F646E61) && (cur.content[5] | 0x20 ) == 0x6D)) {
							ef_scope_random(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x707F796E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x706F)) {
							ef_scope_any_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// country
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7972)) {
							ef_scope_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x65:
						// else_if
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65736C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6669)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
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
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// ideology
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.ideology(parse_ef_ideology(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							ef_scope_location(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// overlord
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C726576) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x726F && (cur.content[7] | 0x20 ) == 0x64)) {
							ef_scope_overlord(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// relation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74616C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// sea_zone
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F7A7F61) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x656E)) {
								ef_scope_sea_zone(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x75:
							// sub_unit
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6E757F62) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7469)) {
								cobj.sub_unit(parse_ef_sub_unit(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 9:
					// ANY_
					// running -  ANY_
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7F796E61))) {
						switch(0x20 | int32_t(cur.content[4])) {
						case 0x6F:
							// any_owned
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
								ef_scope_any_owned(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x73:
							// any_state
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
								ef_scope_any_state(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
					} else {
						ef_scope_variable(cur.content, gen, err, context);
						}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// controller
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6C6F72746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							ef_scope_controller(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6D6F646E61) && (cur.content[9] | 0x20 ) == 0x70)) {
							ef_scope_random_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F796E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7972)) {
							ef_scope_any_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(parse_ef_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F6D6F72) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_from_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// poor_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6174)) {
							ef_scope_poor_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_list
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73696C7F6D6F646E) && (cur.content[10] | 0x20 ) == 0x74)) {
								ef_scope_random_list(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x69:
							// rich_strata
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617274737F6863) && (cur.content[10] | 0x20 ) == 0x61)) {
								ef_scope_rich_strata(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x73:
						// state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F63737F65746174) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							ef_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F736968) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_this_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// upper_house
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F687F72657070) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6573)) {
							cobj.upper_house(parse_ef_upper_house(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_war_goal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F677F7261777F64) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6C61)) {
								cobj.add_war_goal(parse_ef_add_war_goal(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F79) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								ef_scope_any_substate(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							ef_scope_independence(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// loop_bounded
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F706F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6564 && (cur.content[11] | 0x20 ) == 0x64)) {
							ef_scope_loop_bounded(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// RANDOM_
						// running -  ANDOM_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F646E61) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F6D)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x6F:
								// random_owned
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
									ef_scope_random_owned(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x73:
								// random_state
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
									ef_scope_random_state(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_variable
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6261697261767F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x656C)) {
								cobj.set_variable(parse_ef_set_variable(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x70:
							// sphere_owner
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E776F7F65726568) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x7265)) {
								ef_scope_sphere_owner(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// capital_scope
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6C61746970) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x706F && (cur.content[12] | 0x20 ) == 0x65)) {
								ef_capital_scope(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6F:
							// country_event
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6E65 && (cur.content[12] | 0x20 ) == 0x74)) {
								cobj.country_event(parse_ef_country_event(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x6D:
						// middle_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61746172))) {
							ef_scope_middle_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_loyalty
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C7F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746C61))) {
							cobj.party_loyalty(parse_ef_party_loyalty(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// cultural_union
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F696E75) && (cur.content[13] | 0x20 ) == 0x6E)) {
							ef_scope_cultural_union(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// DEFINE_
							// running -  FINE_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x656E6966) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// define_admiral
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72696D64) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_admiral(parse_ef_define_admiral(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x67:
									// define_general
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72656E65) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_general(parse_ef_define_general(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									ef_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								ef_scope_variable(cur.content, gen, err, context);
								}
							break;
						case 0x6F:
							// dominant_issue
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F746E616E696D) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65757373))) {
								cobj.dominant_issue(parse_ef_dominant_issue(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x68:
						// hidden_tooltip
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F6E65646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69746C6F) && (cur.content[13] | 0x20 ) == 0x70)) {
							ef_scope_hidden_tooltip(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(parse_ef_province_event(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72746E75) && (cur.content[13] | 0x20 ) == 0x79)) {
							ef_scope_random_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// TRIGGER_
						// running -  RIGGER_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67676972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7265 && (cur.content[7] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[8])) {
							case 0x63:
								// trigger_crisis
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69736972) && (cur.content[13] | 0x20 ) == 0x73)) {
									cobj.trigger_crisis(parse_ef_trigger_crisis(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x72:
								// trigger_revolt
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7665) && (cur.content[13] | 0x20 ) == 0x74)) {
									cobj.trigger_revolt(parse_ef_trigger_revolt(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6464) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x696C)) {
							cobj.add_casus_belli(parse_ef_add_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// change_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61767F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x62616972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x656C)) {
							cobj.change_variable(parse_ef_change_variable(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// modify_relation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F796669646F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6974616C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E6F)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6563)) {
							ef_scope_random_owned(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 16:
					// scaled_militancy
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F64656C616373) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
						cobj.scaled_militancy(parse_ef_scaled_militancy(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616572677F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265776F707F7265))) {
							ef_scope_any_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_party_name
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E7F7974) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6D61 && (cur.content[16] | 0x20 ) == 0x65)) {
								cobj.change_party_name(parse_ef_change_party_name(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6C:
							// clear_news_scopes
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7377656E7F726165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6F63737F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6570 && (cur.content[16] | 0x20 ) == 0x73)) {
								gen.discard_group();
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crisis_state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F657461) && (cur.content[17] | 0x20 ) == 0x65)) {
							ef_crisis_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_by_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79627F6D6F646E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
								ef_random_by_modifier(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x65:
							// remove_casus_belli
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361637F65766F6D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C6C65627F7375))) {
								cobj.remove_casus_belli(parse_ef_remove_casus_belli(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 19:
					// any_defined_country
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696665647F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F64656E) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7274 && (cur.content[18] | 0x20 ) == 0x79)) {
						ef_scope_any_defined_country(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_country_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72746E756F637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696669646F6D7F79) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7265)) {
								cobj.add_country_modifier(parse_ef_add_country_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_country
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7972)) {
								ef_scope_any_neighbor_country(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// diplomatic_influence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756C666E697F63) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x636E && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.diplomatic_influence(parse_ef_diplomatic_influence(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// flashpoint_tag_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6761747F74) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x706F && (cur.content[19] | 0x20 ) == 0x65)) {
							ef_flashpoint_tag_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_country_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6E65 && (cur.content[19] | 0x20 ) == 0x74)) {
							lambda_country_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F7265746165) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6577 && (cur.content[19] | 0x20 ) == 0x72)) {
							ef_scope_random_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// scaled_consciousness
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F64656C6163) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E73756F6963736E) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7365 && (cur.content[19] | 0x20 ) == 0x73)) {
							cobj.scaled_consciousness(parse_ef_scaled_consciousness(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_province_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6669646F6D7F6563) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6569 && (cur.content[20] | 0x20 ) == 0x72)) {
								cobj.add_province_modifier(parse_ef_add_province_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_province
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x65)) {
								ef_scope_any_neighbor_province(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x62:
						// BUILD_
						// running -  UILD_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x646C6975) && (cur.content[5] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x62:
								// build_bank_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F6B6E61) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_bank_in_capital(parse_ef_build_bank_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x66:
								// build_fort_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F74726F) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_fort_in_capital(parse_ef_build_fort_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x63:
						// change_party_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69736F707F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
							cobj.change_party_position(parse_ef_change_party_position(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F65636E69766F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E6576))) {
							lambda_province_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// move_issue_percentage
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757373697F65766F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65637265707F65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x65676174))) {
							cobj.move_issue_percentage(parse_ef_move_issue_percentage(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x72:
						// random_neighbor_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7972)) {
							ef_scope_random_neighbor_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_remove_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D65727F736968) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6576) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x696C)) {
							cobj.this_remove_casus_belli(parse_ef_this_remove_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 24:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_railway_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6961727F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7961776C) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69706163) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6174 && (cur.content[23] | 0x20 ) == 0x6C)) {
							cobj.build_railway_in_capital(parse_ef_build_railway_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69766F72) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x636E && (cur.content[23] | 0x20 ) == 0x65)) {
							ef_scope_random_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 27:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_empty_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F62686769656E7F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6563)) {
							ef_scope_any_empty_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x62:
						// build_university_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696E757F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79746973726576) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74697061637F6E69) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6C61)) {
							cobj.build_university_in_capital(parse_ef_build_university_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 30:
					// random_empty_neighbor_province
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F6D6F646E6172) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69656E7F7974706D) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F726F626867) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[28]) | 0x2020 ) == 0x6563)) {
						ef_scope_random_empty_neighbor_province(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 34:
					// any_existing_country_except_scoped
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736978657F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F676E6974) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6378657F7972746E) && (*(uint64_t const*)(&cur.content[24]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F747065) && (*(uint16_t const*)(&cur.content[32]) | 0x2020 ) == 0x6465)) {
						ef_scope_any_existing_country_except_scoped(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				default:
					ef_scope_variable(cur.content, gen, err, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 5:
					// money
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E6F6D) && (cur.content[4] | 0x20 ) == 0x79)) {
						cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// badboy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F626461) && (cur.content[5] | 0x20 ) == 0x79)) {
							cobj.badboy(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// chance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x636E6168) && (cur.content[5] | 0x20 ) == 0x65)) {
							cobj.chance = parse_int(rh_token.content, rh_token.line, err);
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
						// capital
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C61)) {
							cobj.capital(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// end_war
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x777F646E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7261)) {
							cobj.end_war(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// inherit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7265686E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469)) {
							cobj.inherit(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61656C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6573)) {
							cobj.release(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F64) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								cobj.add_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// annex_to
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7F78656E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6F74)) {
								cobj.annex_to(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// election
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.election(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6D:
						// move_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65766F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F70 && (cur.content[7] | 0x20 ) == 0x70)) {
							cobj.move_pop(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// pop_type
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x79747F70) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6570)) {
								cobj.pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// prestige
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69747365) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6567)) {
								cobj.prestige(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x65:
							// religion
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6967696C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E6F)) {
								cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x67:
							// rgo_size
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69737F6F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x657A)) {
								cobj.rgo_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// treasury
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73616572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7275 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.treasury(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// add_crime
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6972637F6464))) {
							cobj.add_crime(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// civilized
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64657A696C697669))) {
							cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x70:
						// plurality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974696C6172756C))) {
							cobj.plurality(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// assimilate
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616C696D697373) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.assimilate(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// change_tag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61747F65676E6168) && (cur.content[9] | 0x20 ) == 0x67)) {
							cobj.change_tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6C:
						// leadership
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6968737265646165) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.leadership(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neutrality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C6172747565) && (cur.content[9] | 0x20 ) == 0x79)) {
							cobj.neutrality(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// reduce_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6563756465) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.reduce_pop(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6B:
						// kill_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461656C7F6C6C69) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7265)) {
							cobj.kill_leader(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalize
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C616E6F697461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x657A)) {
							cobj.nationalize(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_core
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F65766F6D65) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6572)) {
							cobj.remove_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// enable_canal
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656C62616E65) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C616E61))) {
						cobj.enable_canal(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6E:
								// consciousness
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E73756F696373) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x7373)) {
									cobj.consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x75:
								// country_event
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6576657F7972746E) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x746E)) {
									cobj.country_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_vassal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F65746165) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6173 && (cur.content[12] | 0x20 ) == 0x6C)) {
								cobj.create_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalvalue
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766C616E6F697461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_crisis
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72637F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73697369))) {
							cobj.remove_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_news_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x667F7377656E7F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x616C && (cur.content[12] | 0x20 ) == 0x67)) {
								cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// social_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727F6C616963) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x726F && (cur.content[12] | 0x20 ) == 0x6D)) {
								cobj.social_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// change_terrain
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69617272) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.change_terrain(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// leave_alliance
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65766165) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.leave_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x767F657361656C65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (cur.content[13] | 0x20 ) == 0x6C)) {
							cobj.release_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_exhaustion
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75616878657F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697473) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.war_exhaustion(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x68:
							// change_pop_size
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x7A69737F) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.change_pop_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// clear_news_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7377656E7F7261) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// clr_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_alliance
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65746165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.create_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// economic_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F63696D6F6E6F) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
								cobj.economic_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// enable_ideology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6564697F656C6261) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x676F6C6F) && (cur.content[14] | 0x20 ) == 0x79)) {
								cobj.enable_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// loop_iterations
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726574697F706F6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697461) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x736E)) {
							cobj.loop_iterations = parse_int(rh_token.content, rh_token.line, err);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MILITARY_
						// running -  ILITARY_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69))) {
							switch(0x20 | int32_t(cur.content[9])) {
							case 0x61:
								// military_access
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x73656363) && (cur.content[14] | 0x20 ) == 0x73)) {
									cobj.military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// military_reform
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
									cobj.military_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// PR
						// running -  R
						if((true && (cur.content[1] | 0x20 ) == 0x72)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// prestige_factor
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61667F6567697473) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x726F7463))) {
									cobj.prestige_factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// primary_culture
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C75637F7972616D) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65727574))) {
									cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// research_points
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F68637261657365) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7374)) {
							cobj.research_points(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// SE
						// running -  E
						if((true && (cur.content[1] | 0x20 ) == 0x65)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x63:
								// secede_province
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F656465) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65636E69))) {
									cobj.secede_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// set_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.set_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// clr_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726C) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// political_reform
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974696C6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6665727F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x726F && (cur.content[15] | 0x20 ) == 0x6D)) {
							cobj.political_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7465) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_controller
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F637F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7274) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x656C && (cur.content[16] | 0x20 ) == 0x72)) {
								cobj.change_controller(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							// clr_province_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x667F6563) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x616C && (cur.content[16] | 0x20 ) == 0x67)) {
								cobj.clr_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// set_province_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F65636E))) {
							cobj.set_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x79:
						// years_of_research
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F666F7F73726165) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6863726165736572))) {
							cobj.years_of_research(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// change_region_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F6E6F6967) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.change_region_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x64:
						// decrement_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D65726365) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.decrement_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// increment_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D6572636E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.increment_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// activate_technology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F657461766974) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6F6E686365) && (cur.content[18] | 0x20 ) == 0x79)) {
								cobj.activate_technology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x64:
							// add_crisis_interest
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73657265746E697F) && (cur.content[18] | 0x20 ) == 0x74)) {
								cobj.add_crisis_interest(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// end_military_access
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C696D7F646E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656363617F797261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7373)) {
							cobj.end_military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// ADD_
						// running -  DD_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6464 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x61:
								// add_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7275 && (cur.content[19] | 0x20 ) == 0x65)) {
									cobj.add_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// add_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6569 && (cur.content[19] | 0x20 ) == 0x72)) {
									cobj.add_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						// change_province_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E7F65636E69766F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6D61 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.change_province_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// masquerade_as_nation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461726575717361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616E7F73617F65) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6F69 && (cur.content[19] | 0x20 ) == 0x6E)) {
							cobj.masquerade_as_nation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_variable_to_zero
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61697261767F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7A7F6F747F656C62) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7265 && (cur.content[19] | 0x20 ) == 0x6F)) {
							cobj.set_variable_to_zero(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// add_province_modifier
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69646F6D7F65636E) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72656966))) {
							cobj.add_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party_ideology
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6564697F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x79676F6C))) {
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
				case 22:
					// add_crisis_temperature
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736972637F646461) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65706D65747F7369) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x75746172) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6572)) {
						cobj.add_crisis_temperature(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_tax_relative_income
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F7861747F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65766974616C65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6F636E69) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x656D)) {
							cobj.add_tax_relative_income(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_
						// running -  EMOVE_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x766F6D65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F65)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x61:
								// remove_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x7275 && (cur.content[22] | 0x20 ) == 0x65)) {
									cobj.remove_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// remove_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6569 && (cur.content[22] | 0x20 ) == 0x72)) {
									cobj.remove_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 24:
					// remove_province_modifier
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F65766F6D6572) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
						cobj.remove_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 25:
					// change_tag_no_core_switch
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F65676E616863) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6F6E7F6761) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63746977737F6572) && (cur.content[24] | 0x20 ) == 0x68)) {
						cobj.change_tag_no_core_switch(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 30:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_factory_in_capital_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6361667F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F79726F74) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617469706163) && (*(uint32_t const*)(&cur.content[25]) | uint32_t(0x20202020) ) == uint32_t(0x74617473) && (cur.content[29] | 0x20 ) == 0x65)) {
							cobj.build_factory_in_capital_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_RANDOM_
						// running -  EMOVE_RANDOM_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61727F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6D6F646E) && (cur.content[13] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[14])) {
							case 0x65:
								// remove_random_economic_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F63696D6F6E6F63) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_economic_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6D:
								// remove_random_military_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_military_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
event_option parse_event_option(token_generator& gen, error_handler& err, C&& context) {
	event_option cobj;
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
					// if
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6669)) {
						ef_scope_if(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 3:
					// war
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6177 && (cur.content[2] | 0x20 ) == 0x72)) {
						cobj.war(parse_ef_war(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// else
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x736C && (cur.content[3] | 0x20 ) == 0x65)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F72 && (cur.content[3] | 0x20 ) == 0x6D)) {
							ef_scope_from(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x73)) {
							ef_scope_this(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// limit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74696D69))) {
							cobj.limit(ef_limit(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// owner
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72656E77))) {
							ef_scope_owner(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 6:
					// random
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x646E6172) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6D6F)) {
						ef_scope_random(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x707F796E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x706F)) {
							ef_scope_any_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// country
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7972)) {
							ef_scope_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x65:
						// else_if
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65736C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6669)) {
							ef_scope_else_if(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
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
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F79) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								ef_scope_all_core(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// ideology
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F6564) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676F && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.ideology(parse_ef_ideology(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							ef_scope_location(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6F:
						// overlord
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C726576) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x726F && (cur.content[7] | 0x20 ) == 0x64)) {
							ef_scope_overlord(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// relation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74616C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// sea_zone
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F7A7F61) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x656E)) {
								ef_scope_sea_zone(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x75:
							// sub_unit
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6E757F62) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7469)) {
								cobj.sub_unit(parse_ef_sub_unit(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 9:
					// A
					// running -  A
					if((true && (cur.content[0] | 0x20 ) == 0x61)) {
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x69:
							// ai_chance
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6168637F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x636E && (cur.content[8] | 0x20 ) == 0x65)) {
								cobj.ai_chance = make_option_ai_chance(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// ANY_
							// running -  Y_
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x7F79)) {
								switch(0x20 | int32_t(cur.content[4])) {
								case 0x6F:
									// any_owned
									if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
										ef_scope_any_owned(gen, err, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x73:
									// any_state
									if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
										ef_scope_any_state(gen, err, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									ef_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								ef_scope_variable(cur.content, gen, err, context);
								}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
					} else {
						ef_scope_variable(cur.content, gen, err, context);
						}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// controller
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C6C6F72746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							ef_scope_controller(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6D6F646E61) && (cur.content[9] | 0x20 ) == 0x70)) {
							ef_scope_random_pop(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F796E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7972)) {
							ef_scope_any_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(parse_ef_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// from_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F6D6F72) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_from_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// poor_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x617274737F726F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6174)) {
							ef_scope_poor_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_list
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73696C7F6D6F646E) && (cur.content[10] | 0x20 ) == 0x74)) {
								ef_scope_random_list(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x69:
							// rich_strata
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617274737F6863) && (cur.content[10] | 0x20 ) == 0x61)) {
								ef_scope_rich_strata(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x73:
						// state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F63737F65746174) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							ef_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_bounce
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F736968) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6563)) {
							ef_scope_this_bounce(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x75:
						// upper_house
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F687F72657070) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6573)) {
							cobj.upper_house(parse_ef_upper_house(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_war_goal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F677F7261777F64) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6C61)) {
								cobj.add_war_goal(parse_ef_add_war_goal(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_substate
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6174736275737F79) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6574)) {
								ef_scope_any_substate(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							ef_scope_independence(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// loop_bounded
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F627F706F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6564 && (cur.content[11] | 0x20 ) == 0x64)) {
							ef_scope_loop_bounded(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// RANDOM_
						// running -  ANDOM_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F646E61) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F6D)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x6F:
								// random_owned
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x64656E77))) {
									ef_scope_random_owned(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x73:
								// random_state
								if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
									ef_scope_random_state(gen, err, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_variable
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6261697261767F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x656C)) {
								cobj.set_variable(parse_ef_set_variable(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x70:
							// sphere_owner
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E776F7F65726568) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x7265)) {
								ef_scope_sphere_owner(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// capital_scope
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6C61746970) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x706F && (cur.content[12] | 0x20 ) == 0x65)) {
								ef_capital_scope(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6F:
							// country_event
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6E65 && (cur.content[12] | 0x20 ) == 0x74)) {
								cobj.country_event(parse_ef_country_event(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x6D:
						// middle_strata
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F656C646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61746172))) {
							ef_scope_middle_strata(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// party_loyalty
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x796F6C7F79747261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746C61))) {
							cobj.party_loyalty(parse_ef_party_loyalty(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// cultural_union
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617275746C75) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F696E75) && (cur.content[13] | 0x20 ) == 0x6E)) {
							ef_scope_cultural_union(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x64:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// DEFINE_
							// running -  FINE_
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x656E6966) && (cur.content[6] | 0x20 ) == 0x7F)) {
								switch(0x20 | int32_t(cur.content[7])) {
								case 0x61:
									// define_admiral
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72696D64) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_admiral(parse_ef_define_admiral(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								case 0x67:
									// define_general
									if((true && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x72656E65) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6C61)) {
										cobj.define_general(parse_ef_define_general(gen, err, context), err, cur.line, context);
									} else {
										ef_scope_variable(cur.content, gen, err, context);
									}
									break;
								default:
									ef_scope_variable(cur.content, gen, err, context);
									break;
								}
							} else {
								ef_scope_variable(cur.content, gen, err, context);
								}
							break;
						case 0x6F:
							// dominant_issue
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F746E616E696D) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65757373))) {
								cobj.dominant_issue(parse_ef_dominant_issue(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x68:
						// hidden_tooltip
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F747F6E65646469) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69746C6F) && (cur.content[13] | 0x20 ) == 0x70)) {
							ef_scope_hidden_tooltip(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(parse_ef_province_event(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x72746E75) && (cur.content[13] | 0x20 ) == 0x79)) {
							ef_scope_random_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// TRIGGER_
						// running -  RIGGER_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67676972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7265 && (cur.content[7] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[8])) {
							case 0x63:
								// trigger_crisis
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69736972) && (cur.content[13] | 0x20 ) == 0x73)) {
									cobj.trigger_crisis(parse_ef_trigger_crisis(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x72:
								// trigger_revolt
								if((true && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7665) && (cur.content[13] | 0x20 ) == 0x74)) {
									cobj.trigger_revolt(parse_ef_trigger_revolt(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6464) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x696C)) {
							cobj.add_casus_belli(parse_ef_add_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						// change_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61767F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x62616972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x656C)) {
							cobj.change_variable(parse_ef_change_variable(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// modify_relation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F796669646F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6974616C) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E6F)) {
							cobj.relation(parse_ef_relation(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6D6F646E61) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6563)) {
							ef_scope_random_owned(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 16:
					// scaled_militancy
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F64656C616373) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79636E6174696C69))) {
						cobj.scaled_militancy(parse_ef_scaled_militancy(gen, err, context), err, cur.line, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616572677F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265776F707F7265))) {
							ef_scope_any_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_party_name
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E7F7974) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6D61 && (cur.content[16] | 0x20 ) == 0x65)) {
								cobj.change_party_name(parse_ef_change_party_name(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6C:
							// clear_news_scopes
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7377656E7F726165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6F63737F) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6570 && (cur.content[16] | 0x20 ) == 0x73)) {
								gen.discard_group();
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crisis_state_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F657461) && (cur.content[17] | 0x20 ) == 0x65)) {
							ef_crisis_state_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// random_by_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79627F6D6F646E) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
								ef_random_by_modifier(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x65:
							// remove_casus_belli
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361637F65766F6D) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C6C65627F7375))) {
								cobj.remove_casus_belli(parse_ef_remove_casus_belli(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 19:
					// any_defined_country
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696665647F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F64656E) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7274 && (cur.content[18] | 0x20 ) == 0x79)) {
						ef_scope_any_defined_country(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_country_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72746E756F637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696669646F6D7F79) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7265)) {
								cobj.add_country_modifier(parse_ef_add_country_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_country
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x7972)) {
								ef_scope_any_neighbor_country(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x64:
						// diplomatic_influence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756C666E697F63) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x636E && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.diplomatic_influence(parse_ef_diplomatic_influence(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x66:
						// flashpoint_tag_scope
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E696F706873616C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63737F6761747F74) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x706F && (cur.content[19] | 0x20 ) == 0x65)) {
							ef_flashpoint_tag_scope(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_country_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x76657F7972746E75) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6E65 && (cur.content[19] | 0x20 ) == 0x74)) {
							lambda_country_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_greater_power
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72677F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F7265746165) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6577 && (cur.content[19] | 0x20 ) == 0x72)) {
							ef_scope_random_greater_power(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x73:
						// scaled_consciousness
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F64656C6163) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E73756F6963736E) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7365 && (cur.content[19] | 0x20 ) == 0x73)) {
							cobj.scaled_consciousness(parse_ef_scaled_consciousness(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_province_modifier
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6669646F6D7F6563) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6569 && (cur.content[20] | 0x20 ) == 0x72)) {
								cobj.add_province_modifier(parse_ef_add_province_modifier(gen, err, context), err, cur.line, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						case 0x6E:
							// any_neighbor_province
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x62686769656E7F79) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F726F) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x636E && (cur.content[20] | 0x20 ) == 0x65)) {
								ef_scope_any_neighbor_province(gen, err, context);
							} else {
								ef_scope_variable(cur.content, gen, err, context);
							}
							break;
						default:
							ef_scope_variable(cur.content, gen, err, context);
							break;
						}
						break;
					case 0x62:
						// BUILD_
						// running -  UILD_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x646C6975) && (cur.content[5] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x62:
								// build_bank_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F6B6E61) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_bank_in_capital(parse_ef_build_bank_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							case 0x66:
								// build_fort_in_capital
								if((true && (*(uint64_t const*)(&cur.content[7]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F6E697F74726F) && (*(uint32_t const*)(&cur.content[15]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[19]) | 0x2020 ) == 0x6C61)) {
									cobj.build_fort_in_capital(parse_ef_build_fort_in_capital(gen, err, context), err, cur.line, context);
								} else {
									ef_scope_variable(cur.content, gen, err, context);
								}
								break;
							default:
								ef_scope_variable(cur.content, gen, err, context);
								break;
							}
						} else {
							ef_scope_variable(cur.content, gen, err, context);
							}
						break;
					case 0x63:
						// change_party_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69736F707F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
							cobj.change_party_position(parse_ef_change_party_position(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6C:
						// lambda_province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F6164626D61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F65636E69766F) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E6576))) {
							lambda_province_event(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x6D:
						// move_issue_percentage
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757373697F65766F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65637265707F65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x65676174))) {
							cobj.move_issue_percentage(parse_ef_move_issue_percentage(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x72:
						// random_neighbor_country
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x7972)) {
							ef_scope_random_neighbor_country(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x74:
						// this_remove_casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6D65727F736968) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73757361637F6576) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6C65627F) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x696C)) {
							cobj.this_remove_casus_belli(parse_ef_this_remove_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 24:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_railway_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6961727F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F7961776C) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69706163) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x6174 && (cur.content[23] | 0x20 ) == 0x6C)) {
							cobj.build_railway_in_capital(parse_ef_build_railway_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x72:
						// random_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F6D6F646E61) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F726F62686769) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x69766F72) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x636E && (cur.content[23] | 0x20 ) == 0x65)) {
							ef_scope_random_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 27:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// any_empty_neighbor_province
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974706D657F796E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F62686769656E7F) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6563)) {
							ef_scope_any_empty_neighbor_province(gen, err, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					case 0x62:
						// build_university_in_capital
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696E757F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79746973726576) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74697061637F6E69) && (*(uint16_t const*)(&cur.content[25]) | 0x2020 ) == 0x6C61)) {
							cobj.build_university_in_capital(parse_ef_build_university_in_capital(gen, err, context), err, cur.line, context);
						} else {
							ef_scope_variable(cur.content, gen, err, context);
						}
						break;
					default:
						ef_scope_variable(cur.content, gen, err, context);
						break;
					}
					break;
				case 30:
					// random_empty_neighbor_province
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657F6D6F646E6172) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69656E7F7974706D) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F726F626867) && (*(uint32_t const*)(&cur.content[24]) | uint32_t(0x20202020) ) == uint32_t(0x6E69766F) && (*(uint16_t const*)(&cur.content[28]) | 0x2020 ) == 0x6563)) {
						ef_scope_random_empty_neighbor_province(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				case 34:
					// any_existing_country_except_scoped
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736978657F796E61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F676E6974) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6378657F7972746E) && (*(uint64_t const*)(&cur.content[24]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F63737F747065) && (*(uint16_t const*)(&cur.content[32]) | 0x2020 ) == 0x6465)) {
						ef_scope_any_existing_country_except_scoped(gen, err, context);
					} else {
						ef_scope_variable(cur.content, gen, err, context);
					}
					break;
				default:
					ef_scope_variable(cur.content, gen, err, context);
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
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 5:
					// money
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E6F6D) && (cur.content[4] | 0x20 ) == 0x79)) {
						cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// badboy
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F626461) && (cur.content[5] | 0x20 ) == 0x79)) {
							cobj.badboy(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// chance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x636E6168) && (cur.content[5] | 0x20 ) == 0x65)) {
							cobj.chance = parse_int(rh_token.content, rh_token.line, err);
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
						// capital
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74697061) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C61)) {
							cobj.capital(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x65:
						// end_war
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x777F646E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7261)) {
							cobj.end_war(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x69:
						// inherit
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7265686E) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469)) {
							cobj.inherit(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61656C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6573)) {
							cobj.release(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x64:
							// add_core
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6F637F64) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6572)) {
								cobj.add_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// annex_to
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7F78656E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6F74)) {
								cobj.annex_to(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// election
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.election(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6D:
						// move_pop
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F65766F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F70 && (cur.content[7] | 0x20 ) == 0x70)) {
							cobj.move_pop(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// pop_type
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x79747F70) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6570)) {
								cobj.pop_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x72:
							// prestige
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69747365) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6567)) {
								cobj.prestige(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x65:
							// religion
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6967696C) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6E6F)) {
								cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x67:
							// rgo_size
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x69737F6F) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x657A)) {
								cobj.rgo_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// treasury
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73616572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7275 && (cur.content[7] | 0x20 ) == 0x79)) {
							cobj.treasury(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// add_crime
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6972637F6464))) {
							cobj.add_crime(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// civilized
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64657A696C697669))) {
							cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x70:
						// plurality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974696C6172756C))) {
							cobj.plurality(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// assimilate
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616C696D697373) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.assimilate(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x63:
						// change_tag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61747F65676E6168) && (cur.content[9] | 0x20 ) == 0x67)) {
							cobj.change_tag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6C:
						// leadership
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6968737265646165) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.leadership(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// neutrality
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C6172747565) && (cur.content[9] | 0x20 ) == 0x79)) {
							cobj.neutrality(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// reduce_pop
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F6563756465) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.reduce_pop(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6B:
						// kill_leader
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461656C7F6C6C69) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7265)) {
							cobj.kill_leader(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalize
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696C616E6F697461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x657A)) {
							cobj.nationalize(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_core
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F65766F6D65) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6572)) {
							cobj.remove_core(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// enable_canal
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F656C62616E65) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C616E61))) {
						cobj.enable_canal(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6E:
								// consciousness
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E73756F696373) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x7373)) {
									cobj.consciousness(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x75:
								// country_event
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6576657F7972746E) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x746E)) {
									cobj.country_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_vassal
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F65746165) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6173 && (cur.content[12] | 0x20 ) == 0x6C)) {
								cobj.create_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalvalue
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766C616E6F697461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// remove_crisis
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72637F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73697369))) {
							cobj.remove_crisis(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// set_news_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x667F7377656E7F74) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x616C && (cur.content[12] | 0x20 ) == 0x67)) {
								cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6F:
							// social_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727F6C616963) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x726F && (cur.content[12] | 0x20 ) == 0x6D)) {
								cobj.social_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// change_terrain
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747F65676E6168) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69617272) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.change_terrain(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// leave_alliance
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65766165) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[13] | 0x20 ) == 0x65)) {
							cobj.leave_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// province_event
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E657665) && (cur.content[13] | 0x20 ) == 0x74)) {
							cobj.province_event(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// release_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x767F657361656C65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x61737361) && (cur.content[13] | 0x20 ) == 0x6C)) {
							cobj.release_vassal(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x77:
						// war_exhaustion
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75616878657F7261) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697473) && (cur.content[13] | 0x20 ) == 0x6E)) {
							cobj.war_exhaustion(assoc_type, parse_constant(rh_token.content, rh_token.line, err, context), err, cur.line, context);
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
						case 0x68:
							// change_pop_size
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706F707F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x7A69737F) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.change_pop_size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// clear_news_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F7377656E7F7261) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// clr_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.clr_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
							// create_alliance
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C617F65746165) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x636E6169) && (cur.content[14] | 0x20 ) == 0x65)) {
								cobj.create_alliance(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// economic_reform
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F63696D6F6E6F) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
								cobj.economic_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6E:
							// enable_ideology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6564697F656C6261) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x676F6C6F) && (cur.content[14] | 0x20 ) == 0x79)) {
								cobj.enable_ideology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// loop_iterations
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726574697F706F6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F697461) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x736E)) {
							cobj.loop_iterations = parse_int(rh_token.content, rh_token.line, err);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// MILITARY_
						// running -  ILITARY_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69))) {
							switch(0x20 | int32_t(cur.content[9])) {
							case 0x61:
								// military_access
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x73656363) && (cur.content[14] | 0x20 ) == 0x73)) {
									cobj.military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x72:
								// military_reform
								if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x726F6665) && (cur.content[14] | 0x20 ) == 0x6D)) {
									cobj.military_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// PR
						// running -  R
						if((true && (cur.content[1] | 0x20 ) == 0x72)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x65:
								// prestige_factor
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61667F6567697473) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x726F7463))) {
									cobj.prestige_factor(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x69:
								// primary_culture
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C75637F7972616D) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65727574))) {
									cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// research_points
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F68637261657365) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7374)) {
							cobj.research_points(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// SE
						// running -  E
						if((true && (cur.content[1] | 0x20 ) == 0x65)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x63:
								// secede_province
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F656465) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x65636E69))) {
									cobj.secede_province(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x74:
								// set_global_flag
								if((true && (*(uint64_t const*)(&cur.content[3]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C61626F6C677F) && (*(uint32_t const*)(&cur.content[11]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66))) {
									cobj.set_global_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 16:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// clr_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F726C) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.clr_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// political_reform
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974696C6F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6665727F) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x726F && (cur.content[15] | 0x20 ) == 0x6D)) {
							cobj.political_reform(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_country_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E756F637F7465) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x667F7972) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x616C && (cur.content[15] | 0x20 ) == 0x67)) {
							cobj.set_country_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x68:
							// change_controller
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F637F65676E61) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7274) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x656C && (cur.content[16] | 0x20 ) == 0x72)) {
								cobj.change_controller(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x6C:
							// clr_province_flag
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69766F72707F72) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x667F6563) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x616C && (cur.content[16] | 0x20 ) == 0x67)) {
								cobj.clr_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// set_province_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67616C667F65636E))) {
							cobj.set_province_flag(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x79:
						// years_of_research
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F666F7F73726165) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6863726165736572))) {
							cobj.years_of_research(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// change_region_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65727F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F6E6F6967) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.change_region_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x64:
						// decrement_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D65726365) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.decrement_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// increment_variable
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D6572636E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6261697261767F) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.increment_variable(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// activate_technology
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F657461766974) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6F6E686365) && (cur.content[18] | 0x20 ) == 0x79)) {
								cobj.activate_technology(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x64:
							// add_crisis_interest
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7369736972637F64) && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73657265746E697F) && (cur.content[18] | 0x20 ) == 0x74)) {
								cobj.add_crisis_interest(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// end_military_access
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74696C696D7F646E) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656363617F797261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7373)) {
							cobj.end_military_access(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x61:
						// ADD_
						// running -  DD_
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6464 && (cur.content[3] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x61:
								// add_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7275 && (cur.content[19] | 0x20 ) == 0x65)) {
									cobj.add_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// add_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[5]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[13]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6569 && (cur.content[19] | 0x20 ) == 0x72)) {
									cobj.add_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x63:
						// change_province_name
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F65676E6168) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E7F65636E69766F) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6D61 && (cur.content[19] | 0x20 ) == 0x65)) {
							cobj.change_province_name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// masquerade_as_nation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6461726575717361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616E7F73617F65) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6F69 && (cur.content[19] | 0x20 ) == 0x6E)) {
							cobj.masquerade_as_nation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// set_variable_to_zero
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61697261767F7465) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7A7F6F747F656C62) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x7265 && (cur.content[19] | 0x20 ) == 0x6F)) {
							cobj.set_variable_to_zero(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// add_province_modifier
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69766F72707F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69646F6D7F65636E) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72656966))) {
							cobj.add_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party_ideology
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6564697F797472) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x79676F6C))) {
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
				case 22:
					// add_crisis_temperature
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736972637F646461) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65706D65747F7369) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x75746172) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6572)) {
						cobj.add_crisis_temperature(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 23:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_tax_relative_income
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F7861747F6464) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65766974616C65) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6F636E69) && (*(uint16_t const*)(&cur.content[21]) | 0x2020 ) == 0x656D)) {
							cobj.add_tax_relative_income(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_
						// running -  EMOVE_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x766F6D65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7F65)) {
							switch(0x20 | int32_t(cur.content[7])) {
							case 0x61:
								// remove_accepted_culture
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F64657470656363) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x746C7563) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x7275 && (cur.content[22] | 0x20 ) == 0x65)) {
									cobj.remove_accepted_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// remove_country_modifier
								if((true && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D7F7972746E756F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6669646F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6569 && (cur.content[22] | 0x20 ) == 0x72)) {
									cobj.remove_country_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 24:
					// remove_province_modifier
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F65766F6D6572) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265696669646F6D))) {
						cobj.remove_province_modifier(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 25:
					// change_tag_no_core_switch
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F65676E616863) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F637F6F6E7F6761) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63746977737F6572) && (cur.content[24] | 0x20 ) == 0x68)) {
						cobj.change_tag_no_core_switch(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 30:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// build_factory_in_capital_state
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6361667F646C6975) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E697F79726F74) && (*(uint64_t const*)(&cur.content[17]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C617469706163) && (*(uint32_t const*)(&cur.content[25]) | uint32_t(0x20202020) ) == uint32_t(0x74617473) && (cur.content[29] | 0x20 ) == 0x65)) {
							cobj.build_factory_in_capital_state(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// REMOVE_RANDOM_
						// running -  EMOVE_RANDOM_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61727F65766F6D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6D6F646E) && (cur.content[13] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[14])) {
							case 0x65:
								// remove_random_economic_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F63696D6F6E6F63) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_economic_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x6D:
								// remove_random_military_reforms
								if((true && (*(uint64_t const*)(&cur.content[15]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F79726174696C69) && (*(uint32_t const*)(&cur.content[23]) | uint32_t(0x20202020) ) == uint32_t(0x6F666572) && (*(uint16_t const*)(&cur.content[27]) | 0x2020 ) == 0x6D72 && (cur.content[29] | 0x20 ) == 0x73)) {
									cobj.remove_random_military_reforms(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
}

