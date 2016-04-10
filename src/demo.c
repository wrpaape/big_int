#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	digit_t res_digits[1024] = {0u};
	digit_t digits1[] = {9u, 9u, 9u, 9u};
	digit_t digits2[] = {9u, 9u, 0u, 0u};
	/* digit_t digits1[] = {9u, 8u, 7u, 1u, 1u, 0u, 6u, 4u, */
	/* 		     7u, 8u, 9u, 0u, 0u, 0u, 2u, 0u, */
	/* 		     7u, 8u, 9u, 0u, 0u, 0u, 2u, 0u, */
	/* 		     7u, 8u, 9u, 0u, 0u, 0u, 2u, 0u}; */
	/* digit_t digits2[] = {2u, 9u, 0u, 9u, 3u, 1u, 2u, 0u, */
	/* 		     7u, 3u, 9u, 1u, 0u, 0u, 1u, 0u, */
	/* 		     7u, 3u, 9u, 1u, 0u, 0u, 1u, 0u, */
	/* 		     7u, 3u, 9u, 1u, 0u, 0u, 1u, 0u}; */

	size_t count = do_multiply_digits(&res_digits[0lu],
					  &digits1[0lu],
					  &digits2[0lu],
					  4);

	char buff[count + 1lu];

	buff[count] = '\0';

	size_t i = 0lu;

	size_t last = count - 1lu;

	while (1) {
		buff[i] = res_digits[last - i] + '0';
		printf("%u\n", res_digits[last - i]);

		if (i == last)
			break;
		++i;
	}

	puts(buff);

	/* struct BigInt *big1 = init_big_int(LONG_MAX); */
	/* struct BigInt *big2 = init_big_int(LONG_MAX); */
	/* struct BigInt *res1 = init_big_int(0); */
	/* struct BigInt *res2 = init_big_int(0); */

	/* add_big_ints(res1, big1, big2); */
	/* add_big_ints(res2, res1, big1); */


	/* printf("WORD_MAX: %llu\n", WORD_MAX); */
	/* printf("LONG_MAX: %ld\n", LONG_MAX); */
	/* printf("big1:     %s\n", big_int_to_string(big1)); */
	/* printf("big2:     %s\n", big_int_to_string(big2)); */
	/* printf("res1:     %s\n", big_int_to_string(res1)); */
	/* printf("res2:     %s\n", big_int_to_string(res2)); */

	return 0;
}
