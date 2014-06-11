#ifndef BEHEMOTH_BIG_NATURAL_DIGIT_H
#define BEHEMOTH_BIG_NATURAL_DIGIT_H
//20140611
namespace behemoth {
	namespace big_naturals {
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
	}// big_naturals
}// namespace behemoth
#endif //BEHEMOTH_BIG_NATURAL_DIGIT_H
