#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define N 11
#define VISITED 1

struct node {
	int id;
	int num_siblings;
	int* visit_edge;
	struct node** siblings;
};

struct node** create_graph( int size ) {
	struct node** graph = ( struct node** ) calloc( size, sizeof( struct node* ) );
	for ( int i = 0; i < size; i++ ) {
		graph[i] = ( struct node* )calloc( 1, sizeof( struct node ) );
		graph[i] -> id = 0;
		graph[i] -> num_siblings = 0;
		graph[i] -> visit_edge = NULL;
		graph[i] -> siblings = ( struct node** )calloc( 1, sizeof( struct node* ) );
	}
	return graph;
}

void free_graph( struct node** graph ) {
	for ( int i = 0; i < N; i++ ) {
		free( graph[i] -> visit_edge);
		free( graph[i] -> siblings );
		free( graph[i]);
	}
	free(graph);
}

int chek_input_data( int argc, char* name_file ) {
	if ( 2 != argc ) {
		printf( "Error: incorrect input data.\n" );
		return -1;
	}
	else {
		FILE* in_file = fopen( name_file, "r" );
		if ( NULL == in_file ) {
			printf( "Can not open %s.\n", name_file );
			return -2;
		}
		fclose( in_file );
	}
	return 0;
}

void add_siblings ( struct node* node1, struct node* node2) {
	( node1 -> num_siblings )++;
	struct node** new_siblings = ( struct node** )calloc( node1 -> num_siblings, sizeof( struct node* ) );
	int* new_visit_edge = ( int* )calloc( node1 -> num_siblings, sizeof( int ) );
	if ( new_siblings ) {
		for ( int i = 0; i < ( node1 -> num_siblings ) - 1; i++ ) {
			new_siblings[i] = (node1 -> siblings)[i];
		}
		new_siblings[(node1-> num_siblings) - 1] = node2;
		free( node1 -> visit_edge );
		free( node1 -> siblings );
		node1 -> visit_edge = new_visit_edge;
		node1 -> siblings = new_siblings;
	}
}

struct node** add_node ( FILE* in_file, struct node** graph ) {
	int id_node1 = 0;
	int id_node2 = 0;
	int ok = 0;
	while( ok != EOF ) {
		ok = fscanf( in_file, "%d%d", &id_node1, &id_node2 );
		if ( 2 == ok ) {
			graph[id_node1] -> id = id_node1;
			graph[id_node2] -> id = id_node2;
			add_siblings( graph[id_node1], graph[id_node2] );
			add_siblings( graph[id_node2], graph[id_node1] );
		}
	}
	return graph;
}

void print_graph ( struct node** graph ) {
	printf("\n");
	for ( int i = 0; i < N; i++ ) {
		printf("%d sibl:", graph[i] -> id );
		for ( int j = 0; j < graph[i] -> num_siblings; j++ ) {
			printf("%d ", graph[i] -> siblings[j] -> id);
		}
		for ( int j = 0; j < graph[i] -> num_siblings; j++ ) {
			printf("  %d ", graph[i] -> visit_edge[j] );
		}
		printf("\n");
	}
	printf("\n");
}

void dfs ( struct node* node, int visit[N] ) {
	visit[node -> id] = VISITED;
	for ( int i = 0; i < node -> num_siblings; i++ ) {
		if ( 0 == (visit[node -> siblings[i] -> id])) {
			dfs( node -> siblings[i], visit );
		}
	}
}

int check_for_euler_path (struct node** graph ) {
	int num_odd_vertex = 0;
	for ( int i = 0; i < N; i++ ) {
		if ( 1 ==  ( ( graph[i] -> num_siblings ) % 2 ) ) {
			num_odd_vertex++;
		}
		if ( num_odd_vertex > 2 ) {
			return 0;
		}
	}
	int visit[N] = {0};
	for ( int i = 0; i < N; i++ ) {
		if ( graph[i] -> siblings > 0 ) {
			dfs( graph[i], visit );
			break;
		}
	}
	for ( int i = 0; i < N; i++ ){ 
		if ((graph[i] -> num_siblings > 0) && ( 0 == visit[i] ) ) {
			return 0;
		}
	}
	return 1;
}

int search_sibl( struct node* n1, struct node* n2 ) {
	for ( int i = 0; i < n2 -> num_siblings; i++ ) {
		if ( n1 == n2 -> siblings[i] ) {
			return i;
		}
	}
}

void find_euler_path( struct node** graph ) {
	for ( int  i = 0; i < N; i++ ) {
		if ( 1 == ( ( graph[i] -> num_siblings ) % 2 ) ) {
			break;
		}
	}
	struct node* nod = graph[i];
	struct stack* stack = create_stack();
	push( stack, nod );
	while ( stack -> peak) {
		nod = stack -> peak -> elem;
		for (int i = 0; i < ( nod -> num_siblings ); i++ ) {
			if ( 0 == ( nod -> visit_edge[i]) ) {
				nod -> visit_edge[i] = VISITED;
				nod -> siblings[i] -> visit_edge[ search_sibl(nod, nod -> siblings[i])] = VISITED;
				push( stack, nod -> siblings[i] );
				break;
			}
		}
		if ( nod == stack -> peak -> elem) {
			printf("%d ", nod -> id );
			pop( stack );
		}
	}
	printf("\n");
	free( stack );
}

int main ( int argc, char* argv[ ] ) {
	FILE* in_file = NULL;
	if( 0 == chek_input_data( argc, argv[1] ) ) {
		in_file = fopen( argv[1], "r" );
	}
	else {
		return -1;
	}
	struct node** graph = create_graph( N );
	graph = add_node( in_file, graph );
	fclose( in_file );
	print_graph( graph );
	if( check_for_euler_path( graph ) ) {
		find_euler_path( graph );
	}
	print_graph(graph);
	free_graph( graph );
	return 0;
}