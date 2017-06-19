#if !defined(QUEUE)
#define QUEUE

struct list_q {
	struct table_cell* x;
	struct list_q* next;
};

struct queue {
	struct list_q* tail;
	struct list_q* head;
};

struct queue* create_queue();
int add_queue ( struct queue* q, struct table_cell* elem );
struct table_cell* poll_queue( struct queue* q );
void free_queue( struct queue* q, void( func )( void* ) );

#endif
