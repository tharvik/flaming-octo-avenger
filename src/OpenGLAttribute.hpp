#ifndef FLAMING_OCTO_AVENGER_OPENGLATTRIBUTE_H
#define FLAMING_OCTO_AVENGER_OPENGLATTRIBUTE_H

#include "Program.hpp"
#include "Attribute.hpp"

#include <set>

class OpenGLAttribute {

public:
	/**
	 * Vertex array buffer; set of information about a given buffer, size; not much used yet
	 */
	GLuint vertex_array;

	/**
	 * Where, in OpenGL, are the vertex stored
	 */
	std::set<GLuint> vertex_buffers;

	/**
	 * Location of the Attribute.name inside OpenGL
	 */
	GLuint id;

	/**
	 * Number of elements in the vertex_buffer
	 */
	GLsizei num_elements;

	/**
	 * Allow inserting into a set; base on the id
	 *
	 * @param other attribute to compare with
	 *
	 * @return this->id < other.id;
	 */
	bool operator<(OpenGLAttribute const & other) const;

	/**
	 * @todo directly use the constructor
	 */
	static OpenGLAttribute get_concret(Program const & program, Attribute const & uniform);

	void draw() const;

private:
	OpenGLAttribute(Program const & program, Attribute const & uniform);

	/**
	 * Return a vertex array
	 *
	 * @return a vertex array
	 */
	static GLuint get_vertex_array(Program const & program);

	/**
	 * Load the points in OpenGL and return the id of the buffer
	 *
	 * @param type type of buffer in OpenGL
	 * @param points points to load into OpenGL
	 *
	 * @return id of the buffer in OpenGL
	 */
	//static std::set<GLuint> get_vertex_buffer(std::set<std::tuple<GLenum const type, std::vector<OpenGLValue::element> const & points);
	static std::set<GLuint> get_vertex_buffers(std::set<std::tuple<GLenum, OpenGLValue>> values);

	/**
	 * Return the id of the vertex attribute
	 *
	 * @param name name of the Attribute to look for
	 * @param vertex_array vertex array to bind
	 * @param vertex_buffer vertex buffer to read the points from
	 * @param program Program to look the Attribute into
	 *
	 * @return the id of the vertex attribute
	 */
	static GLuint get_vertex_attrib(std::string name, GLuint const vertex_array, std::set<GLuint> const vertex_buffer, Program const &program);

	static GLsizei get_num_elements(std::set<std::tuple<GLenum, OpenGLValue>> const & values);
};


#endif //FLAMING_OCTO_AVENGER_OPENGLATTRIBUTE_H
