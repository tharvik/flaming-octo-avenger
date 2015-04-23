#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace Util {

	/**
	 * Check if OpenGL fail recently and if yes, show the error and exit the program
	 *
	 * @param path path of the file in where it is called
	 * @param func name of the function where it is called
	 * @param line line where the it is called
	 */
	void assert_no_glError_at(std::string path, std::string func,
				  size_t line);

// we have to use a macro to have __line__
	/**
	 * Macro the ease with the use of assert_no_glError_at()
	 */
#define assert_no_glError()	\
	assert_no_glError_at(__FILE__, __func__, __LINE__)


	/**
	 * Simple exception class wraping a message
	 */
	class base_exception : public std::exception {

	public:
		/**
		 * Construct a base_exception with the given message
		 *
		 * @param cause message to wrap
		 */
		base_exception(std::string cause);

		/**
		 * Redefine the std::exception::what() to allow to show something
		 *
		 * @return c_str representation of the message
		 */
		const char* what() const noexcept;

	private:
		/**
		 * The message to show
		 */
		std::string const cause;
	};

	/**
	 * Simple ref counting class to allow to duplicate a class and to only delete it component when it is the last
	 * reference
	 */
	class ref_counted {
	protected:

		/**
		 * Construct a ref_counted with the count set to zero
		 */
		ref_counted();

		/**
		 * Copy the ref_counted thus incrementing the count
		 *
		 * @param o object to copy from
		 */
		ref_counted(const ref_counted & o);

		/**
		 * Destruct the ref_counted thus decrementing the count (and deleting the count on last_ref())
		 */
		~ref_counted();

		/**
		 * Return true if it is the last reference (if count == 1)
		 *
		 * @return *this->count == 1;
		 */
		bool last_ref() const;

	private:

		/**
		 * The count of current reference of this class
		 */
		size_t * count;
	};
}

#endif
