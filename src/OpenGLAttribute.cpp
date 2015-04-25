#include "OpenGLAttribute.hpp"

bool OpenGLAttribute::operator<(OpenGLAttribute const & other) const
{
	return this->id < other.id;
}

OpenGLAttribute::OpenGLAttribute(Program const &program, Attribute const &attribute)
	: vertex_array(get_vertex_array(program)), vertex_buffer(get_vertex_buffer(attribute.type_buffer, attribute.value)),
	  id(get_vertex_attrib(attribute.name, this->vertex_array, this->vertex_buffer, program)),
	  num_elements(attribute.value.size())
{}

OpenGLAttribute OpenGLAttribute::get_concret(Program const & program, Attribute const & uniform)
{
	return OpenGLAttribute(program, uniform);
}

GLuint OpenGLAttribute::get_vertex_array(Program const & program)
{
	GLuint vao;

	program.bind();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Util::assert_no_glError();

	return vao;
}

GLuint OpenGLAttribute::get_vertex_buffer(GLenum const type, std::vector<OpenGLValue::element> const & points)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(type, vbo);
	glBufferData(type, points.size() * sizeof(points[0]), points.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	Util::assert_no_glError();

	return vbo;
}

GLuint OpenGLAttribute::get_vertex_attrib(std::string name, GLuint vao, GLuint vbo, Program const &program)
{
	GLint attr;

	//glBindVertexArray(vao);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	attr = glGetAttribLocation(program.get_id(), name.c_str());
	glEnableVertexAttribArray(attr);

	glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(attr);
	//glBindVertexArray(0);

	Util::assert_no_glError();

	return attr;
}

void OpenGLAttribute::draw() const
{
	glBindVertexArray(this->vertex_array);
	//glEnableVertexAttribArray(this->id);
	//glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->num_elements);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(this->id);
	//glBindVertexArray(0);
}
