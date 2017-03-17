#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct node {
	int id;
	int num_siblings;
	int color;
	int distance;
	struct node* parent;
	struct node** siblings;
};

struct list {
	int x;
	struct list* next;
};

struct queue {
	struct list* tail;
	struct list* head;
};

struct queue* create_queue() {
	struct queue* new_queue = ( struct queue* )calloc( 1, sizeof( struct queue ) );
	if ( !new_queue ) {
		return NULL;
	}
	new_queue -> tail = NULL;
	new_queue -> head = NULL;
	return new_queue;
}

int add_queue ( struct queue* q, int index ) {
	struct list* tmp = ( struct list* )calloc( 1, sizeof( struct list ) );
	if ( !tmp ) {
		return -1;
	}
	if ( !( q -> head ) ){
		q -> head = tmp;
		q -> tail = q -> head;

	} 
	else {
		q -> tail -> next = tmp;
		q -> tail = tmp;
	}
	q -> tail -> x = index;
	return 0;
}
 
void poll_queue( struct queue* q ) {
	int ret = q -> head -> x;
	struct list* buff = q -> head;
	q -> head = q -> head -> next;
	free( buff );
}

struct node** create_graph( int size ) {
	struct node** graph = ( struct node** ) calloc( size, sizeof( struct node* ) );
	for ( int i = 0; i < size; i++ ) {
		graph[i] = ( struct node* )calloc( 1, sizeof(struct node ) );
		graph[i] -> id = 0;
		graph[i] -> num_siblings = 0;
		graph[i] -> color = WHITE;
		graph[i] -> distance = -1;
		graph[i] -> parent = NULL;
		graph[i] -> siblings = NULL;
	}
	return graph;
}

int add_siblings ( struct node* actual_node, struct node* siblings ) {
	( actual_node -> num_siblings )++;
	struct node** new_siblings = ( struct node** )calloc( ( actual_node -> num_siblings ), sizeof( struct node* ) ); 
	if ( new_siblings ) {
		for ( int i = 0; i < ( actual_node -> num_siblings ) - 1; i++ ) {
			new_siblings[i] = actual_node -> siblings[i];
		}
		new_siblings[(actual_node -> num_siblings) - 1] = siblings;
		free( actual_node -> siblings );
		actual_node -> siblings = new_siblings;
	}

	return 0;
}

struct node** add_node ( FILE* in_file, struct node** graph ) {
	int id_node1 = 0;
	int id_node2 = 0;
	int ok = 0;
	for( int i = 0; ok != EOF; i++ ) {
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

int bfs(struct node** graph ) {
	graph[0] -> color = GRAY;
	graph[0] -> distance = 0;
	struct queue* q = create_queue( );
	add_queue( q, graph[0] -> id );
	while(	q -> head ){
		struct node* tmp = graph[q -> head -> x];
		printf("%d ", tmp -> id);
		for ( int i = 0; i < ( tmp -> num_siblings ); i++ ) {
			struct node* new_node = ( tmp -> siblings )[i];
			if ( WHITE == ( new_node -> color ) ) {
				new_node -> color = GRAY;
				new_node -> parent = tmp;
				new_node -> distance = ( tmp -> distance ) + 1;
				add_queue( q, new_node -> id );
			}
		}
		poll_queue( q );
		tmp -> color = BLACK;
	}
	printf( "\n" );
	return 0;
}

void free_graph( struct node** graph, int size ) {
	struct node** tmp = graph;
	for ( int i = 0; i < size; i++ ) {
		for ( int j = 0; j < ( tmp[i] -> num_siblings ); j++ ) {
			free((tmp[i] -> siblings)[j]);
		}
		free( tmp[i] -> siblings );
		free( tmp[i]);
	}
	free(graph);
}

int size_graph( FILE* in_file ) {
	int num = 0;
	int read = 0;
	int size = 0;
	while( EOF != read ) {
		read = fscanf( in_file, "%d", &num);
		if ( num > size ) {
			size = num;
		}
	}
	rewind( in_file );
	return size + 1;
}

int main ( int argc, char* argv[ ] ) {
	FILE* in_file = NULL;
	if( 0 == chek_input_data( argc, argv[1] ) ) {
		in_file = fopen( argv[1], "r" );
	}
	else {
		return -1;
	}
	int size = size_graph( in_file );
	struct node** graph = create_graph( size );
	graph = add_node( in_file, graph );
	bfs(graph);
	free_graph( graph, size );
	return 0;
}
