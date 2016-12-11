#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define INPUT_SIZE 3
#define OUTPUT_SIZE 4
#define DEL "."
#define SUF ".base64"

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

void encode( char* orig , char* base64 ) {
	base64[0] = ( ( orig[0] & 0xFC ) >> 2 );
	base64[1] = ( ( orig[0] & 0x03 ) << 4 ) | ( ( orig[1] & 0xF0 ) >> 4 );
	base64[2] = ( ( orig[1] & 0x0F ) << 2 ) | ( ( orig[2] & 0xC0 ) >> 6 );
	base64[3] = ( ( orig[2] & 0x3F ) );
}

void encode_base64 ( FILE* in_file, FILE* out_file ) {
	char orig[INPUT_SIZE] = { };
	char base64[OUTPUT_SIZE] = { };
	int read = fgetc( in_file );
	int size = 0;
	while ( EOF != read ) {
		orig[size] = read;
		size++;
		if ( INPUT_SIZE == size ) {
			encode( orig, base64 );
			for ( int j = 0; j < OUTPUT_SIZE; j++ ) {
				fprintf( out_file, "%c", ALPHA[ base64 [j] ] );
			}
			size = 0;
			memset( orig, 0, INPUT_SIZE );
		}
		read = fgetc( in_file );
	}
	if ( 0 != size ) {
		encode( orig, base64 );
		for ( int j = 0; j < OUTPUT_SIZE; j++ ) {
			if ( 0 == base64[j] ) {
				fprintf( out_file, "=" );
			}
			else {
				fprintf( out_file, "%c", ALPHA[ base64 [j] ] );
			}
		}
	}
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
	out_name = argv[1];
	creat_file( out_name ); // Создаем выходной файл
	out_file = fopen( out_name, "w" );// Открываем файл для записи
	if ( NULL == out_file ) { // Завершаем программу, если файл невозмлжно открыть
		printf( "Can not open %s.\n", out_name );
		return -1;
	}
	encode_base64( in_file, out_file ); // Кодируем в base64
	// Закрываем файлы
	fclose( out_file );
 	fclose( in_file ); 
 	free( out_name );
	return 0;
}
