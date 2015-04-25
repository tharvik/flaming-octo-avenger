#include "OpenGLAttribute.h"

bool OpenGLAttribute::operator<(OpenGLAttribute const & other) const
{
	return this->id < other.id;
}

OpenGLAttribute::OpenGLAttribute(Program const &program, Attribute const &uniform)
	: vertex_array(get_vertex_array()), vertex_buffer(get_vertex_buffer(uniform.value)),
	  id(get_vertex_attrib(uniform.name, this->vertex_array, this->vertex_buffer, program)),
	  num_elements(uniform.value.size())
{}

OpenGLAttribute OpenGLAttribute::get_concret(Program const & program, Attribute const & uniform)
{
	return OpenGLAttribute(program, uniform);
}

GLuint OpenGLAttribute::get_vertex_array()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);

	return vao;
}

GLuint OpenGLAttribute::get_vertex_buffer(std::vector<GLfloat> const & points)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points[0]) * points.size(), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Util::assert_no_glError();

	return vbo;
}

GLuint OpenGLAttribute::get_vertex_attrib(std::string name, GLuint vao, GLuint vbo, Program const &program)
{
	GLuint attr;

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	attr = glGetAttribLocation(program.get_id(), name.c_str());
	glEnableVertexAttribArray(attr);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(attr);
	glBindVertexArray(0);

	Util::assert_no_glError();

	return attr;
}
