#pragma once
#ifndef HASHMAP_H
#define HASHMAP_H
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

HashMap * createHashMap(void);

void setElement(HashMap * hashMap, const char * key, const Value * data);

Value * getElement(HashMap * hashMap, const char * key);

void removeElement(HashMap * hashMap, const char * key);
#endif