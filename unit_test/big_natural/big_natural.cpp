#include <iostream>
#include <behemoth/big_natural.h>
#include <testbeh/assert.h>

namespace testbeh {
	void big_natural_unit_test(){
		using namespace behemoth;
		std::vector<uint_least32_t> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(0);
		vec.push_back(0);

		big_natural bn1(vec);

		// begin
		{
			TESTBEH_ASSERT(vec.front() == *big_naturals::begin(bn1));
		}

		// cbegin
		{
			TESTBEH_ASSERT(vec.front() == *big_naturals::cbegin(bn1));
		}

		// end
		{
			TESTBEH_ASSERT(vec.back() == *(--big_naturals::end(bn1)));
		}
		
		// cend
		{
			TESTBEH_ASSERT(vec.back() == *(--big_naturals::cend(bn1)));
		}
		
		// rbegin
		{
			TESTBEH_ASSERT(vec.back() == *big_naturals::rbegin(bn1));
		}

		// crbegin
		{
			TESTBEH_ASSERT(vec.back() == *big_naturals::crbegin(bn1));
		}

		// rend
		{
			TESTBEH_ASSERT(vec.front() == *(--big_naturals::rend(bn1)));
		}
		
		// crend
		{
			TESTBEH_ASSERT(vec.front() == *(--big_naturals::crend(bn1)));
		}

		// radix_value
		{
			TESTBEH_ASSERT(65536 == big_naturals::radix_value<big_natural>::value);
		}
		
		// radix_digit_num
		{
			TESTBEH_ASSERT(16 == big_naturals::radix_digit_num<big_natural>::value);
		}
		
		// max_value
		{
			TESTBEH_ASSERT(65535 == big_naturals::max_value<big_natural>::value);
		}
		
		// size
		{
			TESTBEH_ASSERT(3 == big_naturals::size(bn1));
		}
	}
}// namespace testbeh

#ifndef TESTBEH_CPP_INCLUDE
#	define TESTBEH_TEST_FUNCTION testbeh::big_natural_unit_test
#	include <testbeh/include_main.h>
#endif
