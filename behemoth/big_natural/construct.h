#ifndef BEHEMOTH_BIG_NATURAL_CONSTRUCT_H
#define BEHEMOTH_BIG_NATURAL_CONSTRUCT_H
//20140616

namespace behemoth {
	//
	// construct
	//
	namespace big_naturals {
		namespace policy {
			template<typename BigNatural>
			struct construct {
				static BigNatural call(std::size_t size) {
					return BigNatural(size, 0);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		BigNatural construct(std::size_t size) {
			return behemoth::big_naturals::policy::construct<BigNatural>::call(size);
		}
	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_CONSTRUCT_H
