#ifndef TESTBEH_TYPEINFO_H
#define TESTBEH_TYPEINFO_H
//20140701
#include <typeinfo>
namespace testbeh {
	//
	// typename_of
	//
	template<typename T>
	inline std::string typename_of() {
		return std::string(typeid(T).name());
	}
	template<typename T>
	inline std::string typename_of(const T& t) {
		return std::string(typeid(T).name());
	}
}// namespace testbeh

#endif //TESTBEH_TYPEINFO_H
