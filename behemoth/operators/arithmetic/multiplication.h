#ifndef BEHEMOTH_OPERATOR_ARITHMETIC_MULTIPLICATION_H
#define BEHEMOTH_OPERATOR_ARITHMETIC_MULTIPLICATION_H
//20140616

#include <iterator>
#include <behemoth/assert.h>
#include <behemoth/mpl.h>
#include <behemoth/big_natural.h>
namespace behemoth {

	//TODO
	//
	// multiply_assign
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct multiply_assign_impl {
				static BigNatural1& call(BigNatural1& lhs, const BigNatural2& rhs, 
						std::random_access_iterator_tag) {
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
					
					const std::size_t l_size = behemoth::big_naturals::size(lhs);
					const std::size_t r_size = behemoth::big_naturals::size(rhs);

					BigNatural1 result = behemoth::big_naturals::construct<BigNatural2>(
							behemoth::big_naturals::size(lhs)+
								behemoth::big_naturals::size(rhs));

					typename behemoth::big_naturals::iterator_type<BigNatural1>::type 
						l_iter = behemoth::big_naturals::begin(lhs),
						result_iter = behemoth::big_naturals::begin(result);
					/*
					typename behemoth::big_naturals::
							const_iterator_type<BigNatural1>::type 
						l_end = behemoth::big_naturals::cend(lhs);
						*/
					typename behemoth::big_naturals::
							const_iterator_type<BigNatural2>::type 
						r_iter = behemoth::big_naturals::cbegin(rhs);
						//r_end = behemoth::big_naturals::cend(rhs);
					for(std::size_t l_i=0; l_i < l_size; ++l_i, ++l_iter){
						for(std::size_t r_i=0; r_i < r_size; ++r_i, ++r_iter){
							result_iter[l_i+r_i] += ((*l_iter)*(*r_iter));
							result_iter[l_i+r_i+1] += (result_iter[l_i+r_i] >> 
								behemoth::big_naturals::
									radix_digit_num<BigNatural1>::value);
							result_iter[l_i+r_i] &= 
								behemoth::big_naturals::max_value<BigNatural1>::value;
						}
					}

					behemoth::big_naturals::cut_zeros(result);
					behemoth::big_naturals::swap(result, lhs);
					return lhs;
				}
			};
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct multiply_assign {
				static BigNatural1& call(BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::policy::
						multiply_assign_impl<BigNatural1, BigNatural2>::call(lhs, rhs,
							typename std::iterator_traits<typename behemoth::big_naturals::
								iterator_type<BigNatural1>::type>::iterator_category());
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		BigNatural1& multiply_assign(BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				multiply_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator*=
	// operator*
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct multiply_assign {
				static BigNatural1& call(BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::multiply_assign(lhs, rhs);
				}
			};
		}// namespace operator impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	BigNatural1& operator*=(BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			multiply_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
	}
	template<typename BigNatural1, typename BigNatural2>
	BigNatural1 operator*(BigNatural1 lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			multiply_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
	}
}// namespace behemoth

#endif //BEHEMOTH_OPERATOR_ARITHMETIC_MULTIPLICATION_H
