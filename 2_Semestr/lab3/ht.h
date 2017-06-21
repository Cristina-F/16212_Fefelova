#if !defined(HASH_TABLE)
#define HASH_TABLE

#include <stdio.h>

#define MULT 3
#define VISITED 1
#define UNVISITED 0

//Хеш-таблица
struct hash_table {
	struct table_cell** cell;
	int size;
};

//Ячейки хеш-таблицы
struct table_cell {
	int id;
	int num_siblings;
	int visited;
	struct table_cell* parent;
	struct list_sibl* siblings;
	struct table_cell* next;
};

//Список соседей
struct list_sibl {
	int weight;
	int flow;
	struct table_cell* t_cell;
	struct list_sibl* next;
};

void print_table2 ( struct hash_table* t );
int check_id ( struct hash_table* hash_table, int id ) ;
struct hash_table* create_table ( int size_table );
struct table_cell* table_search ( struct hash_table* hash_table, int id ) ;
struct hash_table* write_in_table(  struct hash_table* hash_table, int id, int count_elem );
void  print_table ( struct hash_table* table );
void free_table ( struct hash_table* hash_table );

#endif