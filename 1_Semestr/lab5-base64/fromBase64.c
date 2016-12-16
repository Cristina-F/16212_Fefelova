#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define INPUT_SIZE 4
#define OUTPUT_SIZE 3
#define DEL "."
#define SUF ".orig"

void delet_str ( char* Source_str, const char* Del_str ) {
	int len = 1;
	char* start_del = strstr( Source_str, Del_str  );
	while ( Source_str[len] != Del_str[0] ) {
		len++;
	}
	strcpy( start_del, start_del + ( strlen( Source_str ) - len ) );
}

void creat_file ( char* name_file ) {
	delet_str( name_file, DEL );
	name_file = strcat( name_file, SUF );
	FILE* file = fopen( name_file, "w" );
	if ( NULL == file ) {
		printf( "Can not creat %s\n", name_file );
	}
	fclose( file );
}

int check_file ( FILE* file ) {
	char read = fgetc( file ); 
	int length = 0;
	int n = 0;
	while( EOF != read) { 
		if ( '\n'  != read ) {
			length++;
		} 
		if ( '=' == read ) {
			n++;
		}
		if ( 0 != n && '=' != read && '\n' != read ) {
			return 1;
		}
		read = fgetc( file );
	}
	rewind( file );
	if ( 0 != length % INPUT_SIZE ){
		return 2;
	}
	if ( 2 < n ) {
		return 3;
	}
	return 0;
}

int chek ( char read ) {
	if ( 'A' <= read && read <= 'Z' || 'a' <= read && read <= 'z' || '0' <= read && read <= '9' 
		|| '+' == read || '/' == read || '=' == read || '\n' == read ) {
		return 0;
	}
	else {
		return -1;
	}
}

void decode ( char* orig , char* base64 ) {
	 orig[0] = ( base64[0] << 2 ) | ( ( base64[1] & 0x30 ) >> 4 );
     orig[1] = ( ( base64[1] & 0x0F ) << 4 ) | ( ( base64[2] & 0x3C ) >> 2 );
     orig[2] = ( ( base64[2] & 0x03 ) << 6 ) | base64[3];
}

int decode_base64 ( FILE* in_file, FILE* out_file ) {
	char orig[OUTPUT_SIZE] = { };
	char base64[INPUT_SIZE] = { };
	int read = fread( base64, 1, INPUT_SIZE, in_file);
	int equally = 0;
	while ( INPUT_SIZE == read ) {
		for ( int i = 0; i < INPUT_SIZE; i++ ) {
			if ( -1 == chek( base64[i] ) ) {
				return -1;
			}
			if ( '=' != base64[i] ) {
				base64[i] = strchr( ALPHA, base64[i] ) - ALPHA;
			}
			else {
				equally++;
			}
		}
		decode( orig, base64 );
		if ( 0 == equally ) {
			fwrite( orig, 1, OUTPUT_SIZE, out_file );
		}
		else {	
			fwrite( orig, 1, ( OUTPUT_SIZE - equally ), out_file );
		}
		memset( base64, 0, INPUT_SIZE );
		memset( orig, 0, OUTPUT_SIZE );
		read = fread( base64, 1, INPUT_SIZE, in_file );
	}
	return 0;
}

int main ( int argc, char* argv[ ] ) {
	FILE* in_file = NULL;
	FILE* out_file = NULL;
	if ( 2 == argc ) {
		in_file = fopen( argv[1], "r" );
		if ( NULL == in_file ) {
			printf( "Can not open %s.\n", argv[1] );
			return -1;
		}
	}
	else {
		printf( "Error: incorrect input data.\n" );
		return -1;
	}
	char* out_name = ( char* )calloc( ( strlen( argv[1] ) + strlen( SUF ) ), sizeof( char ) );
	strcpy( out_name, argv[1] );
	creat_file( out_name );
	out_file = fopen( out_name, "w" );
	if ( NULL == out_file ) {
		printf( "Can not open %s.\n", out_name );
		return -1;
	}
	int chek = check_file( in_file );
	if ( 0 != chek ) {
		if ( 1 == chek ) {
			printf( "Improper positioning of the sign =\n" );
		}
		else if ( 2 == chek ) {
			printf( "Invalid file size\n" );
		}
		else if ( 3 == chek ) {
			printf( "Wrong number of characters =\n" );
		}
		return -1;
	}	
	if ( -1 == decode_base64( in_file, out_file ) ) {
		printf( "Not all symbols correspond alphabetically base64\n" );
		return -1;
	}
	fclose( out_file );
 	fclose( in_file ); 
	free( out_name );
	return 0;
}
