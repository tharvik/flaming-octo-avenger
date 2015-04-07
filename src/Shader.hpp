#ifndef SHADER_HPP
#define SHADER_HPP

#include "OpenGL.hpp"

#include <string>

class Fragment {};
class Vertex {};

template<class T>
class Shader {
public:
	Shader(std::string name);

	GLuint get_id();

private:
	GLuint const id;

	std::string read_file(std::string filename);
	GLuint create_shader(std::string path, GLenum type);
};

// FIXME find a better way to allow template instantation
template<class T>
GLuint Shader<T>::get_id()
{
	return this->id;
}

#endif
