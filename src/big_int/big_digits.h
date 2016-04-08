#ifndef BIG_INT_BIG_DIGITS_H_
#define BIG_INT_BIG_DIGITS_H_
/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

struct BigDigits *words_to_big_digits(const size_t word_count,
				      word_t *words);

void add_big_digits(struct BigDigits *restrict result,
		    struct BigDigits *restrict big1,
		    struct BigDigits *restrict big2);

void subtract_big_digits(struct BigDigits *restrict result,
			 struct BigDigits *restrict big1,
			 struct BigDigits *restrict big2);


static inline void multiply_big_digits(struct BigDigits *restrict result,
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

static inline struct BigDigits *init_zeroed_big_digits(const size_t count);

static inline void add_digit_to_big_digits(struct BigDigits *big,
					   digit_t digit);

static inline enum Sign compare_digits(digit_t *restrict digits1,
				       digit_t *restrict digits2,
				       const size_t count1,
				       const size_t count2);

size_t do_multiply_big_digits(digit_t *restrict res_digits,
			      digit_t *restrict digits1,
			      digit_t *restrict digits2,
			      const size_t count);

size_t add_split_digits(digit_t *restrict res_digits,
			digit_t *restrict digits1,
			digit_t *restrict digits2,
			const size_t count);

size_t decrement_digits(digit_t *restrict digits1,
			digit_t *restrict digits2,
			const size_t count1,
			const size_t count2);

size_t add_poly_pair(digit_t *restrict res_digits,
		     digit_t *restrict digits1,
		     digit_t *restrict digits2,
		     const size_t count1,
		     const size_t count2,
		     const size_t n);

size_t subtract_poly_pair(digit_t *restrict res_digits,
			  digit_t *restrict digits1,
			  digit_t *restrict digits2,
			  const size_t count1,
			  const size_t count2,
			  const size_t n1,
			  const size_t n2);

/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline void free_big_digits(struct BigDigits *big)
{
	free(big->digits);
	free(big);
}

/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_DIGITS_H_ */
