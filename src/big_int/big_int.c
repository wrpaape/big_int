#include <stdio.h>
#include "big_int/big_int.h"


int main(void)
{
	struct BigInt *big_int = init_big_int(-1031);

	printf("to_s: %s\n", big_int_to_s(big_int));

	return 0;
}





