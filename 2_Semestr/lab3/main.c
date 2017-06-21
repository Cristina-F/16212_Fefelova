#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#include "ht.h"
#include "gr.h"
#include "algo.h"

#define SIZE 3// Начальный размер хеш-таблицы

int check_input_data( int argc, char* name_file ) {
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


int main( int argc, char* argv[] ) {
	FILE* in_file = NULL;
	if( 0 == check_input_data( argc, argv[1] ) ) {
		in_file = fopen( argv[1], "r" );
	}
	else {
		return -1;
	}
	struct hash_table* hash_table = create_table( SIZE );
	int count_vertex = 0;
	hash_table = add_node( hash_table, in_file, &count_vertex );	
	fclose ( in_file );
	struct table_cell* start_vertex = get_vertex( hash_table );
	struct table_cell* finish_vertex = get_vertex( hash_table );
	if ( !start_vertex || !finish_vertex ) {
		printf("Don't found vertex.\n");
		free_table( hash_table );
		return -1;
	}
	algo( hash_table, start_vertex, finish_vertex, count_vertex );
	free_table( hash_table );
	return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 5423c5eeb018f09d45ddfbc932730673bfeded96
