#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Program.hpp"

#include "OpenGL.hpp"
#include <vector>
#include <string>

class Object : public Util::ref_counted {
public:
	Object(std::string const name, std::vector<GLfloat> const & points);
	~Object();

	void draw() const;

	bool operator<(Object const & obj) const;

private:
	Program program;

	GLuint const vertex_array;
	GLuint const vertex_buffer;
	GLuint const vertex_attrib;

	size_t num_elements;

	static GLuint get_vertex_array();
	static GLuint get_vertex_buffer(std::vector<GLfloat> const & points);
	static GLuint get_vertex_attrib(GLuint const vertex_attrib);
};

#endif
