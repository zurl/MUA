#include<stdio.h>


int main(int argc,char * argv) {
	//��������ģʽ
	int mode = 0;
	if (argc == 0)mode = 1;
	//����Buffer
	if (mode == 0) {
		
	}
	else {
		Buffer buffer = getBufferFromFile(argv[0]);
	}
}