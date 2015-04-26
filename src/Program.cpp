#include "Program.hpp"

#include "Util.hpp"

Program::Program(std::string const name)
	: vshader(name), fshader(name), id(get_program(vshader, fshader))
{}

GLuint Program::get_program(Shader<Vertex> vshader, Shader<Fragment> fshader)
{
	GLuint id = glCreateProgram();

	glAttachShader(id, vshader.id);
	glAttachShader(id, fshader.id);

	glLinkProgram(id);

	glUseProgram(id);

	Util::assert_no_glError();

	return id;
}

Program::~Program()
{
	if (last_ref())
		glDeleteProgram(this->id);
}

void Program::bind() const
{
	glUseProgram(this->id);
}

void Program::unbind() const
{
	glUseProgram(0);
}

bool Program::operator<(Program const & obj) const
{
	return this->id < obj.id;
}
