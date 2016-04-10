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
 *			words_to_big_digits(1)				*
 *									*
 * Returns an unsigned base 10 representation of the integer value of	*
 * word_t array 'words'.						*
 ************************************************************************/
struct BigDigits *words_to_big_digits(const size_t word_count,
				      word_t *words)
{
	size_t i;
	word_t word;
	digit_t *digits;

	size_t alloc_count = MAX_DIGITS_PER_WORD;
	size_t alloc_acc   = MAX_DIGITS_PER_WORD * 2;

	for (i = 1lu; i < word_count; ++i) {
		alloc_count += (alloc_acc + 1lu);
		alloc_acc   += MAX_DIGITS_PER_WORD;
	}


	const size_t buff_alloc = next_pow_two(alloc_count);

	struct BigDigits *big = init_zeroed_big_digits(buff_alloc);

	digits = big->digits;
	word = words[0lu];
	i = 0lu;

	do {
		digits[i] = word % 10lu;
		word /= 10lu;
		++i;

	} while (word > 0lu);

	if (word_count == 1lu)
		return big;

	struct BigDigits *base	   = init_zeroed_big_digits(buff_alloc);
	struct BigDigits *base_acc = init_zeroed_big_digits(buff_alloc);
	struct BigDigits *buff1	   = init_zeroed_big_digits(buff_alloc);
	struct BigDigits *buff2	   = init_zeroed_big_digits(buff_alloc);
	struct BigDigits *tmp;

	digit_t *acc_digits;
	digit_t *buff_digits;

	digit_t word_base_digits[] = {
		1u, 8u, 4u, 4u, 6u, 7u, 4u, 4u, 0u, 7u,
		3u, 7u, 0u, 9u, 5u, 5u, 1u, 6u, 1u, 6u
	};

	base->count	= DIGITS_PER_WORD_BASE;

	memcpy(base->digits,
	       word_base_digits,
	       sizeof(digit_t) * DIGITS_PER_WORD_BASE);

	base_acc->count = DIGITS_PER_WORD_BASE;

	memcpy(base_acc->digits,
	       word_base_digits,
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
			free_big_digits(base);
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

	const size_t count_size = sizeof(digit_t) * count;
	const size_t half_count = count / 2lu;

	digit_t *upper1 = digits1 + half_count;
	digit_t *upper2 = digits2 + half_count;

	digit_t *add_res1;
	digit_t *add_res2;
	digit_t *mlt_res1;
	digit_t *mlt_res2;
	digit_t *mlt_res3;
	digit_t *sub_res1;
	digit_t *sub_res2;
	digit_t *app_res;

	size_t max_add_cnt;
	size_t mlt_res1_size;

	HANDLE_MALLOC(add_res1, count_size);
	const bool carry1 = add_split_digits(add_res1,
					     digits1,
					     upper1,
					     half_count);

	HANDLE_MALLOC(add_res2, count_size);
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
		mlt_res1_size = count_size * 2lu;


	} else if (carry2) {
		const size_t half_plus_one   = half_count + 1lu;
		const size_t rem_digits_size = sizeof(digit_t)
					     * (half_count - 1lu);
		add_res2[half_count] = 1u;
		memset(&add_res2[half_plus_one], 0, rem_digits_size);

		memset(&add_res1[half_count], 0,
		       rem_digits_size + sizeof(digit_t));

		max_add_cnt   = count;
		mlt_res1_size = count_size * 2lu;

	} else {
		max_add_cnt   = half_count;
		mlt_res1_size = count_size;
	}


	HANDLE_MALLOC(mlt_res1, mlt_res1_size);
	const size_t mlt_cnt1 = do_multiply_digits(mlt_res1,
						   add_res1,
						   add_res2,
						   max_add_cnt);

	HANDLE_MALLOC(mlt_res2, count_size);
	const size_t mlt_cnt2 = do_multiply_digits(mlt_res2,
						   upper1,
						   upper2,
						   half_count);

	HANDLE_MALLOC(mlt_res3, count_size);
	const size_t mlt_cnt3 = do_multiply_digits(mlt_res3,
						   digits1,
						   digits2,
						   half_count);


	HANDLE_MALLOC(sub_res1, count_size);
	const size_t sub_cnt1 = subtract_digits(sub_res1,
						mlt_res1,
						mlt_res2,
						mlt_cnt1,
						mlt_cnt2);


	HANDLE_MALLOC(sub_res2, sizeof(digit_t) * mlt_cnt1);
	const size_t sub_cnt2 = subtract_digits(sub_res2,
						sub_res1,
						mlt_res3,
						sub_cnt1,
						mlt_cnt3);


	HANDLE_MALLOC(app_res, sizeof(digit_t) * (sub_cnt2 + half_count + 1lu));
	const size_t app_cnt = add_poly_pair(app_res,
					     sub_res2,
					     mlt_res3,
					     sub_cnt2,
					     mlt_cnt3,
					     half_count);


	const size_t res_cnt = add_poly_pair(res_digits,
					     mlt_res2,
					     app_res,
					     mlt_cnt2,
					     app_cnt,
					     count);
	free(add_res1);
	free(add_res2);
	free(mlt_res1);
	free(mlt_res2);
	free(mlt_res3);
	free(sub_res1);
	free(sub_res2);
	free(app_res);

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
	/* fputs("\n\ndigits1: ", stdout); */
	/* for (int i = count1 - 1; i > -1; --i) printf("%u", digits1[i]); */
	/* fputs("\ndigits2: ", stdout); */
	/* for (int i = count2 - 1; i > -1; --i) printf("%u", digits2[i]); */
	/* printf("\nn:      %zu\n\n", n); */

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

		if (rem_cnt2 > count1) {

			return n + add_digits(&res_digits[n],
					      &digits2[n],
					      digits1,
					      rem_cnt2,
					      count1);

		}

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
 * sets 'res_digits' to 'digits1 - digits2 * 10ⁿ' and returns count
 *
 * input conditions:
 *	1. digits1 >= digits2 * 10ⁿ
 */
size_t subtract_poly_pair(digit_t *restrict res_digits,
			  digit_t *restrict digits1,
			  digit_t *restrict digits2,
			  const size_t count1,
			  const size_t count2,
			  const size_t n)
{

	/* copy lower digits of 'digits1' unaffected by shift */
	memcpy(res_digits,
	       digits1,
	       sizeof(digit_t) * n);


	/* shift by 'n' */
	return n + subtract_digits(&res_digits[n],
				   &digits1[n],
				   digits2,
				   count1 - n,
				   count2);
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
		buffer += ((buff_t) word * ((buff_t) big_digits[i]));
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

inline struct BigDigits *init_zeroed_big_digits(const size_t count)
{
	struct BigDigits *big;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_CALLOC(big->digits, sizeof(digit_t), count);

	return big;
}

inline bool digits_equal_p(digit_t *restrict digits1,
			   digit_t *restrict digits2,
			   const size_t count1,
			   const size_t count2)
{

	if (count2 != count1)
		return false;

	size_t i = count1 - 1lu;

	while (1) {
		if (digits1[i] != digits2[i])
			return false;

		if (i == 0lu)
			return true;

		--i;
	}
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
