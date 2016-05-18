//这个文件提供一个哈希表
#include<stdlib.h>
#include<string.h>
#include "Value.h"
#include "HashMap.h"
const int pirmeArray[] = {17,37,79,163,331,673,1361,2729,5471,10949,21911,43853,87719,175447,350899,701819,1403641,2807303,5614657,11229331,22458671, 44917381,89834777,179669557,359339171,718678369,1437356741,2147483647};

HashMap * createHashMap() {
	HashMap * hashmap = (HashMap *)malloc(sizeof(HashMap));
	hashmap->len = 17;
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

void resizeHashMap(HashMap * hashmap) {
	//当size >= len * 2时 resize;
	//TODO:: next
}
HashNode * createNewNode(const char * key, const Value * data, HashNode * next) {
	HashNode * node = (HashNode *)malloc(sizeof(HashNode));
	node->next = next;
	node->data = (Value *)malloc(sizeof(Value));
	node->data = copyValue(data);
	node->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(node->key, key);
//	strcpy(node->data, data);
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
			free(node->data);
			node->data = (Value *)malloc(sizeof(Value));
			//node->data = data;
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

//void forEachElement(HashMap * hashMap)