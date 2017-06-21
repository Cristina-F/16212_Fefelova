#if !defined(GRAPH)
#define GRAPH

#include <stdio.h>

struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file );
void add_siblings( struct hash_table* hash_table, char* actual_name, char* sibl );
int bfs( struct hash_table* hash_table );

#endif