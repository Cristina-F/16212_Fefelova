#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header_graph.h"

#define SIZE 3// Начальный размер хеш-таблицы

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
