#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "FrameBuffer.hpp"
#include "OpenGLAttribute.hpp"
#include "Texture.hpp"

class PerlinNoise {
	public:
		PerlinNoise(size_t const size = 100);

		Texture get_texture(std::string const name) const;

	private:
		FrameBuffer const framebuffer;
};

#endif
