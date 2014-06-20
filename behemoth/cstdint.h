#ifndef BEHEMOTH_CSTDINT_H
#define BEHEMOTH_CSTDINT_H
//20140606
#if __cplusplus == 201103
#include <cstdint>
namespace behemoth {
	typedef std::uint_least8_t uint_least8_t;
	typedef std::uint_least16_t uint_least16_t;
	typedef std::uint_least32_t uint_least32_t;
}
#else
#include <stdint.h>
namespace behemoth {
	typedef uint_least8_t uint_least8_t;
	typedef uint_least16_t uint_least16_t;
	typedef uint_least32_t uint_least32_t;
}
#endif
#endif //BEHEMOTH_CSTDINT_H
