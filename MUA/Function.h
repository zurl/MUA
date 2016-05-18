#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include "Value.h"
void initSystemFunction(void);



Value * SFadd(void);
Value * SFsub(void);
Value * SFmul(void);
Value * SFdiv(void);
#endif