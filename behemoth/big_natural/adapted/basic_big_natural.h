#ifndef BEHEMOTH_BIG_NATURAL_ADAPTED_BASIC_BIG_NATURAL_H
#define BEHEMOTH_BIG_NATURAL_ADAPTED_BASIC_BIG_NATURAL_H
//20140606
#include <vector>
#include <boost/static_assert.hpp>
#include <behemoth/cstdint.h>
#include <behemoth/convert_to_string.h>
#include <behemoth/big_natural/construct.h>
#include <behemoth/big_natural/access.h>
#include <behemoth/big_natural/check.h>
#include <behemoth/big_natural/modify.h>
namespace behemoth {
	template<typename DigitContainer, 
		typename DigitContainer::value_type RadixValue>
	class basic_big_natural {
	public:
		typedef DigitContainer digit_container_type;
		typedef typename digit_container_type::value_type value_type;
		typedef typename digit_container_type::iterator iterator;
		typedef typename digit_container_type::const_iterator const_iterator;
		typedef typename digit_container_type::reverse_iterator reverse_iterator;
		typedef typename digit_container_type::const_reverse_iterator const_reverse_iterator;
		static const value_type radix_value = RadixValue;
		BOOST_STATIC_ASSERT(RadixValue == 16 || RadixValue == 256 || RadixValue == 65536);

		basic_big_natural() : digits_(1, 0) {}
		basic_big_natural(std::size_t size) : digits_(size, 0) {}
		basic_big_natural(const DigitContainer& digits) : digits_(digits) {
			BOOST_STATIC_ASSERT(
				behemoth::big_naturals::radix_value<DigitContainer>::value == radix_value);
		}

		iterator begin() { return digits_.begin(); }
		iterator end() { return digits_.end(); }
		const_iterator begin()const{ return digits_.begin(); }
		const_iterator end()const{ return digits_.end(); }
		
		reverse_iterator rbegin() { return digits_.rbegin(); }
		reverse_iterator rend() { return digits_.rend(); }
		const_reverse_iterator rbegin()const{ return digits_.rbegin(); }
		const_reverse_iterator rend()const{ return digits_.rend(); }

		std::size_t size()const{ return digits_.size(); }
		void resize(std::size_t n, value_type val) { digits_.resize(n, val); }

		void swap(basic_big_natural& bn) {
			digits_.swap(bn.digits_);
		}

		friend std::ostream& operator<<(std::ostream& os, const basic_big_natural& bn) {
			os << behemoth::big_naturals::to_digit_array_string(bn);//TODO make it more natural format
			return os;
		}
	private:
		DigitContainer digits_;
	};
	namespace big_naturals {
		template<typename DigitContainer, 
			typename DigitContainer::value_type RadixValue>
		struct is_big_natural<behemoth::basic_big_natural<DigitContainer, RadixValue> > : 
			public behemoth::true_type {};

		template<typename DigitContainer, 
			typename DigitContainer::value_type RadixValue>
		void swap(behemoth::basic_big_natural<DigitContainer, RadixValue>& a,
				behemoth::basic_big_natural<DigitContainer, RadixValue>& b) {
			a.swap(b);
		}
		template<typename DigitContainer, typename DigitContainer::value_type RadixValue>
		struct radix_value<behemoth::basic_big_natural<DigitContainer, RadixValue> > {
			typedef behemoth::basic_big_natural<DigitContainer, RadixValue> 
				basic_big_natural;
			static const typename behemoth::big_naturals::
					value_type<basic_big_natural>::type 
				value = basic_big_natural::radix_value;
		};
		namespace policy {
			template<typename DigitContainer, 
				typename DigitContainer::value_type RadixValue>
			struct construct<behemoth::basic_big_natural<DigitContainer, RadixValue> > {
				static behemoth::basic_big_natural<DigitContainer, RadixValue> 
				call(std::size_t size) {
					return behemoth::basic_big_natural<DigitContainer, RadixValue>(size);
				}
			};
		}// namespace policy
	}// big_naturals
	typedef basic_big_natural<std::vector<behemoth::uint_least32_t>, 65536> big_natural;
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_ADAPTED__BASIC_BIG_NATURAL_H
