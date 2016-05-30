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
		return getValueFromReal(r((double)registerA->data->integer, registerB->data->real));
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromReal(r(registerA->data->real, (double)registerB->data->integer));
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
long long SFaddI(long long a, long long b) {
	return a + b;
}
double SFaddD(double a, double b) {
	return a + b;
}
Value * SFadd(void) {
	return abstractCalculate(SFaddI, SFaddD);
}
/* SUB */
long long SFsubI(long long a, long long b) {
	return a - b;
}
double SFsubD(double a, double b) {
	return a - b;
}
Value * SFsub(void) {
	return abstractCalculate(SFsubI, SFsubD);
}
/* MUL */
long long SFmulI(long long a, long long b) {
	return a * b;
}
 double SFmulD(double a, double b) {
	return a * b;
}
Value * SFmul(void) {
	return abstractCalculate(SFmulI, SFmulD);
}
/* DIV */

long long SFdivI(long long a, long long b) {
	return a / b;
}
double SFdivD(double a, double b) {
	return a / b;
}
Value * SFdiv(void) {
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
	if (registerA->data->integer && registerA->data->integer)return SFtrue();
	return SFfalse();
}
Value *SFor(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `or` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	if (registerA->data->integer || registerA->data->integer)return SFtrue();
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
	if (registerA->type == VInteger)return getValueFromReal(sqrt((double)registerA->data->integer));
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
Value * SFtest(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: Command `test` can only be applied on `bool` value.\n");
		return getValueFromNull();
	}
	registerTestFlag = (int)registerA->data->integer;
	return getValueFromNull();
}
Value * SFiftrue(void) {
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
Value * SFiffalse(void) {
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
Value * SFword(void) {
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
Value * SFlist(void) {
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
	if (tmp1->node == tmp2->node)tmp1->node = NULL;
	else node->next = NULL;
	return ret;
}
Value * SFjoin(void) {
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
	if (tmp1->node == newnode)tmp1->node = NULL;
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
	char * sta = substring(str, st, ed);
	Value * ret = getValueFromStr(sta);
	free(sta);
	return ret;
}

Value * SFfirst(void) {
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
Value * SFlast(void) {
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
Value * SFbutfirst(void) {
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
Value * SFbutlast(void) {
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
Value * SFitem(void) {
	if (registerA->type != VList && registerA->type != VLiteral) {
		printf("Syntax Error: Command `item` can only recieve `list` or `word` value as first arguments.\n");
		return getValueFromNull();
	}
	if (registerA->type != VInteger) {
		printf("Syntax Error: Command `item` can only recieve integer value as second arguments.\n");
		return getValueFromNull();
	}
	if (registerA->type == VWord) {
		int len = strlen(registerA->data->word);
		if (registerB->data->integer <= 0 || registerB->data->integer > len) {
			printf("Runtime Error: illegal length.\n");
			return getValueFromNull();
		}
		return getValueFromSubString(registerB->data->word, (int)registerB->data->integer - 1, (int)registerB->data->integer - 1);
	}
	else {
		ListNode * node = registerA->data->list->node;
		if (registerB->data->integer <= 0 ) {
			printf("Runtime Error: illegal length.\n");
			return getValueFromNull();
		}
		for (int i = 1; i <= registerB->data->integer; i++) {
			if (node->next != NULL)node = node->next;
			else {
				printf("Runtime Error: illegal length.\n");
				return getValueFromNull();
			}
		}
		return copyValue(node->data);		
	}
}
Value * getValueFromBool(int x) {
	if (x)return SFtrue();
	else return SFfalse();
}
Value * SFeq(void) {
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->integer == registerB->data->integer);
	}
	else if (registerA->type == VInteger && registerB->type == VReal){
		return getValueFromBool(registerA->data->integer == registerB->data->real);
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->real == registerB->data->integer);
	}
	else if (registerA->type == VReal && registerB->type == VReal) {
		return getValueFromBool(registerA->data->real == registerB->data->real);
	}
	else if (registerA->type == VWord && registerB->type == VWord) {
		return getValueFromBool(strcmp(registerA->data->word,registerB->data->word) == 0);
	}
	else {
		printf("Syntax Error: Command `eq` can only recieve `word` or `number` value as arguments.\n");
		return getValueFromNull();
	}
}
Value * SFgt(void) {
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->integer > registerB->data->integer);
	}
	else if (registerA->type == VInteger && registerB->type == VReal) {
		return getValueFromBool(registerA->data->integer > registerB->data->real);
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->real > registerB->data->integer);
	}
	else if (registerA->type == VReal && registerB->type == VReal) {
		return getValueFromBool(registerA->data->real > registerB->data->real);
	}
	else if (registerA->type == VWord && registerB->type == VWord) {
		return getValueFromBool(strcmp(registerA->data->word, registerB->data->word) > 0);
	}
	else {
		printf("Syntax Error: Command `gt` can only recieve `word` or `number` value as arguments.\n");
		return getValueFromNull();
	}
}
Value * SFlt(void) {
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->integer < registerB->data->integer);
	}
	else if (registerA->type == VInteger && registerB->type == VReal) {
		return getValueFromBool(registerA->data->integer < registerB->data->real);
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromBool(registerA->data->real < registerB->data->integer);
	}
	else if (registerA->type == VReal && registerB->type == VReal) {
		return getValueFromBool(registerA->data->real < registerB->data->real);
	}
	else if (registerA->type == VWord && registerB->type == VWord) {
		return getValueFromBool(strcmp(registerA->data->word, registerB->data->word) < 0);
	}
	else {
		printf("Syntax Error: Command `lt` can only recieve `word` or `number` value as arguments.\n");
		return getValueFromNull();
	}
}
Value * SFmod(void) {
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromNumber(registerA->data->integer % registerB->data->integer);
	}
	else {
		printf("Syntax Error: Command `mod` can only recieve integer value as arguments.\n");
		return getValueFromNull();
	}
}
