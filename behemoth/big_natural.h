#ifndef BEHEMOTH_BIG_NATURAL_H
#define BEHEMOTH_BIG_NATURAL_H
//20140530
#include <behemoth/cstdint.h>
#include <behemoth/big_natural/access.h>
#include <behemoth/big_natural/operator.h>
#include <behemoth/big_natural/basic_big_natural.h>
namespace behemoth {
	typedef basic_big_natural<std::vector<behemoth::uint_least32_t>, 65536> big_natural;
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_H
