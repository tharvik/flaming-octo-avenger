#include "OpenGLUniform.hpp"

#include "OpenGL.hpp"

OpenGLUniform::OpenGLUniform(GLuint id)
	: id(id)
{}

bool OpenGLUniform::operator<(OpenGLUniform const & other) const
{
	return this->id < other.id;
}

/**
 * @todo allow other uniform than mat4
 */
OpenGLUniform OpenGLUniform::get_concret(Program const & program, Uniform const &uniform)
{
	GLuint id;

	id = glGetUniformLocation(program.get_id(), uniform.name.c_str());
	glUniformMatrix4fv(id, 1, GL_FALSE, uniform.value.as<GLfloat>().data());

	Util::assert_no_glError();

	return OpenGLUniform(id);
}
