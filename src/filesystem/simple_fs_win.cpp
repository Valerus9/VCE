#include "simple_fs.hpp"
#include "simple_fs_types_win.hpp"
#include "text.hpp"
#include "reports.hpp"

#ifndef UNICODE
#define UNICODE
#endif
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "Windows.h"
#include "Memoryapi.h"
#include "Shlobj.h"
#include <cstdlib>
#include "pdqsort.h"

namespace simple_fs {
	static native_string steam_path;

	void set_steam_path(native_string path) {
		steam_path = path;
	}

	native_string query_steam_path() {
		WCHAR szBuffer[4096]; // excessive but just in case someone has their game directory NESTED
		HKEY hKey;
		LSTATUS res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Paradox Interactive\\Victoria 2", 0, KEY_READ, &hKey); // open key if key exists
		if(res == ERROR_SUCCESS) { // victoria 2 could not be located, see the "Interested in Contributing?" page on the github.
			DWORD lnBuffer = 4096;
			res = RegQueryValueEx(hKey, L"path", NULL, NULL, LPBYTE(szBuffer), &lnBuffer);
			if(res == ERROR_SUCCESS) { // victoria 2 could not be located, see the "Interested in Contributing?" page on the github.
				szBuffer[lnBuffer - 1] = 0;
				RegCloseKey(hKey);
				return native_string(szBuffer);
			}
		}
		return native_string();
	}

	int CALLBACK steam_path_browse_callback_proc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
		if(uMsg == BFFM_INITIALIZED) {
			SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		}
		return 0;
	}

	std::string user_browse_for_steam_path() {
		std::string str;
		WCHAR path[MAX_PATH];
		BROWSEINFO bi = { 0 };
		bi.lpszTitle = NATIVE("Select the Victoria 2 directory...");
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
		bi.lpfn = steam_path_browse_callback_proc;
		LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
		if(pidl != 0) {
			//get the name of the folder and put it in path
			SHGetPathFromIDList(pidl, path);
			//free memory used
			IMalloc* imalloc = 0;
			if(SUCCEEDED(SHGetMalloc(&imalloc))) {
				imalloc->Free(pidl);
				imalloc->Release();
			}
			return text::native_to_utf8(path);
		}
		return std::string();
	}

	/*	Whetever the Victoria 2 game install could be located or not (by probing v2game.exe's existence) */
	bool can_locate_game_install() {
		simple_fs::file_system fs;
		simple_fs::add_root(fs, NATIVE("."));
		auto root = simple_fs::get_root(fs);
		return simple_fs::peek_file(root, NATIVE("v2game.exe")).has_value();
	}

	void identify_global_system_properties() {
		auto root = directory(nullptr, NATIVE("."));
		// victoria 2 not found in current directory - try fallback to steam path
		if(!can_locate_game_install()) {
			// game_dir.txt will override anything that was queried, if it's present
			if(auto game_dir_file = simple_fs::open_file(root, NATIVE("game_dir.txt")); game_dir_file) {
				auto contents = simple_fs::view_contents(*game_dir_file);
				std::string str(contents.data, contents.data + contents.file_size);
				simple_fs::set_steam_path(text::utf8_to_native(str));
			}
			// Try querying from registry
			if(steam_path.empty() && !can_locate_game_install()) {
				steam_path = query_steam_path();
			}
			// No registry -> fallback to asking the user and create a new game_dir.txt
			if(steam_path.empty() && !can_locate_game_install() && !simple_fs::peek_file(root, NATIVE("game_dir.txt"))) {
				auto str = user_browse_for_steam_path();
				if(str.size() > 0) {
					simple_fs::write_file(root, NATIVE("game_dir.txt"), str.c_str(), uint32_t(str.size()));
					simple_fs::set_steam_path(text::utf8_to_native(str));
				}
			}
		}
	}

	file::~file() {
		if(mapping_handle) {
			if(content.data)
			UnmapViewOfFile(content.data);
			CloseHandle(mapping_handle);
		}
		if(file_handle != INVALID_HANDLE_VALUE) {
			CloseHandle(file_handle);
		}
	}

	file::file(file&& other) noexcept : absolute_path(std::move(other.absolute_path)) {
		mapping_handle = other.mapping_handle;
		file_handle = other.file_handle;
		other.mapping_handle = nullptr;
		other.file_handle = INVALID_HANDLE_VALUE;
		content = other.content;
	}
	void file::operator=(file&& other) noexcept {
		mapping_handle = other.mapping_handle;
		file_handle = other.file_handle;
		other.mapping_handle = nullptr;
		other.file_handle = INVALID_HANDLE_VALUE;
		content = other.content;
		absolute_path = std::move(other.absolute_path);
	}

	file::file(native_string const& full_path) {
		file_handle = CreateFileW(full_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
		if(file_handle != INVALID_HANDLE_VALUE) {
			absolute_path = full_path;
			mapping_handle = CreateFileMappingW(file_handle, nullptr, PAGE_READONLY, 0, 0, nullptr);
			if(mapping_handle) {
				content.data = (char const*)MapViewOfFile(mapping_handle, FILE_MAP_READ, 0, 0, 0);
				if(content.data) {
					_LARGE_INTEGER pvalue;
					GetFileSizeEx(file_handle, &pvalue);
					content.file_size = uint32_t(pvalue.QuadPart);
				}
			}
		}
	}
	file::file(HANDLE file_handle, native_string const& full_path) : file_handle(file_handle) {
		absolute_path = full_path;
		mapping_handle = CreateFileMappingW(file_handle, nullptr, PAGE_READONLY, 0, 0, nullptr);
		if(mapping_handle) {
			content.data = (char const*)MapViewOfFile(mapping_handle, FILE_MAP_READ, 0, 0, 0);
			if(content.data) {
				_LARGE_INTEGER pvalue;
				GetFileSizeEx(file_handle, &pvalue);
				content.file_size = uint32_t(pvalue.QuadPart);
			}
		}
	}

	std::optional<file> open_file(unopened_file const& f) {
		std::optional<file> result(file{ f.absolute_path });
		if(!result->content.data) {
			result = std::optional<file>{};
		}
		return result;
	}

	void reset(file_system& fs) {
		fs.ordered_roots.clear();
		fs.ignored_paths.clear();
	}

	void add_root(file_system& fs, native_string_view root_path) {
		fs.ordered_roots.emplace_back(root_path);
	}

	void add_relative_root(file_system& fs, native_string_view root_path) {
		WCHAR module_name[MAX_PATH] = {};
		int32_t path_used = GetModuleFileNameW(nullptr, module_name, MAX_PATH);
		while(path_used >= 0 && module_name[path_used] != L'\\') {
			module_name[path_used] = 0;
			--path_used;
		}
		fs.ordered_roots.push_back(native_string(module_name) + native_string(root_path));
	}

	directory get_root(file_system const& fs) {
		return directory(&fs, NATIVE(""));
	}

	native_string extract_state(file_system const& fs) {
		native_string result;
		for(auto const& str : fs.ordered_roots) {
			result += NATIVE(";") + str;
		}
		result += NATIVE("?");
		for(auto const& replace_path : fs.ignored_paths) {
			result += replace_path + NATIVE(";");
		}
		return result;
	}

	void restore_state(file_system& fs, native_string_view data) {
		simple_fs::reset(fs);
		auto break_position = std::find(data.data(), data.data() + data.length(), NATIVE('?'));
		// Parse ordered roots
		{
			auto position = data.data() + 1;
			auto end = break_position;
			while(position < end) {
				auto next_semicolon = std::find(position, end, NATIVE(';'));
				fs.ordered_roots.emplace_back(position, next_semicolon);
				position = next_semicolon + 1;
			}
		}
		// Replaced paths
		{
			auto position = break_position + 1;
			auto end = data.data() + data.length();
			while(position < end) {
				auto next_semicolon = std::find(position, end, NATIVE(';'));
				fs.ignored_paths.emplace_back(position, next_semicolon);
				position = next_semicolon + 1;
			}
		}
	}

	namespace impl {
		bool contains_non_ascii(native_char const* str) {
			for(auto c = str; *c != 0; ++c) {
				if(int32_t(*c) > 127 || int32_t(*c) < 0) {
					return true;
				}
			}
			return false;
		}
	} // namespace impl

	bool list_files_compare_func(native_char const& char1, native_char const& char2) {
		auto const to_alpha_prec = [](native_char const& ch) -> native_char {
			switch(ch) {
				case NATIVE('0'): return 123;
				case NATIVE('1'): return 124;
				case NATIVE('2'): return 125;
				case NATIVE('3'): return 126;
				case NATIVE('4'): return 127;
				case NATIVE('5'): return native_char(128);
				case NATIVE('6'): return native_char(129);
				case NATIVE('7'): return native_char(130);
				case NATIVE('8'): return native_char(131);
				case NATIVE('9'): return native_char(132);
				case 123: return '0';
				case 124: return '1';
				case 125: return '2';
				case 126: return '3';
				case 127: return '4';
				case 128: return '5';
				case 129: return '6';
				case 130: return '7';
				case 131: return '8';
				case 132: return '9';
			}
			return ch;
		};
		return to_alpha_prec(char1) < to_alpha_prec(char2);
	}

	std::vector<unopened_file> list_files(directory const& dir, native_char const* extension) {
		std::vector<unopened_file> accumulated_results;
		auto r_steam_path = steam_path + NATIVE("\\");
		if(dir.parent_system) {
			for(size_t i = dir.parent_system->ordered_roots.size(); i-- > 0;) {
				auto const dir_path = dir.parent_system->ordered_roots[i] + dir.relative_path;
				auto const appended_path = dir_path + NATIVE("\\*") + extension;
				if(simple_fs::is_ignored_path(*dir.parent_system, appended_path)) {
					continue;
				}
				WIN32_FIND_DATAW find_result;
				auto find_handle = FindFirstFileExW(appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
				if(find_handle != INVALID_HANDLE_VALUE) {
					do {
						if(!(find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
							if(auto search_result = std::find_if(accumulated_results.begin(), accumulated_results.end(), [n = find_result.cFileName](auto const& f) { return f.file_name.compare(n) == 0; }); search_result == accumulated_results.end()) {
								auto const rel_path = dir_path + NATIVE("\\");
								accumulated_results.emplace_back(rel_path + find_result.cFileName, find_result.cFileName);
							}
						}
					} while(FindNextFileW(find_handle, &find_result) != 0);
					FindClose(find_handle);
				}
				if(steam_path.size() > 0) {
					std::memset(&find_result, 0, sizeof(WIN32_FIND_DATAW));
					auto const r_appended_path = r_steam_path + dir_path + NATIVE("\\*") + extension;
					find_handle = FindFirstFileExW(r_appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
					if(find_handle != INVALID_HANDLE_VALUE) {
						do {
							if(!(find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
								if(auto search_result = std::find_if(accumulated_results.begin(), accumulated_results.end(), [n = find_result.cFileName](auto const& f) { return f.file_name.compare(n) == 0; }); search_result == accumulated_results.end()) {
									auto const rel_path = r_steam_path + dir_path + NATIVE("\\");
									accumulated_results.emplace_back(rel_path + find_result.cFileName, find_result.cFileName);
								}
							}
						} while(FindNextFileW(find_handle, &find_result) != 0);
						FindClose(find_handle);
					}
				}
			}
		} else {
			auto const appended_path = dir.relative_path + NATIVE("\\*") + extension;
			WIN32_FIND_DATAW find_result;
			auto find_handle = FindFirstFileExW(appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
			if(find_handle != INVALID_HANDLE_VALUE) {
				do {
					if(!(find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
						auto const rel_path = dir.relative_path + NATIVE("\\");
						accumulated_results.emplace_back(rel_path + find_result.cFileName, find_result.cFileName);
					}
				} while(FindNextFileW(find_handle, &find_result) != 0);
				FindClose(find_handle);
			}
			if(steam_path.size() > 0) {
				std::memset(&find_result, 0, sizeof(WIN32_FIND_DATAW));
				auto const r_appended_path = r_steam_path + dir.relative_path + NATIVE("\\*") + extension;
				find_handle = FindFirstFileExW(r_appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
				if(find_handle != INVALID_HANDLE_VALUE) {
					do {
						if(!(find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
							auto const rel_path = r_steam_path + dir.relative_path + NATIVE("\\");
							accumulated_results.emplace_back(rel_path + find_result.cFileName, find_result.cFileName);
						}
					} while(FindNextFileW(find_handle, &find_result) != 0);
					FindClose(find_handle);
				}
			}
		}
		pdqsort(accumulated_results.begin(), accumulated_results.end(), [](unopened_file const& a, unopened_file const& b) {
			return std::lexicographical_compare(std::begin(a.file_name), std::end(a.file_name), std::begin(b.file_name), std::end(b.file_name), list_files_compare_func);
		});
		return accumulated_results;
	}
	std::vector<directory> list_subdirectories(directory const& dir) {
		std::vector<directory> accumulated_results;
		auto r_steam_path = steam_path + NATIVE("\\");
		if(dir.parent_system) {
			for(size_t i = dir.parent_system->ordered_roots.size(); i-- > 0;) {
				auto const dir_path = dir.parent_system->ordered_roots[i] + dir.relative_path;
				auto const appended_path = dir_path + NATIVE("\\*");
				if(simple_fs::is_ignored_path(*dir.parent_system, appended_path)) {
					continue;
				}
				WIN32_FIND_DATAW find_result;
				auto find_handle = FindFirstFileExW(appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
				if(find_handle != INVALID_HANDLE_VALUE) {
					do {
						if((find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
							auto const rel_name = dir.relative_path + NATIVE("\\") + find_result.cFileName;
							if(find_result.cFileName[0] != NATIVE('.') && std::find_if(accumulated_results.begin(), accumulated_results.end(), [&rel_name](auto const& s) { return s.relative_path.compare(rel_name) == 0; }) == accumulated_results.end()) {
								accumulated_results.emplace_back(dir.parent_system, rel_name);
							}
						}
					} while(FindNextFileW(find_handle, &find_result) != 0);
					FindClose(find_handle);
				}
				if(steam_path.size() > 0) {
					std::memset(&find_result, 0, sizeof(WIN32_FIND_DATAW));
					auto const r_appended_path = r_steam_path + dir_path + NATIVE("\\*");
					find_handle = FindFirstFileExW(r_appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
					if(find_handle != INVALID_HANDLE_VALUE) {
						do {
							if((find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
								auto const rel_name = dir.relative_path + NATIVE("\\") + find_result.cFileName;
								if(find_result.cFileName[0] != NATIVE('.') && std::find_if(accumulated_results.begin(), accumulated_results.end(), [&rel_name](auto const& s) { return s.relative_path.compare(rel_name) == 0; }) == accumulated_results.end()) {
									accumulated_results.emplace_back(dir.parent_system, rel_name);
								}
							}
						} while(FindNextFileW(find_handle, &find_result) != 0);
						FindClose(find_handle);
					}
				}
			}
		} else {
			auto const appended_path = dir.relative_path + NATIVE("\\*");
			WIN32_FIND_DATAW find_result;
			auto find_handle = FindFirstFileExW(appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
			if(find_handle != INVALID_HANDLE_VALUE) {
				do {
					if((find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
						auto const rel_name = dir.relative_path + NATIVE("\\") + find_result.cFileName;
						if(find_result.cFileName[0] != NATIVE('.')) {
							accumulated_results.emplace_back(nullptr, rel_name);
						}
					}
				} while(FindNextFileW(find_handle, &find_result) != 0);
				FindClose(find_handle);
			}
			if(steam_path.size() > 0) {
				std::memset(&find_result, 0, sizeof(WIN32_FIND_DATAW));
				auto const r_appended_path = r_steam_path + dir.relative_path + NATIVE("\\*");
				find_handle = FindFirstFileExW(r_appended_path.c_str(), FindExInfoBasic, &find_result, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
				if(find_handle != INVALID_HANDLE_VALUE) {
					do {
						if((find_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !impl::contains_non_ascii(find_result.cFileName)) {
							auto const rel_name = dir.relative_path + NATIVE("\\") + find_result.cFileName;
							if(find_result.cFileName[0] != NATIVE('.')) {
								accumulated_results.emplace_back(nullptr, rel_name);
							}
						}
					} while(FindNextFileW(find_handle, &find_result) != 0);
					FindClose(find_handle);
				}
			}
		}
		pdqsort(accumulated_results.begin(), accumulated_results.end(), [](directory const& a, directory const& b) {
			return std::lexicographical_compare(std::begin(a.relative_path), std::end(a.relative_path), std::begin(b.relative_path), std::end(b.relative_path), [](native_char const& char1, native_char const& char2) { return tolower(char1) < tolower(char2); });
		});
		return accumulated_results;
	}

	directory open_directory(directory const& dir, native_string_view directory_name) {
		return directory(dir.parent_system, dir.relative_path + NATIVE('\\') + native_string(directory_name));
	}

	native_string get_full_name(directory const& dir) {
		return dir.relative_path;
	}

	std::optional<native_string> get_path_to_file(directory const& dir, native_string_view file_name) {
		if(dir.parent_system) {
			for(size_t i = dir.parent_system->ordered_roots.size(); i-- > 0;) {
				native_string dir_path = dir.parent_system->ordered_roots[i] + dir.relative_path;
				return dir_path + NATIVE('\\') + native_string(file_name);
			}
		} else {
			return dir.relative_path + NATIVE('\\') + native_string(file_name);
		}
		return std::optional<native_string>{};
	}

	std::optional<file> open_file(directory const& dir, native_string_view file_name) {
		auto r_steam_path = steam_path + NATIVE("\\");
		if(dir.parent_system) {
			for(size_t i = dir.parent_system->ordered_roots.size(); i-- > 0;) {
				auto const dir_path = dir.parent_system->ordered_roots[i] + dir.relative_path;
				auto const full_path = dir_path + NATIVE('\\') + native_string(file_name);
				if(simple_fs::is_ignored_path(*dir.parent_system, full_path)) {
					continue;
				}
				HANDLE file_handle = CreateFileW(full_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
				if(file_handle != INVALID_HANDLE_VALUE) {
					return std::optional<file>(file(file_handle, full_path));
				}
				if(steam_path.size() > 0) {
					auto const r_full_path = r_steam_path + dir_path + NATIVE('\\') + native_string(file_name);
					file_handle = CreateFileW(r_full_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
					if(file_handle != INVALID_HANDLE_VALUE) {
						return std::optional<file>(file(file_handle, r_full_path));
					}
				}
			}
		} else {
			auto const full_path = dir.relative_path + NATIVE('\\') + native_string(file_name);
			HANDLE file_handle = CreateFileW(full_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
			if(file_handle != INVALID_HANDLE_VALUE) {
				return std::optional<file>(file(file_handle, full_path));
			}
			if(steam_path.size() > 0) {
				auto const r_full_path = r_steam_path + dir.relative_path + NATIVE('\\') + native_string(file_name);
				file_handle = CreateFileW(r_full_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
				if(file_handle != INVALID_HANDLE_VALUE) {
					return std::optional<file>(file(file_handle, r_full_path));
				}
			}
		}
		return std::optional<file>{};
	}

	std::optional<unopened_file> peek_file(directory const& dir, native_string_view file_name) {
		auto r_steam_path = steam_path + NATIVE("\\");
		if(dir.parent_system) {
			for(size_t i = dir.parent_system->ordered_roots.size(); i-- > 0;) {
				auto const dir_path = dir.parent_system->ordered_roots[i] + dir.relative_path;
				auto const full_path = dir_path + NATIVE('\\') + native_string(file_name);
				if(simple_fs::is_ignored_path(*dir.parent_system, full_path)) {
					continue;
				}
				DWORD dwAttrib = GetFileAttributesW(full_path.c_str());
				if(dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
					return std::optional<unopened_file>(unopened_file(full_path, file_name));
				}
				if(steam_path.size() > 0) {
					auto const r_full_path = r_steam_path + dir_path + NATIVE('\\') + native_string(file_name);
					dwAttrib = GetFileAttributesW(r_full_path.c_str());
					if(dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
						return std::optional<unopened_file>(unopened_file(r_full_path, file_name));
					}
				}
			}
		} else {
			auto const full_path = dir.relative_path + NATIVE('\\') + native_string(file_name);
			DWORD dwAttrib = GetFileAttributesW(full_path.c_str());
			if(dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
				return std::optional<unopened_file>(unopened_file(full_path, file_name));
			}
			if(steam_path.size() > 0) {
				auto const r_full_path = r_steam_path + dir.relative_path + NATIVE('\\') + native_string(file_name);
				dwAttrib = GetFileAttributesW(r_full_path.c_str());
				if(dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
					return std::optional<unopened_file>(unopened_file(r_full_path, file_name));
				}
			}
		}
		return std::optional<unopened_file>{};
	}

	void add_ignore_path(file_system& fs, native_string_view replaced_path) {
		fs.ignored_paths.emplace_back(correct_slashes(replaced_path));
	}

	std::vector<native_string> list_roots(file_system const& fs) {
		return fs.ordered_roots;
	}

	bool is_ignored_path(file_system const& fs, native_string_view path) {
		for(auto const& replace_path : fs.ignored_paths) {
			if(path.starts_with(replace_path))
			return true;
		}
		return false;
	}

	native_string get_full_name(unopened_file const& f) {
		return f.absolute_path;
	}

	native_string get_file_name(unopened_file const& f) {
		return f.file_name;
	}

	native_string get_full_name(file const& f) {
		return f.absolute_path;
	}

	void write_file(directory const& dir, native_string_view file_name, char const* file_data, uint32_t file_size) {
		if(dir.parent_system) {
			reports::write_debug("Undefined parent system\n");
			std::abort();
		}

		native_string full_path = dir.relative_path + NATIVE('\\') + native_string(file_name);
		HANDLE file_handle = CreateFileW(full_path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
		if(file_handle != INVALID_HANDLE_VALUE) {
			DWORD written_bytes = 0;
			WriteFile(file_handle, file_data, DWORD(file_size), &written_bytes, nullptr);
			(void)written_bytes;
			SetEndOfFile(file_handle);
			CloseHandle(file_handle);
		}
	}

	file_contents view_contents(file const& f) {
		return f.content;
	}

	directory get_or_create_settings_directory() {
		wchar_t* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	directory get_or_create_save_game_directory() {
		wchar_t* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
			base_path += NATIVE("\\saved games");
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	directory get_or_create_templates_directory() {
		native_char* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
			base_path += NATIVE("\\templates");
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	directory get_or_create_oos_directory() {
		native_char* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
			base_path += NATIVE("\\oos");
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	directory get_or_create_scenario_directory() {
		native_char* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
			base_path += NATIVE("\\scenarios");
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	directory get_or_create_data_dumps_directory() {
		native_char* local_path_out = nullptr;
		native_string base_path;
		if(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &local_path_out) == S_OK) {
			base_path = native_string(local_path_out) + NATIVE("\\Victoria Community's Engine");
		}
		CoTaskMemFree(local_path_out);
		if(base_path.length() > 0) {
			CreateDirectoryW(base_path.c_str(), nullptr);
			base_path += NATIVE("\\data_dumps");
			CreateDirectoryW(base_path.c_str(), nullptr);
		}
		return directory(nullptr, base_path);
	}

	std::string remove_double_backslashes(std::string_view data_in) {
		std::string res;
		res.reserve(data_in.size());
		for(uint32_t i = 0; i < data_in.size(); ++i) {
			if(data_in[i] == '\\') {
				res += '\\';
				if(i + 1 < data_in.size() && data_in[i + 1] == '\\') {
					++i;
				}
			} else {
				res += data_in[i];
			}
		}
		return res;
	}

	native_string correct_slashes(native_string_view path) {
		native_string res;
		res.reserve(path.size());
		for(size_t i = 0; i < path.size(); i++) {
			res += path[i] == '/' ? '\\' : path[i];
		}
		return res;
	}

	uint64_t get_write_time(file const& f) {
		FILETIME ft;
		GetFileTime(f.file_handle, NULL, NULL, &ft);
		return uint64_t(ft.dwLowDateTime) | (uint64_t(ft.dwHighDateTime) << 32);
	}
} // namespace simple_fs
