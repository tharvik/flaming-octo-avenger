#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Attribute.h"
#include "Program.hpp"
#include "Texture.hpp"

#include "OpenGL.hpp"
#include "Uniform.h"
#include "Attribute.h"
#include "OpenGLUniform.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>

/**
 * Superclass of every drawable object
 */
class Object : public Util::ref_counted {
public:
	/**
	 * Construct a Object with the given name, attributes, uniformes and textures
	 *
	 * @param name name of the Program to load
	 * @param attributes set of Attribute
	 * @param uniformes set of uniforme
	 * @param textures set of Texture
	 */
	Object(std::string const name, std::set<Attribute> attributes, std::set<Uniform> uniformes, std::set<Texture> textures);

	/**
	 * Destructor; need to delete the allocated buffers
	 */
	~Object();

	/**
	 * Draw it
	 */
	void draw() const;

	/**
	 * Allow inserting into a set; base on the program id
	 *
	 * @param obj Object to compare to
	 *
	 * @return this->program < obj.program;
	 */
	bool operator<(Object const & obj) const;

private:
	/**
	 * The Program to use
	 */
	Program program;

	/**
	 * Struct easier to work with when on the OpenGL side than the Attribute class
	 */
	struct attribute {

		/**
		 * Vertex array buffer; set of information about a given buffer, size; not much used yet
		 */
		GLuint vertex_array;

		/**
		 * Where, in OpenGL, are the vertex stored
		 */
		GLuint vertex_buffer;

		/**
		 * Number of elements in the vertex_buffer
		 */
		size_t num_elements;

		/**
		 * Location of the Attribute.name inside OpenGL
		 */
		GLuint id;

		/**
		 * Allow inserting into a set; base on the id
		 *
		 * @param other attribute to compare with
		 *
		 * @return this->id < other.id;
		 */
		bool operator<(attribute const & other) const;
	};

	/**
	 * Set of OpenGLUniform to attach
	 */
	std::set<OpenGLUniform> uniforms;

	void set_uniforms(std::set<Uniform> uniforms);

	/**
	 * Set of attribute to attach
	 */
	std::set<attribute> const attributes;

	/**
	 * Set of Texture to attach
	 */
	std::set<Texture> const textures;

	/**
	 * Return the set of attribute based on the given set of Attribute
	 *
	 * @param program Program to find the given Attribute
	 * @param attribs set of Attribute to set
	 *
	 * @return the set of attribute based on the given set of Attribute
	 */
	static std::set<attribute>
		get_attribs(Program const & program, std::set<Attribute> attribs);

	/**
	 * Return an attribute base on the given Attribute
	 *
	 * @param program to find the Attribute into
	 * @param attrib Attribute to find
	 *
	 * @return an attribute base on the given Attribute
	 */
	static attribute
		get_attrib(Program const & program, Attribute const & attrib);

	/**
	 * Return a vertex array
	 *
	 * @return a vertex array
	 */
	static GLuint get_vertex_array();

	/**
	 * Load the points in OpenGL and return the id of the buffer
	 *
	 * @param points points to load into OpenGL
	 *
	 * @return id of the buffer in OpenGL
	 */
	static GLuint get_vertex_buffer(std::vector<GLfloat> const & points);

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
	static GLuint get_vertex_attrib(std::string name, GLuint const vertex_array, GLuint const vertex_buffer, Program const &program);

	/**
	 * Set in OpenGL the value of the given Program
	 *
	 * @param program Program to find the given Attribute
	 * @param texture Texture to set
	 */
	static void set_texture(Program const & program, Texture const & texture);
};

#endif
