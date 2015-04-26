#include "Uniform.hpp"

Uniform::Uniform(std::string const name, OpenGLValue const value)
	: name(name), value(value)
{}

bool Uniform::operator<(Uniform const & other) const
{
	return this->name < other.name;
}
