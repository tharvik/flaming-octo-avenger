#include "Texture.hpp"

#include <cstring>
#include <png.h>

#define texture_base_path "textures/"

Texture::Texture(std::string filename, std::string name, bool const gl_repeat)
	: name(name), id(get_id()),
	  buffer_id(load_texture(id, texture_base_path + filename, gl_repeat))
{}

Texture::Texture(std::string name, std::vector<uint32_t> data,
		 bool const gl_repeat)
	: name(name), id(get_id()), buffer_id(load_texture(id, data, gl_repeat))
{}

Texture::Texture(std::string const name, GLuint const id,
		 GLuint const buffer_id)
	: name(name), id(id), buffer_id(buffer_id)
{
	get_id(); // drop an id
}

GLuint Texture::load_texture(GLenum id, std::string path, bool const gl_repeat)
{
	png_image image;
	memset(&image, 0, (sizeof image));
	image.version = PNG_IMAGE_VERSION;

	if (png_image_begin_read_from_file(&image, (path).c_str()) == 0)
		throw std::string("pngtopng: error: ") + image.message;

	image.format = PNG_FORMAT_RGBA;

	png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];

	if (!png_image_finish_read(&image, NULL/*background*/, buffer, 0/*row_stride*/, NULL/*colormap*/) != 0) {
		delete[](buffer);
		throw std::string("pngtopng: error: ") + image.message;
	}

	size_t const size = image.width * image.height;

	std::vector<uint32_t> data;
	data.reserve(size);
	for (size_t i = 0; i < size * 4; i += 4) {
		uint32_t elem = 0;
		for (int j = 3; j >= 0; --j)
			elem = (elem << 8) | buffer[i + j];

		data.push_back(elem);
	}

	return load_texture(id, data, gl_repeat);
}

GLuint Texture::load_texture(GLenum id, std::vector<uint32_t> data,
			     bool const gl_repeat)
{
	GLuint tex;

	size_t const border = sqrt(data.size());

	glActiveTexture(id + GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, border, border, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (gl_repeat) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}

	return tex;
}

GLenum Texture::get_id()
{
	static GLuint id = 0;

	return id++;
}

bool Texture::operator<(Texture const & other) const
{
	return this->id < other.id;
}
