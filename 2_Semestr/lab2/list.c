#include <stdio.h>
#include <stdlib.h>

#include "list.h"

//создание списка
struct list* create_list ( void* data ) {
	struct list* new_node = ( struct list* )calloc( 1, sizeof( struct list ) );
	new_node -> elem = data;
	new_node -> next = NULL;
	return new_node;
}

//поиск последнего элемента списка
struct list* find_last( struct list* head ) {
	while ( head -> next ){
		head = head -> next;
	}
	return head;
}

//вставка элемента в список
void insert_list( struct list** head, void* data ) {
	if ( NULL == ( *head ) ) {
		*head = create_list( data );
	}
	else { 
		struct list* last = find_last( *head );
		struct list* new_node = create_list( data ) ;
		last -> next = new_node;
	}
}

//Вычисление длинны списка
int list_length( struct list* head ) {
	int len = 0;
	while ( head ) {
		len++;
		head = head -> next;
	}
	return len;
}

//Поиск узла по номеру
struct list* get_node( struct list* head, int n ) {
	int count = 0;
	while ( count < n ) {
		if ( head -> next ) {
			head = head -> next;
		}
		count++;
	}
	return head;
}

//удаление узла по номеру
void delete_node_by_number( struct list** head, int n ) {
	if ( 0 == n ) {
		struct list* node = NULL;
		node = ( *head );
		( *head ) = ( *head ) -> next;
		free( node );
	}
	else {
		struct list* prev = get_node( *head, n - 1 );
		struct list* elem = prev -> next;

		prev -> next = elem -> next;
		free( elem );
	}
}

//удаление узла
void delete_node( struct list** head, struct list* node) {
	if ( node == *head ) {
		struct list* buf = NULL;
		node = ( *head );
		( *head ) = ( *head ) -> next;
		free( node );
	}
	else {
		struct list* buf = *head;
		while ( node != buf -> next ) {
			buf = buf -> next;
		}
		buf -> next = node -> next;
		free( node );
	}
}

//очищение списка
void free_list( struct list** head ) {
	struct list* prev = NULL;
	if ( NULL == *head ) {
		return;
	}
	while ( ( *head ) -> next ) {
		prev = ( *head );
		( *head ) = ( *head ) -> next;
		free( prev );
	}
	free( *head );
}

void print_list ( struct list* head, void( func_print )( void* ) ) {
	while( head ) {
		func_print( head -> elem );
		head = head -> next;
	}
	printf("\n");
}

struct list* revers( struct list* head ) {
	struct list* new_head = NULL;
	struct list* pos = head;
	while( pos ) {
		struct list* save_next = pos -> next;
		pos -> next = new_head;
		new_head = pos;
		pos = save_next; 
	}
	return new_head;
}