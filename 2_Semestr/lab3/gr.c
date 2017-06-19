#include "gr.h"
#include "ht.h"

#include <stdio.h>
#include <stdlib.h>

//добавление соседий
void add_siblings( struct hash_table* hash_table, int actual_name, int sibl, int weight ) {
	struct list_sibl* new_elem = ( struct list_sibl* )calloc( 1, sizeof( struct list_sibl ) );
	struct table_cell* elem1 = table_search( hash_table, actual_name );
	struct table_cell* elem2 = table_search( hash_table, sibl );
	new_elem -> t_cell = elem2; 
	new_elem -> weight = weight;
	(new_elem -> t_cell -> num_siblings)++;
	struct list_sibl* buff = elem1 -> siblings;
	elem1 -> siblings = new_elem;
	elem1 -> siblings -> next = buff;
}

//Добавляем вершины графа
struct hash_table* add_node ( struct hash_table* hash_table, FILE* in_file, int* vertex  ) {
	int id1 = 0;
	int id2= 0;
	int weight = 0;
	int ok = 0;
	while( ok != EOF ) {
		ok = fscanf( in_file, "%d%d%d", &id1, &id2, &weight );
		if ( 3 == ok ) {
			if ( !check_id( hash_table, id1) ) {
				hash_table = write_in_table( hash_table, id1, ++( *vertex ) );
			}
			if ( !check_id( hash_table, id2) ) {
				hash_table = write_in_table( hash_table, id2, ++( *vertex ) );
			}
			add_siblings(hash_table, id1, id2, weight );
		}
	}
	return hash_table; 
}
