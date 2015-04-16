#include "Triangle.hpp"

#include <array>

Triangle::Triangle()
	: Object("triangle", get_attributes(), std::vector<Attribute>())
{}

std::vector<Attribute> Triangle::get_attributes()
{
	std::vector<Attribute> attribs;

	Attribute attr("vpoint", get_points());
	attribs.push_back(attr);

	return attribs;
}

std::vector<GLfloat> Triangle::get_points()
{
	std::vector<GLfloat> points;

	std::array<GLfloat, 3 * 3> array = {
		-1, -1,  0,
		+1, -1,  0,
		 0, +1,  0
	};

	points.reserve(array.size());
	for (auto e : array)
		points.push_back(e);

	return points;
}
