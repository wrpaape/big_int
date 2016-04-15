#ifndef BIG_INT_BIG_DIGITS_H_
#define BIG_INT_BIG_DIGITS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdbool.h>

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

size_t words_to_digits(digit_t **restrict digits,
		       const word_t *restrict words,
		       const size_t count);

size_t digits_to_words(word_t **restrict words,
		       const digit_t *restrict digits,
		       const size_t count);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

size_t multiply_digits_by_word(digit_t *restrict res_digits,
			       const digit_t *restrict digits,
			       const size_t count,
			       word_t word);

size_t multiply_digits_by_digit(digit_t *restrict res_digits,
			       const digit_t *restrict digits,
			       const size_t count,
			       digit_t digit);

size_t increment_digits(digit_t *restrict digits1,
			const digit_t *restrict digits2,
			const size_t count1,
			const size_t count2);

size_t do_multiply_digits(digit_t *restrict res_digits,
			  const digit_t *restrict digits1,
			  const digit_t *restrict digits2,
			  const size_t count);

bool add_split_digits(digit_t *restrict res_digits,
		      const digit_t *restrict lower,
		      const digit_t *restrict upper,
		      const size_t count);

size_t add_digits(digit_t *restrict res_digits,
		  const digit_t *restrict digits1,
		  const digit_t *restrict digits2,
		  const size_t count1,
		  const size_t count2);

size_t subtract_digits(digit_t *restrict res_digits,
		       const digit_t *restrict digits1,
		       const digit_t *restrict digits2,
		       const size_t count1,
		       const size_t count2);

size_t add_poly_pair(digit_t *restrict res_digits,
		     const digit_t *restrict digits1,
		     const digit_t *restrict digits2,
		     const size_t count1,
		     const size_t count2,
		     const size_t n);


size_t word_div_rem(digit_t *restrict remainder,
		    word_t *restrict divisor,
		    const digit_t *restrict dividend,
		    const digit_t *restrict quotient,
		    const size_t dvd_cnt,
		    const size_t quo_cnt);

struct DCell *digits_mult_map(const digit_t *restrict digits,
			      const size_t count);


bool decrement_remainder(digit_t *restrict rem,
			 const digit_t *restrict mult,
			 const size_t count);


static inline void set_zero_padded_word_base(digit_t *restrict base,
					     const size_t pad_size);

static inline size_t word_to_digits(digit_t *restrict digits,
				    word_t word);

static inline word_t digits_to_word(const digit_t *restrict digits,
				    const size_t count);

static inline void free_digits_mult_map(struct DCell *mult_map);

/* HELPER FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_DIGITS_H_ */
