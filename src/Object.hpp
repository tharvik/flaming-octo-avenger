#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Attribute.hpp"
#include "OpenGLAttribute.hpp"
#include "OpenGLTexture.hpp"
#include "OpenGLUniform.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"

#include "OpenGL.hpp"

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
	 * Set of OpenGLUniform to attach
	 */
	std::set<OpenGLUniform> uniforms;

	void set_uniforms(std::set<Uniform> uniforms);

	/**
	 * Set of attribute to attach
	 */
	std::set<OpenGLAttribute> const attributes;

	/**
	 * Set of Texture to attach
	 */
	std::set<OpenGLTexture> const textures;

	/**
	 * Return the set of attribute based on the given set of Attribute
	 *
	 * @param program Program to find the given Attribute
	 * @param attribs set of Attribute to setJ
	 *
	 * @return the set of attribute based on the given set of Attribute
	 */
	static std::set<OpenGLAttribute>
		get_attribs(Program const & program, std::set<Attribute> attribs);

	static std::set<OpenGLTexture>
		get_texture(Program const & program, std::set<Texture> textures);
};

#endif
