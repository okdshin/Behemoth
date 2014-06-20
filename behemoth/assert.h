#ifndef BEHEMOTH_ASSERT_H
#define BEHEMOTH_ASSERT_H
//20140616
#define BEHEMOTH_STRINGIZE(x) #x
#ifndef BEHEMOTH_ASSERTION_FAILED_FORMAT
#	define BEHEMOTH_ASSERTION_FAILED_FORMAT(expr, file, line) \
		"####### Internal Program Error - assertion (" #expr ") failed: " file "(" BEHEMOTH_STRINGIZE(line) ")"
#endif

namespace behemoth {
	namespace assert_impl {
		inline bool assertion_failed(const char* message) {
			return (std::cerr << message << std::endl), std::abort(), false;
		}
		inline bool assertion_check(bool cond, const char* message) {
			return cond ? true : behemoth::assert_impl::assertion_failed(message);
		}
	}// namespace assert_impl
}// namespace behemoth
#define BEHEMOTH_ASSERT(expr) \
	((void)behemoth::assert_impl::assertion_check((expr), \
		BEHEMOTH_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__)))

#endif //BEHEMOTH_ASSERT_H
