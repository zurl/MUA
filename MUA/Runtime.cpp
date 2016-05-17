//这个文件负责解释程序
#include "Value.h"
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
Value * eval(TokenList * tokenList) {
	Token * token = tokenList->now;
	tokenList->now = tokenList->now->next;
	if (token == NULL) {
		//TODO ::bug?
	}
	else if (token->type == TWord) {

	}
	else if (token->type == TLSB) {
		ListNode * now = (ListNode *)malloc(sizeof(ListNode));
		now->next = NULL;
		now->data = NULL;
		while (tokenList->now->type != TRSB) {
			now->data = eval(tokenList);
			ListNode * tmp = (ListNode *)malloc(sizeof(ListNode));
			tmp->next = now;
			now = tmp;
		}
	}
	else {
		return createValue(token);
	}
}
