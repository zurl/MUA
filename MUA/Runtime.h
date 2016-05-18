#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H
#include "Value.h"
#include "Input.h"
#include "Symbol.h"
Value * eval(TokenList * tokenList);

extern SymbolTable * symbolTable;
#endif