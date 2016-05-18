#include "Function.h"
#include "Runtime.h"

typedef long long(*IntHandeler)(long long, long long);
typedef double(*RealHandeler)(double, double);

Value * abstractCalculate(IntHandeler i, RealHandeler r) {// $x,$y
	if (registerA->type == VInteger && registerB->type == VInteger) {
		return getValueFromNumber(i(registerA->data->integer, registerB->data->integer));
	}
	else if (registerA->type == VInteger && registerB->type == VReal) {
		return getValueFromReal(r(registerA->data->integer, registerB->data->real));
	}
	else if (registerA->type == VReal && registerB->type == VInteger) {
		return getValueFromReal(r(registerA->data->real, registerB->data->integer));
	}
	else if (registerA->type == VReal && registerB->type == VReal) {
		return getValueFromReal(r(registerA->data->real, registerB->data->real));
	}
	else {
		//TODO:err;
	}
}
/* ADD */
inline long long SFaddI(long long a, long long b) {
	return a + b;
}
inline double SFaddD(double a, double b) {
	return a + b;
}
Value * SFadd() {
	return abstractCalculate(SFaddI, SFaddD);
}
/* SUB */
inline long long SFsubI(long long a, long long b) {
	return a - b;
}
inline double SFsubD(double a, double b) {
	return a - b;
}
Value * SFsub() {
	return abstractCalculate(SFsubI, SFsubD);
}
/* MUL */
inline long long SFmulI(long long a, long long b) {
	return a * b;
}
inline double SFmulD(double a, double b) {
	return a * b;
}
Value * SFmul() {
	return abstractCalculate(SFmulI, SFmulD);
}
/* DIV */

inline long long SFdivI(long long a, long long b) {
	return a / b;
}
inline double SFdivD(double a, double b) {
	return a / b;
}
Value * SFdiv() {
	return abstractCalculate(SFdivI, SFdivD);
}