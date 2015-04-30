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

	glm::mat4 mat;

	mat[0] = { 0.970836,    0, -0.485418,         0};
	mat[1] = {-0.182574,    0.912871, -0.365148, -0.228218};
	mat[2] = {-0.0408248,  -0.0408248,-0.0816497,  0.500104};
	mat[3] = { 0,           0,         0,         1};

	this->mvp = mat;

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

	float const angle = 0.01;
	float const scale = 1;

	glm::mat4 x_plus = glm::rotate(angle, glm::vec3(1, 0, 0));
	glm::mat4 y_plus = glm::rotate(angle, glm::vec3(0, 1, 0));
	glm::mat4 z_plus = glm::rotate(angle, glm::vec3(0, 0, 1));
	glm::mat4 x_minus = glm::rotate(-angle, glm::vec3(1, 0, 0));
	glm::mat4 y_minus = glm::rotate(-angle, glm::vec3(0, 1, 0));
	glm::mat4 z_minus = glm::rotate(-angle, glm::vec3(0, 0, 1));

	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_LEFT:
			mvp = x_plus * mvp;
			break;
		case GLFW_KEY_RIGHT:
			mvp = x_minus * mvp;
			break;

		case GLFW_KEY_UP:
			mvp = y_plus * mvp;
			break;
		case GLFW_KEY_DOWN:
			mvp = y_minus * mvp;
			break;

		case GLFW_KEY_A:
			mvp = z_plus * mvp;
			break;
		case GLFW_KEY_D:
			mvp = z_minus * mvp;
			break;

		case GLFW_KEY_W:
			mvp *= scale;
			break;
		case GLFW_KEY_S:
			mvp /= scale;
			break;
	}

	/*std::cout << mvp.w << '\t'
		  << mvp.x << '\t'
		  << mvp.y << '\t'
		  << mvp.z << std::endl;*/

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
