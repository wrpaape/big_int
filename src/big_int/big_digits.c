/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/big_digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define BUFF_TEN ((buff_t) 10llu)

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

extern inline struct BigDigits *init_big_digits(const size_t alloc_count);
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
	word_t first_word;
	word_t i;
	size_t j;
	word_t n;

	struct BigDigits *big = init_big_digits(MAX_DIGITS_PER_WORD * word_count);

	big->digits[0lu] = 0u;
	big->count	 = 1lu;

	/* for (first_word = words[0lu]; first_word > 0lu; first_word /= 10lu) { */

	/* 	add_digit_to_big_digits(big, */
	/* 				(digit_t) (first_word % 10lu)); */
	/* } */



	/* for (n = 1lu; n < word_count; ++n) { */

	/* 	for (i = words[n] * ((word_t) n); i > 0llu; --i) { */

	/* 		/1* for (j = 0lu; j < MAX_DIGITS_PER_WORD; ++j) { *1/ */

	/* 			add_digit_to_big_digits(big, */
	/* 						BASE_DEC_DIGITS[j]); */
	/* 		/1* } *1/ */
	/* 	} */
	/* } */

	return big;
}

/* big1->count >= big2->count */
void add_big_digits(struct BigDigits *restrict result,
		    struct BigDigits *restrict big1,
		    struct BigDigits *restrict big2)
{
	const size_t lrg_count = big1->count;
	const size_t sml_count = big2->count;

	digit_t *lrg_digits = big1->digits;
	digit_t *sml_digits = big2->digits;
	digit_t *res_digits = result->digits;


	digit_t sum_buffer = 0u;
	size_t i = 0lu;

	do {
		sum_buffer += (sml_digits[i] + lrg_digits[i]);

		res_digits[i] = (sum_buffer % 10u);

		sum_buffer /= 10u;

		++i;

	} while (i < sml_count);

	while (i < lrg_count) {

		sum_buffer += lrg_digits[i];

		res_digits[i] = (sum_buffer % 10u);

		sum_buffer /= 10u;

		++i;
	}

	if (sum_buffer == 0u) {
		result->count = lrg_count;

	} else {
		res_digits[i] = sum_buffer;
		result->count = lrg_count + 1lu;
	}
}

/* Karatsuba */
void multiply_big_digits(struct BigDigits *restrict result,
			 struct BigDigits *restrict big1,
			 struct BigDigits *restrict big2)
{
}

void multiply_big_digits_by_digit(struct BigDigits *restrict result,
				  struct BigDigits *restrict big,
				  digit_t digit)
{
	digit_t *res_digits = result->digits;
	digit_t *big_digits = big->digits;
	digit_t buffer = 0u;
	size_t count = big->count;
	size_t i = 0lu;

	do {
		buffer += (digit * big_digits[i]);
		res_digits[i] = buffer % 10u;
		buffer /= 10u;
		++i;

	} while (i < count);

	while (buffer > 0u) {
		res_digits[i] = buffer % 10u;
		buffer /= 10u;
		++i;
	}

	result->count = i;
}

void multiply_big_digits_by_word(struct BigDigits *restrict result,
				 struct BigDigits *restrict big,
				 word_t word)
{
	digit_t *res_digits = result->digits;
	digit_t *big_digits = big->digits;
	buff_t buffer = BUFF_ZERO;
	size_t count = big->count;
	size_t i = 0lu;

	do {
		buffer += multiply_word_by_digit(word, big_digits[i]);
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;

	} while (i < count);

	while (buffer > BUFF_ZERO) {
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;
	}

	result->count = i;
}
/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline buff_t multiply_word_by_digit(word_t word,
				     digit_t digit)
{
	return ((buff_t) word) * ((buff_t) digit);
}


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
