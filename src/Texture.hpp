#ifndef FLAMING_OCTO_AVENGER_TEXTURE_H
#define FLAMING_OCTO_AVENGER_TEXTURE_H

class Texture;

#include "Program.hpp"

#include "OpenGL.hpp"

#include <string>

/**
 * A Texture is an image to load and to display to OpenGL
 */
class Texture {

public:
	/**
	 * Construct a Texture with the given path and the given GLSL name
	 *
	 * @param filename name of the file to load
	 * @param glsl_name name used in the Shader
	 */
	Texture(std::string filename, std::string glsl_name);

	/**
	 * The name used in GLSL
	 */
	std::string const name;

	/**
	 * The id returned by OpenGL
	 */
	GLuint const id;

	/**
	 * The buffer created with OpenGL
	 */
	GLuint const buffer_id;

	bool operator<(Texture const & other) const;

private:
	/**
	 * Load the texture base on the given path and name use by GLSL
	 *
	 * @param path path of the file to load
	 * @param glsl_name name used in the Shader
	 *
	 * @return the id of the buffer of the loaded texture
	 */
	static GLuint load_texture(GLenum id, std::string path);

	/**
	 * Return a new unique id for the texture
	 *
	 * @return a new unique id for the texture
	 */
	static GLenum get_id();
};

#endif //FLAMING_OCTO_AVENGER_TEXTURE_H
