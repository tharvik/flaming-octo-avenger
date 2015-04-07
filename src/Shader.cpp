#include "Shader.hpp"

#include "Object.hpp"
#include "Util.hpp"

#include <fstream>
#include <iostream>

#define shader_base_path "shaders/"

class shader_fail_to_compile : public Util::base_exception {

public:
	shader_fail_to_compile(GLuint shader)
		: Util::base_exception("Fail to compile shader:\n" +
				       get_log(shader))
	{}

private:
	static std::string get_log(GLuint shader)
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		GLchar *log_c = new GLchar[length];
		glGetShaderInfoLog(shader, length, NULL, log_c);

		std::string log(log_c, length);

		delete log_c;

		return log;
	}

};

class file_not_found : public Util::base_exception {

public:
	file_not_found(std::string const filename)
		: Util::base_exception("Unable to open file \"" + filename + "\"")
	{}

};

template<>
Shader<Fragment>::Shader(std::string name)
	: id(create_shader(shader_base_path + name + "_fshader.glsl",
			   GL_FRAGMENT_SHADER))
{}

template<>
Shader<Vertex>::Shader(std::string name)
	: id(create_shader(shader_base_path + name + "_vshader.glsl",
			   GL_VERTEX_SHADER))
{}

template<class T>
GLuint Shader<T>::create_shader(std::string path, GLenum type)
{
	std::string content = read_file(path);
	GLchar const *content_ptr = content.data();

	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &content_ptr, NULL);
	glCompileShader(id);

	GLint err;
	glGetShaderiv(id, GL_COMPILE_STATUS, &err);

	if (err == GL_FALSE)
		throw shader_fail_to_compile(id);

	Util::assert_no_glError();

	return id;
}

template<class T>
std::string Shader<T>::read_file(std::string filename)
{
	std::ifstream file(filename);
	if (!file)
		throw file_not_found(filename);

	file.seekg (0, file.end);
	size_t length = file.tellg();
	file.seekg (0, file.beg);

	char file_content[length];
	file.read(file_content, length);
	std::string content(file_content, length);

	return content;
}
