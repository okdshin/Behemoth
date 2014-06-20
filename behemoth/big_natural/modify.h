#ifndef BEHEMOTH_BIG_NATURAL_MODIFY_H
#define BEHEMOTH_BIG_NATURAL_MODIFY_H
//20140611
#include <behemoth/big_natural/access.h>
namespace behemoth {
	namespace big_naturals {

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
					behemoth::big_naturals::resize(bn, bn.size()-zero_count);
				}
			};
		}// namespace policy
		template<typename BigNatural>
		void cut_zeros(BigNatural& bn) {
			return behemoth::big_naturals::policy::cut_zeros<BigNatural>::call(bn);
		}

	}// namespace big_naturals
}// namespace behemoth

#endif //BEHEMOTH_BIG_NATURAL_MODIFY_H
