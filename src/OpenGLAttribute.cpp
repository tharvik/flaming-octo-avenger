#include "OpenGLAttribute.hpp"

bool OpenGLAttribute::operator<(OpenGLAttribute const & other) const
{
	return this->id < other.id;
}

OpenGLAttribute::OpenGLAttribute(Program const &program, Attribute const &attribute)
	: vertex_array(get_vertex_array(program)), vertex_buffers(get_vertex_buffers(attribute.values)),
	  id(get_vertex_attrib(attribute.name, this->vertex_array, this->vertex_buffers, program)),
	  is_indexed(get_indexed(attribute.values)), num_elements(get_num_elements(is_indexed, attribute.values))
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

//GLuint OpenGLAttribute::get_vertex_buffer(GLenum const type, std::vector<OpenGLValue::element> const & points)
std::set<GLuint> OpenGLAttribute::get_vertex_buffers(std::set<std::tuple<GLenum, OpenGLValue>> values)
{
	std::set<GLuint> vbos;

	for(auto const & value : values) {

		GLenum const type = std::get<0>(value);
		OpenGLValue const val = std::get<1>(value);

		GLuint vbo;

		size_t size;
		switch (val.type) {
			case GL_FLOAT: size = sizeof(GL_FLOAT); break;
			case GL_UNSIGNED_INT: size = sizeof(GL_UNSIGNED_INT); break;
			default: assert(false);
		}

		glGenBuffers(1, &vbo);
		glBindBuffer(type, vbo);
		glBufferData(type, val.value.size() * size, val.value.data(), GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		vbos.insert(vbo);

		Util::assert_no_glError();
	}

	return vbos;
}

GLuint OpenGLAttribute::get_vertex_attrib(std::string name, GLuint vao, std::set<GLuint> vbo, Program const &program)
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

	if (is_indexed)
		glDrawElements(GL_TRIANGLES, this->num_elements, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLE_STRIP, 0, this->num_elements);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(this->id);
	//glBindVertexArray(0);
}

bool OpenGLAttribute::get_indexed(std::set<std::tuple<GLenum, OpenGLValue>> const & values)
{
	for (auto const & value : values) {
		GLenum type = std::get<0>(value);
		if (type == GL_ELEMENT_ARRAY_BUFFER)
			return true;
	}
}

GLsizei OpenGLAttribute::get_num_elements(bool is_indexed, std::set<std::tuple<GLenum, OpenGLValue>> const & values)
{
	GLsizei size = 0;

	for (auto const & value : values) {

		GLenum type = std::get<0>(value);
		OpenGLValue val(std::get<1>(value));
		GLsizei const val_size = val.value.size();

		if (is_indexed) {
			if (type == GL_ELEMENT_ARRAY_BUFFER) {
				size = val_size;
			}
		} else {
			if (val_size > size) {
				size = val_size;
			}
		}
	}

	return size;
}
