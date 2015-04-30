#include <iostream>
#include "World.hpp"

#include "Util.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PI 3.141592

World *World::world;

World::World()
{}

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

	Util::assert_no_glError();

	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_NO_ERROR) {
		std::cerr << glewGetErrorString(err) << std::endl;
		throw "Unable to start glew"; // TODO use object
	}
	glGetError(); // clean error generated from glew

	glClearColor(0.9, 0.9, 0.9, 1);

	glm::quat quat(0.6, -0.4, 0.2, -0.1);
	this->mvp = quat;

	Util::assert_no_glError();

	world = this;
}

World::~World() {
	glfwTerminate();
}

void World::key_callback(GLFWwindow* window,
			int key, int /*scancode*/, int action, int mods)
{
	if (action != GLFW_PRESS || mods != 0)
		return;

	glm::quat & mvp = world->mvp;

	glm::quat w_unit = glm::quat(0.1,0,0,0);
	glm::quat roll_unit = glm::quat(0,0.1,0,0);
	glm::quat pitch_unit = glm::quat(0,0,0.1,0);
	glm::quat yaw_unit = glm::quat(0,0,0,0.1);

	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_LEFT:
			mvp += roll_unit;
			break;
		case GLFW_KEY_RIGHT:
			mvp += -roll_unit;
			break;

		case GLFW_KEY_UP:
			mvp += pitch_unit;
			break;
		case GLFW_KEY_DOWN:
			mvp += -pitch_unit;
			break;

		case GLFW_KEY_A:
			mvp += yaw_unit;
			break;
		case GLFW_KEY_D:
			mvp += -yaw_unit;
			break;

		case GLFW_KEY_W:
			mvp += w_unit;
			break;
		case GLFW_KEY_S:
			mvp += -w_unit;
			break;
	}

	world->update_objects();
}

void World::error_callback(int error, const char* description)
{
	std::cerr << error << ":" << description << std::endl;
}

void World::add_object(Object obj)
{
	OpenGLValue value(GL_FLOAT, glm::mat4_cast(mvp));
	Uniform uniform("mvp", value);

	obj.add_uniform(uniform);

	this->objects.insert(obj);
}

void World::update_objects()
{
	OpenGLValue value(GL_FLOAT, glm::mat4_cast(this->mvp));
	Uniform uniform("mvp", value);

	for (auto object : this->objects)
		object.add_uniform(uniform);
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
