#ifndef FLAMING_OCTO_AVENGER_UNIFORM_H
#define FLAMING_OCTO_AVENGER_UNIFORM_H

#include "OpenGLValue.hpp"

class Uniform : public OpenGLValue {
public:

	/**
	 * Construct an Uniform with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	template<typename T>
	Uniform(std::string const name, GLenum const type, T const value);
};

// TODO find a way to put it in .cpp
template<typename T>
Uniform::Uniform(std::string const name, GLenum const type, T const value)
	: OpenGLValue(name, type, value)
{}

#endif //FLAMING_OCTO_AVENGER_UNIFORM_H
