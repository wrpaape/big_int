#ifndef BIG_INT_BIG_DIGITS_H_
#define BIG_INT_BIG_DIGITS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdbool.h>

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

size_t words_to_digits(digit_t **digits,
		       word_t *words,
		       const size_t word_count);

static inline void add_big_digits(struct BigDigits *restrict result,
				  struct BigDigits *restrict big1,
				  struct BigDigits *restrict big2);

static inline void multiply_big_digits(struct BigDigits *restrict result,
				       struct BigDigits *restrict big1,
				       struct BigDigits *restrict big2);

size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       digit_t *restrict digits,
			       const size_t count,
			       word_t word);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

static inline struct BigDigits *init_zeroed_big_digits(const size_t count);

size_t increment_digits(digit_t *restrict digits1,
			digit_t *restrict digits2,
			const size_t count1,
			const size_t count2);

size_t do_multiply_digits(digit_t *restrict res_digits,
			  digit_t *restrict digits1,
			  digit_t *restrict digits2,
			  const size_t count);

bool add_split_digits(digit_t *restrict res_digits,
		      digit_t *restrict lower,
		      digit_t *restrict upper,
		      const size_t count);

size_t add_digits(digit_t *restrict res_digits,
		  digit_t *restrict digits1,
		  digit_t *restrict digits2,
		  const size_t count1,
		  const size_t count2);

size_t subtract_digits(digit_t *restrict res_digits,
		       digit_t *restrict digits1,
		       digit_t *restrict digits2,
		       const size_t count1,
		       const size_t count2);

size_t add_poly_pair(digit_t *restrict res_digits,
		     digit_t *restrict digits1,
		     digit_t *restrict digits2,
		     const size_t count1,
		     const size_t count2,
		     const size_t n);

/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline void free_big_digits(struct BigDigits *big)
{
	free(big->digits);
	free(big);
}

/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_DIGITS_H_ */
