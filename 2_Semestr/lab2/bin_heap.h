#if !defined(BIN_HEAP)
#define BIN_HEAP

struct table_cell;

struct node {
	int key;//ключ
	struct table_cell* elem;// 
	struct node* parent;//указатель на родителя узла
	struct node* child_left;//указательна левого ребенка узла
	struct node* sibl_right;//казатель на правого брата
	int degree;//степень узла( количество дочерних узлов)
};

struct bin_heap {
	struct node* head;//указатель на корень биноминального дерева минимального порядка
};

struct node* search_node_in_bin_heap( struct node* root, struct table_cell* x );
void print_bin_heap( struct node* root );
struct bin_heap* bin_heap_create( );
struct node* bin_heap_node_init ( struct table_cell* data, int weight );
struct node* get_minimum ( struct bin_heap* heap );
struct bin_heap* bin_heap_insert( struct bin_heap* heap, struct node* elem );
struct node* extract_min( struct bin_heap** heap );
void decrease_key( struct bin_heap* heap,  struct node* elem, int value );
void bin_heap_delete( struct bin_heap* heap, struct node* elem );
void free_bin_heap ( struct bin_heap* heap );

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 5423c5eeb018f09d45ddfbc932730673bfeded96
