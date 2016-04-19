#include <stdio.h>
#include <limits.h>
#include "big_int.h"
#include "big_int/digits.h"

int main(void)
{
	const digit_t small[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
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
				       20ul);

	for (ptrdiff_t i = count - 1l; i > -1l; --i)
		printf("words[%zu]: %llu \n", i, words[i]);


	count = words_to_digits(&digits,
				words,
				count);


	PUT_DIGITS("digits", digits, count);

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
