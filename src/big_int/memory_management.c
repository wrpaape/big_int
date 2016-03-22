#include "big_int.h"
#include "memory_management.h"

/************************************************************************
 *			init_big_int(1)					*
 *									*
 * Allocates memory for a BigInt and initializes its sign and magnitude	*
 * corresponding to input integer 'init_val'.				*
 ************************************************************************/
struct BigInt *init_big_int(long long int init_val)
{
	/* allocate BigInt struct
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	struct BigInt *big_int = malloc(sizeof(struct BigInt));

	if (big_int == NULL) return NULL;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	 *
	 * allocate 2 words for storage of magnitude
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	big_int->words = malloc(sizeof(unsigned long long int) * 2llu);

	if (big_int->words == NULL) return NULL;

	big_int->num_alloc = 2;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	 *
	 * assign sign and set first word to magnitude of 'init_val'
	 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
	if (init_val > 0) {
		big_int->sign	  = POS;
		big_int->words[0] = (unsigned long long int)  init_val;

	} else if (init_val < 0) {
		big_int->sign     = NEG;
		big_int->words[0] = (unsigned long long int) -init_val;

	} else {
		big_int->sign     = ZRO;
		big_int->words[0] = 0llu;
	}

	big_int->num_words = 1;
	/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

	return big_int;
}
