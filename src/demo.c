#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *max1 = init_big_int(LONG_MAX);
	struct BigInt *max2 = init_big_int(LONG_MAX);
	struct BigInt *res1 = init_big_int(LONG_MAX);
	struct BigInt *res2 = init_big_int(LONG_MAX);
	struct BigInt *res3 = init_big_int(LONG_MAX);
	struct BigInt *res4 = init_big_int(LONG_MAX);
	struct BigInt *res5 = init_big_int(LONG_MAX);

	add_big_ints(res1, max1, max2);
	add_big_ints(res2, max1, max2);
	add_big_ints(res3, res1, res2);
	add_big_ints(res4, res1, res2);
	add_big_ints(res5, res3, res4);


	printf("WORD_MAX:    %llu\n", WORD_MAX);
	printf("lmax:        %s\n", big_int_to_string(max1));
	printf("lmax + lmax: %s\n", big_int_to_string(res1));
	printf("lmax * 4:    %s\n", big_int_to_string(res3));
	printf("lmax * 8:    %s\n", big_int_to_string(res5));

	/* word_t words[] = {0ull, 1ull, 0ull, 1ull}; */
	/* digit_t *digits; */
	/* words_to_digits(&digits, &words[0ull], 4ul); */

	return 0;
}
