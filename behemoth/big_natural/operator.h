#ifndef BEHEMOTH_OPERATOR_H
#define BEHEMOTH_OPERATOR_H
//20140606
#include <cassert>
#include <behemoth/big_natural/traits_and_policy.h>
#include <behemoth/big_natural/utility.h>
#include <behemoth/mpl.h>
namespace behemoth {
	//
	// is_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural>
			struct is_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					assert(behemoth::big_naturals::is_valid(lhs));
					assert(behemoth::big_naturals::is_valid(rhs));
					if(behemoth::big_naturals::size(lhs) != 
							behemoth::big_naturals::size(rhs)) {
						return false;
					}
					typename behemoth::big_naturals::const_iterator_type<BigNatural>::type
						l_iter = behemoth::big_naturals::cbegin(lhs),
						l_end = behemoth::big_naturals::cend(lhs),
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
		template<typename BigNatural>
		bool is_equal(const BigNatural& lhs, const BigNatural& rhs) {
			return behemoth::big_naturals::policy::is_equal<BigNatural>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator==
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural, 
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural>::value>::type=behemoth::enabler>
			struct is_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::is_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural>
	bool operator==(const BigNatural& lhs, const BigNatural& rhs) {
		return behemoth::big_naturals::operator_impl::is_equal<BigNatural>::call(lhs, rhs);
	}

	//
	// is_not_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural>
			struct is_not_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					assert(behemoth::big_naturals::is_valid(lhs));
					assert(behemoth::big_naturals::is_valid(rhs));
					return !behemoth::big_naturals::is_equal(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		bool is_not_equal(const BigNatural& lhs, const BigNatural& rhs) {
			return behemoth::big_naturals::policy::
				is_not_equal<BigNatural>::call(lhs, rhs);
		}
	}// namespace big_naturals
	
	//
	// operator!=
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural>::value>::type=behemoth::enabler>
			struct is_not_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::is_not_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural>
	bool operator!=(const BigNatural& lhs, const BigNatural& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_not_equal<BigNatural>::call(lhs, rhs);
	}

	namespace big_naturals {
		namespace policy {
			namespace impl {
				template<bool IsAllowEqual, typename BigNatural>
				bool is_greater(const BigNatural& lhs, const BigNatural& rhs) {
					assert(behemoth::big_naturals::is_valid(lhs));
					assert(behemoth::big_naturals::is_valid(rhs));
					size_t lhs_size = behemoth::big_naturals::size(lhs);
					size_t rhs_size = behemoth::big_naturals::size(rhs);
					if(lhs_size != rhs_size) {
						return lhs_size > rhs_size;
					}
					typename behemoth::big_naturals::const_reverse_iterator_type<BigNatural>::type 
						l_iter = behemoth::big_naturals::crbegin(lhs),
						l_end = behemoth::big_naturals::crend(lhs),
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
			template<typename BigNatural>
			struct is_greater_than {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::policy::impl::
						is_greater<false>(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		bool is_greater_than(const BigNatural& lhs, const BigNatural& rhs) {
			return behemoth::big_naturals::policy::
				is_greater_than<BigNatural>::call(lhs, rhs);
		}
	}// namespace big_naturals

	//
	// operator>
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural>::value>::type=behemoth::enabler>
			struct is_greater_than {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::is_greater_than(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural>
	bool operator>(const BigNatural& lhs, const BigNatural& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_greater_than<BigNatural>::call(lhs, rhs);
	}

	//
	// is_greater_equal
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural>
			struct is_greater_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::policy::impl::
						is_greater<true>(lhs, rhs);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		bool is_greater_equal(const BigNatural& lhs, const BigNatural& rhs) {
			return behemoth::big_naturals::policy::
				is_greater_equal<BigNatural>::call(lhs, rhs);
		}
	}// namespace big_naturals
	
	//
	// operator>=
	//
	namespace big_naturals {
		namespace operator_impl {
			template<typename BigNatural,
				typename behemoth::enabler_if<
					behemoth::is_big_natural<BigNatural>::value>::type=behemoth::enabler>
			struct is_greater_equal {
				static bool call(const BigNatural& lhs, const BigNatural& rhs) {
					return behemoth::big_naturals::is_greater_equal(lhs, rhs);
				}
			};
		}// namespace operator_impl
	}// namespace big_naturals
	template<typename BigNatural>
	bool operator>=(const BigNatural& lhs, const BigNatural& rhs) {
		return behemoth::big_naturals::operator_impl::
			is_greater_equal<BigNatural>::call(lhs, rhs);
	}

	namespace big_naturals {
	/*
		template<typename BigNatural>
		bool is_lower_than(const BigNatural& lhs, const BigNatural& rhs) {
			assert(behemoth::big_naturals::is_valid(lhs));
			assert(behemoth::big_naturals::is_valid(rhs));
			return is_greater_than(rhs, lhs);
		}
		
		template<typename BigNatural>
		bool is_lower_equal(const BigNatural& lhs, const BigNatural& rhs) {
			assert(behemoth::big_naturals::is_valid(lhs));
			assert(behemoth::big_naturals::is_valid(rhs));
			return is_greater_equal(rhs, lhs);
		}
	*/
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

#endif //BEHEMOTH_OPERATOR_H
