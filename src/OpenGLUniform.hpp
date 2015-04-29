#ifndef FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H
#define FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H

#include "Program.hpp"
#include "Attribute.hpp"
#include "Uniform.hpp"

class OpenGLUniform {
public:
	OpenGLUniform(Program const & program, Uniform const & uniform);

	bool operator<(OpenGLUniform const & other) const;

private:
	std::string const name;
	GLuint const id;

	static GLuint get_id(Program const & program, Uniform const &uniform);
};


#endif //FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H
