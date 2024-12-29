#include "parsers.hpp"

namespace parsers {
template<typename C>
news_text_add parse_news_text_add(token_generator& gen, error_handler& err, C&& context) {
	news_text_add cobj;
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
news_picture_case parse_news_picture_case(token_generator& gen, error_handler& err, C&& context) {
	news_picture_case cobj;
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
					// trigger
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67697274) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6567 && (cur.content[6] | 0x20 ) == 0x72)) {
						cobj.trigger = make_news_case_trigger(gen, err, context);
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
				case 7:
					// picture
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x74636970) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7275 && (cur.content[6] | 0x20 ) == 0x65)) {
						cobj.picture(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
news_title_case parse_news_title_case(token_generator& gen, error_handler& err, C&& context) {
	news_title_case cobj;
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
					// trigger
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67697274) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6567 && (cur.content[6] | 0x20 ) == 0x72)) {
						cobj.trigger = make_news_case_trigger(gen, err, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// text_add
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6464617F74786574))) {
						cobj.text_add(parse_news_text_add(gen, err, context), err, cur.line, context);
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
news_desc_case parse_news_desc_case(token_generator& gen, error_handler& err, C&& context) {
	news_desc_case cobj;
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
					// trigger
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67697274) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6567 && (cur.content[6] | 0x20 ) == 0x72)) {
						cobj.trigger = make_news_case_trigger(gen, err, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 8:
					// text_add
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6464617F74786574))) {
						cobj.text_add(parse_news_text_add(gen, err, context), err, cur.line, context);
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
news_generator_selector parse_news_generator_selector(token_generator& gen, error_handler& err, C&& context) {
	news_generator_selector cobj;
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
					// title_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61637F656C746974) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6573)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					// picture_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65727574636970) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65736163))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 16:
					// description_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7470697263736564) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657361637F6E6F69))) {
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
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							/* discarded */
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
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
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
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
news_generate_article parse_news_generate_article(token_generator& gen, error_handler& err, C&& context) {
	news_generate_article cobj;
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
					// title_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x61637F656C746974) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6573)) {
						cobj.title_case(parse_news_title_case(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 12:
					// picture_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65727574636970) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x65736163))) {
						cobj.picture_case(parse_news_picture_case(gen, err, context), err, cur.line, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 16:
					// description_case
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7470697263736564) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x657361637F6E6F69))) {
						cobj.description_case(parse_news_desc_case(gen, err, context), err, cur.line, context);
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
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x73:
						// size
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7A69 && (cur.content[3] | 0x20 ) == 0x65)) {
							cobj.size(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
news_pattern parse_news_pattern(token_generator& gen, error_handler& err, C&& context) {
	news_pattern cobj;
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
					// news_priority
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6972707F7377656E) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x7469726F) && (cur.content[12] | 0x20 ) == 0x79)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 16:
					// generate_article
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65746172656E6567) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656C63697472617F))) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 18:
					// generator_selector
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F746172656E6567) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463656C65737F72) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x726F)) {
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
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						cobj.name(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
news_case parse_news_case(token_generator& gen, error_handler& err, C&& context) {
	news_case cobj;
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
					// trigger
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x67697274) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6567 && (cur.content[6] | 0x20 ) == 0x72)) {
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
					// priority_add
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x797469726F697270) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6464617F))) {
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
news_priority parse_news_priority(token_generator& gen, error_handler& err, C&& context) {
	news_priority cobj;
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
					// case
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65736163))) {
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
					case 0x6E:
						// name
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x6D61 && (cur.content[3] | 0x20 ) == 0x65)) {
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
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
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
news_on_printing parse_news_on_printing(token_generator& gen, error_handler& err, C&& context) {
	news_on_printing cobj;
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
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
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
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
news_on_collection parse_news_on_collection(token_generator& gen, error_handler& err, C&& context) {
	news_on_collection cobj;
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
							/* discarded */
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x74:
						// type
						if((true && (*(uint16_t const*)(&cur.content[1]) | 0x2020 ) == 0x7079 && (cur.content[3] | 0x20 ) == 0x65)) {
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
			}
		} else {
			err.unhandled_free_value(cur);
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
news_pattern_instance parse_news_pattern_instance(token_generator& gen, error_handler& err, C&& context) {
	news_pattern_instance cobj;
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
		}
	}
	cobj.finish(context);
	return cobj;
}
template<typename C>
news_article_types parse_news_article_types(token_generator& gen, error_handler& err, C&& context) {
	news_article_types cobj;
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
					// fake
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656B6166))) {
						cobj.fake = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 8:
					// decision
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F697369636564))) {
						cobj.decision = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 9:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x69:
						// invention
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E6F69746E65766E))) {
							cobj.invention = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x6E:
						// new_party
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x79747261707F7765))) {
							cobj.new_party = parse_int(rh_token.content, rh_token.line, err);
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
					// game_event
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6576657F656D6167) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x746E)) {
						cobj.game_event = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 11:
					// battle_over
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F7F656C74746162) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6576 && (cur.content[10] | 0x20 ) == 0x72)) {
						cobj.battle_over = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 12:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// ai_afraid_of
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6469617266617F69) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6F7F && (cur.content[11] | 0x20 ) == 0x66)) {
							cobj.ai_afraid_of = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x77:
						// war_declared
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x616C6365647F7261) && (*(uint16_t const*)(&cur.content[9]) | 0x2020 ) == 0x6572 && (cur.content[11] | 0x20 ) == 0x64)) {
							cobj.war_declared = parse_int(rh_token.content, rh_token.line, err);
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
					// crisis_backer
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x627F736973697263) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x656B6361) && (cur.content[12] | 0x20 ) == 0x72)) {
						cobj.crisis_backer = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 14:
					// crisis_started
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x737F736973697263) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x74726174) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6465)) {
						cobj.crisis_started = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 15:
					// crisis_resolved
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x727F736973697263) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x6C6F7365) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x6576 && (cur.content[14] | 0x20 ) == 0x64)) {
						cobj.crisis_resolved = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 17:
					// research_complete
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6863726165736572) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x74656C706D6F637F) && (cur.content[16] | 0x20 ) == 0x65)) {
						cobj.research_complete = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 18:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// ai_likes_very_much
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F73656B696C7F69) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63756D7F79726576) && (cur.content[17] | 0x20 ) == 0x68)) {
							cobj.ai_likes_very_much = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x63:
						// crisis_side_joined
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x69737F7369736972) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x656E696F6A7F6564) && (cur.content[17] | 0x20 ) == 0x64)) {
							cobj.crisis_side_joined = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x67:
						// goods_price_change
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6972707F73646F6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x676E6168637F6563) && (cur.content[17] | 0x20 ) == 0x65)) {
							cobj.goods_price_change = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// peace_offer_accept
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x66666F7F65636165) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x70656363617F7265) && (cur.content[17] | 0x20 ) == 0x74)) {
							cobj.peace_offer_accept = parse_int(rh_token.content, rh_token.line, err);
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
					// rebel_break_country
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x72627F6C65626572) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6E756F637F6B6165) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x7274 && (cur.content[18] | 0x20 ) == 0x79)) {
						cobj.rebel_break_country = parse_int(rh_token.content, rh_token.line, err);
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 21:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x63:
						// construction_complete
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463757274736E6F) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x706D6F637F6E6F69) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x6574656C))) {
							cobj.construction_complete = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					case 0x70:
						// province_change_owner
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65636E69766F72) && (*(uint64_t const*)(&cur.content[9]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F7F65676E616863) && (*(uint32_t const*)(&cur.content[17]) | uint32_t(0x20202020) ) == uint32_t(0x72656E77))) {
							cobj.province_change_owner = parse_int(rh_token.content, rh_token.line, err);
						} else {
							err.unhandled_association_key(cur);
						}
						break;
					default:
						err.unhandled_association_key(cur);
						break;
					}
					break;
				case 26:
					// province_change_controller
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x65636E69766F7270) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65676E6168637F) && (*(uint64_t const*)(&cur.content[16]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6C6C6F72746E6F63) && (*(uint16_t const*)(&cur.content[24]) | 0x2020 ) == 0x7265)) {
						cobj.province_change_controller = parse_int(rh_token.content, rh_token.line, err);
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
news_style_article parse_news_style_article(token_generator& gen, error_handler& err, C&& context) {
	news_style_article cobj;
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
					// size
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x657A6973))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// gui_window
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646E69777F697567) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x776F)) {
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
news_title_image parse_news_title_image(token_generator& gen, error_handler& err, C&& context) {
	news_title_image cobj;
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
					// case
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65736163))) {
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
news_style parse_news_style(token_generator& gen, error_handler& err, C&& context) {
	news_style cobj;
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// article
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x63697472) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x656C)) {
							gen.discard_group();
						} else {
							err.unhandled_group_key(cur); gen.discard_group();
						}
						break;
					case 0x74:
						// trigger
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x67676972) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7265)) {
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
				case 11:
					// title_image
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6D697F656C746974) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6761 && (cur.content[10] | 0x20 ) == 0x65)) {
						gen.discard_group();
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 14:
					// article_limits
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F656C6369747261) && (*(uint32_t const*)(&cur.content[8]) | uint32_t(0x20202020) ) == uint32_t(0x696D696C) && (*(uint16_t const*)(&cur.content[12]) | 0x2020 ) == 0x7374)) {
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
					// name
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x656D616E))) {
						/* discarded */
					} else {
						err.unhandled_association_key(cur);
					}
					break;
				case 10:
					// gui_window
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x646E69777F697567) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x776F)) {
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
news_file parse_news_file(token_generator& gen, error_handler& err, C&& context) {
	news_file cobj;
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
					// newgp
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x6777656E) && (cur.content[4] | 0x20 ) == 0x70)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 7:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// ailoves
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x766F6C69) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x7365)) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					case 0x70:
						// pattern
						if((true && (*(uint32_t const*)(&cur.content[1]) | uint32_t(0x20202020) ) == uint32_t(0x65747461) && (*(uint16_t const*)(&cur.content[5]) | 0x2020 ) == 0x6E72)) {
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
					// aiafraidof
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6469617266616961) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x666F)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 11:
					// on_printing
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x746E6972707F6E6F) && (*(uint16_t const*)(&cur.content[8]) | 0x2020 ) == 0x6E69 && (cur.content[10] | 0x20 ) == 0x67)) {
						gen.discard_group();
					} else {
						gen.discard_group();
					}
					break;
				case 13:
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x6E:
						// news_priority
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F6972707F737765) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x79746972))) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					case 0x6F:
						// on_collection
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x63656C6C6F637F6E) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x6E6F6974))) {
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
					switch(0x20 | int32_t(cur.content[0])) {
					case 0x61:
						// article_tensions
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x747F656C63697472) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69736E65) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6E6F && (cur.content[15] | 0x20 ) == 0x73)) {
							gen.discard_group();
						} else {
							gen.discard_group();
						}
						break;
					case 0x67:
						// generate_article
						if((true && (*(uint64_t const*)(&cur.content[1]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7F65746172656E65) && (*(uint32_t const*)(&cur.content[9]) | uint32_t(0x20202020) ) == uint32_t(0x69747261) && (*(uint16_t const*)(&cur.content[13]) | 0x2020 ) == 0x6C63 && (cur.content[15] | 0x20 ) == 0x65)) {
							cobj.generate_article(parse_news_generate_article(gen, err, context), err, cur.line, context);
						} else {
							gen.discard_group();
						}
						break;
					default:
						gen.discard_group();
						break;
					}
					break;
				case 18:
					// generator_selector
					if((true && (*(uint64_t const*)(&cur.content[0]) | uint64_t(0x2020202020202020) ) == uint64_t(0x6F746172656E6567) && (*(uint64_t const*)(&cur.content[8]) | uint64_t(0x2020202020202020) ) == uint64_t(0x7463656C65737F72) && (*(uint16_t const*)(&cur.content[16]) | 0x2020 ) == 0x726F)) {
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

