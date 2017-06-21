#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_LENGTH_STRING 10
#define A 'A'
#define T 'T'
#define C 'C'
#define G 'G'
#define ID_A 0
#define ID_G 1
#define ID_C 2
#define ID_T 3
#define SIZE_TABLE 4
#define GAP_PENALITY -1
#define GAP '-'

void print_table ( int** table, int x, int y ) {
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
static int** create_similarity_table ( ) {
	int** table = create_table( SIZE_TABLE, SIZE_TABLE );
	for ( int i = 0; i < SIZE_TABLE; i++ ) {
		for ( int j = 0; j < SIZE_TABLE; j++ ) {
			if ( i == j ) {
				table[i][j] = 1;
			}
			else {
				table[i][j] = -1;
			}
		}
	}
	print_table( table, SIZE_TABLE, SIZE_TABLE );
	return table; 
}


static int max(int a, int b)
{
	if (a > b) {
		return a;
	}
	else
	{
		return b;
	}
}

static void free_table ( int** table, int y ) {
	for ( int i = 0; i < y; i++ ) {
		free( table[i] );
	}
	free( table );
}
static int get_index_sim_table(char sym)
{
	switch (sym)
	{
	case A:
		return ID_A;
		break;
	case G:
		return ID_G;
		break;
	case C:
		return ID_C;
		break;
	case T:
		return ID_T;
		break;
	}
	return -1;
}

static int value_similarity( int** similarity_table, char sym1, char sym2 ) {
	int i = get_index_sim_table(sym1);
	int j = get_index_sim_table(sym2);
	printf("v = %d %c %c \n", similarity_table[i][j], sym1, sym2 );
	return similarity_table[i][j];
}

static int** create_route_table ( char* a, char* b, int** similarity_table ) {
	int x = strlen( b ) + 1;
	int y = strlen( a ) + 1;
	int** route_table = create_table( x, y );
	for ( int i = 0; i < y; i++ ) {
		route_table[i][0] = i * GAP_PENALITY;
	}
	for ( int i = 0; i < x; i++ ) {
		route_table[0][i] = i * GAP_PENALITY;
	}
	for ( int i = 1; i < y; i++ ) {
		for ( int j = 1; j < x; j++ ) {
			int match = route_table[i - 1][j - 1] + value_similarity( similarity_table, a[i - 1], b[j - 1] );
			int delete = route_table[i -1][j] + GAP_PENALITY;
			int insert = route_table[i][j - 1] + GAP_PENALITY;
			route_table[i][j] = max( max( match, insert ), delete );
		}
	}
	print_table( route_table, x, y );
	return route_table;
}
static void revers (char* string ) {
	if ( string ) {
		int size = strlen( string );
		char tmp = 0;
		for ( int i = 0; i < size - 1; i++ ) {
			tmp = string[i];
			string[i] = string[size];
			string[size] = tmp;
			size--;
		}
	}
}

void Needleman_Wunsch( char* a, char* b ) {
	int i = strlen( a ) ;
	int j = strlen( b ) ;
	printf("%d %d\n", i, j );
	int** similarity_table = create_similarity_table( );
	int** route_table = create_route_table( a, b, similarity_table );
	int align_size = max( i, j );
	char* align_a = ( char* )calloc( align_size + 1, sizeof ( char ) );
	char* align_b = ( char* )calloc( align_size + 1, sizeof( char ) );
	printf("alin size = %d \n", align_size);
	int id = 0;
	for( ; ( i > 0 && j > 0 && id < align_size); id++ ) {
		printf(" id = %d\n", id);
		int score = route_table[i][j];
		int score_diag = route_table[i -1][j - 1];
		int score_up = route_table[i][j -1];
		int score_left = route_table[i - 1][j];
		if ( score == ( score_diag + value_similarity( similarity_table, a[i - 1 ], b[j - 1] ) ) ) {
			printf("A\n");
			align_a[id] = a[i - 1];
			align_b[id] = b[j - 1];
			i--;
			j--;
		}
		else if ( score == ( score_left + GAP_PENALITY ) ) {
			printf("B\n");
			align_a[id] = a[i];
			align_b[id] = GAP;
			i--;
		}
		else if ( score == ( score_up + GAP_PENALITY ) ) {
			printf("C\n");
			align_a[id] = GAP;
			align_b[id] = b[j];
			j--; 
		}
		printf("alig_a = %c alig_b = %c\n",align_a[id], align_b[id] );
	}
	printf("%d\n", id);
	for ( ;i > 0; id++ ) {
		align_a[id] = a[i];
		align_b[id] = GAP;
		i--;
	}
	for(; j > 0; id++ ) {
		align_a[id] = GAP;
		align_b[id] = b[j];
		j--;
	}
	printf("id = %d\n", id);
	align_a[id] = '\0';
	align_b[id] = '\0';
	revers( align_a );
	revers( align_b );
	printf("\n%s\n%s\n", align_a, align_b );
	free( align_a );
	free( align_b );
	free_table( similarity_table, SIZE_TABLE );
	free_table( route_table, strlen( a ) + 1 );
}