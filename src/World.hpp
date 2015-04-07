#ifndef WORLD_HPP
#define WORLD_HPP

#include "Object.hpp"

#include "OpenGL.hpp"

#include <set>

class World {
public:
	World(std::string const name);
	~World();

	void add_object(Object obj);

	void main_loop();

private:
	std::set<Object> objects;
	GLFWwindow *window;

	void draw() const;

	static void key_callback(GLFWwindow* window,
				 int key, int scancode, int action, int mods);
	static void error_callback(int error, const char* description);

};

#endif
