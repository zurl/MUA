#include "Value.h"
#include "Runtime.h"
#include "Symbol.h"
#include <stdlib.h>

typedef long long(*IntHandeler)(long long, long long);
typedef double(*RealHandeler)(double, double);

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
Value * getValueFromNull() {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->type = VNull;
	return ret;
}

typedef struct SSysFunc {
	char * name;
	FunctionData func;
	int argc;
}SysFunc;



Value * abstractCalculate(IntHandeler i,RealHandeler r) {// $x,$y
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
inline long long SFaddI(long long a, long long b) {
	return a + b;
}
inline double SFaddD(double a, double b) {
	return a + b;
}
inline Value * SFadd() {
	return abstractCalculate(SFaddI, SFaddD);
}

inline Value * SFprint() {
	printValue(registerA);
	return getValueFromNull();
}


void initSystemFunction() {
	SysFunc sysFunc[] = { 
		{ "add",SFadd,2 },
		{ "print",SFprint,1 }
	};
	int length = (sizeof(sysFunc) / sizeof(SysFunc));
	for (int i = 0; i <= length - 1; i++) {
		Value * func = (Value *)malloc(sizeof(Value));
		func->data = (ValueData *)malloc(sizeof(ValueData));
		func->type = VFunction;
		func->data->function = (Function *)malloc(sizeof(Function));
		func->data->function->argc = sysFunc[i].argc;
		func->data->function->data = sysFunc[i].func;
		setSymbol(symbolTable, sysFunc[i].name, func);
	}
}