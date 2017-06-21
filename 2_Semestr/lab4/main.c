#include <stdio.h>
#include <stdlib.h>

#include "algo.h"

int main( ) {
	char* a = NULL;
	char* b = NULL;
	if ( !read_input_data( &a, &b ) ) {
		printf("НЕУДАЧА\n");
		return -1;
	}
	Needleman_Wunsch( a, b );
	free( a );
	free( b );
	return 0;
}