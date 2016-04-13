/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/utils.h"
#include "big_int/digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* word base 2⁶⁴ = 18446744073709551616 */
#define DPWB 20ul

static const digit_t WORD_BASE_DIGITS[] = {
	6u, 1u, 6u, 1u, 5u, 5u, 9u, 0u, 7u, 3u,
	7u, 0u, 4u, 4u, 7u, 6u, 4u, 4u, 8u, 1u
};

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* EXTERN INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/************************************************************************
 *			words_to_digits(1)				*
 *									*
 * Deferences **digits to an unsigned base 10 representation		*
 * (digit_t array) of the integer value of word_t array 'words' and	*
 * returns count.							*
 ************************************************************************/
size_t words_to_digits(digit_t **digits,
		       word_t *words,
		       const size_t count)
{

	size_t i;

	/* sum expression:
	 *
	 * DPWB + 1 + 2DPWB + 1 ... (count - 1)DPWB + 1 + word_countDPWB
	 *
	 * = count * (((count + 1) * DPWB) / 2 + 1) - 1
	 *
	 * or
	 *
	 * = (count * (count + 1) * DPWB) / 2 + count - 1
	 *
	 * to ensure no truncation on division by 2
	 */
	const size_t alloc_count = ((count + 1ul) * count * DPWB) / 2ul
				 + count - 1ul;



	const size_t buff_alloc = next_pow_two(alloc_count);

	digit_t *res_digits;

	HANDLE_MALLOC(res_digits, sizeof(digit_t) * buff_alloc);

	word_t word = words[0ul];
	i = 0ul;
	do {
		res_digits[i] = (digit_t) (word % 10ull);
		word /= 10ull;
		++i;
	} while (word > 0u);


	if (count == 1ul) {
		HANDLE_REALLOC(res_digits, sizeof(digit_t) * i);
		*digits = res_digits;
		return i;
	}

	const size_t size_zeros = (buff_alloc - DPWB) * sizeof(digit_t);

	size_t res_cnt = i;
	size_t acc_cnt;
	size_t buff_cnt;
	size_t npt_cnt;

	digit_t *base;
	digit_t *base_acc;
	digit_t *mlt_buff;
	digit_t *tmp;

	HANDLE_MALLOC(base, sizeof(digit_t) * buff_alloc * 3ul);

	base_acc = &base[buff_alloc];
	mlt_buff = &base_acc[buff_alloc];

	acc_cnt	= DPWB;

	set_zero_padded_word_base(base,
				  size_zeros);

	set_zero_padded_word_base(base_acc,
				  size_zeros);

	i = 1ul;

	while (1) {

		if (words[i] == 0ull)
			goto NEXT_WORD;

		buff_cnt = multiply_digits_by_word(mlt_buff,
						   base_acc,
						   acc_cnt,
						   words[i]);

		res_cnt = increment_digits(res_digits,
					   mlt_buff,
					   res_cnt,
					   buff_cnt);
NEXT_WORD:
		++i;

		if (i == count)
			break;

		acc_cnt = do_multiply_digits(mlt_buff,
					     base_acc,
					     base,
					     next_pow_two(acc_cnt));

		tmp = base_acc;
		base_acc = mlt_buff;
		mlt_buff = tmp;
	}

	free(base);

	HANDLE_REALLOC(res_digits, sizeof(digit_t) * res_cnt);

	*digits = res_digits;

	return res_cnt;
}

/************************************************************************
 *			digits_to_words(1)				*
 *									*
 * Deferences **words to an unsigned base 2⁶⁴ representation		*
 * (word_t array) of the integer value of digit_t array 'digits' and	*
 * returns count.							*
 ************************************************************************/
size_t digits_to_words(word_t **words,
		       digit_t *digits,
		       const size_t count)
{
	size_t i;
	word_t buffer   = digits[0ul];
	word_t buff_acc = 10ull;

	if (count < DPWB) {

		HANDLE_MALLOC(*words, sizeof(word_t));

		for (i = 1ul; i < count; ++i) {
			buffer   += (((word_t) digits[i]) * buff_acc);
			buff_acc *= 10ull;
		}

		*words[0ul] = buffer;
		return 1ul;
	}

	const size_t half_count = count / 2ul;

	const size_t buff_alloc = next_pow_two(count);

	const size_t res_alloc  = (count / DPWB) + 1ul;

	/* generate string of digit_t arrays representing word "bits" > 1
	 *
	 * {(word base)¹, (word base)², ..., (word base)ⁿ}
	 *
	 * where 'half_count <= count((word base)ⁿ) < count'
	 */

	size_t *bit_counts;
	digit_t *base;
	digit_t *base_acc;
	digit_t **bit_digits;

	word_t *res_words;

	/* HANDLE_MALLOC(res_words,  sizeof(word_t)    * res_alloc); */
	/* HANDLE_MALLOC(bit_counts, sizeof(size_t)    * res_alloc); */
	/* HANDLE_MALLOC(bit_digits, sizeof(digit_t *) * res_alloc); */


	/* HANDLE_CALLOC(base, sizeof(digit_t), buff_alloc * 2ul); */


	/* base_acc = &base[buff_alloc]; */
	/* mlt_buff = &base_acc[buff_alloc]; */

	/* acc_cnt	= DPWB; */

	/* memcpy(base, */
	/*        &WORD_BASE_DIGITS[0ul], */
	/*        sizeof(digit_t) * DPWB); */

	/* memcpy(base_acc, */
	/*        &WORD_BASE_DIGITS[0ul], */
	/*        sizeof(digit_t) * DPWB); */

	/* digit_t **bit_digits = &base[buff_alloc]; */
	/* mlt_buff = &base_acc[buff_alloc]; */

	/* acc_cnt	 = DPWB; */

	/* memcpy(base, */
	/*        &WORD_BASE_DIGITS[0ul], */
	/*        sizeof(digit_t) * DPWB); */

	/* memcpy(base, */
	/*        &WORD_BASE_DIGITS[0ul], */
	/*        sizeof(digit_t) * DPWB); */

	/* while (1) { */

	/* } */

	return 42ul;

}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/*
 * Karatsuba multiplication:
 *
 * sets 'res_digits' to product and returns count;
 *
 * input conditions:
 *	1. count1 == count2 == 2ⁿ
 *	2. digits have plenty memory allocation
 *	3. digits at indices >= count are zeroed
 */
size_t do_multiply_digits(digit_t *restrict res_digits,
			  digit_t *restrict digits1,
			  digit_t *restrict digits2,
			  const size_t count)
{
	if (count == 1ul) {
		res_digits[0ul] = digits1[0ul] * digits2[0ul];

		if (res_digits[0ul] < 10u)
			return 1ul;

		res_digits[1ul] = res_digits[0ul] / 10u;
		res_digits[0ul] %= 10u;
		return 2ul;
	}

	const size_t buff_alloc = count * 2;
	const size_t half_count = count / 2ul;

	digit_t *upper1 = &digits1[half_count];
	digit_t *upper2 = &digits2[half_count];

	size_t max_add_cnt;

	digit_t *add_res1;

	HANDLE_MALLOC(add_res1, sizeof(digit_t) * buff_alloc * 8ul);

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
		const size_t half_plus_one   = half_count + 1ul;
		const size_t rem_digits_size = sizeof(digit_t)
					     * (half_count - 1ul);

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
		const size_t half_plus_one   = half_count + 1ul;
		const size_t rem_digits_size = sizeof(digit_t)
					     * (half_count - 1ul);
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

	res_digits[0ul] = upper[0ul] + lower[0ul];

	if (res_digits[0ul] > 9u) {
		res_digits[0ul] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (size_t i = 1ul; i < count; ++i) {
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
	if ((count1 == 1ul) && (digits1[0ul] == 0u)) {
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

	large = digits1[0ul];
	small = digits2[0ul];

	if (small > large) {
		res_digits[0ul] = (10u + large) - small;
		carry = true;
	} else {
		res_digits[0ul] = large - small;
		carry = false;
	}

	for (i = 1ul; i < count2; ++i) {

		large = digits1[i];
		small = digits2[i];

		if (carry) {

			if (small >= large) {
				res_digits[i] = (9u + large) - small;

			} else {
				res_digits[i] = large - (small + 1ul);
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

	res_digits[0ul] = digits1[0ul] + digits2[0ul];

	if (res_digits[0ul] > 9u) {
		res_digits[0ul] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (i = 1ul; i < count2; ++i) {
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
				res_digits[count1] = 1ul;
				return count1 + 1ul;
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
 * count2 >= count1
 */
size_t increment_digits(digit_t *restrict digits1,
			digit_t *restrict digits2,
			const size_t count1,
			const size_t count2)
{
	bool carry;
	size_t i;

	digits1[0ul] += digits2[0ul];

	if (digits1[0ul] > 9u) {
		digits1[0ul] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (i = 1ul; i < count1; ++i) {
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
				digits1[count2] = 1ul;
				return count2 + 1ul;
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

/*
 * sets 'res_digits' to the product of 'digits' and 'word' and returns count
 * input conditions:
 *	1. word > 0
 */

size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       digit_t *restrict digits,
			       const size_t count,
			       word_t word)
{
	const buff_t buff_word = (buff_t) word;
	buff_t buffer = buff_word * ((buff_t) digits[0ul]);

	res_digits[0ul] = (digit_t) (buffer % BUFF_TEN);
	buffer /= BUFF_TEN;

	size_t i = 1ul;

	while (i < count) {
		buffer += (buff_word * ((buff_t) digits[i]));
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;
	}

	while (buffer > BUFF_ZERO) {
		res_digits[i] = (digit_t) (buffer % BUFF_TEN);
		buffer /= BUFF_TEN;
		++i;
	}

	return i;
}

inline void set_zero_padded_word_base(digit_t *base,
				      const size_t pad_size)
{
	memcpy(base,
	       &WORD_BASE_DIGITS[0ul],
	       sizeof(digit_t) * DPWB);

	memset(&base[DPWB],
	       0,
	       pad_size);
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
