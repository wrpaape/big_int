#include <stdio.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *big_int = init_big_int(-1031ll);

	printf("to_s: %s\n", big_int_to_string(big_int));

	printf("test: %d\n", test_fun());

	return 0;
}