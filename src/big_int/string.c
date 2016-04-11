/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/string.h"
#include "big_int/digits.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define MAX_DEC_DIGITS_PER_WORD 20lu

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			big_int_to_string(1)				*
 *									*
 * Returns the decimal representation of the integer value of 'big' as	*
 * a NULL-terminated ASCII string of digits.				*
 ************************************************************************/
char *big_int_to_string(struct BigInt *big)
{
	digit_t *digits;
	char *string;
	size_t i;

	const size_t count = words_to_digits(&digits,
					     big->words,
					     big->word_count);


	HANDLE_MALLOC(string, count + 2lu);

	i = 1lu;

	while (1) {

		string[i] = digits[count - i] + '0';

		if (i == count)
			break;
		++i;
	}

	free(digits);

	string[count + 1lu] = '\0';

	if (big->sign == NEG) {
		string[0lu] = '-';
		return string;
	}

	return &string[1lu];
}
/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline size_t num_dec_digits(word_t word)
{
	if (word < 10llu)			return  1lu;
	if (word < 100llu)			return  2lu;
	if (word < 1000llu)			return  3lu;
	if (word < 10000llu)			return  4lu;
	if (word < 100000llu)			return  5lu;
	if (word < 1000000llu)			return  6lu;
	if (word < 10000000llu)			return  7lu;
	if (word < 100000000llu)		return  8lu;
	if (word < 1000000000llu)		return  9lu;
	if (word < 10000000000llu)		return 10lu;
	if (word < 100000000000llu)		return 11lu;
	if (word < 1000000000000llu)		return 12lu;
	if (word < 10000000000000llu)		return 13lu;
	if (word < 100000000000000llu)		return 14lu;
	if (word < 1000000000000000llu)		return 15lu;
	if (word < 10000000000000000llu)	return 16lu;
	if (word < 100000000000000000llu)	return 17lu;
	if (word < 1000000000000000000llu)	return 18lu;
	if (word < 10000000000000000000llu)	return 19lu;

	return MAX_DEC_DIGITS_PER_WORD; /* 20 for 64 bit word */
}

/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
