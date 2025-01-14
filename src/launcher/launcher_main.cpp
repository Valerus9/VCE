#ifndef UNICODE
#define UNICODE
#endif
#include <Windows.h>
#include <Windowsx.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include "Objbase.h"
#include "glad.h"
#include <cassert>
#include "fonts.hpp"
#include "texture.hpp"
#include "text.hpp"
#include "prng.hpp"
#include "system/system_state.hpp"
#include "serialization.hpp"
#include "network.hpp"
#include "simple_fs.hpp"
#include "reports.hpp"
#include "resource.h"

namespace launcher {

	static float scaling_factor = 1.0f;
	static float dpi = 96.0f;
	constexpr inline float base_width = 880.0f;
	constexpr inline float base_height = 540.0f;

	constexpr inline float caption_width = 837.0f;
	constexpr inline float caption_height = 44.0f;

	static int32_t mouse_x = 0;
	static int32_t mouse_y = 0;

	static std::string ip_addr = "127.0.0.1";
	static std::string password = "";
	static std::string player_name = "AnonAnon";

	static uint32_t bookmark_dates_total = 0;
	static uint32_t bookmark_dates_done = 0;

	enum class string_index : uint8_t {
		create_scenario,
		recreate_scenario,
		working,
		ip_address,
		password,
		nickname,
		singleplayer,
		multiplayer,
		start_game,
		host,
		join,
		mod_list,
		count
	};

	//english
	static std::string_view en_localised_strings[uint8_t(string_index::count)] = {
		"Create scenario",
		"Recreate scenario",
		"Working",
		"IP Address",
		"Password",
		"Nickname",
		"Singleplayer",
		"Multiplayer",
		"Start game",
		"Host",
		"Join",
		"Mod list"
	};
	//turkish
	static std::string_view tr_localised_strings[uint8_t(string_index::count)] = {
		"Senaryo oluştur",
		"Senaryoyu yeniden oluştur",
		"Çalışma",
		"IP adresi",
		"Şifre",
		"Takma ad",
		"Tek oyunculu",
		"Çok Oyunculu",
		"Oyunu başlatmak",
		"Ev sahibi",
		"Katılmak",
		"Mod listesi"
	};
	//albanian
	static std::string_view sq_localised_strings[uint8_t(string_index::count)] = {
		"Krijo skenar",
		"Rikrijo skenar",
		"Punon",
		"Adresa IP",
		"Fjalëkalimi",
		"Pseudonimi",
		"Lojtar i vetëm",
		"Shumë lojtarë",
		"Fillo lojen",
		"Mikpritës",
		"Bashkohu",
		"Lista e modës"
	};
	//spanish
	static std::string_view es_localised_strings[uint8_t(string_index::count)] = {
		"Crear escenario",
		"Recrear escenario",
		"Trabajando",
		"Dirección IP",
		"Contraseña",
		"Alias",
		"Un jugador",
		"Multijugador",
		"Empezar juego",
		"Hostear",
		"Unirse",
		"Lista de mods"
	};
	//italian
	static std::string_view it_localised_strings[uint8_t(string_index::count)] = {
		"Crea scenario",
		"Ricreare scenario",
		"Lavorando",
		"Indirizzo IP",
		"Password",
		"Alias",
		"Singolo",
		"Multigiocatore",
		"Inizia il gioco",
		"Ospite",
		"Partecipare",
		"Elenco delle mods"
	};
	//french
	static std::string_view fr_localised_strings[uint8_t(string_index::count)] = {
		"Creer un scènario",
		"Recrèer le scènario",
		"Fonctionnement",
		"Addresse IP",
		"Passe",
		"Alias",
		"Solo",
		"Multijoueur",
		"Dèmarrer jeu",
		"Hõte",
		"Rejoindre",
		"Liste des modifications"
	};
	//portuguese
	static std::string_view po_localised_strings[uint8_t(string_index::count)] = {
		"Criar cenário",
		"Recriar cenário",
		"Trabalhando",
		"Endereço IP",
		"Senha",
		"Alias",
		"Unjogador",
		"Multijogador",
		"Começar o jogo",
		"Hospedar",
		"Junte-se",
		"Lista de modificaçães"
	};
	//deutsch
	static std::string_view de_localised_strings[uint8_t(string_index::count)] = {
		"Szenario erstellen",
		"Szenario neu erstellen",
		"Arbeitet",
		"IP-Adresse",
		"Passwort",
		"Alias",
		"Einzelspieler",
		"Mehrspieler",
		"Spiel starten",
		"Hosten",
		"Teilnehmen",
		"Liste der Modifikationen"
	};
	//swedish
	static std::string_view sv_localised_strings[uint8_t(string_index::count)] = {
		"Skapa scenario",
		"Återskapa scenario",
		"Arbetssått",
		"IP-adress",
		"Lösenord",
		"Alias",
		"Einselspalet",
		"Merspalet",
		"Starta spelet",
		"Gå med",
		"Vara värd",
		"Lista åver åndriggar"
	};
	//chinese
	static std::string_view zh_localised_strings[uint8_t(string_index::count)] = {
		"创建方案",
		"針新创建方案",
		"工作中……",
		"IP 地址",
		"密砝",
		"昵称",
		"坕人游戝",
		"多人游戝",
		"开始游戝",
		"主机",
		"加入",
		"模组列表"
	};
	//arabic
	static std::string_view ar_localised_strings[uint8_t(string_index::count)] = {
		"إنشاء السيناريو",
		"إعادة إنشاء السيناريو",
		"عمل",
		"عنوان IP",
		"كلمة المرور",
		"كنية",
		"لاعب واحد",
		"متعددة اللاعبين",
		"بدء اللعبة",
		"يستضيٝ",
		"ينضم",
		"قائمة وزارة الدٝاع",
	};
	//norwegian
	static std::string_view no_localised_strings[uint8_t(string_index::count)] = {
		"Lag scenario",
		"Gjenskape scenario",
		"Arbeider",
		"IP adresse",
		"Passord",
		"Kallenavn",
		"Enkeltspiller",
		"Flerspiller",
		"Start spill",
		"Vert",
		"Bli med",
		"Mod liste",
	};
	//romanian
	static std::string_view ro_localised_strings[uint8_t(string_index::count)] = {
		"Creați script",
		"Scenariu de recenzie",
		"Lucru",
		"adresa IP",
		"Parola",
		"Poreclă",
		"Un singur jucator",
		"Jucători multipli",
		"Începeți jocul",
		"Gazdă",
		"A te alatura",
		"Lista de moduri"
	};
	//russian
	static std::string_view ru_localised_strings[uint8_t(string_index::count)] = {
		"Создать ѝценарий",
		"Воѝѝоздать ѝценарий",
		"Работающий",
		"айпи адреѝ",
		"Пароль",
		"Пѝевдоним",
		"Один игрок",
		"Мультиплеер",
		"Начать игру",
		"Хозѝин",
		"Приѝоединитьѝѝ",
		"Спиѝок модов",
	};
	//polish
	static std::string_view pl_localised_strings[uint8_t(string_index::count)] = {
        "Stwórz Scenariusz",
        "Odtwórz scenariusz",
        "Czekaj",
        "Adres IP",
        "Hasło",
        "Nazwa",
        "Tryb Jednoosobowy",
        "Tryb Wieloosobowy",
        "Rozpocznij Grę",
        "Hostuj",
        "Dołącz",
        "Lista Modów"
	};
	//bulgarian
	static std::string_view bg_localised_strings[uint8_t(string_index::count)] = {
		"Създайте ѝценарий",
		"Преѝъздайте ѝценарий",
		"Работи",
		"IP адреѝ",
		"Парола",
		"Пѝевдоним",
		"Един играч",
		"Мултиплейър",
		"Започни игра",
		"Домакин",
		"Приѝъединѝване",
		"Мод ѝпиѝък",
	};
	//catalan
	static std::string_view ca_localised_strings[uint8_t(string_index::count)] = {
		"Crea un escenari",
		"Recrea l'escenari",
		"Treballant",
		"Adreça IP",
		"Contrasenya",
		"Pseudònim",
		"Sol jugador",
		"Multijugador",
		"Començar el joc",
		"Amfitrió",
		"Uneixis",
		"Llista de modificacions",
	};
	//czech
	static std::string_view cs_localised_strings[uint8_t(string_index::count)] = {
		"Vytvořte scénář",
		"Znovu vytvořit scénář",
		"Pracovní",
		"IP adresa",
		"Heslo",
		"Přezdívka",
		"Pro jednoho hráĝe",
		"Pro více hráĝů",
		"Zaĝít hru",
		"Hostitel",
		"Připojit",
		"Seznam modů"
	};
	//danish
	static std::string_view da_localised_strings[uint8_t(string_index::count)] = {
		"Opret scenarie",
		"Genskab scenariet",
		"Arbejder",
		"IP - adresse",
		"Adgangskode",
		"Kaldenavn",
		"En spiller",
		"Flere spillere",
		"Start Spil",
		"Vært",
		"Tilslutte",
		"Mod liste"
	};
	//greek
	static std::string_view el_localised_strings[uint8_t(string_index::count)] = {
		"Δημιουϝγία σεναϝίου",
		"Αναδημιουϝγήστε το σενάϝιο",
		"Εϝγαζόμενος",
		"Διεϝθυνση IP",
		"Κωδικός πϝόσβασης",
		"Παϝατσοϝκλι",
		"Μονος παιχτης",
		"Λειτουϝγία για πολλοϝς παίκτες",
		"Ξεκίνα το παιχνίδι",
		"Πλήθος",
		"Συμμετοχή",
		"Λίστα mod"
	};
	//finnish
	static std::string_view fi_localised_strings[uint8_t(string_index::count)] = {
		"Luo skenaario",
		"Luo skenaario uudelleen",
		"Työskentelee",
		"IP - osoite",
		"Salasana",
		"Nimimerkki",
		"Yksinpeli",
		"Moninpeli",
		"Aloita peli",
		"Isäntä",
		"Liittyä seuraan",
		"Mod lista",
	};
	//hebrew
	static std::string_view he_localised_strings[uint8_t(string_index::count)] = {
		"צור תרחיש",
		"ליצור מחדש תרחיש",
		"עובד",
		"כתובת פרוטוקול םינטרנט",
		"סיסמה",
		"כינוי",
		"שחקן יחיד",
		"רב משתתפים",
		"התחל משחק",
		"מנחה",
		"לְהִצְטַרֵף",
		"רשימת השינויים במשחק"
	};
	//hungarian
	static std::string_view hu_localised_strings[uint8_t(string_index::count)] = {
		"Forgatókönyv létrehozása",
		"Forgatókönyv újbóli létrehozása",
		"Töltődik",
		"IP - cím",
		"Jelszó",
		"Becenév",
		"Egyjátékos",
		"Többjátékos",
		"Játék indítása",
		"Házigazda",
		"Belépés",
		"Mod lista"
	};
	//dutch
	static std::string_view nl_localised_strings[uint8_t(string_index::count)] = {
		"Scenario maken",
		"Scenario opnieuw maken",
		"Werken",
		"IP adres",
		"Wachtwoord",
		"Bijnaam",
		"Een speler",
		"Meerdere spelers",
		"Start het spel",
		"Gastheer",
		"Meedoen",
		"Mod - lijst"
	};
	//lithuanian
	static std::string_view lt_localised_strings[uint8_t(string_index::count)] = {
		"Sukurti scenarijų",
		"Atkurti scenarijų",
		"Dirba",
		"IP adresas",
		"Slaptažodis",
		"Slapyvardis",
		"Vieno žaidėjo",
		"Kelių žaidėjų",
		"Pradėti žaidimą",
		"Šeimininkas",
		"Prisijunk",
		"Modifikacijų sąrašas"
	};
	//latvian
	static std::string_view lv_localised_strings[uint8_t(string_index::count)] = {
		"Izveidojiet scenĝriju",
		"Atkĝrtoti izveidojiet scenĝriju",
		"Strĝdĝ",
		"IP adrese",
		"Parole",
		"Segvĝrds",
		"Viens spēlētĝjs",
		"Vairĝku spēlētĝju spēle",
		"Sĝkt spēli",
		"Uzņēmēja",
		"Pievienojieties",
		"Modu saraksts"
	};
	//estonian
	static std::string_view et_localised_strings[uint8_t(string_index::count)] = {
		"Loo stsenaarium",
		"Loo stsenaarium uuesti",
		"Töötab",
		"IP - aadress",
		"Parool",
		"Hüüdnimi",
		"Üksik mängija",
		"Mitmikmäng",
		"Alusta mängu",
		"Host",
		"Liitu",
		"Modifikatsioonide loend"
	};
	//hindi
	static std::string_view hi_localised_strings[uint8_t(string_index::count)] = {
		"परिदृशढ़य बनाझझ",
		"परिदृशढ़य फिर से बनाझझ",
		"कारढ़य कर रहा है",
		"आईपी पता",
		"पासवरढ़ड",
		"उपनाम",
		"झकल खिलाड़ी",
		"मलढ़टीपढ़लेयर",
		"खेल शढ़रू करें",
		"होसढ़ट",
		"जॉइन करें",
		"मॉड सूची"
	};
	//vietnamese
	static std::string_view vi_localised_strings[uint8_t(string_index::count)] = {
		"Tạo kịch bản",
		"Kịch bản tái tạo",
		"ĝang làm việc",
		"ĝịa chỉ IP",
		"Mật khẩu",
		"Tên nick",
		"Người chơi đơn",
		"Nhiờu người chơi",
		"Bắt đầu trò chơi",
		"Chủ nhà",
		"Tham gia",
		"Danh sách mod"
	};
	//armenian
	static std::string_view hy_localised_strings[uint8_t(string_index::count)] = {
		"՝տեղծեք ս֝ենար",
		"Վերստեղծեք ս֝ենարը",
		"Աշխատանքային",
		"IP հաս֝ե",
		"Գաղտնաբառ",
		"Մականուն",
		"Միայնակ խաղա֝ող",
		"Բազմապատկիչ",
		"՝կսել խաղը",
		"Հյուրընկալող",
		"Միանալ",
		"Mod ու֝ակ"
	};
	//ukrainian
	static std::string_view uk_localised_strings[uint8_t(string_index::count)] = {
		"Створити ѝценарій",
		"Сценарій оглѝду",
		"Працює",
		"IP - адреѝа",
		"Пароль",
		"Прізвище",
		"Один гравець",
		"Мультиплеєр",
		"Почніть гру",
		"Гоѝподар",
		"З'єднувати",
		"Спиѝок мод"
	};
	static std::string_view* localised_strings = &en_localised_strings[0];

	static HWND m_hwnd = nullptr;

	struct ui_active_rect {
		int32_t x = 0;
		int32_t y = 0;
		int32_t width = 0;
		int32_t height = 0;
	};

	constexpr inline int32_t ui_obj_close = 0;
	constexpr inline int32_t ui_obj_list_left = 1;
	constexpr inline int32_t ui_obj_list_right = 2;
	constexpr inline int32_t ui_obj_play_game = 3;
	constexpr inline int32_t ui_obj_host_game = 4;
	constexpr inline int32_t ui_obj_join_game = 5;
	constexpr inline int32_t ui_obj_ip_addr = 6;
	constexpr inline int32_t ui_obj_password = 7;
	constexpr inline int32_t ui_obj_player_name = 8;

	constexpr inline int32_t ui_list_first = 9;
	constexpr inline int32_t ui_list_count = 14;
	constexpr inline int32_t ui_list_checkbox = 0;
	constexpr inline int32_t ui_list_move_up = 1;
	constexpr inline int32_t ui_list_move_down = 2;
	constexpr inline int32_t ui_list_end = ui_list_first + ui_list_count * 3;

	constexpr inline int32_t ui_row_height = 32;

	constexpr inline float list_text_right_align = 420.0f;

	static int32_t obj_under_mouse = -1;

	static bool game_dir_not_found = false;

	constexpr inline ui_active_rect ui_rects[] = {
		ui_active_rect{ 880 - 31,  0 , 31, 31}, // close
		ui_active_rect{ 30, 207, 21, 93}, // left
		ui_active_rect{ 515, 207, 21, 93}, // right
		ui_active_rect{ 555, 75 + 32 * 0 + 4, 286, 33 }, // play game
		ui_active_rect{ 555, 48 + 156 * 1 + 36 * 0 + 2, 138, 33 }, // host game
		ui_active_rect{ 703, 48 + 156 * 1 + 36 * 0 + 2, 138, 33 }, // join game
		ui_active_rect{ 555, 54 + 156 * 1 + 36 * 2, 200, 23 }, // ip address textbox
		ui_active_rect{ 555, 54 + 156 * 1 + 36 * 3 + 12, 200, 23 }, // password textbox
		ui_active_rect{ 765, 54 + 156 * 1 + 36 * 2, 76, 23 }, // player name textbox
		ui_active_rect{ 60 + 6, 75 + 32 * 0 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 0 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 0 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 1 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 1 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 1 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 2 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 2 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 2 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 3 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 3 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 3 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 4 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 4 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 4 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 5 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 5 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 5 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 6 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 6 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 6 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 7 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 7 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 7 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 8 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 8 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 8 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 9 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 9 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 9 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 10 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 10 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 10 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 11 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 11 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 11 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 12 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 12 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 12 + 4, 24, 24 },
		ui_active_rect{ 60 + 6, 75 + 32 * 13 + 4, 24, 24 },
		ui_active_rect{ 60 + 383, 75 + 32 * 13 + 4, 24, 24 },
		ui_active_rect{ 60 + 412, 75 + 32 * 13 + 4, 24, 24 },
	};

	static std::vector<parsers::mod_file> mod_list;
	static int32_t frame_in_list = 0;

	static HDC opengl_window_dc = nullptr;
	static void* opengl_context = nullptr;

	void create_opengl_context() {
		HDC window_dc = opengl_window_dc;

		bool has_pfd_set = false;
		auto const pfd_count = DescribePixelFormat(window_dc, 1, sizeof(PIXELFORMATDESCRIPTOR), NULL);
		for(uint32_t i = 0; i < uint32_t(pfd_count); i++) {
			PIXELFORMATDESCRIPTOR pfd;
			if(!DescribePixelFormat(window_dc, i + 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd)) {
				reports::write_debug("Unable to describe PixelFormat " + std::to_string(i) + "\n");
				continue;
			}
			if((pfd.dwFlags & PFD_DRAW_TO_WINDOW) != 0
			&& (pfd.dwFlags & PFD_SUPPORT_OPENGL) != 0
			&& (pfd.dwFlags & PFD_DOUBLEBUFFER) != 0
			&& pfd.iPixelType == PFD_TYPE_RGBA
			&& pfd.cDepthBits >= 8
			&& pfd.cStencilBits >= 8
			&& pfd.cColorBits >= 24) {
				reports::write_debug("Found usable pixel format #" + std::to_string(i) + "\n");
				reports::write_debug("Stencil=" + std::to_string(pfd.cStencilBits) + ",ColorDepth=" + std::to_string(pfd.cColorBits) + ",AccumBits=" + std::to_string(pfd.cAccumBits) + "\n");
				if(SetPixelFormat(window_dc, i + 1, &pfd)) {
					has_pfd_set = true;
					break;
				} else {
					reports::write_debug("Unable to set a pixel format: " + std::to_string(GetLastError()) + "\n");
				}
			}
		}
		if(!has_pfd_set) {
			reports::write_debug("Using default PFD as fallback\n");
			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory(&pfd, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 24;
			pfd.cStencilBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;
			int const pixel_format = ChoosePixelFormat(window_dc, &pfd);
			if(!SetPixelFormat(window_dc, pixel_format, &pfd)) {
				reports::write_debug("Unable to set a pixel format: " + std::to_string(GetLastError()) + "\n");
			}
		}

		auto gl_lib = LoadLibraryW(L"opengl32.dll");
		if(gl_lib) {
			opengl_context = ((decltype(&wglCreateContext))GetProcAddress(gl_lib, "wglCreateContext"))(window_dc);
			if(opengl_context == NULL) {
				window::emit_error_message("Unable to create WGL context: " + std::to_string(GetLastError()), true);
			}
			((decltype(&wglMakeCurrent))GetProcAddress(gl_lib, "wglMakeCurrent"))(window_dc, HGLRC(opengl_context));
			if(gladLoadGL() == 0) {
				window::emit_error_message("GLAD failed to initialize", true);
			}
#if 0
			glDebugMessageCallback(debug_callback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
			glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_FALSE);
#endif
			//
			reports::write_debug("GL Version: " + std::string(reinterpret_cast<char const*>(glGetString(GL_VERSION))) + "\n");
			reports::write_debug("GL Shading version: " + std::string(reinterpret_cast<char const*>(glGetString(GL_SHADING_LANGUAGE_VERSION))) + "\n");
			/*
			if(wglewIsSupported("WGL_EXT_swap_control_tear") == 1) {
				reports::write_debug("WGL_EXT_swap_control_tear is on\n");
				wglSwapIntervalEXT(-1);
			} else if(wglewIsSupported("WGL_EXT_swap_control") == 1) {
				reports::write_debug("WGL_EXT_swap_control is on\n");
				wglSwapIntervalEXT(1);
			}
			*/
			FreeLibrary(gl_lib);
		} else {
			window::emit_error_message("Opengl32.dll is missing", true);
		}
	}

	void shutdown_opengl() {
		auto gl_lib = LoadLibraryW(L"opengl32.dll");
		if(gl_lib) {
			((decltype(&wglMakeCurrent))GetProcAddress(gl_lib, "wglMakeCurrent"))(opengl_window_dc, NULL);
			((decltype(&wglDeleteContext))GetProcAddress(gl_lib, "wglDeleteContext"))(HGLRC(opengl_context));
			FreeLibrary(gl_lib);
		}
		opengl_context = nullptr;
	}

	bool update_under_mouse() { // return if the selected object (if any) has changed
		for(int32_t i = 0; i < ui_list_end; ++i) {
			if(mouse_x >= ui_rects[i].x && mouse_x < ui_rects[i].x + ui_rects[i].width
			&& mouse_y >= ui_rects[i].y && mouse_y < ui_rects[i].y + ui_rects[i].height) {
				if(obj_under_mouse != i) {
					obj_under_mouse = i;
					return true;
				} else {
					return false;
				}
			}
		}

		if(obj_under_mouse != -1) {
			obj_under_mouse = -1;
			return true;
		} else {
			return false;
		}
	}

	void recursively_remove_from_list(parsers::mod_file& mod) {
		for(int32_t i = 0; i < int32_t(mod_list.size()); ++i) {
			if(mod_list[i].mod_selected) {
				if(std::find(mod_list[i].dependent_mods.begin(), mod_list[i].dependent_mods.end(), mod.name_) != mod_list[i].dependent_mods.end()) {
					mod_list[i].mod_selected = false;
					recursively_remove_from_list(mod_list[i]);
				}
			}
		}
	}
	void recursively_add_to_list(parsers::mod_file& mod) {
		for(auto& dep : mod.dependent_mods) {
			for(int32_t i = 0; i < int32_t(mod_list.size()); ++i) {
				if(!mod_list[i].mod_selected && mod_list[i].name_ == dep) {
					mod_list[i].mod_selected = true;
					recursively_add_to_list(mod_list[i]);
				}
			}
		}
	}

	bool transitively_depends_on_internal(parsers::mod_file const& moda, parsers::mod_file const& modb, std::vector<bool>& seen_indices) {
		for(auto& dep : moda.dependent_mods) {
			if(dep == modb.name_) {
				return true;
			}

			for(int32_t i = 0; i < int32_t(mod_list.size()); ++i) {
				if(seen_indices[i] == false && mod_list[i].name_ == dep) {
					seen_indices[i] = true;
					if(transitively_depends_on_internal(mod_list[i], modb, seen_indices)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool transitively_depends_on(parsers::mod_file const& moda, parsers::mod_file const& modb) {
		std::vector<bool> seen_indices;
		seen_indices.resize(mod_list.size());

		return transitively_depends_on_internal(moda, modb, seen_indices);
	}

	void enforce_list_order() {
		std::stable_sort(mod_list.begin(), mod_list.end(), [&](parsers::mod_file const& a, parsers::mod_file const& b) {
			if(a.mod_selected && b.mod_selected) {
				return transitively_depends_on(b, a);
			} else if(a.mod_selected && !b.mod_selected) {
				return true;
			} else if(!a.mod_selected && b.mod_selected) {
				return false;
			} else {
				return a.name_ < b.name_;
			}
		});
	}

	bool nth_item_can_move_up(int32_t n) {
		if(n == 0) {
			return false;
		}
		if(transitively_depends_on(mod_list[n], mod_list[n - 1])) {
			return false;
		}
		return true;
	}
	bool nth_item_can_move_down(int32_t n) {
		if(n >= int32_t(mod_list.size()) - 1) {
			return false;
		}
		if(mod_list[n + 1].mod_selected == false) {
			return false;
		}
		if(transitively_depends_on(mod_list[n + 1], mod_list[n])) {
			return false;
		}
		return true;
	}

	native_string produce_mod_path() {
		simple_fs::file_system dummy;
		simple_fs::add_root(dummy, NATIVE("."));
		for(int32_t i = 0; i < int32_t(mod_list.size()); ++i) {
			if(mod_list[i].mod_selected == false) {
				break;
			}
			mod_list[i].add_to_file_system(dummy);
		}
		return simple_fs::extract_state(dummy);
	}

	void save_playername() {
		sys::player_name p;
		auto len = std::min<size_t>(launcher::player_name.length(), sizeof(p.data));
		std::memcpy(p.data, launcher::player_name.c_str(), len);

		auto settings_location = simple_fs::get_or_create_settings_directory();
		simple_fs::write_file(settings_location, NATIVE("player_name.dat"), (const char*)&p, sizeof(p));
	}

	native_string to_hex(uint64_t v) {
		native_string ret;
		constexpr native_char digits[] = NATIVE("0123456789ABCDEF");
		do {
			ret += digits[v & 0x0F];
			v = v >> 4;
		} while(v != 0);
		return ret;
	}

	void mouse_click() {
		if(obj_under_mouse == -1)
			return;

		switch(obj_under_mouse) {
		case ui_obj_close:
			PostMessageW(m_hwnd, WM_CLOSE, 0, 0);
			return;
		case ui_obj_list_left:
			if(frame_in_list > 0) {
				--frame_in_list;
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
			}
			return;
		case ui_obj_list_right:
			if((frame_in_list + 1) * ui_list_count < int32_t(mod_list.size())) {
				++frame_in_list;
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
			}
			return;
		case ui_obj_play_game:
		case ui_obj_host_game:
		case ui_obj_join_game:
		{
			native_string mod_path = produce_mod_path();
			native_string temp_command_line = native_string(NATIVE("VicCEngine.exe -autofind -path "));
			temp_command_line += NATIVE("\"") + mod_path + NATIVE("\"");

			for(auto const& mod : mod_list) {
				if(mod.mod_selected && mod.extension_script_ui) {
					temp_command_line += NATIVE(" -ext-script-ui");
					break;
				}
			}


			if(obj_under_mouse == ui_obj_host_game) {
				temp_command_line += NATIVE(" -host");
			} else if(obj_under_mouse == ui_obj_join_game) {
				temp_command_line += NATIVE(" -join \"") + text::utf8_to_native(ip_addr) + NATIVE("\"");
				// IPv6 address
				if(!ip_addr.empty() && ::strchr(ip_addr.c_str(), ':') != nullptr) {
					temp_command_line += NATIVE(" -v6");
				}
			}
			temp_command_line += NATIVE(" -name \"") + text::utf8_to_native(player_name) + NATIVE("\"");
			if(!password.empty()) {
				temp_command_line += NATIVE(" -password \"") + text::utf8_to_native(password) + NATIVE("\"");
			}

			reports::write_debug("Command line: [" + text::native_to_utf8(temp_command_line) + "]\n");

			STARTUPINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);

			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));

			// Start the child process.
			if(CreateProcessW(
				NULL,   // Module name
				temp_command_line.data(), // Command line
				NULL, // Process handle not inheritable
				NULL, // Thread handle not inheritable
				FALSE, // Set handle inheritance to FALSE
				0, // No creation flags
				NULL, // Use parent's environment block
				NULL, // Use parent's starting directory
				&si, // Pointer to STARTUPINFO structure
				&pi) != 0) {
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			return;
		}
		case ui_obj_ip_addr:
		case ui_obj_password:
		case ui_obj_player_name:
			return;
		default:
			break;
		}

		int32_t list_position = (obj_under_mouse - ui_list_first) / 3;
		int32_t sub_obj = (obj_under_mouse - ui_list_first) - list_position * 3;

		switch(sub_obj) {
		case ui_list_checkbox:
		{
			int32_t list_offset = launcher::frame_in_list * launcher::ui_list_count + list_position;
			if(list_offset < int32_t(launcher::mod_list.size())) {
				launcher::mod_list[list_offset].mod_selected = !launcher::mod_list[list_offset].mod_selected;
				if(!launcher::mod_list[list_offset].mod_selected) {
					recursively_remove_from_list(launcher::mod_list[list_offset]);
				} else {
					recursively_add_to_list(launcher::mod_list[list_offset]);
				}
				enforce_list_order();
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
			}
			return;
		}
		case ui_list_move_up:
		{
			int32_t list_offset = launcher::frame_in_list * launcher::ui_list_count + list_position;
			if(launcher::mod_list[list_offset].mod_selected && nth_item_can_move_up(list_offset)) {
				std::swap(launcher::mod_list[list_offset], launcher::mod_list[list_offset - 1]);
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
			}
			return;
		}
		case ui_list_move_down:
		{
			int32_t list_offset = launcher::frame_in_list * launcher::ui_list_count + list_position;
			if(launcher::mod_list[list_offset].mod_selected && nth_item_can_move_down(list_offset)) {
				std::swap(launcher::mod_list[list_offset], launcher::mod_list[list_offset + 1]);
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
			}
			return;
		}
		default:
			break;
		}
	}

	GLint compile_shader(std::string_view source, GLenum type) {
		GLuint return_value = glCreateShader(type);

		if(return_value == 0) {
			MessageBoxW(m_hwnd, L"shader creation failed", L"OpenGL error", MB_OK);
		}

		std::string s_source(source);
		GLchar const* texts[] = {
			"#version 140\n",
			"#extension GL_ARB_explicit_uniform_location : enable\n",
			"#extension GL_ARB_explicit_attrib_location : enable\n",
			"#extension GL_ARB_shader_subroutine : enable\n",
			"#define M_PI 3.1415926535897932384626433832795f\n",
			"#define PI 3.1415926535897932384626433832795f\n",
			s_source.c_str()
		};
		glShaderSource(return_value, 7, texts, nullptr);
		glCompileShader(return_value);

		GLint result;
		glGetShaderiv(return_value, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE) {
			GLint log_length = 0;
			glGetShaderiv(return_value, GL_INFO_LOG_LENGTH, &log_length);

			auto log = std::unique_ptr<char[]>(new char[static_cast<size_t>(log_length)]);
			GLsizei written = 0;
			glGetShaderInfoLog(return_value, log_length, &written, log.get());
			auto error = std::string("Shader failed to compile:\n") + log.get();
			MessageBoxA(m_hwnd, error.c_str(), "OpenGL error", MB_OK);
		}
		return return_value;
	}

	GLuint create_program(std::string_view vertex_shader, std::string_view fragment_shader) {
		GLuint return_value = glCreateProgram();
		if(return_value == 0) {
			MessageBoxW(m_hwnd, L"program creation failed", L"OpenGL error", MB_OK);
		}

		auto v_shader = compile_shader(vertex_shader, GL_VERTEX_SHADER);
		auto f_shader = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

		glAttachShader(return_value, v_shader);
		glAttachShader(return_value, f_shader);
		glLinkProgram(return_value);

		GLint result;
		glGetProgramiv(return_value, GL_LINK_STATUS, &result);
		if(result == GL_FALSE) {
			GLint logLen;
			glGetProgramiv(return_value, GL_INFO_LOG_LENGTH, &logLen);

			char* log = new char[static_cast<size_t>(logLen)];
			GLsizei written;
			glGetProgramInfoLog(return_value, logLen, &written, log);
			auto err = std::string("Program failed to link:\n") + log;
			MessageBoxA(m_hwnd, err.c_str(), "OpenGL error", MB_OK);
		}

		glDeleteShader(v_shader);
		glDeleteShader(f_shader);
		return return_value;
	}

static GLfloat global_square_data[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f };
static GLfloat global_square_right_data[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
static GLfloat global_square_left_data[16] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f };
static GLfloat global_square_flipped_data[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };
static GLfloat global_square_right_flipped_data[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f };
static GLfloat global_square_left_flipped_data[16] = { 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	static GLuint ui_shader_program = 0;

	void load_shaders() {
		reports::write_debug("Loading shaders\n");

		simple_fs::file_system fs;
		simple_fs::add_root(fs, NATIVE("."));
		auto root = get_root(fs);
		std::string_view fx_str =
		"in vec2 tex_coord;\n"
		"out vec4 frag_color;\n"
		"uniform sampler2D texture_sampler;\n"
		"uniform vec4 d_rect;\n"
		"uniform float border_size;\n"
		"uniform vec3 inner_color;\n"
		"uniform vec4 subrect;\n"
		"uniform uvec2 subroutines_index;\n"
		"vec4 color_filter(vec2 tc) {\n"
			"\tvec4 color_in = texture(texture_sampler, tc);\n"
			"\tfloat sm_val = smoothstep(0.5 - border_size / 2.0, 0.5 + border_size / 2.0, color_in.r);\n"
			"\treturn vec4(inner_color, sm_val);\n"
		"}\n"
		"vec4 no_filter(vec2 tc) {\n"
			"\treturn texture(texture_sampler, tc);\n"
		"}\n"
		"vec4 disabled_color(vec4 color_in) {\n"
			"\tfloat amount = (color_in.r + color_in.g + color_in.b) / 4.0;\n"
			"\treturn vec4(amount, amount, amount, color_in.a);\n"
		"}\n"
		"vec4 interactable_color(vec4 color_in) {\n"
			"\treturn vec4(color_in.r + 0.1, color_in.g + 0.1, color_in.b + 0.1, color_in.a);\n"
		"}\n"
		"vec4 interactable_disabled_color(vec4 color_in) {\n"
			"\tfloat amount = (color_in.r + color_in.g + color_in.b) / 4.0;\n"
			"\treturn vec4(amount + 0.1, amount + 0.1, amount + 0.1, color_in.a);\n"
		"}\n"
		"vec4 tint_color(vec4 color_in) {\n"
			"\treturn vec4(color_in.r * inner_color.r, color_in.g * inner_color.g, color_in.b * inner_color.b, color_in.a);\n"
		"}\n"
		"vec4 enabled_color(vec4 color_in) {\n"
			"\treturn color_in;\n"
		"}\n"
		"vec4 alt_tint_color(vec4 color_in) {\n"
			"\treturn vec4(color_in.r * subrect.r, color_in.g * subrect.g, color_in.b * subrect.b, color_in.a);\n"
		"}\n"
		"vec4 font_function(vec2 tc) {\n"
			"\treturn int(subroutines_index.y) == 1 ? color_filter(tc) : no_filter(tc);\n"
		"}\n"
		"vec4 coloring_function(vec4 tc) {\n"
			"\tswitch(int(subroutines_index.x)) {\n"
				"\tcase 3: return disabled_color(tc);\n"
				"\tcase 4: return enabled_color(tc);\n"
				"\tcase 12: return tint_color(tc);\n"
				"\tcase 13: return interactable_color(tc);\n"
				"\tcase 14: return interactable_disabled_color(tc);\n"
				"\tcase 16: return alt_tint_color(tc);\n"
				"\tdefault: break;\n"
			"\t}\n"
			"\treturn tc;\n"
		"}\n"
		"void main() {\n"
			"\tfrag_color = coloring_function(font_function(tex_coord));\n"
		"}";
		std::string_view vx_str =
		"layout (location = 0) in vec2 vertex_position;\n"
		"layout (location = 1) in vec2 v_tex_coord;\n"
		"out vec2 tex_coord;\n"
		"uniform float screen_width;\n"
		"uniform float screen_height;\n"
		"uniform vec4 d_rect;\n"
		"void main() {\n"
			"\tgl_Position = vec4(\n"
			"\t\t-1.0 + (2.0 * ((vertex_position.x * d_rect.z)  + d_rect.x) / screen_width),\n"
			"\t\t 1.0 - (2.0 * ((vertex_position.y * d_rect.w)  + d_rect.y) / screen_height),\n"
			"\t\t0.0, 1.0);\n"
			"\ttex_coord = v_tex_coord;\n"
		"}";

		ui_shader_program = create_program(vx_str, fx_str);
	}

	static GLuint global_square_vao = 0;
	static GLuint global_square_buffer = 0;
	static GLuint global_square_right_buffer = 0;
	static GLuint global_square_left_buffer = 0;
	static GLuint global_square_flipped_buffer = 0;
	static GLuint global_square_right_flipped_buffer = 0;
	static GLuint global_square_left_flipped_buffer = 0;

	static GLuint sub_square_buffers[64] = { 0 };
	static GLuint sub_square_arrays[64] = { 0 };

	void load_global_squares() {
		reports::write_debug("Loading global squares\n");

		glGenBuffers(1, &global_square_buffer);

		// Populate the position buffer
		glBindBuffer(GL_ARRAY_BUFFER, global_square_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, global_square_data, GL_STATIC_DRAW);
		glGenVertexArrays(1, &global_square_vao);
		glBindVertexArray(global_square_vao);
		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // texture coordinates
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0); // position
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void*)(sizeof(GLfloat) * 2)); // texture coordinates

		glGenBuffers(64, sub_square_buffers);
		glGenVertexArrays(64, sub_square_arrays);
		for(uint32_t i = 0; i < 64; ++i) {
			float const cell_x = static_cast<float>(i & 7) / 8.0f;
			float const cell_y = static_cast<float>((i >> 3) & 7) / 8.0f;
			GLfloat global_sub_square_data[16] = { 0.0f, 0.0f, cell_x, cell_y, 0.0f, 1.0f, cell_x, cell_y + 1.0f / 8.0f, 1.0f, 1.0f, cell_x + 1.0f / 8.0f, cell_y + 1.0f / 8.0f, 1.0f, 0.0f, cell_x + 1.0f / 8.0f, cell_y };
			glBindBuffer(GL_ARRAY_BUFFER, sub_square_buffers[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, global_sub_square_data, GL_STATIC_DRAW);
			glBindVertexArray(sub_square_arrays[i]);
			glEnableVertexAttribArray(0); // position
			glEnableVertexAttribArray(1); // texture coordinates
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0); // position
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void*)(sizeof(GLfloat) * 2)); // texture coordinates
		}
	}


	namespace ogl {
		namespace parameters {

			inline constexpr GLuint screen_width = 0;
			inline constexpr GLuint screen_height = 1;
			inline constexpr GLuint drawing_rectangle = 2;

			inline constexpr GLuint border_size = 6;
			inline constexpr GLuint inner_color = 7;
			inline constexpr GLuint subrect = 10;

			inline constexpr GLuint enabled = 4;
			inline constexpr GLuint disabled = 3;
			inline constexpr GLuint border_filter = 0;
			inline constexpr GLuint filter = 1;
			inline constexpr GLuint no_filter = 2;
			inline constexpr GLuint sub_sprite = 5;
			inline constexpr GLuint use_mask = 6;
			inline constexpr GLuint progress_bar = 7;
			inline constexpr GLuint frame_stretch = 8;
			inline constexpr GLuint piechart = 9;
			inline constexpr GLuint barchart = 10;
			inline constexpr GLuint linegraph = 11;
			inline constexpr GLuint tint = 12;
			inline constexpr GLuint interactable = 13;
			inline constexpr GLuint interactable_disabled = 14;
			inline constexpr GLuint subsprite_b = 15;
			inline constexpr GLuint atlas_index = 18;

		} // namespace parameters

		enum class color_modification {
			none, disabled, interactable, interactable_disabled
		};

		struct color3f {
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
		};

		inline auto map_color_modification_to_index(color_modification e) {
			switch(e) {
				case color_modification::disabled:
				return parameters::disabled;
				case color_modification::interactable:
				return parameters::interactable;
				case color_modification::interactable_disabled:
				return parameters::interactable_disabled;
				default:
				case color_modification::none:
				return parameters::enabled;
			}
		}

		void render_textured_rect(color_modification enabled, int32_t ix, int32_t iy, int32_t iwidth, int32_t iheight, GLuint texture_handle, ui::rotation r, bool flipped) {
			float x = float(ix);
			float y = float(iy);
			float width = float(iwidth);
			float height = float(iheight);

			glBindVertexArray(global_square_vao);
			glBindBuffer(0, global_square_buffer);

			glUniform4f(glGetUniformLocation(ui_shader_program, "d_rect"), x, y, width, height);
			// glUniform4f(glGetUniformLocation(ui_shader_program, "d_rect"), 0, 0, width, height);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_handle);

		GLuint subroutines[2] = { map_color_modification_to_index(enabled), parameters::no_filter };
			glUniform2ui(glGetUniformLocation(ui_shader_program, "subroutines_index"), subroutines[0], subroutines[1]);
			//glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 2, subroutines); // must set all subroutines in one call

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}

		void internal_text_render(std::string_view str, float baseline_x, float baseline_y, float size, ::text::font& f) {
			hb_buffer_clear_contents(f.hb_buf);
			hb_buffer_pre_allocate(f.hb_buf, static_cast<unsigned int>(str.size()));
			hb_buffer_add_utf8(f.hb_buf, str.data(), int(str.size()), 0, int(str.size()));
			hb_buffer_guess_segment_properties(f.hb_buf);
			hb_shape(f.hb_font_face, f.hb_buf, NULL, 0);
			unsigned int glyph_count = 0;
			hb_glyph_info_t* glyph_info = hb_buffer_get_glyph_infos(f.hb_buf, &glyph_count);
			hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(f.hb_buf, &glyph_count);
			float x = baseline_x;
			for(unsigned int i = 0; i < glyph_count; i++) {
				f.make_glyph(glyph_info[i].codepoint);
			}
			for(unsigned int i = 0; i < glyph_count; i++) {
				hb_codepoint_t glyphid = glyph_info[i].codepoint;
				auto gso = f.glyph_positions[glyphid];
				float x_advance = float(glyph_pos[i].x_advance) / (float((1 << 6) * text::magnification_factor));
				float x_offset = float(glyph_pos[i].x_offset) / (float((1 << 6) * text::magnification_factor)) + float(gso.x);
				float y_offset = float(gso.y) - float(glyph_pos[i].y_offset) / (float((1 << 6) * text::magnification_factor));
				if(glyphid != FT_Get_Char_Index(f.font_face, ' ')) {
					glBindBuffer(GL_ARRAY_BUFFER, sub_square_buffers[f.glyph_positions[glyphid].texture_slot & 63]);
					glBindVertexArray(sub_square_arrays[f.glyph_positions[glyphid].texture_slot & 63]);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, f.textures[f.glyph_positions[glyphid].texture_slot >> 6]);
					glUniform4f(glGetUniformLocation(ui_shader_program, "d_rect"), x + x_offset * size / 64.f, baseline_y + y_offset * size / 64.f, size, size);
					glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
				}
				x += x_advance * size / 64.f;
			}
		}

		void render_new_text(std::string_view sv, color_modification enabled, float x, float y, float size, color3f const& c, ::text::font& f) {
			glUniform3f(glGetUniformLocation(ui_shader_program, "inner_color"), c.r, c.g, c.b);
			glUniform1f(glGetUniformLocation(ui_shader_program, "border_size"), 0.08f * 16.0f / size);
			GLuint subroutines[2] = { map_color_modification_to_index(enabled), parameters::filter };
			glUniform2ui(glGetUniformLocation(ui_shader_program, "subroutines_index"), subroutines[0], subroutines[1]);
			//glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 2, subroutines); // must set all subroutines in one call
			internal_text_render(sv, x, y + size, size, f);
		}

	} // launcher::ogl

	static ::text::font_manager font_collection; //keep static because it uninits FT lib on destructor
	static ::text::font fonts[2];

	static ::ogl::texture bg_tex;
	static ::ogl::texture left_tex;
	static ::ogl::texture right_tex;
	static ::ogl::texture close_tex;
	static ::ogl::texture big_button_tex;
	static ::ogl::texture empty_check_tex;
	static ::ogl::texture check_tex;
	static ::ogl::texture up_tex;
	static ::ogl::texture down_tex;
	static ::ogl::texture line_bg_tex;
	static ::ogl::texture big_l_button_tex;
	static ::ogl::texture big_r_button_tex;
	static ::ogl::texture warning_tex;

	float base_text_extent(char const* codepoints, uint32_t count, int32_t size, text::font& f) {
		hb_buffer_clear_contents(f.hb_buf);
		hb_buffer_pre_allocate(f.hb_buf, static_cast<unsigned int>(count));
		hb_buffer_add_utf8(f.hb_buf, codepoints, int(count), 0, int(count));
		hb_buffer_guess_segment_properties(f.hb_buf);
		hb_shape(f.hb_font_face, f.hb_buf, NULL, 0);
		unsigned int glyph_count = 0;
		hb_glyph_info_t* glyph_info = hb_buffer_get_glyph_infos(f.hb_buf, &glyph_count);
		hb_glyph_position_t* glyph_pos = hb_buffer_get_glyph_positions(f.hb_buf, &glyph_count);
		float x = 0.0f;
		for(unsigned int i = 0; i < glyph_count; i++) {
			f.make_glyph(glyph_info[i].codepoint);
		}
		for(unsigned int i = 0; i < glyph_count; i++) {
			hb_codepoint_t glyphid = glyph_info[i].codepoint;
			auto gso = f.glyph_positions[glyphid];
			float x_advance = float(glyph_pos[i].x_advance) / (float((1 << 6) * text::magnification_factor));
			float x_offset = float(glyph_pos[i].x_offset) / (float((1 << 6) * text::magnification_factor)) + float(gso.x);
			float y_offset = float(gso.y) - float(glyph_pos[i].y_offset) / (float((1 << 6) * text::magnification_factor));
			x += x_advance * size / 64.f;
		}
		return x;
	}

	void render() {
		if(!opengl_context)
			return;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glUseProgram(ui_shader_program);
		glUniform1i(glGetUniformLocation(ui_shader_program, "texture_sampler"), 0);
		glUniform1f(glGetUniformLocation(ui_shader_program, "screen_width"), float(base_width));
		glUniform1f(glGetUniformLocation(ui_shader_program, "screen_height"), float(base_height));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, int32_t(base_width * scaling_factor), int32_t(base_height * scaling_factor));
		glDepthRange(-1.0f, 1.0f);

		launcher::ogl::render_textured_rect(launcher::ogl::color_modification::none, 0, 0, int32_t(base_width), int32_t(base_height), bg_tex.get_texture_handle(), ui::rotation::upright, false);

		launcher::ogl::render_new_text("Victoria Community's Engine", launcher::ogl::color_modification::none, 83, 5, 26, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[1]);

		// bottom right corner
		std::string version_text = "v" + std::to_string(sys::scenario_file_version);
		launcher::ogl::render_new_text(version_text.c_str(), launcher::ogl::color_modification::none, 613, 380, 16, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[1]);

		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_close ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
		ui_rects[ui_obj_close].x,
		ui_rects[ui_obj_close].y,
		ui_rects[ui_obj_close].width,
		ui_rects[ui_obj_close].height,
		close_tex.get_texture_handle(), ui::rotation::upright, false);

		if(int32_t(mod_list.size()) > ui_list_count) {
			if(frame_in_list > 0) {
				launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_list_left ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
				ui_rects[ui_obj_list_left].x,
				ui_rects[ui_obj_list_left].y,
				ui_rects[ui_obj_list_left].width,
				ui_rects[ui_obj_list_left].height,
				left_tex.get_texture_handle(), ui::rotation::upright, false);
			} else {
				launcher::ogl::render_textured_rect(launcher::ogl::color_modification::disabled,
				ui_rects[ui_obj_list_left].x,
				ui_rects[ui_obj_list_left].y,
				ui_rects[ui_obj_list_left].width,
				ui_rects[ui_obj_list_left].height,
				left_tex.get_texture_handle(), ui::rotation::upright, false);
			}

			if((frame_in_list + 1) * ui_list_count < int32_t(mod_list.size())) {
				launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_list_right ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
				ui_rects[ui_obj_list_right].x,
				ui_rects[ui_obj_list_right].y,
				ui_rects[ui_obj_list_right].width,
				ui_rects[ui_obj_list_right].height,
				right_tex.get_texture_handle(), ui::rotation::upright, false);
			} else {
				launcher::ogl::render_textured_rect(launcher::ogl::color_modification::disabled,
				ui_rects[ui_obj_list_right].x,
				ui_rects[ui_obj_list_right].y,
				ui_rects[ui_obj_list_right].width,
				ui_rects[ui_obj_list_right].height,
				right_tex.get_texture_handle(), ui::rotation::upright, false);
			}
		}

		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_play_game ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
			ui_rects[ui_obj_play_game].x,
			ui_rects[ui_obj_play_game].y,
			ui_rects[ui_obj_play_game].width,
			ui_rects[ui_obj_play_game].height,
			big_button_tex.get_texture_handle(), ui::rotation::upright, false);
		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_host_game ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
			ui_rects[ui_obj_host_game].x,
			ui_rects[ui_obj_host_game].y,
			ui_rects[ui_obj_host_game].width,
			ui_rects[ui_obj_host_game].height,
			big_l_button_tex.get_texture_handle(), ui::rotation::upright, false);
		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_join_game ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
			ui_rects[ui_obj_join_game].x,
			ui_rects[ui_obj_join_game].y,
			ui_rects[ui_obj_join_game].width,
			ui_rects[ui_obj_join_game].height,
			big_r_button_tex.get_texture_handle(), ui::rotation::upright, false);

		auto sv = launcher::localised_strings[uint8_t(launcher::string_index::ip_address)];
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ui_rects[ui_obj_ip_addr].x + ui_rects[ui_obj_ip_addr].width - base_text_extent(sv.data(), uint32_t(sv.size()), 14, fonts[0]), ui_rects[ui_obj_ip_addr].y - 21.f, 14.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[0]);
		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_ip_addr ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
		ui_rects[ui_obj_ip_addr].x,
		ui_rects[ui_obj_ip_addr].y,
		ui_rects[ui_obj_ip_addr].width,
		ui_rects[ui_obj_ip_addr].height,
		line_bg_tex.get_texture_handle(), ui::rotation::upright, false);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::password)];
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ui_rects[ui_obj_password].x + ui_rects[ui_obj_password].width - base_text_extent(sv.data(), uint32_t(sv.size()), 14, fonts[0]), ui_rects[ui_obj_password].y - 21.f, 14.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[0]);
		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_password ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
		ui_rects[ui_obj_password].x,
		ui_rects[ui_obj_password].y,
		ui_rects[ui_obj_password].width,
		ui_rects[ui_obj_password].height,
		line_bg_tex.get_texture_handle(), ui::rotation::upright, false);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::nickname)];
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ui_rects[ui_obj_player_name].x + ui_rects[ui_obj_player_name].width - base_text_extent(sv.data(), uint32_t(sv.size()), 14, fonts[0]), ui_rects[ui_obj_player_name].y - 21.f, 14.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[0]);
		launcher::ogl::render_textured_rect(obj_under_mouse == ui_obj_player_name ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
		ui_rects[ui_obj_player_name].x,
		ui_rects[ui_obj_player_name].y,
		ui_rects[ui_obj_player_name].width,
		ui_rects[ui_obj_player_name].height,
		line_bg_tex.get_texture_handle(), ui::rotation::upright, false);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::singleplayer)];
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ui_rects[ui_obj_play_game].x + ui_rects[ui_obj_play_game].width - base_text_extent(sv.data(), uint32_t(sv.size()), 22, fonts[1]), ui_rects[ui_obj_play_game].y - 32.f, 22.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[1]);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::start_game)];
		float sg_x_pos = ui_rects[ui_obj_play_game].x + ui_rects[ui_obj_play_game].width / 2 - base_text_extent(sv.data(), uint32_t(sv.size()), 22, fonts[1]) / 2.0f;
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, sg_x_pos, ui_rects[ui_obj_play_game].y + 2.f, 22.0f, launcher::ogl::color3f{ 50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f }, fonts[1]);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::multiplayer)];
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ui_rects[ui_obj_join_game].x + ui_rects[ui_obj_join_game].width - base_text_extent(sv.data(), uint32_t(sv.size()), 22, fonts[1]), ui_rects[ui_obj_host_game].y - 32.f, 22.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[1]);

		// Join and host game buttons
		sv = launcher::localised_strings[uint8_t(launcher::string_index::host)];
		float hg_x_pos = ui_rects[ui_obj_host_game].x + ui_rects[ui_obj_host_game].width / 2 - base_text_extent(sv.data(), uint32_t(sv.size()), 22, fonts[1]) / 2.0f;
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, hg_x_pos, ui_rects[ui_obj_host_game].y + 2.f, 22.0f, launcher::ogl::color3f{ 50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f }, fonts[1]);
		sv = launcher::localised_strings[uint8_t(launcher::string_index::join)];
		float jg_x_pos = ui_rects[ui_obj_join_game].x + ui_rects[ui_obj_join_game].width / 2 - base_text_extent(sv.data(), uint32_t(sv.size()), 22, fonts[1]) / 2.0f;
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, jg_x_pos, ui_rects[ui_obj_join_game].y + 2.f, 22.0f, launcher::ogl::color3f{ 50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f }, fonts[1]);

		// Text fields
		float ia_x_pos = ui_rects[ui_obj_ip_addr].x + 6.f;// ui_rects[ui_obj_ip_addr].width - base_text_extent(ip_addr.c_str(), uint32_t(ip_addr.length()), 14, fonts[0]) - 4.f;
		launcher::ogl::render_new_text(ip_addr.c_str(), launcher::ogl::color_modification::none, ia_x_pos, ui_rects[ui_obj_ip_addr].y + 3.f, 14.0f, launcher::ogl::color3f{ 255.0f, 255.0f, 255.0f }, fonts[0]);
		float ps_x_pos = ui_rects[ui_obj_password].x + 6.f;
		launcher::ogl::render_new_text(password.c_str(), launcher::ogl::color_modification::none, ia_x_pos, ui_rects[ui_obj_password].y + 3.f, 14.0f, launcher::ogl::color3f{ 255.0f, 255.0f, 255.0f }, fonts[0]);
		float pn_x_pos = ui_rects[ui_obj_player_name].x + 6.f;// ui_rects[ui_obj_player_name].width - base_text_extent(player_name.c_str(), uint32_t(player_name.length()), 14, fonts[0]) - 4.f;
		launcher::ogl::render_new_text(player_name.c_str(), launcher::ogl::color_modification::none, pn_x_pos, ui_rects[ui_obj_player_name].y + 3.f, 14.0f, launcher::ogl::color3f{ 255.0f, 255.0f, 255.0f }, fonts[0]);

		sv = launcher::localised_strings[uint8_t(launcher::string_index::mod_list)];
		auto ml_xoffset = list_text_right_align - base_text_extent(sv.data(), uint32_t(sv.size()), 24, fonts[1]);
		launcher::ogl::render_new_text(sv.data(), launcher::ogl::color_modification::none, ml_xoffset, 45.0f, 24.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[1]);

		int32_t list_offset = launcher::frame_in_list * launcher::ui_list_count;

		for(int32_t i = 0; i < ui_list_count && list_offset + i < int32_t(mod_list.size()); ++i) {
			auto& mod_ref = mod_list[list_offset + i];
			if(i % 2 != 1) {
				launcher::ogl::render_textured_rect(
				launcher::ogl::color_modification::none,
				60,
				75 + ui_row_height * i,
				440,
				ui_row_height,
				launcher::line_bg_tex.get_texture_handle(), ui::rotation::upright, false);
			}
			if(mod_ref.mod_selected) {
				launcher::ogl::render_textured_rect(obj_under_mouse == ui_list_first + 3 * i + ui_list_checkbox ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].x,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].y,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].width,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].height,
				check_tex.get_texture_handle(), ui::rotation::upright, false);

				if(!nth_item_can_move_up(list_offset + i)) {
					launcher::ogl::render_textured_rect(launcher::ogl::color_modification::disabled,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].x,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].y,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].width,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].height,
					up_tex.get_texture_handle(), ui::rotation::upright, false);
				} else {
					launcher::ogl::render_textured_rect(obj_under_mouse == ui_list_first + 3 * i + ui_list_move_up ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].x,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].y,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].width,
					ui_rects[ui_list_first + 3 * i + ui_list_move_up].height,
					up_tex.get_texture_handle(), ui::rotation::upright, false);
				}
				if(!nth_item_can_move_down(list_offset + i)) {
					launcher::ogl::render_textured_rect(launcher::ogl::color_modification::disabled,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].x,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].y,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].width,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].height,
					down_tex.get_texture_handle(), ui::rotation::upright, false);
				} else {
					launcher::ogl::render_textured_rect(obj_under_mouse == ui_list_first + 3 * i + ui_list_move_down ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].x,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].y,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].width,
					ui_rects[ui_list_first + 3 * i + ui_list_move_down].height,
					down_tex.get_texture_handle(), ui::rotation::upright, false);
				}
			} else {
				launcher::ogl::render_textured_rect(obj_under_mouse == ui_list_first + 3 * i + ui_list_checkbox ? launcher::ogl::color_modification::interactable : launcher::ogl::color_modification::none,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].x,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].y,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].width,
				ui_rects[ui_list_first + 3 * i + ui_list_checkbox].height,
				empty_check_tex.get_texture_handle(), ui::rotation::upright, false);
			}

			auto xoffset = list_text_right_align - base_text_extent(mod_ref.name_.data(), uint32_t(mod_ref.name_.length()), 14, fonts[0]);

			launcher::ogl::render_new_text(mod_ref.name_.data(), launcher::ogl::color_modification::none, xoffset, 75.0f + 7.0f + i * ui_row_height, 14.0f, launcher::ogl::color3f{ 255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f }, fonts[0]);
		}

		SwapBuffers(opengl_window_dc);
	}

	bool is_low_surrogate(uint16_t char_code) noexcept {
		return char_code >= 0xDC00 && char_code <= 0xDFFF;
	}
	bool is_high_surrogate(uint16_t char_code) noexcept {
		return char_code >= 0xD800 && char_code <= 0xDBFF;
	}

	char process_utf16_to_win1250(wchar_t c) {
		if(c <= 127)
		return char(c);
		if(is_low_surrogate(c) || is_high_surrogate(c))
		return 0;
		char char_out = 0;
		WideCharToMultiByte(1250, 0, &c, 1, &char_out, 1, nullptr, nullptr);
		return char_out;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		if(message == WM_CREATE) {
			opengl_window_dc = GetDC(hwnd);

			create_opengl_context();

			glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
			glEnable(GL_LINE_SMOOTH);

			load_shaders();				// create shaders
			load_global_squares();		// create various squares to drive the shaders with

			//start globals
			simple_fs::identify_global_system_properties();
			simple_fs::file_system fs;
			simple_fs::add_root(fs, NATIVE("."));
			auto root = get_root(fs);

			uint8_t font_set_load = 0;
			LANGID lang = GetUserDefaultUILanguage();
			//lang = 0x0004;
			switch(lang & 0xff) {
				//case 0x0001:
				//	localised_strings = &ar_localised_strings[0];
				//	font_set_load = 2;
				//	break;
			case 0x0002:
				localised_strings = &bg_localised_strings[0];
				font_set_load = 3;
				break;
			case 0x0003:
				localised_strings = &ca_localised_strings[0];
				break;
			case 0x0004:
				localised_strings = &zh_localised_strings[0];
				font_set_load = 1;
				break;
			case 0x0005:
				localised_strings = &cs_localised_strings[0];
				break;
			case 0x0006:
				localised_strings = &da_localised_strings[0];
				break;
			case 0x0007:
				localised_strings = &de_localised_strings[0];
				break;
			case 0x0008:
				localised_strings = &el_localised_strings[0];
				break;
			case 0x0009:
				localised_strings = &en_localised_strings[0];
				break;
			case 0x000A:
				localised_strings = &es_localised_strings[0];
				break;
			case 0x000B:
				localised_strings = &fi_localised_strings[0];
				break;
			case 0x000C:
				localised_strings = &fr_localised_strings[0];
				break;
				//case 0x000D:
				//	localised_strings = &he_localised_strings[0];
				//	break;
			case 0x000E:
				localised_strings = &hu_localised_strings[0];
				break;
			case 0x000F:
				//localised_strings = &is_localised_strings[0];
				break;
			case 0x0010:
				localised_strings = &it_localised_strings[0];
				break;
			case 0x0011:
				//localised_strings = &ja_localised_strings[0];
				break;
			case 0x0012:
				//localised_strings = &ko_localised_strings[0];
				break;
			case 0x0016:
				localised_strings = &po_localised_strings[0];
				break;
			case 0x0013:
				localised_strings = &nl_localised_strings[0];
				break;
			case 0x0014:
				localised_strings = &no_localised_strings[0];
				break;
			case 0x0015:
				localised_strings = &pl_localised_strings[0];
				break;
			case 0x0018:
				localised_strings = &ro_localised_strings[0];
				break;
			case 0x0019:
				localised_strings = &ru_localised_strings[0];
				font_set_load = 3;
				break;
			case 0x001C:
				localised_strings = &sq_localised_strings[0];
				break;
			case 0x001D:
				localised_strings = &sv_localised_strings[0];
				break;
			case 0x001F:
				localised_strings = &tr_localised_strings[0];
				break;
			case 0x0022:
				localised_strings = &uk_localised_strings[0];
				font_set_load = 3;
				break;
			case 0x0025:
				localised_strings = &et_localised_strings[0];
				break;
			case 0x0026:
				localised_strings = &lv_localised_strings[0];
				break;
			case 0x0027:
				localised_strings = &lt_localised_strings[0];
				break;
			case 0x002A:
				localised_strings = &vi_localised_strings[0];
				break;
			case 0x002B:
				localised_strings = &hy_localised_strings[0];
				break;
			case 0x0039:
				localised_strings = &hi_localised_strings[0];
				break;
			default:
				break;
			}
			if(font_set_load == 0) {
				auto font_a = simple_fs::open_file(root, NATIVE("assets/fonts/LibreCaslonText_Regular.ttf"));
				if(font_a) {
					auto file_content = simple_fs::view_contents(*font_a);
					font_collection.load_font(fonts[0], file_content.data, file_content.file_size);
				}
				auto font_b = simple_fs::open_file(root, NATIVE("assets/fonts/LibreCaslonText_Italic.ttf"));
				if(font_b) {
					auto file_content = simple_fs::view_contents(*font_b);
					font_collection.load_font(fonts[1], file_content.data, file_content.file_size);
				}
			} else if(font_set_load == 1) { //chinese
				auto font_a = simple_fs::open_file(root, NATIVE("assets/fonts/STZHONGS.TTF"));
				if(font_a) {
					auto file_content = simple_fs::view_contents(*font_a);
					font_collection.load_font(fonts[0], file_content.data, file_content.file_size);
				}
				auto font_b = simple_fs::open_file(root, NATIVE("assets/fonts/STZHONGS.TTF"));
				if(font_b) {
					auto file_content = simple_fs::view_contents(*font_b);
					font_collection.load_font(fonts[1], file_content.data, file_content.file_size);
				}
			} else if(font_set_load == 2) { //arabic
				auto font_a = simple_fs::open_file(root, NATIVE("assets/fonts/NotoNaskhArabic_Bold.ttf"));
				if(font_a) {
					auto file_content = simple_fs::view_contents(*font_a);
					font_collection.load_font(fonts[0], file_content.data, file_content.file_size);
				}
				auto font_b = simple_fs::open_file(root, NATIVE("assets/fonts/NotoNaskhArabic_Regular.ttf"));
				if(font_b) {
					auto file_content = simple_fs::view_contents(*font_b);
					font_collection.load_font(fonts[1], file_content.data, file_content.file_size);
				}
			} else if(font_set_load == 3) { //cyrillic
				auto font_a = simple_fs::open_file(root, NATIVE("assets/fonts/NotoSerif_Regular.ttf"));
				if(font_a) {
					auto file_content = simple_fs::view_contents(*font_a);
					font_collection.load_font(fonts[0], file_content.data, file_content.file_size);
				}
				auto font_b = simple_fs::open_file(root, NATIVE("assets/fonts/NotoSerif_Regular.ttf"));
				if(font_b) {
					auto file_content = simple_fs::view_contents(*font_b);
					font_collection.load_font(fonts[1], file_content.data, file_content.file_size);
				}
			}

			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_bg.png"), fs, bg_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_left.png"), fs, left_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_right.png"), fs, right_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_close.png"), fs, close_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_big_button.png"), fs, big_button_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_big_left.png"), fs, big_l_button_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_big_right.png"), fs, big_r_button_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_no_check.png"), fs, empty_check_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_check.png"), fs, check_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_up.png"), fs, up_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_down.png"), fs, down_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_line_bg.png"), fs, line_bg_tex, false);
			::ogl::load_file_and_return_handle(NATIVE("assets/launcher_warning.png"), fs, warning_tex, false);
			game_dir_not_found = false;
			{
				auto f = simple_fs::peek_file(root, NATIVE("v2game.exe"));
				if(!f) {
					f = simple_fs::peek_file(root, NATIVE("victoria2.exe"));
					if(!f) {
						game_dir_not_found = true;
						reports::write_debug("Game directory not found\n");
					}
				}
			}
			auto mod_dir = simple_fs::open_directory(root, NATIVE("mod"));
			parsers::error_handler err("");
			for(auto& f : simple_fs::list_files(mod_dir, NATIVE(".mod"))) {
				if(auto of = simple_fs::open_file(f); of) {
					auto content = view_contents(*of);
					parsers::token_generator gen(content.data, content.data + content.file_size);
					mod_list.push_back(parsers::parse_mod_file(gen, err, parsers::mod_file_context{}));
				}
			}
			reports::write_debug("Finished launcher setup\n");
			return 1;
		} else {
			switch(message) {
			case WM_DPICHANGED:
			{
				dpi = float(HIWORD(wParam));
				auto lprcNewScale = reinterpret_cast<RECT*>(lParam);

				scaling_factor = float(lprcNewScale->right - lprcNewScale->left) / base_width;

				SetWindowPos(hwnd, nullptr, lprcNewScale->left, lprcNewScale->top,
				lprcNewScale->right - lprcNewScale->left, lprcNewScale->bottom - lprcNewScale->top,
				SWP_NOZORDER | SWP_NOACTIVATE);

				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
				break;
			}
			case WM_NCMOUSEMOVE:
			{
				RECT rcWindow;
				GetWindowRect(hwnd, &rcWindow);
				auto x = GET_X_LPARAM(lParam);
				auto y = GET_Y_LPARAM(lParam);

				POINTS adj{ SHORT(x - rcWindow.left), SHORT(y - rcWindow.top) };
				std::memcpy(&lParam, &adj, sizeof(LPARAM));

				mouse_x = int32_t(float(GET_X_LPARAM(lParam)) / scaling_factor);
				mouse_y = int32_t(float(GET_Y_LPARAM(lParam)) / scaling_factor);
				if(update_under_mouse()) {
					InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
				}
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				mouse_x = int32_t(float(GET_X_LPARAM(lParam)) / scaling_factor);
				mouse_y = int32_t(float(GET_Y_LPARAM(lParam)) / scaling_factor);
				if(update_under_mouse()) {
					InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
				}
				return 0;
			}
			case WM_LBUTTONDOWN:
			{
				mouse_click();
				return 0;
			}
			case WM_NCCALCSIZE:
				if(wParam == TRUE)
					return 0;
				break;
			case WM_NCHITTEST:
			{
				POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
				RECT rcWindow;
				GetWindowRect(hwnd, &rcWindow);

				if(ptMouse.x <= int32_t(rcWindow.left + caption_width * scaling_factor)
				&& ptMouse.y <= int32_t(rcWindow.top + caption_height * scaling_factor)) {
					return HTCAPTION;
				}
				return HTCLIENT;
			}
			case WM_PAINT:
			case WM_DISPLAYCHANGE:
			{
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				render();
				EndPaint(hwnd, &ps);
				return 0;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				return 1;
			case WM_KEYDOWN:
				if(GetKeyState(VK_CONTROL) & 0x8000) {
					if(wParam == L'v' || wParam == L'V') {
						if(!IsClipboardFormatAvailable(CF_TEXT))
							return 0;
						if(!OpenClipboard(m_hwnd))
							return 0;

						auto hglb = GetClipboardData(CF_TEXT);
						if(hglb != nullptr) {
							auto lptstr = GlobalLock(hglb);
							if(lptstr != nullptr) {
								std::string cb_data((char*)lptstr);
								while(cb_data.length() > 0 && isspace(cb_data.back())) {
									cb_data.pop_back();
								}
								ip_addr = cb_data;
								GlobalUnlock(hglb);
							}
						}
						CloseClipboard();
					}
				}
				return 0;
			case WM_NCCREATE:
			{
				if(HINSTANCE hUser32dll = LoadLibrary(L"User32.dll"); hUser32dll) {
					auto pSetProcessDpiAwarenessContext = (decltype(&SetProcessDpiAwarenessContext))GetProcAddress(hUser32dll, "SetProcessDpiAwarenessContext");
					if(pSetProcessDpiAwarenessContext == NULL) {
						// not present, so have to call this
						auto pEnableNonClientDpiScaling = (decltype(&EnableNonClientDpiScaling))GetProcAddress(hUser32dll, "EnableNonClientDpiScaling");
						if(pEnableNonClientDpiScaling != NULL) {
							pEnableNonClientDpiScaling(hwnd); //windows 10
						}
					}
					FreeLibrary(hUser32dll);
				}
				break;
			}
			case WM_CHAR:
			{
				if(GetKeyState(VK_CONTROL) & 0x8000) {

				} else {
					char turned_into = process_utf16_to_win1250(wchar_t(wParam));
					if(turned_into) {
						if(obj_under_mouse == ui_obj_ip_addr) {
							if(turned_into == '\b') {
								if(!ip_addr.empty()) {
									ip_addr.pop_back();
								}
							} else if(turned_into >= 32 && turned_into != '\t' && turned_into != ' ' && ip_addr.size() < 46) {
								ip_addr.push_back(turned_into);
							}
						} else if(obj_under_mouse == ui_obj_player_name) {
							if(turned_into == '\b') {
								if(!player_name.empty()) {
									player_name.pop_back();
									save_playername();
								}
							} else if(turned_into >= 32 && turned_into != '\t' && turned_into != ' ' && player_name.size() < 24) {
								player_name.push_back(turned_into);
								save_playername();
							}
						} else if(obj_under_mouse == ui_obj_password) {
							if(turned_into == '\b') {
								if(!password.empty()) {
									password.pop_back();
								}
							} else if(turned_into >= 32 && turned_into != '\t' && turned_into != ' ' && password.size() < 16) {
								password.push_back(turned_into);
							}
						}
					}
				}
				InvalidateRect(HWND(m_hwnd), nullptr, FALSE);
				return 0;
			}
			default:
				break;

			}
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
} // end launcher namespace

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPWSTR /*lpCmdLine*/,
	int /*nCmdShow*/
) {
#ifdef _DEBUG
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
#endif

	// Workaround for old machines
	if(HINSTANCE hUser32dll = LoadLibrary(L"User32.dll"); hUser32dll) {
		auto pSetProcessDpiAwarenessContext = (decltype(&SetProcessDpiAwarenessContext))GetProcAddress(hUser32dll, "SetProcessDpiAwarenessContext");
		if(pSetProcessDpiAwarenessContext != NULL) {
			pSetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
		} else {
			// windows 8.1 (not present on windows 8 and only available on desktop apps)
			if(HINSTANCE hShcoredll = LoadLibrary(L"Shcore.dll"); hShcoredll) {
				auto pSetProcessDpiAwareness = (decltype(&SetProcessDpiAwareness))GetProcAddress(hShcoredll, "SetProcessDpiAwareness");
				if(pSetProcessDpiAwareness != NULL) {
					pSetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
				} else {
					SetProcessDPIAware(); //vista+
				}
				FreeLibrary(hShcoredll);
			} else {
				SetProcessDPIAware(); //vista+
			}
		}
		FreeLibrary(hUser32dll);
	}

	if(!SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		return 0;

	WNDCLASSEX wcex = { };
	wcex.cbSize = UINT(sizeof(WNDCLASSEX));
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = launcher::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = hInstance;
	wcex.hIcon = (HICON)LoadImage(GetModuleHandleW(nullptr), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = NATIVE("vce_launcher_class");

	if(RegisterClassEx(&wcex) == 0) {
		window::emit_error_message("Unable to register window class", true);
	}

	// Load from user settings
	auto settings_location = simple_fs::get_or_create_settings_directory();
	if(auto player_name_file = simple_fs::open_file(settings_location, NATIVE("player_name.dat")); player_name_file) {
		auto contents = simple_fs::view_contents(*player_name_file);
		const sys::player_name *p = (const sys::player_name*)contents.data;
		if(contents.file_size >= sizeof(*p)) {
			launcher::player_name = std::string(p->data);
		}
	} else {
		srand(time(NULL));
		launcher::player_name = "Player" + std::to_string(int32_t(rand() & 0xff));
	}

	launcher::m_hwnd = CreateWindowEx(
		0,
		L"vce_launcher_class",
		L"Launch Victoria Community's Engine",
		WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		880,
		540,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if(launcher::m_hwnd) {
		if(HINSTANCE hUser32dll = LoadLibrary(L"User32.dll"); hUser32dll) {
			auto pGetDpiForWindow = (decltype(&GetDpiForWindow))GetProcAddress(hUser32dll, "GetDpiForWindow");
			if(pGetDpiForWindow != NULL) {
				launcher::dpi = float(pGetDpiForWindow((HWND)(launcher::m_hwnd)));
			} else {
				launcher::dpi = 96.0f; //100%, default
			}
			FreeLibrary(hUser32dll);
		}

		auto monitor_handle = MonitorFromWindow((HWND)(launcher::m_hwnd), MONITOR_DEFAULTTOPRIMARY);
		MONITORINFO mi;
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(monitor_handle, &mi);

		auto vert_space = mi.rcWork.bottom - mi.rcWork.top;
		float rough_scale = float(vert_space) / 1080.0f;
		if(rough_scale >= 1.0f) {
			launcher::scaling_factor = std::round(rough_scale);
		} else {
			launcher::scaling_factor = std::round(rough_scale * 4.0f) / 4.0f;
		}

		SetWindowPos(
			(HWND)(launcher::m_hwnd),
			NULL,
			NULL,
			NULL,
			int(launcher::scaling_factor * launcher::base_width),
			int(launcher::scaling_factor * launcher::base_height),
			SWP_NOMOVE | SWP_FRAMECHANGED | SWP_DRAWFRAME);

		ShowWindow((HWND)(launcher::m_hwnd), SW_SHOWNORMAL);
		UpdateWindow((HWND)(launcher::m_hwnd));
	}

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return 0;
}
