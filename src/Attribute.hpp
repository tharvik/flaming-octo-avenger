#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "OpenGL.hpp"

#include <string>
#include <vector>

class Attribute {
	public:
		Attribute(std::string const name, std::vector<GLfloat> const value);
		Attribute(std::string const name, glm::mat4 const value);

		std::string const name;
		std::vector<GLfloat> const value;

	private:
		// TODO mat4 -> mat<width,heigth>
		template<size_t width, size_t heigth>
		std::vector<GLfloat> mat_to_vec(glm::mat4 const value);
};

// TODO way to put it in cpp
template<size_t width, size_t heigth>
std::vector<GLfloat> Attribute::mat_to_vec(glm::mat4 const value)
{
	std::vector<GLfloat> vec;
	size_t const size = width * heigth;

	vec.reserve(size);
	for (size_t i = 0; i < size; i++)
		vec.push_back(value[i / heigth][i % width]);

	return vec;
}

#endif
