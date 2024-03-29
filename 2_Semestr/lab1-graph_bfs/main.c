#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "hash_table.h"
#include "graph.h"

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
	hash_table = add_node( hash_table, in_file );	
	fclose ( in_file );
	bfs( hash_table );
	print_table(hash_table);
	free_table( hash_table );
	return 0;
}