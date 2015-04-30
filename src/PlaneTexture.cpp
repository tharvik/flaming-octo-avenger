#include "PlaneTexture.hpp"

#include "PerlinNoise.hpp"

PlaneTexture::PlaneTexture(size_t const size)
	: Plane("plane", std::set<Uniform>(), std::set<Attribute>(),
		get_texture(size))
{}


std::set<Texture> PlaneTexture::get_texture(size_t const size)
{
	std::set<Texture> textures;

	PerlinNoise pattern(size);

	textures.insert(pattern.get_texture("pattern"));

	return textures;
}

