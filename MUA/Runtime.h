#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H
#include "Value.h"
#include "Input.h"
#include "Symbol.h"

typedef struct SListInstance {
ListNode * now;
}ListInstance;

Value * eval(ListInstance * listInstance);
Value * call(ListInstance * listInstance);
void initGlobalSymbolTable(void);
void initSystemSymbolTable(void);
extern SymbolTable * symbolTable;
extern Value * registerA;
extern Value * registerB;
extern int registerTestFlag;

#define EXCHANGE_BUFFER_SIZE 256

#endif