#if !defined(ALGO)
#define ALGO

#include "ht.h"

void algo( struct hash_table* hash_table, struct table_cell* start, struct table_cell* finish, int vertex );
struct table_cell* get_vertex( struct hash_table* hash_table );

#endif
