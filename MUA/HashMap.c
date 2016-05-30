//这个文件提供一个哈希表
#include<stdlib.h>
#include<string.h>
#include "Value.h"
#include "HashMap.h"
#include "Input.h"

HashMap * createHashMap(void) {
	HashMap * hashmap = (HashMap *)malloc(sizeof(HashMap));
	hashmap->len = 37;
	hashmap->size = 0;
	hashmap->data = (HashNode **)(malloc(sizeof(HashNode * ) * hashmap->len));
	for (int i = 0; i <= hashmap->len - 1; i++)
		hashmap->data[i] = NULL;
	return hashmap;
}

int hashString(const char * str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str){
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

HashNode * createNewNode(const char * key, const Value * data, HashNode * next) {
	HashNode * node = (HashNode *)malloc(sizeof(HashNode));
	node->next = next;
	node->data = copyValue(data);
	node->key = copyString(key);
	return node;
}

void freeNode(HashNode * node) {
	free(node->key);
	freeValue(node->data);
	free(node);
}
	
void setElement(HashMap * hashMap, const char * key, const Value * data) {
	HashNode * node = hashMap->data[hashString(key) % hashMap->len];
	if (node == NULL) {
		hashMap->data[hashString(key) % hashMap->len] = createNewNode(key, data, NULL);
		return;
	}
	while (node != NULL) {
		if (strcmp(node->key, key) == 0) {
			freeValue(node->data);
			node->data = copyValue(data);
			return;
		}
		if (node->next == NULL) {
			node->next = createNewNode(key, data, NULL);
			return;
		}
		node = node->next;
	}
}

Value * getElement(HashMap * hashMap, const char * key) {
	HashNode * node = hashMap->data[hashString(key) % hashMap->len];
	while (node != NULL) {
		if (strcmp(node->key, key) == 0) {
			return node->data;
		}
		node = node->next;
	}
	return NULL;
}

void removeElement(HashMap * hashMap, const char * key) {
	HashNode * node = hashMap->data[hashString(key) % hashMap->len];
	if (strcmp(node->key, key) == 0) {
		hashMap->data[hashString(key) % hashMap->len] = node->next;
		freeNode(node);
		return;
	}
	while (node != NULL && node->next != NULL) {
		if (strcmp(node->next->key, key) == 0) {
			HashNode * tmp = node->next;
			node->next = node->next->next;
			freeNode(tmp);
			return;
		}
		node = node->next;
	}
	return;
}
void freeHashMap(HashMap * hashMap) {
	int len = hashMap->len;
	for (int i = 0; i < len; i++) {
		HashNode * hn = hashMap->data[i];
		while (hn != NULL) {
			free(hn->key);
			freeValue(hn->data);
			HashNode * tmp = hn;
			hn = hn->next;
			free(tmp);
		}
	}
	free(hashMap);
}
//void forEachElement(HashMap * hashMap)