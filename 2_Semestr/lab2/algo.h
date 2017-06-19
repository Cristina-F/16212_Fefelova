#if !defined(ALGO)
#define ALGO

#include "bin_heap.h"
#include "ht.h"

void dijkstra_algorithm( struct hash_table* hash_table, struct table_cell* start, struct table_cell* finish );
int read_vertex( );
struct table_cell* get_vertex( struct hash_table* hash_table );

#endif
