#if !defined(LIST)
#define LIST

struct list {
	void* elem;
	struct list* next;
};

struct list* create_list ( void* data );
struct list* find_last( struct list* head );
void insert_list( struct list** head, void* data );
int list_length( struct list* head );
struct list* get_node( struct list* head, int n );
void delete_node_by_number( struct list** head, int n );
void delete_node( struct list** head, struct list* node);
void free_list( struct list** head );
void print_list ( struct list* head, void( func_print )( void* ) );
struct list* revers( struct list* head );
#endif
