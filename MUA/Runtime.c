//这个文件负责解释程序
#include "Value.h"
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include "Symbol.h"
#include "Runtime.h"

SymbolTable * symbolTable;
SymbolTable * globalTable;
Value * registerA;
Value * registerB;
Value * registerC;
int registerTestFlag = 0;

void initSystemSymbolTable(void){
	symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));
	symbolTable->hashMap = createHashMap();
	symbolTable->next = NULL;
}
void initGlobalSymbolTable(void) {
	SymbolTable * tmp = symbolTable;
	symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));
	symbolTable->hashMap = createHashMap();
	symbolTable->next = tmp;
}
Value * call(ListInstance * listInstance) {
	while (listInstance->now != NULL) {
		Value * tmp = eval(listInstance);
		if (tmp->type == VFuncStop) {
			freeValue(tmp);
			break;
		}
		freeValue(tmp);
	}
	Value * ret = getSymbol(symbolTable, "$");
	if(ret == NULL)return getValueFromNull();
	else return ret;	
}
Value * eval(ListInstance * listInstance) {
	if (listInstance->now == NULL) {

	}
	
	if (listInstance->now->data->type == VWord) {
		Value *command = getSymbol(symbolTable, listInstance->now->data->data->word);
		if (command == NULL || (command->type != VFunction &&
			(command->type != VList
			||command->data->list->node->data->type!=VList
			||command->data->list->node->next->data->type != VList))) {
			//CANT EXCUTE
			listInstance->now = listInstance->now->next;
			if(command == NULL) printf("Runtime Error : `%s` is undefined .\n", listInstance->now->data->data->word);
			else printf("Runtime Error : `%s` is not a callable value.\n", listInstance->now->data->data->word);
			return getValueFromNull();
		}
		//create new symbol table
		
		Value * ret;
		if (command->type == VList) {
			SymbolTable * saved = symbolTable;
			symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));
			symbolTable->hashMap = createHashMap();
			symbolTable->next = globalTable;
			//argu inject
			listInstance->now = listInstance->now->next;
			ListNode * param = command->data->list->node->data->data->list->node;
			while (param != NULL) {
				if (param->data->type != TLiteral) {
					//CANT EXCUTE
				}
				Value * argu = eval(listInstance);
				setSymbol(symbolTable, param->data->data->word, argu);
				param = param->next;
			}
			ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
			newInstance->now = command->data->list->node->next->data->data->list->node;
			ret = call(newInstance);
			freeSymbolTable(symbolTable);
			symbolTable = saved;
			//DestorySymbolTable
			return ret;
		}
		else {
			Function * func = command->data->function;
			listInstance->now = listInstance->now->next;
			if (func->argc == 1) {
				registerA = eval(listInstance);
			}
			else if (func->argc == 2) {
				Value *tmp = eval(listInstance);
				registerB = eval(listInstance);
				registerA = tmp;
			}
			else if (func->argc == 3) {
				Value * r1 = eval(listInstance);
				Value * r2 = eval(listInstance);
				registerC = eval(listInstance);
				registerA = r1;
				registerB = r2;
			}
			else {
				//todo::
			}
			return func->data();
		}
		
	}
	else {
		ListNode * tmp = listInstance->now;
		listInstance->now = listInstance->now->next;
		return tmp->data;
	}
}
