#include "Object.hpp"

#include "Util.hpp"

#include <iostream>

Object::Object(std::string const name, std::vector<Attribute> attributes, std::vector<Attribute> uniformes)
	: program(name),
	  attributes(get_attribs(program, attributes))
{
	for (Attribute const & attrib : uniformes)
		set_uniforme(attrib, program);
}

Object::~Object()
{
	if (!last_ref())
		return;

	for (auto const & attrib : attributes) {

		GLuint vertex_array = std::get<0>(attrib);
		GLuint vertex_buffer = std::get<1>(attrib);

		glDeleteVertexArrays(1, &vertex_array);
		glDeleteBuffers(1, &vertex_buffer);
	}
}

bool Object::operator<(Object const & obj) const
{
	return this->program < obj.program;
}

void Object::draw() const
{
	program.bind();

	for (auto & attrib : attributes) {

		GLuint vertex_array = std::get<0>(attrib);
		GLuint vertex_buffer = std::get<1>(attrib);
		GLuint vertex_attrib = std::get<2>(attrib);
		size_t num_elements = std::get<3>(attrib);

		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(vertex_attrib);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, num_elements);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(vertex_attrib);
		glBindVertexArray(0);
	}

	program.unbind();

	Util::assert_no_glError();
}

std::vector<std::tuple<GLuint, GLuint, GLuint, size_t>>
	Object::get_attribs(Program const & program, std::vector<Attribute> attribs)
{
	std::vector<std::tuple<GLuint, GLuint, GLuint, size_t>> attrs;

	for (Attribute const & attri : attribs)
		attrs.push_back(get_attrib(program, attri));

	return attrs;
}

std::tuple<GLuint, GLuint, GLuint, size_t> Object::get_attrib(Program const & program, Attribute const & attrib)
{
	GLuint vertex_array;
	GLuint vertex_buffer;
	GLuint vertex_attrib;
	size_t num_elements;

	vertex_array = get_vertex_array();
	vertex_buffer = get_vertex_buffer(attrib.value);
	vertex_attrib = get_vertex_attrib(attrib.name, vertex_array, vertex_buffer, program);
	num_elements = attrib.value.size();

	return std::make_tuple(vertex_array, vertex_buffer, vertex_attrib, num_elements);
}

GLuint Object::get_vertex_array()
{
	GLuint vao;

	glGenVertexArrays(1, &vao);

	return vao;
}

GLuint Object::get_vertex_buffer(std::vector<GLfloat> const & points)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points[0]) * points.size(), points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Util::assert_no_glError();

	return vbo;
}

GLuint Object::get_vertex_attrib(std::string name, GLuint vao, GLuint vbo, Program const &program)
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

void Object::set_uniforme(Attribute const & attrib, Program const &program)
{
	GLuint attr;

	attr = glGetUniformLocation(program.get_id(), attrib.name.c_str());
	glUniformMatrix4fv(attr, 1, GL_FALSE, attrib.value.data());

	Util::assert_no_glError();
}
