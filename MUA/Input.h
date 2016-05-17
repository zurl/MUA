#pragma once
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

Buffer * getBufferFromConsole(void);
Buffer * getBufferFromFile(char * fileName);
TokenList * getTokenListFromBuffer(Buffer * buffer);

char * copyString(const char *src);