#ifndef BEHEMOTH_BIG_NATURAL_H
#define BEHEMOTH_BIG_NATURAL_H
//20140530
#if __cplusplus == 201103
#include <cstdint>
#else
#include <stdint.h>
#endif
#include <vector>
#include <boost/static_assert.hpp>
namespace behemoth {
#if __cplusplus == 201103
	typedef std::uint_least8_t uint_least8_t;
	typedef std::uint_least16_t uint_least16_t;
	typedef std::uint_least32_t uint_least32_t;
#else
	typedef uint_least8_t uint_least8_t;
	typedef uint_least16_t uint_least16_t;
	typedef uint_least32_t uint_least32_t;
#endif
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
	}// big_naturals
	template<typename DigitContainer, 
		typename DigitContainer::value_type RadixValue>
	class basic_big_natural {
	public:
		typedef DigitContainer digit_container_type;
		typedef typename digit_container_type::value_type value_type;
		typedef typename digit_container_type::iterator iterator;
		typedef typename digit_container_type::const_iterator const_iterator;
		static const value_type radix_value = RadixValue;
		BOOST_STATIC_ASSERT(RadixValue == 16 || RadixValue == 256 || RadixValue == 65536);

		basic_big_natural() : digits_() {}
		basic_big_natural(const DigitContainer& digits) : digits_(digits) {
			BOOST_STATIC_ASSERT(
				behemoth::big_naturals::radix<DigitContainer>::value == radix_value);
		}

		iterator begin()const{ return digits_.begin(); }
		iterator end()const{ return digits_.end(); }
		const_iterator cbegin()const{ return digits_.cbegin(); }
		const_iterator cend()const{ return digits_.cend(); }

	private:
		DigitContainer digits_;
	};
	namespace big_naturals {
		template<typename DigitContainer, typename DigitContainer::value_type RadixValue>
		struct radix<behemoth::basic_big_natural<DigitContainer, RadixValue> > {
			typedef behemoth::basic_big_natural<DigitContainer, RadixValue> 
				basic_big_natural;
			static const typename behemoth::big_naturals::
				value_type<basic_big_natural>::type 
			value = basic_big_natural::radix_value;
		};
	}// big_naturals

	typedef basic_big_natural<std::vector<behemoth::uint_least32_t>, 65536> big_natural;
	
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_H
