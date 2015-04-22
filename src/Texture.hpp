#ifndef FLAMING_OCTO_AVENGER_TEXTURE_H
#define FLAMING_OCTO_AVENGER_TEXTURE_H

#include "Program.hpp"

#include "OpenGL.hpp"

#include <string>

class Texture {

public:
	Texture(std::string filename, std::string name);

	std::string const name;
	GLuint const id;

private:
	GLuint const buffer_id;

	static GLuint load_texture(std::string filename, std::string name);
	static GLuint get_id();
};

#endif //FLAMING_OCTO_AVENGER_TEXTURE_H
