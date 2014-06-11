#ifndef BEHEMOTH_BIG_NATURAL_PROPERTY_H
#define BEHEMOTH_BIG_NATURAL_PROPERTY_H
//20140611

#include <cstddef>
#include <behemoth/cstdint.h>
#include <behemoth/mpl.h>
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

	namespace big_naturals {
		//
		// value_type
		//
		template<typename BigNatural>
		struct value_type {
			typedef typename BigNatural::value_type type;
		};

		//
		// radix
		//
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

		//
		// size
		//
		namespace policy {
			template<typename BigNatural>
			struct size {
				static std::size_t call(const BigNatural& bn) {
					return bn.size();
				}
			};
		}// namespace policy
		template<typename BigNatural>
		std::size_t	size(const BigNatural& bn) {
			return behemoth::big_naturals::policy::size<BigNatural>::call(bn);
		}

		//
		// resize
		//
		namespace policy {
			template<typename BigNatural>
			struct resize {
				static void call(BigNatural& bn, std::size_t n) {
					bn.resize(n, 0);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		void resize(BigNatural& bn, std::size_t n) {
			return behemoth::big_naturals::policy::resize<BigNatural>::call(bn, n);
		}
		
		//
		// cut_zeros
		//
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
		}// namespace policy
		template<typename BigNatural>
		void cut_zeros(BigNatural& bn) {
			return behemoth::big_naturals::policy::cut_zeros<BigNatural>::call(bn);
		}
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_PROPERTY_H
