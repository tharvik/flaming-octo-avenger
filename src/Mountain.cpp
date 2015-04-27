#include "Mountain.hpp"

#include "Attribute.hpp"
#include "OpenGLValue.hpp"
#include "PerlinNoise.hpp"

Mountain::Mountain(size_t const size)
	: Plane("plane", get_uniformes(), std::set<Attribute>(), get_texture()),
	  size(size)
{
}

std::set<Uniform> Mountain::get_uniformes()
{
	OpenGLValue value(GL_DOUBLE_MAT4, get_mvp());

	std::set<Uniform> attribs;
	attribs.emplace("mvp", value);

	return attribs;
}

glm::mat4 Mountain::get_mvp()
{
	glm::mat4 mat;

	mat[0] = { 0.970836,	0, -0.485418,         0};
	mat[1] = {-0.182574,	0.912871, -0.365148, -0.228218};
	mat[2] = {-0.0408248,  -0.0408248,-0.0816497,  0.500104};
	mat[3] = { 0,		0,         0,         1};

	mat = glm::transpose(mat);

	return mat;
}

/**
 * @todo order matter, it has to change
 */
std::set<Texture> Mountain::get_texture()
{
	std::set<Texture> textures;

	PerlinNoise pattern;

	textures.emplace("plane.png", "tex");
	textures.insert(pattern.get_texture("pattern"));

	return textures;
}
