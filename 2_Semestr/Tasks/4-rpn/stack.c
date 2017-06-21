#include "stack.h"

struct stack* create_stack( ) {
	struct stack* new_stack = ( struct stack* ) calloc( 1, sizeof( struct stack ) );
	if ( !new_stack ) {
		return NULL;
	}
	new_stack -> size = 0;
	new_stack -> peak = NULL;
	return new_stack;
}

struct Lexem* pop( struct stack* stack ) {
	struct stack_list *out= stack -> peak;
	struct Lexem* elem;
	if( !(stack -> peak ) ) {
		return NULL;
	}
	out = stack -> peak;
	elem = out -> elem;
	stack -> peak = out -> next;
	free( out );
	( stack -> size )--;
	return elem;
}

int push( struct stack* stack, struct Lexem* elem ) {
	struct stack_list* tmp = ( struct stack_list* ) calloc( 1, sizeof( struct stack_list ) );
	if( !tmp ) {
		return -1;
	}
	tmp -> elem = elem;
	tmp -> next = stack -> peak;
	stack -> peak = tmp;
	( stack -> size )++;
	return 1;
}