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

extern inline void free_big_digits(struct BigDigits *big);

/* EXTERN INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			words_to_digits(1)				*
 *									*
 * Returns an unsigned base 10 representation of the integer value of	*
 * word_t array 'words'.						*
 ************************************************************************/
size_t words_to_digits(digit_t **digits,
		       word_t *words,
		       const size_t word_count)
{
	size_t i;
	size_t alloc_count = MAX_DIGITS_PER_WORD;
	size_t alloc_acc   = MAX_DIGITS_PER_WORD * 2;

	for (i = 1lu; i < word_count; ++i) {
		alloc_count += (alloc_acc + 1lu);
		alloc_acc   += MAX_DIGITS_PER_WORD;
	}


	/* const size_t buff_alloc = next_pow_two(alloc_count); */
	const size_t buff_size  = sizeof(digit_t) * next_pow_two(alloc_count);

	/* struct BigDigits *result = init_zeroed_big_digits(buff_alloc); */

	digit_t *res_digits;

	HANDLE_MALLOC(res_digits, buff_size);

	size_t word = words[0lu];
	i = 0lu;
	do {
		res_digits[i] = ((digit_t) word) % 10u;
		word /= 10llu;
		++i;
	} while (word > 0u);


	if (word_count == 1lu) {
		HANDLE_REALLOC(res_digits, i);
		*digits = res_digits;
		return i;
	}

	digit_t WORD_BASE_DIGITS[] = {
		6u, 1u, 6u, 1u, 5u, 5u, 9u, 0u, 7u, 3u,
		7u, 0u, 4u, 4u, 7u, 6u, 4u, 4u, 8u, 1u
	};

	size_t base_cnt;
	size_t acc_cnt;
	size_t buff_cnt
	size_t res_cnt;

	digit_t *base;
	digit_t *base_acc;
	digit_t *mlt_buff;
	digit_t *tmp;

	HANDLE_CALLOC(base, sizeof(digit_t) * buff_alloc * 3lu);

	base_acc = &base[buff_alloc];
	mlt_buff = &base_acc[buff_alloc];


	size_t base_cnt	= DIGITS_PER_WORD_BASE;
	size_t acc_cnt	= DIGITS_PER_WORD_BASE;

	memcpy(base,
	       WORD_BASE_DIGITS,
	       sizeof(digit_t) * DIGITS_PER_WORD_BASE);

	memcpy(base_acc,
	       WORD_BASE_DIGITS,
	       sizeof(digit_t) * DIGITS_PER_WORD_BASE);

	i = 1lu;

	while (1) {
		buff_cnt = multiply_digits_by_word(mlt_buff,
						   base_acc,
						   acc_cnt,
						   words[i]);

		res_cnt = increment_digits(res_digits,
					   mlt_buff,
					   res_cnt,
					   buff_cnt);
		++i;

		if (i == word_count) {
			free(base);
			HANDLE_REALLOC(res_digits, res_cnt);
			*digits = res_digits;
			return res_cnt;
		}

		acc_cnt = do_multiply_digits(mlt_buff,
					     base_acc,
					     base,
					     next_pow_two(acc_cnt));
		tmp = base_acc;
		base_acc = mlt_buff;
		mlt_buff = tmp;
	}
}

/* big1->count >= big2->count */
inline void add_big_digits(struct BigDigits *restrict result,
			   struct BigDigits *restrict big1,
			   struct BigDigits *restrict big2)
{
	/* call add_digits */
	result->count = add_digits(result->digits,
				   big1->digits,
				   big2->digits,
				   big1->count,
				   big2->count);
}

/*
 * head function for recursive 'do_multiply_digits'
 *
 * input conditions:
 *	1. big1->count >= big2->count
 *	2. each have plenty memory allocation
 *	3. digits at indices >= count are zeroed
 */
inline void multiply_big_digits(struct BigDigits *restrict result,
				struct BigDigits *restrict big1,
				struct BigDigits *restrict big2)
{
	/* temporarily force counts to the same power of 2 */
	/* fputs("\n*************************************\nbig1: ", stdout); */
	/* for (int i = big1->count - 1; i > -1; --i) printf("%u", big1->digits[i]); */
	/* fputs("\nbig2: ", stdout); */
	/* for (int i = big2->count - 1; i > -1; --i) printf("%u", big2->digits[i]); */
	/* fflush(stdout); */

	/* do recursive Karatsuba multiplication */
	result->count = do_multiply_digits(result->digits,
					   big1->digits,
					   big2->digits,
					   next_pow_two(big1->count));
}

/*
 * Karatsuba multiplication:
 *
 * sets 'res_digits' to product and returns count;
 *
 * input conditions:
 *	1. big1->count == big2->count == 2ⁿ
 */
size_t do_multiply_digits(digit_t *restrict res_digits,
			  digit_t *restrict digits1,
			  digit_t *restrict digits2,
			  const size_t count)
{
	if (count == 1lu) {
		res_digits[0lu] = digits1[0lu] * digits2[0lu];

		if (res_digits[0lu] < 10u)
			return 1lu;

		res_digits[1lu] = res_digits[0lu] / 10u;
		res_digits[0lu] %= 10u;
		return 2lu;
	}

	const size_t buff_alloc = count * 2;
	const size_t half_count = count / 2lu;

	digit_t *upper1 = &digits1[half_count];
	digit_t *upper2 = &digits2[half_count];

	size_t max_add_cnt;

	digit_t *add_res1;

	HANDLE_MALLOC(add_res1, sizeof(digit_t) * buff_alloc * 8lu);

	digit_t *add_res2 = &add_res1[buff_alloc];
	digit_t *mlt_res1 = &add_res2[buff_alloc];
	digit_t *mlt_res2 = &mlt_res1[buff_alloc];
	digit_t *mlt_res3 = &mlt_res2[buff_alloc];
	digit_t *sub_res1 = &mlt_res3[buff_alloc];
	digit_t *sub_res2 = &sub_res1[buff_alloc];
	digit_t *ply_res  = &sub_res2[buff_alloc];

	const bool carry1 = add_split_digits(add_res1,
					     digits1,
					     upper1,
					     half_count);

	const bool carry2 = add_split_digits(add_res2,
					     digits2,
					     upper2,
					     half_count);
	if (carry1) {
		const size_t half_plus_one   = half_count + 1lu;
		const size_t rem_digits_size = sizeof(digit_t)
					     * (half_count - 1lu);

		add_res1[half_count] = 1u;
		memset(&add_res1[half_plus_one], 0, rem_digits_size);

		if (carry2) {
			add_res2[half_count] = 1u;
			memset(&add_res2[half_plus_one], 0, rem_digits_size);

		} else {
			memset(&add_res2[half_count], 0,
			       rem_digits_size + sizeof(digit_t));
		}

		max_add_cnt   = count;


	} else if (carry2) {
		const size_t half_plus_one   = half_count + 1lu;
		const size_t rem_digits_size = sizeof(digit_t)
					     * (half_count - 1lu);
		add_res2[half_count] = 1u;
		memset(&add_res2[half_plus_one], 0, rem_digits_size);

		memset(&add_res1[half_count], 0,
		       rem_digits_size + sizeof(digit_t));

		max_add_cnt   = count;

	} else {
		max_add_cnt   = half_count;
	}


	const size_t mlt_cnt1 = do_multiply_digits(mlt_res1,
						   add_res1,
						   add_res2,
						   max_add_cnt);

	const size_t mlt_cnt2 = do_multiply_digits(mlt_res2,
						   upper1,
						   upper2,
						   half_count);

	const size_t mlt_cnt3 = do_multiply_digits(mlt_res3,
						   digits1,
						   digits2,
						   half_count);

	const size_t sub_cnt1 = subtract_digits(sub_res1,
						mlt_res1, mlt_res2,
						mlt_cnt1, mlt_cnt2);

	const size_t sub_cnt2 = subtract_digits(sub_res2,
						sub_res1, mlt_res3,
						sub_cnt1, mlt_cnt3);

	const size_t ply_cnt = add_poly_pair(ply_res,
					     sub_res2, mlt_res3,
					     sub_cnt2, mlt_cnt3,
					     half_count);

	const size_t res_cnt = add_poly_pair(res_digits,
					     mlt_res2, ply_res,
					     mlt_cnt2, ply_cnt,
					     count);

	free(add_res1);

	return res_cnt;
}

/*
 * hard-wired helper for karatsuba
 *
 * sets 'res_digits' to 'lower + upper' and returns carry
 *
 * input conditions:
 */
bool add_split_digits(digit_t *restrict res_digits,
		      digit_t *restrict lower,
		      digit_t *restrict upper,
		      const size_t count)
{
	bool carry;

	res_digits[0lu] = upper[0lu] + lower[0lu];

	if (res_digits[0lu] > 9u) {
		res_digits[0lu] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (size_t i = 1lu; i < count; ++i) {
		res_digits[i] = upper[i] + lower[i];

		if (carry) {

			if (res_digits[i] > 8u) {
				res_digits[i] -= 9u;

			} else {
				++res_digits[i];
				carry = false;
			}

		} else if (res_digits[i] > 9u) {

			res_digits[i] -= 10u;
			carry = true;
		}
	}

	return carry;
}

/*
 * hard-wired helper for karatsuba
 *
 * sets 'res_digits' to 'digits1 * 10ⁿ + digits2' and returns count
 *
 * input conditions:
 *	1. digits1 * 10ⁿ >= digits2
 */
size_t add_poly_pair(digit_t *restrict res_digits,
		     digit_t *restrict digits1,
		     digit_t *restrict digits2,
		     const size_t count1,
		     const size_t count2,
		     const size_t n)
{
	if ((count1 == 1lu) && (digits1[0lu] == 0u)) {
		memcpy(res_digits,
		       digits2,
		       sizeof(digit_t) * count2);

		return count2;
	}

	if (n < count2) {
		memcpy(res_digits,
		       digits2,
		       sizeof(digit_t) * n);

		const size_t rem_cnt2 = count2 - n;

		if (rem_cnt2 > count1)
			return n + add_digits(&res_digits[n],
					      &digits2[n],
					      digits1,
					      rem_cnt2,
					      count1);

		return n + add_digits(&res_digits[n],
				      digits1,
				      &digits2[n],
				      count1,
				      rem_cnt2);
	}


	memcpy(res_digits,
	       digits2,
	       sizeof(digit_t) * count2);

	memset(&res_digits[count2],
	       0,
	       sizeof(digit_t) * (n - count2));

	memcpy(&res_digits[n],
	       digits1,
	       sizeof(digit_t) * count1);

	return count1 + n;
}

/*
 * hard-wired helper for karatsuba
 *
 * sets 'res_digits' to  'digits1 - digits2' and returns count
 *
 * input conditions:
 *	1. digits1 >= digits2
 */
size_t subtract_digits(digit_t *restrict res_digits,
		       digit_t *restrict digits1,
		       digit_t *restrict digits2,
		       const size_t count1,
		       const size_t count2)
{
	bool carry;
	digit_t large;
	digit_t small;
	size_t i;

	large = digits1[0lu];
	small = digits2[0lu];

	if (small > large) {
		res_digits[0lu] = (10u + large) - small;
		carry = true;
	} else {
		res_digits[0lu] = large - small;
		carry = false;
	}

	for (i = 1lu; i < count2; ++i) {

		large = digits1[i];
		small = digits2[i];

		if (carry) {

			if (small >= large) {
				res_digits[i] = (9u + large) - small;

			} else {
				res_digits[i] = large - (small + 1lu);
				carry = false;
			}

		} else {

			if (small > large) {
				res_digits[i] = (10u + large) - small;
				carry = true;

			} else {
				res_digits[i] = large - small;
			}
		}
	}

	if (carry) {
		while (digits1[i] == 0u) {
			res_digits[i] = 9u;
			++i;
		}

		res_digits[i] = digits1[i] - 1u;
		++i;
	}

	if (i == count1) {

		while (1) {
			if (i == 1u)
				return 1u;

			--i;

			if (res_digits[i] > 0u)
				return i + 1u;
		}
	}


	memcpy(&res_digits[i],
	       &digits1[i],
	       sizeof(digit_t) * (count1 - i));

	return count1;
}


/*
 * hard-wired helper for karatsuba
 *
 * sets 'res_digits' to 'digits1 + digits2' and returns count
 *
 * input conditions:
 *	1. count1 >= count2
 * */
size_t add_digits(digit_t *restrict res_digits,
		  digit_t *restrict digits1,
		  digit_t *restrict digits2,
		  const size_t count1,
		  const size_t count2)
{
	bool carry;
	size_t i;

	res_digits[0lu] = digits1[0lu] + digits2[0lu];

	if (res_digits[0lu] > 9u) {
		res_digits[0lu] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (i = 1lu; i < count2; ++i) {
		res_digits[i] = digits1[i] + digits2[i];

		if (carry) {

			if (res_digits[i] > 8u) {
				res_digits[i] -= 9u;

			} else {
				++res_digits[i];
				carry = false;
			}

		} else if (res_digits[i] > 9u) {

			res_digits[i] -= 10u;
			carry = true;
		}
	}

	if (carry) {
		while (1)  {
			if (i == count1) {
				res_digits[count1] = 1lu;
				return count1 + 1lu;
			}

			if (digits1[i] < 9u)
				break;

			res_digits[i] = 0u;
			++i;

		}

		res_digits[i] = digits1[i] + 1u;
		++i;
	}


	memcpy(&res_digits[i],
	       &digits1[i],
	       sizeof(digit_t) * (count1 - i));

	return count1;
}

/*
 * sets increments 'digits1' by 'digits2' and returns count
 *
 * input conditions:
 * count2 >= count1 OR digits2 == 0
 */
size_t increment_digits(digit_t *restrict digits1,
			digit_t *restrict digits2,
			const size_t count1,
			const size_t count2)
{
	if (count2 == 1lu)
		return count1; /* digits2 must be zero, do nothing */

	bool carry;
	size_t i;

	digits1[0lu] += digits2[0lu];

	if (digits1[0lu] > 9u) {
		digits1[0lu] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (i = 1lu; i < count1; ++i) {
		digits1[i] += digits2[i];

		if (carry) {

			if (digits1[i] > 8u) {
				digits1[i] -= 9u;

			} else {
				++digits1[i];
				carry = false;
			}

		} else if (digits1[i] > 9u) {

			digits1[i] -= 10u;
			carry = true;
		}
	}

	if (carry) {
		while (1)  {
			if (i == count2) {
				digits1[count2] = 1lu;
				return count2 + 1lu;
			}

			if (digits2[i] < 9u)
				break;

			digits1[i] = 0u;
			++i;
		}

		++digits1[i];
		++i;
	}

	memcpy(&digits1[i],
	       &digits2[i],
	       sizeof(digit_t) * (count2 - i));

	return count2;
}


size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       digit_t *restrict digits,
			       const size_t count,
			       word_t word)
{
	const buff_t buff_word = (buff_t) word;
	buff_t buffer = BUFF_ZERO;
	size_t i = 0lu;

	do {
		buffer += (buff_word * ((buff_t) digits[i]));
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;

	} while (i < count);

	while (buffer > BUFF_ZERO) {
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;
	}

	return i;
}
/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline struct BigDigits *init_zeroed_big_digits(const size_t count)
{
	struct BigDigits *big;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_CALLOC(big->digits, sizeof(digit_t), count);

	return big;
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
