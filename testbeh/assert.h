#ifndef TESTBEH_ASSERT_H
#define TESTBEH_ASSERT_H
//20140701
#include <stdexcept>
#include <behemoth/assert.h>
namespace testbeh {
	//
	// assertion_failed_error
	//
	class assertion_failed_error : public std::runtime_error {
	public:
		explicit assertion_failed_error(const std::string& msg) : std::runtime_error(msg){}
		explicit assertion_failed_error(const char* msg) : std::runtime_error(msg){}
	};

}// namespace testbeh
#define TESTBEH_ASSERT(expr) \
	((void)behemoth::assert_impl::assertion_check((expr), \
		BEHEMOTH_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__)))
#endif //TESTBEH_ASSERT_H
