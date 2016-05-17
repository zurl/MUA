#include "Value.h"
typedef struct SHashNode {
	char * key;
	Value * data;
	struct SHashNode * next;
}HashNode;

typedef struct SHashMap {
	HashNode ** data;
	int len;
	int size;
}HashMap;