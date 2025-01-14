/*
BASIC bm_font example implementation with Kerning, for C++ and OpenGL 2.0

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
--------------------------------------------------------------------------------
These editors can be used to generate BMFonts:
 • http://www.angelcode.com/products/bmfont/ (free, windows)
 • http://glyphdesigner.71squared.com/ (commercial, mac os x)
 • http://www.n4te.com/hiero/hiero.jnlp (free, java, multiplatform)
 • http://slick.cokeandcode.com/demos/hiero.jnlp (free, java, multiplatform)

Some code below based on code snippets from this gamedev posting:

http://www.gamedev.net/topic/330742-quick-tutorial-variable-width-bitmap-fonts/

Although I'm giving this away, I'd appreciate an email with fixes or better code!

aaedev@gmail.com 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdarg.h>
#include "glad.h"
#include "system/system_state.hpp"
#include "bmfont.hpp"
#include "texture.hpp"
#include "fonts.hpp"
#include "parsers.hpp"
#include "parsers_declarations.hpp"

#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

#include "parsers.hpp"

namespace parsers {
	struct bmfont_file_context {
		scenario_building_context& outer_context;
		text::bm_font& font;
		uint8_t char_id = 0;
		int32_t first = 0;
		int32_t second = 0;

	bmfont_file_context(scenario_building_context& outer_context, text::bm_font& font) : outer_context(outer_context), font(font) { }
	};
	struct bmfont_file {
		void x(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].x = value;
		}
		void y(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].y = value;
		}
		void xadvance(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].x_advance = value;
		}
		void xoffset(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].x_offset = value;
		}
		void yoffset(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].y_offset = value;
		}
		void page(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].page = value;
		}
		void width(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].width = value;
		}
		void height(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.chars[context.char_id].height = value;
		}
		void first(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.first = value;
		}
		void second(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.second = value;
		}
		void amount(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			uint16_t index = (uint16_t(context.first) << 8) | uint16_t(context.second);
			context.font.kernings.insert_or_assign(index, value);
		}
		void id(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.char_id = uint8_t(value);
		}
		void lineheight(association_type, int32_t value, error_handler& err, int32_t line, bmfont_file_context& context) {
			context.font.line_height = value;
		}
		void finish(bmfont_file_context& context) {
			assert(context.font.line_height >= 0);
		}
	};
}
#include "bmfont_defs.hpp"

namespace text {

	bool bm_font::parse_font(sys::state& state, simple_fs::file& f) {
		auto content = simple_fs::view_contents(f);
		parsers::error_handler err("");
		parsers::scenario_building_context context(state);
		err.file_name = text::native_to_utf8(simple_fs::get_full_name(f));
		parsers::token_generator gen(content.data, content.data + content.file_size);
		parsers::bmfont_file_context bmfont_file_context(context, *this);
		parsers::parse_bmfont_file(gen, err, bmfont_file_context);
		return true;
	}

	int bm_font::get_kerning_pair(char first, char second) const {
		uint16_t index = (uint16_t(first) << 8) | uint16_t(second);
		if(auto it = kernings.find(index); it != kernings.end()) {
			return it->second;
		}
		return 0;
	}

	float bm_font::get_string_width(sys::state& state, char const* string, uint32_t count) const {
		auto total = 0.f;
		for(uint32_t i = 0; i < count; ++i) {
			auto ch = uint8_t(string[i]);
			if(i != 0 && i < count - 1 && ch == 0xC3 && uint8_t(string[i + 1]) == 0xA3) {
				ch = 0xA3;
				i++;
			} else if(ch == 0xA4) {
				ch = 0xA3;
			}
			if(i != count - 1) {
				total += get_kerning_pair(ch, string[i + 1]);
			}
			total += chars[ch].x_advance;
		}
		return total;
	}

	bm_font::bm_font(sys::state& state, simple_fs::file& font_metrics, simple_fs::file& font_image) {
		auto font_result = ogl::make_font_texture(font_image);
		ftexid = font_result.handle;
		parse_font(state, font_metrics);
		assert(ftexid != 0);
		width = int16_t(font_result.size);
	}

	bm_font::bm_font(bm_font&& src) noexcept {
		ftexid = src.ftexid;
		chars = src.chars;
		kernings = std::move(src.kernings);
		width = src.width;
		height = src.height;
		base = src.base;
		line_height = src.line_height;
		src.ftexid = 0;
	}

	bm_font& bm_font::operator=(bm_font&& src) noexcept {
		ftexid = src.ftexid;
		chars = src.chars;
		kernings = std::move(src.kernings);
		width = src.width;
		height = src.height;
		base = src.base;
		line_height = src.line_height;
		src.ftexid = 0;
		return *this;
	}

	bm_font::~bm_font() {
		
	}

	void bm_font::clear_opengl_objects() {
		if(ftexid) {
			glDeleteTextures(1, &ftexid);
		}
	}

	bm_font const& get_bm_font(sys::state& state, uint16_t font_handle) {
		if(auto it = state.font_collection.bitmap_fonts.find(font_handle); it != state.font_collection.bitmap_fonts.end()) {
			return it->second;
		} else {
			auto const fit = state.font_collection.font_names.find(font_handle);
			assert(fit != state.font_collection.font_names.end());
			auto const fname = [&]() {
				auto sv = state.to_string_view(fit->second);
				if(sv == "Main_14")
					return std::string("garamond_14");
				else if(sv == "Main_14_plain")
					return std::string("garamond_14");
				else if(sv == "Main_14_grey")
					return std::string("garamond_14_bold");
				else if(sv == "Main_14_black")
					return std::string("garamond_14_bold");
				else if(sv == "Main_14_red")
					return std::string("garamond_14_bold");
				else if(sv == "Main_14_bold")
					return std::string("garamond_14_bold");
				else if(sv == "Main_14_orange")
					return std::string("garamond_14_bold");
				else if(sv == "Main_14_eu")
					return std::string("garamond_14");
				else if(sv == "tahoma_60")
					return std::string("mapfont_56");
				else if(sv == "mapfont_56_small")
					return std::string("vic_22_bl");
				else if(sv == "ToolTip_Font")
					return std::string("vic_18");
				else if(sv == "FPS_Font")
					return std::string("Arial14");
				return std::string(sv);
			}();

			auto root = get_root(state.common_fs);
			auto gfx_dir = open_directory(root, NATIVE("gfx"));
			auto font_dir = open_directory(gfx_dir, NATIVE("fonts"));
			auto font_def = open_file(font_dir, text::win1250_to_native(fname + ".fnt"));
			auto font_image = open_file(font_dir, text::win1250_to_native(fname + ".tga"));
			if(!bool(font_def) || !bool(font_image)) {
				auto result = state.font_collection.bitmap_fonts.insert_or_assign(font_handle, bm_font());
				return result.first->second;
			}
			auto result = state.font_collection.bitmap_fonts.insert_or_assign(font_handle, bm_font(state, *font_def, *font_image));
			return result.first->second;
		}
	}

} // namespace text
