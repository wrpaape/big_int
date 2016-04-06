#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *big1   = init_big_int(LONG_MAX - 1);
	struct BigInt *big2   = init_big_int(LONG_MAX);
	struct BigInt *result = init_big_int(0);

	add_big_ints(result, big1, big2);


	printf("LONG_MIN: %ld\n", LONG_MIN);
	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("big1:     %s\n", big_int_to_string(big1));
	printf("big2:     %s\n", big_int_to_string(big2));
	printf("result:   %s\n", big_int_to_string(result));

	return 0;
}
