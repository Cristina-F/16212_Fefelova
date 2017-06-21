#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 5

struct node {
	int id;
	int num_siblings;
	int* weight;
	struct node** siblings;
};

struct node** create_graph( int size ) {
	struct node** graph = ( struct node** ) calloc( size, sizeof( struct node* ) );
	for ( int i = 0; i < size; i++ ) {
		graph[i] = ( struct node* )calloc( 1, sizeof( struct node ) );
		graph[i] -> id = 0;
		graph[i] -> num_siblings = 0;
		graph[i] -> weight = NULL;
		graph[i] -> siblings = ( struct node** )calloc( 1, sizeof( struct node* ) );
	}
	return graph;
}

void add_siblings ( struct node* node1, struct node* node2, int weight ) {
	( node1 -> num_siblings )++;
	struct node** new_siblings = ( struct node** )calloc( node1 -> num_siblings, sizeof( struct node* ) );
	int* new_weight = ( int* )calloc( node1 -> num_siblings, sizeof( int ) );
	if ( new_siblings ) {
		for ( int i = 0; i < ( node1 -> num_siblings ) - 1; i++ ) {
			new_siblings[i] = (node1 -> siblings)[i];
			new_weight[i] = ( node1 -> weight)[i];
		}
		new_siblings[(node1-> num_siblings) - 1] = node2;
		new_weight[(node1-> num_siblings) - 1] = weight;
		free( node1 -> weight );
		free( node1 -> siblings );
		node1 -> weight = new_weight;
		node1 -> siblings = new_siblings;
	}
}

struct node** add_node ( FILE* in_file, struct node** graph ) {
	int id_node1 = 0;
	int id_node2 = 0;
	int weight = 0;
	int ok = 0;
	while( ok != EOF ) {
		ok = fscanf( in_file, "%d%d%d", &id_node1, &id_node2, &weight );
		if ( 3 == ok ) {
			graph[id_node1] -> id = id_node1;
			graph[id_node2] -> id = id_node2;
			add_siblings( graph[id_node1], graph[id_node2], weight );
		}
	}
	return graph;
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

void print_graph ( struct node** graph ) {
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < graph[i] -> num_siblings; j++ ) {
			printf("id1 = %d, id2 =  %d, w = %d \n", graph[i] -> id, graph[i] -> siblings[j] -> id, graph[i] -> weight[j] );
		}
	}
}

int min( int x, int y ) {
	if( x < y ) {
		return x;
	}
	return y;
}

void floyd_warshall( int result[N][N] ) {
	for( int k = 0; k < N; k++ ) {
		for( int i = 0; i < N; i++ ) {
			for( int j = 0; j < N; j++ ){
				if ( INT_MAX == result[i][k] || INT_MAX == result[k][j] ) {
					continue;
				}
				result[i][j] = min( result[i][j], result[i][k] + result[k][j] );
			}
		}
	} 	
}

int searh( struct node* gr1, struct node* gr2 ){
	for ( int i = 0; i < gr1 -> num_siblings; i++ ) {
		if ( gr2 == gr1 -> siblings[i] ) {
			return i;
		}
	}
	return -1;
}

void fill_table( int result[N][N], struct node** graph ) {
	for( int i = 0; i < N; i++ ) {
		for( int j = 0; j < N; j++ ) {
			if ( i == j ) {
				result[i][j] = 0;
			}
			else {
				int id = searh( graph[i], graph[j] );
				if ( -1 == id ) {
					result[i][j] = INT_MAX;
				}
				else {
					result[i][j] = graph[i] -> weight[id];
				}				
			}
		}
	}
}

void print_table ( int result[N][N] ) {
	for (int i = 0; i < N; i++ ) {
		for (int j = 0; j < N; j++ ) {
			printf( "%5d ", result[i][j] );
		}
		printf("\n");
	}
	printf("\n");
}

void free_graph( struct node** graph ) {
	for ( int i = 0; i < N; i++ ) {
		free( graph[i] -> weight );
		free( graph[i] -> siblings );
		free( graph[i]);
	}
	free(graph);
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
	int result[N][N];
	fill_table( result, graph );
	print_table( result );
	floyd_warshall(result);
	print_table(result);
	free_graph( graph );
	return 0;
}