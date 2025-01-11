#pragma once

#include "container_types.hpp" 
#include "economy_container_types.hpp" 
#include "culture_container_types.hpp" 
#include "system_container_types.hpp"

#include "glad.h"

namespace ogl {

	class texture;

	GLuint get_texture_handle(sys::state& state, dcon::texture_id id, bool keep_data);
	native_string flag_type_to_name(sys::state& state, dcon::flag_type_id type);
	GLuint get_flag_handle(sys::state& state, dcon::national_identity_id nat_id, dcon::flag_type_id type);
	GLuint load_file_and_return_handle(native_string const& native_name, simple_fs::file_system const& fs, texture& asset_texture, bool keep_data);

	enum {
		SOIL_FLAG_TEXTURE_REPEATS = 4,
	};

	GLuint SOIL_direct_load_DDS_from_memory(unsigned char const* const buffer, uint32_t buffer_length, uint32_t& width, uint32_t& height, int soil_flags);
	GLuint SOIL_direct_load_DDS_array_from_memory(unsigned char const* const buffer, uint32_t buffer_length, uint32_t& width, uint32_t& height, int soil_flags, uint32_t tiles_x, uint32_t tiles_y);

	class texture {
		GLuint texture_handle = 0;

		public:
		uint8_t* data = nullptr;
		int32_t size_x = 0;
		int32_t size_y = 0;
		int32_t channels = 4;

		bool loaded = false;

	texture() { }
		texture(texture const&) = delete;
		texture(texture&& other) noexcept;
		~texture();

		texture& operator=(texture const&) = delete;
		texture& operator=(texture&& other) noexcept;

		GLuint get_texture_handle() const;

		friend GLuint get_texture_handle(sys::state& state, dcon::texture_id id, bool keep_data);
		friend GLuint load_file_and_return_handle(native_string const& native_name, simple_fs::file_system const& fs,
			texture& asset_texture, bool keep_data);
		friend GLuint get_flag_handle(sys::state& state, dcon::national_identity_id nat_id, dcon::flag_type_id type);
	};

	class data_texture {
		GLuint texture_handle = 0;

		public:
		uint8_t* data = nullptr;
		int32_t size = 0;
		int32_t channels = 4;

		bool data_updated = false;

		data_texture(int32_t sz, int32_t ch);
		data_texture(data_texture const&) = delete;
		data_texture(data_texture&& other) noexcept;

		data_texture& operator=(data_texture const&) = delete;
		data_texture& operator=(data_texture&& other) noexcept;

		GLuint handle();
		~data_texture();
	};

	struct font_texture_result {
		uint32_t handle = 0;
		uint32_t size = 0;
	};

	font_texture_result make_font_texture(simple_fs::file& f);

} // namespace ogl
