#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int search ( int** arr, int count ){
	int one = 0;
	for ( int i = 0; i < SIZE; i++ ) {
		for ( int j = 0; j < SIZE; j++ ) {
			if ( 1 == arr[i][j] ) {
				one++;
				break;
			} 
		}
		if ( 0 == one ) {
			printf("%d ", i );
			for ( int k = 0; k < SIZE; k++ ) {
				arr[k][i] = 0;
				arr[i][k] = 1;
			}
			count++;
		}
		one = 0;
	}
	return count;
}

void free_memory ( int** arr ) {
	for ( int i = 0; i < SIZE; i++ ) {
		free( arr[i]);
	}
	free(arr);
}

int main ( ) {
	int** arr = ( int** )calloc( SIZE, sizeof( int* ) );
	for ( int i = 0; i < SIZE; i++ ){
		arr[i] = ( int* )calloc( SIZE, sizeof( int ) );
	}
	int count = 0;
	arr[1][0] = arr[2][0] = arr[5][0] = arr[3][2] = arr[1][3] = arr[4][3] = arr[3][5] = 
	arr[0][7] = arr[3][7] = arr[3][8] = arr[6][8] = 1;
	while ( count < SIZE ) { 
		count = search( arr, count );
	}
	free_memory( arr );
	printf("\n");
	return 0;
}
