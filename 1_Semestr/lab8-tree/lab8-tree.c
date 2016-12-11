#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT 0
#define RIGHT 1

struct list {
	int data;
	struct list* next;
};

struct tree {
	int key;
	struct tree* left;
	struct tree* right;
};
// Создаем новый узел в списке
struct list* creatList ( int x ) {
	struct list* new = ( struct list* )calloc( 1, sizeof( struct list ) );
	new -> data = x;
	new -> next = NULL;
	return new;
}
// Считываем число из файла
int read_number ( FILE* file, char* read) { 
	int number = 0;
	int sgn = 1;
	while ( ( *read = fgetc( file ) ) != ' ' ) {
		if ( EOF == *read) {
			break;
		}
		if ( '\n' == *read ) {
			continue;
		}
		if ( '-' == *read ) {
			sgn = -1;
			continue;
		}
		number = number * 10 + atoi( read );
	} 
	number *= sgn;
	return number;
}
// Записываем числа в список
struct list* write_number ( FILE *file ) {
	char read = 0;
	struct list* head = creatList( read_number( file, &read) );
	struct list* counter = head;
	int number = 0;
	while ( read != EOF ) {
		number = read_number( file, &read );
		counter -> next = creatList( number );
		counter = counter -> next;
	}
	counter = head;
	return head;
}
// Считаем длинну списка
int length ( struct list* head ) {
	int count = 0;
	struct list* counter = head;
	while ( NULL != counter ) {
		count++;
		counter = counter -> next;
	}
	return count;
}
// Делим список на два подсписка
void divide ( struct list* input, struct list** left, struct list** right ) {
	int size = length( input );
	struct list* actual = input;
	if ( size < 2 ) {
		*left = input;
		*right = NULL;
	}
	else {
		int middle = ( size - 1 ) / 2;
		for ( int i = 0; i < middle; i++ ) {
			actual = actual -> next;
		}
		*left = input;
		*right = actual -> next;
		actual -> next = NULL;
	}
}
// Объединяем два подсписка
struct list* merge_sort ( struct list* left, struct list* right ) {
	struct list* result = NULL;
	if ( NULL == left ) {
		return right;
	}
	if ( NULL == right ) {
		return left;
	}
	if ( left -> data <= right -> data ) {
		result = left;
		result -> next = merge_sort( left -> next, right );
	}
	else {
		result = right;
		result -> next = merge_sort( left, right -> next );
	}
	return result;
}

// Сортировка списка
void merge_list ( struct list** start ) {
	struct list* head = *start;
	struct list* left = NULL;
	struct list* right = NULL;
	if ( ( NULL == head ) || ( NULL == head -> next ) ) {
		return;
	}
	divide( head, &left, &right );
	merge_list( &left );
	merge_list( &right );
	*start = merge_sort( left, right );
}
// Удаляем из списка одиннаковые элементы
struct list* delete (struct list* head){
	struct list* tmp = head;
	while(NULL != tmp-> next){
		if( tmp -> data == tmp -> next -> data){
			struct list* follow = tmp -> next -> next;
			free(tmp -> next);
			tmp -> next= follow;
		}
		else {
			tmp =tmp -> next;
		}
	}
	return head;
}
// Создаем сбалансированное дерево
struct tree* createTree( struct list* head, int size, int side) {
	if ( 0 == size ) {
		return NULL;
	}
	struct list* counter = head;
	int bias = 0;
	if ( ( 0 == size % 2 ) && ( RIGHT == side) ) {
		bias = 1;
	}
	int mid = ( size / 2 ) - bias; 
	struct tree* root = ( struct tree* )calloc( 1, sizeof( struct tree ) );
	for ( int i = 0; i < mid; i++) {
		counter = counter -> next;
	}
	root -> key = counter -> data;
	root -> left = createTree( head, mid, LEFT ); 
	root -> right = createTree( counter -> next, size-mid-1, RIGHT );
	return root;
}
// Печать дерева на экран
void print_tree( struct tree* root, int count ) {
	if ( count > 0) {
		printf( "\n|" );
		for( int i = 0; i < count; i++ ) {
			printf( "  " );
		}
		printf( "|\n|  " );	
		for( int i = 0; i < count; i++ ) {
			if( i + 1 < count ) {
				printf( "  " );
			} 
			else {
				printf( " -" );
			}	
		}
	}
	if ( NULL != root ) {
		printf( "(%d)", root -> key );
		if ( 0 == count ) {
			printf( "--" );
		}
		count++;
		print_tree( root -> right, count );
		print_tree( root -> left, count );
	}
}
// Освобождаем память списка
void free_list ( struct list* head ) {
	for( int i = 0; i < length( head ); i++ ) {
		struct list* tmp = head;
		head = head -> next;
		free( tmp );
	}
	free( head );
}
// Освобождаем память дерева
void free_tree ( struct tree* root ) {
	if ( root -> left ) {
		free_tree( root -> left );
	}
	if ( root -> right ) {
		free_tree( root -> right );
	}
	free ( root );
}

int main ( int argc, char* argv[ ] ) {
	FILE *in_file = NULL;
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
	struct list *head = write_number( in_file );
	merge_list( &head );
	delete(head);
	struct tree * root = createTree( head, length( head ), RIGHT );
	print_tree( root, 0 );
	printf("\n");
	free_list( head );
	free_tree( root );
	fclose ( in_file );
	return 0;
}
