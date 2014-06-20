#ifndef BEHEMOTH_MPL_H
#define BEHEMOTH_MPL_H
//20140610

namespace behemoth {
	template<typename T, T V>
	struct integral_constant {
		typedef T value_type;
		typedef integral_constant type;
		static const value_type value = V;
		operator value_type()const { return value; }
		value_type operator()()const { return value; }
	};
	typedef behemoth::integral_constant<bool, true> true_type;
	typedef behemoth::integral_constant<bool, false> false_type;

	template<bool C, typename T=void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> { typedef T type; };
	
	typedef void* enabler_t;
	enabler_t enabler;
	extern enabler_t enabler;

	template<bool C>
	struct enabler_if : public behemoth::enable_if<C, enabler_t&> {};

}// namespace behemoth

#endif //BEHEMOTH_MPL_H
