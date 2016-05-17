#pragma once

typedef union UValueDate ValueData;

typedef struct SListNode {
	ValueData * data;
	struct SListNode * next;
}ListNode;

typedef struct SList {
	ListNode * node;
}List;

typedef enum EValueType {
	boolean, integer, real, list, word
}ValueType;

typedef union UValueDate {
	long long integer;
	double real;
	char * word;
	List * list;
}ValueData;

typedef struct SValue {
	ValueType type;
	ValueData * data;
}Value;

void freeValue(Value * value);
Value * copyValue(Value * value);