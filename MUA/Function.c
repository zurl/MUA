#include "Value.h"
#include "Runtime.h"
#include "Symbol.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int isInFunction(void) {
	if (symbolTable->next->next == NULL)return 0;
	return 1;
}
Value * SFoutput(void) {
	if (!isInFunction()) {
		printf("Runtime Error: `output` only can be used in function.\n");		
	}
	else {
		setSymbol(symbolTable,"$" , registerA);
	}
	return getValueFromNull();
}
Value * SFstop(void) {
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->type = VFuncStop;
	return ret;
}
Value * SFendl(void) {
	printf("\n");
	return getValueFromNull();
}	
Value * SFerase(void) {
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

Value * SFrepeat(void) {
	if (registerA->type != VInteger || registerA->data->integer<0) {
		printf("Syntax Error: `repeat` only can recieve positive integer as first argument.\n");
		return getValueFromNull();
	}
	if (registerB->type != VList) {
		printf("Syntax Error: `repeat` only can recieve list as second argument.\n");
		return getValueFromNull();
	}
	int times = (int)registerA->data->integer;
	ListNode * tmp = registerB->data->list->node;
	for (int i = 1; i <= times; i++) {
		ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
		listInstance->now = tmp;
		call(listInstance);
	}
	return getValueFromNull();
}

Value * SFread(void) {
	char * buffer = (char *)malloc(sizeof(char) * EXCHANGE_BUFFER_SIZE);
	scanf("%s", buffer);
	Buffer *buf = (Buffer *)malloc(sizeof(Buffer));
	buf->data = buffer;
	buf->st = 0;
	buf->ed = strlen(buffer);
	buffer[strlen(buffer)] = '\n';
	TokenList * tokenList = getTokenListFromBuffer(buf);
	List * list = getListFromTokenList(tokenList);
	Value * ret = copyValue(list->node->data);
	free(buffer);
	//todo::freeTokenList();
	//todo::freeList();
	return ret;
}
Value * SFreadlist(void) {
	Buffer * buffer = getBufferFromConsole();
	TokenList * tokenList = getTokenListFromBuffer(buffer);
	List * list = getListFromTokenList(tokenList);
	Value * ret = (Value *)malloc(sizeof(Value));
	ret->data = (ValueData *)malloc(sizeof(ValueData));
	ret->data->list = list;
	free(buffer);
	//freeTokenList todo::
	return ret;
}

Value * SFpi(void) {
	return getValueFromReal(3.14159);
}
Value * SFrun(void) {
	if (registerA->type != VList) {
		printf("Syntax Error: `run` only can recieve list as first argument.\n");
		return getValueFromNull();
	}
	ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
	listInstance->now = registerA->data->list->node;
	call(listInstance);
	return getValueFromNull();
}
Value * SFif(void) {
	if (registerA->type != VBoolean) {
		printf("Syntax Error: `run` only can recieve `bool` as first argument.\n");
		return getValueFromNull();
	}
	if (registerB->type != VList || registerC->type != VList) {
		printf("Syntax Error: `if` only can recieve  `list` as second and third argument.\n");
		return getValueFromNull();
	}
	if (registerA->data->integer == 1){
		ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
		listInstance->now = registerB->data->list->node;
		call(listInstance);
	}
	else {
		ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
		listInstance->now = registerC->data->list->node;
		call(listInstance);
	}
	return getValueFromNull();
}
Value * SFlocal(void) {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: `local` only can recieve `word` as first argument.\n");
		return getValueFromNull();
	}
	setSymbol(symbolTable, registerA->data->word, getValueFromNull());
	return getValueFromNull();
}
Value * SFnull(void) {
	return getValueFromNull();
}
Value * SFpoall(void) {
	int len = symbolTable->hashMap->len;
	for (int i = 0; i < len; i++) {
		HashNode * hn = symbolTable->hashMap->data[i];
		while (hn != NULL) {
			printf("%s : ", hn->key);
			printValue(hn->data);
			printf("\n");
			hn = hn->next;
		}
	}
	return getValueFromNull();
}
Value * SFerall(void) {
	SymbolTable * tmp = symbolTable->next;
	freeSymbolTable(symbolTable);
	symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));
	symbolTable->hashMap = createHashMap();
	symbolTable->next = tmp;
	return getValueFromNull();
}
Value * SFload(void) {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: `save` only can recieve `word` as first argument.\n");
		return getValueFromNull();
	}
	Buffer * buffer = getBufferFromFile(registerA->data->word);
	if (buffer == NULL) {
		printf("Runtime Error: invaild filename.\n");
		return getValueFromNull();
	}
	TokenList * tokenList = getTokenListFromBuffer(buffer);
	List * list = getListFromTokenList(tokenList);
	ListInstance * listInstance = (ListInstance *)malloc(sizeof(ListInstance));
	listInstance->now = list->node;
	call(listInstance);
	return getValueFromNull();
}
Value * SFsave(void) {
	if (registerA->type != VLiteral) {
		printf("Syntax Error: `save` only can recieve `word` as first argument.\n");
		return getValueFromNull();
	}
	FILE * tmp = fopen(registerA->data->word, "w");
	if (tmp == NULL) {
		printf("Runtime Error: invaild filename.\n");
		return getValueFromNull();
	}
	int len = symbolTable->hashMap->len;
	for (int i = 0; i < len; i++) {
		HashNode * hn = symbolTable->hashMap->data[i];
		while (hn != NULL) {
			fprintf(tmp,"make \'%s ", hn->key);
			printRawValue(tmp,hn->data);
			fprintf(tmp,"\n");
			hn = hn->next;
		}
	}
	fclose(tmp);
	return getValueFromNull();
}

void initFunction(SysFunc * sysFunc ,int length) {
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

void initSystemFunction(void) {
	SysFunc sysFunc[] = {
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
		{ "isempty",SFisempty,1 },
		{ "stop",SFstop,0 },
		{ "output",SFoutput,1 },
		{ "test",SFtest,1 },
		{ "iftrue",SFiftrue,1 },
		{ "iffalse",SFiffalse,1 },
		{ "first", SFfirst, 1 },
		{ "last", SFlast, 1 },
		{ "butfirst", SFbutfirst, 1 },
		{ "butlast",SFbutlast,1 },
		{ "word",SFword,2 },
		{ "list",SFlist,2 },
		{ "join",SFjoin,2 },
		{ "isname",SFisname,1 },
		{ "repeat",SFrepeat,2 },
		{ "erase",SFerase,1 } ,
		{ "not",SFnot,1 },
		{ "and",SFand,2 },
		{ "or",SFor,2 },
		{ "random",SFrandom,1 },
		{ "sqrt",SFsqrt,1 },
		{ "item",SFitem,2 },
		{ "read",SFread,0 },
		{ "readlist",SFreadlist,0 },
		{ "eq",SFeq,2 },
		{ "gt",SFgt,2 },
		{ "lt",SFlt,2 },
		{ "mod",SFmod,2 },
		{ "endl",SFendl, 0 },
		{ "null",SFnull, 0 },
		{ "load",SFload,1},
		{ "save",SFsave,1},
		{ "erall",SFerall,0},
		{ "poall",SFpoall,0}
	};
	initFunction(sysFunc, sizeof(sysFunc) / sizeof(SysFunc));
}
void initGlobalFunction(void) {
	SysFunc globalFunc[] = {
		{ "if", SFif,3 },
		{ "pi", SFpi,0 },
		{ "run",SFrun,0 }
	};
	initFunction(globalFunc, sizeof(globalFunc) / sizeof(SysFunc));
}
