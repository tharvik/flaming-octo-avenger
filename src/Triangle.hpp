#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

#include <string>

class Triangle : public Object {

public:
	Triangle();

private:
	static std::vector<Attribute> get_attributes();
	static std::vector<GLfloat> get_points();
};

#endif
