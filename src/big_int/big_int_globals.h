#ifndef BIG_INT_BIG_INT_GLOBALS_H_
#define BIG_INT_BIG_INT_GLOBALS_H_
/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdlib.h>	/* malloc, free, exit, size_t */
#include <stdio.h>	/* fprintf, printf */
#include <errno.h>	/* errno */
#include <string.h>	/* strerror */

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* ENUM AND STRUCT DEFINITIONS, TYPEDEFS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

enum Sign {
	NEG = -1,
	ZRO =  0,
	POS =  1
};


struct BigInt {
	enum Sign sign;
	size_t num_words;
	size_t num_alloc;
	unsigned long long int *words;
};

/* ENUM AND STRUCT DEFINITIONS, TYPEDEFS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define FORMAT_ERROR(MSG) "\n\e[31m\e[5mERROR:\e[25m\t\e[4m" MSG "\e[0m\n"

#define PRINT_CONTEXT_AND_EXIT_ON_FAILURE()				\
do {									\
	fprintf(stderr,							\
		"\n\e[31merrno:\t%s\n\n"				\
		"file:\t%s\n\n"						\
		"func:\t%s\n\n"						\
		"line:\t%d\e[0m\n",					\
		strerror(errno), __FILE__, __func__, __LINE__);		\
	exit(EXIT_FAILURE);						\
} while(0)


#define HANDLE_MALLOC(ptr, size)					\
do {									\
	ptr = malloc(size);						\
	if (ptr == NULL) {						\
		fprintf(stderr,						\
			FORMAT_ERROR("failed to allocate %lu bytes"),	\
			size);						\
		PRINT_CONTEXT_AND_EXIT_ON_FAILURE();			\
	}								\
} while(0)

/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */



/* TOP-LEVEL FUNCTION PROTOTYPES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

int test_fun(void);

/* TOP-LEVEL FUNCTION PROTOTYPES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */




/* EXTERN INLINE FUNCTION DEFINITIONS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


/* EXTERN INLINE FUNCTION DEFINITIONS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
#endif /* ifndef BIG_INT_BIG_INT_GLOBALS_H_ */
