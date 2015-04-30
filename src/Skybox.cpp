#include "Skybox.hpp"

#include "Attribute.hpp"
#include "OpenGLValue.hpp"
#include "PerlinNoise.hpp"

Skybox::Skybox(size_t const size)
	: Object("skybox", get_attributes(size))
{}

std::set<Attribute> Skybox::get_attributes(size_t const size)
{
	std::set<std::tuple<GLenum, OpenGLValue>> values;

	OpenGLValue points(GL_FLOAT, get_points(size));
	OpenGLValue indices(GL_UNSIGNED_INT, get_indices(size));

	values.emplace(GL_ARRAY_BUFFER, points);
	values.emplace(GL_ELEMENT_ARRAY_BUFFER, indices);

	std::set<Attribute> attribs;
	attribs.emplace("vpoint", values);

	return attribs;
}

std::vector<GLfloat> Skybox::get_points(size_t const size)
{
	std::vector<GLfloat> vertices;

	vertices.reserve(6 * 3);
	for(uint8_t i = 0x0; i < 0x8; ++i) {
		GLfloat x = i & (0x1 << 2);
		GLfloat y = i & (0x1 << 1);
		GLfloat z = i & (0x1 << 0);

		x = (x == 0) ? -1 : 1;
		y = (y == 0) ? -1 : 1;
		z = (z == 0) ? -1 : 1;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}

	return vertices;
}

std::vector<GLuint> Skybox::get_indices(size_t const size)
{
	std::vector<GLuint> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(0);
	indices.push_back(2);

	indices.push_back(5);
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(4);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(2);

	indices.push_back(7);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(7);
	indices.push_back(2);
	indices.push_back(3);

	return indices;
}
