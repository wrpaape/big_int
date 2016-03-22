#include "big_int.h"
#include "string_io.h"

#define CHARS_PER_DIGIT 20

char *big_int_to_string(struct BigInt *big_int)
{
	char *dig_str = malloc(sizeof(char) *
			       ((big_int->num_words *
				 CHARS_PER_DIGIT) + 2lu));

	char *dig_char = dig_str;

	unsigned long long int *digit = big_int->words;

	if (big_int->sign == NEG) {
		*dig_char = '-';
		++dig_char;
	}

	sprintf(dig_char, "%llu", *digit);

	return dig_str;
}
