#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *big1 = init_big_int(INT_MAX);
	struct BigInt *big2 = init_big_int(INT_MAX);
	struct BigInt *big3 = init_big_int(0);

	add_big_ints(big1, big2, big3);


	printf("big1: %s\n", big_int_to_string(big1));
	printf("big2: %s\n", big_int_to_string(big2));
	printf("big3: %s\n", big_int_to_string(big3));

	return 0;
}
