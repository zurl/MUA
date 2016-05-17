#pragma once

typedef struct SValue Value;

typedef struct SListNode {
	Value * data;
	struct SListNode * next;
}ListNode;

typedef struct SList {
	ListNode * node;
}List;

typedef enum EValueType {
	boolean, integer, real, list, word,
	function, null
}ValueType;

typedef union UValueData {
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
Value * copyValue(const Value * value);
Value * createValue(const Token * token);