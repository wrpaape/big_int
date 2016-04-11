#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	word_t words[] = {WORD_MAX, 0lu, WORD_MAX};

	digit_t *digits;

	const size_t count = words_to_digits(&digits, &words[0lu], 3lu);

	char buff[count + 1lu];

	buff[count] = '\0';

	size_t i = 0lu;

	size_t last = count - 1lu;

	while (1) {
		buff[i] = digits[last - i] + '0';

		if (i == last)
			break;
		++i;
	}

	printf("WORD_MAX: %llu\n", WORD_MAX);
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
