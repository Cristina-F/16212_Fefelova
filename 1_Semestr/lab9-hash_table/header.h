#if !defined(HASHTABLE)

#define HASHTABLE

//Ячейки хеш-таблицы
struct table_cell {
	char *name;
	int height;
	int weight;
	struct table_cell *next;
};
//Хеш-таблица
struct hash_table {
	struct table_cell** cell;
	int size;
	int rehash;
};

struct hash_table* create_table ( int size_table, int rehash );
struct hash_table* write_in_table( FILE* in_file, struct hash_table* hash_table );
int check_name( char* name );
struct table_cell* table_search ( struct hash_table* hash_table, char* name);
void print_search( struct table_cell* search );
void print_table ( struct hash_table* table );
void free_table ( struct hash_table* hash_table );

#endif
