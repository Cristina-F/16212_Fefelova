#include "header_queue.h"

struct queue* create_queue( ) {
	struct queue* new_queue = ( struct queue* )calloc( 1, sizeof( struct queue ) );
	if ( !new_queue ) {
		return NULL;
	}
	new_queue -> tail = NULL;
	new_queue -> head = NULL;
	return new_queue;
}

int add_queue ( struct queue* q, char* index ) {
	struct list_q* tmp = ( struct list_q* )calloc( 1, sizeof( struct list_q ) );
	if ( !tmp ) {
		return -1;
	}
	if ( !( q -> head ) ){
		q -> head = tmp;
		q -> tail = q -> head;

	} 
	else {
		q -> tail -> next = tmp;
		q -> tail = tmp;
	}
	q -> tail -> x = index;
	return 0;
}
 
void poll_queue( struct queue* q ) {
	struct list_q* buff = q -> head;
	q -> head = q -> head -> next;
	free( buff );
}
