#include "header_queue.h"
#include "header_graph.h"

#define MULT 3
#define VISITED 1
#define UNVISITED 0

//Освобождение памяти списка
static void free_list( struct list* head ) {
	while( head ) {
		struct list* tmp = head;
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
			free( tmp -> id);
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
	hash_table -> cell = ( struct table_cell**)calloc( hash_table -> size, sizeof( struct table_cell ) );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		hash_table -> cell[i] = NULL;
	}
	return hash_table;
}

static char* itoa( int n ) {
	int size = 0;
	int work = n;
	while( 0 != work ) {
		work /= 10;
		size++;
	}
	if ( 0 == n ) {
		size = 1;
	}
	char* out_str = ( char* )calloc( size + 1, sizeof( char ) );
	for( int i = ( size - 1 ); i >= 0; i-- ) {
		out_str[i] = '0' + (n % 10);
		n %= 10;
	}
	return out_str;
}

//Хеш-функция
static int hash_function ( struct hash_table* hash_table, char* id ) {
	int long long  key = 0;
	int divider = hash_table -> size;
	int mult = 1;
	for ( int i = 0; '\0' != id[i]; i++ ) {
		key = key + ( int )id[i] * mult;
		mult *= ( MULT );
	}
	return ( key % divider );
}

int check_input_data( int argc, char* name_file ) {
	if ( 2 != argc ) {
		printf( "Error: incorrect input data.\n" );
		return -1;
	}
	else {
		FILE* in_file = fopen( name_file, "r" );
		if ( NULL == in_file ) {
			printf( "Can not open %s.\n", name_file );
			return -2;
		}
		fclose( in_file );
	}
	return 0;
}

//Проверяем есть ли такой элемент уже в хеш-таблице
static int check_id ( struct hash_table* hash_table, char* id ) {
	int index = hash_function( hash_table, id );
	struct table_cell* elem = hash_table -> cell[index];
	while( elem ) {
		if ( 0 == strcmp ( elem -> id, id ) ) {
			return 1;
		}
		elem = elem -> next;
	}
	return 0;
}

// Поиск в хеш-таблице
static struct table_cell* table_search ( struct hash_table* hash_table, char* id ) {
	int index = hash_function( hash_table, id );
	if ( NULL == hash_table -> cell[index] ) {
		return NULL;
	}
	else {
		if ( NULL == hash_table -> cell[index] -> next ) {
			if( 0 == strcmp( hash_table -> cell[index] -> id, id ) ) {
				return hash_table -> cell[index];
			}
			else {
				return NULL;
			}
		}
		else {
			struct table_cell* tmp  = hash_table -> cell[index];
			while ( NULL != tmp ) {
				if ( 0 == strcmp( tmp -> id, id )) {
					return tmp;
				}
					tmp = tmp -> next;
			}
			return NULL;
		}
	}
}

// Добавляет элемент в ячейку хеш-таблицы
static void fill_cell( struct hash_table* hash_table, int index, char* id, int num_sibl,  int name_length ) {
	hash_table -> cell[index] = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	hash_table -> cell[index] -> id = ( char* )calloc( name_length + 1, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		hash_table -> cell[index] -> id[i] = id[i];
	}
	hash_table -> cell[index] -> num_siblings = num_sibl;
	hash_table -> cell[index] -> visited = UNVISITED;
	hash_table -> cell[index] -> distance = -1;
	hash_table -> cell[index] -> siblings = NULL;
}

//Добавляет элемент в цепочку
static void fill_chain( struct hash_table* hash_table, struct table_cell* tail, int index, char* name, int num_sibl, int name_length ) {
	tail -> next = ( struct table_cell* )calloc( 1, sizeof( struct table_cell ) );
	tail -> next -> id = ( char* )calloc( name_length + 1, sizeof( char ) );
	for ( int i = 0; i < name_length; i++ ) {
		tail -> next -> id[i] = name[i];
	}
	tail -> next -> num_siblings = num_sibl;
	tail -> next -> visited = VISITED;
	tail -> next -> distance = -1;
	tail -> next -> siblings = NULL;
}

// Запись данных в ячейку хеш-таблицы
static struct hash_table* complete_table ( struct hash_table* hash_table, char* id,  int num_sibl,  int name_length ) {
	int index = hash_function( hash_table, id);
	//Если ячейка пустая, то записываем в нее
	if ( NULL == hash_table -> cell[index] ) {
		fill_cell( hash_table, index, id, num_sibl,  name_length );
	}
	//Если ячейка занята, то записываем в конец цепочки
	else {
		struct table_cell* tail = hash_table -> cell[index];
		while ( NULL != tail -> next ) {
			tail = tail -> next;
		}
		fill_chain( hash_table, tail, index, id, num_sibl, name_length );
	}
	return hash_table;
}

//Добавляем соседей
static void add_siblings( struct hash_table* hash_table, char* actual_name, char* sibl ) {
	struct list* new_elem = ( struct list* )calloc( 1, sizeof( struct list ) );
	struct table_cell* elem1 = table_search( hash_table, actual_name );
	struct table_cell* elem2 = table_search( hash_table, sibl );
	new_elem -> t_cell = elem2; 
	(new_elem -> t_cell -> num_siblings)++;
	struct list* buff = elem1 -> siblings;
	elem1 -> siblings = new_elem;
	elem1 -> siblings -> next = buff;
}

static struct hash_table* copy_siblings( struct hash_table* hash_table, struct hash_table* new_hash_table ) {
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				struct list* sibl = tmp -> siblings;
				while( sibl ){
					add_siblings( new_hash_table, tmp -> id, sibl -> t_cell -> id );
					sibl = sibl -> next;
				}
				tmp = tmp -> next;
			}
		}
	}
	return new_hash_table;
}

//Перехеширование таблицы
static struct hash_table* rehashing( struct hash_table* hash_table, char* ind ) {
	int new_size_table = ( hash_table -> size ) * 10;
	struct hash_table* new_hash_table = create_table( new_size_table );
	for ( int i = 0; i < hash_table -> size; i++ ) {
		struct table_cell* tmp = hash_table -> cell[i];
		if ( NULL != tmp ) {
			while ( NULL != tmp ){
				new_hash_table = complete_table( new_hash_table, tmp -> id, tmp -> num_siblings,  strlen( tmp -> id ) );
				tmp = tmp -> next;
			}
		}
	}
	new_hash_table = complete_table( new_hash_table, ind, 0, strlen( ind ) );
	new_hash_table = copy_siblings( hash_table,  new_hash_table );
	free_table( hash_table );
	return new_hash_table;
}

// Заносим данные в хеш-таблицу
static struct hash_table* write_in_table(  struct hash_table* hash_table, char* index, int count_elem ) {
	int stress = ( 3 *( hash_table -> size) ) / 4 ;
	int name_length = strlen( index );
	if ( count_elem > stress ) {
		hash_table = rehashing( hash_table, index );
	}
	else {
		hash_table = complete_table( hash_table, index, 0,  name_length );
	}
	return hash_table;
}

//Добавляем вершины графа
struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file  ) {
	int id_node1 = 0;
	int id_node2 = 0;
	int ok = 0;
	int count_elem = 0;
	while( ok != EOF ) {
		ok = fscanf( in_file, "%d%d", &id_node1, &id_node2 );
		if ( 2 == ok ) {
			char* id1 = itoa( id_node1 );
			char* id2 = itoa( id_node2 );
			if ( !check_id( hash_table, id1) ) {
				hash_table = write_in_table( hash_table, id1, ++count_elem );
			}
			if ( !check_id( hash_table, id2) ) {
				hash_table = write_in_table( hash_table, id2, ++count_elem );
			}
			add_siblings(hash_table, id1, id2);
			add_siblings( hash_table, id2, id1);
			free( id1 );
			free( id2 );
		}
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
				printf( "id = %s ", tmp -> id );
				printf( "num_siblings = %d; ", tmp -> num_siblings );
				printf("v = %d ", tmp -> visited );
				printf("dis = %d sibl: ",tmp -> distance );
				struct list* sibl = tmp -> siblings;
				while( sibl ) {
					printf("%s ",sibl -> t_cell -> id );
					sibl = sibl -> next;
				}
				printf("index = %d;\n", i);
				tmp = tmp -> next;
			}
		}
	}
	printf("\n");
}

//Обход графа в ширину
int bfs( struct hash_table* hash_table ) {
	struct table_cell* start = table_search( hash_table,  "0");
	start -> visited = VISITED;
	start -> distance = 0;
	struct queue* q = create_queue( );
	add_queue( q, start -> id );
	while(	q -> head ){
		struct table_cell* tmp = table_search( hash_table, q -> head -> x );
		struct list* tmp1 = tmp -> siblings;
		printf("%s ", tmp -> id);
		while( tmp1 ){
			struct table_cell* new_node = table_search(hash_table, tmp1 -> t_cell -> id );
			if ( UNVISITED == ( new_node -> visited ) ) {
				add_queue( q, new_node -> id );
				new_node -> visited = VISITED;
				new_node -> distance = ( tmp -> distance ) + 1;
			}
			tmp1 = tmp1 -> next;
		}
		tmp -> visited = VISITED;
		poll_queue( q );
	}
	free( q );
	printf( "\n" );
	return 0;
}
