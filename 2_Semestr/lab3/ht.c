#include "ht.h"
#include "gr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Освобождение памяти списка
static void free_list( struct list_sibl* head ) {
	while( head ) {
		struct list_sibl* tmp = head;
		head = head -> next;
		free( tmp );
	}
	free( head );
 }
 
// Освобождение память хеш-таблицы
void free_table ( struct hash_table* hash_table ) {
	struct table_cell** elem = hash_table -> cell;
	for ( int i = 0; i < hash_table -> size; i++ ) {
		while ( NULL != hash_table -> cell[i] ) {
			struct table_cell* tmp = hash_table -> cell[i];
			hash_table -> cell[i] = hash_table -> cell[i] -> next;
			free_list( tmp -> siblings);
			free( tmp );
		}
		free( hash_table -> cell[i] );
	}
	free( elem );
	free( hash_table );
}

//Создание  хеш-таблицы
struct hash_table* create_table ( int size_table ) {
	struct hash_table* hash_table = ( struct hash_table* )calloc( 1, sizeof( struct hash_table ) );
	hash_table -> size = size_table;
	hash_table -> cell = ( struct table_cell**)calloc( hash_table -> size, sizeof( struct table_cell* ) );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		hash_table -> cell[i] = NULL;
	}
	return hash_table;
}

//Хеш-функция
static int hash_function ( struct hash_table* hash_table, int id ) {
	int long long  key = 0;
	int divider = hash_table -> size;
	int mult = 1;
	for ( int i = 0; id > 0; i++ ) {
		key = key + ( id % 10 ) * mult;
		id = id / 10;
		mult *= ( MULT );
	}
	return ( key % divider );
}

//Проверяем есть ли такой элемент уже в хеш-таблице
int check_id ( struct hash_table* hash_table, int id ) {
	int index = hash_function( hash_table, id );
	struct table_cell* elem = hash_table -> cell[index];
	while( elem ) {
		if ( id  == elem -> id ) {
			return 1;
		}
		elem = elem -> next;
	}
	return 0;
}

// Поиск в хеш-таблице
struct table_cell* table_search ( struct hash_table* hash_table, int id ) {
	int index = hash_function( hash_table, id );
	if ( NULL == hash_table -> cell[index] ) {
		return NULL;
	}
	else {
		if ( NULL == hash_table -> cell[index] -> next ) {
			if( id == hash_table -> cell[index] -> id ) {
				return hash_table -> cell[index];
			}
			else {
				return NULL;
			}
		}
		else {
			struct table_cell* tmp  = hash_table -> cell[index];
			while ( NULL != tmp ) {
				if ( id == tmp -> id ) {
					return tmp;
				}
					tmp = tmp -> next;
			}
			return NULL;
		}
	}
}

// Добавляет элемент в ячейку хеш-таблицы
static void fill_cell( struct hash_table* hash_table, int index, int id, int num_sibl ) {
	hash_table -> cell[index] = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	hash_table -> cell[index] -> id = id;
	hash_table -> cell[index] -> num_siblings = num_sibl;
	hash_table -> cell[index] -> visited = UNVISITED;
	hash_table -> cell[index] -> siblings = NULL;
}

//Добавляет элемент в цепочку
static void fill_chain( struct hash_table* hash_table, struct table_cell* tail, int index, int id, int num_sibl ) {
	tail -> next = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	tail -> next -> id = id;
	tail -> next -> num_siblings = num_sibl;
	tail -> next -> visited = UNVISITED;
	tail -> next -> siblings = NULL;
}

// Запись данных в ячейку хеш-таблицы
static struct hash_table* complete_table ( struct hash_table* hash_table, int id,  int num_sibl ) {
	int index = hash_function( hash_table, id);
	//Если ячейка пустая, то записываем в нее
	if ( NULL == hash_table -> cell[index] ) {
		fill_cell( hash_table, index, id, num_sibl );
	}
	//Если ячейка занята, то записываем в конец цепочки
	else {
		struct table_cell* tail = hash_table -> cell[index];
		while ( NULL != tail -> next ) {
			tail = tail -> next;
		}
		fill_chain( hash_table, tail, index, id, num_sibl );
	}
	return hash_table;
}

static struct hash_table* copy_siblings( struct hash_table* hash_table, struct hash_table* new_hash_table ) {
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				struct list_sibl* sibl = tmp -> siblings;
				while( sibl ){
					add_siblings( new_hash_table, tmp -> id, sibl -> t_cell -> id , sibl -> weight );
					sibl = sibl -> next;
				}
				tmp = tmp -> next;
			}
		}
	}
	return new_hash_table;
}

//Перехеширование таблицы
static struct hash_table* rehashing( struct hash_table* hash_table, int id ) {
	int new_size_table = ( hash_table -> size ) * 10;
	struct hash_table* new_hash_table = create_table( new_size_table );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				new_hash_table = complete_table( new_hash_table, tmp -> id, tmp -> num_siblings );
				tmp = tmp -> next;
			}
		}
	}
	new_hash_table = complete_table( new_hash_table, id, 0 );
	new_hash_table = copy_siblings( hash_table,  new_hash_table );
	free_table( hash_table );
	return new_hash_table;
}

// Заносим данные в хеш-таблицу
struct hash_table* write_in_table(  struct hash_table* hash_table, int id, int count_elem ) {
	int stress = ( 3 *( hash_table -> size) ) / 4 ;
	if ( count_elem > stress ) {
		hash_table = rehashing( hash_table, id );
	}
	else {
		hash_table = complete_table( hash_table, id, 0 );
	}
	return hash_table;
}


//Печать хеш-таблицы
void print_table ( struct hash_table* t ) {
	printf("\n");
	struct hash_table* table  = t;
	printf("size_table = %d;\n", table -> size );
	for ( int i = 0; i < table -> size; i++ ) {
		int t = 0;
		if ( NULL != table -> cell[i] ) {
			struct table_cell* tmp = table -> cell[i];
			while ( NULL != tmp ) {
				printf( "id = %d ", tmp -> id );
				printf( "num_siblings = %d; ", tmp -> num_siblings );
				printf("v = %d ", tmp -> visited );
				struct list_sibl* sibl = tmp -> siblings;
				while( sibl ) {
					printf("%d ",sibl -> t_cell -> id );
					sibl = sibl -> next;
				}
				printf("index = %d;\n", i);
				tmp = tmp -> next;
			}
		}
	}
	printf("\n");
}

void print_table2 ( struct hash_table* t ) {
	printf("\n");
	struct hash_table* table = t;
	printf("size_table = %d;\n", table -> size );
	for ( int i = 0; i < table -> size; i++ ) {
		if ( NULL != table -> cell[i] ) {
			struct table_cell* tmp = table -> cell[i];
			while ( NULL != tmp ) {
				printf("index = %d;\n", i);
				struct list_sibl* sibl = tmp -> siblings;
				while( sibl ) {
					printf("id1 = %d id2 = %d w = %d \n", tmp -> id, sibl -> t_cell -> id , sibl -> weight );
					sibl = sibl -> next;
				}
				
				tmp = tmp -> next;
			}
		}
	}
	printf("\n");
}

