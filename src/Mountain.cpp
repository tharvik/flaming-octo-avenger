#include "Mountain.hpp"

#include "Attribute.hpp"
#include "OpenGLValue.hpp"
#include "PerlinNoise.hpp"

Mountain::Mountain(size_t const size)
	: Plane("mountain", std::set<Uniform>(), std::set<Attribute>(),
		get_texture(size)),
	  size(size)
{}

std::set<Texture> Mountain::get_texture(size_t const size)
{
	std::set<Texture> textures;

	PerlinNoise pattern(size);

	textures.insert(pattern.get_texture("pattern"));
	textures.emplace("grass.png", "grass");
	textures.emplace("rock.png", "rock");
	textures.emplace("sand.png", "sand");
	textures.emplace("snow.png", "snow");

	return textures;
}
