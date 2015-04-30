#include "FrameBuffer.hpp"

#include "Texture.hpp"
#include "Util.hpp"

FrameBuffer::FrameBuffer(size_t const size)
	: size(size),
	  color_attachement(get_color_attachement()),
	  texture(get_texture(size)),
	  render_buffer(get_render_buffer(size)),
	  id(get_id(color_attachement, texture, render_buffer))
{}

GLenum FrameBuffer::get_color_attachement()
{
	static GLenum color_attachement = GL_COLOR_ATTACHMENT0;

	return color_attachement++;
}

GLuint FrameBuffer::get_texture(size_t const size)
{
	GLuint texture;

	glActiveTexture(Texture::get_id() + GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB,
		     GL_UNSIGNED_BYTE, NULL);

	Util::assert_no_glError();

	return texture;
}

GLuint FrameBuffer::get_render_buffer(size_t const size)
{
	GLuint render_buffer;

	glGenRenderbuffers(1, &render_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32,
			      size, size);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

	Util::assert_no_glError();

	return render_buffer;
}

#include <iostream>
GLuint FrameBuffer::get_id(GLenum color_attachement, GLuint texture,
			   GLuint render_buffer)
{
	GLuint id;

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glFramebufferTexture2D(GL_FRAMEBUFFER, color_attachement,
			       GL_TEXTURE_2D, texture, 0);
	Util::assert_no_glError();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				  GL_RENDERBUFFER, render_buffer);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return id;
}

void FrameBuffer::bind() const
{
	glViewport(0, 0, this->size, this->size);

	glBindFramebuffer(GL_FRAMEBUFFER, this->id);

	glDrawBuffers(1, &this->color_attachement);

	Util::assert_no_glError();
}

/**
 * @todo not hardcoded values! Should had something to world, make it static
 */
void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 1920, 1080);

	Util::assert_no_glError();
}
