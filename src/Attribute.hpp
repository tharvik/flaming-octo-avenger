#ifndef FLAMING_OCTO_AVENGER_ATTRIBUTE_H
#define FLAMING_OCTO_AVENGER_ATTRIBUTE_H

#include "OpenGLValue.hpp"

// TODO put todo in doxygen

class Attribute : public OpenGLValue {
public:

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param type_buffer type of the buffer to create in OpenGL
	 * @param type type wrapped
	 * @param value value to load into
	 */
	template<typename T>
	Attribute(GLenum const type_buffer, GLenum const type, T const value, std::string const name);

	/**
	 * Type of buffer used in OpenGL
	 */
	GLenum const type_buffer;
};

// TODO find a way to put it in .cpp
template<typename T>
Attribute::Attribute(GLenum const type_buffer, GLenum const type, T const value, std::string const name)
	: OpenGLValue(name, type, value), type_buffer(type_buffer)
{}

#endif //FLAMING_OCTO_AVENGER_ATTRIBUTE_H
