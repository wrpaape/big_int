#ifndef BIG_INT_BIG_DIGITS_H_
#define BIG_INT_BIG_DIGITS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdbool.h>

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

size_t words_to_digits(digit_t **digits,
		       word_t *words,
		       const size_t word_count);

size_t digits_to_words(word_t **words,
		       digit_t *digits,
		       const size_t digit_count);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       digit_t *restrict digits,
			       const size_t count,
			       word_t word);

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
/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_DIGITS_H_ */
