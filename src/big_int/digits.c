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
						      words[0l]);

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
					words[0l]);

	digit_t *mlt_buff;

	HANDLE_MALLOC(mlt_buff,	  buff_size * 3ul);

	size_t buff_cnt = multiply_digits_by_word(mlt_buff,
						  &WORD_BASE_DIGITS[0l],
						  DPWB,
						  words[1l]);

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

	ptrdiff_t i = 3l;
	word_t word = words[2l];

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
	/* ptrdiff_t i; */

	if (count < DPWB) {
		HANDLE_MALLOC(*words, sizeof(word_t));
		(*words)[0l] = digits_to_word(digits,
					      count);
		return 1ul;
	}

	const size_t half_count = count / 2ul;

	if (half_count < DPWB) {

		digit_t *rem_digits;
		HANDLE_MALLOC(rem_digits, sizeof(digit_t) * DPWB);
		HANDLE_MALLOC(*words,	  sizeof(word_t)  * 2ul);

		const size_t rem_cnt = word_div_rem(rem_digits,
						    &(*words)[1l],
						    digits,
						    &WORD_BASE_DIGITS[0l],
						    count,
						    DPWB);

		(*words)[0l] = digits_to_word(rem_digits,
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

/* 	const size_t res_alloc = (count / DPWB) + 1ul; */

/* 	word_t *res_words; */

/* 	HANDLE_MALLOC(res_words,  sizeof(word_t) * res_alloc); */

/* 	const size_t buff_alloc = next_pow_two(half_count); */




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

	/* bit_digits[0l] = WORD_BASE_DIGITS; */
	/* bit_digits[1l] = WORD_BASE_DIGITS; */

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



/*
 * Hard-wired helper for 'word_div_rem'.
 *
 * Builds a structure housing the first 9 multiples of a multi-digit
 * integer, 'base', designed for convienient lookup according to:
 *
 *	1. count
 *	2. lead digit
 *	3. second digit
 *
 * For instance, input parameters
 *
 *	digits = {9, 9, 1}, count =  3
 *
 * representing the integer '199' would yield 9 'MultNodes' according to the
 * products:
 *			mult	digits		count
 *	199	→	1	{9, 9, 1}	3
 *	398  	→	2	{8, 9, 3}	3
 *	597  	→	3	{7, 9, 5}	3
 *	796  	→	4	{6, 9, 7}	3
 *	995  	→	5	{5, 9, 9}	3
 *	1194 	→	6	{4, 9, 1, 1}	4
 *	1394 	→	7	{4, 9, 3, 1}	4
 *	1592 	→	8	{2, 9, 5, 1}	4
 *	1791 	→	9	{1, 9, 7, 1}	4
 *
 *
 */
#define SET_NODE(MULT)							\
do {									\
	++node;								\
	prev  = next;							\
	next += buff_cnt;						\
	mlt_cnt = add_digits(next, prev, base, mlt_cnt, count);		\
	node->mult    = MULT;						\
	node->digits  = next;						\
	node->count   = mlt_cnt;					\
	next[mlt_cnt] = 0u;						\
	key = keys[mlt_cnt & 1];					\
	map[ key.i ][ next[key.j] ][ next[key.k] ] = node;		\
} while (0)
struct MultMap *build_mult_map(const digit_t *restrict base,
			       const size_t count)
{

	const size_t buff_cnt  = count + 2ul;
	const size_t buff_size = sizeof(digit_t) * buff_cnt;

	struct MultMap *mult_map;
	struct MultMapKey key;
	struct MultMapKey *keys;
	struct MultNode ****map;
	struct MultNode ***leads;
	struct MultNode ***bound_ptr;
	struct MultNode **seconds;
	struct MultNode **start_ptr;
	struct MultNode *node;
	struct MultNode *base_node;
	digit_t *prev;
	digit_t *next;
	size_t mlt_cnt;

	HANDLE_MALLOC(mult_map, sizeof(struct MultMap));
	HANDLE_MALLOC(map,	sizeof(struct MultNode ***) * 2ul);
	HANDLE_MALLOC(leads,    sizeof(struct MultNode **)  * 20ul);
	HANDLE_CALLOC(seconds,  200ul, sizeof(struct MultNode *));
	HANDLE_MALLOC(node,     sizeof(struct MultNode)     * 9ul);
	HANDLE_MALLOC(next,     buff_size		    * 9ul);

	mult_map->map     = map;
	mult_map->leads	  = leads;
	mult_map->seconds = seconds;
	mult_map->nodes   = node;
	mult_map->digits  = next;

	/* cache key indices for multiples having 'count' (less) and 'count + 1'
	 * (more) digits */
	const ptrdiff_t cnt_m1 = count - 1l;
	const ptrdiff_t cnt_m2 = count - 2l;

	struct MultMapKey less_key = {
		.i = 0l,
		.j = cnt_m1,
		.k = cnt_m2
	};

	struct MultMapKey more_key = {
		.i = 1l,
		.j = count,
		.k = cnt_m1
	};

	keys = &mult_map->keys[0l];

	keys[count  & 1] = less_key;
	keys[cnt_m1 & 1] = more_key;

	/* hook up block and boundary pointers to imitate a 2 × 10 × 10 (3d) array */
	base_node = node;
	start_ptr = seconds;
	bound_ptr = leads + 10l;
	map[0l] = leads;
	map[1l] = bound_ptr;
	bound_ptr += 10l;

	while (1) {
		*leads = seconds;
		++leads;
		if (leads == bound_ptr) {
			seconds += 9l; /* set to last valid pointer */
			break;	       /* (i.e. '&start_ptr[199]') */
		}
		seconds += 10l;	/* advance to next valid 10-node block */
	}


	/* starting with multiple of 1...
	 * ================================================================== */
	/* copy base into digits buffer 'next' */
	memcpy(next, base, buff_size - (2ul * sizeof(digit_t)));

	/* set fields */
	node->mult   = 1u;
	node->digits = next;
	node->count  = count;
	next[count]  = 0u; /* provide one zero pad above lead digit (for
			      convenient nine's compliment subtraction) */

	/* set base node according to its count, lead digit, and second digit */
	map[ 0l ][ next[cnt_m1] ][ next[cnt_m2] ] = node;


	/* multiple of 2...
	 * ================================================================== */

	/* advance buffer pointers */
	++node;
	next += buff_cnt;

	/* calculate base * 2 */
	mlt_cnt = add_digits(next, base, base, count, count);

	/* set fields */
	node->mult    = 2u;
	node->digits  = next;
	node->count   = mlt_cnt;
	next[mlt_cnt] = 0u; /* pad lead */

	/* set node */
	key = keys[mlt_cnt & 1];
	map[ key.i ][ next[key.j] ][ next[key.k] ] = node;


	/* remaining multiples...
	 * ================================================================== */
	SET_NODE(3u); SET_NODE(4u); SET_NODE(5u); SET_NODE(6u);
	SET_NODE(7u); SET_NODE(8u); SET_NODE(9u);

	/* printf("node:	   %p\n", node); */
	/* printf("base_node: %p\n", base_node); */
	/* printf("diff:	   %ld\n", node - base_node); */
	/* printf("seconds:   %p\n", seconds); */
	/* printf("start_ptr: %p\n", start_ptr); */
	/* printf("diff:	   %ld\n", seconds - start_ptr); */
	/* printf("*seconds:  %p\n", *seconds); */
	/* fflush(stdout); */

	/* starting from the last slot in the node buffer 'seconds', set unset
	 * pointers greater than base node to the immediate previous valid node
	 * so as to "round down" accesses to a "floor multiple"...
	 * ================================================================== */
	do {
		while (*seconds == NULL) {
			/* printf("seconds:   %p\n", seconds); */
			/* fflush(stdout); */
			*seconds = node;
			--seconds;
		}

		printf("node->mult:  %u\n", node->mult);
		printf("node->count: %zu\n\n", node->count);
		for (ptrdiff_t i = node->count - 1l; i > -1l; --i)
			printf("%u", node->digits[i]);
		printf("\nsecs->mult:  %u\n", (*seconds)->mult);
		printf("secs->count: %zu\n\n\n", (*seconds)->count);
		for (ptrdiff_t i = (*seconds)->count - 1l; i > -1l; --i)
			printf("%u", (*seconds)->digits[i]);
		puts("\n******");
		fflush(stdout);
		sleep(1);


		--node;

	} while (node > base_node);

	puts("DONE");

	/* /1* set pointers below base node to NULL to signal a base multiple of '0' */
	/*  * ================================================================== *1/ */
	/* while (seconds > start_ptr) { */
	/* 	*seconds = NULL; */
	/* 	--seconds; */
	/* } */

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
	/* memcpy(rem, */
	/*        dvd, */
	/*        sizeof(digit_t) * dvd_cnt + 1ul); */

	/* rem[dvd_cnt] = 0u; */

	/* struct MultMap *mult_map = build_mult_map(quo, */
	/* 					  quo_cnt); */

	/* const size_t qc_minus_one = quo_cnt - 1ul; */
	/* const size_t qc_plus_one  = quo_cnt + 1ul; */

	/* const digit_t quo_lead = quo[qc_minus_one]; */

	/* ptrdiff_t i = dvd_cnt - quo_cnt; */
	/* word_t word_acc = 0ull; */
	/* word_t word_mag; */
	/* digit_t div_digit; */
	/* digit_t rem_lead; */
	/* size_t rem_cnt; */
	/* size_t j; */


	/* while (1) { */

	/* 	rem_lead = rem[i + qc_minus_one]; */

	/* 	if (quo_lead > rem_lead) { */
	/* 		rem_cnt   = qc_plus_one; */
	/* 		div_digit = rem_lead * 10u / quo_lead; */
	/* 		--i; */

	/* 	} else { */
	/* 		rem_cnt   = quo_cnt; */
	/* 		div_digit = rem_lead / quo_lead; */
	/* 	} */




	/* 	size_t mlt_cnt = mult_map[div_digit].count; */

	/* 	if (mlt_cnt > rem_cnt) { */
	/* 		--div_digit; */
	/* 		mlt_cnt = mult_map[div_digit].count; */
	/* 	} */



	/* } */

	return 42ul;
}

/*
 * decrements 'rem' by 'mult' and returns carry
 *
 * input conditions:
 *
 * 1. mult's count <= count == rem's count
 * 2. 'rem' and 'mult' have zero-padded upper digits */

bool decrement_remainder(digit_t *restrict rem,
			 const digit_t *restrict mult,
			 const size_t count)
{

	bool carry;
	digit_t buffer = NINES_COMP[rem[0l]] + mult[0l];
	ptrdiff_t i;

	if (buffer > 9u) {
		rem[0l] = NINES_COMP[buffer - 10u];
		carry	 = true;
	} else {
		rem[0l] = NINES_COMP[buffer];
		carry	 = false;
	}

	for (i = 1l; i < count; ++i) {
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

	return carry;
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
		res_digits[0l] = digits1[0l] * digits2[0l];

		if (res_digits[0l] < 10u)
			return 1ul;

		res_digits[1l] = res_digits[0l] / 10u;
		res_digits[0l] %= 10u;
		return 2ul;
	}

	const size_t buff_alloc = count * 2;
	const size_t half_count = count / 2ul;

	const digit_t *upper1 = &digits1[half_count];
	const digit_t *upper2 = &digits2[half_count];

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
		const size_t half_plus_one   = half_count + 1l;
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

	res_digits[0l] = upper[0l] + lower[0l];

	if (res_digits[0l] > 9u) {
		res_digits[0l] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (ptrdiff_t i = 1l; i < count; ++i) {
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
	if ((count1 == 1ul) && (digits1[0l] == 0u)) {
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
	ptrdiff_t i;

	large = digits1[0l];
	small = digits2[0l];

	if (small > large) {
		res_digits[0l] = (10u + large) - small;
		carry = true;
	} else {
		res_digits[0l] = large - small;
		carry = false;
	}

	for (i = 1l; i < count2; ++i) {

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
	ptrdiff_t i;

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
	ptrdiff_t i;

	digits1[0l] += digits2[0l];

	if (digits1[0l] > 9u) {
		digits1[0l] -= 10u;
		carry = true;
	} else {
		carry = false;
	}

	for (i = 1l; i < count1; ++i) {
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
				digits1[count2] = 1u;
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
	buff_t buffer = buff_word * ((buff_t) digits[0l]);

	res_digits[0l] = (digit_t) (buffer % BUFF_TEN);
	buffer /= BUFF_TEN;

	ptrdiff_t i = 1l;

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

	digit_t buffer = digits[0l] * digit;

	res_digits[0l] = buffer % 10u;
	res_digits[1l] = buffer / 10u;

	ptrdiff_t i = 1l;

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
	       &WORD_BASE_DIGITS[0l],
	       sizeof(digit_t) * DPWB);

	memset(&base[DPWB],
	       0,
	       pad_size);
}


inline size_t word_to_digits(digit_t *restrict digits,
			     word_t word)
{
	ptrdiff_t i = 0l;

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
	word_t word     = (word_t) digits[0l];
	word_t word_acc = 10ull;

	for (ptrdiff_t i = 1l; i < count; ++i) {
		word     += (((word_t) digits[i]) * word_acc);
		word_acc *= 10ull;
	}

	return word;
}

/* static inline struct MultNode *closest_multiple(struct MultMap *restrict mult_map, */
/* 						const digit_t *restrict digits, */
/* 						const size_t count) */
struct MultNode *closest_multiple(struct MultMap *restrict mult_map,
				  const digit_t *restrict digits,
				  const size_t count)
{
	struct MultMapKey key = mult_map->keys[count & 1];

	printf("key.i: %zu\n", key.i);
	printf("key.j: %zu\n", key.j);
	printf("key.k: %zu\n", key.k);
	fflush(stdout);

	return mult_map->map[ key.i ][ digits[key.j] ][ digits[ key.k ] ];
}


inline void free_mult_map(struct MultMap *mult_map)
{
	free(mult_map->map);
	free(mult_map->leads);
	free(mult_map->seconds);
	free(mult_map->nodes);
	free(mult_map->digits);
	free(mult_map);
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
