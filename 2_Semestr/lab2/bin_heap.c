#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#include "bin_heap.h"
#include "ht.h"

//создание кучи
struct bin_heap* bin_heap_create( ) {
	struct bin_heap* new_heap = ( struct bin_heap* )calloc( 1, sizeof( struct bin_heap ) );
	new_heap -> head = NULL;
	return new_heap;
}

//иницилизация узла кучи
struct node* bin_heap_node_init ( struct table_cell* data, int weight ) {
	struct node* new_elem = ( struct node* )calloc( 1, sizeof( struct node ) );
	new_elem -> key = weight;
	new_elem -> elem = data;
	new_elem -> degree = 0;
	return new_elem;
}

//поиск минимального узла
struct node* get_minimum ( struct bin_heap* heap ) {
	if ( NULL == heap || NULL == heap -> head ) {
		return NULL;
	}
	struct node* min = heap -> head;
	struct node* root = heap -> head;
	while( root ) {
		if (root -> key < min -> key ) {
			min = root;
		}
		root = root -> sibl_right;
	}
	return min;
}

//поиск узла в кучу
struct node* search_node_in_bin_heap( struct node* root, struct table_cell* x ) {
	struct node* found = NULL;
		if ( root ) { 
			if ( root -> elem == x ) {
				return root;
			}
			if ( root -> sibl_right && !found ) {
				found = search_node_in_bin_heap( root -> sibl_right, x);
			}
			if ( root -> child_left && !found ) {
				found = search_node_in_bin_heap( root -> child_left, x);
			} 
		}
		return found;		
}

//слияние списка корней двх куч
static struct node* heap_merge( struct node* root1, struct node* root2 ) {
	struct node* result = NULL;
	if ( root1 -> degree <= root1 -> degree ) {
		result = root1;
		root1 = root1 -> sibl_right;
	}
	else {
		result = root2;
		root2 = root2 -> sibl_right;
	}
	struct node* tmp = result;
	while ( root1 && root2 ) {
		if ( root1 -> degree <= root2 -> degree ) {
			tmp -> sibl_right = root1;
			tmp = root1;
			root1 = root1 -> sibl_right;
		}
		else {
			tmp -> sibl_right = root2;
			tmp = root2;
			root2 = root2 -> sibl_right;
		}
	}
	if ( root1 ) {
		tmp -> sibl_right = root1;
	}
	else {
		tmp -> sibl_right = root2;
	}
	return result;
}

//связывает два узла
static void heap_link( struct node* root, struct node* child ) {
	child -> parent = root;
	child -> sibl_right = root -> child_left;
	root -> child_left = child;
	( root -> degree )++;
}

//объединение куч
static struct bin_heap* union_bin(  struct bin_heap* h1, struct bin_heap* h2 ) {
	if ( NULL == h1 -> head ) {
		free( h1 );
		return h2;
	}
	if ( NULL == h2 -> head ) {
		free( h2 );
		return h1;
	}
	struct bin_heap* new_heap = bin_heap_create( );
	new_heap -> head  = heap_merge ( h1 -> head, h2 -> head );
	free( h1 );
	free( h2 );
	struct node* prev = NULL;
	struct node* x = new_heap -> head;
	struct node* next = x -> sibl_right;
	while( NULL != next ) {
		if ( x -> degree != next -> degree || ( next -> sibl_right && x -> degree == next -> sibl_right -> degree ) ) {
			prev = x;
			x = next;
		}
		else if ( x -> key <= next -> key ) {
			x -> sibl_right = next -> sibl_right;
			heap_link( x, next );
		}
		else {
			if ( prev ) {
				prev -> sibl_right = next;
			}
			else {
				new_heap -> head = next;
			}
			heap_link(  next,  x );
			x = next;
		}
		next = x -> sibl_right;
	}
	return new_heap;
}

//вставка элемента в кучу
struct bin_heap* bin_heap_insert( struct bin_heap* heap, struct node* elem ) {
	struct bin_heap* tmp = bin_heap_create();
	tmp -> head = elem;
	return union_bin( heap, tmp );
}

static struct node* revers( struct node* head ) {
	struct node* new_head = NULL;
	struct node* pos = head;
	while( pos ) {
		struct node* save_next = pos -> sibl_right;
		pos -> sibl_right = new_head;
		new_head = pos;
		pos = save_next; 
	}
	return new_head;
}

//извлечение минимального элемента
struct node* extract_min( struct bin_heap** heap ) {
	struct node* min = (*heap) -> head;
	struct node* min_before = NULL;
	struct node* cur_min = (*heap) -> head;
	struct node* cur_min_before = NULL;
	// Ищем минимальный элемент и предыдущий
	while ( NULL != cur_min ) {
		if ( cur_min -> key < min -> key ) {
			min = cur_min;
			min_before = cur_min_before;
		}
		cur_min_before = cur_min;
		cur_min = cur_min -> sibl_right;
	}
	// удаляем min изи списка корней
	if ( NULL == min_before ) {
		(*heap) -> head = min -> sibl_right;
	}
	else {
		min_before -> sibl_right = min -> sibl_right;
	}

	struct bin_heap* heap_tmp = bin_heap_create( );
	cur_min = min -> child_left;
	heap_tmp -> head = min -> child_left;
	while ( NULL != cur_min ) {
		cur_min -> parent = NULL;
		cur_min = cur_min -> sibl_right;
	}
	heap_tmp -> head = revers( heap_tmp -> head );
	(*heap ) = union_bin((*heap), heap_tmp );
	return min;
}

//обмен узлов значениями
static void swap_value( struct node** x,  struct node** y ) {
	int buff = (*x) -> key;
	struct table_cell* tmp = (*x) -> elem ;
	(*x) -> key = (*y) -> key;
	(*x) -> elem = (*y) -> elem;
	(*y) -> key = buff;
	(*y) -> elem = tmp;
}

//уменьшение ключа
void decrease_key( struct bin_heap* heap,  struct node* elem, int value ) {
	if ( value > ( elem -> key ) ) {
		return ;
	}
	elem -> key = value;
	struct node* tmp1 = elem;
	struct node* tmp2 = elem -> parent;
	while ( NULL != tmp2 && tmp1 -> key < tmp2 -> key ) {
		swap_value( &tmp1, &tmp2 );
		tmp1 = tmp2;
		tmp2 = tmp1 -> parent;
	}
}

//удаление элемента из кучи
void bin_heap_delete( struct bin_heap* heap, struct node* elem ) {
	decrease_key( heap, elem, INT_MIN );
	extract_min( &heap );
}

//печать биномиальной кучи
void print_bin_heap( struct node* root ) {
	struct node* tmp = root;
	while( tmp ) {
		printf("%d %d\n",tmp -> elem -> id, tmp -> key );
		if ( tmp -> child_left ) {
			print_bin_heap( tmp -> child_left);
		}
		tmp = tmp -> sibl_right;
	}
}

static void free_roots ( struct node* root ) {
	if ( root ) {
		if ( root -> sibl_right ) {
			free_roots( root -> sibl_right );
		}
		if ( root -> child_left ) {
			free_roots( root -> child_left );
		}
		free( root );
	}
}

void free_bin_heap ( struct bin_heap* heap ) {
	free_roots( ( heap ) -> head );
	free( heap );
}
