#include "priority_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include "haf.h"

struct priority_queue* create_queue( ) {
	struct priority_queue* new_queue = ( struct priority_queue* )calloc( 1, sizeof( struct priority_queue ) );
	if ( !new_queue ) {
		return NULL;
	}
	new_queue -> tail = NULL;
	new_queue -> head = NULL;
	return new_queue;
}

void add_priority_queue( struct priority_queue* q, struct tree* data, long long int priority ) {
	struct list_q* tmp = ( struct list_q* )calloc( 1, sizeof( struct list_q ) );
	tmp -> x = data;
	tmp -> priority = priority;
	if ( NULL == q -> head ) {
		q -> head = tmp;
		q -> tail = q -> head;
		return;
	}
	struct list_q* current = q -> head;
	struct list_q* prev = NULL;
	int adder = 0;
	while ( !adder && NULL != current ) {
		if ( tmp -> priority < current -> priority ) {
			if ( NULL == prev ) {
				tmp -> next = current;
				q -> head = tmp;
				adder =1;
			}
			else {
				tmp -> next = current;
				prev -> next = tmp;
				adder = 1;
			}
		}
		prev = current;
		current = current -> next; 
	}
	if ( !adder ) {
		q -> tail -> next = tmp;
		q -> tail = tmp;
	} 
	(q -> size)++;

}

struct tree* poll_priority_queue( struct priority_queue* q ) {
	struct list_q* tmp = q -> head;
	if ( NULL == q -> head ) {
		printf("??????\n");
		return NULL;
	}
	(q -> size)--;
	struct tree* ret = q -> head -> x;
	//printf("p = %lld\n",q -> head -> priority );
	//printf("%lld\n",ret -> frequency );
	q -> head = q -> head -> next;
	free( tmp );
	//printf("%lld\n",ret -> frequency );
	return ret;
}

struct tree* peek ( struct priority_queue* q ) {
	return q -> head -> x;
}
void print_queue ( struct priority_queue* q ) {
	struct list_q* tmp = q -> head;
	while( NULL != tmp ) {
		//printf("%d %d\n", tmp -> x -> type, tmp -> priority);
		tmp = tmp -> next;
	}
}