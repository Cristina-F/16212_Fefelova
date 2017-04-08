#include <stdio.h>
#include <stdlib.h>

#include "create.h"

#define WEIGHT 13
#define N 5

int min_weight( int** things ) {
	int min = WEIGHT;
	for ( int i = 0; i < N; i++ ) {
		if( things[i][0] < min ) {
			min = things[i][0];
		}
	}
	return min;
}

int max_value ( int val1, int val2 ) {
	if ( val1 > val2 ) {
		return  val1;
	}
	else {
		return val2;
	}
}

void print_table ( int** arr, int y, int x ) {
	for ( int i = 0; i < y; i++ ){
		for( int j = 0; j < x; j++ ) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int fill_table( int** table, int** things, int start ) {
	for ( int i = 1; i <= N ; i++ ) {
		for ( int j = start ; j <= WEIGHT; j++ ) {
			int tmp = j - things[i -1 ][0];
			if ( tmp < 0 ) {
				table [i][j] = table[i -1][j];
			}
			else {
				table[i][j] = max_value( table[i - 1][j], table[i - 1][tmp] + things[i - 1][1]);
			}
		}
	}
}

void find_things( int** table, int** things, int start ) {
	int tmp = table[N][WEIGHT];
	int w = WEIGHT;
	for (int i = N; i > 0; i-- ) {
		if ( tmp != table[i - 1][w]) {
			w = w - things[i - 1][0];
			if ( w < 0) {
				w = 0;
			}
			tmp = table[i-1][w];
			printf("Кладем  вещь № %d, вес = %d, ценность = %d\n", i, things[i - 1][0], things[i - 1][1] );
		}
	}
}

void free_memory( int** arr, int n ) {
	for ( int i = 0; i < n; i++ ) {
		free( arr[i] );
	}
	free( arr );
}

int main( ){
	int** things = create_two_array( N );
	for ( int i = 0; i < N; i++ ) {
		things[i] = create_array( 2 );
	}
	things[0][0] = 3;
	things[0][1] = 1;
	things[1][0] = 4;
	things[1][1] = 6;
	things[2][0] = 5;
	things[2][1] = 4;
	things[3][0] = 8;
	things[3][1] = 7;
	things[4][0] = 9;
	things[4][1] = 6;
	print_table( things, N, 2 );
	int** table = create_two_array( N + 1 );
	for ( int i = 0; i < N + 1; i++ ) {
		table[i] = create_array( WEIGHT + 1 );
	}
	int start = min_weight( things );
	fill_table( table, things, start );
	print_table( table, N + 1, WEIGHT + 1 );
	find_things( table, things, start );
	free_memory( table, N + 1 );
	free_memory( things, N );
	return 0;
}
