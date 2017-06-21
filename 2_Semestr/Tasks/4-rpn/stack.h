#if !defined(STACK)
#define STACK

#include <stdio.h>
#include <stdlib.h>

struct stack {
	int size;
	struct stack_list* peak;
};

struct stack_list {
	struct Lexem* elem;
	struct stack_list* next;
};

struct stack* create_stack( );
struct Lexem* pop( struct stack* stack );
int push( struct stack* stack, struct Lexem* elem );

#endif