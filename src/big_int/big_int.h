#ifndef BIG_INT__BIG_INT_H_
#define BIG_INT__BIG_INT_H_

#include "memory_management/memory_management.h"
#include "string_io/string_io.h"

enum Sign {
	NEG = -1,
	ZRO =  0,
	POS =  1
};

struct BigInt {
	enum Sign sign;
	unsigned int num_words;
	unsigned int num_alloc;
	unsigned long long int *words;
};

#endif /* ifndef BIG_INT__BIG_INT_H_ */
