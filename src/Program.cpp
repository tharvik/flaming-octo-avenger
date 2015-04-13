#include "Program.hpp"

#include "Util.hpp"

#include <iostream>

Program::Program(std::string const name)
	: vshader(name), fshader(name), id(get_program(vshader, fshader))
{}

GLuint Program::get_program(Shader<Vertex> vshader, Shader<Fragment> fshader)
{
	GLuint id = glCreateProgram();

	glAttachShader(id, vshader.get_id());
	glAttachShader(id, fshader.get_id());

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

GLuint Program::get_id() const
{
	return this->id;
}
