//这个文件提供基本数据类型
#include "Value.h"
#include<stdio.h>
#include "Input.h"
#include<stdlib.h>
#include<string.h>

//基本数据类型
void freeValue(Value * value) {

}
Value * copyValue(const Value * value) {
	return NULL;
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