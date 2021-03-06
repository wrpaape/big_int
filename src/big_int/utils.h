#ifndef BIG_INT_UTILS_H_
#define BIG_INT_UTILS_H_
/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define BUFF_ZERO ((buff_t) 0llu)
#define BUFF_ONE ((buff_t) 1llu)
#define BUFF_NINE ((buff_t) 9llu)
#define BUFF_TEN ((buff_t) 10llu)

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define VAR_SWAP(x, y)			\
do {					\
	__typeof__(x) __swap_tmp = x;	\
	x = y;				\
	y = __swap_tmp;			\
} while(0)

#define PUT_DIGITS(DIGITS, COUNT)		\
do {							\
	fputs(#DIGITS ": ", stdout);			\
	for (ptrdiff_t i = COUNT - 1l; i > -1l; --i)	\
		putc(DIGITS[i] + '0', stdout);		\
	putc('\n', stdout);				\
	fflush(stdout);					\
} while (0)

/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			next_pow_two(1)					*
 *									*
 * Returns 'num' rounded up to the next closest power of two so long as	*
 * num > 0.								*
 ************************************************************************/
inline size_t next_pow_two(size_t num)
{
	return 1lu << ((sizeof(size_t) * CHAR_BIT) - __builtin_clzl(num - 1lu));
}


#define priv_nth_pow_body(fun)						\
do {									\
	if (n == 0) return lil;						\
	if (n == 1) return big * lil;					\
	if (n & 1)  return fun(big * lil, big * big, (n - 1) / 2);	\
	else	    return fun(lil,       big * big, n / 2);		\
} while (0)

inline word_t priv_nth_pow_word(const word_t lil,
				const word_t big,
				const int n)
{
	priv_nth_pow_body(priv_nth_pow_word);
}

inline buff_t priv_nth_pow_buffer(const buff_t lil,
				  const buff_t big,
				  const int n)
{
	priv_nth_pow_body(priv_nth_pow_buffer);
}
#undef priv_nth_pow_body

inline word_t nth_pow_word(const word_t base,
			   const int n)
{
	return priv_nth_pow_word(1llu, base, n);
}

inline buff_t nth_pow_buffer(const buff_t base,
			     const int n)
{
	return priv_nth_pow_buffer(BUFF_ONE, base, n);
}

inline buff_t add_words(word_t word1,
			word_t word2)
{
	return ((buff_t) word1) + ((buff_t) word2);
}

inline buff_t add_word_to_buffer(buff_t buffer,
				 word_t word)
{
	return buffer + ((buff_t) word);
}

inline word_t upper_word(buff_t buffer)
{
	return (word_t) (buffer >> WORD_BITS);
}

inline word_t lower_word(buff_t buffer)
{
	return (word_t) buffer;
}

inline enum Sign compare_big_int_mags(struct BigInt *big1, struct BigInt *big2)
{
	if (big1->word_count < big2->word_count)
		return POS;

	if (big1->word_count > big2->word_count)
		return NEG;

	size_t i = big1->word_count;

	while (1) {
		if (big1->words[i] > big2->words[i])
			return POS;

		if (big1->words[i] < big2->words[i])
			return NEG;

		if (i == 0lu)
			return ZRO;

		--i;
	}
}


inline enum Sign compare_big_ints(struct BigInt *big1, struct BigInt *big2)
{
	if (big1->sign > big2->sign)
		return POS;

	if (big1->sign < big2->sign)
		return NEG;

	return compare_big_int_mags(big1, big2);
}

/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_UTILS_H_ */
