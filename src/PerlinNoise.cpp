#include "PerlinNoise.hpp"

#include "Plane.hpp"

PerlinNoise::PerlinNoise()
{
	Plane plane("perlin_noise");

	//program.bind();
	framebuffer.bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	plane.draw();

	framebuffer.unbind();
	//program.unbind();
}

Texture PerlinNoise::get_texture(std::string const name) const
{
	return Texture(name, 0, framebuffer.color_attachement);
}
