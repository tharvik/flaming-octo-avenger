#include "Util.hpp"

#include "OpenGL.hpp"

#include <iostream>

void Util::assert_no_glError_at(std::string path, std::string func,
				size_t line)
{
	GLenum err = glGetError();
	std::string msg;
	std::string const header(" OpenGL error detected: ");

	if (err == GL_NO_ERROR)
		return;

	std::cerr << path << ":" << line << ":" << func << "():" << header;

	switch (err) {
#define ASSIGN_MSG(err_def)	\
	case err_def:		\
		msg = #err_def;	\
		break;

ASSIGN_MSG(GL_INVALID_ENUM);
ASSIGN_MSG(GL_INVALID_VALUE);
ASSIGN_MSG(GL_INVALID_OPERATION);
ASSIGN_MSG(GL_INVALID_FRAMEBUFFER_OPERATION);
ASSIGN_MSG(GL_OUT_OF_MEMORY);
ASSIGN_MSG(GL_STACK_UNDERFLOW);
ASSIGN_MSG(GL_STACK_OVERFLOW);

#undef ASSIGN_MSG

	default:
		std::cerr << err << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

Util::base_exception::base_exception(std::string cause)
	: cause(cause)
{}

const char* Util::base_exception::what() const noexcept
{
	return this->cause.c_str();
}

Util::ref_counted::ref_counted()
	: count(new size_t)
{}

Util::ref_counted::ref_counted(const ref_counted & o)
	: count(o.count)
{
	*o.count += 1;
}

Util::ref_counted::~ref_counted()
{
	if (last_ref())
		delete this->count;
}

bool Util::ref_counted::last_ref() const
{
	return *this->count == 1;
}
