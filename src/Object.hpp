#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Program.hpp"
#include "Attribute.hpp"

#include "OpenGL.hpp"

#include <string>
#include <tuple>
#include <vector>

class Object : public Util::ref_counted {
public:
	Object(std::string const name, std::vector<Attribute> attribs);
	~Object();

	void draw() const;

	bool operator<(Object const & obj) const;

private:
	Program program;

	/**
	 * vertex array,
	 * vertex buffer,
	 * attribute id,
	 * number of elements
	 */
	std::vector<std::tuple<GLuint, GLuint, GLuint, size_t>> const attributes;

	static std::vector<std::tuple<GLuint, GLuint, GLuint, size_t>>
		get_attribs(Program const & program, std::vector<Attribute> attribs);
	static std::tuple<GLuint, GLuint, GLuint, size_t>
		get_attrib(Program const & program, Attribute const & attrib);

	static GLuint get_vertex_array();
	static GLuint get_vertex_buffer(std::vector<GLfloat> const & points);
	static GLuint get_vertex_attrib(GLuint const vertex_array, GLuint const vertex_attrib, Program const &program);
};

#endif
