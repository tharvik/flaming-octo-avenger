#ifndef FLAMING_OCTO_AVENGER_UNIFORM_H
#define FLAMING_OCTO_AVENGER_UNIFORM_H

#include "OpenGLValue.hpp"

#include <set>

class Uniform {
public:

	/**
	 * Construct an Uniform with the given name and value
	 *
	 * @param name name used by GLSL
	 * @param value value to load into
	 */
	Uniform(std::string const name, OpenGLValue const value);

	std::string const name;
	OpenGLValue const value;

	bool operator<(Uniform const & other) const;
};

#endif //FLAMING_OCTO_AVENGER_UNIFORM_H
