#include "Input.h"
#include "Runtime.h"
#include "Function.h"
#include <stdlib.h>

int main(int argc,char * argv) {
	//决定交互模式
	int mode = 0;
	if (argc == 0)mode = 1;
	//读入Buffer
	if (mode == 1) {
		
	}
	else {
		Buffer * buffer = getBufferFromFile("D:\\DataBase\\MUA\\MUA\\test.mua");
		TokenList * tokenList = getTokenListFromBuffer(buffer);
		List * list = getListFromTokenList(tokenList);
		ListInstance * newInstance = (ListInstance *)malloc(sizeof(ListInstance));
		newInstance->now = list->node;
		initSystemSymbolTable();
		initSystemFunction();
		initGlobalSymbolTable();
		call(newInstance);

		return 0;
	}
	return 0;
}