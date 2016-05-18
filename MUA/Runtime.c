//这个文件负责解释程序
#include "Value.h"
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include "Symbol.h"
#include "Runtime.h"

SymbolTable * symbolTable;
Value * registerA;
Value * registerB;

void initGlobalSymbolTable(){
	symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));
	symbolTable->hashMap = createHashMap();
	symbolTable->next = NULL;
}


Value * call(ListInstance * listInstance) {
	while (listInstance->now != NULL)
		eval(listInstance);
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
			printf("cant call var");
			return NULL;
		}
		//create new symbol table
		
		Value * ret;
		if (command->data->list->node->next->data->type == VList) {
			SymbolTable * tmp = (SymbolTable *)malloc(sizeof(SymbolTable));
			tmp->hashMap = createHashMap();
			tmp->next = symbolTable;
			symbolTable = tmp;
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
			tmp = symbolTable;
			symbolTable = symbolTable->next;
			freeSymbolTable(tmp);
		}
		else {
			Function * func = command->data->list->node->next->data->data->function;
			if (func->argc == 1) {
				registerA = eval(listInstance);
			}
			else if (func->argc == 2) {
				registerA = eval(listInstance);
				registerB = eval(listInstance);
			}
			else {
				//future
			}
			return func->data();
		}
		//DestorySymbolTable
		return ret;
	}
	else {
		ListNode * tmp = listInstance->now;
		listInstance->now = listInstance->now->next;
		return tmp->data;
	}
}
