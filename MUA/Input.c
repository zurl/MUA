//����ļ���������
//֧���������뷽ʽ������ʽ������ļ�����

//�ַ�����
typedef struct SBuffer{
	char *data;
	int st, ed;
}Buffer;

Buffer * getBufferFromFile() {

}
Buffer * getConsoleBuffer() {

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

TokenList * dolexicalAnalysis(Buffer * buffer) {

}