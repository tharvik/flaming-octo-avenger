#ifndef MOUNTAIN_HPP
#define MOUNTAIN_HPP

#include "Plane.hpp"
#include "Attribute.hpp"

#include <string>

/**
 * Represent a simple plane which will soon evolve into a montain
 */
class Mountain : public Plane {

public:
	/**
	 * Construct a Plane, forward everything to Object
	 */
	Mountain(size_t const size = 512);

private:
	size_t const size;

	/**
	 * Return all the uniformes
	 *
	 * @return the uniformes
	 */
	static std::set<Uniform> get_uniformes();

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
	static std::set<Texture> get_texture(size_t const size);
};

#endif
