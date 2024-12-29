#include "parsers.hpp"

namespace parsers {
template<typename C>
gfx_xy_pair parse_gfx_xy_pair(token_generator& gen, error_handler& err, C&& context) {
	gfx_xy_pair cobj;
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
							cobj.x = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x79:
						// y
						if((true)) {
							cobj.y = parse_int(rh_token.content, rh_token.line, err);
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
			cobj.free_value(parse_int(cur.content, cur.line, err), err, cur.line, context);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
gfx_object parse_gfx_object(token_generator& gen, error_handler& err, C&& context) {
	gfx_object cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size_obj = parse_gfx_xy_pair(gen, err, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 5:
					// color
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F6C6F63) && (cur.content[4] | 0x20 ) == 0x72)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// color2
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F6C6F63) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x3272)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// colortwo
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F7774726F6C6F63))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 10:
					// bordersize
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6973726564726F62) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x657A)) {
						cobj.bordersize = parse_gfx_xy_pair(gen, err, context);
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
							cobj.name = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// size
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7A69 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.size = parse_int(rh_token.content, rh_token.line, err);
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
					// flipv
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x70696C66) && (cur.content[4] | 0x20 ) == 0x76)) {
						cobj.flipv = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// loadtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6570797464616F6C))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// linewidth
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6874646977656E69))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6E:
						// noreftype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079746665726F))) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// clicksound
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F736B63696C) && (cur.content[9] | 0x20 ) == 0x64)) {
							cobj.clicksound(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x65:
						// effectfile
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C69667463656666) && (cur.content[9] | 0x20 ) == 0x65)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x68:
						// HORI
						// running -  ORI
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x726F && (cur.content[3] | 0x20 ) == 0x69)) {
							switch(0x20 | int32_t(cur.content[4])) {
							case 0x73:
								// horisontal
								if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61746E6F) && (cur.content[9] | 0x20 ) == 0x6C)) {
									cobj.horizontal = parse_bool(rh_token.content, rh_token.line, err);
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x7A:
								// horizontal
								if((true && (*(uint32_t const*)(&cur.content[5]) | uint32_t(0x20202020) ) == uint32_t(0x61746E6F) && (cur.content[9] | 0x20 ) == 0x6C)) {
									cobj.horizontal = parse_bool(rh_token.content, rh_token.line, err);
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
					case 0x6E:
						// NO
						// running -  O
						if((true && (cur.content[1] | 0x20 ) == 0x6F)) {
							switch(0x20 | int32_t(cur.content[2])) {
							case 0x6F:
								// noofframes
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x61726666) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x656D && (cur.content[9] | 0x20 ) == 0x73)) {
									cobj.noofframes = parse_int(rh_token.content, rh_token.line, err);
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x72:
								// norefcount
								if((true && (*(uint32_t const*)(&cur.content[3]) | uint32_t(0x20202020) ) == uint32_t(0x6F636665) && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E75 && (cur.content[9] | 0x20 ) == 0x74)) {
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
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 11:
					// texturefile
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727574786574) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6C69 && (cur.content[10] | 0x20 ) == 0x65)) {
						cobj.primary_texture = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					// TEXTUREFILE
					// running -  TEXTUREFILE
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6665727574786574) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6C69 && (cur.content[10] | 0x20 ) == 0x65)) {
						switch(0x20 | int32_t(cur.content[11])) {
						case 0x31:
							// texturefile1
							if((true)) {
								cobj.primary_texture = parse_text(rh_token.content, rh_token.line, err);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x32:
							// texturefile2
							if((true)) {
								cobj.secondary_texture = parse_text(rh_token.content, rh_token.line, err);
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
				case 17:
					// transparencecheck
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726170736E617274) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6365686365636E65) && (cur.content[16] | 0x20 ) == 0x6B)) {
						cobj.transparencecheck = parse_bool(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					// allwaystransparent
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737961776C6C61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65726170736E6172) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x746E)) {
						cobj.allwaystransparent = parse_bool(rh_token.content, rh_token.line, err);
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
gfx_object_outer parse_gfx_object_outer(token_generator& gen, error_handler& err, C&& context) {
	gfx_object_outer cobj;
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
					// spritetype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974657469727073) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6570)) {
						cobj.spritetype(parse_gfx_object(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// barcharttype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7474726168637261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.barcharttype(parse_gfx_object(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// piecharttype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7474726168636569) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.piecharttype(parse_gfx_object(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 13:
					// linecharttype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72616863656E696C) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x70797474) && (cur.content[12] | 0x20 ) == 0x65)) {
						cobj.linecharttype(parse_gfx_object(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 14:
					// T
					// running -  T
					if((true && (cur.content[0] | 0x20 ) == 0x74)) {
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x65:
							// textspritetype
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574697270737478) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
								cobj.textspritetype(parse_gfx_object(gen, err, context), err, cur.line, context);
							} else {
								err.unhandled_group_key(cur); gen.discard_group();
							}
							break;
						case 0x69:
							// tilespritetype
							if((true && (*(uint64_t const*)(&cur.content[2]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657469727073656C) && (*(uint32_t const*)(&cur.content[10]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
								cobj.tilespritetype(parse_gfx_object(gen, err, context), err, cur.line, context);
							} else {
								err.unhandled_group_key(cur); gen.discard_group();
							}
							break;
						default:
							err.unhandled_group_key(cur); gen.discard_group();
							break;
						}
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
						}
					break;
				case 15:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x70:
						// progressbartype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6273736572676F72) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79747261) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6570)) {
							cobj.progressbartype(parse_gfx_object(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// scrollingsprite
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E696C6C6F7263) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69727073) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6574)) {
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
				case 16:
					// maskedshieldtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x687364656B73616D) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65707974646C6569))) {
						cobj.maskedshieldtype(parse_gfx_object(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 22:
					// corneredtilespritetype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646572656E726F63) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69727073656C6974) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x79746574) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6570)) {
						cobj.corneredtilespritetype(parse_gfx_object(gen, err, context), err, cur.line, context);
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
template<typename C>
gfx_emfx_actor_type parse_gfx_emfx_actor_type(token_generator& gen, error_handler& err, C&& context) {
	gfx_emfx_actor_type cobj;
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
					// attach
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x61747461) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6863)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 9:
					// animation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6974616D696E61) && (cur.content[8] | 0x20 ) == 0x6E)) {
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
					case 0x69:
						// idle
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6C64 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.idle = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						// move
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x766F && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.move = parse_text(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.name = parse_text(rh_token.content, rh_token.line, err);
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
					// scale
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6C616373) && (cur.content[4] | 0x20 ) == 0x65)) {
						cobj.scale = parse_float(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// attack
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x61747461) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6B63)) {
						cobj.attack = parse_text(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					// actorfile
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6966726F746361) && (cur.content[8] | 0x20 ) == 0x65)) {
						cobj.actorfile = parse_text(rh_token.content, rh_token.line, err);
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
gfx_object_types parse_gfx_object_types(token_generator& gen, error_handler& err, C&& context) {
	gfx_object_types cobj;
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
					// mapinfo
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6970616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x666E && (cur.content[6] | 0x20 ) == 0x6F)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// flagtype
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7467616C) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7079 && (cur.content[7] | 0x20 ) == 0x65)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6D:
						// meshtype
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74687365) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7079 && (cur.content[7] | 0x20 ) == 0x65)) {
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
				case 9:
					// arrowtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974776F727261) && (cur.content[8] | 0x20 ) == 0x65)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// battlearrow
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727261656C747461) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x776F)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6D:
						// maptexttype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974747865747061) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
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
					// provincetype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// billboardtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6472616F626C6C69) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x65:
						// emfxactortype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726F74636178666D) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.emfxactortype(parse_gfx_emfx_actor_type(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 14:
					// projectiontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697463656A6F7270) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x79746E6F) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6570)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 15:
					// animatedmaptext
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646574616D696E61) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x7470616D) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7865 && (cur.content[14] | 0x20 ) == 0x74)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 17:
					// PRO
					// running -  PRO
					if((true && (*(uint16_t const*)(&cur.content[0]) | 0x2020 ) == 0x7270 && (cur.content[2] | 0x20 ) == 0x6F)) {
						switch(0x20 | int32_t(cur.content[3])) {
						case 0x67:
							// progressbar3dtype
							if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x3372616273736572) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x70797464) && (cur.content[16] | 0x20 ) == 0x65)) {
								gen.discard_group();
							} else {
								err.unhandled_group_key(cur); gen.discard_group();
							}
							break;
						case 0x76:
							// provincewatertype
							if((true && (*(uint64_t const*)(&cur.content[4]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6574617765636E69) && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x70797472) && (cur.content[16] | 0x20 ) == 0x65)) {
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
						err.unhandled_group_key(cur); gen.discard_group();
						}
					break;
				case 22:
					// unitstatsbillboardtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461747374696E75) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616F626C6C696273) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x79746472) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6570)) {
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
template<typename C>
gfx_files parse_gfx_files(token_generator& gen, error_handler& err, C&& context) {
	gfx_files cobj;
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
					// fonts
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x746E6F66) && (cur.content[4] | 0x20 ) == 0x73)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 10:
					// lighttypes
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974746867696C) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7365)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 11:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// bitmapfonts
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F6670616D7469) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7374)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6F:
						// objecttypes
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079747463656A62) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7365)) {
							cobj.objecttypes(parse_gfx_object_types(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// spritetypes
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079746574697270) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7365)) {
							gfx_add_obj(gen, err, context);
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
gui_element_common parse_gui_element_common(token_generator& gen, error_handler& err, C&& context) {
	gui_element_common cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// extends
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65747865) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E && (cur.content[6] | 0x20 ) == 0x73)) {
						cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// orientation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461746E6569726F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
button parse_button(token_generator& gen, error_handler& err, C&& context) {
	button cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// format
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x616D726F) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.format(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// parent
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657261) && (cur.content[5] | 0x20 ) == 0x74)) {
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
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltip
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746C6F6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7069)) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// shortcut
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74726F68) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7563 && (cur.content[7] | 0x20 ) == 0x74)) {
							cobj.shortcut(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// BUTTON
						// running -  UTTON
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F747475) && (cur.content[5] | 0x20 ) == 0x6E)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x66:
								// buttonfont
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E6F && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttonfont(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x74:
								// buttontext
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x7865 && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttontext(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// clicksound
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F736B63696C) && (cur.content[9] | 0x20 ) == 0x64)) {
							cobj.clicksound(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spritetype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079746574697270) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6F:
						// orientation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461746E656972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltiptext
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7478)) {
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
				case 17:
					// quadtexturesprite
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7478657464617571) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469727073657275) && (cur.content[16] | 0x20 ) == 0x65)) {
						cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					// delayedtooltiptext
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74646579616C6564) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7478)) {
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
province_script_button parse_province_script_button(token_generator& gen, error_handler& err, C&& context) {
	province_script_button cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 5:
					// allow
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F6C6C61) && (cur.content[4] | 0x20 ) == 0x77)) {
						cobj.allow(province_button_allow(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// effect
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65666665) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7463)) {
						cobj.effect(province_button_effect(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// format
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x616D726F) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.format(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// parent
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657261) && (cur.content[5] | 0x20 ) == 0x74)) {
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
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltip
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746C6F6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7069)) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// shortcut
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74726F68) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7563 && (cur.content[7] | 0x20 ) == 0x74)) {
							cobj.shortcut(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// BUTTON
						// running -  UTTON
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F747475) && (cur.content[5] | 0x20 ) == 0x6E)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x66:
								// buttonfont
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E6F && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttonfont(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x74:
								// buttontext
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x7865 && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttontext(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// clicksound
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F736B63696C) && (cur.content[9] | 0x20 ) == 0x64)) {
							cobj.clicksound(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spritetype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079746574697270) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6F:
						// orientation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461746E656972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltiptext
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7478)) {
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
				case 17:
					// quadtexturesprite
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7478657464617571) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469727073657275) && (cur.content[16] | 0x20 ) == 0x65)) {
						cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					// delayedtooltiptext
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74646579616C6564) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7478)) {
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
nation_script_button parse_nation_script_button(token_generator& gen, error_handler& err, C&& context) {
	nation_script_button cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 5:
					// allow
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6F6C6C61) && (cur.content[4] | 0x20 ) == 0x77)) {
						cobj.allow(nation_button_allow(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// effect
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65666665) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7463)) {
						cobj.effect(nation_button_effect(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// format
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x616D726F) && (cur.content[5] | 0x20 ) == 0x74)) {
							cobj.format(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// parent
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657261) && (cur.content[5] | 0x20 ) == 0x74)) {
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
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltip
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746C6F6F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7069)) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// shortcut
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x74726F68) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7563 && (cur.content[7] | 0x20 ) == 0x74)) {
							cobj.shortcut(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// BUTTON
						// running -  UTTON
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6F747475) && (cur.content[5] | 0x20 ) == 0x6E)) {
							switch(0x20 | int32_t(cur.content[6])) {
							case 0x66:
								// buttonfont
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x6E6F && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttonfont(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
								} else {
									err.unhandled_association_key(cur);
								}
								break;
							case 0x74:
								// buttontext
								if((true && (*(uint16_t const*)(&cur.content[7]) | 0x2020 ) == 0x7865 && (cur.content[9] | 0x20 ) == 0x74)) {
									cobj.buttontext(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// clicksound
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F736B63696C) && (cur.content[9] | 0x20 ) == 0x64)) {
							cobj.clicksound(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spritetype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079746574697270) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6F:
						// orientation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461746E656972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// tooltiptext
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7478)) {
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
				case 17:
					// quadtexturesprite
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7478657464617571) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469727073657275) && (cur.content[16] | 0x20 ) == 0x65)) {
						cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					// delayedtooltiptext
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74646579616C6564) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65747069746C6F6F) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7478)) {
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
image parse_image(token_generator& gen, error_handler& err, C&& context) {
	image cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 5:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// frame
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x656D6172))) {
							cobj.frame(assoc_type, parse_uint(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// scale
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x656C6163))) {
							cobj.scale(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// extends
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65747865) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E && (cur.content[6] | 0x20 ) == 0x73)) {
						cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// buttonmesh
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x73656D6E6F747475) && (cur.content[9] | 0x20 ) == 0x68)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spritetype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7079746574697270) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.spritetype(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// orientation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461746E6569726F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
textbox parse_textbox(token_generator& gen, error_handler& err, C&& context) {
	textbox cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 10:
					// bordersize
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6973726564726F62) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x657A)) {
						cobj.bordersize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// font
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6E6F && (cur.content[3] | 0x20 ) == 0x74)) {
							cobj.font(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x74:
						// text
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7865 && (cur.content[3] | 0x20 ) == 0x74)) {
							cobj.text(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// format
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6D726F66) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7461)) {
						cobj.format(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// extends
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65747865) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E && (cur.content[6] | 0x20 ) == 0x73)) {
						cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x66:
						// fixedsize
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657A697364657869))) {
							cobj.fixedsize(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						// maxheight
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7468676965687861))) {
							cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6F:
						// orientation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461746E656972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// texturefile
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6966657275747865) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x656C)) {
							cobj.texturefile(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 18:
					// allwaystransparent
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737961776C6C61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65726170736E6172) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x746E)) {
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
listbox parse_listbox(token_generator& gen, error_handler& err, C&& context) {
	listbox cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// offset
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7366666F) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7465)) {
						cobj.offset(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 10:
					// bordersize
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6973726564726F62) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x657A)) {
						cobj.bordersize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x73:
						// step
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6574 && (cur.content[3] | 0x20 ) == 0x70)) {
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
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spacing
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69636170) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E)) {
							cobj.spacing(assoc_type, parse_uint(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// priority
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x726F6972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469 && (cur.content[7] | 0x20 ) == 0x79)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// background
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F72676B6361) && (cur.content[9] | 0x20 ) == 0x64)) {
							cobj.background(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x68:
						// horizontal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61746E6F7A69726F) && (cur.content[9] | 0x20 ) == 0x6C)) {
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
					// orientation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461746E6569726F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 13:
					// scrollbartype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61626C6C6F726373) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x70797472) && (cur.content[12] | 0x20 ) == 0x65)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					// allwaystransparent
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74737961776C6C61) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65726170736E6172) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x746E)) {
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
overlapping parse_overlapping(token_generator& gen, error_handler& err, C&& context) {
	overlapping cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
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
				case 4:
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// format
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6D726F66) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7461)) {
						cobj.format(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// spacing
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69636170) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x676E)) {
							cobj.spacing(assoc_type, parse_float(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x6D:
						// maxwidth
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x69777861) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7464 && (cur.content[7] | 0x20 ) == 0x68)) {
							cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// orientation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461746E6569726F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
scrollbar parse_scrollbar(token_generator& gen, error_handler& err, C&& context) {
	scrollbar cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x69:
						// icontype
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E6F63) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7079 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.icontype(parse_image(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 10:
					// bordersize
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6973726564726F62) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x657A)) {
						cobj.bordersize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 13:
					// guibuttontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F74747562697567) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x7079746E) && (cur.content[12] | 0x20 ) == 0x65)) {
						cobj.guibuttontype(parse_button(gen, err, context), err, cur.line, context);
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
				case 5:
					// track
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x63617274) && (cur.content[4] | 0x20 ) == 0x6B)) {
						cobj.track(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 6:
					// slider
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x64696C73) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7265)) {
						cobj.slider(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 7:
					// extends
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65747865) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x646E && (cur.content[6] | 0x20 ) == 0x73)) {
						cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6C:
						// lockable
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x616B636F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6C62 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.lockable(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// MAX
							// running -  X
							if((true && (cur.content[2] | 0x20 ) == 0x78)) {
								switch(0x20 | int32_t(cur.content[3])) {
								case 0x76:
									// maxvalue
									if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x65756C61))) {
										cobj.maxvalue(assoc_type, parse_uint(rh_token.content, rh_token.line, err), err, cur.line, context);
									} else {
										err.unhandled_association_key(cur);
									}
									break;
								case 0x77:
									// maxwidth
									if((true && (*(uint32_t const*)(&cur.content[4]) | uint32_t(0x20202020) ) == uint32_t(0x68746469))) {
										cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						case 0x69:
							// minvalue
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x6C61766E) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6575)) {
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
					case 0x70:
						// priority
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x726F6972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7469 && (cur.content[7] | 0x20 ) == 0x79)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// stepsize
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x73706574) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.stepsize(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// maxheight
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x686769656878616D) && (cur.content[8] | 0x20 ) == 0x74)) {
						cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x68:
						// horizontal
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61746E6F7A69726F) && (cur.content[9] | 0x20 ) == 0x6C)) {
							cobj.horizontal(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6C:
						// leftbutton
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F74747562746665) && (cur.content[9] | 0x20 ) == 0x6E)) {
							cobj.leftbutton(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// startvalue
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x756C617674726174) && (cur.content[9] | 0x20 ) == 0x65)) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6F:
						// orientation
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x697461746E656972) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x72:
						// rightbutton
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7474756274686769) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6E6F)) {
							cobj.rightbutton(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					case 0x75:
						// userangelimit
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C65676E61726573) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x74696D69))) {
							cobj.userangelimit(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// RANGELIMITM
					// running -  RANGELIMITM
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D696C65676E6172) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x7469 && (cur.content[10] | 0x20 ) == 0x6D)) {
						switch(0x20 | int32_t(cur.content[11])) {
						case 0x61:
							// rangelimitmaxicon
							if((true && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F636978) && (cur.content[16] | 0x20 ) == 0x6E)) {
								cobj.rangelimitmaxicon(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x69:
							// rangelimitminicon
							if((true && (*(uint32_t const*)(&cur.content[12]) | uint32_t(0x20202020) ) == uint32_t(0x6F63696E) && (cur.content[16] | 0x20 ) == 0x6E)) {
								cobj.rangelimitminicon(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
window parse_window(token_generator& gen, error_handler& err, C&& context) {
	window cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						cobj.size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 7:
					// maxsize
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x7378616D) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7A69 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.maxsize(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// add_size
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x737F6464) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7A69 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.add_size(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x69:
						// icontype
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x746E6F63) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7079 && (cur.content[7] | 0x20 ) == 0x65)) {
							cobj.icontype(parse_image(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// position
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7469736F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x73:
						// shieldtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974646C656968) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.shieldtype(parse_image(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x77:
						// windowtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974776F646E69) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.windowtype(parse_window(gen, err, context), err, cur.line, context);
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
					case 0x65:
						// editboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62746964) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.editboxtype(parse_textbox(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6C:
						// listboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747369) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.listboxtype(parse_listbox(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// textboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747865) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.textboxtype(parse_textbox(gen, err, context), err, cur.line, context);
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
					case 0x61:
						// add_position
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7469736F707F6464) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F69 && (cur.content[11] | 0x20 ) == 0x6E)) {
							cobj.add_position(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x63:
						// checkboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74786F626B636568) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.checkboxtype(parse_button(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// positiontype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6F697469736F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.positiontype(parse_gui_element_common(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// table_layout
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79616C7F656C6261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x756F && (cur.content[11] | 0x20 ) == 0x74)) {
							cobj.table_layout(parse_gfx_xy_pair(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// eu3dialogtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6169643375) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.eu3dialogtype(parse_window(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x67:
						// guibuttontype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F747475626975) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.guibuttontype(parse_button(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// scrollbartype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261626C6C6F7263) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.scrollbartype(parse_scrollbar(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 18:
					// instanttextboxtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74746E6174736E69) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747865) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x6570)) {
						cobj.instanttextboxtype(parse_textbox(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 22:
					// nationscriptbuttontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63736E6F6974616E) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7474756274706972) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x79746E6F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6570)) {
						cobj.nationscriptbuttontype(parse_nation_script_button(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 24:
					// provincescriptbuttontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7562747069726373) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079746E6F7474))) {
						cobj.provincescriptbuttontype(parse_province_script_button(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 26:
					// overlappingelementsboxtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7070616C7265766F) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D656C65676E69) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F6273746E) && (*(uint16_t const*)(&cur.content[24]) | 0x2020 ) == 0x6570)) {
						cobj.overlappingelementsboxtype(parse_overlapping(gen, err, context), err, cur.line, context);
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
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// extends
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x6E657478) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7364)) {
							cobj.extends(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x75:
						// upsound
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x756F7370) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x646E)) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6D:
						switch(0x20 | int32_t(cur.content[1])) {
						case 0x61:
							// maxwidth
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x64697778) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x6874)) {
								cobj.maxwidth(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
							} else {
								err.unhandled_association_key(cur);
							}
							break;
						case 0x6F:
							// moveable
							if((true && (*(uint32_t const*)(&cur.content[2]) | uint32_t(0x20202020) ) == uint32_t(0x62616576) && (*(uint16_t const*)(&cur.content[6]) | 0x2020 ) == 0x656C)) {
								cobj.moveable(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
						// rotation
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x7461746F) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6F69 && (cur.content[7] | 0x20 ) == 0x6E)) {
							cobj.rotation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x64:
						// downsound
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646E756F736E776F))) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6D:
						// maxheight
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7468676965687861))) {
							cobj.maxheight(assoc_type, parse_int(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x62:
						// background
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F72676B6361) && (cur.content[9] | 0x20 ) == 0x64)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x64:
						// dontrender
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65646E6572746E6F) && (cur.content[9] | 0x20 ) == 0x72)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x66:
						// fullscreen
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65657263736C6C75) && (cur.content[9] | 0x20 ) == 0x6E)) {
							cobj.fullscreen(assoc_type, parse_bool(rh_token.content, rh_token.line, err), err, cur.line, context);
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
					// orientation
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7461746E6569726F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6F69 && (cur.content[10] | 0x20 ) == 0x6E)) {
						cobj.orientation(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 14:
					// verticalborder
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C61636974726576) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x64726F62) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7265)) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 16:
					// horizontalborder
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6F7A69726F68) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x726564726F626C61))) {
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
guitypes parse_guitypes(token_generator& gen, error_handler& err, C&& context) {
	guitypes cobj;
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
					// icontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079746E6F6369))) {
						cobj.icontype(parse_image(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 10:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x73:
						// shieldtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974646C656968) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.shieldtype(parse_image(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x77:
						// windowtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x707974776F646E69) && (cur.content[9] | 0x20 ) == 0x65)) {
							cobj.windowtype(parse_window(gen, err, context), err, cur.line, context);
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
					case 0x65:
						// editboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62746964) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.editboxtype(parse_textbox(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x6C:
						// listboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747369) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.listboxtype(parse_listbox(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// textboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747865) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6570)) {
							cobj.textboxtype(parse_textbox(gen, err, context), err, cur.line, context);
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
					case 0x63:
						// checkboxtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74786F626B636568) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.checkboxtype(parse_button(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x70:
						// positiontype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6F697469736F) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x7079 && (cur.content[11] | 0x20 ) == 0x65)) {
							cobj.positiontype(parse_gui_element_common(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x65:
						// eu3dialogtype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676F6C6169643375) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.eu3dialogtype(parse_window(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x67:
						// guibuttontype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F747475626975) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.guibuttontype(parse_button(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x73:
						// scrollbartype
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7261626C6C6F7263) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x65707974))) {
							cobj.scrollbartype(parse_scrollbar(gen, err, context), err, cur.line, context);
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					default:
						err.unhandled_group_key(cur); gen.discard_group();
						break;
					}
					break;
				case 18:
					// instanttextboxtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74746E6174736E69) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F62747865) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x6570)) {
						cobj.instanttextboxtype(parse_textbox(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 22:
					// nationscriptbuttontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63736E6F6974616E) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7474756274706972) && (*(uint32_t const*)(&cur.content[16]) | uint32_t(0x20202020) ) == uint32_t(0x79746E6F) && (*(uint16_t const*)(&cur.content[20]) | 0x2020 ) == 0x6570)) {
						cobj.nationscriptbuttontype(parse_nation_script_button(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 24:
					// provincescriptbuttontype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7562747069726373) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657079746E6F7474))) {
						cobj.provincescriptbuttontype(parse_province_script_button(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 26:
					// overlappingelementsboxtype
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7070616C7265766F) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656D656C65676E69) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7974786F6273746E) && (*(uint16_t const*)(&cur.content[24]) | 0x2020 ) == 0x6570)) {
						cobj.overlappingelementsboxtype(parse_overlapping(gen, err, context), err, cur.line, context);
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
template<typename C>
gui_files parse_gui_files(token_generator& gen, error_handler& err, C&& context) {
	gui_files cobj;
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
					// guitypes
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7365707974697567))) {
						parse_guitypes(gen, err, context);
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

