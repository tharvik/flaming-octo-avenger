#include "Plane.hpp"

#include "OpenGLValue.hpp"
#include "Attribute.hpp"

Plane::Plane(size_t const size)
	: Object("plane", get_attributes(size), get_uniformes(), get_texture()), size(size)
{
}

std::set<Attribute> Plane::get_attributes(size_t const size)
{
	std::set<std::tuple<GLenum, OpenGLValue>> values;

	OpenGLValue points(GL_FLOAT, get_points(size));
	OpenGLValue indices(GL_UNSIGNED_INT, get_indices(size));

	values.emplace(GL_ARRAY_BUFFER, points);
	values.emplace(GL_ELEMENT_ARRAY_BUFFER, indices);

	std::set<Attribute> attribs;
	attribs.emplace("position", values);

	return attribs;
}

std::set<Uniform> Plane::get_uniformes()
{
	OpenGLValue value(GL_DOUBLE_MAT4, get_mvp());

	std::set<Uniform> attribs;
	attribs.emplace("mvp", value);

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

/**
 * @todo order matter, it has to change
 */
std::set<Texture> Plane::get_texture()
{
	std::set<Texture> textures;

	textures.emplace("plane.png", "tex");
	textures.emplace("pattern.png", "pattern");

	return textures;
}
