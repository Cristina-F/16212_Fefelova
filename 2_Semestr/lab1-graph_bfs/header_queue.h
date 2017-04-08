#if !defined(QUEUE)

#include <stdio.h>
#include <stdlib.h>

#define QUEUE

struct list_q {
	char* x;
	struct list_q* next;
};

struct queue {
	struct list_q* tail;
	struct list_q* head;
};

struct queue* create_queue();
int add_queue ( struct queue* q, char* index );
void poll_queue( struct queue* q );

#endif
