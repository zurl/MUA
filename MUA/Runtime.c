//这个文件负责解释程序
#include "Value.h"
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include "Symbol.h"

SymbolTable * symbolTable;

void initGlobalSymbolTable(){

}

typedef struct SListInstance {
	ListNode * now;
}ListInstance;

Value * call(ListInstance * listInstance) {
	
}
Value * eval(ListInstance * listInstance) {
	if (listInstance->now == NULL) {

	}
	if (listInstance->now->data->type == VWord) {
		Value *command = getSymbol(symbolTable, listInstance->now->data->data->word);
		if (command == NULL || command->type != VList
			||command->data->list->node->data->type!=VList
			||(command->data->list->node->next->data->type != VList
				&&command->data->list->node->next->data->type != VFunction)) {
			//CANT EXCUTE
		}
		//create new symbol table
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
		Value * ret;
		if (command->data->list->node->next->data->type == VList) {
			ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
			newInstance->now = command->data->list->node->next->data->data->list;
			ret = call(newInstance);
		}
		else {

		}
		//DestorySymbolTable
		tmp = symbolTable;
		symbolTable = symbolTable->next;
		freeSymbolTable(tmp);
		return ret;
	}
	else {
		ListNode * tmp = listInstance->now;
		listInstance->now = listInstance->now->next;
		return tmp->data;
	}
}
