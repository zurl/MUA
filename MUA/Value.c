//这个文件提供基本数据类型
#include "Value.h"
#include<stdio.h>
#include "Input.h"
#include<stdlib.h>
#include<string.h> 

void dfsFreeList(ListNode *x) {
	if (x != NULL) {
		dfsFreeList(x->next);
		freeValue(x->data);
		free(x);
	}
}
void freeList(List * value) {
	dfsFreeList(value->node);
	free(value);
}

void printList(const List * value) {
	printf(" [ ");
	ListNode * node = value->node;
	while (node != NULL) {
		printValue(node->data); putchar(' ');
		node = node->next;
	}
	printf(" ] ");
}
void printValue(const Value * value) {
	if (value->type == VNull)printf("[NULL]");
	if (value->type == VInteger)printf("%lld",value->data->integer);
	if (value->type == VReal)printf("%0.2f", value->data->real);
	if (value->type == VWord)printf("%s", value->data->word);
	if (value->type == VLiteral)printf("%s", value->data->word);
	if (value->type == VBoolean)if (value->data->integer == 1)printf("true");else printf("false");
	if (value->type == VList)printList(value->data->list);
}
void printRawList(FILE * f, const List * value) {
	fprintf(f," [ ");
	ListNode * node = value->node;
	while (node != NULL) {
		printRawValue(f, node->data); fprintf(f, " ");
		node = node->next;
	}
	fprintf(f," ] ");
}
void printRawValue(FILE * f,const Value * value) {
	if (value->type == VNull || value->type == VFunction)fprintf(f," null ");
	if (value->type == VInteger)fprintf(f," %lld ", value->data->integer);
	if (value->type == VReal)fprintf(f," %f ", value->data->real);
	if (value->type == VWord)fprintf(f," %s ", value->data->word);
	if (value->type == VLiteral)fprintf(f," \'%s ", value->data->word);
	if (value->type == VBoolean)if (value->data->integer == 1)fprintf(f," true "); else fprintf(f," false ");
	if (value->type == VList)printRawList(f,value->data->list);
}
//基本数据类型
void freeValue(Value * value) {
	if (value->type == VWord || value->type == VLiteral) {
		free(value->data->word);
	}if (value->type == VList) {
		freeList(value->data->list);
	}
	if (value->data != NULL)free(value->data);
	free(value);
}
List * copyList(List * list);
Value * copyValue(const Value * value) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = value->type;
	if (value->type == VNull) {
		ret->data = NULL;
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
		return node;
	}
}
List * copyList(List * list) {
	List * ret = (List *)malloc(sizeof(List));
	ret->node = copyListDfs(list->node);
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
	else {
		return getValueFromNull();
	}
}
Value * getValueFromNumber(long long x) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = VInteger;
	ret->data->integer = x;
	return ret;
}
Value * getValueFromReal(double x) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = VReal;
	ret->data->real = x;
	return ret;
}
Value * getValueFromStr(const char * x) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = VWord;
	ret->data->word = copyString(x);
	return ret;
}
Value * getValueFromNull(void) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->type = VNull;
	ret->data = NULL;
	return ret;
}
