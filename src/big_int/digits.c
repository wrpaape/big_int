/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/utils.h"
#include "big_int/digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* word base 2⁶⁴ = 18446744073709551616 */

/* digits per word base */
#define DPWB 20ul
/* next_pow_two(DPWB) */
#define NEXT_POW_TWO_DPWB 32ul

/* digits in 2¹²⁸ */
#define DPWB_SQ 39ul

static const digit_t WORD_BASE_DIGITS[] = {
	6u, 1u, 6u, 1u, 5u, 5u, 9u, 0u, 7u, 3u,
	7u, 0u, 4u, 4u, 7u, 6u, 4u, 4u, 8u, 1u
};

static const word_t TEN_POW_MAP[DPWB] = {
	1ull, 10ull, 100ull, 1000ull, 10000ull, 100000ull, 1000000ull,
	10000000ull, 100000000ull, 1000000000ull, 10000000000ull,
	100000000000ull, 1000000000000ull, 10000000000000ull,
	100000000000000ull, 1000000000000000ull, 10000000000000000ull,
	100000000000000000ull, 1000000000000000000ull, 10000000000000000000ull
};

static const digit_t NINES_COMP[] = {
	9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u
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

size_t words_to_digits(digit_t **restrict digits,
		       const word_t *restrict words,
		       const size_t count)
{
	if (count == 1ul) {
		HANDLE_MALLOC(*digits, sizeof(digit_t) * DPWB);

		const size_t res_cnt = word_to_digits(*digits,
						      words[0ul]);

		HANDLE_REALLOC(*digits, sizeof(digit_t) * res_cnt);

		return res_cnt;
	}

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

	const size_t buff_size = sizeof(digit_t) * buff_alloc;


	digit_t *res_digits;

	HANDLE_MALLOC(res_digits, buff_size);

	size_t res_cnt = word_to_digits(res_digits,
					words[0ul]);

	digit_t *mlt_buff;

	HANDLE_MALLOC(mlt_buff,	  buff_size * 3ul);

	size_t buff_cnt = multiply_digits_by_word(mlt_buff,
						  &WORD_BASE_DIGITS[0ul],
						  DPWB,
						  words[1ul]);

	res_cnt = increment_digits(res_digits,
				   mlt_buff,
				   res_cnt,
				   buff_cnt);

	if (count == 2ul)
		goto FREE_TMPS_REALLOC_RETURN;

	digit_t *base	  = &mlt_buff[buff_alloc];
	digit_t *base_acc = &base[buff_alloc];
	digit_t *tmp;

	const size_t base_pad = buff_size - (sizeof(digit_t) * DPWB);
	const size_t buff_pad = buff_size - (sizeof(digit_t) * DPWB_SQ);

	set_zero_padded_word_base(base,
				  base_pad);

	set_zero_padded_word_base(base_acc,
				  base_pad);
	memset(mlt_buff,
	       0,
	       buff_pad);

	size_t acc_cnt = do_multiply_digits(mlt_buff,
					    base_acc,
					    base,
					    NEXT_POW_TWO_DPWB);

	size_t i = 3ul;
	word_t word = words[2ul];

	while (1) {
		tmp = base_acc;
		base_acc = mlt_buff;
		mlt_buff = tmp;

		if (word == 0ull)
			goto NEXT_WORD;

		buff_cnt = multiply_digits_by_word(mlt_buff,
						   base_acc,
						   acc_cnt,
						   word);

		res_cnt = increment_digits(res_digits,
					   mlt_buff,
					   res_cnt,
					   buff_cnt);
		if (i == count)
			break;
NEXT_WORD:
		word = words[i];
		++i;

		acc_cnt = do_multiply_digits(mlt_buff,
					     base_acc,
					     base,
					     next_pow_two(acc_cnt));
	}

FREE_TMPS_REALLOC_RETURN:

	free(mlt_buff);

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
size_t digits_to_words(word_t **restrict words,
		       const digit_t *restrict digits,
		       const size_t count)
{
	size_t i;

	if (count < DPWB) {
		HANDLE_MALLOC(*words, sizeof(word_t));
		(*words)[0ul] = digits_to_word(digits,
					     count);
		return 1ul;
	}

	const size_t half_count = count / 2ul;

	if (half_count < DPWB) {

		digit_t *rem_digits;
		HANDLE_MALLOC(rem_digits, sizeof(digit_t) * DPWB);
		HANDLE_MALLOC(*words,	  sizeof(word_t) * 2ul);

		const size_t rem_cnt = word_div_rem(rem_digits,
						    &(*words)[1ul],
						    digits,
						    &WORD_BASE_DIGITS[0ul],
						    count,
						    DPWB);

		(*words)[0ul] = digits_to_word(rem_digits,
					     rem_cnt);

		free(rem_digits);


	}

	/* generate string of digit_t arrays representing
	 * word "bits" > (word base)¹
	 *
	 * {(word base)², (word base)³, ..., (word base)ⁿ}
	 *
	 * where 'half_count <= count((word base)ⁿ) < count'
	 */

	const size_t res_alloc = (count / DPWB) + 1ul;

	word_t *res_words;

	HANDLE_MALLOC(res_words,  sizeof(word_t) * res_alloc);

	const size_t buff_alloc = next_pow_two(half_count);




	/* const size_t size_zeros = (buff_alloc - DPWB) * sizeof(digit_t); */

	/* size_t *bit_counts; */
	/* digit_t *base; */
	/* digit_t *base_acc; */
	/* digit_t *mlt_buff; */
	/* digit_t *bit_digits; */
	/* digit_t *tmp; */

	/* size_t acc_cnt = DPWB; */

	/* HANDLE_MALLOC(bit_counts, sizeof(size_t) * res_alloc); */

	/* HANDLE_MALLOC(base, sizeof(digit_t) * buff_alloc * 4ul); */

	/* base_acc   = &base[buff_alloc]; */
	/* mlt_buff   = &base_acc[buff_alloc]; */
	/* bit_digits = &mlt_buff[buff_alloc]; */

	/* bit_digits[0ul] = WORD_BASE_DIGITS; */
	/* bit_digits[1ul] = WORD_BASE_DIGITS; */

	/* set_zero_padded_word_base(base, */
	/* 			  size_zeros); */

	/* set_zero_padded_word_base(base_acc, */
	/* 			  size_zeros); */

	/* acc_cnt = do_multiply_digits(mlt_buff, */
	/* 			     base_acc, */
	/* 			     base, */
	/* 			     NEXT_POW_TWO_DPWB); */



	return 42ul;

}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define PUT_MULT(i)							\
do {									\
	mult_map[i].digits = &mult_map[i - 1ul].digits[buff_cnt];	\
	mult_map[i].count  = add_digits(mult_map[i].digits,		\
					mult_map[i - 1ul].digits,	\
					digits,				\
					mult_map[i - 1ul].count,	\
					count);				\
	mult_map[i].digits[mult_map[i].count] = 0u;			\
} while (0)
struct DCell *digits_mult_map(const digit_t *restrict digits,
			      const size_t count)
{
	const size_t buff_cnt  = count + 2ul;
	const size_t buff_size = sizeof(digit_t) * buff_cnt;

	struct DCell *mult_map;

	HANDLE_MALLOC(mult_map,  sizeof(struct DCell) * 10ul);
	HANDLE_MALLOC(mult_map[0ul].digits, buff_size * 10ul);

	/* TODO: may not need sentinel zero mult or so much zero-padding */
	memset(mult_map[0ul].digits,
	       0,
	       buff_size);
	mult_map[0ul].count = 1ul;

	mult_map[1ul].digits = &mult_map[0ul].digits[buff_cnt];
	mult_map[1ul].count  = count;
	memcpy(mult_map[1ul].digits,
	       digits,
	       buff_size - (2 * sizeof(digit_t)));
	mult_map[1ul].digits[count] = 0u;

	mult_map[2ul].digits = &mult_map[1ul].digits[buff_cnt];
	mult_map[2ul].count  = add_digits(mult_map[2ul].digits,
					  digits,
					  digits,
					  count,
					  count);
	mult_map[2ul].digits[mult_map[2ul].count] = 0u;

	PUT_MULT(3ul); PUT_MULT(4ul); PUT_MULT(5ul); PUT_MULT(6ul);
	PUT_MULT(7ul); PUT_MULT(8ul); PUT_MULT(9ul);

	return mult_map;
}
#undef PUT_MULT

/*
 * long division:
 *
 * given digit_t arrays 'dvd' (dividend) and 'quo' (quotient), calculates 'div'
 * (divisor) and 'rem' (remainder) s.t.
 *
 * quo * div + rem = dvd
 *
 * sets 'rem' and 'div' and returns count(rem);
 *
 * input conditions:
 *	1. quo <= dvd <= quo * WORD_MAX
 *	2. sizeof(rem) >= sizeof(dvd)
 */
size_t word_div_rem(digit_t *restrict rem,
		    word_t *restrict div,
		    const digit_t *restrict dvd,
		    const digit_t *restrict quo,
		    const size_t dvd_cnt,
		    const size_t quo_cnt)
{
	memcpy(rem,
	       dvd,
	       sizeof(digit_t) * dvd_cnt + 1ul);

	rem[dvd_cnt] = 0u;

	struct DCell *mult_map = digits_mult_map(quo,
						 quo_cnt);

	const size_t qc_minus_one = quo_cnt - 1ul;
	const size_t qc_plus_one  = quo_cnt + 1ul;

	const digit_t quo_lead = quo[qc_minus_one];

	size_t i = dvd_cnt - quo_cnt;
	word_t word_acc = 0ull;
	word_t word_mag;
	digit_t div_digit;
	digit_t rem_lead;
	size_t rem_cnt;
	size_t j;


	while (1) {

		rem_lead = rem[i + qc_minus_one];

		if (quo_lead > rem_lead) {
			rem_cnt   = qc_plus_one;
			div_digit = rem_lead * 10u / quo_lead;
			--i;

		} else {
			rem_cnt   = quo_cnt;
			div_digit = rem_lead / quo_lead;
		}

		rem_cnt = dec_rem_by_mult(&rem[i],
					  &div_digit,
					  mult_map,
					  rem_cnt);

	}

}

/*
 * decrements 'digits1' by 'digits2' and returns count
 *
 * input conditions:
 * digits2 <= digits1
 */
size_t decrement_digits(digit_t *restrict digits1,
			const digit_t *restrict digits2,
			const size_t count1,
			const size_t count2)
{
}

/* TODO: clean up lots of unneccessary steps, redundancy */
/* 'rem' and 'mult' have zero-padded upper digits */
size_t dec_rem_by_mult(digit_t *restrict rem,
		       digit_t *div,
		       struct DCell *mult_map,
		       size_t rem_cnt)
{
	size_t mult_cnt = mult_map[*div].count;

	if (mult_cnt > rem_cnt) {
		--(*div);
		mult_cnt = mult_map[*div].count;
	}

	digit_t *mult = mult_map[*div].digits;

	bool carry;

	digit_t buffer = NINES_COMP[rem[0ul]] + mult[0ul];

	size_t i;

	if (buffer > 9u) {
		rem[0ul] = NINES_COMP[buffer - 10u];
		carry	 = true;
	} else {
		rem[0ul] = NINES_COMP[buffer];
		carry	 = false;
	}

	for (i = 1ul; i < mult_cnt; ++i) {
		buffer = NINES_COMP[rem[i]] + mult[i];

		if (carry) {

			if (buffer > 8u) {
				rem[i] = NINES_COMP[buffer - 9u];

			} else {
				rem[i] = NINES_COMP[buffer + 1u];
				carry  = false;
			}

		} else if (buffer > 9u) {

			rem[i] = NINES_COMP[buffer - 10u];
			carry  = true;
		}
	}

	/* when 'mult' has 1 less digit than remainder 'rem' */
	if (i < rem_cnt && carry) {
		--rem[i];
	}


	while (1) {
		if (i == 1u) {
			rem_cnt = 1u;
			break;
		}

		--i;

		if (rem[i] > 0u) {
			rem_cnt = i + 1u;
			break;
		}
	}

	if (carry) {
		digit_t result[rem_cnt];

		rem_cnt = sub
	}

	return rem_cnt;
}

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
			  const digit_t *restrict digits1,
			  const digit_t *restrict digits2,
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
		      const digit_t *restrict lower,
		      const digit_t *restrict upper,
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
		     const digit_t *restrict digits1,
		     const digit_t *restrict digits2,
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
		       const digit_t *restrict digits1,
		       const digit_t *restrict digits2,
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
		  const digit_t *restrict digits1,
		  const digit_t *restrict digits2,
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
 * increments 'digits1' by 'digits2' and returns count
 *
 * input conditions:
 * count2 >= count1
 */
size_t increment_digits(digit_t *restrict digits1,
			const digit_t *restrict digits2,
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
 *
 * input conditions:
 *	1. word > 0
 */
size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       const digit_t *restrict digits,
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

/*
 * sets 'res_digits' to the product of 'digits' and 'digit' and returns count
 *
 * input conditions:
 *	1. digit > 0
 *	2. sizeof(res_digits) > sizeof(digits)
 */
size_t multiply_digits_by_digit(digit_t *restrict res_digits,
			       const digit_t *restrict digits,
			       const size_t count,
			       digit_t digit)
{

	digit_t buffer = digits[0ul] * digit;

	res_digits[0ul] = buffer % 10u;
	res_digits[1ul] = buffer / 10u;

	size_t i = 1ul;

	while (i < count) {
		buffer = digits[i] * digit;
		res_digits[i] += buffer % 10u;
		++i;
		res_digits[i]  = buffer / 10u;
	}

	return (buffer > 9u) ? (i + 1lu) : i;
}


inline void set_zero_padded_word_base(digit_t *restrict base,
				      const size_t pad_size)
{
	memcpy(base,
	       &WORD_BASE_DIGITS[0ul],
	       sizeof(digit_t) * DPWB);

	memset(&base[DPWB],
	       0,
	       pad_size);
}


inline size_t word_to_digits(digit_t *restrict digits,
			     word_t word)
{
	size_t i = 0ul;

	do {
		digits[i] = (digit_t) (word % 10ull);
		word /= 10ull;
		++i;
	} while (word > 0u);

	return i;
}

inline word_t digits_to_word(const digit_t *restrict digits,
			     const size_t count)
{
	word_t word     = (word_t) digits[0ul];
	word_t word_acc = 10ull;

	for (size_t i = 1ul; i < count; ++i) {
		word     += (((word_t) digits[i]) * word_acc);
		word_acc *= 10ull;
	}

	return word;
}

inline void free_digits_mult_map(struct DCell *mult_map)
{
	free(mult_map[0ul].digits);
	free(mult_map);
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
