#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "OpenGL.hpp"

#include <string>
#include <vector>

class Attribute {
	public:
		Attribute(std::string const name, std::vector<GLfloat> const points);

		std::string const name;
		std::vector<GLfloat> const points;
};

#endif
