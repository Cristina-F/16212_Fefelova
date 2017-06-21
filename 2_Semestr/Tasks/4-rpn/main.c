#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "create.h"
#include "rpn.h"

int main( ) {
	char* string = read_string( string );
	struct list* head = ( struct list* )calloc( 1, sizeof( struct list ) );
	if ( -1 == parse( string, head ) ) {
		printf("Ошибка\n");
		free_list( head );
		free( string );
		return -1;
	}
	struct list* note = reverse_polish_notation( head );
	print_list( note );
	printf("\n");
	if ( !note ){
		printf("Ошибка\n");
		free_list( note );
		free( string );
		return -1;
	}
	int result = calculate( note );
	printf("result = %d\n", result );
	free( string );
	free_list( note );
	return 0;
}