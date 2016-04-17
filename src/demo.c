#include <stdio.h>
#include <limits.h>
#include "big_int.h"
#include "big_int/digits.h"

int main(void)
{
	const digit_t test_rem[] = {1u, 1u, 1u, 2u, 0u};
	const digit_t test_quo[] = {5u, 5u, 5u, 5u, 0u};

	const digit_t *rem_ptr = test_rem;
	const digit_t *quo_ptr = test_quo;

	struct MultMap *mult_map = build_mult_map(rem_ptr,
						  4ul);

	struct MultNode *node = closest_multiple(mult_map,
						 quo_ptr,
						 4ul);

	printf("node: %p\n", node);
	fflush(stdout);

	printf("node->mult: %u\nnode->count: %zu\nnode->digits: ",
	       node->mult, node->count);


	for (ptrdiff_t i = node->count - 1l; i > -1l; --i)
		printf("%u", node->digits[i]);





	/* word_t words[] = {0ull, 1ull, 0ull, 1ull}; */
	/* digit_t *digits; */
	/* words_to_digits(&digits, &words[0ull], 4ul); */

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


	/* printf("WORD_MAX:  %llu\n", WORD_MAX); */
	/* printf("lmax:      %s\n", big_int_to_string(lmax)); */
	/* printf("lmax * 2:  %s\n", big_int_to_string(res1)); */
	/* printf("lmax * 4:  %s\n", big_int_to_string(res2)); */
	/* printf("lmax * 8:  %s\n", big_int_to_string(res3)); */
	/* printf("lmax * 16: %s\n", big_int_to_string(res4)); */
	/* printf("lmax * 32: %s\n", big_int_to_string(res5)); */

	return 0;
}
