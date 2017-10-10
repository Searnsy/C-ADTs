#ifndef TYPE_H
#define TYPE_H

typedef enum type_e{
	CHAR,
	UNSIGNED_CHAR,
	INT,
	UNSIGNED_INT,
	SHORT,
	UNSIGNED_SHORT,
	LONG,
	UNSIGNED_LONG,
	FLOAT,
	DOUBLE,
	POINTER
} data_t;

typedef union data_u{
	char c;
	unsigned char u_c;
	int i;
	unsigned int u_i;
	short s;
	unsigned short u_s;
	long l;
	unsigned long u_l;
	float f;
	double d;
	void* p;
} data_d;

typedef struct Data_S{
	data_d data;
	data_t type;
} STYPE;

STYPE* create(data_d data, data_t type);

void destroy_data(STYPE* dat);

int compare(STYPE *first, STYPE *second);

void print(STYPE *dat);

#endif
