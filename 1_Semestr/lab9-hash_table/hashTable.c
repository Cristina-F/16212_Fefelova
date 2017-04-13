#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5// Начальный размер хеш-таблицы
#define MAX_LENGTH 30 // Максимальная длинна имени
#define MULT 3

// Проверка длинны имени
int check_name( char* name ) {
	for( int i = 0; '\0' != name[i]; i++ ) {
		if ( i > MAX_LENGTH ) {
			return -1;
		}
	}
	return 0;
}


char* read_name ( char* name ) {
	int num = 0;
	while (1) {
		num = scanf( "%s", name );
		if ( ( 1 != num ) ) {
			while ( '\n' != getchar( ) );
		}
		else if ( -1 == check_name( name ) ){
			while ( '\n' != getchar( ) );
		}
		else {
			break;
		}
		printf( "\n" );
	}
	return name;
}

//Создание  хеш-таблицы
struct hash_table* create_table ( int size_table ) {
	struct hash_table* hash_table = ( struct hash_table* )calloc( 1, sizeof( struct hash_table ) );
	hash_table -> size = size_table;
	hash_table -> cell = ( struct table_cell**)calloc( hash_table -> size, sizeof( struct table_cell ) );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		hash_table -> cell[i] = NULL;
	}
	return hash_table;
}

static int hash_function ( struct hash_table* hash_table, char* name ) {
	int long long  key = 0;
	int divider = hash_table -> size;
	int mult = 1;
	for ( int i = 0; '\0' != name[i]; i++ ) {
		key = key + ( int )name[i] * mult;
		mult *= ( MULT );
	}
	return ( key % divider );
}

// Добавляет элемент в ячейку хеш-таблицы
static void fill_cell( struct hash_table* hash_table, int index, char* name, int height, int weight, int name_length ) {
	hash_table -> cell[index] = ( struct table_cell* )calloc(1, sizeof( struct table_cell ) );
	hash_table -> cell[index] -> name = ( char* )calloc( name_length + 1, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		hash_table -> cell[index] -> name[i] = name[i];
	}
	hash_table -> cell[index] -> height = height;
	hash_table -> cell[index] -> weight = weight;
}

//Добавляет элемент в цепочку
static void fill_chain( struct hash_table* hash_table, struct table_cell* tail, int index, char* name, int height, int weight, int name_length ) {
	tail -> next = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	tail -> next -> name = ( char* )calloc( name_length + 1, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		tail -> next -> name[i] = name[i];
	}
	tail -> next -> height = height;
	tail -> next -> weight = weight;
}

// Освобождение память хеш-таблицы
void free_table ( struct hash_table* hash_table ) {
	struct table_cell** elem = hash_table -> cell;
	for ( int i = 0; i < hash_table -> size; i++ ){
		while ( NULL != hash_table -> cell[i] ) {
			struct table_cell* tmp = hash_table -> cell[i];
			hash_table -> cell[i] = hash_table -> cell[i] -> next;
			free( tmp -> name);
			free( tmp );
		}
		free( hash_table -> cell[i] );
	}
	free( elem );
	free( hash_table );
}

// Запись данных в ячейку хеш-таблицы
static struct hash_table* complete_table ( struct hash_table* hash_table, char* name, int height, int weight, int name_length ) {
	int index = hash_function( hash_table, name );
	printf("index = %d\n", index );
	//Если ячейка пустая, то записываем в нее
	if ( NULL == hash_table -> cell[index] ) {
		fill_cell( hash_table, index, name, height, weight, name_length );
	}
	//Если ячейка занята, то записываем в конец цепочки
	else {
		struct table_cell* tail = hash_table -> cell[index];
		while ( NULL != tail -> next ) {
			tail = tail -> next;
		}
		fill_chain( hash_table, tail, index, name, height, weight, name_length );
	}
	return hash_table;
}

//Перехеширование таблицы
static struct hash_table* rehashing( struct hash_table* hash_table, char* name, int height, int weight ) {
	int new_size_table = ( hash_table -> size ) * 10;
	printf("new_size_table = %d; \n",new_size_table );
	struct hash_table* new_hash_table = create_table( new_size_table );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				new_hash_table = complete_table( new_hash_table, tmp -> name, tmp -> height, tmp -> weight, strlen( tmp -> name ) );
				tmp = tmp -> next;
			}
		}

	}
	new_hash_table = complete_table( new_hash_table, name, height, weight, strlen( name ) );
	free_table( hash_table );
	return new_hash_table;
}

// Считываем данные из файла и записываем в хеш-таблицу
struct hash_table* write_in_table( FILE* in_file, struct hash_table* hash_table ) {
	int count_elem = 0;
	int i = 1;
	while ( !feof( in_file ) ) {
		int name_length = 0;
		count_elem++;
		while ( ' ' != fgetc( in_file ) ) {
			if ( feof( in_file ) ) {
				return hash_table;
			}
			name_length++;
		}
		if ( 0 == name_length ) {
			printf("Record does not contain the name.\n");
			return NULL;
		}
		fseek( in_file, -1 * ( name_length + 1 ), SEEK_CUR );
		char* name = ( char* )calloc( ( name_length + 1 ), sizeof( char ) );
		for ( int i = 0; i < name_length; i++ ) {
			name[i] = fgetc( in_file );
		}
		name[ name_length ]	= '\0';
		int height =  0;
		int weight = 0;
		fscanf( in_file, "%d", &height );
		fscanf( in_file, "%d", &weight );
		fgetc( in_file );
		int stress = ( 3 *( hash_table -> size) ) / 4 ;
		if ( count_elem > stress ) {
			hash_table = rehashing( hash_table, name, height, weight );
		}
		else {
			hash_table = complete_table( hash_table, name, height, weight, name_length );
		}
		free( name );
	}
	return hash_table;
}

// Печать результата поиска
static void print_search( struct table_cell* search ) {
	if ( NULL == search ) {
		printf("Error: Data not found.\n" );
	}
	else {
		printf( "%s %d %d\n", search -> name, search -> height, search -> weight );
	}
}

// Поиск в хеш-таблице
int table_search ( struct hash_table* hash_table, char* name ) {
	struct table_cell* dont_search = NULL;
	int index = hash_function( hash_table, name );
	if ( NULL == hash_table -> cell[index] ) {
		print_search( dont_search );
		return -1;
	}
	else {
		if ( NULL == hash_table -> cell[index] -> next ) {
			if( 0 == strcmp( hash_table -> cell[index] -> name, name ) ) {
				print_search( hash_table -> cell[index] );
				return 0;
			}
			else {
				print_search( dont_search );
				return -1;
			}
		}
		else {
			struct table_cell* tmp  = hash_table -> cell[index];
			while ( NULL != tmp ) {
				if ( 0 == strcmp( tmp -> name, name )) {
					print_search ( tmp );
					return 0;
				}
					tmp = tmp -> next;
			}
			print_search( dont_search );
			return -1;
		}
	}
}
