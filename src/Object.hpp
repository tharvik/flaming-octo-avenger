#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Attribute.hpp"
#include "Program.hpp"
#include "Texture.hpp"

#include "OpenGL.hpp"

#include <set>
#include <string>
#include <tuple>
#include <vector>

class Object : public Util::ref_counted {
public:
	Object(std::string const name, std::vector<Attribute> attributes, std::vector<Attribute> uniformes, std::set<Texture> textures);
	~Object();

	void draw() const;

	bool operator<(Object const & obj) const;

private:
	Program program;

	struct attribute {
		GLuint vertex_array;
		GLuint vertex_buffer;
		GLuint id;
		size_t num_elements;
	};
	std::vector<attribute> const attributes;
	std::set<Texture> const textures;

	static std::vector<attribute>
		get_attribs(Program const & program, std::vector<Attribute> attribs);

	static attribute
		get_attrib(Program const & program, Attribute const & attrib);

	static GLuint get_vertex_array();
	static GLuint get_vertex_buffer(std::vector<GLfloat> const & points);
	static GLuint get_vertex_attrib(std::string name, GLuint const vertex_array, GLuint const vertex_attrib, Program const &program);
	static void set_uniforme(Attribute const & attrib, Program const &program);
	static void set_texture(Program const & program, Texture const & texture);
};

#endif
