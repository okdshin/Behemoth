#ifndef BEHEMOTH_BIG_NATURAL_OPERATOR_BIT_LOGICAL_H
#define BEHEMOTH_BIG_NATURAL_OPERATOR_BIT_LOGICAL_H
//20140611
#include <behemoth/mpl.h>
#include <behemoth/big_natural/check.h>
#include <behemoth/big_natural/modify.h>
#include <behemoth/big_natural/access.h>
namespace behemoth {
	namespace big_naturals {

		template<typename BigNatural>
		BigNatural& bitand_assign(BigNatural& lhs, const BigNatural& rhs) {
			assert(behemoth::big_naturals::is_valid(lhs));
			assert(behemoth::big_naturals::is_valid(rhs));
			typename behemoth::big_naturals::iterator_type<BigNatural>::type 
				l_iter = behemoth::big_naturals::begin(lhs);
			typename behemoth::big_naturals::const_iterator_type<BigNatural>::type 
				l_end = behemoth::big_naturals::cend(lhs),
				r_iter = behemoth::big_naturals::cbegin(rhs),
				r_end = behemoth::big_naturals::cend(rhs);
			while(l_iter != l_end) {
				if(r_iter == r_end) {
					behemoth::big_naturals::resize(lhs, behemoth::big_naturals::size(rhs));
					break;
				}
				*l_iter &= *r_iter;
				++l_iter; ++r_iter;
			}
			behemoth::big_naturals::cut_zeros(lhs);
			return lhs;
		}
			
		template<typename BigNatural>
		BigNatural& bitor_assign(BigNatural& lhs, const BigNatural& rhs) {
			assert(behemoth::big_naturals::is_valid(lhs));
			assert(behemoth::big_naturals::is_valid(rhs));
			typename behemoth::big_naturals::iterator_type<BigNatural>::type 
				l_iter = behemoth::big_naturals::begin(lhs);
			typename behemoth::big_naturals::const_iterator_type<BigNatural>::type 
				l_end = behemoth::big_naturals::cend(lhs),
				r_iter = behemoth::big_naturals::cbegin(rhs),
				r_end = behemoth::big_naturals::cend(rhs);
			while(l_iter != l_end) {
				if(r_iter == r_end) {
					return lhs;
				}
				*l_iter |= *r_iter;
				++l_iter; ++r_iter;
			}
			behemoth::big_naturals::resize(lhs,
					behemoth::big_naturals::size(rhs));
			std::copy(r_iter, r_end, l_iter);
			return lhs;
		}
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_OPERATOR_BIT_LOGICAL_H
