#include <stdio.h>
#include "big_int.h"


int main(void)
{
	struct BigInt *big_int = init_big_int(-1031);

	printf("to_s: %s\n", big_int_to_s(big_int));

	return 0;
}


struct BigInt *init_big_int(long long int init_val)
{
	/* allocate BigInt struct
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	struct BigInt *big_int = malloc(sizeof(struct BigInt));

	if (big_int == NULL) return NULL;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	 *
	 * allocate 2 words for storage of magnitude
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	big_int->words = malloc(sizeof(unsigned long long int) * 2llu);

	if (big_int->words == NULL) return NULL;

	big_int->num_alloc = 2;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	 *
	 * assign sign and set first word to magnitude of 'init_val'
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	if (init_val > 0) {
		big_int->sign	  = POS;
		big_int->words[0] = (unsigned long long int)  init_val;

	} else if (init_val < 0) {
		big_int->sign     = NEG;
		big_int->words[0] = (unsigned long long int) -init_val;

	} else
		big_int->sign     = ZRO;
		big_int->words[0] = 0llu;
	}

	big_int->num_words = 1;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

	return big_int;
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
