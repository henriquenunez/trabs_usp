#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct _string_pair
{
	char *key;
	char *value;
} STRING_PAIR;

typedef struct _vector
{
	STRING_PAIR *data;
	unsigned int size;
} STRING_PAIR_VECTOR;

#endif
