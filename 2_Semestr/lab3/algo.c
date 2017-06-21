#include "gr.h"
#include "algo.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int read_vertex( ) {
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

static void print_table_flow ( struct hash_table* table ) {
		for ( int k = 0; k < table -> size; k++ ) {
		if ( NULL != table -> cell[k] ) {
			struct table_cell* tmp = table -> cell[k];
			while ( NULL != tmp ) {
				struct list_sibl* sibl = tmp -> siblings;
				while( sibl ){
					printf("(%d, %d)  flow = %d weight = %d;\n", tmp -> id, sibl -> t_cell -> id, sibl -> flow, sibl -> weight);
					sibl = sibl -> next;
				}
				
				tmp = tmp -> next;
			}
		}
	}
}

static void unvisited_graph ( struct hash_table* table ) {
	for ( int i = 0; i < table -> size; i++ ) {
		if ( NULL != table -> cell[i] ) {
			struct table_cell* tmp = table -> cell[i];
			while ( NULL != tmp ) {
				struct list_sibl* sibl = tmp -> siblings;
				tmp -> visited = UNVISITED;
				tmp -> parent = NULL;
				tmp = tmp -> next;
			}
		}
	}
}

static int bfs(struct hash_table* table, struct table_cell* s, struct table_cell* t) {
	unvisited_graph( table );
	struct queue* q = create_queue( );
	add_queue( q, s );
	while (q -> head) {
		struct table_cell* vi = poll_queue( q );
		struct list_sibl* sibl = vi -> siblings;
		while( sibl ) {
			struct table_cell* tmp = sibl -> t_cell;
			if ( UNVISITED == tmp -> visited && ( sibl -> weight > sibl -> flow ) ) {
				tmp -> visited = VISITED;
				tmp -> parent = vi;
				add_queue( q, tmp );
			}
			sibl = sibl -> next;
		}
		vi -> visited = VISITED;
	}
	free( q );
	if ( VISITED == t -> visited ) {
		return 1;
	}
	else {
		return 0;
	}
}

static int residual_capacity ( struct table_cell* u, struct table_cell* v ) {
	struct list_sibl* sibl_u = u -> siblings;
	int residual_capacity =  0;
	while ( sibl_u ){
		if ( sibl_u -> t_cell == v ) {
			residual_capacity = sibl_u -> weight - sibl_u -> flow;
		}
		sibl_u = sibl_u -> next;
	}
	struct list_sibl* sibl_v = v -> siblings;
	while ( sibl_v ) {
		if ( sibl_v -> t_cell == u ) {
			residual_capacity = sibl_v -> flow;
		}
		sibl_v = sibl_v -> next;
	} 
	return residual_capacity;
}

static int min ( int* residual_capacity, int id ) {
	int min = residual_capacity[0];
	for ( int i = 1; i < id; i++ ) {
		if ( residual_capacity[i] < min  && 0 != residual_capacity[i] ) {
			min = residual_capacity[i];
		}
	}
	return min;
}

static int min_residual_capacity ( struct table_cell* start, struct table_cell* finish, int size ) {
	int* res_capacity = ( int* )calloc( size, sizeof( int ) );
	int id = 0;
	struct table_cell* v = finish;
	struct table_cell* u = finish -> parent;
	while ( start != v ) {
		printf("%d ", v -> id);
		res_capacity[id++ ] = residual_capacity ( u, v );
		u = u -> parent;
		v = v -> parent;
	}
	printf("%d\n", start -> id );
	int min_cap = min( res_capacity, id );
	free( res_capacity );
	return min_cap;
}

static struct list_sibl* edge ( struct table_cell* u, struct table_cell* v ) {
	struct list_sibl* sibl_u = u -> siblings;
	while ( sibl_u ){
		if ( sibl_u -> t_cell == v ) {
			return sibl_u;
		}
		sibl_u = sibl_u -> next;
	}
	return NULL;
}

static void fill_flow(struct table_cell* start, struct table_cell* finish, int flow ) {
	struct table_cell* u = finish -> parent;
	struct table_cell* v = finish;
	while ( start != v ) {
		struct list_sibl* edge_u_v = edge( u, v );
		edge_u_v -> flow = ( edge_u_v -> flow ) + flow;
		struct list_sibl* edge_v_u = edge( v, u );
		if ( edge_v_u ) {
			edge_v_u -> flow = ( edge_v_u -> flow ) - flow;
		}
		u = u -> parent;
		v = v -> parent;
	}
}

void algo(struct hash_table* hash_table, struct table_cell* start, struct table_cell* finish, int vertex ) {
	int max_flow = 0;
	while ( bfs( hash_table, start, finish ) ) {
		int flow = min_residual_capacity( start , finish, vertex );
		printf("flow = %d\n", flow);
		fill_flow( start, finish, flow );
		max_flow += flow;	
	}
	print_table_flow( hash_table );
	printf( "max_flow = %d\n", max_flow );
<<<<<<< HEAD
}
=======
}
>>>>>>> 5423c5eeb018f09d45ddfbc932730673bfeded96
