//这个文件处理输入
//支持两种输入方式：交互式输入和文件输入

//字符处理
typedef struct SBuffer{
	char *data;
	int st, ed;
}Buffer;

Buffer * getBufferFromFile() {

}
Buffer * getConsoleBuffer() {

}
//词法分析
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

TokenList * dolexicalAnalysis(Buffer * buffer) {

}