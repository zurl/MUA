#include "Input.h"

int main(int argc,char * argv) {
	//��������ģʽ
	int mode = 0;
	if (argc == 0)mode = 1;
	//����Buffer
	if (mode == 1) {
		
	}
	else {
		Buffer * buffer = getBufferFromFile("D:\\DataBase\\MUA\\MUA\\test.mua");
		TokenList * tokenList = getTokenListFromBuffer(buffer);
		List * list = getListFromTokenList(tokenList);
		return 0;
	}
	return 0;
}