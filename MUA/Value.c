//这个文件提供基本数据类型
#include "Value.h"
#include<stdio.h>
#include "Input.h"
#include<stdlib.h>
#include<string.h> 

void printList(const Value * value) {

}
void printValue(const Value * value) {
	if (value->type == VNull)printf("[NULL]");
	if (value->type == VInteger)printf("%lld",value->data->integer);
	if (value->type == VReal)printf("%0.2f", value->data->real);
	if (value->type == VWord)printf("%s", value->data->word);
	if (value->type == VLiteral)printf("%s", value->data->word);
	if (value->type == VBoolean)if (value->data->integer == 0)printf("true");else printf("false");
	if (value->type == VList)printList(value);
}
//基本数据类型
void freeValue(Value * value) {

}
List * copyList(List * list);
Value * copyValue(const Value * value) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = value->type;
	if (value->type == VNull) {
		
	}
	else if (value->type == VBoolean || value->type == VInteger) {
		ret->data->integer = value->data->integer;
	}
	else if (value->type == VReal) {
		ret->data->real = value->data->real;
	}
	else if (value->type == VWord || value->type == VLiteral) {
		ret->data->word = copyString(value->data->word);
	}
	else if (value->type == VList) {
		ret->data->list = copyList(value->data->list);
	}
	else  if (value->type == VFunction) {
		ret->data->function = value->data->function;
	}
	return ret;
}

ListNode * copyListDfs(ListNode * x) {
	if (x == NULL)return NULL;
	else {
		ListNode * node = (ListNode*)malloc(sizeof(ListNode));
		node->data = copyValue(x->data);
		node->next = copyListDfs(x->next);
	}
}
List * copyList(List * list) {
	List * ret = (List *)malloc(sizeof(List));
	ret->node = copyListDfs(ret->node);
	return ret;
}
Value * createValue(const Token * token) {
	if (token->type == TLiteral ) {
		Value * ret = (Value *)malloc(sizeof(Value));
		ret->data = (ValueData *)malloc(sizeof(ValueData));
		ret->data->word = copyString(token->data);
		ret->type = VLiteral;
		return ret;
	}
	if (token->type == TWord) {
		Value * ret = (Value *)malloc(sizeof(Value));
		ret->data = (ValueData *)malloc(sizeof(ValueData));
		ret->data->word = copyString(token->data);
		ret->type = VWord;
		return ret;
	}
	else if(token->type == TNumber) {
		//check .
		Value * ret = (Value *)malloc(sizeof(Value));
		ret->data = (ValueData *)malloc(sizeof(ValueData));
		int isDouble = 0;
		int size = strlen(token->data);
		for (int i = 0; i <= size - 1; i++)
			if (token->data[i] == '.')isDouble = 1;
		if (isDouble) {
			ret->type = VReal;
			ret->data->real = atof(token->data);
			return ret;
		}
		else {
			ret->type = VInteger;
			ret->data->integer = atoi(token->data);
			return ret;
		}
	}
}