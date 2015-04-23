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
	template<typename T>
	Attribute(std::string const name, T const value);

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
	 * Transform nearly (see implementation) any value into a std::vector<GLfloat>
	 *
	 * @param value value to read from
	 *
	 * @return vector representation of the value
	 */
	template<typename T>
	static std::vector<GLfloat> to_vec(T const value);
};

// TODO find a way to put it in .cpp
template<typename T>
Attribute::Attribute(std::string const name, T const value)
	: name(name), value(to_vec<>(value))
{}

#endif
