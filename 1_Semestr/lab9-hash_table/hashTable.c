#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define SIZE 10 // Размер таблицы
#define MAX_LENGTH 30 // Максимальная длинна имени

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
	int key = 0;
	int divider = hash_table -> size;
	for ( int i = 0; i < strlen( name ); i++ ) {
		key = key + ( int )name[i];
	}
	return ( key % divider );
}
// Запись данных в ячейку хеш-таблицы
static struct hash_table* complete_table ( struct hash_table* hash_table, char* name, int height, int weight ) {
	int index = hash_function( hash_table, name );
	//Если ячейка пустая, то записываем в нее
	if ( NULL == hash_table -> cell[index] ) {
		hash_table -> cell[index] = ( struct table_cell* )calloc(1, sizeof( struct table_cell ) );
		hash_table -> cell[index] -> name = ( char* )calloc( strlen( name ), sizeof( char ) );
		for ( int i = 0; i < strlen( name ); i++ ) {
			hash_table -> cell[index] -> name[i] = name[i];
		}
		hash_table -> cell[index] -> height = height;
		hash_table -> cell[index] -> weight = weight;
	}
	//Если ячейка занята, то записываем в конец цепочки
	else {
		struct table_cell* tmp = hash_table -> cell[index];
		while ( NULL != tmp -> next ) {
			tmp = tmp -> next;
		}
		struct table_cell* tail = tmp;
		tail -> next = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
		tail -> next -> name = ( char* )calloc( strlen( name ), sizeof( char ) );
		for ( int i = 0; i < strlen( name ); i++ ) {
			tail -> next -> name[i] = name[i];
		}
		tail -> next -> height = height;
		tail -> next -> weight = weight;
	}
	return hash_table;
}
// Считываем данные из файла и записываем в хеш-таблицу
struct hash_table* write_in_table( FILE* in_file, struct hash_table* hash_table ) {
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
		char* name = ( char* )calloc( name_length + 1, sizeof( char ) );
		for ( int i = 0; i < name_length; i++ ) {
			name[i] = fgetc( in_file );
		}
		name[ name_length ]	= '\0';
		int height =  0;
		int weight = 0;
		fscanf( in_file, "%d", &height );
		fscanf( in_file, "%d", &weight );
		fgetc( in_file );
		hash_table = complete_table( hash_table, name, height, weight);
		free( name );
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
	for ( int i = 0; i < table -> size; i++ ) {
		if ( NULL != table -> cell[i] ) {
			struct table_cell* tmp = table -> cell[i];
			while ( NULL != tmp ) {
				printf( "%s ", tmp -> name );
				printf( "%d ", tmp -> height );
				printf( "%d\n", tmp -> weight );
				tmp = tmp -> next;
			}
		}
	}
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
