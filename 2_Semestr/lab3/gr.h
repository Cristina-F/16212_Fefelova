#if !defined(GRAPH)
#define GRAPH

#include <stdio.h>

struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file, int* vertex  ) ;
void add_siblings( struct hash_table* hash_table, int actual_name, int sibl, int weight ) ;


#endif
