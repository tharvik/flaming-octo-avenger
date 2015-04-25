#include "Texture.hpp"

#include <cstring>
#include <png.h>

#define texture_base_path "textures/"

Texture::Texture(std::string filename, std::string name)
	: name(name), id(get_id()), buffer_id(load_texture(id, texture_base_path + filename, name))
{}

GLuint Texture::load_texture(GLenum id, std::string path, std::string name)
{
	GLuint tex;

	png_image image;
	memset(&image, 0, (sizeof image));
	image.version = PNG_IMAGE_VERSION;

	if (png_image_begin_read_from_file(&image, (path).c_str()) == 0);
		// TODO fail

	image.format = PNG_FORMAT_RGBA;

	png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];

	if (!png_image_finish_read(&image, NULL/*background*/, buffer, 0/*row_stride*/, NULL/*colormap*/) != 0)
		delete[](buffer);

	//fprintf(stderr, "pngtopng: error: %s\n", image.message); TODO throw message

	glActiveTexture(id);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return tex;
}

GLenum Texture::get_id()
{
	static GLuint id = GL_TEXTURE0;

	return id++;
}
