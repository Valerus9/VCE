#include <string>
#include <string_view>
#include <variant>
#include <filesystem>
#include "gui_console.hpp"
#include "gui_fps_counter.hpp"
#include "nations.hpp"
#include "serialization.hpp"
#include "stb_image_write.h"
#include "element/gui_element_templates.hpp"

struct command_info {
	static constexpr uint32_t max_arg_slots = 4;

	std::string_view name;
	enum class type : uint8_t {
		none = 0,
		reload,
		abort,
		clear_log,
		fps,
		set_tag,
		help,
		show_stats,
		colour_guide,
		diplomacy_points,
		research_points,
		infamy,
		money,
		westernize,
		unwesternize,
		cb_progress,
		crisis,
		end_game,
		event,
		militancy,
		dump_out_of_sync,
		dump_event_graph,
		prestige,
		force_ally,
		toggle_ai,
		always_allow_wargoals,
		always_allow_reforms,
		always_allow_decisions,
		always_potential_decisions,
		always_accept_deals,
		complete_constructions,
		instant_research,
		game_info,
		spectate,
		conquer_tag,
		change_owner,
		change_control,
		toggle_core,
		province_id_tooltip,
		add_population,
		instant_construction,
		add_year,
		innovate,
		daily_oos_check,
		dump_map,
		list_all_flags,
		set_auto_choice_all,
		clear_auto_choice_all
	} mode = type::none;
	std::string_view desc;
	struct argument_info {
		std::string_view name;
		enum class type : uint8_t {
			none = 0, numeric, tag, text
		} mode = type::none;
		bool optional = false;
	} args[max_arg_slots] = {};
};

inline constexpr command_info possible_commands[] = {
	command_info{"none", command_info::type::none, "Dummy command", {
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"reload", command_info::type::reload, "Reloads VicCEngine", {
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"abort", command_info::type::abort, "Abnormally terminates execution", {
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"clr", command_info::type::clear_log, "Clears console logs", {
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"fps", command_info::type::fps, "Toggles FPS counter", {
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"tag", command_info::type::set_tag, "Set the current player's country", {
		command_info::argument_info{"country", command_info::argument_info::type::tag, false},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"help", command_info::type::help, "Display help", {
		command_info::argument_info{"cmd", command_info::argument_info::type::text, true},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"stats", command_info::type::show_stats, "Shows statistics of the current resources used", {
		command_info::argument_info{"type", command_info::argument_info::type::text, true},
		command_info::argument_info{},
		command_info::argument_info{},
		command_info::argument_info{}
	}},
	command_info{"dp", command_info::type::diplomacy_points, "Adds the specified number of diplo points",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"rp", command_info::type::research_points, "Adds the specified number of research points",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"inf", command_info::type::infamy, "Adds the specified number of infamy",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"cbp", command_info::type::cb_progress, "Adds the specified % of progress towards CB fabrication",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"money", command_info::type::money, "Adds the specified amount of money to the national treasury",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"west", command_info::type::westernize, "Westernizes",
	{command_info::argument_info{}, command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"unwest", command_info::type::unwesternize, "Unwesternizes",
	{command_info::argument_info{}, command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"crisis", command_info::type::crisis, "Force a crisis to occur",
	{command_info::argument_info{}, command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"end_game", command_info::type::end_game, "Ends the game",
	{command_info::argument_info{}, command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"event", command_info::type::event, "Triggers a random country event by its legacy id",
	{command_info::argument_info{"id", command_info::argument_info::type::numeric, false},
	command_info::argument_info{"target", command_info::argument_info::type::tag, true}}},
	command_info{"angry", command_info::type::militancy, "Makes everyone in your nation very militant",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"pr", command_info::type::prestige, "Increases prestige by amount",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}}},
	command_info{"oos", command_info::type::dump_out_of_sync, "Dump an OOS save",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"graph", command_info::type::dump_event_graph, "Dump an event graph",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}}},
	command_info{"fa", command_info::type::force_ally, "Force an alliance between you and a country",
	{command_info::argument_info{"country", command_info::argument_info::type::tag, false}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"toggle_ai", command_info::type::toggle_ai, "Toggles ON/OFF AI for countries",
	{command_info::argument_info{"country", command_info::argument_info::type::tag, false}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	/* doesn't work, removed until someone fixes it
	command_info{ "aw", command_info::type::always_allow_wargoals, "Always allow adding wargoals",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}}, */
	command_info{"ar", command_info::type::always_allow_reforms, "Always allow enacting reforms",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"dida", command_info::type::always_allow_decisions, "Always allow taking decisions",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"didp", command_info::type::always_potential_decisions, "Always showing all decisions",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"cc", command_info::type::complete_constructions, "Complete all current constructions",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"ir", command_info::type::instant_research, "Instant research",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{"ym", command_info::type::always_accept_deals, "AI always accepts our deals",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}}},
	command_info{ "saopt", command_info::type::set_auto_choice_all, "Set all events to auto choice",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "caopt", command_info::type::clear_auto_choice_all, "Clear all events from auto choice",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "spectate", command_info::type::spectate, "Become spectator nation",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "conquer", command_info::type::conquer_tag, "Annexes an entire nation (use 'all' for the entire world)",
	{command_info::argument_info{"tag", command_info::argument_info::type::tag, false}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "chow", command_info::type::change_owner, "Change province owner to country",
	{command_info::argument_info{"province", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "chcon", command_info::type::change_control, "Give province control to country",
	{command_info::argument_info{"province", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "provid", command_info::type::province_id_tooltip, "show province id in mouse tooltip",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "addpop", command_info::type::add_population, "Add a certain ammount of population to your nation",
	{command_info::argument_info{"ammount", command_info::argument_info::type::numeric, false }, command_info::argument_info{ },
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "inc", command_info::type::instant_construction, "Instantly builds all armies and navies and industry",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "add_year", command_info::type::add_year, "Add years to date",
	{command_info::argument_info{"amount", command_info::argument_info::type::numeric, false}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "doos", command_info::type::daily_oos_check, "Toggle daily OOS check",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "dmap", command_info::type::dump_map, "Dumps the map in a MS Paint friendly format",
	{command_info::argument_info{"type", command_info::argument_info::type::text, true}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "laf", command_info::type::list_all_flags, "List all flags",
	{command_info::argument_info{}, command_info::argument_info{},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "tcore", command_info::type::toggle_core, "Toggle add/remove core",
	{command_info::argument_info{"province", command_info::argument_info::type::numeric, false}, command_info::argument_info{"country", command_info::argument_info::type::tag, true},
	command_info::argument_info{}, command_info::argument_info{}} },
	command_info{ "innovate", command_info::type::innovate, "Instantly discovers an innovation. Just use the normal innovation's name with '_' instead of spaces.",
	{command_info::argument_info{"innovation", command_info::argument_info::type::text }, command_info::argument_info{ },
	command_info::argument_info{}, command_info::argument_info{}} },
};

uint32_t levenshtein_distance(std::string_view s1, std::string_view s2) {
	// NOTE: Change parameters as you wish - but these work fine for the majority of mods
	constexpr uint32_t insertion_cost = 1;
	constexpr uint32_t deletion_cost = 1;
	constexpr uint32_t subst_cost = 1;

	if(s1.empty() || s2.empty())
		return uint32_t(s1.empty() ? s2.size() : s1.size());
	std::vector<std::vector<uint32_t>> dist(s1.size(), std::vector<uint32_t>(s2.size(), 0));
	for(size_t i = 1; i < s1.size(); ++i)
		dist[i][0] = uint32_t(i);
	for(size_t j = 1; j < s2.size(); ++j)
		dist[0][j] = uint32_t(j);
	for(size_t j = 1; j < s2.size(); ++j)
		for(size_t i = 1; i < s1.size(); ++i) {
			auto cost = s1[i] == s2[j] ? 0 : subst_cost;
			auto x = std::min(dist[i - 1][j] + deletion_cost, dist[i][j - 1] + insertion_cost);
			dist[i][j] = std::min(x, dist[i - 1][j - 1] + cost);
		}
	return dist[s1.size() - 1][s2.size() - 1];
}

// Splits the strings into tokens and treats them as words individually, it is important that
// the needle DOES NOT have spaces or else the algorithm will not work properly.
// This is for being able to match country names which might be matchable iff treated as individual
// words instead of a big giant text.
uint32_t levenshtein_tokenized_distance(std::string_view needle, std::string_view haystack) {
	assert(needle.find(" ") == std::string::npos);
	uint32_t dist = std::numeric_limits<uint32_t>::max();
	std::string str{ haystack };
	size_t pos = 0;
	while((pos = str.find(" ")) != std::string::npos) {
		auto token = str.substr(0, pos);
		dist = std::min<uint32_t>(dist, levenshtein_distance(needle, token));
		str.erase(0, pos + 1);
	}
	return std::min<uint32_t>(dist, levenshtein_distance(needle, str));
}

bool set_active_tag(sys::state& state, std::string_view tag) noexcept {
	bool found = false;
	state.world.for_each_national_identity([&](dcon::national_identity_id id) {
		auto curr = nations::int_to_tag(state.world.national_identity_get_identifying_int(id));
		if(curr == tag) {
			command::c_switch_nation(state, state.local_player_nation, id);
			found = true;
		}
	});
	return found;
}

void log_to_console(sys::state& state, ui::element_base* parent, std::string_view s) noexcept {
	Cyto::Any output = std::string(s);
	parent->impl_get(state, output);
}

struct parser_state {
	command_info cmd{};
	std::variant< std::monostate, // none
		std::string, // tag/string
		int32_t // numeric
	> arg_slots[command_info::max_arg_slots] = {};
};

dcon::national_identity_id smart_get_national_identity_from_tag(sys::state& state, ui::element_base* parent, std::string_view tag) noexcept {
	dcon::national_identity_id nid{};
	for(auto id : state.world.in_national_identity) {
		if(nations::int_to_tag(state.world.national_identity_get_identifying_int(id)) == tag) {
			nid = id;
			break;
		}
	}

	// print entire schema arguing for the tag and the autosuggester
	if(!bool(nid)) {
		std::pair<uint32_t, dcon::national_identity_id> closest_tag_match{}; // schombert notes: using pair in this way is an abomination
		closest_tag_match.first = std::numeric_limits<uint32_t>::max();
		std::pair<uint32_t, dcon::national_identity_id> closest_name_match{};
		closest_name_match.first = std::numeric_limits<uint32_t>::max();
		for(auto fat_id : state.world.in_national_identity) {
			{ // Tags
				auto name = nations::int_to_tag(state.world.national_identity_get_identifying_int(fat_id));
				uint32_t dist = levenshtein_distance(tag, name);
				if(dist < closest_tag_match.first) {
					closest_tag_match.first = dist;
					closest_tag_match.second = fat_id;
				}
			}
			{ // Names
				auto name = text::produce_simple_string(state, fat_id.get_name());
				std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return char(toupper(char(c))); });
				uint32_t dist = levenshtein_tokenized_distance(tag, name);
				if(dist < closest_name_match.first) {
					closest_name_match.first = dist;
					closest_name_match.second = fat_id;
				}
			}
		}
		// Print results of search
		if(tag.size() == 3) {
			auto fat_id = dcon::fatten(state.world, closest_tag_match.second);
			log_to_console(state, parent,
			"Tag could refer to @" + nations::int_to_tag(fat_id.get_identifying_int()) + " \"?Y" + nations::int_to_tag(fat_id.get_identifying_int()) + "?W\" (?Y" + text::produce_simple_string(state, text::get_name(state, fat_id.get_nation_from_identity_holder().id)) + "?W) Id #" + std::to_string(closest_tag_match.second.value));
		} else {
			auto fat_id = dcon::fatten(state.world, closest_name_match.second);
			log_to_console(state, parent, "Name could refer to @" + nations::int_to_tag(fat_id.get_identifying_int()) + " \"?Y" + nations::int_to_tag(fat_id.get_identifying_int()) + "?W\" (?Y" + text::produce_simple_string(state, text::get_name(state, fat_id.get_nation_from_identity_holder().id)) + "?W) Id #" + std::to_string(closest_name_match.second.value));
		}
		if(tag.size() != 3)
			log_to_console(state, parent, "You need to use ?Ytags?W (3-letters) instead of the full name");
		else
			log_to_console(state, parent, "Is this what you meant?");
	}
	return nid;
}

parser_state parse_command(sys::state& state, std::string_view text) {
	std::string s{ text };
	// Makes all text lowercase for proper processing
	std::transform(s.begin(), s.end(), s.begin(), [](auto c) { return char(tolower(char(c))); });

	// Parse command
	parser_state pstate{};
	pstate.cmd = possible_commands[0];
	size_t first_space = 0;
	for(size_t i = 0; i < s.size(); ++i) {
		if(isspace(s.at(i))) break;
		first_space = i;
	}
	for(auto const& cmd : possible_commands)
		if(s.compare(0, first_space + 1, cmd.name) == 0) {
			pstate.cmd = cmd;
			break;
		}
	if(pstate.cmd.mode == command_info::type::none)
		return parser_state{};
	char const* start = s.data();
	char const* end = s.data() + s.length();
	char const* position = start + pstate.cmd.name.size();
	for(; position < end && isspace(*position); ++position)
		;
	for(uint32_t i = 0; i < command_info::max_arg_slots; ++i) {
		char const* ident_start = position;
		for(; position < end && !isspace(*position); ++position)
			;
		char const* ident_end = position;
		if(ident_start == ident_end)
			break;

		std::string_view ident(ident_start, ident_end);
		switch(pstate.cmd.args[i].mode) {
			case command_info::argument_info::type::text:
			pstate.arg_slots[i] = std::string(ident);
			break;
			case command_info::argument_info::type::tag:
			{
			std::string tag{ ident };
			std::transform(tag.begin(), tag.end(), tag.begin(), [](auto c) { return char(toupper(char(c))); });
				pstate.arg_slots[i] = tag;
				break;
			}
			case command_info::argument_info::type::numeric:
			if(isdigit(ident[0]) || ident[0] == '-') {
				pstate.arg_slots[i] = int32_t(atoi(ident.data()));
				//pstate.arg_slots[i] = int32_t(std::stoi(std::string(ident)));
			} else {
				pstate.arg_slots[i] = int32_t(0);
			}
			break;
			default:
			pstate.arg_slots[i] = std::monostate{};
			break;
		}
		// Skip spaces
		for(; position < end && isspace(*position); ++position)
			;
		if(position >= end)
			break;
	}
	return pstate;
}

void ui::console_edit::render(sys::state& state, int32_t x, int32_t y) noexcept {
	ui::edit_box_element_base::render(state, x, y);

	auto font_handle = base_data.data.text.font_handle;
	auto& font = state.font_collection.get_font(state, text::font_index_from_font_id(state, font_handle));
	// Render the suggestions given (after the inputted text obv)

	float x_offs = 0;
	for(auto& t : internal_layout.contents) {
		x_offs = std::max(x_offs, t.x + t.width);
	}

	if(lhs_suggestion.glyph_info.size() > 0) {
		ogl::render_text(state, lhs_suggestion, ogl::color_modification::none,
			float(x + base_data.data.text.border_size.x) + x_offs, float(y + base_data.data.text.border_size.y),
			get_text_color(state, text::text_color::light_grey), base_data.data.button.font_handle);
		x_offs += state.font_collection.text_extent(state, lhs_suggestion, 0, uint32_t(lhs_suggestion.glyph_info.size()), font_handle);
	}
	if(rhs_suggestion.glyph_info.size() > 0) {
		// Place text right before it ends (centered right)
		x_offs = float(base_data.size.x);
		x_offs -= 24.f;
		x_offs -= state.font_collection.text_extent(state, rhs_suggestion, 0, uint32_t(rhs_suggestion.glyph_info.size()), font_handle);
		ogl::render_text(state, rhs_suggestion, ogl::color_modification::none,
			float(x + base_data.data.text.border_size.x) + x_offs, float(y + base_data.data.text.border_size.y),
			get_text_color(state, text::text_color::light_grey), base_data.data.button.font_handle);
	}
	
}

void ui::console_edit::edit_box_update(sys::state& state, std::string_view s) noexcept {
	lhs_suggestion.glyph_info.clear();
	rhs_suggestion.glyph_info.clear();
	if(s.empty())
		return;

	auto font_handle = base_data.data.text.font_handle;
	auto& font = state.font_collection.get_font(state, text::font_index_from_font_id(state, font_handle));

	std::size_t pos = s.find_last_of(' ');
	if(pos == std::string::npos) {
		// Still typing command - so suggest commands
		std::pair<uint32_t, command_info const*> closest_match =
			std::make_pair<uint32_t, command_info const*>(std::numeric_limits<uint32_t>::max(), &possible_commands[0]);
		for(auto const& cmd : possible_commands) {
			std::string_view name = cmd.name;
			if(name.starts_with(s)) {
				if(name == s)
					return; // No suggestions given...
				uint32_t dist = levenshtein_distance(s, name);
				if(dist < closest_match.first) {
					closest_match.first = dist;
					closest_match.second = &cmd;
				}
			}
		}
		// Only suggest the "unfinished" part of the command and provide a brief description of it
		if(closest_match.second->name.length() > s.length())
			lhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), std::string(closest_match.second->name.substr(s.length())));
		rhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), std::string(closest_match.second->desc));
	} else {
		// Specific suggestions for each command
		if(s.starts_with("tag") && pos + 1 < s.size()) {
			std::string tag = std::string(s.substr(pos + 1));
			if(tag.empty())
				return; // Can't give suggestion if nothing was inputted
			std::transform(tag.begin(), tag.end(), tag.begin(), [](auto c) { return char(toupper(char(c))); });
			// Tag will autofill a country name + indicate it's full name
			std::pair<uint32_t, dcon::national_identity_id> closest_match{};
			closest_match.first = std::numeric_limits<uint32_t>::max();
			state.world.for_each_national_identity([&](dcon::national_identity_id id) {
				dcon::national_identity_fat_id fat_id = dcon::fatten(state.world, id);
				std::string name = nations::int_to_tag(state.world.national_identity_get_identifying_int(id));
				if(name.starts_with(tag)) {
					uint32_t dist = levenshtein_distance(tag, name);
					if(dist < closest_match.first) {
						closest_match.first = dist;
						closest_match.second = id;
					}
				}
			});
			if(closest_match.second) {
				// Now type in a suggestion...
				dcon::nation_id nid = state.world.identity_holder_get_nation(state.world.national_identity_get_identity_holder(closest_match.second));
				std::string name = nations::int_to_tag(state.world.national_identity_get_identifying_int(closest_match.second));
				if(tag.size() < name.size()) {
					lhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), name.substr(tag.size()));
				}
				rhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), std::string(name) + "-" + text::produce_simple_string(state, text::get_name(state, nid)));
			} else {
				if(tag.size() == 1)
					rhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), tag + "?? - ???");
				else if(tag.size() == 2)
					rhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), tag + "? - ???");
			}
		} else if(s.starts_with("innovate") && pos + 1 < s.size()) {
			std::string inputted = std::string(s.substr(pos + 1));
			if(inputted.empty())
				return; // Can't give suggestion if nothing was inputted
			std::transform(inputted.begin(), inputted.end(), inputted.begin(), [](auto c) { return char(tolower(char(c))); });
			// Tag will autofill a country name + indicate it's full name
			std::pair<uint32_t, dcon::invention_id> closest_match{};
			closest_match.first = std::numeric_limits<uint32_t>::max();
			for(auto const id : state.world.in_invention) {
				std::string name = text::produce_simple_string(state, id.get_name());
				std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return char(tolower(c)); });
				if(name.starts_with(inputted)) {
					uint32_t dist = levenshtein_distance(inputted, name);
					if(dist < closest_match.first) {
						closest_match.first = dist;
						closest_match.second = id;
					}
				}
			}
			if(closest_match.second) {
				// Now type in a suggestion...
				std::string name = text::produce_simple_string(state, state.world.invention_get_name(closest_match.second));
				if(inputted.size() < name.size()) {
					std::string canon_name = name;
					std::transform(canon_name.begin(), canon_name.end(), canon_name.begin(), [](unsigned char c) { return char(c == ' ' ? '_' : c); });
					lhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), std::string(canon_name.substr(inputted.size())));
				}
				rhs_suggestion.set_text(state, text::font_index_from_font_id(state, font_handle), name);
			}
		}
	}
}

void ui::console_edit::edit_box_tab(sys::state& state, std::string_view s) noexcept {
	if(s.empty()) {
		edit_box_update(state, s);
		return;
	}

	std::pair<uint32_t, std::string_view> closest_match{};
	closest_match.first = std::numeric_limits<uint32_t>::max();

	// Loop through possible_commands
	for(auto const& cmd : possible_commands) {
		std::string_view name = cmd.name;
		if(name.starts_with(s)) {
			uint32_t dist = levenshtein_distance(s, name);
			if(dist < closest_match.first) {
				closest_match.first = dist;
				closest_match.second = name;
			}
		}
	}
	auto closest_name = closest_match.second;
	if(closest_name.empty()) {
		edit_box_update(state, s);
		return;
	}
	std::string str = std::string(closest_name) + " ";
	set_text(state, str);
	auto index = int32_t(closest_name.size() + 1);
	edit_index_position(state, index);
	edit_box_update(state, str);
}

void ui::console_edit::edit_box_up(sys::state& state) noexcept {
	std::string up = up_history();
	if(!up.empty()) {
		this->set_text(state, up);
		auto index = int32_t(up.size());
		this->edit_index_position(state, index);
	}
}
void ui::console_edit::edit_box_down(sys::state& state) noexcept {
	std::string down = down_history();
	if(!down.empty()) {
		this->set_text(state, down);
		auto index = int32_t(down.size());
		this->edit_index_position(state, index);
	}
}

template<typename F>
void write_single_component(sys::state& state, native_string_view filename, F&& func) {
	auto sdir = simple_fs::get_or_create_oos_directory();
	auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[sys::sizeof_scenario_section(state).total_size]);
	auto buffer_position = func(buffer.get(), state);
	size_t total_size_used = reinterpret_cast<uint8_t*>(buffer_position) - buffer.get();
	simple_fs::write_file(sdir, filename, reinterpret_cast<char*>(buffer.get()), uint32_t(total_size_used));
}

void ui::console_edit::edit_box_enter(sys::state& state, std::string_view s) noexcept {
	if(s.empty()) {
		edit_box_update(state, s);
		return;
	}

	auto pstate = parse_command(state, s);
	if(pstate.cmd.mode == command_info::type::none) {
		edit_box_update(state, s);
		return;
	}

	if(state.network_mode != sys::network_mode_type::single_player) {
		command::chat_message(state, state.local_player_nation, s, dcon::nation_id{});
	}

	log_to_console(state, parent, s);
	for(uint32_t i = 0; i < command_info::max_arg_slots; ++i) {
		if(pstate.cmd.args[i].optional)
			continue;
		if(pstate.cmd.args[i].mode == command_info::argument_info::type::text) {
			if(!std::holds_alternative<std::string>(pstate.arg_slots[i])) {
				log_to_console(state, parent, "Command requires a ?Ytext?W argument at " + std::to_string(i));
				Cyto::Any payload = this;
				impl_get(state, payload);
				edit_box_update(state, s);
				return;
			}
		} else if(pstate.cmd.args[i].mode == command_info::argument_info::type::tag) {
			if(!std::holds_alternative<std::string>(pstate.arg_slots[i])) {
				log_to_console(state, parent, "Command requires a ?Ytag?W argument at " + std::to_string(i));
				Cyto::Any payload = this;
				impl_get(state, payload);
				edit_box_update(state, s);
				return;
			}
		} else if(pstate.cmd.args[i].mode == command_info::argument_info::type::numeric) {
			if(!std::holds_alternative<int32_t>(pstate.arg_slots[i])) {
				log_to_console(state, parent, "Command requires a ?Ynumeric?W argument at " + std::to_string(i));
				Cyto::Any payload = this;
				impl_get(state, payload);
				edit_box_update(state, s);
				return;
			}
		}
	}
	switch(pstate.cmd.mode) {
	case command_info::type::reload:
		log_to_console(state, parent, "Reloading...");
		state.map_state.map_data.clear_opengl_objects();
		state.map_state.map_data.load_map(state);
		//state.map_state.update_borders(state);
		break;
	case command_info::type::abort:
		log_to_console(state, parent, "Aborting...");
		std::abort();
		break;
	case command_info::type::clear_log:
		static_cast<console_window*>(parent)->clear_list(state);
		break;
	case command_info::type::fps:
		if(!state.ui_state.fps_counter) {
			auto fps_counter = make_element_by_type<fps_counter_text_box>(state, "fps_counter");
			state.ui_state.fps_counter = fps_counter.get();
			state.ui_state.root->add_child_to_front(std::move(fps_counter));
		} else {
			state.ui_state.fps_counter->set_visible(state, !state.ui_state.fps_counter->is_visible());
			state.ui_state.root->move_child_to_front(state.ui_state.fps_counter);
		}
		break;
	case command_info::type::set_tag:
	{
		auto tag = std::get<std::string>(pstate.arg_slots[0]);
		if(set_active_tag(state, tag) == false) {
			std::pair<uint32_t, dcon::national_identity_id> closest_tag_match{};
			closest_tag_match.first = std::numeric_limits<uint32_t>::max();
			std::pair<uint32_t, dcon::national_identity_id> closest_name_match{};
			closest_name_match.first = std::numeric_limits<uint32_t>::max();
			state.world.for_each_national_identity([&](dcon::national_identity_id id) {
				auto fat_id = dcon::fatten(state.world, id);
				{ // Tags
					auto name = nations::int_to_tag(state.world.national_identity_get_identifying_int(id));
					uint32_t dist = levenshtein_distance(tag, name);
					if(dist < closest_tag_match.first) {
						closest_tag_match.first = dist;
						closest_tag_match.second = id;
					}
				}
				{ // Names
					auto name = text::produce_simple_string(state, fat_id.get_name());
					std::transform(name.begin(), name.end(), name.begin(), [](auto c) { return char(toupper(char(c))); });
					uint32_t dist = levenshtein_tokenized_distance(tag, name);
					if(dist < closest_name_match.first) {
						closest_name_match.first = dist;
						closest_name_match.second = id;
					}
				}
			});
			// Print results of search
			if(tag.size() == 3) {
				auto fat_id = dcon::fatten(state.world, closest_tag_match.second);
				log_to_console(state, parent,
					"Tag could refer to @" + nations::int_to_tag(fat_id.get_identifying_int()) + " \"?Y" + nations::int_to_tag(fat_id.get_identifying_int()) + "?W\" (?Y" +
							text::produce_simple_string(state, text::get_name(state, fat_id.get_nation_from_identity_holder().id)) + "?W) Id #" +
							std::to_string(closest_tag_match.second.value));
			} else {
				auto fat_id = dcon::fatten(state.world, closest_name_match.second);
				log_to_console(state, parent,
					"Name could refer to @" + nations::int_to_tag(fat_id.get_identifying_int()) + " \"?Y" + nations::int_to_tag(fat_id.get_identifying_int()) + "?W\" (?Y" +
							text::produce_simple_string(state, text::get_name(state, fat_id.get_nation_from_identity_holder().id)) + "?W) Id #" +
							std::to_string(closest_name_match.second.value));
			}

			if(tag.size() != 3)
				log_to_console(state, parent, "You need to use ?Ytags?W (3-letters) instead of the full name");
			else
				log_to_console(state, parent, "Is this what you meant?");
		} else {
			auto nid = smart_get_national_identity_from_tag(state, parent, tag);
			if(bool(nid)) {
				command::c_switch_nation(state, state.local_player_nation, nid);
				log_to_console(state, parent, "Switching to @" + std::string(tag) + " ?Y" + std::string(tag) + "?W");
				state.game_state_updated.store(true, std::memory_order::release);
			}
		}
		state.game_state_updated.store(true, std::memory_order::release);
	} break;
	case command_info::type::help:
	{
		auto log_command_info = [&](auto cmd) {
			std::string text =
				"• ?Y" + std::string(cmd.name) + "?! ";
			for(const auto& arg : cmd.args)
				if(arg.mode != command_info::argument_info::type::none) {
					if(arg.optional)
						text += "?Y[(optional)?!" + std::string(arg.name) + "] ";
					else
						text += "?G(" + std::string(arg.name) + ")?! ";
				}
			text += "- " + std::string(cmd.desc);
			log_to_console(state, parent, text);
			};
		if(std::holds_alternative<std::string>(pstate.arg_slots[0])) {
			auto cmd_name = std::get<std::string>(pstate.arg_slots[0]);
			bool found = false;
			for(auto const& cmd : possible_commands)
				if(cmd.name == cmd_name) {
					log_command_info(cmd);
					found = true;
					break;
				}
			if(!found) {
				log_to_console(state, parent, "Command " + std::string(cmd_name) + " not found :<");
				// Give the user a command they might've mispelt!
				std::pair<uint32_t, command_info> closest_match{};
				closest_match.first = std::numeric_limits<uint32_t>::max();
				for(auto const& cmd : possible_commands) {
					const uint32_t distance = levenshtein_distance(cmd_name, cmd.name);
					if(distance < closest_match.first) {
						closest_match.first = distance;
						closest_match.second = cmd;
					}
				}
				log_to_console(state, parent, "Did you mean ?Y" + std::string(closest_match.second.name) + "?! (" + std::string(closest_match.second.desc) + ")?");
			}
		} else {
			log_to_console(state, parent, "Here's some helpful commands ^-^");
			for(auto const& cmd : possible_commands)
				log_command_info(cmd);
		}
	} break;
	case command_info::type::show_stats:
	{
		log_to_console(state, parent, "Seed: " + std::to_string(state.game_seed));
		log_to_console(state, parent, std::string("Great Wars: "));
		log_to_console(state, parent, state.military_definitions.great_wars_enabled ? "@(T)" : "@(F)");
		log_to_console(state, parent, std::string("World Wars: "));
		log_to_console(state, parent, state.military_definitions.world_wars_enabled ? "@(T)" : "@(F)");
		if(!std::holds_alternative<std::string>(pstate.arg_slots[0])) {
			log_to_console(state, parent, "Valid options: demo(graphics), diplo(macy), eco(nomy), event(s), mil(itary)");
			log_to_console(state, parent, "tech(nology), pol(itics), a(ll)/all");
			log_to_console(state, parent, "Ex: \"stats pol\"");
			break;
		}
		enum class flags : uint8_t {
			none = 0x00,
			demographics = 0x01,
			diplomacy = 0x02,
			economy = 0x04,
			events = 0x08,
			military = 0x10,
			technology = 0x20,
			politics = 0x40,
			all = 0x7F,
			count
		};
		uint8_t v = 0;
		auto const k = std::get<std::string>(pstate.arg_slots[0]);
		if(k[0] == 'd' && k[1] == 'e') { // de(mo)
			v |= uint8_t(flags::demographics);
		} else if(k[0] == 'd') { // d(iplo)
			v |= uint8_t(flags::diplomacy);
		} else if(k[0] == 'e' && k[1] == 'c') { // ec(on)
			v |= uint8_t(flags::economy);
		} else if(k[0] == 'e') { // e(vent)
			v |= uint8_t(flags::events);
		} else if(k[0] == 'm') { // m(il)
			v |= uint8_t(flags::military);
		} else if(k[0] == 't') { // t(ech)
			v |= uint8_t(flags::technology);
		} else if(k[0] == 'p') { // p(ol)
			v |= uint8_t(flags::politics);
		} else if(k[0] == 'a') { // a(ll)
			v |= uint8_t(flags::all);
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YNational Identities?W: " + std::to_string(state.world.national_identity_size()));
			log_to_console(state, parent, "?YPolitical Parties?W: " + std::to_string(state.world.political_party_size()));
			log_to_console(state, parent, "?YReligions?W: " + std::to_string(state.world.religion_size()));
			log_to_console(state, parent, "?YCulture Groups?W: " + std::to_string(state.world.culture_group_size()));
			log_to_console(state, parent, "?YCultures?W: " + std::to_string(state.world.culture_size()));
			log_to_console(state, parent, "?YCulture Group Memberships?W: " + std::to_string(state.world.culture_group_membership_size()));
			log_to_console(state, parent, "?YCultural Unions (Of)?W: " + std::to_string(state.world.cultural_union_of_size()));
		}
		if((v & uint8_t(flags::economy)) != 0) {
			log_to_console(state, parent, "?YCommodities?W: " + std::to_string(state.world.commodity_size()));
			log_to_console(state, parent, "?YModifiers?W: " + std::to_string(state.world.modifier_size()));
			log_to_console(state, parent, "?YFactory Types?W: " + std::to_string(state.world.factory_type_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YIdeology Groups?W: " + std::to_string(state.world.ideology_group_size()));
			log_to_console(state, parent, "?YIdeologies?W: " + std::to_string(state.world.ideology_size()));
			log_to_console(state, parent, "?YIdeology Group Memberships?W: " + std::to_string(state.world.ideology_group_membership_size()));
			log_to_console(state, parent, "?YIssues?W: " + std::to_string(state.world.issue_size()));
			log_to_console(state, parent, "?YIssue Options?W: " + std::to_string(state.world.issue_option_size()));
			log_to_console(state, parent, "?YReforms?W: " + std::to_string(state.world.reform_size()));
			log_to_console(state, parent, "?YReform Options?W: " + std::to_string(state.world.reform_option_size()));
		}
		if((v & uint8_t(flags::diplomacy)) != 0) {
			log_to_console(state, parent, "?YCB Types?W: " + std::to_string(state.world.cb_type_size()));
		}
		if((v & uint8_t(flags::military)) != 0) {
			log_to_console(state, parent, "?YLeader Traits?W: " + std::to_string(state.world.leader_trait_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YPop Types?W: " + std::to_string(state.world.pop_type_size()));
			log_to_console(state, parent, "?YRebel Types?W: " + std::to_string(state.world.rebel_type_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YProvinces?W: " + std::to_string(state.world.province_size()));
			log_to_console(state, parent, "?YProvince Adjacenciess?W: " + std::to_string(state.world.province_adjacency_size()));
			log_to_console(state, parent, "?YNation Adjacencies?W: " + std::to_string(state.world.nation_adjacency_size()));
		}
		if((v & uint8_t(flags::military)) != 0) {
			log_to_console(state, parent, "?YRegiments?W: " + std::to_string(state.world.regiment_size()));
			log_to_console(state, parent, "?YShips?W: " + std::to_string(state.world.ship_size()));
			log_to_console(state, parent, "?YArmies?W: " + std::to_string(state.world.army_size()));
			log_to_console(state, parent, "?YNavies?W: " + std::to_string(state.world.navy_size()));
			log_to_console(state, parent, "?YArmy Controls?W: " + std::to_string(state.world.army_control_size()));
			log_to_console(state, parent, "?YArmy Locations?W: " + std::to_string(state.world.army_location_size()));
			log_to_console(state, parent, "?YArmy Memberships?W: " + std::to_string(state.world.army_membership_size()));
			log_to_console(state, parent, "?YRegiment Sources?W: " + std::to_string(state.world.regiment_source_size()));
			log_to_console(state, parent, "?YNavy Controls?W: " + std::to_string(state.world.navy_control_size()));
			log_to_console(state, parent, "?YNavy Locations?W: " + std::to_string(state.world.navy_location_size()));
			log_to_console(state, parent, "?YNavy Memberships?W: " + std::to_string(state.world.navy_membership_size()));
			log_to_console(state, parent, "?YLeaders?W: " + std::to_string(state.world.leader_size()));
			log_to_console(state, parent, "?YArmy Leadership (leader<->army)?W: " + std::to_string(state.world.army_leadership_size()));
			log_to_console(state, parent, "?YNavy Leadership (leader<->navy)?W: " + std::to_string(state.world.navy_leadership_size()));
			log_to_console(state, parent, "?YLeader Loyalties (leader<->nation membership)?W: " + std::to_string(state.world.leader_loyalty_size()));
		}
		if((v & uint8_t(flags::diplomacy)) != 0) {
			log_to_console(state, parent, "?YWars?W: " + std::to_string(state.world.war_size()));
			log_to_console(state, parent, "?YWargoals?W: " + std::to_string(state.world.wargoal_size()));
			log_to_console(state, parent, "?YWar Participants?W: " + std::to_string(state.world.war_participant_size()));
			log_to_console(state, parent, "?YWargoals Attached (wargoal<->war)?W: " + std::to_string(state.world.wargoals_attached_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YState Definitions?W: " + std::to_string(state.world.state_definition_size()));
			log_to_console(state, parent, "?YState Instances?W: " + std::to_string(state.world.state_instance_size()));
		}
		if((v & uint8_t(flags::diplomacy)) != 0) {
			log_to_console(state, parent, "?YColonizations?W: " + std::to_string(state.world.colonization_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YState Ownerships?W: " + std::to_string(state.world.state_ownership_size()));
			log_to_console(state, parent, "?YAbstract State Memberships?W: " + std::to_string(state.world.abstract_state_membership_size()));
			log_to_console(state, parent, "?YCores?W: " + std::to_string(state.world.core_size()));
			log_to_console(state, parent, "?YIdentity Holders?W: " + std::to_string(state.world.identity_holder_size()));
		}
		if((v & uint8_t(flags::technology)) != 0) {
			log_to_console(state, parent, "?YTechnologies?W: " + std::to_string(state.world.technology_size()));
			log_to_console(state, parent, "?YInventions?W: " + std::to_string(state.world.invention_size()));
		}
		if((v & uint8_t(flags::diplomacy)) != 0) {
			log_to_console(state, parent, "?YNations?W: " + std::to_string(state.world.nation_size()));
			log_to_console(state, parent, "?YDiplomatic Relations?W: " + std::to_string(state.world.diplomatic_relation_size()));
			log_to_console(state, parent, "?YUnilateral Relationships?W: " + std::to_string(state.world.unilateral_relationship_size()));
			log_to_console(state, parent, "?YGP Relationships?W: " + std::to_string(state.world.gp_relationship_size()));
		}
		if((v & uint8_t(flags::economy)) != 0) {
			log_to_console(state, parent, "?YFactories?W: " + std::to_string(state.world.factory_size()));
			log_to_console(state, parent, "?YFactory Locations?W: " + std::to_string(state.world.factory_location_size()));
		}
		if((v & uint8_t(flags::politics)) != 0) {
			log_to_console(state, parent, "?YProvince Ownerships?W: " + std::to_string(state.world.province_ownership_size()));
			log_to_console(state, parent, "?YProvince Controls?W: " + std::to_string(state.world.province_control_size()));
			log_to_console(state, parent, "?YProvince Rebel Controls?W: " + std::to_string(state.world.province_rebel_control_size()));
			log_to_console(state, parent, "?YOverlords?W: " + std::to_string(state.world.overlord_size()));
			log_to_console(state, parent, "?YRebel Factions?W: " + std::to_string(state.world.rebel_faction_size()));
			log_to_console(state, parent, "?YRebellions Within?W: " + std::to_string(state.world.rebellion_within_size()));
			log_to_console(state, parent, "?YMovements?W: " + std::to_string(state.world.movement_size()));
			log_to_console(state, parent, "?YMovements Within?W: " + std::to_string(state.world.movement_within_size()));
			log_to_console(state, parent, "?YPop Movement Memberships?W: " + std::to_string(state.world.pop_movement_membership_size()));
			log_to_console(state, parent, "?YPop Rebellion Memberships?W: " + std::to_string(state.world.pop_rebellion_membership_size()));
		}
		if((v & uint8_t(flags::demographics)) != 0) {
			log_to_console(state, parent, "?YPops?W: " + std::to_string(state.world.pop_size()));
			log_to_console(state, parent, "?YPop Locations?W: " + std::to_string(state.world.pop_location_size()));
		}
		if((v & uint8_t(flags::events)) != 0) {
			log_to_console(state, parent, "?YNational Events?W: " + std::to_string(state.world.national_event_size()));
			log_to_console(state, parent, "?YProvincial Events?W: " + std::to_string(state.world.provincial_event_size()));
			log_to_console(state, parent, "?YFree National Events?W: " + std::to_string(state.world.free_national_event_size()));
			log_to_console(state, parent, "?YFree Provincial Events?W: " + std::to_string(state.world.free_provincial_event_size()));
			log_to_console(state, parent, "?YNational Focuses?W: " + std::to_string(state.world.national_focus_size()));
			log_to_console(state, parent, "?YDecisions?W: " + std::to_string(state.world.decision_size()));
		}
	} break;
	case command_info::type::diplomacy_points:
	{
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
			auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
			command::c_change_diplo_points(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
		} else {
			command::c_change_diplo_points(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{ });
		}
		break;
	}
	case command_info::type::research_points:
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
			auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
			command::c_change_research_points(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
		} else {
			command::c_change_research_points(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{});
		}
		break;
	case command_info::type::money: {
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
			auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
			command::c_change_money(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
		} else {
			command::c_change_money(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{ });
		}
	} break;
	case command_info::type::infamy:
	if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
		auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
		auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
		command::c_change_infamy(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
	} else {
		command::c_change_infamy(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{});
	}
		
	break;
	case command_info::type::cb_progress:
	if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
		auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
		auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
		command::c_change_cb_progress(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
	} else {
		command::c_change_cb_progress(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{});
	}
	break;
	case command_info::type::westernize:
	{
		command::c_westernize(state, state.local_player_nation);
	}
	break;
	case command_info::type::unwesternize:
	{
		command::c_unwesternize(state, state.local_player_nation);
	}
	break;
	case command_info::type::crisis:
	{
		command::c_force_crisis(state, state.local_player_nation);
	}
	break;
	case command_info::type::end_game:
	{
		command::c_end_game(state, state.local_player_nation);
	}
	break;
	case command_info::type::event:
	{
		dcon::national_identity_id nid = state.world.nation_get_identity_from_identity_holder(state.local_player_nation);
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto tag = std::get<std::string>(pstate.arg_slots[1]);
			nid = smart_get_national_identity_from_tag(state, parent, tag);
		}
		if(nid) {
			command::c_event_as(state, state.local_player_nation, state.world.national_identity_get_nation_from_identity_holder(nid), std::get<int32_t>(pstate.arg_slots[0]));
		} else {
			command::c_event(state, state.local_player_nation, std::get<int32_t>(pstate.arg_slots[0]));
		}
	}
	break;
	case command_info::type::militancy:
	command::c_change_national_militancy(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])));
	break;
	case command_info::type::prestige:
	if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
		auto nid = smart_get_national_identity_from_tag(state, parent, std::get<std::string>(pstate.arg_slots[1]));
		auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
		command::c_change_prestige(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), n);
	} else {
		command::c_change_prestige(state, state.local_player_nation, float(std::get<int32_t>(pstate.arg_slots[0])), dcon::nation_id{});
	}
		
	break;
	case command_info::type::force_ally:
	{
		dcon::national_identity_id nid = state.world.nation_get_identity_from_identity_holder(state.local_player_nation);
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto tag = std::get<std::string>(pstate.arg_slots[1]);
			nid = smart_get_national_identity_from_tag(state, parent, tag);
			command::c_force_ally(state, state.local_player_nation, state.world.national_identity_get_nation_from_identity_holder(nid));
		}
	}
	break;
	case command_info::type::dump_event_graph:
	{
		struct graph_event_option {
			std::variant<
			dcon::national_event_id,
			dcon::free_national_event_id,
			dcon::provincial_event_id,
			dcon::free_provincial_event_id
			> parent;
			uint8_t index = 0;
		};
		using graph_node_data = std::variant<
		dcon::national_event_id,
		dcon::free_national_event_id,
		dcon::provincial_event_id,
		dcon::free_provincial_event_id,
		dcon::decision_id,
		dcon::cb_type_id,
		dcon::rebel_type_id,
		dcon::issue_option_id,
		graph_event_option
		>;
		struct graph_node {
			std::string name;
			graph_node_data data;
			dcon::effect_key e;
			uint32_t ref_count;
		};
		std::vector<graph_node> nodes;
		for(const auto e : state.world.in_national_event) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ name, graph_node_data(e.id), e.get_immediate_effect(), 0 });
			auto const& opt = e.get_options();
			for(uint8_t i = 0; i < uint8_t(opt.size()); i++) {
				auto const opt_name = text::produce_simple_string(state, opt[i].name);
				nodes.push_back(graph_node{ opt_name, graph_node_data(graph_event_option{ e.id, i }), opt[i].effect, 0 });
			}
		}
		for(const auto e : state.world.in_provincial_event) {
			auto const name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ name, graph_node_data(e.id), e.get_immediate_effect(), 0 });
			auto const& opt = e.get_options();
			for(uint8_t i = 0; i < uint8_t(opt.size()); i++) {
				auto const opt_name = text::produce_simple_string(state, opt[i].name);
				nodes.push_back(graph_node{ opt_name, graph_node_data(graph_event_option{ e.id, i }), opt[i].effect, 0 });
			}
		}
		for(const auto e : state.world.in_free_national_event) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ name, graph_node_data(e.id), e.get_immediate_effect(), 0 });
			auto const& opt = e.get_options();
			for(uint8_t i = 0; i < uint8_t(opt.size()); i++) {
				auto const opt_name = text::produce_simple_string(state, opt[i].name);
				nodes.push_back(graph_node{ opt_name, graph_node_data(graph_event_option{ e.id, i }), opt[i].effect, 0 });
			}
		}
		for(const auto e : state.world.in_free_provincial_event) {
			auto const name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ name, graph_node_data(e.id), e.get_immediate_effect(), 0 });
			auto const& opt = e.get_options();
			for(uint8_t i = 0; i < uint8_t(opt.size()); i++) {
				auto const opt_name = text::produce_simple_string(state, opt[i].name);
				nodes.push_back(graph_node{ opt_name, graph_node_data(graph_event_option{ e.id, i }), opt[i].effect, 0 });
			}
		}
		for(const auto e : state.world.in_decision) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ name, graph_node_data(e.id), e.get_effect(), 0 });
		}
		for(const auto e : state.world.in_cb_type) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ "(add) " + name, graph_node_data(e.id), e.get_on_add(), 0 });
			nodes.push_back(graph_node{ "(accept) " + name, graph_node_data(e.id), e.get_on_po_accepted(), 0 });
		}
		for(const auto e : state.world.in_rebel_type) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ "(siege) " + name, graph_node_data(e.id), e.get_siege_won_effect(), 0 });
			nodes.push_back(graph_node{ "(demands) " + name, graph_node_data(e.id), e.get_demands_enforced_effect(), 0 });
		}
		for(const auto e : state.world.in_issue_option) {
			auto name = text::produce_simple_string(state, e.get_name());
			nodes.push_back(graph_node{ "(execute) " + name, graph_node_data(e.id), e.get_on_execute_effect(), 0 });
		}
		for(uint32_t i = 0; i < uint32_t(nodes.size()); i++) {
			auto& node = nodes[i];
			for(auto& c : node.name) {
				if(c == '\\' || c == '"')
				c = '\'';
			}
		}

		std::string out_text = "digraph {\n";
			for(uint32_t i = 0; i < uint32_t(nodes.size()); i++) {
				const auto& node = nodes[i];
				uint16_t* efd = state.effect_data.data() + state.effect_data_indices[node.e.index() + 1];
				effect::recurse_over_effects(efd, [&](uint16_t* tval) {
					if((tval[0] & effect::code_mask) == effect::country_event_immediate_province_this_nation
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_province_this_pop
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_province_this_province
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_province_this_state
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_this_nation
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_this_pop
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_this_province
					|| (tval[0] & effect::code_mask) == effect::country_event_immediate_this_state
					|| (tval[0] & effect::code_mask) == effect::country_event_province_this_nation
					|| (tval[0] & effect::code_mask) == effect::country_event_province_this_pop
					|| (tval[0] & effect::code_mask) == effect::country_event_province_this_province
					|| (tval[0] & effect::code_mask) == effect::country_event_province_this_state
					|| (tval[0] & effect::code_mask) == effect::country_event_this_nation
					|| (tval[0] & effect::code_mask) == effect::country_event_this_pop
					|| (tval[0] & effect::code_mask) == effect::country_event_this_province
					|| (tval[0] & effect::code_mask) == effect::country_event_this_state) {
						auto ev = trigger::payload(tval[1]).nev_id;
						for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
							if(std::holds_alternative<dcon::national_event_id>(nodes[j].data)
							&& std::get<dcon::national_event_id>(nodes[j].data) == ev) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
								break;
							}
						}
						//province event
					} else if((tval[0] & effect::code_mask) == effect::province_event_immediate_this_nation
					|| (tval[0] & effect::code_mask) == effect::province_event_immediate_this_pop
					|| (tval[0] & effect::code_mask) == effect::province_event_immediate_this_province
					|| (tval[0] & effect::code_mask) == effect::province_event_immediate_this_state
					|| (tval[0] & effect::code_mask) == effect::province_event_this_nation
					|| (tval[0] & effect::code_mask) == effect::province_event_this_pop
					|| (tval[0] & effect::code_mask) == effect::province_event_this_province
					|| (tval[0] & effect::code_mask) == effect::province_event_this_state) {
						auto ev = trigger::payload(tval[1]).pev_id;
						for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
							if(std::holds_alternative<dcon::provincial_event_id>(nodes[j].data)
							&& std::get<dcon::provincial_event_id>(nodes[j].data) == ev) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
								break;
							}
						}
					}
				});
			}
			for(uint32_t i = 0; i < uint32_t(nodes.size()); i++) {
				const auto& d1 = nodes[i].data;
				if(std::holds_alternative<dcon::national_event_id>(d1)) {
					auto id = std::get<dcon::national_event_id>(d1);
					for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
						const auto& d2 = nodes[j].data;
						if(nodes[j].ref_count > 0 && std::holds_alternative<graph_event_option>(d2)) {
							auto geo = std::get<graph_event_option>(d2);
							if(std::holds_alternative<dcon::national_event_id>(geo.parent)
							&& std::get<dcon::national_event_id>(geo.parent) == id) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
							}
						}
					}
				} else if(std::holds_alternative<dcon::free_national_event_id>(d1)) {
					auto id = std::get<dcon::free_national_event_id>(d1);
					for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
						const auto& d2 = nodes[j].data;
						if(nodes[j].ref_count > 0 && std::holds_alternative<graph_event_option>(d2)) {
							auto geo = std::get<graph_event_option>(d2);
							if(std::holds_alternative<dcon::free_national_event_id>(geo.parent)
							&& std::get<dcon::free_national_event_id>(geo.parent) == id) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
							}
						}
					}
				} else if(std::holds_alternative<dcon::provincial_event_id>(d1)) {
					auto id = std::get<dcon::provincial_event_id>(d1);
					for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
						const auto& d2 = nodes[j].data;
						if(nodes[j].ref_count > 0 && std::holds_alternative<graph_event_option>(d2)) {
							auto geo = std::get<graph_event_option>(d2);
							if(std::holds_alternative<dcon::provincial_event_id>(geo.parent)
							&& std::get<dcon::provincial_event_id>(geo.parent) == id) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
							}
						}
					}
				} else if(std::holds_alternative<dcon::free_provincial_event_id>(d1)) {
					auto id = std::get<dcon::free_provincial_event_id>(d1);
					for(uint32_t j = 0; j < uint32_t(nodes.size()); j++) {
						const auto& d2 = nodes[j].data;
						if(nodes[j].ref_count > 0 && std::holds_alternative<graph_event_option>(d2)) {
							auto geo = std::get<graph_event_option>(d2);
							if(std::holds_alternative<dcon::free_provincial_event_id>(geo.parent)
							&& std::get<dcon::free_provincial_event_id>(geo.parent) == id) {
								nodes[i].ref_count++;
								nodes[j].ref_count++;
								out_text += "A_" + std::to_string(i) + " -> A_" + std::to_string(j) + ";\n";
							}
						}
					}
				}
			}
			for(uint32_t i = 0; i < uint32_t(nodes.size()); i++) {
				const auto& node = nodes[i];
				if(node.ref_count > 0) {
					const auto& d = node.data;
					if(std::holds_alternative<dcon::national_event_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=crimson, shape=box];\n";
					} else if(std::holds_alternative<dcon::free_national_event_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=lightcoral, shape=diamond];\n";
					} else if(std::holds_alternative<dcon::provincial_event_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=royalblue2, shape=box];\n";
					} else if(std::holds_alternative<dcon::free_provincial_event_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=deepskyblue, shape=diamond];\n";
					} else if(std::holds_alternative<dcon::decision_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=darkseagreen1, shape=trapezium];\n";
					} else if(std::holds_alternative<graph_event_option>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=mediumturquoise];\n";
					} else if(std::holds_alternative<dcon::cb_type_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=lemonchiffon1, shape=diamond];\n";
					} else if(std::holds_alternative<dcon::rebel_type_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=lightsalmon2, shape=diamond];\n";
					} else if(std::holds_alternative<dcon::issue_option_id>(d)) {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=lightgoldenrodyellow, shape=diamond];\n";
					} else {
						out_text += "A_" + std::to_string(i) + " [label=\"" + node.name + "\", style=\"filled\", fillcolor=yellow];\n";
					}
				}
			}
		out_text += "}\n";
		auto sdir = simple_fs::get_or_create_oos_directory();
		simple_fs::write_file(sdir, NATIVE("graph.txt"), out_text.c_str(), uint32_t(out_text.size()));
	}
	break;
	case command_info::type::dump_out_of_sync:
	{
		window::change_cursor(state, window::cursor_type::busy);
		state.debug_save_oos_dump();
		state.debug_scenario_oos_dump();
		state.debug_unsaved_oos_dump();
		log_to_console(state, parent, "Check \"My Documents\\Victoria Community's Engine\\oos\\\" for the OOS dump");
		window::change_cursor(state, window::cursor_type::normal);
		break;
	}
	case command_info::type::toggle_ai:
	{
		auto tag = std::get<std::string>(pstate.arg_slots[0]);
		if(auto nid = smart_get_national_identity_from_tag(state, parent, tag); nid) {
			auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
			if(state.world.nation_get_is_player_controlled(n)) {
				log_to_console(state, parent, "@(T) AI");
			} else {
				log_to_console(state, parent, "@(F) AI");
			}
			command::c_toggle_ai(state, state.local_player_nation, n);
		}
		break;
	}
	case command_info::type::always_allow_wargoals:
	{
		log_to_console(state, parent, !state.cheat_data.always_allow_wargoals ? "@(T)" : "@(F)");
		command::c_always_allow_wargoals(state, state.local_player_nation);
		break;
	}
	case command_info::type::always_allow_reforms:
	{
		log_to_console(state, parent, !state.cheat_data.always_allow_reforms ? "@(T)" : "@(F)");
		command::c_always_allow_reforms(state, state.local_player_nation);
		break;
	}
	case command_info::type::always_allow_decisions:
	{
		log_to_console(state, parent, !state.cheat_data.always_allow_decisions ? "@(T)" : "@(F)");
		command::c_always_allow_decisions(state, state.local_player_nation);
		break;
	}
	case command_info::type::always_potential_decisions:
	{
		log_to_console(state, parent, !state.cheat_data.always_potential_decisions ? "@(T)" : "@(F)");
		command::c_always_potential_decisions(state, state.local_player_nation);
		break;
	}
	case command_info::type::always_accept_deals:
	{
		log_to_console(state, parent, !state.cheat_data.always_accept_deals ? "@(T)" : "@(F)");
		command::c_always_accept_deals(state, state.local_player_nation);
		break;
	}
	case command_info::type::set_auto_choice_all:
	{
		command::c_set_auto_choice_all(state, state.local_player_nation);
		break;
	}
	case command_info::type::clear_auto_choice_all:
	{
		command::c_clear_auto_choice_all(state, state.local_player_nation);
		break;
	}
	case command_info::type::complete_constructions:
	{
		command::c_complete_constructions(state, state.local_player_nation);
		break;
	}
	case command_info::type::instant_research:
	{
		auto has_us = false;
		for(const auto n : state.cheat_data.instant_research_nations)
		if(n == state.local_player_nation) {
			has_us = true;
			break;
		}
		log_to_console(state, parent, !has_us ? "@(T)" : "@(F)");
		command::c_instant_research(state, state.local_player_nation);
		break;
	}
	case command_info::type::spectate:
	{
		command::c_switch_nation(state, state.local_player_nation, state.national_definitions.rebel_id);
		break;
	}
	case command_info::type::conquer_tag:
	{
		auto tag = std::get<std::string>(pstate.arg_slots[0]);
		if(tag == "ALL") {
			for(const auto p : state.world.in_province) {
				command::c_change_owner(state, state.local_player_nation, p, state.local_player_nation);
			}
		} else {
			auto nid = smart_get_national_identity_from_tag(state, parent, tag);
			if(nid) {
				auto n = state.world.national_identity_get_nation_from_identity_holder(nid);
				for(const auto po : state.world.in_province_ownership) {
					if(po.get_nation() == n)
					command::c_change_owner(state, state.local_player_nation, po.get_province(), state.local_player_nation);
				}
			}
		}
		break;
	}
	case command_info::type::toggle_core:
	{
		auto province_id = dcon::province_id((uint16_t)std::get<std::int32_t>(pstate.arg_slots[0]));
		auto nid = state.world.nation_get_identity_from_identity_holder(state.local_player_nation);
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto tag = std::get<std::string>(pstate.arg_slots[1]);
			nid = smart_get_national_identity_from_tag(state, parent, tag);
		}
		command::c_toggle_core(state, state.local_player_nation, province_id, state.world.national_identity_get_nation_from_identity_holder(nid));
		break;
	}
	case command_info::type::change_owner:
	{
		auto province_id = dcon::province_id((uint16_t)std::get<std::int32_t>(pstate.arg_slots[0]));
		auto nid = state.world.nation_get_identity_from_identity_holder(state.local_player_nation);
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto tag = std::get<std::string>(pstate.arg_slots[1]);
			nid = smart_get_national_identity_from_tag(state, parent, tag);
		}
		command::c_change_owner(state, state.local_player_nation, province_id, state.world.national_identity_get_nation_from_identity_holder(nid));
		break;
	}
	case command_info::type::change_control:
	{
		auto province_id = dcon::province_id((uint16_t)std::get<std::int32_t>(pstate.arg_slots[0]));
		auto nid = state.world.nation_get_identity_from_identity_holder(state.local_player_nation);
		if(std::holds_alternative<std::string>(pstate.arg_slots[1])) {
			auto tag = std::get<std::string>(pstate.arg_slots[1]);
			nid = smart_get_national_identity_from_tag(state, parent, tag);
		}
		command::c_change_controller(state, state.local_player_nation, province_id, state.world.national_identity_get_nation_from_identity_holder(nid));
		break;
	}
	case command_info::type::province_id_tooltip:
	{
		state.cheat_data.show_province_id_tooltip = not state.cheat_data.show_province_id_tooltip;
		log_to_console(state, parent, state.cheat_data.show_province_id_tooltip ? "✔" : "✘");
		break;
	}
	case command_info::type::add_population:
	{
		auto ammount = std::get<std::int32_t>(pstate.arg_slots[0]);
		command::c_add_population(state, state.local_player_nation, ammount);
		break;
	}
	case command_info::type::instant_construction:
	{
		log_to_console(state, parent, !state.cheat_data.instant_army ? "@(T)" : "@(F)");
		command::c_instant_army(state, state.local_player_nation);
		log_to_console(state, parent, !state.cheat_data.instant_navy ? "@(T)" : "@(F)");
		command::c_instant_navy(state, state.local_player_nation);
		log_to_console(state, parent, !state.cheat_data.instant_industry ? "@(T)" : "@(F)");
		command::c_instant_industry(state, state.local_player_nation);
		break;
	}
	case command_info::type::add_year:
	{
		auto years = std::get<std::int32_t>(pstate.arg_slots[0]);
		command::c_add_year(state, state.local_player_nation, years);
		break;
	}
	case command_info::type::daily_oos_check:
	{
		state.cheat_data.daily_oos_check = not state.cheat_data.daily_oos_check;
		log_to_console(state, parent, state.cheat_data.daily_oos_check ? "✔" : "✘");
		break;
	}
	case command_info::type::dump_map:
	{
		bool opt_sea_lines = true;
		bool opt_province_lines = true;
		bool opt_blend = true;
		if(!std::holds_alternative<std::string>(pstate.arg_slots[0])) {
			log_to_console(state, parent, "Valid options: nosealine, noblend, nosealine2, blendnosea, vanilla");
			log_to_console(state, parent, "Ex: \"dmap nosealine2\"");
			break;
		}
		auto type = std::get<std::string>(pstate.arg_slots[0]);
		if(type == "nosealine") {
			opt_sea_lines = false;
			opt_province_lines = false;
		} else if(type == "noblend") {
			opt_blend = false;
		} else if(type == "nosealine2") {
			opt_sea_lines = false;
		} else if(type == "blendnosea") {
			opt_sea_lines = false;
			opt_blend = false;
		} else if(type == "vanilla") {
			opt_sea_lines = false;
			opt_province_lines = false;
			opt_blend = false;
		}

		auto total_px = state.map_state.map_data.size_x * state.map_state.map_data.size_y;
		auto buffer = std::unique_ptr<uint8_t[]>(new uint8_t[total_px * 3]);
		auto blend_fn = [&](uint32_t idx, bool sea_a, bool sea_b, dcon::province_id pa, dcon::province_id pb) {
			if(sea_a != sea_b) {
				buffer[idx * 3 + 0] = 0;
				buffer[idx * 3 + 1] = 0;
				buffer[idx * 3 + 2] = 0;
			}
			if(pa != pb) {
				if(((sea_a || sea_b) && opt_sea_lines)
				|| sea_a != sea_b
				|| (opt_province_lines && !sea_a && !sea_b)) {
					if(opt_blend) {
						buffer[idx * 3 + 0] &= 0x7f;
						buffer[idx * 3 + 1] &= 0x7f;
						buffer[idx * 3 + 2] &= 0x7f;
					} else {
						buffer[idx * 3 + 0] = 0;
						buffer[idx * 3 + 1] = 0;
						buffer[idx * 3 + 2] = 0;
					}
				}
			}
		};
		for(uint32_t y = 0; y < uint32_t(state.map_state.map_data.size_y); y++) {
			for(uint32_t x = 0; x < uint32_t(state.map_state.map_data.size_x); x++) {
				auto idx = y * uint32_t(state.map_state.map_data.size_x) + x;
				auto p = province::from_map_id(state.map_state.map_data.province_id_map[idx]);
				bool p_is_sea = state.map_state.map_data.province_id_map[idx] >= province::to_map_id(state.province_definitions.first_sea_province);
				if(p_is_sea) {
					buffer[idx * 3 + 0] = 128;
					buffer[idx * 3 + 1] = 128;
					buffer[idx * 3 + 2] = 255;
				} else {
					auto owner = state.world.province_get_nation_from_province_ownership(p);
					if(owner) {
						auto owner_color = state.world.nation_get_color(owner);
						buffer[idx * 3 + 0] = uint8_t(owner_color & 0xff);
						buffer[idx * 3 + 1] = uint8_t((owner_color >> 8) & 0xff) & 0xff;
						buffer[idx * 3 + 2] = uint8_t((owner_color >> 16) & 0xff) & 0xff;
					} else {
						buffer[idx * 3 + 0] = 170;
						buffer[idx * 3 + 1] = 170;
						buffer[idx * 3 + 2] = 170;
					}
				}
				if(x < uint32_t(state.map_state.map_data.size_x - 1)) {
					auto br_idx = idx + uint32_t(state.map_state.map_data.size_x);
					if(br_idx < total_px) {
						auto br_p = province::from_map_id(state.map_state.map_data.province_id_map[br_idx]);
						bool br_is_sea = state.map_state.map_data.province_id_map[br_idx] >= province::to_map_id(state.province_definitions.first_sea_province);
						blend_fn(idx, br_is_sea, p_is_sea, br_p, p);
					}
					auto rs_idx = idx + 1;
					if(rs_idx < total_px) {
						auto br_p = province::from_map_id(state.map_state.map_data.province_id_map[rs_idx]);
						bool br_is_sea = state.map_state.map_data.province_id_map[rs_idx] >= province::to_map_id(state.province_definitions.first_sea_province);
						blend_fn(idx, br_is_sea, p_is_sea, br_p, p);
					}
				}
			}
		}
		stbi_flip_vertically_on_write(true);
		auto func = [](void*, void* ptr_in, int size) -> void {
			auto sdir = simple_fs::get_or_create_oos_directory();
			simple_fs::write_file(sdir, NATIVE("map.png"), static_cast<const char*>(ptr_in), uint32_t(size));
		};
		stbi_write_png_to_func(func, nullptr, int(state.map_state.map_data.size_x), int(state.map_state.map_data.size_y), 3, buffer.get(), 0);
		break;
	}
	case command_info::type::list_all_flags:
	{
		log_to_console(state, parent, std::string("-------------------------------"));
		log_to_console(state, parent, text::produce_simple_string(state, "national_variables"));
		for(int32_t i = 0; i < state.national_definitions.num_allocated_national_variables; i++) {
			auto nv = dcon::national_variable_id(dcon::national_variable_id::value_base_t(i));
			auto v = state.world.nation_get_variables(state.local_player_nation, nv);
			if(v != 0.f)
				log_to_console(state, parent, text::produce_simple_string(state, state.national_definitions.variable_names[nv]) + ": " + text::format_float(v, 4));
		}
		log_to_console(state, parent, std::string("-------------------------------"));
		log_to_console(state, parent, text::produce_simple_string(state, "national_flags"));
		for(int32_t i = 0; i < state.national_definitions.num_allocated_national_flags; i++) {
			auto nv = dcon::national_flag_id(dcon::national_flag_id::value_base_t(i));
			if(state.world.nation_get_flag_variables(state.local_player_nation, nv))
				log_to_console(state, parent, text::produce_simple_string(state, state.national_definitions.flag_variable_names[nv]));
		}
		log_to_console(state, parent, std::string("-------------------------------"));
		log_to_console(state, parent, text::produce_simple_string(state, "global_flags"));
		for(int32_t i = 0; i < state.national_definitions.num_allocated_global_flags; i++) {
			auto nv = dcon::global_flag_id(dcon::global_flag_id::value_base_t(i));
			if(state.national_definitions.is_global_flag_variable_set(nv))
				log_to_console(state, parent, text::produce_simple_string(state, state.national_definitions.global_flag_variable_names[nv]));
		}
	} break;
	case command_info::type::innovate: {
		auto searched_name = std::get<std::string>(pstate.arg_slots[0]);
		std::replace(searched_name.begin(), searched_name.end(), '_', ' ');
		bool found = false;
		for(auto invention : state.world.in_invention) {
			auto innovation_name = text::produce_simple_string(state, invention.get_name());
			std::transform(innovation_name.begin(), innovation_name.end(), innovation_name.begin(), [](unsigned char c) { return (char)std::tolower(c); });

			if(searched_name == innovation_name) {
				command::c_innovate(state, state.local_player_nation, invention);
				found = true;
				break;
			}
		}
		if(!found) {
			log_to_console(state, parent, "Couldn't find innovation: " + searched_name);
		}
	} break;
	case command_info::type::none:
		log_to_console(state, parent, "Command \"" + std::string(s) + "\" not found.");
		break;
	default:
		break;
	}
	log_to_console(state, parent, ""); // space after command
	add_to_history(state, std::string(s));

	Cyto::Any payload = this;
	impl_get(state, payload);
	edit_box_update(state, s);
}

void ui::console_edit::edit_box_esc(sys::state& state) noexcept {
	ui::console_window::show_toggle(state);
}
void ui::console_edit::edit_box_backtick(sys::state& state) noexcept {
	ui::console_window::show_toggle(state);
}
void ui::console_edit::edit_box_back_slash(sys::state& state) noexcept {
	ui::console_window::show_toggle(state);
}

void ui::console_window::show_toggle(sys::state& state) {
	if(!state.ui_state.console_window) {
		auto win = ui::make_element_by_type<ui::console_window>(state, "vce_console_window");
		state.ui_state.console_window = win.get();
		state.ui_state.root->add_child_to_front(std::move(win));
	}
	if(state.ui_state.console_window->is_visible()) { //close
		sound::play_interface_sound(state, sound::get_console_close_sound(state), state.user_settings.master_volume * state.user_settings.interface_volume);
	} else { //open
		sound::play_interface_sound(state, sound::get_console_open_sound(state), state.user_settings.master_volume * state.user_settings.interface_volume);
	}

	state.ui_state.console_window->set_visible(state, !state.ui_state.console_window->is_visible());
	if(state.ui_state.console_window->is_visible())
		state.ui_state.root->move_child_to_front(state.ui_state.console_window);
}

void ui::console_list::on_update(sys::state& state) noexcept {
	auto contents = text::create_endless_layout(state, delegate->internal_layout,
	text::layout_parameters{ 0, 0, int16_t(base_data.size.x), int16_t(base_data.size.y),
		base_data.data.text.font_handle, 0, text::alignment::left,
	text::is_black_from_font_id(base_data.data.text.font_handle) ? text::text_color::black : text::text_color::white, false });
	auto box = text::open_layout_box(contents);
	text::add_unparsed_text_to_layout_box(state, contents, box, raw_text);
	text::close_layout_box(contents, box);
	calibrate_scrollbar(state);
}
