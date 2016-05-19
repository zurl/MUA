#include "Function.h"
#include "Runtime.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef long long(*IntHandeler)(long long, long long);
typedef double(*RealHandeler)(double, double);

Value * abstractCalculate(IntHandeler i, RealHandeler r) {// $x,$y
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromNumber(i(registerA->data->integer, registerB->data->integer));
	}
	else if (registerA->type == VInteger && registerB->type == VReal) {
		return getValueFromReal(r(registerA->data->integer, registerB->data->real));
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromReal(r(registerA->data->real, registerB->data->integer));
	}
	else if (registerA->type == VReal && registerB->type == VReal) {
		return getValueFromReal(r(registerA->data->real, registerB->data->real));
	}
	else {
		printf("Syntax Error: Operand type is invaild.\n");
		return getValueFromNull();
	}
}
/* ADD */
inline long long SFaddI(long long a, long long b) {
	return a + b;
}
inline double SFaddD(double a, double b) {
	return a + b;
}
Value * SFadd() {
	return abstractCalculate(SFaddI, SFaddD);
}
/* SUB */
inline long long SFsubI(long long a, long long b) {
	return a - b;
}
inline double SFsubD(double a, double b) {
	return a - b;
}
Value * SFsub() {
	return abstractCalculate(SFsubI, SFsubD);
}
/* MUL */
inline long long SFmulI(long long a, long long b) {
	return a * b;
}
inline double SFmulD(double a, double b) {
	return a * b;
}
Value * SFmul() {
	return abstractCalculate(SFmulI, SFmulD);
}
/* DIV */

inline long long SFdivI(long long a, long long b) {
	return a / b;
}
inline double SFdivD(double a, double b) {
	return a / b;
}
Value * SFdiv() {
	return abstractCalculate(SFdivI, SFdivD);
}
Value *SFnot(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `not` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	if (registerA->data->integer)return SFfalse();
	return SFtrue();
}
Value *SFand(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `and` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	if (registerA->data->integer && registerA->data->integer)return SFture();
	return SFfalse();
}
Value *SFor(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `or` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	if (registerA->data->integer || registerA->data->integer)return SFture();
	return SFfalse();
}

Value *SFrandom(void) {
	if (registerA->type != VInteger) {
		printf("Syntax Error: Command `random` can only be applied on `number` value.\n");
		return getValueFromNull();
	}
	return getValueFromNumber(rand() % registerA->data->integer);
}
Value *SFsqrt(void) {
	if (registerA->type != VInteger && registerA->type != VReal) {
		printf("Syntax Error: Command `random` can only be applied on `number` value.\n");
		return getValueFromNull();
	}
	if (registerA->type == VInteger)return getValueFromReal(sqrt(registerA->data->integer));
	else return getValueFromReal(sqrt(registerA->data->real));
}

Value * SFtrue(void) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = VBoolean;
	ret->data->integer = 1;
	return ret;
}
Value * SFfalse(void) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->type = VBoolean;
	ret->data->integer = 0;
	return ret;
}
Value * SFislist(void) {
	if (registerA->type == VList)return SFtrue();
	else return SFfalse();
}
Value * SFisword(void) {
	if (registerA->type == VLiteral)return SFtrue();
	else return SFfalse();
}
Value * SFisnumber(void) {
	if (registerA->type == VInteger || registerA->type == VReal)return SFtrue();
	else return SFfalse();
}
Value * SFisbool(void) {
	if (registerA->type == VBoolean)return SFtrue();
	else return SFfalse();
}
Value * SFisempty(void) {
	if (registerA->type == VList) {
		if (registerA->data->list->node == NULL)return SFfalse();
		else return SFtrue();
	}
	else if (registerA->type == VLiteral) {
		if (strcmp(registerA->data->word,"") == 0)return SFfalse();
		else return SFtrue();
	}
	else {
		printf("Syntax Error: Command `isempty` can only be applyed on `word` or `list`.\n");
		return getValueFromNull();
	}
}
Value * SFtest() {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `test` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	registerTestFlag = registerA->data->integer;
	return getValueFromNull();
}
Value * SFiftrue() {
	if (registerA->type != VList) {
		printf("Syntax Error: Command `iftrue` can only be applied on `list` value.\n");
		return getValueFromNull();
	}
	if (registerTestFlag == 1) {
		ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
		newInstance->now = registerA->data->list->node;
		eval(newInstance);
		free(newInstance);
	}
	return getValueFromNull();
}
Value * SFiffalse() {
	if (registerA->type != VList) {
		printf("Syntax Error: Command `iffalse` can only be applied on `list` value.\n");
		return getValueFromNull();
	}
	if (registerTestFlag == 0) {
		ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
		newInstance->now = registerA->data->list->node;
		eval(newInstance);
		free(newInstance);
	}
	return getValueFromNull();
}
Value * SFword() {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: Command `word` can only recieve `word` value as first argument .\n");
		return getValueFromNull();
	}
	if (registerB->type != VLiteral && registerB->type != VInteger && registerB->type != VReal && registerB->type != VBoolean) {
		printf("Syntax Error: Command `word` can only recieve `word` or `number` or `bool` value as second argument .\n");
		return getValueFromNull();
	}
	char * buffer = (char *)malloc(sizeof(char) * EXCHANGE_BUFFER_SIZE);
	if (registerB->type == VLiteral)sprintf(buffer, "%s%s", registerA->data->word, registerB->data->word);
	if (registerB->type == VInteger)sprintf(buffer, "%s%lld", registerA->data->word, registerB->data->integer);
	if (registerB->type == VReal)sprintf(buffer, "%s%lf", registerA->data->word, registerB->data->real);
	if (registerB->type == VBoolean)sprintf(buffer, "%s%s", registerA->data->word, registerB->data->integer==1?"true":"false");
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData*)malloc(sizeof(ValueData));
	ret->type = VLiteral;
	ret->data->word = buffer;
	return ret;	
}
Value * SFlist() {
	if (registerB->type != VList &&registerA->type != VList) {
		printf("Syntax Error: Command `list` can only recieve `list` value as arguments.\n");
		return getValueFromNull();
	}
	List * tmp1 = registerA->data->list;
	List * tmp2 = registerB->data->list;
	ListNode * node = tmp1->node;
	if (node == NULL) {
		tmp1->node = tmp2->node;
	}
	else {
		while (node->next != NULL) node = node->next;
		node->next = tmp2->node;
	}
	Value * ret = copyValue(registerA);
	if (tmp1->node == tmp2->node)tmp1->node == NULL;
	else node->next = NULL;
	return ret;
}
Value * SFjoin() {
	if (registerA->type != VList) {
		printf("Syntax Error: Command `join` can only recieve `list` value as the first arguments.\n");
		return getValueFromNull();
	}
	List * tmp1 = registerA->data->list;
	ListNode * node = tmp1->node;
	ListNode * newnode = (ListNode *)malloc(sizeof(ListNode));
	newnode->data = copyValue(registerB);
	newnode->next = NULL;
	if (node == NULL) {
		tmp1->node = newnode;
	}
	else {
		while (node->next != NULL) node = node->next;
		node->next = newnode;
	}
	Value * ret = copyValue(registerA);
	if (tmp1->node == newnode)tmp1->node == NULL;
	else node->next = NULL;
	return ret;
}


char * substring(const char * src, int st, int ed) {
	char * ret = (char *)malloc(sizeof(char) * (ed - st + 2));
	for (int i = st; i <= ed; i++)
		ret[i - st] = src[i];
	ret[ed - st + 1] = 0;
	return ret;
}
Value * getValueFromSubString(const char * str, int st, int ed) {
	if (*str == 0) {
		printf("Runtime Error: Command `first` cannot be applied for NULL word.\n");
		return getValueFromNull();
	}
	str = substring(str, st, ed);
	Value * ret = getValueFromStr(str);
	free(str);
	return ret;
}

Value * SFfirst() {
	if (registerA->type == VLiteral)
		return getValueFromSubString(registerA->data->word, 0, 0);
	if (registerA->type != VList) {
		printf("Syntax Error: Command `first` can only recieve `list` or `word` value as arguments.\n");
		return getValueFromNull();
	}
	if (registerA->data->list->node == NULL) {
		printf("Runtime Error: Command `first` cannot be applied for NULL list.\n");
		return getValueFromNull();
	}
	return copyValue(registerA->data->list->node->data);
}
Value * SFlast() {
	if (registerA->type == VLiteral) {
		int len = strlen(registerA->data->word);
		return getValueFromSubString(registerA->data->word,len-1, len-1);
	}
	if (registerA->type != VList) {
		printf("Syntax Error: Command `last` can only recieve `list` value as arguments.\n");
		return getValueFromNull();
	}
	if (registerA->data->list->node == NULL) {
		printf("Runtime Error: Command `last` cannot be applied for NULL list.\n");
		return getValueFromNull();
	}
	ListNode * node = registerA->data->list->node;
	while (node->next != NULL)node = node->next;
	return copyValue(node->data);
}
Value * SFbutfirst() {
	if (registerA->type == VLiteral) {
		int len = strlen(registerA->data->word);
		return getValueFromSubString(registerA->data->word, 1, len - 1);
	}
	if (registerA->type != VList) {
		printf("Syntax Error: Command `butfirst` can only recieve `list` value as arguments.\n");
		return getValueFromNull();
	}
	if (registerA->data->list->node == NULL) {
		printf("Runtime Error: Command `butfirst` cannot be applied for NULL list.\n");
		return getValueFromNull();
	}
	ListNode * node = registerA->data->list->node;
	registerA->data->list->node = registerA->data->list->node->next;
	Value * ret = copyValue(registerA);
	registerA->data->list->node = node;
	return ret;
}
Value * SFbutlast() {
	if (registerA->type == VLiteral) {
		int len = strlen(registerA->data->word);
		return getValueFromSubString(registerA->data->word, 0, len - 2);
	}
	if (registerA->type != VList) {
		printf("Syntax Error: Command `butlast` can only recieve `list` value as arguments.\n");
		return getValueFromNull();
	}
	if (registerA->data->list->node == NULL) {
		printf("Runtime Error: Command `first` cannot be applied for NULL list.\n");
		return getValueFromNull();
	}
	if (registerA->data->list->node->next == NULL) {
		ListNode * tmp = registerA->data->list->node;
		registerA->data->list->node = NULL;
		Value * ret = copyValue(registerA);
		registerA->data->list->node = tmp;
		return ret;
	}
	else {
		ListNode * node = registerA->data->list->node;
		while (node->next->next != NULL)node = node->next;
		ListNode * tmp = node->next;
		node->next = NULL;
		Value * ret = copyValue(registerA);
		node->next = tmp;
		return ret;
	}
}