#include "Object.hpp"

#include <iostream>

Object::Object(std::string const name, std::set<Attribute> attributes, std::set<Uniform> uniforms, std::set<Texture> textures)
	: program(name),
	  attributes(get_attribs(program, attributes)),
	  textures(textures)
{
	set_uniforms(uniforms);
}

void Object::set_uniforms(std::set<Uniform> uniforms)
{
	this->uniforms.clear();

	for (auto const & uniform : uniforms)
		this->uniforms.insert(OpenGLUniform::get_concret(this->program, uniform));
}

Object::~Object()
{
	if (!last_ref())
		return;

	for (auto const & attrib : attributes) {
		glDeleteVertexArrays(1, &attrib.vertex_array);
		glDeleteBuffers(1, &attrib.vertex_buffer);
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

		glBindVertexArray(attrib.vertex_array);
		glEnableVertexAttribArray(attrib.id);
		glBindBuffer(GL_ARRAY_BUFFER, attrib.vertex_buffer);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, attrib.num_elements);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(attrib.id);
		glBindVertexArray(0);
	}

	program.unbind();

	Util::assert_no_glError();
}

std::set<OpenGLAttribute>
	Object::get_attribs(Program const & program, std::set<Attribute> attribs)
{
	std::set<OpenGLAttribute> attrs;

	for (auto const & attri : attribs)
		attrs.insert(OpenGLAttribute::get_concret(program, attri));

	return attrs;
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
