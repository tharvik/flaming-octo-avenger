#ifndef FLAMING_OCTO_AVENGER_ATTRIBUTE_H
#define FLAMING_OCTO_AVENGER_ATTRIBUTE_H

#include "OpenGLValue.hpp"

class Attribute : public OpenGLValue {
public:

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	template<typename T>
	Attribute(std::string const name, T const value);
};

// TODO find a way to put it in .cpp
template<typename T>
Attribute::Attribute(std::string const name, T const value)
	: OpenGLValue(name, value)
{}

#endif //FLAMING_OCTO_AVENGER_ATTRIBUTE_H
