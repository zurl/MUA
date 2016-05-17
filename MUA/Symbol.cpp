//这个文件提供符号表

#include "HashMap.h"
#include<stdio.h>

typedef struct SSymbolTable {
	HashMap * hashMap;
	struct SymbolTable * next;
}SymbolTable;

Value * getSymbol(SymbolTable * symbolTable, const char * key) {
	Value * ret;
	while (symbolTable != NULL) {
		ret = getElement(symbolTable->hashMap, key);
		if (ret != NULL)return ret;
		symbolTable = symbolTable->next;
	}
	return NULL;
}

int hasSymbol(SymbolTable * symbolTable, const char * key) {
	return getSymbol(symbolTable, key) != NULL;
}

void setSymbol(SymbolTable * symbolTable, const char *key, const Value * data) {
	setElement(symbolTable->hashMap, key, data);
}

void deleteSymbol(SymbolTable * symbolTable, const char *key) {
	//TODO:: system symbol
}