#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include "Value.h"

typedef struct SSysFunc {
	char * name;
	FunctionData func;
	int argc;
}SysFunc;

void initSystemFunction(void);
void initGlobalFunction(void);

/*Arithmetic.c*/
Value * SFtest(void);
Value * SFiftrue(void);
Value * SFiffalse(void);
Value * SFtrue(void);
Value * SFfalse(void);
Value * SFadd(void);
Value * SFsub(void);
Value * SFmul(void);
Value * SFdiv(void);
Value * SFislist(void);
Value * SFisword(void);
Value * SFisnumber(void);
Value * SFisbool(void);
Value * SFisempty(void);
Value * SFfirst(void);
Value * SFlast(void);
Value * SFbutfirst(void);
Value * SFbutlast(void);
Value * SFword(void);
Value * SFlist(void);
Value * SFjoin(void);
Value * SFnot(void);
Value * SFand(void);
Value * SFor(void);
Value * SFrandom(void);
Value * SFsqrt(void);
Value * SFitem(void);
Value * SFeq(void);
Value * SFgt(void);
Value * SFlt(void);
Value * SFmod(void);
#endif