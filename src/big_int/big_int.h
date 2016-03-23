#ifndef BIG_INT_BIG_INT_H_
#define BIG_INT_BIG_INT_H_

#include "mem_mgmt.h"
#include "string_io.h"

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

int test_fun(void);

#endif /* ifndef BIG_INT_BIG_INT_H_ */
