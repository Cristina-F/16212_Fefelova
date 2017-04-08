#if !defined(GRAPH)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRAPH


//Хеш-таблица
struct hash_table {
	struct table_cell** cell;
	int size;
};

//Ячейки хеш-таблицы
struct table_cell {
	char* id;
	int num_siblings;
	int visited;
	int distance;
	struct list* siblings;
	struct table_cell* next;
};

//Список соседей
struct list {
	struct table_cell* t_cell;
	struct list* next;
};


struct hash_table* create_table ( int size_table );
int check_input_data( int argc, char* name_file );
struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file  );
void  print_table ( struct hash_table* table );
int bfs( struct hash_table* hash_table );
void free_table ( struct hash_table* hash_table );
#endif
