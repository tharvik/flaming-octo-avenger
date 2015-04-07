#include "World.hpp"

#include "Util.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#include <cassert>
#include <iostream>

World::World(std::string const name)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() != GL_TRUE)
		throw "Unable to start glfw"; // TODO use object

	// enforce a OpenGL 3.2+ context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, name.c_str(),
				  NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	glGetError(); // clean error generated from glew
	if (err != GLEW_OK) {
		std::cerr << glewGetErrorString(err) << std::endl;
		throw "Unable to start glew"; // TODO use object
	}

	glClearColor(0.9, 0.9, 0.9, 1);

	Util::assert_no_glError();
}

World::~World() {
	glfwTerminate();
}

void World::key_callback(GLFWwindow* window,
			int key, int /*scancode*/, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && mods == 0)
	    glfwSetWindowShouldClose(window, GL_TRUE);
}

void World::error_callback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void World::add_object(Object obj)
{
	this->objects.insert(obj);
}

void World::main_loop()
{
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		draw();

		glfwSwapBuffers(window);
	}
}

void World::draw() const
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto const & o : objects)
		o.draw();

	Util::assert_no_glError();
}
