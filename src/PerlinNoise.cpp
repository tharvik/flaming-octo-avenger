#include "PerlinNoise.hpp"

#include "Plane.hpp"

#include <algorithm>
#include <noise/noise.h>

#include <iostream>

/**
 * @todo remove deps on libnoise
 */
PerlinNoise::PerlinNoise(size_t const size)
	: framebuffer(size)
{
	std::set<Uniform> uniforms;
	std::set<Attribute> attributes;
	std::set<Texture> textures;

	std::vector<uint32_t> data;
	data.reserve(size * size);

	noise::module::Perlin myModule;

	double const x_base = 0;
	double const y_base = 0;
	double const x_end = 1;
	double const y_end = 1;
	double const ground = 0.7;

	for (double x = x_base; x < x_end; x += (x_end - x_base) / size) {

		for (double y = y_base; y < y_end; y += (y_end - y_base) / size) {
			double value = myModule.GetValue(x, y, ground);
			data.push_back(value * 0xFF);
		}
	}

	textures.emplace("noise", data);

	Plane plane("perlin_noise", uniforms, attributes, textures);

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
