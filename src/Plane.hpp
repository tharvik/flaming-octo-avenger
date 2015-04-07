#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

#include <string>

class Plane : public Object {

public:
	Plane();

private:
	static std::vector<GLfloat> get_points();
};

#endif
