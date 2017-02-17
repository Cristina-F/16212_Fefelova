#include <stdio.h>

#define SIZE_ARRAY 10

void search_max_sum( int* array ) {
	int max_sum = array[0];
	int sum = 0;
	int left = 0; 
	int right = 0;
	for ( int i = 0; i < SIZE_ARRAY; i++ ) {
		sum = sum + array[i];
		if ( sum > max_sum ) {
			max_sum = sum;
			right = i;
		}
		if ( sum < 0 ) {
			sum = 0;
			left = i + 1;
		}
	}
	printf("left = %d; right = %d; max_sum = %d;\n", left, right, max_sum );
}

int main ( ) {
	int array[SIZE_ARRAY] = { 1, -3, 5, -1, 6, 7, -9, 3, 4, 5 };
	search_max_sum( array );
	return 0;
}
