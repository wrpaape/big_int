#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	digit_t res_digits[10] = {0};
	digit_t digits1[] = {9, 9, 9, 0};
	digit_t digits2[] = {9, 9, 0, 0};

	size_t count = do_multiply_digits(&res_digits[0lu],
					  &digits1[0lu],
					  &digits2[0lu],
					  next_pow_two(4));

	char buff[count + 1lu];

	buff[count] = '\0';

	do {
		--count;
		buff[count] = res_digits[count] + '0';

	} while (count > 0lu);

	/* for (int i = count - 1; i > -1; --i) { */
	/* /1* 	printf("digits1[%d]:    %u\n", i, digits1[i]); *1/ */
	/* 	printf("res_digits[%d]: %u\n", i, res_digits[i]); */
	/* } */



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
