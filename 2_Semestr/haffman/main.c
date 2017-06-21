#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "haf.h"

#define TO_HAF '1'
#define FROM_HAF '2'
#define TO_HAF_SUF ".haf"
#define FROM_HAF_SUF ".orig"

int check_input_data( int argc, char* name_file ) {
	if ( 2 != argc ) {
		printf( "Error: incorrect input data.\n" );
		return 0;
	}
	else {
		FILE* in_file = fopen( name_file, "rb" );
		if ( NULL == in_file ) {
			printf( "Can not open %s.\n", name_file );
			return 0;
		}
		fclose( in_file );
	}
	return 1;
}

char* create_out_file_name ( char* in_file_name, char* suf ) {
	char* out_name = ( char* )calloc( ( strlen( in_file_name ) + strlen( suf ) + 1 ), sizeof( char ) );
	strcpy( out_name, in_file_name );
	out_name = strcat( out_name, suf );
	return out_name;
}

int main( int argc, char* argv[] ) {
	FILE* in_file = NULL;
	FILE* out_file = NULL;
	char cmd = 0;
	if( check_input_data( argc, argv[1] ) ) {
		in_file = fopen( argv[1], "rb" );
		printf( "1 - to haffman \n2 - from haffman\n");
		cmd = getchar( );
		if ( ( TO_HAF != cmd ) && ( FROM_HAF != cmd ) ) {
			printf("Invalid command\n");
			fclose( in_file );
			return -1;
		}
		char* out_name = NULL;
		if ( TO_HAF == cmd ) {
			out_name = create_out_file_name( argv[1], TO_HAF_SUF );
		}
		else {
			out_name = create_out_file_name( argv[1], FROM_HAF_SUF );
		}
		out_file = fopen( out_name, "wb" );
		if ( NULL == out_file ) { 
			printf( "Can not open %s.\n", out_name );
			free( out_name );
			fclose( in_file );
			return -1;
		}
		free(out_name);
	}
	else {
		return -1;
	}
	if ( TO_HAF == cmd ) {
		compression( in_file, out_file );
	}
	else {
		decompression( in_file, out_file );
	}
	fclose( in_file );
	fclose( out_file );
	
	return 0;
}