#include "parsers.hpp"

namespace parsers {
template<typename C>
save_flags parse_save_flags(token_generator& gen, error_handler& err, C&& context) {
	save_flags cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_variables parse_save_variables(token_generator& gen, error_handler& err, C&& context) {
	save_variables cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_pop_ideology parse_save_pop_ideology(token_generator& gen, error_handler& err, C&& context) {
	save_pop_ideology cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_pop_issues parse_save_pop_issues(token_generator& gen, error_handler& err, C&& context) {
	save_pop_issues cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_pop parse_save_pop(token_generator& gen, error_handler& err, C&& context) {
	save_pop cobj;
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
				case 4:
					// need
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6465656E))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// issues
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x75737369) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7365)) {
						cobj.issues(parse_save_pop_issues(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// ideology
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79676F6C6F656469))) {
						cobj.ideology(parse_save_pop_ideology(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 9:
					// stockpile
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C69706B636F7473) && (cur.content[8] | 0x20 ) == 0x65)) {
						gen.discard_group();
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
				case 2:
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 3:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// con
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F)) {
							cobj.con(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6D:
						// mil
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6C69)) {
							cobj.mil(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// bank
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E61 && (cur.content[3] | 0x20 ) == 0x6B)) {
							cobj.bank(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x73:
						// size
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7A69 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.size(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// money
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E6F6D) && (cur.content[4] | 0x20 ) == 0x79)) {
						cobj.money(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 6:
					// random
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x646E6172) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6D6F)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// leftover
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x766F7466) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7265)) {
								/* discarded */
							} else {
								cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							}
							break;
						case 0x69:
							// literacy
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x61726574) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x7963)) {
								cobj.literacy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// promoted
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F6D6F72) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6574 && (cur.content[7] | 0x20 ) == 0x64)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// throttle
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746F7268) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C74 && (cur.content[7] | 0x20 ) == 0x65)) {
							/* discarded */
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
						// con_factor
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F746361667F6E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// life_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6465656E7F656669) && (cur.content[9] | 0x20 ) == 0x73)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// needs_cost
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736F637F73646565) && (cur.content[9] | 0x20 ) == 0x74)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// days_of_loss
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C7F666F7F737961) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x736F && (cur.content[11] | 0x20 ) == 0x73)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6C:
						// luxury_needs
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E7F7972757875) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6465 && (cur.content[11] | 0x20 ) == 0x73)) {
							/* discarded */
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
					// last_spending
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6570737F7473616C) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E69646E) && (cur.content[12] | 0x20 ) == 0x67)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 14:
					// everyday_needs
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7961647972657665) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65656E7F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7364)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 15:
					// production_type
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69746375646F7270) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x747F6E6F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7079 && (cur.content[14] | 0x20 ) == 0x65)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 16:
					// percent_afforded
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F746E6563726570) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646564726F666661))) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// current_producing
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707F746E65727275) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E696375646F72))) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x70:
						// production_income
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F69746375646F72) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6F636E697F6E))) {
							/* discarded */
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
					// percent_sold_export
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F746E6563726570) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7078657F646C6F73) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x726F && (cur.content[18] | 0x20 ) == 0x74)) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 21:
					// percent_sold_domestic
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F746E6563726570) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D6F647F646C6F73) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x69747365) && (cur.content[20] | 0x20 ) == 0x63)) {
						/* discarded */
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
save_war_dated_history parse_save_war_dated_history(token_generator& gen, error_handler& err, C&& context) {
	save_war_dated_history cobj;
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
				case 6:
					// battle
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74746162) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x656C)) {
						gen.discard_group();
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
				case 12:
					// ADD_
					// running -  ADD_
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7F646461))) {
						switch(0x20 | int32_t(cur.content[4])) {
						case 0x61:
							// add_attacker
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x63617474) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x656B && (cur.content[11] | 0x20 ) == 0x72)) {
								cobj.add_attacker(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x64:
							// add_defender
							if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x6E656665) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6564 && (cur.content[11] | 0x20 ) == 0x72)) {
								cobj.add_defender(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						default:
							err.unhandled_association_key(cur);
							break;
						}
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
save_war_history parse_save_war_history(token_generator& gen, error_handler& err, C&& context) {
	save_war_history cobj;
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
					cobj.any_group(cur.content, parse_save_war_dated_history(gen, err, context), err, cur.line, context);
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
save_wargoal parse_save_wargoal(token_generator& gen, error_handler& err, C&& context) {
	save_wargoal cobj;
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
					// date
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65746164))) {
						cobj.date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// actor
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x726F7463))) {
							cobj.actor(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// score
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65726F63))) {
							cobj.score(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// change
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6E616863) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6567)) {
						cobj.change(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// receiver
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7265766965636572))) {
						cobj.receiver(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 12:
					// is_fulfilled
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69666C75667F7369) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x64656C6C))) {
						cobj.is_fulfilled(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_alliance parse_save_alliance(token_generator& gen, error_handler& err, C&& context) {
	save_alliance cobj;
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
					// first
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73726966) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.first(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// second
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F636573) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E)) {
						cobj.second(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// start_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61647F7472617473) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6574)) {
						/* discarded */
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
save_vassal parse_save_vassal(token_generator& gen, error_handler& err, C&& context) {
	save_vassal cobj;
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
					// first
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73726966) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.first(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// second
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F636573) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E)) {
						cobj.second(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// end_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657461647F646E65))) {
						cobj.end_date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// start_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61647F7472617473) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6574)) {
						/* discarded */
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
save_substate parse_save_substate(token_generator& gen, error_handler& err, C&& context) {
	save_substate cobj;
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
					// first
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73726966) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.first(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// second
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F636573) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E)) {
						cobj.second(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// end_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657461647F646E65))) {
						cobj.end_date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// start_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61647F7472617473) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6574)) {
						/* discarded */
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
save_casus_belli parse_save_casus_belli(token_generator& gen, error_handler& err, C&& context) {
	save_casus_belli cobj;
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
					// first
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73726966) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.first(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// second
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F636573) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E)) {
						cobj.second(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// end_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657461647F646E65))) {
						cobj.end_date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// start_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61647F7472617473) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6574)) {
						/* discarded */
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
save_diplomacy parse_save_diplomacy(token_generator& gen, error_handler& err, C&& context) {
	save_diplomacy cobj;
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
				case 6:
					// vassal
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x73736176) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6C61)) {
						cobj.vassal(parse_save_vassal(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// alliance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61696C6C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x636E && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.alliance(parse_save_alliance(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// substate
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74736275) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7461 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.substate(parse_save_substate(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// casus_belli
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65627F73757361) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x696C)) {
							cobj.casus_belli(parse_save_casus_belli(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6C:
						// land_combat
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x626D6F637F646E61) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7461)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6E:
						// naval_combat
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D6F637F6C617661) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6162 && (cur.content[11] | 0x20 ) == 0x74)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// siege_combat
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D6F637F65676569) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6162 && (cur.content[11] | 0x20 ) == 0x74)) {
							gen.discard_group();
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
save_typed_id parse_save_typed_id(token_generator& gen, error_handler& err, C&& context) {
	save_typed_id cobj;
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
						cobj.id = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 4:
					// type
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
						cobj.type = parse_int(rh_token.content, rh_token.line, err);
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
save_rebel_faction parse_save_rebel_faction(token_generator& gen, error_handler& err, C&& context) {
	save_rebel_faction cobj;
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
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 3:
					// pop
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6F70 && (cur.content[2] | 0x20 ) == 0x70)) {
						cobj.pop(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// leader
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6461656C) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.leader(parse_save_typed_id(gen, err, context), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 7:
					// C
					// running -  C
					if((true && (cur.content[0] | 0x20 ) == 0x63)) {
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x6F:
							// country
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x72746E75) && (cur.content[6] | 0x20 ) == 0x79)) {
								cobj.country(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x75:
							// culture
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x7275746C) && (cur.content[6] | 0x20 ) == 0x65)) {
								cobj.culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						default:
							err.unhandled_association_key(cur);
							break;
						}
					} else {
						err.unhandled_association_key(cur);
						}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x70:
						// province
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69766F72) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x636E && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.province(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
				case 9:
					// next_unit
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696E757F7478656E) && (cur.content[8] | 0x20 ) == 0x74)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// government
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6E7265766F67) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x746E)) {
						cobj.government(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x69:
						// independence
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E657065646E) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x636E && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.independence(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6F:
						// organization
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74617A696E616772) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.organization(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_war parse_save_war(token_generator& gen, error_handler& err, C&& context) {
	save_war cobj;
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
				case 7:
					// history
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74736968) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F && (cur.content[6] | 0x20 ) == 0x79)) {
						cobj.history(parse_save_war_history(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// war_goal
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616F677F726177))) {
						cobj.war_goal(parse_save_wargoal(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 16:
					// original_wargoal
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616E696769726F) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616F677261777F))) {
						cobj.original_wargoal(parse_save_wargoal(gen, err, context), err, cur.line, context);
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
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// action
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x69746361) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6E6F)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// attacker
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x63617474) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x656B && (cur.content[7] | 0x20 ) == 0x72)) {
							cobj.attacker(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x64:
						// defender
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E656665) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6564 && (cur.content[7] | 0x20 ) == 0x72)) {
							cobj.defender(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 17:
					// ORIGINAL_
					// running -  ORIGINAL_
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C616E696769726F) && (cur.content[8] | 0x20 ) == 0x7F)) {
						switch(0x20 | int32_t(cur.content[9])) {
						case 0x61:
							// original_attacker
							if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x63617474) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x656B && (cur.content[16] | 0x20 ) == 0x72)) {
								cobj.original_attacker(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x64:
							// original_defender
							if((true && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x6E656665) && (*(uint16_t const*)(&cur.content[14]) | 0x2020 ) == 0x6564 && (cur.content[16] | 0x20 ) == 0x72)) {
								cobj.original_defender(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						default:
							err.unhandled_association_key(cur);
							break;
						}
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
save_rgo parse_save_rgo(token_generator& gen, error_handler& err, C&& context) {
	save_rgo cobj;
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
				case 10:
					// employment
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D796F6C706D65) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x746E)) {
						gen.discard_group();
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
				case 10:
					// goods_type
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79747F73646F6F67) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6570)) {
						cobj.goods_type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// last_income
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x636E697F7473616C) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6D6F && (cur.content[10] | 0x20 ) == 0x65)) {
						/* discarded */
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
save_unit_path parse_save_unit_path(token_generator& gen, error_handler& err, C&& context) {
	save_unit_path cobj;
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
			cobj.free_value(parse_int(cur.content, cur.line, err), err, cur.line, context);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
save_regiment parse_save_regiment(token_generator& gen, error_handler& err, C&& context) {
	save_regiment cobj;
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
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 3:
					// pop
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6F70 && (cur.content[2] | 0x20 ) == 0x70)) {
						cobj.pop(parse_save_typed_id(gen, err, context), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 5:
					// count
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6E756F63) && (cur.content[4] | 0x20 ) == 0x74)) {
						cobj.count(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// strength
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6874676E65727473))) {
						cobj.strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// experience
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65697265707865) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6563)) {
						cobj.experience(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					// organisation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6173696E6167726F) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
						cobj.organisation(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_army parse_save_army(token_generator& gen, error_handler& err, C&& context) {
	save_army cobj;
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
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 4:
					// path
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x68746170))) {
						cobj.path(parse_save_unit_path(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// leader
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6461656C) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.leader(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// regiment
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D69676572))) {
						cobj.regiment(parse_save_regiment(gen, err, context), err, cur.line, context);
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
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.location(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// previous
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69766572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x756F && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.previous(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// supplies
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C707075) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6569 && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.supplies(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 16:
					// dig_in_last_date
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C7F6E697F676964) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657461647F747361))) {
						cobj.dig_in_last_date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 17:
					// movement_progress
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D65766F6D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736572676F72707F) && (cur.content[16] | 0x20 ) == 0x73)) {
						cobj.movement_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_ship parse_save_ship(token_generator& gen, error_handler& err, C&& context) {
	save_ship cobj;
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
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(parse_save_typed_id(gen, err, context), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 8:
					// strength
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6874676E65727473))) {
						cobj.strength(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// experience
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65697265707865) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6563)) {
						cobj.experience(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					// organisation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6173696E6167726F) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
						cobj.organisation(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_navy parse_save_navy(token_generator& gen, error_handler& err, C&& context) {
	save_navy cobj;
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
					// id
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6469)) {
						cobj.id(parse_save_typed_id(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x70:
						// path
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7461 && (cur.content[3] | 0x20 ) == 0x68)) {
							cobj.path(parse_save_unit_path(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// ship
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6968 && (cur.content[3] | 0x20 ) == 0x70)) {
							cobj.ship(parse_save_ship(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 6:
					// leader
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6461656C) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.leader(parse_save_typed_id(gen, err, context), err, cur.line, context);
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
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// location
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.location(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// previous
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69766572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x756F && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.previous(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// supplies
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C707075) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6569 && (cur.content[7] | 0x20 ) == 0x73)) {
							cobj.supplies(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 17:
					// movement_progress
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E656D65766F6D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736572676F72707F) && (cur.content[16] | 0x20 ) == 0x73)) {
						cobj.movement_progress(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_province parse_save_province(token_generator& gen, error_handler& err, C&& context) {
	save_province cobj;
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
				case 3:
					// rgo
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6772 && (cur.content[2] | 0x20 ) == 0x6F)) {
						cobj.rgo(parse_save_rgo(gen, err, context), err, cur.line, context);
					} else {
						cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
					}
					break;
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// army
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D72 && (cur.content[3] | 0x20 ) == 0x79)) {
							cobj.army(parse_save_army(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x6E:
						// navy
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7661 && (cur.content[3] | 0x20 ) == 0x79)) {
							cobj.navy(parse_save_navy(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 10:
					// unit_names
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D616E7F74696E75) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7365)) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
					}
					break;
				case 13:
					// party_loyalty
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6C7F7974726170) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x746C6179) && (cur.content[12] | 0x20 ) == 0x79)) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
					}
					break;
				case 21:
					// military_construction
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726174696C696D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x757274736E6F637F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6F697463) && (cur.content[20] | 0x20 ) == 0x6E)) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
					}
					break;
				default:
					cobj.any_group(cur.content, parse_save_pop(gen, err, context), err, cur.line, context);
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// core
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x726F && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.core(assoc_type, parse_tag(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 5:
					// owner
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656E776F) && (cur.content[4] | 0x20 ) == 0x72)) {
						cobj.owner(assoc_type, parse_tag(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// colonial
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6C6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6169 && (cur.content[7] | 0x20 ) == 0x6C)) {
							cobj.colonial(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x67:
						// garrison
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69727261) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F73 && (cur.content[7] | 0x20 ) == 0x6E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 10:
					// controller
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C6F72746E6F63) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7265)) {
						cobj.controller(assoc_type, parse_tag(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// life_rating
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461727F6566696C) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6E69 && (cur.content[10] | 0x20 ) == 0x67)) {
						cobj.life_rating(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 15:
					// last_imigration
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696D697F7473616C) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x74617267) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6F69 && (cur.content[14] | 0x20 ) == 0x6E)) {
						/* discarded */
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
save_technologies parse_save_technologies(token_generator& gen, error_handler& err, C&& context) {
	save_technologies cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_upper_house parse_save_upper_house(token_generator& gen, error_handler& err, C&& context) {
	save_upper_house cobj;
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
					cobj.any_value(cur.content, assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
save_tax parse_save_tax(token_generator& gen, error_handler& err, C&& context) {
	save_tax cobj;
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
				case 7:
					// tax_eff
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7F786174) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6665 && (cur.content[6] | 0x20 ) == 0x66)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 10:
					// tax_income
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F636E697F786174) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x656D)) {
						gen.discard_group();
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
				case 5:
					// total
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x61746F74) && (cur.content[4] | 0x20 ) == 0x6C)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// factor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636166) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x726F)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// current
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65727275) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x746E)) {
							cobj.current = parse_float(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// max_tax
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x61747F78) && (cur.content[6] | 0x20 ) == 0x78)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x69:
							// min_tax
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x61747F6E) && (cur.content[6] | 0x20 ) == 0x78)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						default:
							err.unhandled_association_key(cur);
							break;
						}
						break;
					case 0x72:
						// reserve
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x72657365) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6576)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 8:
					// settings
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73676E6974746573))) {
						cobj.current = parse_float(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x72:
						// RANGELIMITM
						// running -  ANGELIMITM
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x696D696C65676E61) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6D74)) {
							switch(0x20 | int32_t(cur.content[11])) {
							case 0x61:
								// rangelimitmax
								if((true && (cur.content[12] | 0x20 ) == 0x78)) {
									/* discarded */
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x69:
								// rangelimitmin
								if((true && (cur.content[12] | 0x20 ) == 0x6E)) {
									/* discarded */
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							default:
								err.unhandled_association_key(cur);
								break;
							}
						} else {
							err.unhandled_association_key(cur);
							}
						break;
					case 0x74:
						// temp_settings
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747465737F706D65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x73676E69))) {
							cobj.current = parse_float(rh_token.content, rh_token.line, err);
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
save_relations parse_save_relations(token_generator& gen, error_handler& err, C&& context) {
	save_relations cobj;
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
save_country parse_save_country(token_generator& gen, error_handler& err, C&& context) {
	save_country cobj;
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
					// ai
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x6961)) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 4:
					// bank
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6B6E6162))) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// flags
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7367616C))) {
							cobj.flags(parse_save_flags(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x74:
						// trade
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65646172))) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 7:
					// incomes
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F636E69) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x656D && (cur.content[6] | 0x20 ) == 0x73)) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// expenses
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657078) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6573 && (cur.content[7] | 0x20 ) == 0x73)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x70:
						// poor_tax
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F726F6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6174 && (cur.content[7] | 0x20 ) == 0x78)) {
							cobj.poor_tax(parse_save_tax(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x72:
						// rich_tax
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F686369) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6174 && (cur.content[7] | 0x20 ) == 0x78)) {
							cobj.rich_tax(parse_save_tax(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 9:
					// variables
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C626169726176) && (cur.content[8] | 0x20 ) == 0x73)) {
						cobj.variables(parse_save_variables(gen, err, context), err, cur.line, context);
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// max_bought
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746867756F627F78))) {
								gen.discard_group();
							} else {
								cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
							}
							break;
						case 0x69:
							// middle_tax
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7861747F656C6464))) {
								cobj.middle_tax(parse_save_tax(gen, err, context), err, cur.line, context);
							} else {
								cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
							}
							break;
						default:
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
							break;
						}
						break;
					case 0x74:
						// technology
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6F6E686365) && (cur.content[9] | 0x20 ) == 0x79)) {
							cobj.technology(parse_save_technologies(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 11:
					// upper_house
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F687F7265707075) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7375 && (cur.content[10] | 0x20 ) == 0x65)) {
						cobj.upper_house(parse_save_upper_house(gen, err, context), err, cur.line, context);
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 12:
					// buy_domestic
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D6F647F797562) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x63697473))) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crime_fighting
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6769667F656D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E697468) && (cur.content[13] | 0x20 ) == 0x67)) {
							cobj.crime_fighting(parse_save_tax(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x6E:
						// national_focus
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6C616E6F697461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x75636F66) && (cur.content[13] | 0x20 ) == 0x73)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x67:
						// government_flag
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D6E7265766F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6C667F74) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6761)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x73:
						// social_spending
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x70737F6C6169636F) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69646E65) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x676E)) {
							cobj.social_spending(parse_save_tax(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 16:
					// ai_hard_strategy
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F647261687F6961) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7967657461727473))) {
						gen.discard_group();
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 17:
					// military_spending
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79726174696C696D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69646E6570737F) && (cur.content[16] | 0x20 ) == 0x67)) {
						cobj.military_spending(parse_save_tax(gen, err, context), err, cur.line, context);
					} else {
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// education_spending
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461637564) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E69646E6570737F) && (cur.content[17] | 0x20 ) == 0x67)) {
							cobj.education_spending(parse_save_tax(gen, err, context), err, cur.line, context);
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x69:
						// illegal_inventions
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F6C6167656C6C) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F69746E65766E) && (cur.content[17] | 0x20 ) == 0x73)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				case 20:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// actual_sold_domestic
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F737F6C61757463) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73656D6F647F646C) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6974 && (cur.content[19] | 0x20 ) == 0x63)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					case 0x64:
						// DOMESTIC_
						// running -  OMESTIC_
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F63697473656D6F))) {
							switch(0x20 | int32_t(cur.content[9])) {
							case 0x64:
								// domestic_demand_pool
								if((true && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F646E616D65) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6C6F)) {
									gen.discard_group();
								} else {
									cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
								}
								break;
							case 0x73:
								// domestic_supply_pool
								if((true && (*(uint64_t const*)(&cur.content[10]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F796C707075) && (*(uint16_t const*)(&cur.content[18]) | 0x2020 ) == 0x6C6F)) {
									gen.discard_group();
								} else {
									cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
								}
								break;
							default:
								cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
								break;
							}
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
							}
						break;
					case 0x73:
						// saved_country_supply
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756F637F64657661) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7075737F7972746E) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6C70 && (cur.content[19] | 0x20 ) == 0x79)) {
							gen.discard_group();
						} else {
							cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						}
						break;
					default:
						cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
						break;
					}
					break;
				default:
					cobj.any_group(cur.content, parse_save_relations(gen, err, context), err, cur.line, context);
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
					// badboy
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x62646162) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x796F)) {
						cobj.badboy(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x73:
						// schools
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F6F6863) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x736C)) {
							cobj.schools(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x70:
						// prestige
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74736572) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6769 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.prestige(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// religion
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67696C65) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.religion(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x74:
						// tax_base
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x627F7861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7361 && (cur.content[7] | 0x20 ) == 0x65)) {
							/* discarded */
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
						// civilized
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x64657A696C697669))) {
							cobj.civilized(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6C:
						// leadership
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6968737265646165) && (cur.content[9] | 0x20 ) == 0x70)) {
							cobj.leadership(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					default:
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						break;
					}
					break;
				case 11:
					// suppression
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7373657270707573) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.suppression(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// active_party
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F6576697463) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x79)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// ruling_party
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61707F676E696C75) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7472 && (cur.content[11] | 0x20 ) == 0x79)) {
							cobj.ruling_party(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6C:
						// LAST_
						// running -  AST_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F747361))) {
							switch(0x20 | int32_t(cur.content[5])) {
							case 0x62:
								// last_bankrupt
								if((true && (*(uint32_t const*)(&cur.content[6]) | uint32_t(0x20202020) ) == uint32_t(0x726B6E61) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x7075 && (cur.content[12] | 0x20 ) == 0x74)) {
									cobj.last_bankrupt(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x65:
								// last_election
								if((true && (*(uint32_t const*)(&cur.content[6]) | uint32_t(0x20202020) ) == uint32_t(0x7463656C) && (*(uint16_t const*)(&cur.content[10]) | 0x2020 ) == 0x6F69 && (cur.content[12] | 0x20 ) == 0x6E)) {
									cobj.last_election(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// nationalvalue
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766C616E6F697461) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
							cobj.nationalvalue(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x70:
						// primary_culture
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F7972616D6972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x75746C75) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6572)) {
							cobj.primary_culture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x72:
						// research_points
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F68637261657365) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E696F70) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x7374)) {
							cobj.research_points(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// overseas_penalty
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x736165737265766F) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79746C616E65707F))) {
						/* discarded */
					} else {
						cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					}
					break;
				case 17:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// diplomatic_points
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6974616D6F6C7069) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73746E696F707F63))) {
							cobj.diplomatic_points(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// next_yearly_pulse
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726165797F747865) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65736C75707F796C))) {
							/* discarded */
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
						// AUTO_
						// running -  UTO_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7F6F7475))) {
							switch(0x20 | int32_t(cur.content[5])) {
							case 0x61:
								// auto_assign_leaders
								if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C7F6E67697373) && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x72656461) && (cur.content[18] | 0x20 ) == 0x73)) {
									/* discarded */
								} else {
									cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								}
								break;
							case 0x63:
								// auto_create_leaders
								if((true && (*(uint64_t const*)(&cur.content[6]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C7F6574616572) && (*(uint32_t const*)(&cur.content[14]) | uint32_t(0x20202020) ) == uint32_t(0x72656461) && (cur.content[18] | 0x20 ) == 0x73)) {
									/* discarded */
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
						// last_mission_cancel
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7373696D7F747361) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x636E61637F6E6F69) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6C65)) {
							/* discarded */
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
					case 0x69:
						// is_releasable_vassal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361656C65727F73) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7361767F656C6261) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x6173 && (cur.content[19] | 0x20 ) == 0x6C)) {
							/* discarded */
						} else {
							cobj.any_value(cur.content, assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						}
						break;
					case 0x6E:
						// next_quarterly_pulse
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726175717F747865) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x75707F796C726574) && (*(uint16_t const*)(&cur.content[17]) | 0x2020 ) == 0x736C && (cur.content[19] | 0x20 ) == 0x65)) {
							/* discarded */
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
save_file parse_save_file(token_generator& gen, error_handler& err, C&& context) {
	save_file cobj;
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
					// flags
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67616C66) && (cur.content[4] | 0x20 ) == 0x73)) {
						cobj.flags(parse_save_flags(gen, err, context), err, cur.line, context);
					} else {
						gen.discard_group();
					}
					break;
				case 6:
					// region
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x69676572) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6E6F)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 8:
					// outliner
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72656E696C74756F))) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// diplomacy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7963616D6F6C7069))) {
							cobj.diplomacy(parse_save_diplomacy(gen, err, context), err, cur.line, context);
						} else {
							gen.discard_group();
						}
						break;
					case 0x69:
						// invention
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F69746E65766E))) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					default:
						gen.discard_group();
						break;
					}
					break;
				case 10:
					// active_war
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x777F657669746361) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7261)) {
						cobj.active_war(parse_save_war(gen, err, context), err, cur.line, context);
					} else {
						gen.discard_group();
					}
					break;
				case 11:
					// worldmarket
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72616D646C726F77) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x656B && (cur.content[10] | 0x20 ) == 0x74)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 12:
					// previous_war
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73756F6976657270) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x7261777F))) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 13:
					// great_nations
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616E7F7461657267) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974) && (cur.content[12] | 0x20 ) == 0x73)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 14:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// crisis_manager
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616D7F7369736972) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6567616E) && (cur.content[13] | 0x20 ) == 0x72)) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					case 0x6E:
						// news_collector
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C6F637F737765) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6F746365) && (cur.content[13] | 0x20 ) == 0x72)) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					default:
						gen.discard_group();
						break;
					}
					break;
				case 16:
					// gameplaysettings
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C70656D6167) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73676E6974746573))) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				default:
					gen.discard_group();
					break;
				}
			} else {
				auto const assoc_token = gen.get();
				auto const assoc_type = parse_association_type(assoc_token.content, assoc_token.line, err);
				auto const rh_token = gen.get();
				switch(int32_t(cur.content.length())) {
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// date
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7461 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.date(assoc_type, parse_date(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x75:
						// unit
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x696E && (cur.content[3] | 0x20 ) == 0x74)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x72:
						// rebel
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6C656265))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// state
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65746174))) {
							/* discarded */
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
					// player
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x79616C70) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.player(assoc_type, parse_tag(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x67:
						// government
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E656D6E7265766F) && (cur.content[9] | 0x20 ) == 0x74)) {
							cobj.government(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// start_date
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461647F74726174) && (cur.content[9] | 0x20 ) == 0x65)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 14:
					// automate_trade
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574616D6F747561) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6172747F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6564)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 15:
					// start_pop_index
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F707F7472617473) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E697F70) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6564 && (cur.content[14] | 0x20 ) == 0x78)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 16:
					// automate_sliders
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574616D6F747561) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73726564696C737F))) {
						/* discarded */
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
}

