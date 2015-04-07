#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace Util {

	void assert_no_glError_at(std::string path, std::string func,
				  size_t line);

// we have to use a macro to have __line__
#define assert_no_glError()	\
	assert_no_glError_at(__FILE__, __func__, __LINE__)


	class base_exception : public std::exception {

	public:
		base_exception(std::string cause);

		const char* what() const noexcept;

	private:
		std::string const cause;
	};

	class ref_counted {
	protected:
		ref_counted();
		ref_counted(const ref_counted & o);
		~ref_counted();

		bool last_ref() const;

	private:
		size_t * count;
	};
}

#endif
