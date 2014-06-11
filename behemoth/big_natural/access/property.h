#ifndef BEHEMOTH_BIG_NATURAL_PROPERTY_H
#define BEHEMOTH_BIG_NATURAL_PROPERTY_H
//20140611
#include <cstddef>
#include <behemoth/cstdint.h>
namespace behemoth {
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

	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_PROPERTY_H
