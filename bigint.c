#include <stdio.h>
#include "big_int.h"
#include "big_int_memory.h"
#include "big_int_string.h"


int main(void)
{
	struct BigInt *big_int = init_big_int(-1031);

	printf("to_s: %s\n", big_int_to_s(big_int));

	return 0;
}




char *big_int_to_s(struct BigInt *big_int)
{
	char *dig_str = handle_malloc(sizeof(char) *
				      ((big_int->size * CHARS_PER_DIGIT)
				       + 2lu));

	char *dig_char = dig_str;

	unsigned int *digit = big_int->digits;

	if (big_int->sign == MINUS) {
		*dig_char = '-';
		++dig_char;
	}

	sprintf(dig_char, "%u", *digit);

	return dig_str;
}

#undef CHARS_PER_DIGIT
