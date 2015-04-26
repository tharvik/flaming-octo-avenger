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
	 */
	bool operator<(OpenGLValue const & other) const;

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	template<typename T>
	OpenGLValue(GLenum type, T const value);

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

template<typename T>
OpenGLValue::OpenGLValue(GLenum type, T const value)
	: type(type), value(to_vec<>(value))
{}

#endif
