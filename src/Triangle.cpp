#include "Triangle.hpp"
#include "Attribute.hpp"

#include <array>

Triangle::Triangle()
	: Object("triangle", get_attributes(), std::set<Uniform>(), std::set<Texture>())
{}

std::set<Attribute> Triangle::get_attributes()
{
	std::set<std::tuple<GLenum, OpenGLValue>> values;

	values.insert(std::make_pair(GL_ARRAY_BUFFER, OpenGLValue(GL_FLOAT, get_points())));

	std::set<Attribute> attribs;
	attribs.emplace("vpoint", values);

	return attribs;
}

std::vector<GLfloat> Triangle::get_points()
{
	std::vector<GLfloat> points;

	std::array<GLfloat, 3 * 3> array = {
		-1, -1,  0,
		 1, -1,  0,
		 0,  1,  0
	};

	points.reserve(array.size());
	for (auto e : array)
		points.push_back(e);

	return points;
}
