#include<stdio.h>


int main(int argc,char * argv) {
	//决定交互模式
	int mode = 0;
	if (argc == 0)mode = 1;
	//读入Buffer
	if (mode == 0) {
		
	}
	else {
		Buffer buffer = getBufferFromFile(argv[0]);
	}
}