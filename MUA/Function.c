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
int isInFunction() {
	if (symbolTable->next->next == NULL)return 0;
	return 1;
}
Value * SFoutput() {
	if (!isInFunction()) {
		printf("Runtime Error: `output` only can be used in function.\n");		
	}
	else {
		setSymbol(symbolTable,"$" , registerA);
	}
	return getValueFromNull();
}
Value * SFstop() {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->type = VFuncStop;
	return ret;
}
Value * SFendl() {
	printf("\n");
	return getValueFromNull();
}	
Value * SFerase() {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: `erase` only can recieve `word` as argument.\n");
		return getValueFromNull();
	}
	Value * tmp = getElement(symbolTable->hashMap, registerA->data->word);
	if (tmp == NULL) {
		printf("Runtime Error: undefined word.\n");
		return getValueFromNull();
	}
	deleteSymbol(symbolTable, registerA->data->word);
	return getValueFromNull();	
}
Value * SFisname(void) {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: `isname` only can recieve `word` as argument.\n");
		return getValueFromNull();
	}
	Value * value = getSymbol(symbolTable, registerA->data->word);
	if(value != NULL)return SFtrue();
	else return SFfalse();
}

Value * SFrepeat() {
	if (registerA->type != VInteger || registerA->data->integer<0) {
		printf("Syntax Error: `repeat` only can recieve positive integer as first argument.\n");
		return getValueFromNull();
	}
	if (registerB->type != VList) {
		printf("Syntax Error: `repeat` only can recieve list as second argument.\n");
		return getValueFromNull();
	}
	int times = registerA->data->integer;
	for (int i = 1; i <= times; i++) {
		ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
		listInstance->now = registerB->data->list->node;
		while (listInstance->now != NULL) {
			Value * tmp = eval(listInstance);
			if (tmp->type == VFuncStop) {
				freeValue(tmp);
				i = times;
				break;
			}
			freeValue(tmp);
		}
	}
	return getValueFromNull();
}

void initSystemFunction() {
	SysFunc sysFunc[] = { 
		{ "endl",SFendl, 0},
		{ "add",SFadd,2 },
		{ "sub",SFsub,2 },
		{ "mul",SFmul,2 },
		{ "div",SFdiv,2 },
		{ "print",SFprint,1 },
		{ "make",SFmake,2 },
		{ "thing",SFthing,1 },
		{ "true",SFtrue,0 },
		{ "false",SFfalse,0 },
		{ "islist",SFislist,1 },
		{ "isword",SFisword,1 },
		{ "isnumber",SFisnumber,1 },
		{ "isbool",SFisbool,1 },
		{ "isempty",SFisempty,1},
		{ "stop",SFstop,0 },
		{ "output",SFoutput,1 },
		{ "test",SFtest,1 },
		{ "iftrue",SFiftrue,1 },
		{ "iffalse",SFiffalse,1 },
		{ "first", SFfirst, 1},
		{ "last", SFlast, 1 },
		{ "butfirst", SFbutfirst, 1 },
		{ "butlast",SFbutlast,1 },
		{ "word",SFword,2 },
		{ "list",SFlist,2 },
		{ "join",SFjoin,2 },
		{ "isname",SFisname,1},
		{ "repeat",SFrepeat,2},
		{ "erase",SFerase,1}
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

