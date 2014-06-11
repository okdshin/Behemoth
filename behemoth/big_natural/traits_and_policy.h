#ifndef BEHEMOTH_TRAITS_AND_POLICY_H
#define BEHEMOTH_TRAITS_AND_POLICY_H
//20140606
#include <cstddef>
#include <behemoth/cstdint.h>
#include <behemoth/mpl.h>
namespace behemoth {
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

	namespace big_naturals {
		template<typename BigNatural>
		struct value_type {
			typedef typename BigNatural::value_type type;
		};
		template<typename BigNatural>
		struct iterator_type {
			typedef typename BigNatural::iterator type;
		};
		template<typename BigNatural>
		struct const_iterator_type {
			typedef typename BigNatural::const_iterator type;
		};
		template<typename BigNatural>
		struct reverse_iterator_type {
			typedef typename BigNatural::reverse_iterator type;
		};
		template<typename BigNatural>
		struct const_reverse_iterator_type {
			typedef typename BigNatural::const_reverse_iterator type;
		};
		
		//default radix values
		template<typename BigNatural>struct radix_impl {};
		template<>struct radix_impl<behemoth::uint_least8_t> 
			{ static const uint_least8_t value = 16; };
		template<>struct radix_impl<behemoth::uint_least16_t> 
			{ static const uint_least16_t value = 256; };
		template<>struct radix_impl<behemoth::uint_least32_t> 
			{ static const uint_least32_t value = 65536; };
		template<typename BigNatural>
		struct radix {
			typedef typename behemoth::big_naturals::
				value_type<BigNatural>::type value_type;
			static const value_type value = 
				behemoth::big_naturals::radix_impl<value_type>::value;
		};
		namespace policy {
			template<typename BigNatural>
			struct begin {
				static typename behemoth::big_naturals::
					iterator_type<BigNatural>::type
				call(BigNatural& bn) { return bn.begin(); }
			};
			template<typename BigNatural>
			struct end {
				static typename behemoth::big_naturals::
					iterator_type<BigNatural>::type
				call(BigNatural& bn) { return bn.end(); }
			};
			template<typename BigNatural>
			struct cbegin {
				static typename behemoth::big_naturals::
					const_iterator_type<BigNatural>::type
				call(const BigNatural& bn) { return bn.begin(); }
			};
			template<typename BigNatural>
			struct cend {
				static typename behemoth::big_naturals::
					const_iterator_type<BigNatural>::type
				call(const BigNatural& bn) { return bn.end(); }
			};

			template<typename BigNatural>
			struct rbegin {
				static typename behemoth::big_naturals::
					reverse_iterator_type<BigNatural>::type
				call(BigNatural& bn) { return bn.rbegin(); }
			};
			template<typename BigNatural>
			struct rend {
				static typename behemoth::big_naturals::
					reverse_iterator_type<BigNatural>::type
				call(BigNatural& bn) { return bn.rend(); }
			};
			template<typename BigNatural>
			struct crbegin {
				static typename behemoth::big_naturals::
					const_reverse_iterator_type<BigNatural>::type
				call(const BigNatural& bn) { return bn.rbegin(); }
			};
			template<typename BigNatural>
			struct crend {
				static typename behemoth::big_naturals::
					const_reverse_iterator_type<BigNatural>::type
				call(const BigNatural& bn) { return bn.rend(); }
			};

			template<typename BigNatural>
			struct size {
				static std::size_t call(const BigNatural& bn) {
					return bn.size();
				}
			};
			template<typename BigNatural>
			struct resize {
				static void call(BigNatural& bn, std::size_t n) {
					bn.resize(n, 0);
				}
			};
		}// policy
		template<typename BigNatural>
		typename behemoth::big_naturals::iterator_type<BigNatural>::type
		begin(BigNatural& bn) {
			return behemoth::big_naturals::policy::begin<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::iterator_type<BigNatural>::type
		end(BigNatural& bn) {
			return behemoth::big_naturals::policy::end<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::const_iterator_type<BigNatural>::type
		cbegin(const BigNatural& bn) {
			return behemoth::big_naturals::policy::cbegin<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::const_iterator_type<BigNatural>::type
		cend(const BigNatural& bn) {
			return behemoth::big_naturals::policy::cend<BigNatural>::call(bn);
		}

		template<typename BigNatural>
		typename behemoth::big_naturals::reverse_iterator_type<BigNatural>::type
		rbegin(BigNatural& bn) {
			return behemoth::big_naturals::policy::rbegin<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::reverse_iterator_type<BigNatural>::type
		rend(BigNatural& bn) {
			return behemoth::big_naturals::policy::rend<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::const_reverse_iterator_type<BigNatural>::type
		crbegin(const BigNatural& bn) {
			return behemoth::big_naturals::policy::crbegin<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		typename behemoth::big_naturals::const_reverse_iterator_type<BigNatural>::type
		crend(const BigNatural& bn) {
			return behemoth::big_naturals::policy::crend<BigNatural>::call(bn);
		}

		template<typename BigNatural>
		std::size_t		
		size(const BigNatural& bn) {
			return behemoth::big_naturals::policy::size<BigNatural>::call(bn);
		}
		template<typename BigNatural>
		void
		resize(BigNatural& bn, std::size_t n) {
			return behemoth::big_naturals::policy::resize<BigNatural>::call(bn, n);
		}
		
		namespace policy {
			template<typename BigNatural>
			struct cut_zeros{
				static void call(BigNatural& bn) {
					typename behemoth::big_naturals::
							const_reverse_iterator_type<BigNatural>::type
						i = behemoth::big_naturals::crbegin(bn),
						back = behemoth::big_naturals::crend(bn); --back;
					std::size_t zero_count = 0;
					while((!*i) && i != back){
						++zero_count; ++i;	
					}
					bn.resize(bn.size()-zero_count);
				}
			};
		}// policy
		template<typename BigNatural>
		void
		cut_zeros(BigNatural& bn) {
			return behemoth::big_naturals::policy::cut_zeros<BigNatural>::call(bn);
		}
	}// big_naturals
}// namespace behemoth

#endif //BEHEMOTH_TRAITS_AND_POLICY_H
