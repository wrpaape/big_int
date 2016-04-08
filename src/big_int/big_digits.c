/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/utils.h"
#include "big_int/big_digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
#define DIGITS_PER_WORD_BASE 20lu
/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


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
	size_t i;
	word_t word;
	digit_t *digits;

	size_t alloc_count = MAX_DIGITS_PER_WORD;
	size_t alloc_acc   = MAX_DIGITS_PER_WORD * 2;

	for (i = 1lu; i < word_count; ++i) {
		alloc_count += (alloc_acc + 1lu);
		alloc_acc   += MAX_DIGITS_PER_WORD;
	}


	const size_t buffer_size = sizeof(digit_t) * next_pow_two(alloc_count);

	HANDLE_MALLOC(digits, buffer_size);

	word = words[0lu];

	i = 0lu;

	do {
		digits[i] = word % 10lu;
		word /= 10lu;
		++i;

	} while (word > 0lu);

	HANDLE_MALLOC(big, sizeof(struct BigDigits));

	big->count  = i;
	big->digits = digits;

	if (word_count == 1lu)
		return big;

	struct BigDigits *base_acc;
	struct BigDigits *buff1;
	struct BigDigits *buff2;
	struct BigDigits *tmp;
	digit_t *acc_digits;
	digit_t *buff_digits;

	digit_t word_base_digits[] = {
		1u, 8u, 4u, 4u, 6u, 7u, 4u, 4u, 0u, 7u,
		3u, 7u, 0u, 9u, 5u, 5u, 1u, 6u, 1u, 6u
	};

	struct BigDigits base = {
		.count  = DIGITS_PER_WORD_BASE,
		.digits = word_base_digits
	};


	HANDLE_MALLOC(base_acc, sizeof(struct BigDigits));
	HANDLE_MALLOC(buff1,	sizeof(struct BigDigits));
	HANDLE_MALLOC(buff2,	sizeof(struct BigDigits));
	HANDLE_MALLOC(base_acc->digits, buffer_size);
	HANDLE_MALLOC(buff1->digits,	buffer_size);
	HANDLE_MALLOC(buff2->digits,	buffer_size);

	base_acc->count  = DIGITS_PER_WORD_BASE;
	memcpy(base_acc->digits,
	       base.digits,
	       sizeof(digit_t) * DIGITS_PER_WORD_BASE);


	i = 1lu;

	while (1) {
		word = words[i];

		multiply_big_digits_by_word(buff1,
					    base_acc,
					    word);

		add_big_digits(buff2,
			       buff1,
			       big);

		++i;

		if (i == word_count) {
			free_big_digits(base_acc);
			free_big_digits(buff1);
			free_big_digits(big);

			return buff2;
		}

		multiply_big_digits(buff1,
				    base_acc,
				    base);

		tmp = base_acc;
		base_acc = buff1;
		buff1 = base_acc;

		tmp = buff2;
		buff2 = big;
		big = buff2;
	}
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

	if (i == lrg_count) {

		if (carry > 0lu)
			EXIT_ON_FAILURE("AWOOGA, big2 > big1");

		/* rewind to first nonzero digit */
		do {
			--i;
		} while ((i > 0lu) && (res_digits[i] == 0u));

		result->count = i + 1lu;
		return;
	}

	/* propogate carry to upper digits */
	if (carry == 1u) {

		while (lrg_digits[i] == 0u) {
			res_digits[i] = 9u;
			++i;

			if (i == lrg_count)
				EXIT_ON_FAILURE("AWOOGA, segfault immenent, malformed big1");
		}

		res_digits[i] = lrg_digits[i] - 1lu;
		++i;
	}

	/* copy remaining digits directly */
	memcpy(res_digits, &lrg_digits[i], sizeof(digit_t) * (lrg_count - i));

	result->count = lrg_count;
}

/* Karatsuba, big1->count == big2->count */

inline void multiply_big_digits(struct BigDigits *restrict result,
				struct BigDigits *restrict big1,
				struct BigDigits *restrict big2)
{
}

void do_multiply_big_digits(struct BigDigits *restrict result,
			    struct BigDigits *restrict big1,
			    struct BigDigits *restrict big2)
{
	/* if (big2->count == 1lu) { */
	/* 	multiply_big_digits_by_digit(result, */
	/* 				     big1, */
	/* 				     big2->digits[0lu]); */
	/* 	return; */
	/* } */

	/* /1* round up if odd count, ensure split is even or left-biased *1/ */
	/* const size_t m_half = (big1->count & 1lu) */
	/* 		    ? (big1->count / 2lu) + 1lu */
	/* 		    : big1->count / 2lu; */

	/* /1* split digits of 'big1', 'big2' *1/ */
	/* struct BigDigits lower1; */
	/* struct BigDigits lower2; */
	/* struct BigDigits upper1; */
	/* struct BigDigits upper2; */

	/* lower1.count  = m_half; */
	/* lower1.digits = big1->digits; */

	/* upper1.count  = big1->count  - m_half; */
	/* upper1.digits = big1->digits + m_half; */


	/* /1* ensure count of 'upper2' is at least 1 *1/ */
	/* if (big2->count > m_half) { */

	/* 	lower2.count  = m_half; */
	/* 	lower2.digits = big2->digits; */

	/* 	upper2.count  = big2->count  - m_half; */
	/* 	upper2.digits = big2->digits + m_half; */

	/* } else { */

	/* 	lower2.count  = big2->count; */
	/* 	lower2.digits = big2->digits; */

	/* 	upper2.count  = 1lu; */
	/* 	upper2.digits = {0u}; */
	/* } */

	/* /1* allocate space for temporary intermediate BigDigits *1/ */
	/* const size_t add_alloc_1  = m_half	 + 1lu; */
	/* const size_t mlt_alloc_1  = big1->count  + 2lu; */
	/* const size_t mlt_alloc_2a = mlt_alloc_1  + m_half; */
	/* const size_t mlt_alloc_2b = mlt_alloc_2a + m_half; */
	/* const size_t add_alloc_2  = mlt_alloc_2b + 1lu; */

	/* struct BigDigits *add_tmp_1a = init_big_digits(add_alloc_1); */
	/* struct BigDigits *add_tmp_1b = init_big_digits(add_alloc_1); */

	/* struct BigDigits *mlt_tmp_1a = init_big_digits(mlt_alloc_1); */
	/* struct BigDigits *mlt_tmp_1b = init_big_digits(mlt_alloc_1); */
	/* struct BigDigits *mlt_tmp_1c = init_big_digits(mlt_alloc_1); */

	/* struct BigDigits *sub_tmp_1a = init_big_digits(mlt_alloc_1); */
	/* struct BigDigits *sub_tmp_1b = init_big_digits(mlt_alloc_1); */

	/* struct BigDigits *mlt_tmp_2a = init_big_digits(mlt_alloc_2a); */
	/* struct BigDigits *mlt_tmp_2b = init_big_digits(mlt_alloc_2b); */

	/* struct BigDigits *add_tmp_2a = init_big_digits(add_alloc_2); */

	/* add_big_digits(add_tmp_1a, */
	/* 	       &lower1, */
	/* 	       &upper); */

	/* add_big_digits(add_tmp_1b, */
	/* 	       &lower2, */
	/* 	       &upper); */

	/* do_multiply_big_digits(mlt_tmp_1a, */
	/* 		       &lower1, */
	/* 		       &lower2); */

	/* do_multiply_big_digits(mlt_tmp_1b, */
	/* 		       add_tmp_1a, */
	/* 		       add_tmp_1b); */

	/* do_multiply_big_digits(mlt_tmp_1c, */
	/* 		       &upper1, */
	/* 		       &upper2); */

	/* subtract_big_digits(sub_tmp_1a, */
	/* 		    mlt_tmp_1b, */
	/* 		    mlt_tmp_1c); */

	/* subtract_big_digits(sub_tmp_1b, */
	/* 		    sub_tmp_1a, */
	/* 		    mlt_tmp_1a); */

	/* const digit_t ten_raised_m_half = nth_pow_digit(10u, (int) m_half); */

	/* multiply_big_digits_by_digit(mlt_tmp_2a, */
	/* 			     sub_tmp_1b, */
	/* 			     ten_raised_m_half); */

	/* multiply_big_digits_by_digit(mlt_tmp_2b, */
	/* 			     mlt_tmp_1c, */
	/* 			     ten_raised_m_half * ten_raised_m_half); */

	/* add_big_digits(add_tmp_2a, */
	/* 	       mlt_tmp_2a, */
	/* 	       mlt_tmp_2c); */

	/* add_big_digits(result, mlt_tmp_2b, add_tmp_2a); */

	/* free_big_digits(add_tmp_1a); */
	/* free_big_digits(add_tmp_1b); */
	/* free_big_digits(mlt_tmp_1a); */
	/* free_big_digits(mlt_tmp_1b); */
	/* free_big_digits(mlt_tmp_1c); */
	/* free_big_digits(sub_tmp_1a); */
	/* free_big_digits(sub_tmp_1b); */
	/* free_big_digits(mlt_tmp_2a); */
	/* free_big_digits(mlt_tmp_2b); */
	/* free_big_digits(add_tmp_2a); */
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

inline struct BigDigits *init_big_digits(const size_t digits_size)
{
	struct BigDigits *big;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_CALLOC(big->digits, digits_size);

	return big;
}

inline void free_big_digits(struct BigDigits *big)
{
	free(big->digits);
	free(big);
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
