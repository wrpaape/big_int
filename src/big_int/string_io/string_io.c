#define CHARS_PER_DIGIT
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
