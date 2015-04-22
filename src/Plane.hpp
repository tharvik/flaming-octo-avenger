#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

#include <string>

class Plane : public Object {

public:
	Plane();

private:
	static std::vector<Attribute> get_attributes();
	static std::vector<Attribute> get_uniformes();

	static std::vector<GLfloat> get_points();
	static glm::mat4 get_mvp();
	static std::set<Texture> get_texture();
};

#endif
