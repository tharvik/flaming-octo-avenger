#include "Attribute.hpp"

Attribute::Attribute(std::string const name, std::vector<GLfloat> const value)
	: name(name), value(value)
{}

Attribute::Attribute(std::string const name, glm::mat4 const value)
	: name(name), value(mat_to_vec<4,4>(value))
{}

