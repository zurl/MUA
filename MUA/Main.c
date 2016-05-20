#include "Input.h"
#include "Runtime.h"
#include "Function.h"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
int main(int argc,char * argv) {

	srand((unsigned)time(NULL));
	Buffer * buffer = getBufferFromFile("test.mua");
	TokenList * tokenList = getTokenListFromBuffer(buffer);
	List * list = getListFromTokenList(tokenList);
	ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
	newInstance->now = list->node;
	initSystemSymbolTable();
	initSystemFunction();
	initGlobalSymbolTable();
	initGlobalFunction();
	globalTable = symbolTable;
	call(newInstance);
	return 0;
}