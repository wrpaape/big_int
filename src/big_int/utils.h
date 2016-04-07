#ifndef BIG_INT_UTILS_H_
#define BIG_INT_UTILS_H_
/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define BUFF_ZERO ((buff_t) 0llu)

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define VAR_SWAP(x, y)			\
do {					\
	__typeof__(x) __swap_tmp = x;	\
	x = y;				\
	y = __swap_tmp;			\
} while(0)


/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
static inline digit_t priv_nth_pow_digit(const digit_t lil,
					 const digit_t big,
					 const int n);
static inline word_t priv_nth_pow_word(const word_t lil,
				       const word_t big,
				       const int n);
static inline buff_t priv_nth_pow_buffer(const buff_t lil,
					 const buff_t big,
					 const int n);
/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline digit_t nth_pow_digit(const digit_t base,
			     const int n)
{
	return priv_nth_pow_digit(1u, base, n);
}

inline word_t nth_pow_word(const word_t base,
			   const int n)
{
	return priv_nth_pow_word(1llu, base, n);
}

inline buff_t nth_pow_buffer(const buff_t base,
			     const int n)
{
	return priv_nth_pow_buffer((buff_t) 1llu, base, n);
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

inline buff_t multiply_word_by_digit(word_t word,
				     digit_t digit)
{
	return ((buff_t) word) * ((buff_t) digit);
}


inline enum Sign compare_big_ints(struct BigInt *big1, struct BigInt *big2)
{
	if (big1->sign > big2->sign)
		return POS;

	if (big1->sign < big2->sign)
		return NEG;

	return compare_big_int_mags(big1, big2);
}



#define priv_nth_pow_body(fun)						\
do {									\
	if (n == 0) return lil;						\
	if (n == 1) return big * lil;					\
	if (n & 1)  return fun(big * lil, big * big, (n - 1) / 2);	\
	else	    return fun(lil,       big * big, n / 2);		\
} while (0)
inline digit_t priv_nth_pow_digit(digit_t lil, digit_t big, const int n)
{
	priv_nth_pow_body(priv_nth_pow_digit);
}
inline word_t priv_nth_pow_word(word_t lil, word_t big, const int n);
{
	priv_nth_pow_body(priv_nth_pow_word);
}
inline buff_t priv_nth_pow_buffer(buff_t lil, buff_t big, const int n);
{
	priv_nth_pow_body(priv_nth_pow_buffer);
}
#undef priv_nth_pow_body

/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_UTILS_H_ */
