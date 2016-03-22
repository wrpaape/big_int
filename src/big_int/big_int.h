#ifndef BIG-INT_BIG-INT_H_
#define BIG-INT_BIG-INT_H_

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

#endif /* ifndef BIG-INT_BIG-INT_H_ */
