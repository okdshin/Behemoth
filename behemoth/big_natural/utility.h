#ifndef BEHEMOTH_BIG_NATURAL_UTILITY_H
#define BEHEMOTH_BIG_NATURAL_UTILITY_H
//20140606
#include <sstream>
#include <behemoth/big_natural/traits_and_policy.h>
namespace behemoth {
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
		template<typename BigNatural>
		std::string to_digit_array_string(const BigNatural& bn) {
			std::stringstream ss;
			for(typename behemoth::big_naturals::const_iterator_type<BigNatural>::type 
						i = behemoth::big_naturals::cbegin(bn); 
					i != behemoth::big_naturals::cend(bn); ++i) {
				ss << *i << ",";
			}
			return ss.str();
		}
		
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_UTILITY_H
