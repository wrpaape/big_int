#include <stdio.h>
#include <limits.h>
#include "big_int.h"
#include "big_int/digits.h"

int main(void)
{
	const digit_t small[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u};

	const digit_t large[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
				 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u};

	word_t *words;
	digit_t *digits;

	size_t count = digits_to_words(&words,
				       &small[0l],
				       40ul);

	for (ptrdiff_t i = count - 1l; i > -1l; --i)
		printf("words[%zd]: %llu \n", i, words[i]);


	count = words_to_digits(&digits,
				words,
				count);



/* dvd_digits: 8354570280438880660901816588598410986 */
/* res_words[1]: 452902162411733219 wrong */
	/*	 452902162411733222 */
	/*	 452902162411733222 */
/* rem_digits: 56427215838696079082 */

/* mlt: 80000000000000000 */
/* rem: 687883075454211653162 */
/* acc: 80000000000000000 */
/* *********** */
/* mlt: 400000000000000000 */
/* rem: 9758726509550600145 */
/* acc: 400000000000000000 */
	digit_t dvd_digits[] = {
		6, 8, 9, 0, 1, 4, 8, 9, 5, 8, 8, 5, 6, 1, 8, 1, 0, 9, 0, 6, 6,
		0, 8, 8, 8, 3, 4, 0, 8, 2, 0, 7, 5, 4, 5, 3, 8, 1
	};

	static const digit_t WORD_BASE_DIGITS[] = {
		6u, 1u, 6u, 1u, 5u, 5u, 9u, 0u, 7u, 3u,
		7u, 0u, 4u, 4u, 7u, 6u, 4u, 4u, 8u, 1u
	};

	word_t word;

	size_t rem_cnt = word_div_rem(&word,
				      &dvd_digits[0l],
				      &WORD_BASE_DIGITS[0l],
				      37ul,
				      20ul);

	/* printf("word: %llu\n", word); */
	/* PUT_DIGITS("rem_digits", dvd_digits, rem_cnt); */


	/* word_t words[] = {0ull, 1ull, 0ull, 1ull}; */
	/* digit_t *digits; */
	/* size_t count = words_to_digits(&digits, &words[0l], 4ul); */

	/* PUT_DIGITS("digits", digits, count); */

	/* struct BigInt *lmax = init_big_int(LONG_MAX); */
	/* struct BigInt *res1 = init_big_int(LONG_MAX); */
	/* struct BigInt *res2 = init_big_int(LONG_MAX); */
	/* struct BigInt *res3 = init_big_int(LONG_MAX); */
	/* struct BigInt *res4 = init_big_int(LONG_MAX); */
	/* struct BigInt *res5 = init_big_int(LONG_MAX); */
	/* struct BigInt *res6 = init_big_int(LONG_MAX); */
	/* struct BigInt *res7 = init_big_int(LONG_MAX); */
	/* struct BigInt *res8 = init_big_int(LONG_MAX); */

	/* add_big_ints(res1, lmax, lmax); */
	/* add_big_ints(res2, res1, res1); */
	/* add_big_ints(res3, res2, res2); */
	/* add_big_ints(res4, res3, res3); */
	/* add_big_ints(res5, res4, res4); */
	/* add_big_ints(res6, res5, res5); */
	/* add_big_ints(res7, res6, res6); */
	/* add_big_ints(res8, res7, res7); */


	/* printf("WORD_MAX:   %llu\n", WORD_MAX); */
	/* printf("lmax:       %s\n", big_int_to_string(lmax)); */
	/* printf("lmax * 2:   %s\n", big_int_to_string(res1)); */
	/* printf("lmax * 4:   %s\n", big_int_to_string(res2)); */
	/* printf("lmax * 8:   %s\n", big_int_to_string(res3)); */
	/* printf("lmax * 16:  %s\n", big_int_to_string(res4)); */
	/* printf("lmax * 32:  %s\n", big_int_to_string(res5)); */
	/* printf("lmax * 64:  %s\n", big_int_to_string(res6)); */
	/* printf("lmax * 128: %s\n", big_int_to_string(res7)); */
	/* printf("lmax * 256: %s\n", big_int_to_string(res8)); */

	return 0;
}
