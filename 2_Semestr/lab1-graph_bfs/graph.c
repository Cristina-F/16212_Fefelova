#include "queue.h"
#include "graph.h"
#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VISITED 1
#define UNVISITED 0
#define MAX_LENGTH 30


static char* itoa( int n ) {
	int size = 0;
	int num = n;
	while( 0 != num ) {
		num /= 10;
		size++;
	}
	if ( 0 == n ) {
		size = 1;
	}
	char* out = ( char* )calloc( size + 1, sizeof( char ) );
	for( int i = ( size - 1 ); i >= 0; i-- ) {
		out[i] = '0' + (n % 10);
		n %= 10;
	}
	return out;
}

void add_siblings( struct hash_table* hash_table, char* actual_name, char* sibl ) {
	struct list* new_elem = ( struct list* )calloc( 1, sizeof( struct list ) );
	struct table_cell* elem1 = table_search( hash_table, actual_name );
	struct table_cell* elem2 = table_search( hash_table, sibl );
	new_elem -> t_cell = elem2; 
	(new_elem -> t_cell -> num_siblings)++;
	struct list* buff = elem1 -> siblings;
	elem1 -> siblings = new_elem;
	elem1 -> siblings -> next = buff;
}

//Добавляем вершины графа
struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file  ) {
	int id_node1 = 0;
	int id_node2 = 0;
	int ok = 0;
	int count_elem = 0;
	while( ok != EOF ) {
		ok = fscanf( in_file, "%d%d", &id_node1, &id_node2 );
		if ( 2 == ok ) {
			char* id1 = itoa( id_node1 );
			char* id2 = itoa( id_node2 );
			if ( !check_id( hash_table, id1) ) {
				hash_table = write_in_table( hash_table, id1, ++count_elem );
			}
			if ( !check_id( hash_table, id2) ) {
				hash_table = write_in_table( hash_table, id2, ++count_elem );
			}
			add_siblings(hash_table, id1, id2);
			add_siblings( hash_table, id2, id1);
			free( id1 );
			free( id2 );
		}
	}
	return hash_table; 
}
static int check_name( char* name ) {
	for( int i = 0; '\0' != name[i]; i++ ) {
		if ( i > MAX_LENGTH ) {
			return -1;
		}
	}
	return 0;
}

static char* read_name ( char* name ) {
	int num = 0;
	while (1) {
		num = scanf( "%s", name );
		if ( ( 1 != num ) ) {
			while ( '\n' != getchar( ) );
		}
		else if ( -1 == check_name( name ) ){
			while ( '\n' != getchar( ) );
		}
		else {
			break;
		}
		printf( "\n" );
	}
	return name;
}
//Обход графа в ширину
int bfs( struct hash_table* hash_table ) {
	printf("Введите номер вершины, с которой начать обход: \n");
	char* id = ( char* )calloc( MAX_LENGTH, sizeof( char ) );
	id = read_name( id );
	struct table_cell* start = table_search( hash_table,  id );
	if ( NULL == start ) {
		printf("Вершина не найдена\n");
		free( id );
		return -1;
	}
	start -> visited = VISITED;
	start -> distance = 0;
	struct queue* q = create_queue( );
	add_queue( q, start -> id );
	while(	q -> head ){
		struct table_cell* tmp = table_search( hash_table, q -> head -> x );
		struct list* tmp1 = tmp -> siblings;
		printf("%s ", tmp -> id);
		while( tmp1 ){
			struct table_cell* new_node = table_search(hash_table, tmp1 -> t_cell -> id );
			if ( UNVISITED == ( new_node -> visited ) ) {
				add_queue( q, new_node -> id );
				new_node -> visited = VISITED;
				new_node -> distance = ( tmp -> distance ) + 1;
			}
			tmp1 = tmp1 -> next;
		}
		tmp -> visited = VISITED;
		poll_queue( q );
	}
	free( q );
	free( id );
	printf( "\n" );
	return 0;
}

