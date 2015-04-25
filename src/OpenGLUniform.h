#ifndef FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H
#define FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H

#include "Program.hpp"
#include "Attribute.h"
#include "Uniform.h"

class OpenGLUniform {
public:
	bool operator<(OpenGLUniform const & other) const;

	static OpenGLUniform get_concret(Program const & program, Uniform const & uniform);

private:
	OpenGLUniform(GLuint id);

	GLuint const id;
};


#endif //FLAMING_OCTO_AVENGER_OPENGLUNIFORM_H
