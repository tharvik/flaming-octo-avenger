#ifndef SHADER_HPP
#define SHADER_HPP

#include "OpenGL.hpp"

#include <string>

/**
 * Dummy class to differentiate between Fragment and Vertex
 */
class Fragment {};

/**
 * Dummy class to differentiate between Fragment and Vertex
 */
class Vertex {};

/**
 * A shader if an OpenGL unit, a part of the pipeline
 */
template<class T>
class Shader {
public:
	/**
	 * Construct a new Shader based on the name given
	 *
	 * @param name name of the file to load
	 */
	Shader(std::string name);

	/**
	 * Return the Shader id as allocated by OpenGL
	 */
	GLuint const id;

private:

	/**
	 * Read and return the content of a file as a string
	 *
	 * @param path path of the file to load
	 *
	 * @return std::string version of the file
	 */
	std::string read_file(std::string path);

	/**
	 * Compile the Shader with the given path and the given OpenGL type
	 *
	 * @param path path to load the file from
	 * @param type type of the Shader; one of GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
	 *
	 * @return id returned by OpenGL
	 */
	GLuint create_shader(std::string path, GLenum type);
};

#endif
