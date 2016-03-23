#ifndef BIG_INT_BIG_INT_TYPESPEC_H_
#define BIG_INT_BIG_INT_TYPESPEC_H_
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
#endif /* ifndef BIG_INT_BIG_INT_TYPESPEC_H_ */
