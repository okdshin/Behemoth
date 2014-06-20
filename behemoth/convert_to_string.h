#ifndef BEHEMOTH_BIG_NATURAL_CONVERT_TO_STRING_H
#define BEHEMOTH_BIG_NATURAL_CONVERT_TO_STRING_H
//20140606
#include <sstream>
#include <behemoth/big_natural.h>
namespace behemoth {
	namespace big_naturals {
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

#endif //BEHEMOTH_BIG_NATURAL_CONVERT_TO_STRING_H
