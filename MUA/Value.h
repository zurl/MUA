#pragma once
#ifndef VALUE_H  
#define VALUE_H  

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
	VFunction, VNull
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

#endif