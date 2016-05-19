//这个文件处理输入
//支持两种输入方式：交互式输入和文件输入
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Input.h"
#include "Value.h"
//字符处理

char * copyString(const char *src) {
	char *ret = (char *)malloc(sizeof(char)*(strlen(src) + 1));
	strcpy(ret, src);
	return ret;
}

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
	buffer->data = (char *)(malloc(sizeof(char) * (size+1)));
	fseek(file, 0L, 0);
	while ((buffer->data[buffer->ed] = (char)fgetc(file)) != EOF)buffer->ed++;
	buffer->data[buffer->ed] = '\n';
	fclose(file);
	return buffer;
}
Buffer * getBufferFromConsole() {
	Buffer * buffer = malloc(sizeof(Buffer));
	buffer->st = 0;
	buffer->ed = 0;
	buffer->data = (char *)(malloc(sizeof(char) * 1024));
	while((buffer->data[buffer->ed] = (char)getchar()) != '\n')buffer->ed++;
	return buffer;
}
//词法分析

int isNum(char x) {
	return x >= '0' && x <= '9';
}
int isLetter(char x) {
	return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
}
void copyChar(char *dest,char *src,int length) {
	for (int i = 0; i <= length - 1; i++)
		*(dest + i) = *(src + i);
	*(dest + length) = 0;
}

TokenList * getTokenListFromBuffer(Buffer * buffer) {
	TokenList * tokenList = (TokenList *)malloc(sizeof(TokenList));
	Token * node = (Token * )malloc(sizeof(Token));
	node->type = TLSB;
	char * cache = (char *)malloc(sizeof(char) * 256);
	int now = 0,st = 0;
	while (buffer->st <= buffer->ed) {
		char c = buffer->data[buffer->st];
		if (c == ' ' || c== '\n' ) {
			if (now != 0) {
				node->data = (char *)malloc(sizeof(char) * (now + 1));
				if (node->type == TNumber || node->type == TWord)
					copyChar(node->data, buffer->data + st, now);
				if (node->type == TLiteral)
					copyChar(node->data, buffer->data + st + 1, now - 1);
				now = 0;
			}
			buffer->st++;
			continue;
		}
		if (now == 0) {
			Token * token = (Token *)malloc(sizeof(Token));
			token->next = node;
			node = token;
			st = buffer->st;
			if (c == '\'') {
				token->type = TLiteral;
			}
			else if (isNum(c) || c== '-') {
				token->type = TNumber;
			}
			else if (isLetter(c)) {
				token->type = TWord;
			}
			else if (c == '[') {
				token->type = TLSB;
				buffer->st++;
				now = 0;
				continue;
			}
			else if (c == ']') {
				token->type = TRSB;
				now = 0;
				buffer->st++;
				continue;
			}
			else {
				//TODO:: BUG?
			}
		}
		if (node->type == TNumber && (!isNum(c) && c != '.')) {
			//TODO::BUG?
		}
		now++;
		buffer->st++;
	}
	free(cache);
	Token * tmp = (Token *)malloc(sizeof(Token));
	tmp->type = TRSB;
	tmp->next = node;
	tokenList->st = tokenList->now = tmp;
	return tokenList;
}

//语法分析

List * getListFromTokenList(TokenList * tokenList) {
	if (tokenList->now->type != TRSB) {
		//TODO::
	}
	tokenList->now = tokenList->now->next;
	ListNode * listNode = (ListNode *)malloc(sizeof(ListNode));
	listNode->next = NULL;
	while (tokenList->now != NULL && tokenList->now->type != TLSB) {
		if (tokenList->now->type == TRSB) {
			listNode->data = (Value *)malloc(sizeof(Value));
			listNode->data->data = (ValueData *)malloc(sizeof(ValueData));
			listNode->data->type = VList;
			listNode->data->data->list = getListFromTokenList(tokenList);
		}
		else {
			listNode->data = createValue(tokenList->now);
		}
		ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
		tmp->next = listNode;
		listNode = tmp;
		tokenList->now = tokenList->now->next;
	}
	if (tokenList->now == NULL) {
		//TODO ::
	}
	List * list = (List *)malloc(sizeof(List));
	list->node = listNode->next;
	return list;
}
