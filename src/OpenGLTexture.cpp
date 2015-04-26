#include "OpenGLTexture.hpp"

#include "Util.hpp"

#include <iostream>

OpenGLTexture::OpenGLTexture(Program const &program, Texture const &texture)
	: texture(texture)
{
	GLint loc = glGetUniformLocation(program.id, texture.name.c_str());
	glUniform1i(loc, texture.id);

	Util::assert_no_glError();
}

bool OpenGLTexture::operator<(OpenGLTexture const & other) const
{
	return this->texture < other.texture;
}
