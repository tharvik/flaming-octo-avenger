#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Shader.hpp"

#include "OpenGL.hpp"
#include "Util.hpp"

#include <string>

class Program : public Util::ref_counted {

public:
	Program(std::string const name);
	~Program();

	void bind() const;
	void unbind() const;

private:
	Shader<Vertex> vshader;
	Shader<Fragment> fshader;

	GLuint const id;

	static GLuint get_program(Shader<Vertex> vshader,
				  Shader<Fragment> fshader);
};

#endif
