#ifndef BIG_INT_BIG_INT_GLOBALS_H_
#define BIG_INT_BIG_INT_GLOBALS_H_
/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdlib.h>	/* malloc, free, exit, size_t, uint64_t, __int128_t */
#include <stddef.h>	/* ptrdiff_t */
#include <stdio.h>	/* printf, fprintf */
#include <errno.h>	/* errno */
#include <string.h>	/* strerror */
#include <limits.h>	/* max word value */

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TYPEDEFS, ENUM AND STRUCT DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

typedef uint32_t digit_t;

typedef uint64_t word_t;

typedef __uint128_t buff_t;

enum Sign {
	NEG = -1,
	ZRO =  0,
	POS =  1
};

struct BigInt {
	enum Sign sign;
	size_t word_count;
	size_t alloc_count;
	word_t *words;
};

struct DNode {
	digit_t *digits;
	size_t count;
};

struct MultNode {
	word_t mult;
	digit_t *digits;
};

struct MultMapKey {
	ptrdiff_t i;
	ptrdiff_t j;
	ptrdiff_t k;
};

struct MultMap {
	struct MultMapKey keys[2ul];
	struct MultNode *map[2ul][10ul][10ul];
	struct MultNode nodes[9ul];
	digit_t *digits;
};

/* TYPEDEFS, ENUM AND STRUCT DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define WORD_BITS (sizeof(word_t) * CHAR_BIT)
#define WORD_MAX UINT64_MAX
#define WORD_BASE (((buff_t) 1ull) << WORD_BITS)

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define EXIT_ON_FAILURE(format, ...)					\
do {									\
	fprintf(stderr,							\
		"\n\e[31m\e[5mERROR:\e[25m\t\e[4m" format "\e[24m\n\n"	\
		"errno:\t%s\n\n"					\
		"file:\t%s\n\n"						\
		"func:\t%s\n\n"						\
		"line:\t%d\e[0m\n",					\
		##__VA_ARGS__,						\
		strerror(errno), __FILE__, __func__, __LINE__);		\
	exit(EXIT_FAILURE);						\
} while (0)


#define HANDLE_MALLOC(ptr, size)					\
do {									\
	ptr = malloc(size);						\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu bytes", size);	\
} while (0)

#define HANDLE_CALLOC(ptr, count, size)					\
do {									\
	ptr = calloc(count, size);					\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu blocks of %lu"	\
				"bytes", count, size);			\
} while (0)

#define HANDLE_REALLOC(ptr, size)					\
do {									\
	ptr = realloc(ptr, size);					\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to reallocate memory at '" #ptr	\
				"' to %lu bytes", size);		\
} while (0)

/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

int test_fun(void);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_INT_GLOBALS_H_ */
