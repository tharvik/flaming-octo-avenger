#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"
#include "Attribute.hpp"

#include <string>

/**
 * Represent a simple plane which will soon evolve into a montain
 */
class Plane : public Object {

public:
	/**
	 * Construct a Plane, forward everything to Object
	 */
	Plane(std::string const name,
	      std::set<Uniform> const uniforms = std::set<Uniform>(),
	      std::set<Attribute> const attributes = std::set<Attribute>(),
	      std::set<Texture> const textures = std::set<Texture>(),
	      size_t const size = 100);

private:
	size_t const size;

	/**
	 * Return all the attributes
	 *
	 * @return the attributes
	 */
	static std::set<Attribute>
		get_attributes(std::set<Attribute> const attributes,
			       size_t const size);

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
