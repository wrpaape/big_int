/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int/globals.h"
#include "big_int/string.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define DIGIT_BITS (sizeof(digit_t) * CHAR_BIT)
#define MAX_DEC_DIGITS_PER_WORD 20lu

/* static const digit_t BASE_DEC_DIGITS[] = { */
/* 	1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 6 */
/* }; */
/* static const char CHAR_MAP[] = { */
/* 	'0', '1', '2', '3', '4', '5', '6', '7', */
/* 	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F', */
/* }; */

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

/************************************************************************
 *			words_to_big_digits(1)				*
 *									*
 * Returns an unsigned base 10 representation of the integer value of	*
 * word_t array 'words'.						*
 ************************************************************************/
struct BigDigits *words_to_big_digits(const size_t word_count,
				      word_t *words)
{
	struct BigDigits *big;
	word_t first_word;
	word_t i;
	size_t j;
	word_t n;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_MALLOC(big->digits,
		      sizeof(digit_t) * MAX_DEC_DIGITS_PER_WORD * word_count);

	big->digits[0lu] = 0u;
	big->count	 = 1lu;

	for (first_word = words[0lu]; first_word > 0lu; first_word /= 10lu) {

		add_word_to_big_digits(big,
					(digit_t) (first_word % 10lu));
	}



	for (n = 1lu; n < word_count; ++n) {

		for (i = words[n] * ((word_t) n); i > 0llu; --i) {

			for (j = 0lu; j < MAX_DEC_DIGITS_PER_WORD; ++j) {

				add_word_to_big_digits(big,
							BASE_DEC_DIGITS[j]);
			}
		}
	}

	return big;
}
/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
inline word_t add_digits(digit_t digit1,
			 digit_t digit2)
{
	return ((word_t) digit1) + ((word_t) digit2);
}

inline word_t add_digit_to_word(word_t word,
				digit_t digit)
{
	return word + ((word_t) digit);
}

inline digit_t upper_digit(word_t word)
{
	return (digit_t) (word >> DIGIT_BITS);
}

inline digit_t lower_digit(word_t word)
{
	return (digit_t) word;
}

inline void add_word_to_big_digits(struct BigDigits *big,
				   word_t word)

inline void add_word_to_big_digits(struct BigDigits *big,
				   word_t word)
{
	digit_t *digits = big->digits;
	size_t count	= big->count;

	word_t sum_buffer = add_digits(lower_digit(word),
				       digits[0lu])
	digit_t carry;
	size_t i = 0lu;


	while (1) {
	}

}

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


static inline void free_big_digits(struct BigDigits *big)
{
	free(big->digits);
	free(big);
}
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
