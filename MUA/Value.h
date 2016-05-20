#pragma once
#ifndef VALUE_H  
#define VALUE_H  
#include <stdio.h>

typedef struct SValue Value;
typedef Value*(*FunctionData)(void);

typedef struct SFunction {
	FunctionData data;
	int argc;
}Function;
typedef struct SValue Value;

typedef struct SListNode {
	Value * data;
	struct SListNode * next;
}ListNode;

typedef struct SList {
	ListNode * node;
}List;

typedef enum EValueType {
	VBoolean, VInteger, VReal, VList, VWord, VLiteral,
	VFunction, VNull , VFuncStop
}ValueType;

typedef union UValueData {
	long long integer;
	double real;
	char * word;
	List * list;
	Function * function;
}ValueData;

typedef struct SValue {
	ValueType type;
	ValueData * data;
}Value;



void freeValue(Value * value);
Value * copyValue(const Value * value);
void printValue(const Value * value);
Value * getValueFromNumber(long long x);
Value * getValueFromReal(double x);
Value * getValueFromStr(const char * x);
Value * getValueFromNull(void);
void freeList(List * value);
void printRawValue(FILE * f,const Value * value);
#endif