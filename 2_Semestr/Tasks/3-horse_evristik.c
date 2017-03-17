#include <stdio.h> 
#include <stdlib.h>

#define N 8
#define SIZE 64
#define LAST_MOVE -2
#define START_X 2
#define START_Y 1

int read_scanf ( int position) { 
	int count = 0;
	int num = 0;
	while (1) {
		num = scanf( "%d", &position );
		if ( ( 1 != num ) || ( 0 > position ) ) {
			while ( '\n' != getchar() );
		}
		else {
			while ( '\n' != getchar() ) {
				count++;
			}
			if ( 0 == count ) {
				break;
			}
		}
		printf( "Enter an integer between 0 and 7 \n" );
		count = 0;
	}
	return position;
}

void build_moves( int moves[8][2], int** array, int x, int y ) {
	if ( ( x + 2 < N ) && ( x + 2 >= 0 ) && ( y + 1 < N ) && ( y + 1 >= 0) && ( 0 == array[y + 1][x + 2] ) ) {
		moves[0][0] = x + 2;
		moves[0][1] = y + 1;
	}
	else {
		moves[0][0] = -1;
		moves[0][1] = -1;
	}
	if ( (x + 2 < N ) && ( x + 2 >= 0 ) && ( y - 1 >= 0 ) && (y - 1 < N) && ( 0 == array[y - 1][x + 2] ) ) {
		moves[1][0] = x + 2;
		moves[1][1] = y - 1;
	}
	else {
		moves[1][0] = -1;
		moves[1][1] = -1;
	}
	if ( (x - 2 >= 0) && ( x - 2 < N) && ( y + 1 < N ) &&  ( y + 1 >= 0) && ( 0 == array[y + 1][x - 2] ) ) {
		moves[2][0] = x - 2;
		moves[2][1] = y + 1;
	}
	else {
		moves[2][0] = -1;
		moves[2][1] = -1;
	}
	if ( (x - 2 >= 0 ) && ( x - 2 < N) && ( y - 1 >= 0 ) && (y - 1 < N) && ( 0 == array[y - 1][x - 2] ) ) {
		moves[3][0] = x - 2;
		moves[3][1] = y - 1;
	}
	else {
		moves[3][0] = -1;
		moves[3][1] = -1;
	}
	if ( (x - 1 >= 0 ) && (x - 1 < N) && ( y + 2 < N ) && ( y + 2 >= 0 ) && ( 0 == array[y + 2][x - 1] ) ) {
		moves[4][0] = x - 1;
		moves[4][1] = y + 2;
	}
	else {
		moves[4][0] = -1;
		moves[4][1] = -1;
	}
	if ( (x - 1 >= 0 ) && (x - 1 < N ) && ( y - 2 >= 0 ) && ( y - 2 < N ) && ( 0 == array[y - 2][x - 1] ) ) {
		moves[5][0] = x - 1;
		moves[5][1] = y - 2;
	}
	else {
		moves[5][0] = -1;
		moves[5][1] = -1;
	}
	if ( (x + 1 < N ) && (x + 1 >= 0 ) && ( y + 2 < N ) && ( y + 2 >= 0 ) &&( 0 == array[y + 2][x + 1] ) ) {
		moves[6][0] = x + 1;
		moves[6][1] = y + 2;
	}
	else {
		moves[6][0] = -1;
		moves[6][1] = -1;
	}
	if ( (x + 1 < N ) && (x + 1 >= 0 ) && ( y - 2 >= 0 ) && ( y - 2 < N ) && ( 0 == array[y - 2][x + 1] ) ) {
		moves[7][0] = x + 1;
		moves[7][1] = y - 2;
	}
	else {
		moves[7][0] = -1;
		moves[7][1] = -1;
	}

}

void print_field( int** array ){
	for ( int i = 0; i < N; i++ ) {
		for ( int j = 0; j < N; j++ ) {
			printf("%5d ", array[i][j]);
		}
		printf("\n");
	}
}

int move_ok( int* moves ) {
	if ( ( -1 != moves[0] ) && ( -1 != moves[1] ) ) {
		return 1;
	}
	return 0;
}

void count_step_cell( int moves[8][2], int count_step[8], int** array ) {
	int new_moves[8][2];
	for ( int i = 0; i < 8; i++) {
		if ( move_ok(moves[i])) {
			build_moves( new_moves, array, moves[i][0], moves[i][1] );
			for ( int j = 0; j < 8; j++ ) {
				if ( move_ok( new_moves[j] ) ) {
				count_step[i]++;
				}
			}
		}
	}
}

int min_step ( int moves[8][2], int** array, int step ) {
	int count_step[8] = {0};
	count_step_cell( moves, count_step, array );
	int min = 9;
	int index = -1;
	int count = 0;
	for ( int i = 0; i < 8; i++) {
		if ( ( count_step[i]  < min ) && ( count_step[i] > 0 ) ){
			min = count_step[i];
			index = i;
		}
		if ( 0 == count_step[i] ) {
			count++;
		}
	}
	if ( 8 == count && SIZE == step) {
		return LAST_MOVE;
	}
	return index;
}

int bad_step ( int moves[8][2 ] ) {
	int bad = 0;
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 2; j++ ) {
			if ( -1 == moves[i][j] ) {
				bad++;
			}
		}
	}
	if ( 2 * 8 == bad ) {
		return -1;
	}
	return 0;
}

int go ( int** array, int x, int y, int count ) {
	int moves[8][2];
		build_moves( moves, array, x, y );
		if ( -1 == bad_step( moves) ) {
			return -1;
		}
		while (1) {
			int index = min_step ( moves, array, count );
			if ( -1 == index ) {
				return -1;
			}
			else if ( LAST_MOVE == index ){
				for ( int i = 0; i < 8; i++ ) {
					if ( move_ok( moves[i] ) ) {
						array[moves[i][1]][moves[i][0]] = count;
						return 1;
					}
				}
			}
			else {
				array[moves[index][1]][moves[index][0]] = count;
				int step = go( array, moves[index][0], moves[index][1], count + 1);
				if ( 1 == step ) {
					return 1;
				}
				else if ( -1 == step ) {
					array[moves[index][1]][moves[index][0]] = 0;
					moves[index][0] = -1;
					moves[index][1] = -1;
				}
			}
		}
	return 1;
}

void free_memory( int** array ) {
	for ( int i = 0; i < N; i++ ) {
		free( array[i] );
	}
	free( array );
}

int main( ) {
	int** array = ( int** )calloc( N, sizeof( int* ) );
	for ( int i = 0; i < N; i++ ) {
		array[i] = ( int* )calloc( N, sizeof( int ) );
	}
	int x = read_scanf( x );
	int y = read_scanf( y );
	array[y][x] = 1;
	go( array, x, y, 2 );
	print_field( array );
	free_memory( array );
	return 0;
}
