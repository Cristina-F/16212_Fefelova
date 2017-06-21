#include "gr.h"
#include "list.h"
#include "algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VISITED 1
#define UNVISITED 0

void print_elem ( void* el ){
	struct table_cell* elem = ( struct table_cell* )el;
	printf("id = %d d = %d / ", elem -> id,  elem -> distance );
}

int read_vertex( ) {
	printf("Enter the number of the vertex: \n");
	int id  = 0;
	int ok = 0;
	while ( 1 ) {
		int count = 0;
		ok = scanf( "%d", &id );
		if ( 1 != ok ) {
			while ( '\n' != getchar( ) );
		}
		else {
			while ( '\n' != getchar( ) ) {
				count++;
			}
			if ( 0 == count ) {
				break;
			}
		}
		printf( "Enter a number \n" );
		count = 0;
	}
	return id;
}

struct table_cell* get_vertex( struct hash_table* hash_table ){
	int id = read_vertex( );
	struct table_cell* vertex = table_search( hash_table, id );
	return vertex;
}

void add_graph_to_the_heap( struct bin_heap** heap, struct hash_table* hash_table, struct table_cell* start ) {
	for ( int i = 0; i < hash_table-> size; i++ ) {
		if ( NULL !=  hash_table -> cell[i] ) {
			struct table_cell* tmp = hash_table  -> cell[i];
			while ( NULL != tmp ) { 
				int ok = 0;
				if ( start != tmp ) {
					struct list_sibl* buff = start -> siblings;
					while( buff ) {
						if ( buff -> t_cell == tmp ) { 
							ok = 1;
							struct node* data = bin_heap_node_init( tmp, INT_MAX );
							*heap = bin_heap_insert( *heap, data );
							break;
						}
						buff = buff -> next;
					}
					if ( !ok ) {
						struct node* data = bin_heap_node_init( tmp, INT_MAX ); 
						*heap = bin_heap_insert( *heap , data );
					}
				}
				tmp = tmp -> next;
			}
		}
	}
}

void relax( struct bin_heap** q, struct table_cell* u, struct table_cell* start ) {
	struct list_sibl* sibl = u -> siblings;
		while ( sibl ) {
			int edge_weight = sibl -> weight;
			if( ( sibl -> t_cell -> distance > ( ( u ->  distance ) + edge_weight ) ) && ( INT_MAX != u -> distance)) {
				sibl -> t_cell ->  distance = ( u -> distance ) + edge_weight;
				if ( VISITED ==  sibl -> t_cell -> visited ) {
					struct node* data = bin_heap_node_init( sibl -> t_cell, sibl -> t_cell ->  distance);
					*q = bin_heap_insert( *q,  data );
				}
				struct node* elem = search_node_in_bin_heap( (*q) -> head, sibl -> t_cell );
				decrease_key( (*q), elem, sibl -> t_cell -> distance );	 
				sibl -> t_cell -> parent = u;
			}
			sibl = sibl -> next;
		}
}

void print_path( struct table_cell* start, struct table_cell* finish ) {
	struct table_cell* child = finish;
	struct table_cell* pred = finish -> parent;
	struct list* way = create_list( child );

	while ( start != child) {
		if ( NULL == pred  || NULL == child){
			printf("ПУТИ НЕТ\n");
			free_list( &way );
			return;
		}
		child = child -> parent;
		pred = pred -> parent;
		
		insert_list( &way, child );
	}
	way = revers( way );
	print_list( way, print_elem );
	printf("min distance = %d\n", finish -> distance);
	free_list( &way );
}

int get_edge_weight( struct table_cell*u, struct table_cell* v ) {
	struct list_sibl* sibl = u -> siblings;
	while( sibl ) {
		if ( v == sibl -> t_cell ) {
			return sibl -> weight;
		}
		sibl = sibl -> next;
	}
	return 0;
}

void dijkstra_algorithm( struct hash_table* hash_table, struct table_cell* start, struct table_cell* finish ) {
	start -> distance = 0;
	start -> visited = VISITED;
	if ( start == finish ) {
		printf(" min_distance = 0\n" );
		return ;
	}
	struct bin_heap* q = bin_heap_create( );
	add_graph_to_the_heap( &q, hash_table, start );
	while( q -> head ) {
		struct node* min = extract_min( &q );
		struct table_cell* u = min -> elem;
		u -> distance = min -> key;
		u -> visited = VISITED;
		int edge = get_edge_weight( start, u );
		if ( edge  && edge < u -> distance ) {
			u -> distance = edge;
			u -> parent = start;
		}
		relax( &q, u, start );
		free( min );
	}
	//print_table3( hash_table );
	print_path( start, finish);
	free_bin_heap( q );
<<<<<<< HEAD
}
=======
}
>>>>>>> 5423c5eeb018f09d45ddfbc932730673bfeded96
