#include "Value.h"
#include "Runtime.h"
#include "Symbol.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct SSysFunc {
	char * name;
	FunctionData func;
	int argc;
}SysFunc;



inline Value * SFprint(void) {
	printValue(registerA);
	return getValueFromNull();
}
inline Value * SFmake(void) {
	if (registerA->type != VLiteral) {
		//ERROR
		printf("Syntax Error: `make` command only can be used on literial.");
		return getValueFromNull();
	}
	setSymbol(symbolTable, registerA->data->word, registerB);
	return getValueFromNull();
}
inline Value * SFthing(void) {
	if (registerA->type != VLiteral) {
		//ERROR
		printf("Syntax Error: `thing` command only can be used on literial.\n");
		return getValueFromNull();
	}
	Value * ret = getSymbol(symbolTable, registerA->data->word);
	if (ret == NULL) {
		printf("Runtime Error: undefined symbol `%s`.\n", registerA->data->word);
		return getValueFromNull();
	}
	return ret;
}


void initSystemFunction() {
	SysFunc sysFunc[] = { 
		{ "add",SFadd,2 },
		{ "sub",SFsub,2 },
		{ "mul",SFmul,2 },
		{ "div",SFdiv,2 },
		{ "print",SFprint,1 },
		{ "make",SFmake,2 },
		{ "thing",SFthing,1 }
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