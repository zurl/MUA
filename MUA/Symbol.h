#pragma once
#ifndef SYMBOL_H
#define SYMBOL_H
#include "HashMap.h"
typedef struct SSymbolTable {
	HashMap * hashMap;
	struct SSymbolTable * next;
}SymbolTable;



Value * getSymbol(SymbolTable * symbolTable, const char * key);

int hasSymbol(SymbolTable * symbolTable, const char * key);

void setSymbol(SymbolTable * symbolTable, const char *key, const Value * data);

void deleteSymbol(SymbolTable * symbolTable, const char *key);

void freeSymbolTable(SymbolTable * symbolTable);
#endif
