#include "Object.hpp"

#include "Util.hpp"

#include <iostream>

Object::Object(std::string const name, std::vector<GLfloat> const & points)
	:
	  program(name),
	  vertex_array(get_vertex_array()),
	  vertex_buffer(get_vertex_buffer(points)),
	  vertex_attrib(get_vertex_attrib(vertex_buffer)),
	  num_elements(points.size() / 3)
{}

Object::~Object()
{
	if (last_ref()) {
		glDeleteBuffers(1, &vertex_buffer);
		glDeleteVertexArrays(1, &vertex_array);
	}
}

bool Object::operator<(Object const & obj) const
{
	return this->vertex_buffer < obj.vertex_buffer;
}

void Object::draw() const
{
	program.bind();
	Util::assert_no_glError();
	glBindVertexArray(vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	Util::assert_no_glError();

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->num_elements);
	Util::assert_no_glError();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Util::assert_no_glError();
	glBindVertexArray(0);
	program.unbind();

	Util::assert_no_glError();
}

GLuint Object::get_vertex_array()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);

	return vao;
}

GLuint Object::get_vertex_attrib(GLuint vbo)
{
	GLuint attr = 0;

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(attr);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	Util::assert_no_glError();

	return attr;
}


GLuint Object::get_vertex_buffer(std::vector<GLfloat> const & points)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points[0]), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Util::assert_no_glError();

	return vbo;
}
