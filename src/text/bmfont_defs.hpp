#include "parsers.hpp"

namespace parsers {
template<typename C>
bmfont_file parse_bmfont_file(token_generator& gen, error_handler& err, C&& context) {
	bmfont_file cobj;
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
				case 1:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x78:
						// x
						if((true)) {
							cobj.x(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x79:
						// y
						if((true)) {
							cobj.y(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 2:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// aa
						if((true && (cur.content[1] | 0x20 ) == 0x61)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x69:
						// id
						if((true && (cur.content[1] | 0x20 ) == 0x64)) {
							cobj.id(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// bold
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6C6F && (cur.content[3] | 0x20 ) == 0x64)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x63:
						// char
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6168 && (cur.content[3] | 0x20 ) == 0x72)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x66:
						// face
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6361 && (cur.content[3] | 0x20 ) == 0x65)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x69:
						// info
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x666E && (cur.content[3] | 0x20 ) == 0x6F)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// page
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6761 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.page(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// size
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7A69 && (cur.content[3] | 0x20 ) == 0x65)) {
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
					case 0x63:
						// count
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E756F))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x66:
						// first
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74737269))) {
							cobj.first(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// pages
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73656761))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// width
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68746469))) {
							cobj.width(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// amount
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E756F6D) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.amount(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x63:
						// common
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F6D6D6F) && (cur.content[5] | 0x20 ) == 0x6E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x68:
						// height
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x68676965) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.height(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x69:
						// italic
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x696C6174) && (cur.content[5] | 0x20 ) == 0x63)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x63:
							// SCALE
							// running -  ALE
							if((true && (*(uint16_t const*)(&cur.content[2]) | 0x2020 ) == 0x6C61 && (cur.content[4] | 0x20 ) == 0x65)) {
								switch(0x20 | int32_t(cur.content[5])) {
								case 0x68:
									// scaleh
									if((true)) {
										/* discarded */
									} else {
										err.unhandled_association_key(cur);
									}
									break;
								case 0x77:
									// scalew
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
						case 0x65:
							// second
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x646E6F63))) {
								cobj.second(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x6D:
							// smooth
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x68746F6F))) {
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
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// charset
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73726168) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7465)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6B:
						// kerning
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x696E7265) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// padding
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69646461) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spacing
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69636170) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x78:
						// xoffset
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7366666F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7465)) {
							cobj.xoffset(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x79:
						// yoffset
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7366666F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7465)) {
							cobj.yoffset(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6B:
						// kernings
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x696E7265) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E && (cur.content[7] | 0x20 ) == 0x73)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// stretchh
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74657274) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6863 && (cur.content[7] | 0x20 ) == 0x68)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x78:
						// xadvance
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x61766461) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x636E && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.xadvance(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// lineheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x67696568656E696C) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7468)) {
						cobj.lineheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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

