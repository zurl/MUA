MUA : Main.o Arithmetic.o Function.o HashMap.o Input.o Value.o Symbol.o Runtime.o 
cc -o MUA Main.o Arithmetic.o Function.o HashMap.o Input.o Value.o Symbol.o Runtime.o
Main.o : Main.c Input.h Runtime.h Function.h
cc -c Main.c 
Arithmetic.o : Arithmetic.c Function.h Runtime.h
cc -c Arithmetic.c
Function.o : Function.c Value.h Runtime.h Symbol.h Function.h
cc -c Function.c
HashMap.o : HaspMap.c Value.h HashMap.h Input.h
cc -c HashMap.o
Input.o : Input.c Input.h Value.h
cc -c Input.c
Value.o : Value.c Input.h
cc -c Value.c
Symbol.o : Symbol.c HashMap.h Symbol.h
cc -c Symbol.c
Runtime.o : Runtime.c Value.h Input.h Symbol.h Runtime.h
cc -c Runtime.o

