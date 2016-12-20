#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define INPUT_SIZE 3
#define OUTPUT_SIZE 4
#define SUF ".base64"

void creat_file ( char* name_file ) {
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
	char* orig = ( char* )calloc( INPUT_SIZE, sizeof( char ) );
	char* base64 = ( char* )calloc( OUTPUT_SIZE, sizeof( char ) );
	int read  = fread( orig, 1, INPUT_SIZE, in_file );
	while ( read > 0 ) {
		encode( orig, base64 );
		for (int i = 0; i < OUTPUT_SIZE; i++ ) {
			base64[i] = ALPHA[( int )base64[i]];
		}
		if ( read < INPUT_SIZE ) {
			base64[INPUT_SIZE] = '=';
			if ( 1 == read ) {
				base64[2] = '=';
			}
		}
		fwrite( base64, 1, OUTPUT_SIZE, out_file );
		memset( orig, 0, INPUT_SIZE );
		memset( base64, 0, OUTPUT_SIZE );
		read = fread( orig, 1, INPUT_SIZE, in_file );
	}
	free( orig );
	free( base64 );
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
	creat_file( out_name ); // Создаем выходной файл
	out_file = fopen( out_name, "w" );// Открываем файл для записи
	if ( NULL == out_file ) { // Завершаем программу, если файл невозможно открыть
		printf( "Can not open %s.\n", out_name );
		free( out_name );
		fclose( in_file );
		return -1;
	}
	encode_base64( in_file, out_file ); // Кодируем в base64
	// Закрываем файлы
	fclose( out_file );
 	fclose( in_file ); 
 	free( out_name );
	return 0;
}
