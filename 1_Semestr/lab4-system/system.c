#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define START_SIZE 5
#define MIN 2
#define TEN 10
#define ALPHA "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

// Считываем основание системы счисления
int read_base ( int n ) {
	int count = 0;
	int num = 0;
	while (1) {
		num = scanf( "%d", &n);
		if ( ( 1 != num ) || ( MIN > n ) || ( strlen( ALPHA ) < n ) ) {
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
		printf( "Enter a positive integer number from 2 to 36\n" );
		count = 0;
	}
	return n;
}
//Считываем число с экрана консоли
char* read_number ( char* string ) {
	char* new_string = NULL;
	string = ( char* )calloc( START_SIZE, sizeof( char ) );
	char symbol = 0;
	int size = START_SIZE ;
	for ( int i = 0; '\n' != ( symbol = getchar( ) ); i++ ) {
		if ( size == (i + 1) ) {
			size *= START_SIZE;
			new_string = ( char* ) realloc( string, size * sizeof( char ) );
			if ( NULL == new_string ) {
				free( string );
				return NULL;
			}
			string = new_string;
		}
		string[i] = symbol;
	}
	return string;
}
//Проверка числа
int check_number( char* number, int from ) {
	int i = 0;
	while ( '\0' != number[i] ) {
		if( ( number[i] >= '0' && number[i] <= '9' ) || ( number[i] >= 'A' && number[i] <= 'Z' ) 
			|| '-' == number[0]  ||  '+' == number[0] ) {
				if ( from > TEN ) {
					if ( ( number[i] >= '0' && number[i] <= '9' ) || ( number[i] <= 'A' + from - TEN - 1 && number[i] >= 'A' ) 
						|| ( '-' == number[0] ) || ( '+' == number[0] ) ) {
					}
					else {
						printf( "The number does not match the number system.\n" );
						return -1;
					}
				}
				else {
					if ( ( number[i] <= '0' + from - 1 && number[i] >= '0' ) || ( '-' == number[i] ) || ( '+' == number[i] ) ) {

					}
					else {
						printf( "The number does not match the number system.\n" );
						return -1;
					}
				}
			}
		else {
			printf( "Invalid characters.\n" );
			return -1;
		}
		i++;
	}
	return 0;
}
// Переводим число в десятичную систему счисления
int to_ten ( char* string, int from, int* overflow ) {
	int ten = 0;
	int j = 0;
	char symbol = 0;
	if ( '-' == string[0] || '+' == string[0] ) {
		j = 1;
	}
	for ( int i = strlen( string ) - 1 - j; i >= 0; i--, j++ ) {
		if ( ( INT_MAX - symbol ) / from >= ten ) {
			symbol = strchr( ALPHA, string[j] ) - ALPHA;
			ten = ( ten * from ) + symbol;
		}
		else {
			printf( "OVERFLOW!!!\n" );
			*overflow = -1;
			return -1;
		}
	}
	if ( '-' == string[0] ) {
		return ( -1 * ten );
	}
	return ten;
}
// Считаем размер нового числа
int size_new_number ( int number, int to ) {
	int count = 0;
	int sgn = 0;
	if ( number < 0 ) {
		number *= -1;
		sgn = 1;
	}
	for ( count; number > 0; count++ ) {
		number = number / to;
	}
	return ( count + sgn );
}
// Переводим число в новую систему счисления
char* translate( int number, int to ) {
	int sgn = 0;
	int size = size_new_number( number, to );
	if ( number < 0 ){
		sgn = -1;
		number *= sgn;
	}
	char* new_number = ( char* ) calloc( size, sizeof( char ) );
	for ( int i = size - 1; i >= 0; i-- ){
		if ( 0 == i && -1 == sgn ) {
			new_number[i] = '-';
		}
		else {
			new_number[i] = number % to;
			number = number / to;
		}
	}
	return new_number;
}
// Выводим результат на экран
void print_result( char* string, int from, int to, char* number, int ten_num  ) {
	printf( "The number " );
	for ( int i = 0; '\0' != string[i]; i++ ) {
		printf( "%c", string[i] );
	}
	printf( " of the system with the base %d is translated in the base %d as a ", from, to );
	if ( 0 == ten_num ) {
		printf("0");
	}
	else {
		for (int i = 0; i < size_new_number(ten_num, to); i++) {
			if ( '-' == number[i] ) {
				printf( "%c", number[i] );
			} 
			else {
				printf( "%d", number[i] );
			}
		}
	}
	printf( ".\n" );
}

int main ( ) {
	printf( "Enter the original base number system: " );
	int from = read_base( from );
	printf( "Enter the number: " );
	char *number = read_number( number );
	int chek = check_number( number, from );
	if ( -1 == chek ) {
		free( number );
		return -1;
	}
	printf( "Enter the new base of the number system: " );
	int to = read_base( to );
	int overflow = 0;
	int ten_num = to_ten( number, from, &overflow );
	if ( -1 == overflow ) {
		free( number );
		return -1;
	} 
	char* new_number = translate( ten_num, to );
	print_result ( number, from, to, new_number, ten_num );
	free( number );
	free( new_number );
	return 0;
}
	
