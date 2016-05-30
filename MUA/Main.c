#include "Input.h"
#include "Runtime.h"
#include "Function.h"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
int main(int argc,char ** argv) {
	srand((unsigned)time(NULL));
	initSystemSymbolTable();
	initSystemFunction();
	initGlobalSymbolTable();
	initGlobalFunction();
	globalTable = symbolTable;
	if (argc == 1) {
		printf("MUA Interpreter v1.0.0 stable by Zhang Chengyi\n");
		while (1) {
			printf("MUA>");
			Buffer * buffer = getBufferFromConsole();
			TokenList * tokenList = getTokenListFromBuffer(buffer);
			List * list = getListFromTokenList(tokenList);
			ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
			newInstance->now = list->node;
			while (newInstance->now != NULL) {
				Value * ret = eval(newInstance);
				printf("\n>>>");
				printValue(ret);
				printf("\n");
			}
		}
	}
	else {
		Buffer * buffer = getBufferFromFile(argv[0]);
		TokenList * tokenList = getTokenListFromBuffer(buffer);
		List * list = getListFromTokenList(tokenList);
		ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
		newInstance->now = list->node;
		call(newInstance);
	}	
	return 0;
}