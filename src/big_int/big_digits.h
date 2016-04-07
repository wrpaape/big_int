#ifndef BIG_INT_BIG_DIGITS_H_
#define BIG_INT_BIG_DIGITS_H_
/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

struct BigDigits *words_to_big_digits(const size_t word_count,
				      word_t *words);

void add_big_digits(struct BigDigits *restrict result,
		    struct BigDigits *restrict big1,
		    struct BigDigits *restrict big2);

void multiply_big_digits(struct BigDigits *restrict result,
			 struct BigDigits *restrict big1,
			 struct BigDigits *restrict big2);

void multiply_big_digits_by_digit(struct BigDigits *restrict result,
				  struct BigDigits *restrict big,
				  digit_t digit);

void multiply_big_digits_by_word(struct BigDigits *restrict result,
				 struct BigDigits *restrict big,
				 word_t word);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

static inline void free_big_digits(struct BigDigits *big);

static inline void add_digit_to_big_digits(struct BigDigits *big,
					   digit_t digit);
/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline struct BigDigits *init_big_digits(const size_t alloc_count)
{
	struct BigDigits *big;

	HANDLE_MALLOC(big, sizeof(struct BigDigits));
	HANDLE_MALLOC(big->digits, sizeof(digit_t) * alloc_count);

	return big;
}

inline void free_big_digits(struct BigDigits *big)
{
	free(big->digits);
	free(big);
}

/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_DIGITS_H_ */
