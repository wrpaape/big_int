#include "big_int_string.h"

/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define CHARS_PER_DIGIT 20lu

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			big_int_to_string(1)				*
 *									*
 * Returns the decimal representation of the integer value of 'big_int'	*
 * as a NULL-terminated ASCII string of digits.				*
 ************************************************************************/
char *big_int_to_string(struct BigInt *big_int)
{
	/* char *dig_str = malloc(sizeof(char) * ((big_int->num_words * CHARS_PER_DIGIT) + 2lu)); */

	char *dig_str;

	HANDLE_MALLOC(dig_str,
		      (sizeof(char) * (big_int->num_words * CHARS_PER_DIGIT))
		      + 2lu);

	char *dig_char = dig_str;

	unsigned long long int *digit = big_int->words;

	if (big_int->sign == NEG) {
		*dig_char = '-';
		++dig_char;
	}

	sprintf(dig_char, "%llu", *digit);

	return dig_str;
}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
