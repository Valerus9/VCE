#include "system/system_state.hpp"
#include "texture.hpp"
#include "simple_fs.hpp"
#include "glad.h"
#include "reports.hpp"
#include "stb_image.h"

namespace ogl {

// DDS loader taken from SOIL2

#define DDSD_CAPS 0x00000001
#define DDSD_HEIGHT 0x00000002
#define DDSD_WIDTH 0x00000004
#define DDSD_PITCH 0x00000008
#define DDSD_PIXELFORMAT 0x00001000
#define DDSD_MIPMAPCOUNT 0x00020000
#define DDSD_LINEARSIZE 0x00080000
#define DDSD_DEPTH 0x00800000

/*	DirectDraw Pixel Format	*/
#define DDPF_ALPHAPIXELS 0x00000001
#define DDPF_FOURCC 0x00000004
#define DDPF_RGB 0x00000040
#define DDPF_PALETTEINDEXED8 0x00000020

/*	The dwCaps1 member of the DDSCAPS2 structure can be
set to one or more of the following values.	*/
#define DDSCAPS_COMPLEX 0x00000008
#define DDSCAPS_TEXTURE 0x00001000
#define DDSCAPS_MIPMAP 0x00400000

/*	The dwCaps2 member of the DDSCAPS2 structure can be
	set to one or more of the following values.		*/
#define DDSCAPS2_CUBEMAP 0x00000200
#define DDSCAPS2_CUBEMAP_POSITIVEX 0x00000400
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0x00000800
#define DDSCAPS2_CUBEMAP_POSITIVEY 0x00001000
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x00002000
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x00004000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x00008000
#define DDSCAPS2_VOLUME 0x00200000

#define SOIL_GL_SRGB 0x8C40
#define SOIL_GL_SRGB_ALPHA 0x8C42
#define SOIL_RGB_S3TC_DXT1 0x83F0
#define SOIL_RGBA_S3TC_DXT1 0x83F1
#define SOIL_RGBA_S3TC_DXT3 0x83F2
#define SOIL_RGBA_S3TC_DXT5 0x83F3

#define SOIL_TEXTURE_WRAP_R 0x8072
#define SOIL_CLAMP_TO_EDGE 0x812F
#define SOIL_REFLECTION_MAP 0x8512

	typedef struct {
		unsigned int dwMagic;
		unsigned int dwSize;
		unsigned int dwFlags;
		unsigned int dwHeight;
		unsigned int dwWidth;
		unsigned int dwPitchOrLinearSize;
		unsigned int dwDepth;
		unsigned int dwMipMapCount;
		unsigned int dwReserved1[11];

		/*  DDPIXELFORMAT	*/
		struct {
			unsigned int dwSize;
			unsigned int dwFlags;
			unsigned int dwFourCC;
			unsigned int dwRGBBitCount;
			unsigned int dwRBitMask;
			unsigned int dwGBitMask;
			unsigned int dwBBitMask;
			unsigned int dwAlphaBitMask;
		} sPixelFormat;

		/*  DDCAPS2	*/
		struct {
			unsigned int dwCaps1;
			unsigned int dwCaps2;
			unsigned int dwDDSX;
			unsigned int dwReserved;
		} sCaps;
		unsigned int dwReserved2;
	} DDS_header;

	GLuint SOIL_direct_load_DDS_from_memory(unsigned char const* const buffer, uint32_t buffer_length, uint32_t& width, uint32_t& height, int soil_flags) {
		/*	file reading variables	*/
		uint32_t block_size = 16;
		if(buffer_length < sizeof(DDS_header)) {
			return 0;
		}

		/*	try reading in the header */
		DDS_header const* header = reinterpret_cast<DDS_header const*>(buffer);
		uint32_t buffer_index = sizeof(DDS_header);
		uint32_t palette_index = buffer_index;

		/*	validate the header (warning, "goto"'s ahead, shield your eyes!!)	*/
		if(header->dwMagic != (('D' << 0) | ('D' << 8) | ('S' << 16) | (' ' << 24))) {
			reports::write_debug("Invalid DDS header checksum\n");
			return 0;
		}
		if(header->dwSize != 124) {
			reports::write_debug("Invalid DDS header size\n");
			return 0;
		}
		/*	I need all of these	*/
		uint32_t flag = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		if((header->dwFlags & flag) != flag) {
			reports::write_debug("Invalid DDS capabilities\n");
			return 0;
		}
		/*	According to the MSDN spec, the dwFlags should contain
		DDSD_LINEARSIZE if it's compressed, or DDSD_PITCH if
		uncompressed.  Some DDS writers do not conform to the
		spec, so I need to make my reader more tolerant	*/
		if(header->sPixelFormat.dwSize != 32) {
			reports::write_debug("Invalid DDS pixel format size\n");
			return 0;
		}
		/*	I need one of these	*/
		bool is_alpha = (header->sPixelFormat.dwFlags & (DDPF_ALPHAPIXELS)) != 0;
		bool uncompressed = (header->sPixelFormat.dwFlags & DDPF_FOURCC) == 0;
		if((header->sPixelFormat.dwFlags & (DDPF_FOURCC | DDPF_RGB | DDPF_PALETTEINDEXED8)) == 0) {
			reports::write_debug("Invalid DDS pixel format flags" + std::to_string(header->sPixelFormat.dwFlags) + "\n");
			return 0;
		}
		/*	make sure it is a type we can upload	*/
		if((header->sPixelFormat.dwFlags & DDPF_FOURCC) &&
		!((header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('1' << 24)))
		|| (header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('3' << 24)))
		|| (header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('5' << 24))))) {
			reports::write_debug("Invalid DDS flag saying DXT but with no DXT CC\n");
			return 0;
		}
		if((header->sCaps.dwCaps1 & DDSCAPS_TEXTURE) == 0) {
			reports::write_debug("No texture capability\n");
			return 0;
		}
		if((header->sCaps.dwCaps2 & DDSCAPS2_CUBEMAP) != 0) {
			reports::write_debug("Insupported cubemap DDS\n");
			return 0;
		}
		/*	OK, validated the header, let's load the image data	*/
		width = header->dwWidth;
		height = header->dwHeight;

		GLint s3tc_format = 0; //How we want to give it to shaders
		GLint s3tc_format_layout = 0; //How's it laid on memory
		GLint s3tc_type = GL_UNSIGNED_BYTE;
		uint32_t dds_main_size = 0;
		if(uncompressed) {
			block_size = 3;
			if(is_alpha) {
				block_size = 4;
				if(header->sPixelFormat.dwRGBBitCount == 16) {
					//s3tc_format_layout = GL_RGBA;
					//s3tc_type = GL_UNSIGNED_BYTE;
					block_size = 2;
				}
			}
			if((header->sPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) != 0) {
				block_size = 1;
				// skip the palette
				palette_index = buffer_index;
				buffer_index += 4 * 256;
			}
			//pitch = (width * (header->sPixelFormat.dwRGBBitCount) + 7) / 8;
			dds_main_size = width * height * block_size;
		} else {
			/*	can we even handle direct uploading to OpenGL DXT compressed images?	*/
			/*	well, we know it is DXT1/3/5, because we checked above	*/
			switch((header->sPixelFormat.dwFourCC >> 24) - '0') {
			case 1:
				s3tc_format = SOIL_RGBA_S3TC_DXT1;
				block_size = 8;
				break;
			case 3:
				s3tc_format = SOIL_RGBA_S3TC_DXT3;
				block_size = 16;
				break;
			case 5:
				s3tc_format = SOIL_RGBA_S3TC_DXT5;
				block_size = 16;
				break;
			}
			dds_main_size = ((width + 3) >> 2) * ((height + 3) >> 2) * block_size;
		}

		uint32_t dds_full_size = dds_main_size;
		uint32_t mipmaps = 0;
		if((header->sCaps.dwCaps1 & DDSCAPS_MIPMAP) != 0 && (header->dwMipMapCount > 1)) {
			mipmaps = header->dwMipMapCount - 1;
			for(uint32_t i = 1; i <= mipmaps; ++i) {
				uint32_t w = std::max<uint32_t>(width >> i, 1);
				uint32_t h = std::max<uint32_t>(height >> i, 1);
				if(uncompressed) {
					/*	uncompressed DDS, simple MIPmap size calculation	*/
					dds_full_size += w * h * block_size;
				} else {
					/*	compressed DDS, MIPmap size calculation is block based	*/
					dds_full_size += ((w + 3) / 4) * ((h + 3) / 4) * block_size;
				}
			}
		}
		/*	do this for each face of the cubemap!	*/
		if(buffer_index + dds_full_size <= uint32_t(buffer_length)) {
			/*	got the image data RAM, create or use an existing OpenGL texture handle	*/
			GLuint texid = 0;
			glGenTextures(1, &texid);
			/*  bind an OpenGL texture ID	*/
			glBindTexture(GL_TEXTURE_2D, texid);
			if(!texid)
				return 0;
			/*	did I have MIPmaps?	*/
			if(mipmaps > 0) {
				/*	instruct OpenGL to use the MIPmaps	*/
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			} else {
				/*	instruct OpenGL _NOT_ to use the MIPmaps	*/
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			/*	does the user want clamping, or wrapping? */
			if((soil_flags & SOIL_FLAG_TEXTURE_REPEATS) != 0) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, SOIL_TEXTURE_WRAP_R, GL_REPEAT);
			} else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, SOIL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			}
			/*	upload the main chunk */
			if(uncompressed) {
				/* TODO: make keep_rgba return false if we can compress it to 3-components without affecting alignment */
				bool keep_rgba = true;
				/*	and remember, DXT uncompressed uses BGR(A), so swap to (A)BGR for ALL MIPmap levels	*/
				std::unique_ptr<uint8_t[]> dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[dds_full_size]);
				switch(block_size) {
				case 1:
				{
					reports::write_debug("Experimental paletted DDS used\n");
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint8_t pidx = buffer[buffer_index + i];
							dds_dest_data[i * 4 + 0] = buffer[palette_index + pidx * 4 + 0];
							dds_dest_data[i * 4 + 1] = buffer[palette_index + pidx * 4 + 1];
							dds_dest_data[i * 4 + 2] = buffer[palette_index + pidx * 4 + 2];
							dds_dest_data[i * 4 + 3] = is_alpha ? buffer[palette_index + pidx * 4 + 3] : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint8_t pidx = buffer[buffer_index + i];
							dds_dest_data[i * 3 + 0] = buffer[palette_index + pidx * 4 + 0];
							dds_dest_data[i * 3 + 1] = buffer[palette_index + pidx * 4 + 1];
							dds_dest_data[i * 3 + 2] = buffer[palette_index + pidx * 4 + 2];
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 2:
				{
					reports::write_debug("Experimental 16-bits DDS used\n");
					uint16_t mr1 = uint16_t(header->sPixelFormat.dwRBitMask >> std::countr_zero(header->sPixelFormat.dwRBitMask));
					float mr2 = mr1 == 0 ? 0.f : 255.f / float(mr1);
					uint16_t mg1 = uint16_t(header->sPixelFormat.dwGBitMask >> std::countr_zero(header->sPixelFormat.dwGBitMask));
					float mg2 = mg1 == 0 ? 0.f : 255.f / float(mg1);
					uint16_t mb1 = uint16_t(header->sPixelFormat.dwBBitMask >> std::countr_zero(header->sPixelFormat.dwBBitMask));
					float mb2 = mb1 == 0 ? 0.f : 255.f / float(mb1);
					uint16_t ma1 = uint16_t(header->sPixelFormat.dwAlphaBitMask >> std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					float ma2 = ma1 == 0 ? 0.f : 255.f / float(ma1);
					uint16_t rmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint16_t gmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint16_t bmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint16_t amask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint16_t data = *reinterpret_cast<uint16_t const*>(buffer + buffer_index + i * block_size);
							uint16_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint16_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint16_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint16_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = uint8_t(float(r) * mr2);
							dds_dest_data[i * 4 + 1] = uint8_t(float(g) * mg2);
							dds_dest_data[i * 4 + 2] = uint8_t(float(b) * mb2);
							dds_dest_data[i * 4 + 3] = is_alpha ? uint8_t(float(a) * ma2) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint16_t data = *reinterpret_cast<uint16_t const*>(buffer + buffer_index + i * block_size);
							uint16_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint16_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint16_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint16_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = uint8_t(float(r) * mr2);
							dds_dest_data[i * 3 + 1] = uint8_t(float(g) * mg2);
							dds_dest_data[i * 3 + 2] = uint8_t(float(b) * mb2);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 3:
				{
					reports::write_debug("Experimental 24-bits DDS used\n");
					uint32_t rmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint32_t gmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint32_t bmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint32_t amask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							auto ptr = buffer + buffer_index + i * block_size;
							uint32_t data = uint32_t((ptr[2] << 16) | (ptr[1] << 8) | ptr[0]);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 4 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 4 + 2] = static_cast<uint8_t>(b);
							dds_dest_data[i * 4 + 3] = is_alpha ? static_cast<uint8_t>(a) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							auto ptr = buffer + buffer_index + i * block_size;
							uint32_t data = uint32_t((ptr[2] << 16) | (ptr[1] << 8) | ptr[0]);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 3 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 3 + 2] = static_cast<uint8_t>(b);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 4:
				{
					uint32_t rmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint32_t gmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint32_t bmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint32_t amask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint32_t data = *reinterpret_cast<uint32_t const*>(buffer + buffer_index + i * block_size);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 4 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 4 + 2] = static_cast<uint8_t>(b);
							dds_dest_data[i * 4 + 3] = is_alpha ? static_cast<uint8_t>(a) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint32_t data = *reinterpret_cast<uint32_t const*>(buffer + buffer_index + i * block_size);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 3 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 3 + 2] = static_cast<uint8_t>(b);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				default:
				{
					reports::write_debug("Experimental " + std::to_string(block_size) + " DDS block size used\n");
					dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
					break;
				}
				}
				glTexImage2D(GL_TEXTURE_2D, 0, s3tc_format, width, height, 0, s3tc_format_layout, s3tc_type, dds_dest_data.get());
				uint32_t dest_buffer_index = (dds_main_size / block_size) * (keep_rgba ? 4 : 3);
				/*	upload the mipmaps, if we have them	*/
				for(uint32_t i = 1; i <= mipmaps; ++i) {
					uint32_t w = std::max<uint32_t>(width >> i, 1);
					uint32_t h = std::max<uint32_t>(height >> i, 1);
					/*	upload this mipmap	*/
					uint32_t mip_size = w * h * (keep_rgba ? 4 : 3);
					glTexImage2D(GL_TEXTURE_2D, i, s3tc_format, w, h, 0, s3tc_format_layout, s3tc_type, dds_dest_data.get() + dest_buffer_index);
					/*	and move to the next mipmap	*/
					dest_buffer_index += mip_size;
				}
			} else {
				glCompressedTexImage2D(GL_TEXTURE_2D, 0, s3tc_format, width, height, 0, dds_main_size, buffer + buffer_index);
				buffer_index += dds_main_size;
				/*	upload the mipmaps, if we have them	*/
				for(uint32_t i = 1; i <= mipmaps; ++i) {
					uint32_t w = std::max<uint32_t>(width >> i, 1);
					uint32_t h = std::max<uint32_t>(height >> i, 1);
					/*	upload this mipmap	*/
					uint32_t mip_size = ((w + 3) / 4) * ((h + 3) / 4) * block_size;
					glCompressedTexImage2D(GL_TEXTURE_2D, i, s3tc_format, w, h, 0, mip_size, buffer + buffer_index);
					/*	and move to the next mipmap	*/
					buffer_index += mip_size;
				}
			}
			return texid;
		}
		return 0;
	}

	GLuint SOIL_direct_load_DDS_array_from_memory(unsigned char const* const buffer, uint32_t buffer_length, uint32_t& width, uint32_t& height, int soil_flags, uint32_t tiles_x, uint32_t tiles_y) {
		/*	file reading variables	*/
		uint32_t block_size = 16;
		if(buffer_length < sizeof(DDS_header)) {
			return 0;
		}

		/*	try reading in the header */
		DDS_header const* header = reinterpret_cast<DDS_header const*>(buffer);
		uint32_t buffer_index = sizeof(DDS_header);
		uint32_t palette_index = buffer_index;

		/*	validate the header (warning, "goto"'s ahead, shield your eyes!!)	*/
		if(header->dwMagic != (('D' << 0) | ('D' << 8) | ('S' << 16) | (' ' << 24))) {
			reports::write_debug("Invalid DDS header checksum\n");
			return 0;
		}
		if(header->dwSize != 124) {
			reports::write_debug("Invalid DDS header size\n");
			return 0;
		}
		/*	I need all of these	*/
		uint32_t flag = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		if((header->dwFlags & flag) != flag) {
			reports::write_debug("Invalid DDS capabilities\n");
			return 0;
		}
		/*	According to the MSDN spec, the dwFlags should contain
		DDSD_LINEARSIZE if it's compressed, or DDSD_PITCH if
		uncompressed.  Some DDS writers do not conform to the
		spec, so I need to make my reader more tolerant	*/
		if(header->sPixelFormat.dwSize != 32) {
			reports::write_debug("Invalid DDS pixel format size\n");
			return 0;
		}
		/*	I need one of these	*/
		bool is_alpha = (header->sPixelFormat.dwFlags & (DDPF_ALPHAPIXELS)) != 0;
		bool uncompressed = (header->sPixelFormat.dwFlags & DDPF_FOURCC) == 0;
		if((header->sPixelFormat.dwFlags & (DDPF_FOURCC | DDPF_RGB | DDPF_PALETTEINDEXED8)) == 0) {
			reports::write_debug("Invalid DDS pixel format flags" + std::to_string(header->sPixelFormat.dwFlags) + "\n");
			return 0;
		}
		/*	make sure it is a type we can upload	*/
		if((header->sPixelFormat.dwFlags & DDPF_FOURCC) &&
		!((header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('1' << 24)))
		|| (header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('3' << 24)))
		|| (header->sPixelFormat.dwFourCC == (('D' << 0) | ('X' << 8) | ('T' << 16) | ('5' << 24))))) {
			reports::write_debug("Invalid DDS flag saying DXT but with no DXT CC\n");
			return 0;
		}
		if((header->sCaps.dwCaps1 & DDSCAPS_TEXTURE) == 0) {
			reports::write_debug("No texture capability\n");
			return 0;
		}
		if((header->sCaps.dwCaps2 & DDSCAPS2_CUBEMAP) != 0) {
			reports::write_debug("Insupported cubemap DDS\n");
			return 0;
		}
		/*	OK, validated the header, let's load the image data	*/
		width = header->dwWidth;
		height = header->dwHeight;
		
		GLint s3tc_format = 0; //How we want to give it to shaders
		GLint s3tc_format_layout = 0; //How's it laid on memory
		GLint s3tc_type = GL_UNSIGNED_BYTE;
		uint32_t dds_main_size = 0;
		if(uncompressed) {
			block_size = 3;
			if(is_alpha) {
				block_size = 4;
				if(header->sPixelFormat.dwRGBBitCount == 16) {
					//s3tc_format_layout = GL_RGBA;
					//s3tc_type = GL_UNSIGNED_BYTE;
					block_size = 2;
				}
			}
			if((header->sPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) != 0) {
				block_size = 1;
				// skip the palette
				palette_index = buffer_index;
				buffer_index += 4 * 256;
			}
			//pitch = (width * (header->sPixelFormat.dwRGBBitCount) + 7) / 8;
			dds_main_size = width * height * block_size;
		} else {
			/*	can we even handle direct uploading to OpenGL DXT compressed images?	*/
			/*	well, we know it is DXT1/3/5, because we checked above	*/
			switch((header->sPixelFormat.dwFourCC >> 24) - '0') {
			case 1:
				s3tc_format = SOIL_RGBA_S3TC_DXT1;
				block_size = 8;
				break;
			case 3:
				s3tc_format = SOIL_RGBA_S3TC_DXT3;
				block_size = 16;
				break;
			case 5:
				s3tc_format = SOIL_RGBA_S3TC_DXT5;
				block_size = 16;
				break;
			}
			dds_main_size = ((width + 3) >> 2) * ((height + 3) >> 2) * block_size;
		}

		uint32_t dds_full_size = dds_main_size;
		uint32_t mipmaps = 0;
		if((header->sCaps.dwCaps1 & DDSCAPS_MIPMAP) != 0 && (header->dwMipMapCount > 1)) {
			mipmaps = header->dwMipMapCount - 1;
			for(uint32_t i = 1; i <= mipmaps; ++i) {
				uint32_t w = std::max<uint32_t>(width >> i, 1);
				uint32_t h = std::max<uint32_t>(height >> i, 1);
				if(uncompressed) {
					/*	uncompressed DDS, simple MIPmap size calculation	*/
					dds_full_size += w * h * block_size;
				} else {
					/*	compressed DDS, MIPmap size calculation is block based	*/
					dds_full_size += ((w + 3) / 4) * ((h + 3) / 4) * block_size;
				}
			}
		}
		/*	do this for each face of the cubemap!	*/
		if(buffer_index + dds_full_size <= uint32_t(buffer_length)) {
			/*	got the image data RAM, create or use an existing OpenGL texture handle	*/
			GLuint texid = 0;
			glGenTextures(1, &texid);
			/*  bind an OpenGL texture ID	*/
			glBindTexture(GL_TEXTURE_2D_ARRAY, texid);
			if(!texid)
				return 0;
			/*	did I have MIPmaps?	*/
			if(mipmaps > 0) {
				/*	instruct OpenGL to use the MIPmaps	*/
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			} else {
				/*	instruct OpenGL _NOT_ to use the MIPmaps	*/
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			/*	does the user want clamping, or wrapping? */
			if((soil_flags & SOIL_FLAG_TEXTURE_REPEATS) != 0) {
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, SOIL_TEXTURE_WRAP_R, GL_REPEAT);
			} else {
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, SOIL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			}
			glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, height);
			/*	upload the main chunk */
			if(uncompressed) {
				/* TODO: make keep_rgba return false if we can compress it to 3-components without affecting alignment */
				bool keep_rgba = true;
				/*	and remember, DXT uncompressed uses BGR(A), so swap to (A)BGR for ALL MIPmap levels	*/
				std::unique_ptr<uint8_t[]> dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[dds_full_size]);
				switch(block_size) {
				case 1:
				{
					reports::write_debug("Experimental paletted DDS used\n");
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint8_t pidx = buffer[buffer_index + i];
							dds_dest_data[i * 4 + 0] = buffer[palette_index + pidx * 4 + 0];
							dds_dest_data[i * 4 + 1] = buffer[palette_index + pidx * 4 + 1];
							dds_dest_data[i * 4 + 2] = buffer[palette_index + pidx * 4 + 2];
							dds_dest_data[i * 4 + 3] = is_alpha ? buffer[palette_index + pidx * 4 + 3] : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint8_t pidx = buffer[buffer_index + i];
							dds_dest_data[i * 3 + 0] = buffer[palette_index + pidx * 4 + 0];
							dds_dest_data[i * 3 + 1] = buffer[palette_index + pidx * 4 + 1];
							dds_dest_data[i * 3 + 2] = buffer[palette_index + pidx * 4 + 2];
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 2:
				{
					reports::write_debug("Experimental 16-bits DDS used\n");
					uint16_t mr1 = uint16_t(header->sPixelFormat.dwRBitMask >> std::countr_zero(header->sPixelFormat.dwRBitMask));
					float mr2 = mr1 == 0 ? 0.f : 255.f / float(mr1);
					uint16_t mg1 = uint16_t(header->sPixelFormat.dwGBitMask >> std::countr_zero(header->sPixelFormat.dwGBitMask));
					float mg2 = mg1 == 0 ? 0.f : 255.f / float(mg1);
					uint16_t mb1 = uint16_t(header->sPixelFormat.dwBBitMask >> std::countr_zero(header->sPixelFormat.dwBBitMask));
					float mb2 = mb1 == 0 ? 0.f : 255.f / float(mb1);
					uint16_t ma1 = uint16_t(header->sPixelFormat.dwAlphaBitMask >> std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					float ma2 = ma1 == 0 ? 0.f : 255.f / float(ma1);
					uint16_t rmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint16_t gmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint16_t bmask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint16_t amask_zeros = uint16_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint16_t data = *reinterpret_cast<uint16_t const*>(buffer + buffer_index + i * block_size);
							uint16_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint16_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint16_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint16_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = uint8_t(float(r) * mr2);
							dds_dest_data[i * 4 + 1] = uint8_t(float(g) * mg2);
							dds_dest_data[i * 4 + 2] = uint8_t(float(b) * mb2);
							dds_dest_data[i * 4 + 3] = is_alpha ? uint8_t(float(a) * ma2) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint16_t data = *reinterpret_cast<uint16_t const*>(buffer + buffer_index + i * block_size);
							uint16_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint16_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint16_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint16_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = uint8_t(float(r) * mr2);
							dds_dest_data[i * 3 + 1] = uint8_t(float(g) * mg2);
							dds_dest_data[i * 3 + 2] = uint8_t(float(b) * mb2);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 3:
				{
					reports::write_debug("Experimental 24-bits DDS used\n");
					uint32_t rmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint32_t gmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint32_t bmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint32_t amask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							auto ptr = buffer + buffer_index + i * block_size;
							uint32_t data = uint32_t((ptr[2] << 16) | (ptr[1] << 8) | ptr[0]);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 4 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 4 + 2] = static_cast<uint8_t>(b);
							dds_dest_data[i * 4 + 3] = is_alpha ? static_cast<uint8_t>(a) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							auto ptr = buffer + buffer_index + i * block_size;
							uint32_t data = uint32_t((ptr[2] << 16) | (ptr[1] << 8) | ptr[0]);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 3 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 3 + 2] = static_cast<uint8_t>(b);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				case 4:
				{
					uint32_t rmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwRBitMask));
					uint32_t gmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwGBitMask));
					uint32_t bmask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwBBitMask));
					uint32_t amask_zeros = uint32_t(std::countr_zero(header->sPixelFormat.dwAlphaBitMask));
					if(keep_rgba) {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint32_t data = *reinterpret_cast<uint32_t const*>(buffer + buffer_index + i * block_size);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 4 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 4 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 4 + 2] = static_cast<uint8_t>(b);
							dds_dest_data[i * 4 + 3] = is_alpha ? static_cast<uint8_t>(a) : 0xff;
						}
						s3tc_format = s3tc_format_layout = GL_RGBA;
					} else {
						dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 3]);
						for(uint32_t i = 0; i < dds_full_size / block_size; i++) {
							uint32_t data = *reinterpret_cast<uint32_t const*>(buffer + buffer_index + i * block_size);
							uint32_t r = (data & header->sPixelFormat.dwRBitMask) >> rmask_zeros;
							uint32_t g = (data & header->sPixelFormat.dwGBitMask) >> gmask_zeros;
							uint32_t b = (data & header->sPixelFormat.dwBBitMask) >> bmask_zeros;
							uint32_t a = (data & header->sPixelFormat.dwAlphaBitMask) >> amask_zeros;
							dds_dest_data[i * 3 + 0] = static_cast<uint8_t>(r);
							dds_dest_data[i * 3 + 1] = static_cast<uint8_t>(g);
							dds_dest_data[i * 3 + 2] = static_cast<uint8_t>(b);
						}
						s3tc_format = s3tc_format_layout = GL_RGB;
					}
					break;
				}
				default:
				{
					reports::write_debug("Experimental " + std::to_string(block_size) + " DDS block size used\n");
					dds_dest_data = std::unique_ptr<uint8_t[]>(new uint8_t[(dds_full_size / block_size) * 4]);
					break;
				}
				}
				reports::write_debug("Experimental DDS texturesheet (not-compressed)\n");
				size_t p_dx = width / tiles_x; // Pixels of each tile in x
				size_t p_dy = height / tiles_y; // Pixels of each tile in y
				for(uint32_t x = 0; x < tiles_x; x++) {
					for(uint32_t y = 0; y < tiles_y; y++) {
						uint32_t offset = uint32_t(x * p_dy * width + y * p_dx * (keep_rgba ? 4 : 3));
						glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, GLint(x * tiles_x + y), GLsizei(p_dx), GLsizei(p_dy), 1, s3tc_format, s3tc_type, dds_dest_data.get() + offset);
					}
				}
				//glTexImage2D(GL_TEXTURE_2D_ARRAY, 0, s3tc_format, width, height, 0, s3tc_format_layout, s3tc_type, dds_dest_data.get());
				//uint32_t dest_buffer_index = (dds_main_size / block_size) * (keep_rgba ? 4 : 3);
				/*	upload the mipmaps, if we have them	*/
				/*
				for(uint32_t i = 1; i <= mipmaps; ++i) {
					uint32_t w = std::max<uint32_t>(width >> i, 1);
					uint32_t h = std::max<uint32_t>(height >> i, 1);
					//	upload this mipmap
					uint32_t mip_size = w * h * (keep_rgba ? 4 : 3);
					glTexImage2D(GL_TEXTURE_2D_ARRAY, i, s3tc_format, w, h, 0, s3tc_format_layout, s3tc_type, dds_dest_data.get() + dest_buffer_index);
					//	and move to the next mipmap
					dest_buffer_index += mip_size;
				}*/
				//
			} else {
				reports::write_debug("Experimental DDS texturesheet (compressed)\n");
				size_t p_dx = width / tiles_x; // Pixels of each tile in x
				size_t p_dy = height / tiles_y; // Pixels of each tile in y
				glCompressedTexImage3D(GL_TEXTURE_2D_ARRAY, 0, s3tc_format, GLsizei(p_dx), GLsizei(p_dy), GLsizei(tiles_x * tiles_y), 0, GLsizei(dds_main_size), buffer);
				//glCompressedTexImage2D(GL_TEXTURE_2D_ARRAY, 0, s3tc_format, width, height, 0, dds_main_size, buffer + buffer_index);
				buffer_index += dds_main_size;
				/*	upload the mipmaps, if we have them	*/
				/*for(uint32_t i = 1; i <= mipmaps; ++i) {
					uint32_t w = std::max<uint32_t>(width >> i, 1);
					uint32_t h = std::max<uint32_t>(height >> i, 1);
					// upload this mipmap
					uint32_t mip_size = ((w + 3) / 4) * ((h + 3) / 4) * block_size;
					glCompressedTexImage2D(GL_TEXTURE_2D_ARRAY, i, s3tc_format, w, h, 0, mip_size, buffer + buffer_index);
					// and move to the next mipmap
					buffer_index += mip_size;
				}*/
			}
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
			return texid;
		}
		return 0;
	}

	texture::~texture() {
		stbi_image_free(data);
		data = nullptr;
	}

	texture::texture(texture&& other) noexcept {
		channels = other.channels;
		loaded = other.loaded;
		size_x = other.size_x;
		size_y = other.size_y;
		data = other.data;
		texture_handle = other.texture_handle;

		other.data = nullptr;
	}
	texture& texture::operator=(texture&& other) noexcept {
		channels = other.channels;
		loaded = other.loaded;
		size_x = other.size_x;
		size_y = other.size_y;
		data = other.data;
		texture_handle = other.texture_handle;

		other.data = nullptr;
		return *this;
	}

	GLuint texture::get_texture_handle() const {
		assert(loaded);
		return texture_handle;
	}

	GLuint load_file_and_return_handle(native_string const& native_name, simple_fs::file_system const& fs, texture& asset_texture, bool keep_data) {
		auto name_length = native_name.length();
		auto ext_pos = native_name.find_last_of('.');
		auto root = get_root(fs);
		if(name_length > 4) { // try loading as a dds
			auto dds_name = native_name;
			if(ext_pos != native_string::npos) {
				dds_name[ext_pos + 1] = NATIVE('d');
				dds_name[ext_pos + 2] = NATIVE('d');
				dds_name[ext_pos + 3] = NATIVE('s');
				dds_name.resize(ext_pos + 4);
			}
			if(auto f = open_file(root, dds_name); f) {
				auto content = simple_fs::view_contents(*f);
				reports::write_debug("Loading DDS texture: " + text::native_to_utf8(dds_name) + "\n");
				uint32_t w = 0;
				uint32_t h = 0;
				asset_texture.texture_handle = SOIL_direct_load_DDS_from_memory(reinterpret_cast<uint8_t const*>(content.data), content.file_size, w, h, 0);
				if(asset_texture.texture_handle) {
					glBindTexture(GL_TEXTURE_2D, asset_texture.texture_handle);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

					asset_texture.channels = 4;
					asset_texture.size_x = int32_t(w);
					asset_texture.size_y = int32_t(h);
					if(keep_data) {
						asset_texture.data = static_cast<uint8_t*>(malloc(4 * w * h));
						glGetTexImage(asset_texture.texture_handle, 0, GL_RGBA, GL_UNSIGNED_BYTE, asset_texture.data);
					}
					asset_texture.loaded = true;
					return asset_texture.texture_handle;
				}
			}
		}
		auto f = open_file(root, native_name);
		if(!f && name_length > 4) {
			auto png_name = native_name;
			if(ext_pos != native_string::npos) {
				png_name[ext_pos + 1] = NATIVE('p');
				png_name[ext_pos + 2] = NATIVE('n');
				png_name[ext_pos + 3] = NATIVE('g');
				png_name.resize(ext_pos + 4);
			}
			f = open_file(root, png_name);
			if(!f) {
				auto tga_name = native_name;
				if(ext_pos != native_string::npos) {
					tga_name[ext_pos + 1] = NATIVE('t');
					tga_name[ext_pos + 2] = NATIVE('g');
					tga_name[ext_pos + 3] = NATIVE('a');
					tga_name.resize(ext_pos + 4);
				}
				f = open_file(root, tga_name);
			}
		}
		if(f) {
			auto content = simple_fs::view_contents(*f);
			reports::write_debug("Loading texture: " + text::native_to_utf8(simple_fs::get_full_name(*f)) + "\n");
			int32_t file_channels = 4;
			asset_texture.data = stbi_load_from_memory(reinterpret_cast<uint8_t const*>(content.data), int32_t(content.file_size), &asset_texture.size_x, &asset_texture.size_y, &file_channels, 4);
			asset_texture.channels = file_channels;
			glGenTextures(1, &asset_texture.texture_handle);
			glBindTexture(GL_TEXTURE_2D, asset_texture.texture_handle);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, asset_texture.size_x, asset_texture.size_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, asset_texture.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			if(keep_data) {
				reports::write_debug("Texture is marked persistent in RAM\n");
			} else {
				stbi_image_free(asset_texture.data);
				asset_texture.data = nullptr;
			}
			asset_texture.loaded = true;
			return asset_texture.texture_handle;
		}
		asset_texture.loaded = true; // because we tried to load it (and failed) and trying again will be wasteful
		return 0;
	}

	native_string flag_type_to_name(sys::state& state, dcon::flag_type_id type) {
		if(type) {
			auto const sv = state.to_string_view(state.flag_type_names[type]);
			if(sv.size() > 0) {
				return NATIVE("_") + text::win1250_to_native(sv);
			}
		}
		return NATIVE("");
	}

	GLuint get_flag_handle(sys::state& state, dcon::national_identity_id nat_id, dcon::flag_type_id type) {
		auto masq_nat_id = state.world.nation_get_masquerade_identity(state.world.national_identity_get_nation_from_identity_holder(nat_id));
		if(!masq_nat_id) {
			masq_nat_id = nat_id;
		}
		auto const offset = type.index() + 1;
		auto const ui_textures = state.ui_defs.textures.size();
		dcon::texture_id id = dcon::texture_id{ dcon::texture_id::value_base_t(ui_textures
			+ (1 + masq_nat_id.id.index()) * (1 + state.flag_type_names.size()) + offset) };
		if(state.open_gl.asset_textures[id].loaded) {
			return state.open_gl.asset_textures[id].texture_handle;
		} else { // load from file
			native_string file_str = NATIVE("gfx");
			file_str += NATIVE_DIR_SEPARATOR;
			file_str += NATIVE("flags");
			file_str += NATIVE_DIR_SEPARATOR;
			file_str += text::win1250_to_native(nations::int_to_tag(state.world.national_identity_get_identifying_int(masq_nat_id)));
			native_string default_file_str = file_str;
			file_str += flag_type_to_name(state, type);
			GLuint p_tex = load_file_and_return_handle(file_str + NATIVE(".png"), state.common_fs, state.open_gl.asset_textures[id], false);
			if(!p_tex) {
				p_tex = load_file_and_return_handle(file_str + NATIVE(".tga"), state.common_fs, state.open_gl.asset_textures[id], false);
				if(!p_tex) {
					p_tex = load_file_and_return_handle(default_file_str + NATIVE(".png"), state.common_fs, state.open_gl.asset_textures[id], false);
					if(!p_tex) {
						return load_file_and_return_handle(default_file_str + NATIVE(".tga"), state.common_fs, state.open_gl.asset_textures[id], false);
					}
				}
			}
			return p_tex;
		}
	}

	GLuint get_texture_handle(sys::state& state, dcon::texture_id id, bool keep_data) {
		if(id) {
			if(state.open_gl.asset_textures[id].loaded) {
				return state.open_gl.asset_textures[id].texture_handle;
			}
			// load from file
			auto fname = state.ui_defs.textures[id];
			auto fname_view = state.to_string_view(fname);
			auto native_name = text::win1250_to_native(fname_view);
			return load_file_and_return_handle(native_name, state.common_fs, state.open_gl.asset_textures[id], keep_data);
		}
		return 0;
	}

	data_texture::data_texture(int32_t sz, int32_t ch) {
		size = sz;
		channels = ch;
		data = new uint8_t[size * channels];

		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);
		if(channels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		} else if(channels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, size, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		} else if(channels == 2) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, size, 1, 0, GL_RG, GL_UNSIGNED_BYTE, NULL);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, size, 1, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	data_texture::~data_texture() {
		delete[] data;
		data = nullptr;
	}

	uint32_t data_texture::handle() {
		if(data && data_updated) {
			glBindTexture(GL_TEXTURE_2D, texture_handle);
			if(channels == 4) {
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
			} else if(channels == 3) {
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
			} else if(channels == 2) {
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, 1, GL_RG, GL_UNSIGNED_BYTE, data);
			} else {
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size, 1, GL_RED, GL_UNSIGNED_BYTE, data);
			}
			data_updated = false;
		}
		return texture_handle;
	}

	data_texture::data_texture(data_texture&& other) noexcept {
		data = other.data;
		size = other.size;
		channels = other.channels;
		texture_handle = other.texture_handle;

		other.data = nullptr;
	}

	data_texture& data_texture::operator=(data_texture&& other) noexcept {
		data = other.data;
		size = other.size;
		channels = other.channels;
		texture_handle = other.texture_handle;

		other.data = nullptr;

		return *this;
	}

	font_texture_result make_font_texture(simple_fs::file& f) {
		auto content = simple_fs::view_contents(f);
		int32_t file_channels = 4;
		int32_t size_x = 0;
		int32_t size_y = 0;
		uint8_t* data = stbi_load_from_memory(reinterpret_cast<uint8_t const*>(content.data), int32_t(content.file_size), &(size_x), &(size_y), &file_channels, 4);
		GLuint ftexid = 0;
		if(data) {
			glGenTextures(1, &ftexid);
			glBindTexture(GL_TEXTURE_2D, ftexid);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size_x, size_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			// TODO: Change to GL_LINEAR dynamically when scaling up
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			stbi_image_free(data);
		}
		return font_texture_result{ uint32_t(ftexid), uint32_t(size_x) };
	}

} // namespace ogl
