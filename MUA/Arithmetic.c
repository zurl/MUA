#include "Function.h"
#include "Runtime.h"
#include <stdio.h>
#include <string.h>

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
		//TODO:err;
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
		printf("Syntax Error: `isempty` can only be applyed on `word` or `list`.\n");
		return getValueFromNull();
	}
}