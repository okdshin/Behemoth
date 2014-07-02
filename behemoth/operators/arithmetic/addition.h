#ifndef BEHEMOTH_OPERATOR_ARITHMETIC_ADDITION_H
#define BEHEMOTH_OPERATOR_ARITHMETIC_ADDITION_H
//20140616

#include <behemoth/assert.h>
#include <behemoth/mpl.h>
#include <behemoth/big_natural.h>
namespace behemoth {

	//
	// add_assign
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct add_assign {
				static BigNatural1& call(BigNatural1& lhs, const BigNatural2& rhs) {
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));

					const std::size_t lhs_size = behemoth::big_naturals::size(lhs);
					const std::size_t rhs_size = behemoth::big_naturals::size(rhs);
					behemoth::big_naturals::resize(lhs, 
							lhs_size > rhs_size ? lhs_size+1 : rhs_size+1);

					typename behemoth::big_naturals::iterator_type<BigNatural1>::type 
						l_iter = behemoth::big_naturals::begin(lhs);
					typename behemoth::big_naturals::
							const_iterator_type<BigNatural1>::type 
						l_end = behemoth::big_naturals::cend(lhs);
					typename behemoth::big_naturals::
							const_iterator_type<BigNatural2>::type 
						r_iter = behemoth::big_naturals::cbegin(rhs),
						r_end = behemoth::big_naturals::cend(rhs);
					while(r_iter != r_end) {
						*l_iter += *r_iter;
						*(l_iter+1) += (*l_iter >> behemoth::big_naturals::
								radix_digit_num<BigNatural2>::value);
						*l_iter &= behemoth::big_naturals::max_value<BigNatural2>::value;
						++l_iter; ++r_iter;
					}
					while((l_iter+1) != l_end) {
						*(l_iter+1) += (*l_iter >> behemoth::big_naturals::
								radix_digit_num<BigNatural2>::value);
						*l_iter &= behemoth::big_naturals::max_value<BigNatural2>::value;
						++l_iter;
					}

					behemoth::big_naturals::cut_zeros(lhs);
					return lhs;
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		BigNatural1& add_assign(BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				add_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator+=
	// operator+
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct add_assign {
				static BigNatural1& call(BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::add_assign(lhs, rhs);
				}
			};
		}// namespace operator impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	BigNatural1& operator+=(BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			add_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
	}
	template<typename BigNatural1, typename BigNatural2>
	BigNatural1 operator+(BigNatural1 lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			add_assign<BigNatural1, BigNatural2>::call(lhs, rhs);
	}
}// namespace behemoth

#endif //BEHEMOTH_OPERATOR_ARITHMETIC_ADDITION_H
