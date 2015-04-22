#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"

#include <string>

class Triangle : public Object {

public:
	Triangle();

private:
	static std::set<Attribute> get_attributes();
	static std::vector<GLfloat> get_points();
};

#endif
