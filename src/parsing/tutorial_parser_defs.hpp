#include "parsers.hpp"

namespace parsers {
template<typename C>
tutorial_diplomatic_action parse_tutorial_diplomatic_action(token_generator& gen, error_handler& err, C&& context) {
	tutorial_diplomatic_action cobj;
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
					// actor
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F746361) && (cur.content[4] | 0x20 ) == 0x72)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					// recipient
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E65697069636572) && (cur.content[8] | 0x20 ) == 0x74)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 17:
					// diplomatic_action
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616D6F6C706964) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F697463617F6369) && (cur.content[16] | 0x20 ) == 0x6E)) {
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
tutorial_unit_set parse_tutorial_unit_set(token_generator& gen, error_handler& err, C&& context) {
	tutorial_unit_set cobj;
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
					// morale
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x61726F6D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x656C)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// location
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697461636F6C))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					// organisation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6173696E6167726F) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
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
tutorial_page parse_tutorial_page(token_generator& gen, error_handler& err, C&& context) {
	tutorial_page cobj;
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
					// effect
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65666665) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7463)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// unit_set
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7465737F74696E75))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 11:
					// window_size
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F776F646E6977) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7A69 && (cur.content[10] | 0x20 ) == 0x65)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 17:
					// diplomatic_action
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74616D6F6C706964) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F697463617F6369) && (cur.content[16] | 0x20 ) == 0x6E)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 24:
					// tutorial_window_position
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6169726F747574) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F776F646E69777F) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697469736F70))) {
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
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x67:
						// goto
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x746F && (cur.content[3] | 0x20 ) == 0x6F)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// text
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7865 && (cur.content[3] | 0x20 ) == 0x74)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x7A:
						// zoom
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6F6F && (cur.content[3] | 0x20 ) == 0x6D)) {
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
					// TEXT
					// running -  TEXT
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74786574))) {
						switch(0x20 | int32_t(cur.content[4])) {
						case 0x31:
							// text1
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x32:
							// text2
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x33:
							// text3
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x34:
							// text4
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x35:
							// text5
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x36:
							// text6
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x37:
							// text7
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x38:
							// text8
							if((true)) {
								/* discarded */
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x39:
							// text9
							if((true)) {
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
				case 6:
					// text10
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74786574) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x3031)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// lockpan
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x706B636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E61)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						// mapmode
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F6D7061) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6564)) {
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
					// lockzoom
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D6F6F7A6B636F6C))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// diplomacy
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7963616D6F6C7069))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x65:
						// exclusive
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65766973756C6378))) {
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
				case 11:
					// allow_merge
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D7F776F6C6C61) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6772 && (cur.content[10] | 0x20 ) == 0x65)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// allow_screen
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7263737F776F6C6C) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6565 && (cur.content[11] | 0x20 ) == 0x6E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// select_units
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E757F7463656C65) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7469 && (cur.content[11] | 0x20 ) == 0x73)) {
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
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// ALLOW_
						// running -  LLOW_
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x776F6C6C) && (cur.content[5] | 0x20 ) == 0x7F)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x73:
								// allow_screens
								if((true && (*(uint32_t const*)(&cur.content[7]) | uint32_t(0x20202020) ) == uint32_t(0x65657263) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x736E)) {
									/* discarded */
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x75:
								// allow_unpause
								if((true && (*(uint32_t const*)(&cur.content[7]) | uint32_t(0x20202020) ) == uint32_t(0x7561706E) && (*(uint16_t const*)(&cur.content[11]) | 0x2020 ) == 0x6573)) {
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
					case 0x63:
						// custom_action
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63617F6D6F747375) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
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
					// custom_int_arg
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697F6D6F74737563) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x617F746E) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6772)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 15:
					// tutorial_window
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6169726F747574) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E69777F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6F64 && (cur.content[14] | 0x20 ) == 0x77)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// continue_on_action
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65756E69746E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F697463617F6E6F) && (cur.content[17] | 0x20 ) == 0x6E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// specific_exclusive
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F63696669636570) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766973756C637865) && (cur.content[17] | 0x20 ) == 0x65)) {
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
				case 19:
					// cont_on_unit_select
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E6F7F746E6F63) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65737F74696E75) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x6365 && (cur.content[18] | 0x20 ) == 0x74)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 20:
					// allow_province_click
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72707F776F6C6C61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x637F65636E69766F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x6B63696C))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 21:
					// continue_on_interface
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65756E69746E6F63) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65746E697F6E6F7F) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x63616672) && (cur.content[20] | 0x20 ) == 0x65)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 24:
					// cont_on_unit_select_prov
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F6E6F7F746E6F63) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65737F74696E75) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x766F72707F746365))) {
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
tutorial parse_tutorial(token_generator& gen, error_handler& err, C&& context) {
	tutorial cobj;
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
					// page
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65676170))) {
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
				case 4:
					// desc
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x63736564))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					// title
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6C746974) && (cur.content[4] | 0x20 ) == 0x65)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// country
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6E756F63) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7274 && (cur.content[6] | 0x20 ) == 0x79)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// exclusive
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65766973756C6378))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// save_game
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D61677F657661))) {
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
				case 11:
					// basic_start
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737F6369736162) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7261 && (cur.content[10] | 0x20 ) == 0x74)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 15:
					// tutorial_window
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6169726F747574) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6E69777F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6F64 && (cur.content[14] | 0x20 ) == 0x77)) {
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
tutorial_file parse_tutorial_file(token_generator& gen, error_handler& err, C&& context) {
	tutorial_file cobj;
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
				case 8:
					// tutorial
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6169726F747574))) {
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

