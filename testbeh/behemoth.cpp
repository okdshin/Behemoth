#ifndef TESTBEH_BEHEMOTH_CPP
#define TESTBEH_BEHEMOTH_CPP
//20140630
#include "../libs/big_natural/big_natural.cpp"
//...

namespace testbeh {
	void behemoth_test() {
		testbeh::big_natural_test();
		//...
	}
}// namespace testbeh

#ifndef TESTBEH_CPP_INCLUDE
#	define TESTBEH_TEST_FUNCTION testbeh::behemoth_test
#	include <testbeh/include_main.h>
#endif
#endif //TESTBEH_BEHEMOTH_CPP
