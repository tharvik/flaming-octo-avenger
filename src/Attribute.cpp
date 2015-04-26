#include "Attribute.hpp"

Attribute::Attribute(std::string const name, std::set<std::tuple<GLenum, OpenGLValue>> values)
	: name(name), values(values)
{}

bool Attribute::operator<(Attribute const & other) const
{
	return this->name < other.name;
}
