#include "Plane.hpp"

#include "Attribute.hpp"
#include "OpenGLValue.hpp"
#include "PerlinNoise.hpp"

Plane::Plane(std::string const name,
	     std::set<Uniform> const uniforms,
	     std::set<Attribute> const attributes,
	     std::set<Texture> const textures,
	     size_t const size)
	: Object(name,
		 get_attributes(attributes, size),
		 uniforms,
		 textures),
	  size(size)
{}

std::set<Attribute> Plane::get_attributes(std::set<Attribute> const attributes,
					  size_t const size)
{
	std::set<std::tuple<GLenum, OpenGLValue>> values;

	OpenGLValue points(GL_FLOAT, get_points(size));
	OpenGLValue indices(GL_UNSIGNED_INT, get_indices(size));

	values.emplace(GL_ARRAY_BUFFER, points);
	values.emplace(GL_ELEMENT_ARRAY_BUFFER, indices);

	std::set<Attribute> attribs;
	attribs.insert(attributes.begin(), attributes.end());
	attribs.emplace("position", values);

	return attribs;
}

std::vector<GLfloat> Plane::get_points(size_t const size)
{
	std::vector<GLfloat> vertices;

	size_t const reserve = 2 * (size + 1) * (size + 1);
	vertices.reserve(reserve);
	float const delta = size / 2.f;
	for(float i = - delta; i <= delta; ++i) {
		float const offset_x = i * 2 / size;
		for(float j = - delta; j <= delta; ++j) {
			float const offset_y = j * 2 / size;
			vertices.push_back(offset_y);
			vertices.push_back(offset_x);
			vertices.push_back(0);
		}
	}

	return vertices;
}

std::vector<GLuint> Plane::get_indices(size_t const size)
{
	std::vector<GLuint> indices;

	for(size_t i = 0; i < size; ++i) {
		for(size_t j = 0; j < size; ++j) {
			size_t const lb = (size + 1) * i + j;
			size_t const lt = (size + 1) * i + j + 1;
			size_t const rb = (size + 1) * (i + 1) + j;
			size_t const rt = (size + 1) * (i + 1) + j + 1;
			indices.push_back(lb);
			indices.push_back(rb);
			indices.push_back(lt);
			indices.push_back(lt);
			indices.push_back(rb);
			indices.push_back(rt);
		}
	}

	return indices;
}
