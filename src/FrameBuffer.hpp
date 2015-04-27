#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "OpenGL.hpp"

class FrameBuffer {

	public:
		FrameBuffer(size_t const width = 100,
			    size_t const height = 100);

		void bind() const;
		void unbind() const;

	private:
		size_t const width;
		size_t const height;

	public:
		GLuint const color_attachement;
		GLuint const texture;
	private:
		GLuint const render_buffer;

	public:
		GLuint const id;

	private:

		static GLenum get_color_attachement();
		static GLuint get_texture(size_t const width,
					  size_t const height);
		static GLuint get_render_buffer(size_t const width,
						size_t const height);
		static GLuint get_id(GLenum const color_attachement,
				     GLuint const tex,
				     GLuint const render_buffer);

		GLenum get_new_id();
};

#endif
