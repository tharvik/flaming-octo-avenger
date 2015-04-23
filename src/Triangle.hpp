#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"

#include <string>

/**
 * Debug Object; just show a red triangle
 */
class Triangle : public Object {

public:
	/**
	 * Construct a Triangle
	 */
	Triangle();

private:
	/**
	 * Get all the attributes
	 *
	 * @return the set of attributes to pass to the parent
	 */
	static std::set<Attribute> get_attributes();

	/**
	 * Return the points to draw
	 *
	 * @return the points just created
	 */
	static std::vector<GLfloat> get_points();
};

#endif
