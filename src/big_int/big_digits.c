/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/big_digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

static const digit_t BASE_DEC_DIGITS[] = {
	1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 6
};
/* static const char CHAR_MAP[] = { */
/* 	'0', '1', '2', '3', '4', '5', '6', '7', */
/* 	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F', */
/* }; */

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

extern inline void free_big_digits(struct BigDigits *big);

/* EXTERN INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			words_to_big_digits(1)				*
 *									*
 * Returns an unsigned base 10 representation of the integer value of	*
 * word_t array 'words'.						*
 ************************************************************************/
struct BigDigits *words_to_big_digits(const size_t word_count,
				      word_t *words)
{
	struct BigDigits *big;
	word_t first_word;
	word_t i;
	size_t j;
	word_t n;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_MALLOC(big->digits,
		      sizeof(digit_t) * MAX_DEC_DIGITS_PER_WORD * word_count);

	big->digits[0lu] = 0u;
	big->count	 = 1lu;

	/* for (first_word = words[0lu]; first_word > 0lu; first_word /= 10lu) { */

	/* 	add_digit_to_big_digits(big, */
	/* 				(digit_t) (first_word % 10lu)); */
	/* } */



	/* for (n = 1lu; n < word_count; ++n) { */

	/* 	for (i = words[n] * ((word_t) n); i > 0llu; --i) { */

	/* 		/1* for (j = 0lu; j < MAX_DEC_DIGITS_PER_WORD; ++j) { *1/ */

	/* 			add_digit_to_big_digits(big, */
	/* 						BASE_DEC_DIGITS[j]); */
	/* 		/1* } *1/ */
	/* 	} */
	/* } */

	return big;
}
/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline void add_digit_to_big_digits(struct BigDigits *big,
				    digit_t digit)
{
	/* digit_t *digits = big->digits; */
	/* size_t count	= big->count; */

	/* word_t sum_buffer = add_digits(lower_digit(word), */
	/* 			       digits[0lu]) */
	/* digit_t carry; */
	/* size_t i = 0lu; */


	/* while (1) { */
	/* } */

}

/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
