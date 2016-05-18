#pragma once
#ifndef INPUT_H  
#define INPUT_H  
#include "Value.h"
typedef struct SBuffer {
	char *data;
	int st, ed;
}Buffer;

typedef enum ETokenType {
	TNumber, TWord, TLiteral,
	TLSB, TRSB
}TokenType;

typedef struct SToken {
	TokenType type;
	char * data;
	struct SToken * next;
}Token;

typedef struct STokenList {
	Token * st;
	Token * now;
}TokenList;

Value * createValue(const Token * token);
Buffer * getBufferFromConsole(void);
Buffer * getBufferFromFile(char * fileName);
TokenList * getTokenListFromBuffer(Buffer * buffer);
List * getListFromTokenList(TokenList * tokenList);

char * copyString(const char *src);

#endif