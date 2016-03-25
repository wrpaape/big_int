#ifndef BIG_INT_ADD_H_
#define BIG_INT_ADD_H_
/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/subtract.h"
#include "big_int/multiply.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

void add_big_ints_same_sign(struct BigInt *result,
			    struct BigInt *big1,
			    struct BigInt *big2);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERNAL API ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline void add_big_ints(struct BigInt *result,
			 struct BigInt *big1,
			 struct BigInt *big2)
{

	if (big1->sign == big2->sign) {
		add_big_ints_same_sign(result, big1, big2);
		return;
	}




	size_t req_wc;


		result->sign = big1->sign;

		if (result->alloc_count < req_wc)
			expand_big_int(result, req_wc);


	}

}

/* { */

/* 	/1* compare magnitudes before calling implementation */
/* 	 * ================================================================== *1/ */
/* 	switch (compare_big_int_mags(big1, big2)) { */

/* 	case POS: */
/* 		/1* big1 > big2, call low level add function */
/* 		 * ========================================================== *1/ */
/* 		add_big_ints_same_sign_ordered(result, big1, big2); */
/* 		return; */

/* 	case NEG: */
/* 		/1* big1 < big1, correct param ordering before calling add */
/* 		 * ========================================================== *1/ */
/* 		add_big_ints_same_sign_ordered(result, big2, big1); */
/* 		return; */


/* 	default: */
/* 		/1* abs(big1) == abs(big2) */
/* 		 * */
/* 		 *  → big1 + big2 */
/* 		 *  = 2big1 */
/* 		 *  = arithmetic shift left by 1 on big1 */
/* 		 * */
/* 		 *  delegate addition to more efficient bitwise operation */
/* 		 * ========================================================== *1/ */
/* 		big_int_ash_left(result, big1, 1lu); */
/* 		return; */
/* 	} */
/* } */

/* EXTERNAL API ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_ADD_H_ */
