#include "OpenGLValue.hpp"

bool OpenGLValue::operator<(OpenGLValue const & other) const
{
	return this->name < other.name;
}

template<>
std::vector<OpenGLValue::element> OpenGLValue::to_vec(glm::mat4 const value)
{
	size_t const width = 4, height = 4;

	std::vector<element> vec;
	size_t const size = width * height;

	vec.resize(size);
	for (size_t i = 0; i < size; i++)
		vec[i].as_GLfloat = value[i / height][i % width];

	return vec;
}

#define OpenGLValue_macro(name, id)							\
template<>										\
std::vector<OpenGLValue::element> OpenGLValue::to_vec(std::vector<name> const value)	\
{											\
	std::vector<element> vec;							\
											\
	vec.resize(value.size());							\
	for (size_t i = 0; i < value.size(); i++)					\
		vec[i].as_##name = value[i];						\
											\
	return vec;									\
}
#include "OpenGLValue.x"
#undef OpenGLValue_macro

#include <iostream>

#define OpenGLValue_macro(name, id)		\
template<>					\
std::vector<name> OpenGLValue::as() const	\
{						\
	std::vector<name> vec;			\
	vec.reserve(value.size());		\
						\
	for (auto const & v : value)		\
		vec.push_back(v.as_##name);	\
						\
	return vec;				\
}
#include "OpenGLValue.x"
#undef OpenGLValue_macro
