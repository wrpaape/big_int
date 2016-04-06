#ifndef BIG_INT_UTILS_H_
#define BIG_INT_UTILS_H_
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
/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

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
#endif /* ifndef BIG_INT_UTILS_H_ */
