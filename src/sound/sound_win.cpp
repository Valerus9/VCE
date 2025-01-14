#include "system/system_state.hpp"
#include "sound.hpp"
#include "reports.hpp"

#include "Dshow.h"
#define WM_GRAPHNOTIFY (WM_APP + 1)

namespace sound {

	constexpr int32_t volume_function(float v) {
		return std::clamp(int32_t((v + -1.0f) * 4'500.0f), -10'000, 0);
	}

	audio_instance::~audio_instance() {
		if(audio_interface) {
			((IBasicAudio*)audio_interface)->Release();
			audio_interface = nullptr;
		}
		if(control_interface) {
			((IMediaControl*)control_interface)->Release();
			control_interface = nullptr;
		}
		if(seek_interface) {
			((IMediaSeeking*)seek_interface)->Release();
			seek_interface = nullptr;
		}
		if(event_interface) {
			((IMediaEventEx*)event_interface)->SetNotifyWindow(NULL, 0, NULL);
			((IMediaEventEx*)event_interface)->Release();
			event_interface = nullptr;
		}
		if(graph_interface) {
			((IGraphBuilder*)graph_interface)->Release();
			graph_interface = nullptr;
		}
	}

	void audio_instance::play(float volume, bool as_music, void* window_handle) {
		if(volume * volume_multiplier <= 0.0f || filename.size() == 0)
			return;

		if(!graph_interface) {
			// graph interface not built yet (first time playing)
			// so play
			IGraphBuilder* pGraph = NULL;
			HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
			if(FAILED(hr)) {
				reports::write_debug("failed to create graph builder\n");
				return;
			}
			hr = pGraph->RenderFile((wchar_t const*)(filename.c_str()), NULL);
			if(FAILED(hr)) {
				reports::write_debug("unable to play audio file\n");
				volume_multiplier = 0.0f;
				return;
			}
			IMediaControl* pControl = NULL;
			hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
			if(FAILED(hr)) {
				reports::write_debug("failed to get control interface\n");
				return;
			}
			if(as_music) {
				IMediaEventEx* pEvent = NULL;
				hr = pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent);
				if(FAILED(hr)) {
					reports::write_debug("failed to get event interface\n");
					return;
				}
				auto const res_b = pEvent->SetNotifyWindow((OAHWND)window_handle, WM_GRAPHNOTIFY, NULL);
				if(FAILED(res_b)) {
					reports::write_debug("failed to set notification window\n");
					return;
				}
				event_interface = pEvent;
			}
			IBasicAudio* pAudio = NULL;
			hr = pGraph->QueryInterface(IID_IBasicAudio, (void**)&pAudio);
			if(FAILED(hr)) {
				reports::write_debug("failed to get audio interface\n");
				return;
			}
			IMediaSeeking* pSeek = NULL;
			hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);
			if(FAILED(hr)) {
				reports::write_debug("failed to get seeking interface\n");
				return;
			}
			graph_interface = pGraph;
			control_interface = pControl;
			audio_interface = pAudio;
			seek_interface = pSeek;
		}
		HRESULT hr;
		if(audio_interface) {
			hr = audio_interface->put_Volume(volume_function(volume * volume_multiplier));
			if(FAILED(hr)) {
				reports::write_debug("failed to put_Volume\n");
			}
		}
		if(seek_interface) {
			LONGLONG new_position = 0;
			hr = seek_interface->SetPositions(&new_position, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
			if(FAILED(hr)) {
				reports::write_debug("failed to SetPositions\n");
			}
		}
		if(control_interface) {
			hr = control_interface->Run();
			if(FAILED(hr)) {
				reports::write_debug("failed to Run\n");
			}
		}
	}

	void audio_instance::pause() const {
		if(control_interface) {
			control_interface->Pause();
		}
	}
	void audio_instance::resume() const {
		if(control_interface) {
			control_interface->Run();
		}
	}
	void audio_instance::stop() const {
		if(control_interface) {
			control_interface->Pause();
		}
	}

	bool audio_instance::is_playing() const {
		if(seek_interface && volume_multiplier > 0.0f) {
			LONGLONG end_position = 0;
			LONGLONG current_position = 0;
			auto const result = seek_interface->GetPositions(&current_position, &end_position);
			return !(FAILED(result) || current_position >= end_position);
		}
		return false;
	}

	bool audio_instance::is_finished() const {
		if(event_interface) {
			LONG_PTR param1;
			LONG_PTR param2;
			long evCode;
			while(SUCCEEDED(event_interface->GetEvent(&evCode, &param1, &param2, 0))) {
				event_interface->FreeEventParams(evCode, param1, param2);
				switch(evCode) {
				case EC_COMPLETE: //Fall through.
				case EC_USERABORT: //Fall through.
					return true;
				default:;
					// nothing
				}
			}
		}
		return false;
	}

	void audio_instance::change_volume(float new_volume) const {
		if(new_volume * volume_multiplier > 0.0f) {
			if(audio_interface) {
				audio_interface->put_Volume(volume_function(new_volume * volume_multiplier));
			}
		} else {
			if(control_interface) {
				control_interface->Pause();
			}
		}
	}

	void sound_impl::play_new_track(sys::state& ws) {
		if(music_list.size() > 0) {
			int32_t result = int32_t((last_music + 1) % music_list.size());
			play_music(result, ws.user_settings.master_volume * ws.user_settings.music_volume);
		}
	}
	void sound_impl::play_next_track(sys::state& ws) {
		if(music_list.size() > 0) {
			int32_t result = int32_t((last_music + 1) % music_list.size());
			play_music(result, ws.user_settings.master_volume * ws.user_settings.music_volume);
		}
	}
	void sound_impl::play_previous_track(sys::state& ws) {
		if(music_list.size() > 0) {
			int32_t result = int32_t((last_music - 1) % music_list.size());
			play_music(result, ws.user_settings.master_volume * ws.user_settings.music_volume);
		}
	}

	bool sound_impl::music_finished() const {
		if(last_music != -1) {
			return music_list[last_music].is_finished();
		}
		return false;
	}

	void sound_impl::play_effect(audio_instance& s, float volume) {
		if(!global_pause) {
			if(!current_effect || current_effect->is_playing() == false) {
				current_effect = &s;
				s.play(volume, false, window_handle);
			}
		}
	}

	void sound_impl::play_interface_sound(audio_instance& s, float volume) {
		if(!global_pause) {
			if(current_interface_sound) {
				current_interface_sound->stop();
			}
			current_interface_sound = &s;
			s.play(volume, false, window_handle);
		}
	}

	void sound_impl::play_music(int32_t track, float volume) {
		if(global_pause)
		return;

		auto const lm = last_music;
		if(lm != -1)
		music_list[lm].stop();
		last_music = track;
		if(track != -1)
		music_list[track].play(volume, true, window_handle);
	}

	void sound_impl::change_effect_volume(float v) const {
		if(current_effect)
		current_effect->change_volume(v);
	}

	void sound_impl::change_interface_volume(float v) const {
		if(current_interface_sound)
		current_interface_sound->change_volume(v);
	}

	void sound_impl::change_music_volume(float v) const {
		auto const lm = last_music;
		if(lm != -1) {
			music_list[lm].change_volume(v);
		}
	}

	void sound_impl::pause_effect() const {
		if(current_effect)
		current_effect->pause();
	}
	void sound_impl::pause_interface_sound() const {
		if(current_interface_sound)
		current_interface_sound->pause();
	}
	void sound_impl::pause_music() const {
		auto const lm = last_music;
		if(lm != -1) {
			music_list[lm].pause();
		}
	}

	void sound_impl::resume_effect() const {
		if(current_effect)
		current_effect->resume();
	}
	void sound_impl::resume_interface_sound() const {
		if(current_interface_sound)
		current_interface_sound->resume();
	}
	void sound_impl::resume_music() const {
		auto const lm = last_music;
		if(lm != -1) {
			music_list[lm].resume();
		}
	}

	// called on startup and shutdown -- initialize should also load the list of available music files and load sound effects
	void initialize_sound_system(sys::state& state) {
		reports::write_debug("Initializing sound system\n");

		state.sound_ptr = std::make_unique<sound_impl>();
		state.sound_ptr->window_handle = state.win_ptr->hwnd;

		auto root_dir = simple_fs::get_root(state.common_fs);
		auto const music_dir = simple_fs::open_directory(root_dir, NATIVE("music"));
		for(auto const& mp3_file : simple_fs::list_files(music_dir, NATIVE(".mp3"))) {
			auto file_name = simple_fs::get_full_name(mp3_file);
			state.sound_ptr->music_list.emplace_back(file_name);
			if(parsers::native_has_fixed_suffix_ci(file_name.c_str(), file_name.c_str() + file_name.length(), NATIVE("thecoronation_titletheme.mp3")))
				state.sound_ptr->first_music = int32_t(state.sound_ptr->music_list.size()) - 1;
		}
		for(auto const& music_subdir : simple_fs::list_subdirectories(music_dir)) {
			for(auto const& mp3_file : simple_fs::list_files(music_subdir, NATIVE(".mp3"))) {
				auto file_name = simple_fs::get_full_name(mp3_file);
				state.sound_ptr->music_list.emplace_back(file_name);
			}
		}
		struct {
			audio_instance* audio;
			native_string_view name;
		} sound_table[] = {
			//{ &state.sound_ptr->click_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->technology_finished_sound, NATIVE("UI_TechnologyFinished.wav") },
			{ &state.sound_ptr->army_move_sound, NATIVE("GI_InfantryMove.wav") },
			{ &state.sound_ptr->army_select_sound, NATIVE("GI_InfantrySelected.wav") },
			{ &state.sound_ptr->navy_move_sound, NATIVE("UI_SailMove.wav") },
			{ &state.sound_ptr->navy_select_sound, NATIVE("UI_SailSelected.wav") },
			{ &state.sound_ptr->declaration_of_war_sound, NATIVE("DeclarationofWar.wav") },
			{ &state.sound_ptr->chat_message_sound, NATIVE("GI_ChatMessage.wav") },
			{ &state.sound_ptr->error_sound, NATIVE("GI_ErrorBlip.wav") },
			{ &state.sound_ptr->peace_sound, NATIVE("Misc_Peace.wav") },
			{ &state.sound_ptr->army_built_sound, NATIVE("UI_LandUnitFinished.wav") },
			{ &state.sound_ptr->navy_built_sound, NATIVE("UI_NavalUnitFinished.wav") },
			{ &state.sound_ptr->factory_built_sound, NATIVE("Misc_NewFactory.wav") },
			{ &state.sound_ptr->revolt_sound, NATIVE("Misc_revolt.wav") },
			{ &state.sound_ptr->fort_built_sound, NATIVE("Misc_Fortification.wav") },
			{ &state.sound_ptr->railroad_built_sound, NATIVE("Misc_Infrastructure.wav") },
			{ &state.sound_ptr->naval_base_built_sound, NATIVE("Misc_CoalingStation.wav") },
			{ &state.sound_ptr->minor_event_sound, NATIVE("GI_MinorBlip.wav") },
			{ &state.sound_ptr->major_event_sound, NATIVE("Misc_Attention.wav") },
			{ &state.sound_ptr->decline_sound, NATIVE("GI_FailureBlip.wav") },
			{ &state.sound_ptr->accept_sound, NATIVE("GI_SuccessBlip.wav") },
			{ &state.sound_ptr->diplomatic_request_sound, NATIVE("GI_MessageWindow.wav") },
			{ &state.sound_ptr->election_sound, NATIVE("Misc_ElectionHeld.wav") },
			{ &state.sound_ptr->land_battle_sounds[0], NATIVE("Combat_Cavalry_1.wav") },
			{ &state.sound_ptr->land_battle_sounds[1], NATIVE("Combat_Cavalry_2.wav") },
			{ &state.sound_ptr->land_battle_sounds[2], NATIVE("Combat_Cavalry_3.wav") },
			{ &state.sound_ptr->land_battle_sounds[3], NATIVE("Combat_Infantry_1.wav") },
			{ &state.sound_ptr->land_battle_sounds[4], NATIVE("Combat_Infantry_2.wav") },
			{ &state.sound_ptr->land_battle_sounds[5], NATIVE("Combat_Infantry_3.wav") },
			{ &state.sound_ptr->naval_battle_sounds[0], NATIVE("Combat_MajorShip_1.wav") },
			{ &state.sound_ptr->naval_battle_sounds[1], NATIVE("Combat_MajorShip_2.wav") },
			{ &state.sound_ptr->naval_battle_sounds[2], NATIVE("Combat_MajorShip_3.wav") },
			{ &state.sound_ptr->naval_battle_sounds[3], NATIVE("Combat_MinorShip_1.wav") },
			{ &state.sound_ptr->naval_battle_sounds[4], NATIVE("Combat_MinorShip_2.wav") },
			{ &state.sound_ptr->naval_battle_sounds[5], NATIVE("Combat_MinorShip_3.wav") },
			{ &state.sound_ptr->click_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->click_left_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->click_right_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->console_open_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->console_close_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_budget_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->hover_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->checkbox_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->enact_sound, NATIVE("NU_EnactGI_ValidClickwav") },
			{ &state.sound_ptr->subtab_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->delete_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->autochoose_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_politics_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_diplomacy_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_military_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_population_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_production_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_technology_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->tab_military_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->event_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->decision_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->pause_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->unpause_sound, NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->province_select_sounds[0], NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->province_select_sounds[1], NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->province_select_sounds[2], NATIVE("GI_ValidClick.wav") },
			{ &state.sound_ptr->province_select_sounds[3], NATIVE("GI_ValidClick.wav") },
		};
		auto const sound_directory = simple_fs::open_directory(root_dir, NATIVE("sound"));
		for(const auto& e : sound_table) {
			auto file_peek = simple_fs::peek_file(sound_directory, e.name);
			e.audio->set_file(file_peek ? simple_fs::get_full_name(*file_peek) : native_string());
		}
	}

	// these functions are called to change the volume of the currently playing track or effect
	void change_effect_volume(sys::state& state, float v) {
		state.sound_ptr->change_effect_volume(v);
	}
	void change_interface_volume(sys::state& state, float v) {
		state.sound_ptr->change_interface_volume(v);
	}
	void change_music_volume(sys::state& state, float v) {
		state.sound_ptr->change_music_volume(v);
	}

	// these start playing an effect or track at the specified volume
	void play_effect(sys::state& state, audio_instance& s, float volume) {
		if(volume > 0.0f)
		state.sound_ptr->play_effect(s, volume);
	}
	void play_interface_sound(sys::state& state, audio_instance& s, float volume) {
		if(volume > 0.0f)
		state.sound_ptr->play_interface_sound(s, volume);
	}

	// controls autoplaying music (start music should start with the main theme)
	void stop_music(sys::state& state) {
		if(state.sound_ptr->last_music != -1)
		state.sound_ptr->music_list[state.sound_ptr->last_music].stop();
		state.sound_ptr->last_music = -1;
	}
	void start_music(sys::state& state, float v) {
		if(v > 0.0f && state.sound_ptr->music_list.size() != 0) {
			if(state.sound_ptr->first_music != -1)
			state.sound_ptr->play_music(state.sound_ptr->first_music, v);
			else
			state.sound_ptr->play_music(int32_t(rand() % state.sound_ptr->music_list.size()), v);
		}
	}

	void pause_all(sys::state& state) {
		if(!state.sound_ptr.get())
		return;

		state.sound_ptr->global_pause = true;
		state.sound_ptr->pause_effect();
		state.sound_ptr->pause_interface_sound();
		state.sound_ptr->pause_music();
	}
	void resume_all(sys::state& state) {
		if(!state.sound_ptr.get())
		return;

		state.sound_ptr->global_pause = false;
		state.sound_ptr->resume_effect();
		state.sound_ptr->resume_interface_sound();
		state.sound_ptr->resume_music();
	}

	void sound_impl::update_graphs() {
		// fix for WINE
		if(current_effect && current_effect->is_finished()) {
			current_effect->stop();
		}
		if(current_interface_sound && current_interface_sound->is_finished()) {
			current_interface_sound->stop();
		}
	}

	void update_music_track(sys::state& state) {
		if(state.sound_ptr->music_finished()) {
			state.sound_ptr->play_new_track(state);
		}
		if(state.sound_ptr) {
			state.sound_ptr->update_graphs();
		}
	}

	// returns the default click sound -- expect this list of functions to expand as
	//    we implement more of the fixed sound effects
	audio_instance& get_click_sound(sys::state& state) {
		return state.sound_ptr->click_sound;
	}
	audio_instance& get_click_left_sound(sys::state& state) {
		return state.sound_ptr->click_left_sound;
	}
	audio_instance& get_click_right_sound(sys::state& state) {
		return state.sound_ptr->click_right_sound;
	}
	audio_instance& get_tab_budget_sound(sys::state& state) {
		return state.sound_ptr->tab_budget_sound;
	}
	audio_instance& get_hover_sound(sys::state& state) {
		return state.sound_ptr->hover_sound;
	}
	audio_instance& get_checkbox_sound(sys::state& state) {
		return state.sound_ptr->checkbox_sound;
	}
	audio_instance& get_enact_sound(sys::state& state) {
		return state.sound_ptr->enact_sound;
	}
	audio_instance& get_subtab_sound(sys::state& state) {
		return state.sound_ptr->subtab_sound;
	}
	audio_instance& get_delete_sound(sys::state& state) {
		return state.sound_ptr->delete_sound;
	}
	audio_instance& get_autochoose_sound(sys::state& state) {
		return state.sound_ptr->autochoose_sound;
	}
	audio_instance& get_tab_politics_sound(sys::state& state) {
		return state.sound_ptr->tab_politics_sound;
	}
	audio_instance& get_tab_diplomacy_sound(sys::state& state) {
		return state.sound_ptr->tab_diplomacy_sound;
	}
	audio_instance& get_tab_military_sound(sys::state& state) {
		return state.sound_ptr->tab_military_sound;
	}
	audio_instance& get_tab_population_sound(sys::state& state) {
		return state.sound_ptr->tab_population_sound;
	}
	audio_instance& get_tab_production_sound(sys::state& state) {
		return state.sound_ptr->tab_production_sound;
	}
	audio_instance& get_tab_technology_sound(sys::state& state) {
		return state.sound_ptr->tab_technology_sound;
	}
	audio_instance& get_army_select_sound(sys::state& state) {
		return state.sound_ptr->army_select_sound;
	}
	audio_instance& get_army_move_sound(sys::state& state) {
		return state.sound_ptr->army_move_sound;
	}
	audio_instance& get_navy_select_sound(sys::state& state) {
		return state.sound_ptr->navy_select_sound;
	}
	audio_instance& get_navy_move_sound(sys::state& state) {
		return state.sound_ptr->navy_move_sound;
	}
	audio_instance& get_error_sound(sys::state& state) {
		return state.sound_ptr->error_sound;
	}
	audio_instance& get_peace_sound(sys::state& state) {
		return state.sound_ptr->peace_sound;
	}
	audio_instance& get_army_built_sound(sys::state& state) {
		return state.sound_ptr->army_built_sound;
	}
	audio_instance& get_navy_built_sound(sys::state& state) {
		return state.sound_ptr->navy_built_sound;
	}
	audio_instance& get_declaration_of_war_sound(sys::state& state) {
		return state.sound_ptr->declaration_of_war_sound;
	}
	audio_instance& get_technology_finished_sound(sys::state& state) {
		return state.sound_ptr->technology_finished_sound;
	}
	audio_instance& get_factory_built_sound(sys::state& state) {
		return state.sound_ptr->factory_built_sound;
	}
	audio_instance& get_election_sound(sys::state& state) {
		return state.sound_ptr->election_sound;
	}
	audio_instance& get_revolt_sound(sys::state& state) {
		return state.sound_ptr->revolt_sound;
	}
	audio_instance& get_fort_built_sound(sys::state& state) {
		return state.sound_ptr->fort_built_sound;
	}
	audio_instance& get_railroad_built_sound(sys::state& state) {
		return state.sound_ptr->railroad_built_sound;
	}
	audio_instance& get_naval_base_built_sound(sys::state& state) {
		return state.sound_ptr->naval_base_built_sound;
	}
	audio_instance& get_minor_event_sound(sys::state& state) {
		return state.sound_ptr->minor_event_sound;
	}
	audio_instance& get_major_event_sound(sys::state& state) {
		return state.sound_ptr->major_event_sound;
	}
	audio_instance& get_decline_sound(sys::state& state) {
		return state.sound_ptr->decline_sound;
	}
	audio_instance& get_accept_sound(sys::state& state) {
		return state.sound_ptr->accept_sound;
	}
	audio_instance& get_diplomatic_request_sound(sys::state& state) {
		return state.sound_ptr->diplomatic_request_sound;
	}
	audio_instance& get_chat_message_sound(sys::state& state) {
		return state.sound_ptr->chat_message_sound;
	}
	audio_instance& get_console_open_sound(sys::state& state) {
		return state.sound_ptr->console_open_sound;
	}
	audio_instance& get_console_close_sound(sys::state& state) {
		return state.sound_ptr->console_close_sound;
	}

	audio_instance& get_event_sound(sys::state& state) {
		return state.sound_ptr->event_sound;
	}
	audio_instance& get_decision_sound(sys::state& state) {
		return state.sound_ptr->decision_sound;
	}
	audio_instance& get_pause_sound(sys::state& state) {
		return state.sound_ptr->pause_sound;
	}
	audio_instance& get_unpause_sound(sys::state& state) {
		return state.sound_ptr->unpause_sound;
	}

	audio_instance& get_random_land_battle_sound(sys::state& state) {
		return state.sound_ptr->land_battle_sounds[int32_t(std::rand() % 6)];
	}
	audio_instance& get_random_naval_battle_sound(sys::state& state) {
		return state.sound_ptr->naval_battle_sounds[int32_t(std::rand() % 6)];
	}
	audio_instance& get_random_province_select_sound(sys::state& state) {
		return state.sound_ptr->province_select_sounds[int32_t(std::rand() % 4)];
	}

	void play_new_track(sys::state& state) {
		state.sound_ptr->play_new_track(state);
	}
	void play_next_track(sys::state& state) {
		state.sound_ptr->play_next_track(state);
	}
	void play_previous_track(sys::state& state) {
		state.sound_ptr->play_previous_track(state);
	}

	native_string get_current_track_name(sys::state& state) {
		if(state.sound_ptr->last_music == -1)
		return NATIVE("");
		auto fname = state.sound_ptr->music_list[state.sound_ptr->last_music].filename;
		auto f = simple_fs::peek_file(simple_fs::get_root(state.common_fs), fname);
		if(f) {
			return simple_fs::get_file_name(*f);
		}
		return fname;
	}

} // namespace sound
