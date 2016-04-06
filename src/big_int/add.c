/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/memory.h"
#include "big_int/utils.h"
#include "big_int/add.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

/* EXTERNAL INLINE FUNCTION PROTOTYPES  ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

extern inline void add_big_ints(struct BigInt *result,
				struct BigInt *big1,
				struct BigInt *big2);

/* EXTERNAL INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */





/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

void add_big_ints_same_sign(struct BigInt *result,
			    struct BigInt *big1,
			    struct BigInt *big2)
{
	if (big2->word_count > big1->word_count)
		VAR_SWAP(big1, big2);

	const size_t lrg_wc = big1->word_count;
	const size_t sml_wc = big2->word_count;
	const size_t req_wc = lrg_wc + 1lu;

	if (result->alloc_count < req_wc)
		expand_big_int(result, req_wc);

	result->sign = big1->sign;

	word_t *lrg_words = big1->words;
	word_t *sml_words = big2->words;
	word_t *res_words = result->words;



	buff_t add_buffer = ((buff_t) lrg_words[0])
			  + ((buff_t) sml_words[0]);

	word_t carry	  = (word_t) (add_buffer >> WORD_BITS);

	printf("carry: %llu\n", carry);
	printf("bitss: %zu\n", WORD_BITS);

	res_words[0] = (word_t) add_buffer;

	size_t i = 1lu;

	while (i < sml_wc) {
		add_buffer   = ((buff_t) lrg_words[i])
			     + ((buff_t) sml_words[i]);

		res_words[i] = ((word_t) add_buffer) + carry;
		carry	     = (word_t) (add_buffer >> WORD_BITS);
		++i;
	}


	while (i < lrg_wc) {

		if (carry == 0llu) {
			memcpy(&res_words[i], &lrg_words[i], lrg_wc - i);
			result->word_count = lrg_wc;
			return;
		}

		add_buffer   = lrg_words[i] + carry;
		res_words[i] = (word_t) add_buffer;
		carry	     = (word_t) (add_buffer >> WORD_BITS);
		++i;
	}

	if (carry == 0llu) {
		result->word_count = lrg_wc;
		return;
	}

	result->words[lrg_wc] = carry;
	result->word_count    = req_wc;
}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
