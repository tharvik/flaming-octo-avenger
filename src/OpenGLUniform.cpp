#include "OpenGLUniform.hpp"

#include "OpenGL.hpp"

#include <iostream>

OpenGLUniform::OpenGLUniform(Program const & program, Uniform const & uniform)
	: name(uniform.name), id(get_id(program, uniform))
{}

bool OpenGLUniform::operator<(OpenGLUniform const & other) const
{
	return this->name < other.name;
}

/**
 * @todo allow other uniform than mat4
 * @todo fail on glGetUniformLocation == -1
 */
GLuint OpenGLUniform::get_id(Program const & program, Uniform const &uniform)
{
	GLuint id;

	program.bind();

	id = glGetUniformLocation(program.id, uniform.name.c_str());
	glUniformMatrix4fv(id, 1, GL_FALSE, uniform.value.as<GLfloat>().data());

	Util::assert_no_glError();

	return id;
}
