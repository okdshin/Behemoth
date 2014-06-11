#ifndef BEHEMOTH_BIG_NATURAL_CHECK_H
#define BEHEMOTH_BIG_NATURAL_CHECK_H
//20140611
#include <behemoth/big_natural/access.h>
namespace behemoth {

	//
	// is_big_natural
	//
	namespace big_naturals {
		template<typename T>
		struct is_big_natural : 
			public behemoth::false_type {};

		template<typename T>
		struct is_big_natural<const T> : 
			public is_big_natural<T> {};

		template<typename T>
		struct is_big_natural<volatile T> : 
			public is_big_natural<T> {};

		template<typename T>
		struct is_big_natural<const volatile T> : 
			public is_big_natural<T> {};
	}// namespace big_naturals
	using behemoth::big_naturals::is_big_natural;

	//
	// is_valid
	//
	namespace big_naturals {
		template<typename BigNatural>
		bool is_equal_zero(const BigNatural& bn) {
			for(typename behemoth::big_naturals::const_iterator_type<BigNatural>::type 
						i = behemoth::big_naturals::cbegin(bn); 
					i != behemoth::big_naturals::cend(bn); ++i) {
				if(*i){
					return false;
				}
			}
			return true;
		}
		template<typename BigNatural>
		bool is_top_digit_zero(const BigNatural& bn) {
			return !*behemoth::big_naturals::crbegin(bn);
		}
		template<typename BigNatural>
		bool is_valid(const BigNatural& bn) {
			return is_equal_zero(bn) || !is_top_digit_zero(bn);
		}
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_CHECK_H
