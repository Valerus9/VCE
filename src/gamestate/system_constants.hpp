#pragma once
#include <stdint.h>

namespace sys {
	enum class projection_mode : uint8_t {
		globe_ortho = 0,
		flat = 1,
		globe_perspect = 2,
		num_of_modes = 3
	};
	
	enum class difficulty_level : uint8_t {
		very_easy = 0,
		easy = 1,
		normal = 2,
		hard = 3,
		very_hard = 4,
	};
	
	enum class static_game_rule : uint8_t {
		state_transfer,
		start_research,
		increase_relations,
		decrease_relations,
		factory_construction,
		unit_construction,
		delete_factory,
		release_vassal,
		start_election,
		change_influence_priority,
		discredit_advisors,
		expel_advisors,
		ban_embassy,
		increase_opinion,
		decrease_opinion,
		add_to_sphere,
		remove_from_sphere,
		intervene_in_war,
		civilize,
		become_interested_in_crisis,
		change_stockpile_settings,
		fabricate_cb,
		give_military_access,
		ask_military_access,
		release_subject,
		add_war_goal,
		declare_war,
		land_rally_point,
		naval_rally_point,
		release_and_play_as,
		release_and_make_vassal,
		on_colonial_migration,
		on_immigration,
		on_internal_migration,
		count,
	};
	enum class virtual_key : uint8_t {
		NONE = 0x00,
		LBUTTON = 0x01,
		RBUTTON = 0x02,
		CANCEL = 0x03,
		MBUTTON = 0x04,
		XBUTTON_1 = 0x05,
		XBUTTON_2 = 0x06,
		BACK = 0x08,
		TAB = 0x09,
		CLEAR = 0x0C,
		RETURN = 0x0D,
		SHIFT = 0x10,
		CONTROL = 0x11,
		MENU = 0x12,
		PAUSE = 0x13,
		CAPITAL = 0x14,
		KANA = 0x15,
		JUNJA = 0x17,
		FINAL = 0x18,
		KANJI = 0x19,
		ESCAPE = 0x1B,
		CONVERT = 0x1C,
		NONCONVERT = 0x1D,
		ACCEPT = 0x1E,
		MODECHANGE = 0x1F,
		SPACE = 0x20,
		PRIOR = 0x21,
		NEXT = 0x22,
		END = 0x23,
		HOME = 0x24,
		LEFT = 0x25,
		UP = 0x26,
		RIGHT = 0x27,
		DOWN = 0x28,
		SELECT = 0x29,
		PRINT = 0x2A,
		EXECUTE = 0x2B,
		SNAPSHOT = 0x2C,
		INSERT = 0x2D,
		DELETE_KEY = 0x2E,
		HELP = 0x2F,
		NUM_0 = 0x30,
		NUM_1 = 0x31,
		NUM_2 = 0x32,
		NUM_3 = 0x33,
		NUM_4 = 0x34,
		NUM_5 = 0x35,
		NUM_6 = 0x36,
		NUM_7 = 0x37,
		NUM_8 = 0x38,
		NUM_9 = 0x39,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		LWIN = 0x5B,
		RWIN = 0x5C,
		APPS = 0x5D,
		SLEEP = 0x5F,
		NUMPAD0 = 0x60,
		NUMPAD1 = 0x61,
		NUMPAD2 = 0x62,
		NUMPAD3 = 0x63,
		NUMPAD4 = 0x64,
		NUMPAD5 = 0x65,
		NUMPAD6 = 0x66,
		NUMPAD7 = 0x67,
		NUMPAD8 = 0x68,
		NUMPAD9 = 0x69,
		MULTIPLY = 0x6A,
		ADD = 0x6B,
		SEPARATOR = 0x6C,
		SUBTRACT = 0x6D,
		DECIMAL = 0x6E,
		DIVIDE = 0x6F,
		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
		F5 = 0x74,
		F6 = 0x75,
		F7 = 0x76,
		F8 = 0x77,
		F9 = 0x78,
		F10 = 0x79,
		F11 = 0x7A,
		F12 = 0x7B,
		F13 = 0x7C,
		F14 = 0x7D,
		F15 = 0x7E,
		F16 = 0x7F,
		F17 = 0x80,
		F18 = 0x81,
		F19 = 0x82,
		F20 = 0x83,
		F21 = 0x84,
		F22 = 0x85,
		F23 = 0x86,
		F24 = 0x87,
		NAVIGATION_VIEW = 0x88,
		NAVIGATION_MENU = 0x89,
		NAVIGATION_UP = 0x8A,
		NAVIGATION_DOWN = 0x8B,
		NAVIGATION_LEFT = 0x8C,
		NAVIGATION_RIGHT = 0x8D,
		NAVIGATION_ACCEPT = 0x8E,
		NAVIGATION_CANCEL = 0x8F,
		NUMLOCK = 0x90,
		SCROLL = 0x91,
		OEM_NEC_EQUAL = 0x92,
		LSHIFT = 0xA0,
		RSHIFT = 0xA1,
		LCONTROL = 0xA2,
		RCONTROL = 0xA3,
		LMENU = 0xA4,
		RMENU = 0xA5,
		SEMICOLON = 0xBA,
		PLUS = 0xBB,
		COMMA = 0xBC,
		MINUS = 0xBD,
		PERIOD = 0xBE,
		FORWARD_SLASH = 0xBF,
		TILDA = 0xC0,
		OPEN_BRACKET = 0xDB,
		BACK_SLASH = 0xDC,
		CLOSED_BRACKET = 0xDD,
		QUOTE = 0xDE
	};
	enum class key_modifiers : uint8_t {
		modifiers_none = 0x0,
		modifiers_alt = 0x4,
		modifiers_ctrl = 0x2,
		modifiers_shift = 0x1,
		modifiers_ctrl_shift = 0x3,
		modifiers_ctrl_alt = 0x6,
		modifiers_alt_shift = 0x5,
		modifiers_all = 0x7
	};
	constexpr inline float ui_scales[] = { 0.25f, 0.30f, 0.35f, 0.5f, 0.75f, 1.0f, 1.25f, 1.5f, 1.75f, 2.0f, 2.5f, 3.0f };
	constexpr inline uint32_t ui_scales_count = 12;
	
	enum class autosave_frequency : uint8_t {
		none = 0,
		yearly = 1,
		monthly = 2,
		sixmonthly = 3,
		daily = 4,
	};
	
	constexpr inline int32_t max_autosaves = 16;
	
	enum class map_label_mode : uint8_t {
		none = 0,
		linear = 1,
		quadratic = 2,
		cubic = 3
	};
	
	enum class map_zoom_mode : uint8_t {
		panning = 0,
		inverted = 1,
		centered = 2,
		to_cursor = 3,
		away_from_cursor = 4,
	};
	
	enum class map_vassal_color_mode : uint8_t {
		inherit = 0,
		same = 1,
		none = 2
	};
	
	enum class commodity_group : uint8_t {
		military_goods = 0, raw_material_goods, industrial_goods, consumer_goods, industrial_and_consumer_goods, count
	};
	
	enum class network_mode_type {
		single_player,
		client,
		host
	};
	
	enum class color_blind_mode {
		none,
		protan, //lack red
		deutan, //lack green
		tritan, //lack blue
		achroma, //black and white
	};
	
	constexpr inline uint32_t max_event_options = 18;
	constexpr inline uint32_t max_factory_bonuses = 8;
	constexpr inline uint32_t max_languages = 64;
	constexpr inline uint32_t max_news_generator_cases = 8;
	
	enum save_type : uint8_t {
		normal,
		autosave,
		bookmark
	};
} // namespace sys
