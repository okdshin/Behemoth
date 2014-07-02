#include <iostream>
#include <behemoth/big_natural.h>
#include <testbeh/assert.h>

namespace testbeh {
	void big_natural_unit_test(){
		std::cout << "###this is unit test function" << std::endl;
		std::vector<uint_least32_t> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(0);
		vec.push_back(0);

		//begin
		{
			TESTBEH_ASSERT(vec.front() == *behemoth::big_naturals::begin(vec));
		}
		/*
		std::cout << "back " << *(behemoth::big_naturals::end(vec)-1) << std::endl;
		std::cout << "cut_zeros" << std::endl;
		behemoth::big_naturals::cut_zeros(vec);
		std::cout << "front " << *behemoth::big_naturals::begin(vec) << std::endl;
		std::cout << "back " << *(behemoth::big_naturals::end(vec)-1) << std::endl;
		*/
		//std::cout << "radix " << behemoth::big_naturals::radix<std::vector<uint_least32_t> >::value << std::endl;

	}
}// namespace testbeh

#ifndef TESTBEH_CPP_INCLUDE
#	define TESTBEH_TEST_FUNCTION testbeh::big_natural_unit_test
#	include <testbeh/include_main.h>
#endif
