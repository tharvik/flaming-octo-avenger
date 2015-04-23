#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "OpenGL.hpp"

#include <string>
#include <vector>

/**
 * An attribute is a value shared by the Shaders
 */
class Attribute {
public:
	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	Attribute(std::string const name, std::vector<GLfloat> const value);

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	Attribute(std::string const name, glm::mat4 const value);

	/**
	 * The name used in GLSL
	 */
	std::string const name;

	/**
	 * The value to put into the Program
	 */
	std::vector<GLfloat> const value;

	/**
	 * Allow insertion into a set; based on the name
	 *
	 * @param other Attribute to compare to
	 *
	 * @return this->name < other.name;
	 */
	bool operator<(Attribute const & other) const;

private:
	/**
	 * Transform a mat4 into a value
	 *
	 * @param value glm::mat4 to read from
	 *
	 * @return vector representation of glm::mat4
	 */
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
