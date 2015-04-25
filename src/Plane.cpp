#include "Plane.hpp"

#include "OpenGLValue.hpp"
#include "Attribute.hpp"

#include <array>

// TODO use size instead of hardcoded grid_res

Plane::Plane(size_t const size)
	: Object("plane", get_attributes(), get_uniformes(), get_texture()), size(size)
{
}

std::set<Attribute> Plane::get_attributes()
{
	std::set<Attribute> attribs;

	Attribute vpoint(GL_ARRAY_BUFFER, GL_FLOAT, get_points(), "position");
	Attribute indices(GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT, get_indices(), "position");

	attribs.insert(vpoint);
	attribs.insert(indices);

	return attribs;
}

std::set<Uniform> Plane::get_uniformes()
{
	std::set<Uniform> attribs;

	Uniform mvp("mvp", GL_DOUBLE_MAT4, get_mvp());

	attribs.insert(mvp);

	return attribs;
}

std::vector<GLfloat> Plane::get_points()
{
	std::vector<GLfloat> vertices;
	size_t const grid_res = 100;

	size_t const reserve = 2 * (grid_res + 1) * (grid_res + 1);
	vertices.reserve(reserve);
	float const delta = grid_res / 2.f;
	for(float i = - delta; i <= delta; ++i) {
		float const offset_x = i * 2 / grid_res;
		for(float j = - delta; j <= delta; ++j) {
			float const offset_y = j * 2 / grid_res;
			vertices.push_back(offset_x);
			vertices.push_back(offset_y);
		}
	}

	return vertices;
}

std::vector<GLuint> Plane::get_indices()
{
	std::vector<GLuint> indices;
	size_t const grid_res = 100;

	for(size_t i = 0; i < grid_res; ++i) {
		for(size_t j = 0; j < grid_res; ++j) {
			size_t const lb = (grid_res + 1) * i + j;
			size_t const lt = (grid_res + 1) * i + j + 1;
			size_t const rb = (grid_res + 1) * (i + 1) + j;
			size_t const rt = (grid_res + 1) * (i + 1) + j + 1;
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
