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

struct BigInt *init_big_int(long long int init_val);

char *big_int_to_s(struct BigInt *big_int);
