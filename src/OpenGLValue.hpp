#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "OpenGL.hpp"

#include <string>
#include <vector>

/**
 * An attribute is a value shared by the Shaders
 */
class OpenGLValue {
public:
	/**
	 * The name used in GLSL
	 */
	std::string const name;

	/**
	 * OpenGL type contained
	 */
	GLenum const type;

	union element {
	#define OpenGLValue_macro(type, id) \
		type as_##type;
	#include "OpenGLValue.x"
	#undef OpenGLValue_macro
	};

	/**
	 * The values to put into the Program
	 */
	std::vector<element> const value;

	template<typename T>
	std::vector<T> as() const;

	/**
	 * Allow insertion into a set; based on the name
	 *
	 * @param other Attribute to compare to
	 *
	 * @return this->name < other.name;
	 */
	bool operator<(OpenGLValue const & other) const;

protected:

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	template<typename T>
	OpenGLValue(std::string const name, GLenum type, T const value);


private:

	/**
	 * Transform nearly (see implementation) any value into a std::vector<GLfloat>
	 *
	 * @param value value to read from
	 *
	 * @return vector representation of the value
	 */
	template<typename T>
	static std::vector<element> to_vec(T const value);
};

// TODO find a way to put it in .cpp
template<typename T>
OpenGLValue::OpenGLValue(std::string const name, GLenum type, T const value)
	: name(name), type(type), value(to_vec<>(value))
{}

#endif
