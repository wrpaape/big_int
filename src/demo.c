#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *big1 = init_big_int(LONG_MAX);
	struct BigInt *big2 = init_big_int(LONG_MAX);
	struct BigInt *res1 = init_big_int(0);
	struct BigInt *res2 = init_big_int(0);

	add_big_ints(res1, big1, big2);
	add_big_ints(res2, res1, big1);


	printf("WORD_MAX: %llu\n", WORD_MAX);
	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("big1:     %s\n", big_int_to_string(big1));
	printf("big2:     %s\n", big_int_to_string(big2));
	printf("res1:     %s\n", big_int_to_string(res1));
	printf("res2:     %s\n", big_int_to_string(res2));

	return 0;
}
