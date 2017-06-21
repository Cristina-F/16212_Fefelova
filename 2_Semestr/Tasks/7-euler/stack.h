#if !defined(STACK)
#define STACK

#include <stdio.h>
#include <stdlib.h>

struct stack {
	int size;
	struct stack_list* peak;
};

struct stack_list {
	struct node* elem;
	struct stack_list* next;
};

struct stack* create_stack( );
struct node* pop( struct stack* stack );
int push( struct stack* stack, struct node* elem );

#endif