#if !defined(PRIORITY_QUEUE)
#define PRIORITY_QUEUE

struct tree;

struct list_q {
	struct tree* x;
	long long int priority;
	struct list_q* next;

};

struct priority_queue {
	int size;
	struct list_q* tail;
	struct list_q* head;
};

struct priority_queue* create_queue( );
void add_priority_queue(struct priority_queue* q, struct tree* data, long long int priority );
struct tree* poll_priority_queue( struct priority_queue* q );
struct tree* peek ( struct priority_queue* q );
void print_queue ( struct priority_queue* q );
#endif
