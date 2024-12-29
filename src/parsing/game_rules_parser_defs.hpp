#include "parsers.hpp"

namespace parsers {
template<typename C>
game_rule_action parse_game_rule_action(token_generator& gen, error_handler& err, C&& context) {
	game_rule_action cobj;
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
						cobj.limit = make_game_rule_trigger(gen, err, context);
					} else {
						err.unhandled_group_key(cur); gen.discard_group();
					}
					break;
				case 6:
					// effect
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x65666665) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x7463)) {
						cobj.effect = make_game_rule_effect(gen, err, context);
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
						cobj.type(assoc_type, parse_text(rh_token.content, rh_token.line, err), err, cur.line, context);
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
game_rules_file parse_game_rules_file(token_generator& gen, error_handler& err, C&& context) {
	game_rules_file cobj;
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
					// action
					if((true && (*(uint32_t const*)(&cur.content[0]) | uint32_t(0x20202020) ) == uint32_t(0x69746361) && (*(uint16_t const*)(&cur.content[4]) | 0x2020 ) == 0x6E6F)) {
						cobj.action(make_game_rule_action(gen, err, context), err, cur.line, context);
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

