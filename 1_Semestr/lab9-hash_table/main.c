#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define SIZE 3
#define MAX_LENGTH 30 // Максимальная длина имени

int main( int argc, char* argv[] ) {
	FILE* in_file = NULL;
	if ( 2 == argc ) {
		in_file = fopen( argv[1], "r" );
		if ( NULL == in_file ) {
			printf( "Error: Can not open %s.\n", argv[1] );
			return -1;
		}
	}
	else {
		printf( "Error: incorrect input data.\n" );
		return -1;
	}		
	struct hash_table* hash_table = create_table( SIZE, 0 );
	hash_table = write_in_table( in_file, hash_table );
	fclose ( in_file );
	print_table( hash_table );
	char* name = ( char* )calloc( MAX_LENGTH, sizeof( char ) );
	scanf( "%s", name );
	int check = check_name( name );
	if( -1 == check) {
		printf("Name is too long.\n");
		free( name );
		free_table( hash_table );
		return -1;
	}
	struct table_cell* search = table_search( hash_table, name );
	print_search( search );
	free( name );
	free_table( hash_table );
	return 0;
}
