#ifndef OPENGLTEXTURE_HPP
#define OPENGLTEXTURE_HPP

#include "Program.hpp"
#include "Texture.hpp"

class OpenGLTexture {
	public:
		OpenGLTexture(Program const &program, Texture const &texture);

		bool operator<(OpenGLTexture const & other) const;

	private:
		Texture const &texture;
};

#endif
