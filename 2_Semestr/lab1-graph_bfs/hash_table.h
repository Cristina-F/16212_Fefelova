#if !defined(HASH_TABLE)
#define HASH_TABLE

#include <stdio.h>

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

int check_id ( struct hash_table* hash_table, char* id );
struct hash_table* create_table ( int size_table );
struct table_cell* table_search ( struct hash_table* hash_table, char* id );
struct hash_table* write_in_table(  struct hash_table* hash_table, char* index, int count_elem );
void  print_table ( struct hash_table* table );
void free_table ( struct hash_table* hash_table );

#endif