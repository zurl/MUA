//����ļ���������
//֧���������뷽ʽ������ʽ������ļ�����
#include<stdio.h>
#include<stdlib.h>
//�ַ�����
typedef struct SBuffer{
	char *data;
	int st, ed;
}Buffer;

Buffer * getBufferFromFile(char * fileName) {
	FILE * file = fopen(fileName, "r");
	if (file == NULL) {
		printf("File cannot be opened/n");
		return NULL;
	}
	Buffer * buffer = malloc(sizeof(Buffer));
	buffer->st = 0;
	buffer->ed = 0;
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	buffer->data = (char *)(malloc(sizeof(char) * size));
	while ((buffer->data[buffer->ed] = fgetchar(file)) != EOF)buffer->ed++;
	buffer->ed--;
	fclose(file);
	return buffer;
}
Buffer * getBufferFromConsole() {
	Buffer * buffer = malloc(sizeof(Buffer));
	buffer->st = 0;
	buffer->ed = 0;
	buffer->data = (char *)(malloc(sizeof(char) * 1024));
	while((buffer->data[buffer->ed] = getchar()) != '\n')buffer->ed++;
	buffer->ed--;
	return buffer;
}
//�ʷ�����
typedef enum ETokenType{
	TNumber,TWord,TLiteral,
	TLSB,TRSB
}TokenType;

typedef struct SToken {
	TokenType type;
	char * begin;
	int len;
}Token;

typedef struct STokenList {
	Token * token;
	int len;
}TokenList;

TokenList * doLexicalAnalysis(Buffer * buffer) {

}