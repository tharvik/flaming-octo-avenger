#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Object.hpp"

class Skybox : public Object {

public:
	Skybox(size_t const size = 1024);

private:
	/**
	 * Return all the attributes
	 *
	 * @return the attributes
	 */
	static std::set<Attribute> get_attributes(size_t const size);

	/**
	 * Return the points to draw
	 *
	 * @return the points to draw
	 */
	static std::vector<GLfloat> get_points(size_t const size);

	/**
	 * Return the indices of the points to draw
	 *
	 * @return the indices of the points to draw
	 */
	static std::vector<GLuint> get_indices(size_t const size);
};

#endif
