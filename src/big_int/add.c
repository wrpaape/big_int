/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/memory.h"
#include "big_int/utils.h"
#include "big_int/add.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

/* EXTERNAL INLINE FUNCTION PROTOTYPES  ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

extern inline void add_big_ints(struct BigInt *restrict result,
				const struct BigInt *restrict big1,
				const struct BigInt *restrict big2);

/* EXTERNAL INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */





/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

void add_big_ints_same_sign(struct BigInt *restrict result,
			    const struct BigInt *restrict big1,
			    const struct BigInt *restrict big2)
{
	if (big2->word_count > big1->word_count)
		VAR_SWAP(big1, big2);

	const size_t lrg_wc = big1->word_count;
	const size_t sml_wc = big2->word_count;
	const size_t req_wc = lrg_wc + 1ul;

	if (result->alloc_count < req_wc)
		expand_big_int(result, req_wc);

	result->sign = big1->sign;

	word_t *lrg_words = big1->words;
	word_t *sml_words = big2->words;
	word_t *res_words = result->words;

	buff_t sum_buffer = add_words(lrg_words[0ul],
				      sml_words[0ul]);

	res_words[0ul] = lower_word(sum_buffer);

	word_t carry = upper_word(sum_buffer);

	size_t i = 1ul;

	/* add 'sml_words' to 'lrg_words', accumulating word overflow 'carry' */
	while (i < sml_wc) {
		sum_buffer = add_words(lrg_words[i],
				       sml_words[i]);

		sum_buffer = add_word_to_buffer(sum_buffer,
						carry);

		res_words[i] = lower_word(sum_buffer);

		carry = upper_word(sum_buffer);

		++i;
	}


	/* propogate 'carry' to unmatched upper words of 'lrg_words' */
	while (i < lrg_wc) {

		if (carry == 0ull) {
			memcpy(&res_words[i],
			       &lrg_words[i],
			       lrg_wc - i);

			result->word_count = lrg_wc;
			return;
		}

		sum_buffer = add_words(lrg_words[i],
				       carry);

		res_words[i] = lower_word(sum_buffer);
		carry	     = upper_word(sum_buffer);
		++i;
	}

	if (carry == 0ull) {
		result->word_count = lrg_wc;
		return;
	}


	result->words[lrg_wc] = carry;
	result->word_count    = req_wc;
}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
