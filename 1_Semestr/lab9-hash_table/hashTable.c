#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define STRESS 2 // Максимальная длина цепочки
#define MAX_LENGTH 30 // Максимальная длинна имени

int SIZE_TAB[] = { 3, 17, 19, 37, 101, 211, 409, 701, 997, 2003, 4451, 7177, 9973  };

//Создание  хеш-таблицы
struct hash_table* create_table ( int size_table, int rehash ) {
	struct hash_table* hash_table = ( struct hash_table* )calloc( 1, sizeof( struct hash_table ) );
	hash_table -> size = size_table;
	hash_table -> rehash = rehash;
	hash_table -> cell = ( struct table_cell**)calloc( hash_table -> size, sizeof( struct table_cell ) );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		hash_table -> cell[i] = NULL;
	}
	return hash_table;
}

static int hash_function ( struct hash_table* hash_table, char* name ) {
	int key = 0;
	int divider = hash_table -> size;
	for ( int i = 0; '\0' != name[i]; i++ ) {
		key = key + ( int )name[i];
	}
	return ( key % divider );
}

// Добавляет элемент в ячейку хеш-таблицы
static void fill_cell( struct hash_table* hash_table, int index, char* name, int height, int weight, int name_length ) {
	hash_table -> cell[index] = ( struct table_cell* )calloc(1, sizeof( struct table_cell ) );
	hash_table -> cell[index] -> name = ( char* )calloc( name_length, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		hash_table -> cell[index] -> name[i] = name[i];
	}
	hash_table -> cell[index] -> height = height;
	hash_table -> cell[index] -> weight = weight;
}

//Добавляет элемент в цепочку
static void fill_chain( struct hash_table* hash_table, struct table_cell* tail, int index, char* name, int height, int weight, int name_length ) {
	tail -> next = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	tail -> next -> name = ( char* )calloc( name_length, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		tail -> next -> name[i] = name[i];
	}
	tail -> next -> height = height;
	tail -> next -> weight = weight;
}

//Перехеширование таблицы
static struct hash_table* rehashing( struct hash_table* hash_table, int* rehash ) {
	*rehash = 0;
	hash_table -> rehash = ( hash_table -> rehash ) + 1;
	int new_size_table = SIZE_TAB[hash_table -> rehash];
	struct hash_table* new_hash_table = create_table( new_size_table, hash_table -> rehash );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				int new_index = hash_function( new_hash_table, tmp -> name  );
				if ( NULL == new_hash_table -> cell[new_index] ) {
					fill_cell( new_hash_table, new_index, tmp -> name, tmp -> height, tmp -> weight, strlen( tmp -> name));
				}
				else {	
					int count  = 1;
					struct table_cell* tail = new_hash_table -> cell[new_index];
					while ( NULL != tail -> next ) {
						count++;
						if ( count >= STRESS ) {
							*rehash = 1;
						}
						tail = tail-> next;
					}
					fill_chain( new_hash_table, tail, new_index, tmp -> name, tmp -> height,tmp -> weight, strlen( tmp -> name) );
				}
				tmp = tmp -> next;
			}
		}
	}
	free( hash_table );
	return new_hash_table;
}

// Запись данных в ячейку хеш-таблицы
static struct hash_table* complete_table ( struct hash_table* hash_table, char* name, int height, int weight, int name_length, int* rehash ) {
	int index = hash_function( hash_table, name );
	//Если ячейка пустая, то записываем в нее
	if ( NULL == hash_table -> cell[index] ) {
		fill_cell( hash_table, index, name, height, weight, name_length );
	}
	//Если ячейка занята, то записываем в конец цепочки
	else {
		int count  = 1;
		struct table_cell* tail = hash_table -> cell[index];
		while ( NULL != tail -> next ) {
			count++;
			if ( count >= STRESS ) {
				*rehash = 1;
			}
			tail = tail -> next;
		}
		fill_chain( hash_table, tail, index, name, height, weight, name_length);
	}
	return hash_table;
}

// Считываем данные из файла и записываем в хеш-таблицу
struct hash_table* write_in_table( FILE* in_file, struct hash_table* hash_table ) {
	int rehash = 0;
	while ( !feof( in_file ) ) {
		int name_length = 0;
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
		hash_table = complete_table( hash_table, name, height, weight, name_length , &rehash );
		free( name );
	}
	while ( 1 == rehash ){
		hash_table = rehashing( hash_table, &rehash );
	}
	return hash_table;
}

// Проверка длинны имени
int check_name( char* name ) {
	for( int i = 0; '\0' != name[i]; i++ ) {
		if ( i > MAX_LENGTH ) {
			return -1;
		}
	}
	return 0;
}

// Поиск в хеш-таблице
struct table_cell* table_search ( struct hash_table* hash_table, char* name) {
	int index = hash_function( hash_table, name );

	if ( NULL == hash_table -> cell[index] ) {
		return NULL;
	}
	else {
		if ( NULL == hash_table -> cell[index] -> next ) {
			if( 0 == strcmp( hash_table -> cell[index] -> name, name ) ) {
				return hash_table -> cell[index];
			}
			else {
				return NULL;
			}
		}
		else {
			struct table_cell* tmp  = hash_table -> cell[index];
			while ( NULL != tmp ) {
				if ( 0 == strcmp( tmp -> name, name ) ) {
					return tmp;
				}
				tmp = tmp -> next;
			}
			return NULL;
		}
	}
}

// Печать результата поиска
void print_search( struct table_cell* search ) {
	if ( NULL == search ) {
		printf("Error: Data not found.\n" );
	}
	else {
		printf( "%s %d %d\n", search -> name, search -> height, search -> weight );
	}
}

// Печать хеш-таблицы
void print_table ( struct hash_table* table ) {
	printf("\n");
	printf("size_table = %d;\n", table -> size );
	printf("rehash = %d;\n", table -> rehash);
	for ( int i = 0; i < table -> size; i++ ) {
		int t = 0;
		if ( NULL != table -> cell[i] ) {
			struct table_cell* tmp = table -> cell[i];
			while ( NULL != tmp ) {
				printf( "%s ", tmp -> name );
				printf( "%d ", tmp -> height );
				printf( "%d ", tmp -> weight );
				printf("index = %d;\n", i);
				tmp = tmp -> next;
			}
		}
	}
	printf("\n");
}

// Освобождение память хеш-таблицы
void free_table ( struct hash_table* hash_table ) {
	for ( int i = 0; i < hash_table -> size; i++ ){
		while ( NULL != hash_table -> cell[i] ) {
			struct table_cell* tmp = hash_table -> cell[i];
			hash_table -> cell[i] = hash_table -> cell[i] -> next;
			free( tmp );
		}
		free( hash_table -> cell[i] );
	}
	free( hash_table );
}
