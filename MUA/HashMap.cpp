//这个文件提供一个哈希表
#include<stdlib.h>
#include<string.h>
#include "Value.h"
const int pirmeArray[] = {17,37,79,163,331,673,1361,2729,5471,10949,21911,43853,87719,175447,350899,701819,1403641,2807303,5614657,11229331,22458671, 44917381,89834777,179669557,359339171,718678369,1437356741,2147483647};

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

HashMap * createHashMap() {
	HashMap * hashmap = (HashMap *)malloc(sizeof(HashMap));
	hashmap->len = 17;
	hashmap->size = 0;
	hashmap->data = (HashNode *)(malloc(sizeof(HashNode * ) * hashmap->len));
	return hashmap;
}

int hashString(char * str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str){
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

void resizeHashMap(HashMap * hashmap) {
	//当size >= len * 2时 resize;
	//TODO:: next
}
HashNode * createNewNode(char * key, Value * data, HashNode * next) {
	HashNode * node = (HashNode *)malloc(sizeof(HashNode));
	node->next = NULL;
	node->data = (char *)malloc(sizeof(char) * (strlen(data) + 1));
	strcpy(node->data, data);
	return node;
}

void freeNode(HashNode * node) {
	free(node->key);
	freeValue(node->data);
	free(node);
}
	
void setElement(HashMap * hashMap, char * key, Value * data) {
	HashNode * node = hashMap->data[hashString(key,hashMap) % hashMap->len];
	if (node == NULL) {
		hashMap->data[hashString(key, hashMap) % hashMap->len] = createNewNode(key, data, NULL);
		return;
	}
	while (node != NULL) {
		if (strcmp(node->key, key) == 0) {
			free(node->data);
			node->data = (char *)malloc(sizeof(char) * (strlen(data) + 1));
			strcpy(node->data, data);
			return;
		}
		if (node->next == NULL) {
			node->next = createNewNode(key, data, NULL);
			return;
		}
		node = node->next;
	}
}

Value * getElement(HashMap * hashMap, char * key) {
	HashNode * node = hashMap->data[hashString(key, hashMap) % hashMap->len];
	while (node != NULL) {
		if (strcmp(node->key, key) == 0) {
			return node->key;
		}
		node = node->next;
	}
	return NULL;
}

void removeElement(HashMap * hashMap, char * key) {
	HashNode * node = hashMap->data[hashString(key, hashMap) % hashMap->len];
	if (strcmp(node->key, key) == 0) {
		hashMap->data[hashString(key, hashMap) % hashMap->len] = node->next;
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

//void forEachElement(HashMap * hashMap)