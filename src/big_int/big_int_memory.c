/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "big_int_globals.h"
#include "big_int_memory.h"

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define MIN_WORDS 2lu

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* EXTERN INLINE FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

extern inline void free_big_int(struct BigInt *big_int);

/* EXTERN INLINE FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			init_big_int(1)					*
 *									*
 * Allocates memory for a BigInt with 2 words then initializes its sign	*
 * and magnitude corresponding to input integer 'init_val'.		*
 ************************************************************************/
struct BigInt *init_big_int(const long long int init_val)
{
	/* allocate BigInt struct
	 * ================================================================== */
	struct BigInt *big;

	HANDLE_MALLOC(big, sizeof(struct BigInt));


	/* allocate 2 words for storage of magnitude
	 * ================================================================== */
	HANDLE_MALLOC(big->words, sizeof(unsigned long long int) * 2lu);

	big->num_alloc = 2lu;


	/* assign sign and set first word to magnitude of 'init_val'
	 * ================================================================== */
	if (init_val > 0) {
		big->sign     = POS;
		big->words[0] = (unsigned long long int)  init_val;

	} else if (init_val < 0) {
		big->sign     = NEG;
		big->words[0] = (unsigned long long int) -init_val;

	} else {
		big->sign     = ZRO;
		big->words[0] = 0llu;
	}

	big->num_words = 1u;


	return big;
}



/************************************************************************
 *			expand_big_int_words(1)				*
 *									*
 * Allocates additional space for 'words' array of 'big'.		*
 ************************************************************************/
void expand_big_int(struct BigInt *big, const size_t required)
{
	const size_t expanded = next_pow_two(required);

	if (realloc(big->words,
		    sizeof(unsigned long long int) * expanded) == NULL) {

		EXIT_ON_FAILURE("failed to reallocate number of words"
				"from %lu to %lu",
				big->num_alloc, expanded);
	}

	big->num_alloc = expanded;
}

/* TOP-LEVEL FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* HELPER FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/************************************************************************
 *			next_pow_two(1)					*
 *									*
 * Returns 'num' rounded up to the next closest power of two.		*
 ************************************************************************/
inline size_t next_pow_two(size_t num)
{
	return 1lu << (sizeof(size_t) - __builtin_clzl(num - 1lu));
}

/* HELPER FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
