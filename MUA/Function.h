#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include "Value.h"
void initSystemFunction(void);

Value * getValueFromNumber(long long x);
Value * getValueFromReal(double x);
Value * getValueFromStr(const char * x);
Value * getValueFromNull(void);

Value * SFadd(void);
Value * SFsub(void);
Value * SFmul(void);
Value * SFdiv(void);
#endif