#include "OpenGLValue.hpp"

bool OpenGLValue::operator<(OpenGLValue const & other) const
{
	return this->name < other.name;
}

template<>
std::vector<GLfloat> OpenGLValue::to_vec(glm::mat4 const value)
{
	size_t const width = 4, height = 4;

	std::vector<GLfloat> vec;
	size_t const size = width * height;

	vec.reserve(size);
	for (size_t i = 0; i < size; i++)
		vec.push_back(value[i / height][i % width]);

	return vec;
}

template<>
std::vector<GLfloat> OpenGLValue::to_vec(std::vector<GLfloat> const value)
{
	return value;
}
