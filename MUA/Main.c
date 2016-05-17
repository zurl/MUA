#include "Input.h"

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
		eval();
	}
	return 0;
}