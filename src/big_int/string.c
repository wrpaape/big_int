/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/string.h"

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

	const size_t MAX_LENGTH = sizeof(char)
				* big->word_count
				* MAX_DEC_DIGITS_PER_WORD
				+ 2lu;

	char *digits;
	char *root;
	word_t *words;
	word_t word;
	size_t i;
	size_t j;

	HANDLE_MALLOC(digits, MAX_LENGTH);

	root = digits;

	if (big->sign == NEG) {
		*root = '-';
		++root;
	}

	i = big->word_count - 1lu;

	words = big->words;
	word  = words[i];

	const size_t sig_word_digits = num_dec_digits(word);

	printf("sig: %zu\n", sig_word_digits);

	root += sig_word_digits;

	j = 1lu;

	while (1) {
		root[-j] = ((char) (word % 10llu)) + '0';

		if (j == sig_word_digits)
			break;

		word /= 10llu;

		++j;
	}



	while (i > 0lu) {
		word  = words[i];

		j = MAX_DEC_DIGITS_PER_WORD - 1lu;

		while (1) {

			root[j] = ((char) (word % 10llu)) + '0';

			if (word < 10llu)
				break;

			word /= 10llu;

			--j;
		}

		memset(root, '0', j);

		root += MAX_DEC_DIGITS_PER_WORD;

		--i;
	}


	*root = '\0';

	return digits;
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