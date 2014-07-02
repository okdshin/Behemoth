#ifndef TESTBEH_INCLUDE_MAIN_H
#define TESTBEH_INCLUDE_MAIN_H
//20140630
#ifndef TESTBEH_TEST_FUNCTION
#	error undefined TESTBEH_TEST_FUNCTION
#endif
#include <cstdlib>
#include <exception>
#include <iostream>
#include <testbeh/assert.h>
#include <testbeh/typeinfo.h>

//#define BEHEMOTH_PP_STRINGIZE(arg) ##arg
#define BEHEMOTH_PP_STRINGIZE(text) BEHEMOTH_PP_STRINGIZE_I(text)
#define BEHEMOTH_PP_STRINGIZE_I(text) #text
int main() {
	std::cout << "testbeh exec(" << BEHEMOTH_PP_STRINGIZE(TESTBEH_TEST_FUNCTION) << "):" << std::endl;
	try {
		TESTBEH_TEST_FUNCTION();
	}
	catch (const testbeh::assertion_failed_error& e) {
		std::cout
			<< "  testbeh failed." << std::endl
			<< "  " << e.what() << std::endl
			;
		return EXIT_FAILURE;
	}
	catch(const std::exception& e) {
		std::cout 
			<< " testbeh failed." << std::endl
			<< " exception handled:" << std::endl
			<< "	type = " << testbeh::typename_of(e) << std::endl
			<< "	what = " << e.what() << std::endl
			;
		return EXIT_FAILURE;
	}
	catch(...) {
		std::cout 
			<< " testbeh failed." << std::endl
			<< " exception handled:" << std::endl
			<< "	type = <unknown>" << std::endl
			;
		return EXIT_FAILURE;
	}
	std::cout << " testbeh succeeded." << std::endl;
}

#endif //TESTBEH_INCLUDE_MAIN_H
