#include "Plane.hpp"

#include "Attribute.hpp"

#include <array>

Plane::Plane()
	: Object("plane", get_attributes(), get_uniformes(), get_texture())
{
}

std::vector<Attribute> Plane::get_attributes()
{
	std::vector<Attribute> attribs;

	Attribute vpoint("position", get_points());

	attribs.push_back(vpoint);

	return attribs;
}

std::vector<Attribute> Plane::get_uniformes()
{
	std::vector<Attribute> attribs;

	Attribute mvp("mvp", get_mvp());

	attribs.push_back(mvp);

	return attribs;
}

std::vector<GLfloat> Plane::get_points()
{
	std::vector<GLfloat> points;

	std::array<GLfloat, 4 * 3> array = {
		-1.0f, -1.0f, 0.0f,
		+1.0f, -1.0f, 0.0f,
		-1.0f, +1.0f, 0.0f,
		+1.0f, +1.0f, 0.0f
	};

	points.reserve(array.size());
	for (auto e : array)
		points.push_back(e);

	return points;
}

glm::mat4 Plane::get_mvp()
{
	glm::mat4 mat;

	mat[0] = { 0.970836,	0, -0.485418,         0};
	mat[1] = {-0.182574,	0.912871, -0.365148, -0.228218};
	mat[2] = {-0.0408248,  -0.0408248,-0.0816497,  0.500104};
	mat[3] = { 0,		0,         0,         1};

	mat = glm::transpose(mat);

	return mat;
}

std::set<Texture> Plane::get_texture()
{
	std::set<Texture> textures;

	Texture tex("plane.png", "pattern");

	return textures;
}
