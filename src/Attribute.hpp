#ifndef FLAMING_OCTO_AVENGER_ATTRIBUTE_H
#define FLAMING_OCTO_AVENGER_ATTRIBUTE_H

#include "OpenGLValue.hpp"

#include <set>
#include <tuple>

class Attribute {
public:

	/**
	 * Construct an Attribute with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param type_buffer type of the buffer to create in OpenGL
	 * @param type type wrapped
	 * @param value value to load into
	 */
	Attribute(std::string const name, std::set<std::tuple<GLenum, OpenGLValue>> const values);

	std::string name;

	std::set<std::tuple<GLenum, OpenGLValue>> const values;

	bool operator<(Attribute const & other) const;
};

#endif //FLAMING_OCTO_AVENGER_ATTRIBUTE_H
