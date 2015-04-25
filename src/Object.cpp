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

	for (auto const & attrib : attributes)
		attrib.draw();

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
