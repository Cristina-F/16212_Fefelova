#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 'A'
#define T 'T'
#define C 'C'
#define G 'G'
#define START_LENGTH_STRING 30
#define GAP '-'
#define GAP_OPEN 15
#define GAP_EXTEND 1
#define MATCH 5 
#define NOT_MATCH -3

void print_table ( int** table, int x, int y ) {
	printf("\n");
	for ( int i = 0; i < y; i++ ) {
		for( int j = 0; j < x; j++ ) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

static char* read_string ( ) {
	char* string  = ( char* )calloc( START_LENGTH_STRING + 1, sizeof( char ) );
	if ( !string ) {
		return NULL;
	}
	char symbol = 0;
	int i = 0;
	for ( ; '\n' != ( symbol = getchar( ) ); i++ ) {	
		if ( 0 == i % START_LENGTH_STRING && i != 0 ) {
			string = ( char* )realloc( string, ( 2 * i ) + 1  );
		}
		string[i] = symbol;
	}
	string[ i ] = '\0';
	return string;
}

static int check_input_data( char* str ) {
	for ( int i = 0; '\0' != str[i]; i++ ) {
		if ( ( A != str[i]) && ( T != str[i] ) && ( C != str[i] ) && ( G != str[i] ) ) {
			free( str );
			return 0;
		}
	}
	return 1;
}

int read_input_data( char** a, char** b ) {
	*a = read_string( );
	*b = read_string( );
	if ( !check_input_data( *a ) || !check_input_data( *b ) ) {
		return 0;
	}
	return 1;
}

static int** create_table ( int x, int y ) {
	int** table = ( int** )calloc( y, sizeof( int* ) );
	for ( int i = 0; i < y; i++ ) {
		table[i] = ( int* )calloc( x, sizeof( int ) ); 
	}
	return table;
}

static int max( int a, int b ) {
	if ( a > b ) {
		return a;
	}
	else {
		return b;
	}
}

static void free_table ( int** table, int y ) {
	for ( int i = 0; i < y; i++ ) {
		free( table[i] );
	}
	free( table );
}

int check_match ( char a, char b ) {
	if ( a == b ) {
		return MATCH;
	}
	else {
		return NOT_MATCH;
	}
}
static int** create_scoring_table ( char* a, char* b, int** gap_table ) {
	int x = strlen( b ) + 1;
	int y = strlen( a ) + 1;
	int** scoring_table = create_table( x, y );
	for ( int i = 0; i < y; i++ ) {
		scoring_table[i][0] = - GAP_OPEN - GAP_EXTEND * i;
		gap_table[i][0] = GAP_EXTEND;
	}
	for ( int i = 0; i < x; i++ ) {
		scoring_table[0][i] = - GAP_OPEN - GAP_EXTEND * i;
		gap_table[0][i] = GAP_EXTEND;
	}
	int state_gap = 0;
	int actual_gap = 0;
	for ( int i = 1; i < y; i++ ) {
		for ( int j = 1; j < x; j++ ) {
			if ( 0 == state_gap ) {
				actual_gap = GAP_OPEN;
			}
			else {
				actual_gap = GAP_EXTEND;
			}
			gap_table[i][j] = actual_gap;
			int match = scoring_table[i - 1][j - 1] + check_match( a[i - 1], b[j - 1] );
			int delete = scoring_table[i -1][j] - actual_gap;
			int insert = scoring_table[i][j - 1] - actual_gap;
			scoring_table[i][j] = max( max( match, insert ), delete );
			if ( match == scoring_table[i][j] ) {
				state_gap = 0;
			}
			else {
				state_gap = 1;
			}
		}
	}
	//print_table( scoring_table, x, y );
	//print_table( gap_table, x, y );
	return scoring_table;
}

static void revers (char* string ) {
	if ( string ) {
		int size = strlen( string ) - 1;
		for ( int i = 0; i < size; i++ ) {
			char c = string[i];
			string[i] = string[size];
			string[size] = c;
			size--;
		}
	}
}
void realloc_string ( char** a, char** b, int size ) {
	( *a ) = ( char* )realloc ( *a, ( START_LENGTH_STRING + size ) * sizeof ( char )  );
	( *b ) = ( char* )realloc ( *b, ( START_LENGTH_STRING + size ) * sizeof ( char )  );
}
void Needleman_Wunsch( char* a, char* b ) {
	int i = strlen( a ) ;
	int j = strlen( b ) ;
	int** gap_table = create_table( j + 1, i + 1);
	int** scoring_table = create_scoring_table( a, b, gap_table );
	char* align_a = ( char* )calloc( START_LENGTH_STRING, sizeof ( char ) );
	char* align_b = ( char* )calloc( START_LENGTH_STRING, sizeof( char ) );
	int id = 0;
	for( ;  ( i > 0 && j > 0 ); id++ ) {
		if ( 0 == id % START_LENGTH_STRING ) {
			realloc_string(&align_a, &align_b, id );
        }
		int score = scoring_table[i][j];
		int score_diag = scoring_table[i -1][j - 1];
		int score_up = scoring_table[i][j -1];
		int score_left = scoring_table[i - 1][j];
		if ( score == ( score_diag + check_match( a[i - 1 ], b[j - 1] ) ) ) {
			align_a[id] = a[i - 1];
			align_b[id] = b[j - 1];
			i--;
			j--;
		}
		else if ( i > 0 && score == ( score_left - gap_table[i][j] ) ) {
			align_a[id] = a[i - 1];
			align_b[id] = GAP;
			i--;
		}
		else if (  j > 0 && score == ( score_up - gap_table[i][j] ) ) {
			align_a[id] = GAP;
			align_b[id] = b[j - 1];
			j--; 
		}
		//printf("alig_a = %c alig_b = %c\n",align_a[id], align_b[id] );
	}
	while ( i > 0 ) {
		align_a[id] = a[i - 1];
		align_b[id] = GAP;
		i--;
		id++;
		if ( 0 == id % START_LENGTH_STRING ) {
            realloc_string(&align_a, &align_b, id );
        }
	}
	while ( j > 0 ){
		align_a[id] = GAP;
		align_b[id] = b[j - 1];
		j--;
		id++;
		if ( 0 == id % START_LENGTH_STRING ) {
            realloc_string(&align_a, &align_b, id );
        }
	}
	//printf("id = %d\n", id);
	align_a[id] = '\0';
	align_b[id] = '\0';
	revers( align_a );
	revers( align_b );
	printf("\n%s\n%s\n", align_a, align_b );
	free( align_a );
	free( align_b );
	free_table( gap_table, strlen( a ) + 1 );
	free_table( scoring_table, strlen( a ) + 1 );
}