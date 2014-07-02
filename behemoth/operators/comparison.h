#ifndef BEHEMOTH_BIG_NATURAL_OPERATOR_COMPARISON_H
#define BEHEMOTH_BIG_NATURAL_OPERATOR_COMPARISON_H
//20140611
#include <behemoth/assert.h>
#include <behemoth/mpl.h>
#include <behemoth/big_natural/check.h>
#include <behemoth/big_natural/access.h>
#include <behemoth/big_natural/modify.h>
namespace behemoth {

	//
	// is_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
					if(behemoth::big_naturals::size(lhs) != 
							behemoth::big_naturals::size(rhs)) {
						return false;
					}
					typename behemoth::big_naturals::const_iterator_type<BigNatural1>::type
						l_iter = behemoth::big_naturals::cbegin(lhs),
						l_end = behemoth::big_naturals::cend(lhs);
					typename behemoth::big_naturals::const_iterator_type<BigNatural2>::type
						r_iter = behemoth::big_naturals::cbegin(rhs);
					while(l_iter != l_end) {
						if(*l_iter != *r_iter){
							return false;
						}
						++l_iter; ++r_iter;
					}
					return true;
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		bool is_equal(const BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				is_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator==
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2, 
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::is_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	bool operator==(const BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
	}

	//
	// is_not_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_not_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
					return !behemoth::big_naturals::is_equal(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		bool is_not_equal(const BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				is_not_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals
	
	//
	// operator!=
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_not_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::is_not_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	bool operator!=(const BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_not_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
	}

	namespace big_naturals {
		namespace policy {
			namespace impl {
				template<bool IsAllowEqual, typename BigNatural1, typename BigNatural2>
				bool is_greater(const BigNatural1& lhs, const BigNatural2& rhs) {
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
					BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
					size_t lhs_size = behemoth::big_naturals::size(lhs);
					size_t rhs_size = behemoth::big_naturals::size(rhs);
					if(lhs_size != rhs_size) {
						return lhs_size > rhs_size;
					}
					typename behemoth::big_naturals::
							const_reverse_iterator_type<BigNatural1>::type 
						l_iter = behemoth::big_naturals::crbegin(lhs),
						l_end = behemoth::big_naturals::crend(lhs);
					typename behemoth::big_naturals::
							const_reverse_iterator_type<BigNatural2>::type 
						r_iter = behemoth::big_naturals::crbegin(rhs);
					while(l_iter != l_end) {
						if(*l_iter !=  *r_iter){
							return *l_iter > *r_iter;
						}
						++l_iter; ++r_iter;
					}
					return IsAllowEqual;
				}
			}// namespace impl
		}//namespace policy
	}// namespace big_naturals
	
	//
	// is_greater_than
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_greater_than {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::policy::impl::
						is_greater<false>(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		bool is_greater_than(const BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				is_greater_than<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator>
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_greater_than {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::is_greater_than(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	bool operator>(const BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_greater_than<BigNatural1, BigNatural2>::call(lhs, rhs);
	}

	//
	// is_greater_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::big_naturals::radix_value<BigNatural1>::value ==
						behemoth::big_naturals::radix_value<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_greater_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::policy::impl::
						is_greater<true>(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural1, typename BigNatural2>
		bool is_greater_equal(const BigNatural1& lhs, const BigNatural2& rhs) {
			return behemoth::big_naturals::policy::
				is_greater_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
		}
	}// namespace big_naturals
	
	//
	// operator>=
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural1, typename BigNatural2,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural1>::value &&
						behemoth::is_big_natural<BigNatural2>::value>::type=
							behemoth::enabler>
			struct is_greater_equal {
				static bool call(const BigNatural1& lhs, const BigNatural2& rhs) {
					return behemoth::big_naturals::is_greater_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural1, typename BigNatural2>
	bool operator>=(const BigNatural1& lhs, const BigNatural2& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_greater_equal<BigNatural1, BigNatural2>::call(lhs, rhs);
	}

	//TODO
	namespace big_naturals {
	/*
		template<typename BigNatural>
		bool is_lower_than(const BigNatural& lhs, const BigNatural& rhs) {
			BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
			BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
			return is_greater_than(rhs, lhs);
		}
		
		template<typename BigNatural>
		bool is_lower_equal(const BigNatural& lhs, const BigNatural& rhs) {
			BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(lhs));
			BEHEMOTH_ASSERT(behemoth::big_naturals::is_valid(rhs));
			return is_greater_equal(rhs, lhs);
		}
	*/
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_OPERATOR_COMPARISON_H
