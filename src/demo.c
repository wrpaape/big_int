#include <stdio.h>
#include <limits.h>
#include "big_int.h"

int main(void)
{
	struct BigInt *lmax = init_big_int(LONG_MAX);
	struct BigInt *res1 = init_big_int(0);
	struct BigInt *res2 = init_big_int(0);

	add_big_ints(res1, lmax, lmax);
	add_big_ints(res2, res1, res1);


	printf("WORD_MAX:    %llu\n", WORD_MAX);
	printf("lmax:        %s\n", big_int_to_string(lmax));
	printf("lmax + lmax: %s\n", big_int_to_string(res1));
	printf("lmax * 4:    %s\n", big_int_to_string(res2));

	return 0;
}
