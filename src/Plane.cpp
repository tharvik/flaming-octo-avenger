#include "Plane.hpp"

#include <array>

Plane::Plane()
	: Object("plane", get_points())
{
}

std::vector<GLfloat> Plane::get_points()
{
	std::vector<GLfloat> points;

	std::array<GLfloat, 4 * 3> array = {
		-1.0f, -1.0f, 0.0f,
		+1.0f, -1.0f, 0.0f,
		-1.0f, +1.0f, 0.0f,
		+1.0f, +1.0f, 0.0f
	};

	points.reserve(array.size());
	for (auto e : array)
		points.push_back(e);

	return points;
}
