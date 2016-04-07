/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/utils.h"
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

/* big1 >= big2 */
void subtract_big_digits(struct BigDigits *restrict result,
			 struct BigDigits *restrict big1,
			 struct BigDigits *restrict big2)
{
	const size_t lrg_count = big1->count;
	const size_t sml_count = big2->count;

	digit_t *lrg_digits = big1->digits;
	digit_t *sml_digits = big2->digits;
	digit_t *res_digits  = result->digits;

	digit_t lrg = lrg_digits[0lu];
	digit_t sml = sml_digits[0lu];

	digit_t carry;
	size_t i = 1lu;

	if (lrg < sml) {
		res_digits[0lu] = (10u + lrg) - sml;
		carry = 1u;

	} else {
		res_digits[0lu] = lrg - sml;
		carry = 0u;
	}

	for (i = 1lu; i < sml_count; ++i) {

		lrg = lrg_digits[i];
		sml = sml_digits[i];

		/* only possible when lrg == 0 and carry == 1 */
		if (lrg < carry) {
			res_digits[i] = 9u - sml;
			continue;
		}

		lrg -= carry;

		if (lrg < sml) {
			res_digits[i] = (10u + lrg) - sml;
			carry = 1u;

		} else {
			res_digits[i] = lrg - sml;
			carry = 0u;
		}
	}



}

/* Karatsuba, big1->count >= big2->count */
void multiply_big_digits(struct BigDigits *restrict result,
			 struct BigDigits *restrict big1,
			 struct BigDigits *restrict big2)
{
	if (big2->count == 1lu) {
		multiply_big_digits_by_digit(result,
					     big1,
					     big2->digits[0lu]);
		return;
	}

	/* round up if odd count, ensure split is even or left-biased */
	const size_t m_half = (big1->count & 1lu)
			    ? (big1->count / 2lu) + 1lu
			    : big1->count / 2lu;

	/* split digits of 'big1', 'big2' */
	struct BigDigits lower1;
	struct BigDigits lower2;
	struct BigDigits upper1;
	struct BigDigits upper2;

	lower1 = {
		.count  = m_half,
		.digits = big1->digits
	};

	upper1 = {
		.count  = big1->count  - m_half,
		.digits = big1->digits + m_half
	};


	/* ensure count of 'upper2' is at least 1 */
	if (big2->count > m_half) {

		lower2 = {
			.count  = m_half,
			.digits = big2->digits
		};

		upper2 = {
			.count  = big2->count  - m_half,
			.digits = big2->digits + m_half
		};

	} else {

		lower2 = {
			.count  = big2->count,
			.digits = big2->digits
		};

		upper2 = {
			.count  = 1lu,
			.digits = {0u}
		};
	}

	/* allocate space for temporary intermediate BigDigits */
	const size_t m_res_size = big1->count + 2lu;
	const size_t a_res_size = m_half + 1lu;

	struct BigDigits *a_res1 = init_big_digits(a_res_size);
	struct BigDigits *a_res2 = init_big_digits(a_res_size);
	struct BigDigits *m_res1 = init_big_digits(m_res_size);
	struct BigDigits *m_res2 = init_big_digits(m_res_size);
	struct BigDigits *m_res3 = init_big_digits(m_res_size);
	struct BigDigits *m_res4 = init_big_digits(m_res_size + m_half);
	struct BigDigits *m_res5 = init_big_digits(m_res_size + (m_half * 2lu));


	add_big_digits(a_res1, &lower1, &upper);
	add_big_digits(a_res2, &lower2, &upper);

	multiply_big_digits(m_res1, &lower1, &lower2);
	multiply_big_digits(m_res2, a_res1,  a_res2);
	multiply_big_digits(m_res3, &upper1, &upper2);

	const digit_t ten_raised_m_half = nth_pow_digit(10u, (int) m_half);


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
