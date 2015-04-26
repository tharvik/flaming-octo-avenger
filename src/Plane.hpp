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
	Plane(size_t const size = 100);

private:
	size_t const size;

	/**
	 * Return all the attributes
	 *
	 * @return the attributes
	 */
	static std::set<Attribute> get_attributes(size_t const size);

	/**
	 * Return all the uniformes
	 *
	 * @return the uniformes
	 */
	static std::set<Uniform> get_uniformes();

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

	/**
	 * Return the model-view-projection matrix
	 *
	 * @return the model-view-projection matrix
	 */
	static glm::mat4 get_mvp();

	/**
	 * Return all the textures
	 *
	 * @return all the textures
	 */
	static std::set<Texture> get_texture();
};

#endif
