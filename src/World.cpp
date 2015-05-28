#include <iostream>
#include "World.hpp"

#include "Util.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

	mvp = glm::ortho(-4.0f/3.0f, 4.0f/3.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	mvp = glm::rotate(mvp, -0.56f, glm::vec3(0.64f,0.08f,0.0f));

	glfwGetWindowSize(window, &this->width, &this->height);

	Util::assert_no_glError();

	world = this;
}

World::~World() {
	glfwTerminate();
}

void World::key_callback(GLFWwindow* window,
			int key, int /*scancode*/, int action, int mods)
{
	if (action == GLFW_RELEASE || mods != 0)
		return;
	
	glm::mat4 & mvp = world->mvp;

	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_LEFT:
			mvp = glm::rotate(mvp, 0.01f, glm::vec3(0.0f,1.0f,0.0f));
			break;
		case GLFW_KEY_RIGHT:
			mvp = glm::rotate(mvp, -0.01f, glm::vec3(0.0f,1.0f,0.0f));
			break;

		case GLFW_KEY_UP:
			mvp = glm::rotate(mvp, 0.01f, glm::vec3(1.0f,0.0f,0.0f));
			break;
		case GLFW_KEY_DOWN:
			mvp = glm::rotate(mvp, -0.01f, glm::vec3(1.0f,0.0f,0.0f));
			break;

		case GLFW_KEY_Q:
			mvp = glm::rotate(mvp, 0.01f, glm::vec3(0.0f,0.0f,1.0f));
			break;
		case GLFW_KEY_E:
			mvp = glm::rotate(mvp, -0.01f, glm::vec3(0.0f,0.0f,1.0f));
			break;

	}

	world->update_objects();
}

void World::error_callback(int error, const char* description)
{
	std::cerr << error << ":" << description << std::endl;
}

void World::window_size_callback(GLFWwindow* window, int width, int height)
{
	world->width = width;
	world->height = height;
}

Uniform World::get_mvp() const
{
	OpenGLValue value(GL_FLOAT, mvp);
	Uniform uniform("mvp", value);

	return uniform;
}

void World::add_object(Object obj)
{
	obj.add_uniform(get_mvp());

	this->objects.insert(obj);
}

void World::update_objects()
{
	Uniform uniform = get_mvp();

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
