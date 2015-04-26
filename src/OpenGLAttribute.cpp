#include "OpenGLAttribute.hpp"

bool OpenGLAttribute::operator<(OpenGLAttribute const & other) const
{
	return this->id < other.id;
}

OpenGLAttribute::OpenGLAttribute(Program const &program, Attribute const &attribute)
	: vertex_array(get_vertex_array(program)), vertex_buffers(get_vertex_buffers(attribute.values)),
	  id(get_vertex_attrib(attribute.name, this->vertex_array, this->vertex_buffers, program)),
	  num_elements(get_num_elements(attribute.values))
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
		std::vector<OpenGLValue::element> const vals = std::get<1>(value).value;

		GLuint vbo;

		glGenBuffers(1, &vbo);

		glBindBuffer(type, vbo);
		glBufferData(type, vals.size() * sizeof(vals[0]), vals.data(), GL_STATIC_DRAW);
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

	glDrawArrays(GL_TRIANGLE_STRIP, 0, this->num_elements);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(this->id);
	//glBindVertexArray(0);
}

GLsizei OpenGLAttribute::get_num_elements(std::set<std::tuple<GLenum, OpenGLValue>> const & values)
{
	GLsizei size = 0;
	bool got_element_array = false;

	for (auto const & value : values) {

		GLenum type = std::get<0>(value);
		OpenGLValue val(std::get<1>(value));

		GLsizei const val_size = val.value.size();

		if (type == GL_ELEMENT_ARRAY_BUFFER) {
			got_element_array = true;
			size = val_size;
		}

		if (!got_element_array && val_size > size)
			size = val_size;
	}

	return size;
}
