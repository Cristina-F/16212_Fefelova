#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "create.h"
#include "priority_queue.h"
#include "haf.h"

static void print_tree( struct tree* root, int indent ) {
    if ( NULL == root ) {
        return;
    }
    print_tree( root -> right, indent + 1 );
    for ( int i = 0; i < indent; i++ ) {
        printf(" ");
    }
    printf("%c\n", root->type);
    print_tree(root->left, indent + 1);
}


/*static struct tree* find_min ( struct tree** node, int num_node ){
    int min_elem_val = INT_MAX;
    int index = -1;
    struct tree* min_elem = NULL;
    for ( int i = 0; i < num_node; i++ ) {
        if ( NULL != node [ i ] ) {
            if ( node [ i ] -> frequency < min_elem_val ) {
                min_elem_val = node [ i ] -> frequency;
                min_elem = node[ i ];
                index = i;
            }
        }
    }
    if ( -1 != index ) {
        node [ index ] = NULL;
    }
    return min_elem;
}

static struct tree** create_nodes ( int* table, struct tree** node) {
    int index = 0;
    for ( int i = 0; i < SIZE_TABLE; i++ ){
        if ( 0 != table[ i ] ) {
            struct tree* elem = ( struct tree* ) calloc ( 1, sizeof ( struct tree) );
            node [ index ] = elem;
            elem -> type = (char)i;
            elem -> frequency = table[ i ];
            elem -> left = NULL;
            elem -> right = NULL;
            index++;
        }
    }
    return node;
}

static struct tree* fill_node ( struct tree** min_elem ) {
    struct tree* parent = ( struct tree* ) calloc ( 1, sizeof ( struct tree) );
    parent -> type = '0';
    parent -> frequency = min_elem [ 0 ] -> frequency + min_elem [ 1 ] -> frequency;
    parent -> left = min_elem [ 0 ];
    parent -> right = min_elem [ 1 ];
    return parent;
}

static void add_node (struct tree** node, struct tree* parent, int num_node ) {
    for ( int i = 0; i < num_node; i++ ) {
        if ( NULL == node [ i ] ) {
            node [ i ] = parent;
            break;
        }
    }
}
static struct tree* create_tree ( int * table, int num_node ) {
    struct tree** node = ( struct tree** ) calloc ( num_node, sizeof ( struct tree* ) );
    create_nodes ( table, node );
    struct tree* root = NULL;
    while ( 1 ) {
        struct tree* min_elem [ 2 ];
        for ( int i = 0; i < 2; i++ ) {
            min_elem [ i ] = find_min ( node, num_node );
        }
        if ( NULL == min_elem [ 1 ] ) {
            root = min_elem[ 0 ];
            break;
        }
        struct tree* parent = fill_node ( min_elem );
        if ( NULL == parent ) {
            return NULL;
        }
        add_node ( node, parent, num_node );
    }
    return root;
}*/

struct tree** create_tree( int sum_node ) {
    struct tree** node = ( struct tree** )calloc( sum_node, sizeof( struct tree ) );
    for ( int i = 0; i < sum_node; i++ ) {
        node[i] = ( struct tree* )calloc( 1, sizeof( struct tree ) );
        node[i] -> type = '0';
    }
    return node;
}
static struct tree* create_nodes( struct tree** node, int* table, int sum_node ) {
    struct priority_queue* q = create_queue();
    int id = 0;
    for ( int i = 0; i < SIZE_TABLE; i++ ) {
        if ( 0 != table[i] ) {
            node[id] -> type = (char)i;
            node[id] -> frequency = table[i];
            node[id] -> right = NULL;
            node[id] -> left = NULL;
            add_priority_queue( q, node[id], node[id] -> frequency );
            id++;
        }
    }
    printf("sum_node = %d\n", sum_node );
    while ( id < sum_node ){
        struct tree* node1 = poll_priority_queue( q );
        struct tree* node2 = poll_priority_queue( q );
        node[id] -> right = node2;
        node[id] -> left = node1;
        node[id] -> frequency = ( node1 -> frequency ) + ( node2 -> frequency );
        node1 -> parent = node[id];
        node2 -> parent = node[id];
        add_priority_queue( q, node[id], node[id] -> frequency );
        id++;  
    }
    struct tree* root = poll_priority_queue( q );
    free( q );
    return root;
}

static void print_table( int* table ) {
    int k = 0;
    for ( int i = 0; i < SIZE_TABLE; i++ ) {
        k++;
        if ( k == 20 ) {
            printf("\n");
        }
        printf("%d %d ",i, table[i] );
    }
}


void fill_codes ( struct tree* root, char** codes, int* lenght_codes, char* tmp_code, int lenght ) {
    if ( root ) {
        if ( root -> left ) {
                tmp_code[lenght] = 0;
                fill_codes ( root -> left, codes, lenght_codes, tmp_code, ++lenght );
                tmp_code[lenght - 1] = 1;
                fill_codes ( root -> right, codes, lenght_codes, tmp_code, lenght );
        }
        else {
            memcpy ( codes [ (int)(root -> type) ], tmp_code, lenght );
            lenght_codes [ (int)(root -> type) ] = lenght;
        }
    }
}

char** create_table_codes( struct tree* root, int* lenght_codes ){
    char** codes = ( char** )calloc( SIZE_TABLE, sizeof( char* ) );
    for ( int i = 0; i < SIZE_TABLE; i++ ) {
        codes[i] = (char*)calloc( SIZE_TABLE, sizeof( char ) );
    }
    char* tmp_code = ( char* )calloc( SIZE_TABLE, sizeof( char ) );
    if ( ( NULL == root -> left ) && ( NULL == root -> right ) ) {
        codes[(int)(root -> type) ][ 0 ] = 0;
        lenght_codes[ (int)(root -> type) ] = 1;  
    } 
    else {
        fill_codes( root, codes, lenght_codes, tmp_code, 0 );

    }
    free( tmp_code );
    return codes;
}
static void print_codes ( char** codes, int* lenght_codes ) {
    for ( int i = 0; i < SIZE_TABLE; i++ ) { 
        if ( 0 < lenght_codes[i] ) {
            int k = 0;
            for ( int j = 0; j < SIZE_TABLE; j++ ) {
                if ( k < lenght_codes[i]) {
                    printf("%d ", codes[i][j]);
                    k++;
                }
            }
            printf("    %d\n", lenght_codes[i]);
        }
    }
}

static void free_table( char** table ) {
    for ( int i = 0; i < SIZE_TABLE; i++ ) {
        free( table[i] );
    }
    free( table );
}

static void write_tree ( FILE* out, struct tree* root, int* first ) {
    if ( root -> left -> left ) {
        fprintf( out, "%c", '0' );
        write_tree( out, root->left, first );
    }
    else {
        fprintf(out, "%c", ' ' );
        fprintf(out, "%c", root -> left -> type);
    }

    if ( NULL != root -> right -> left ) {
        fprintf(out, "%c", '0' );
        write_tree( out, root->right, first );
    }
    else {
        fprintf( out, "%c", ' ' );
        fprintf(out, "%c", root -> right -> type);
    }
}

static void free_tree ( struct tree* root ) {
    if ( root -> left ) {
        free_tree( root -> left );
    }
    if ( root -> right ) {
        free_tree( root -> right );
    }
    free ( root );
}

static void write_haf_to_file( FILE* in_file, FILE* out_file, struct tree* root ){
    int* lenght_codes = ( int* )calloc( SIZE_TABLE, sizeof( int ) );
    memset ( lenght_codes, -1, SIZE_TABLE * sizeof ( int ) );
    char** codes = create_table_codes( root, lenght_codes ); 
    //print_codes( codes, lenght_codes );
    int first = 1;
    if ( NULL == root -> left) {
        fprintf( out_file, "%c", ' ');
        fprintf( out_file, "%c", root -> type);
        fprintf( out_file, "%c", ' ' );
        fprintf( out_file, "%c", root -> type);
    } 
    else {
          write_tree( out_file, root, &first );
    }
    int sym = fgetc ( in_file );
    int lenght = lenght_codes [ sym ];
    int count = 0;
    int index = 0;
    unsigned char byte = 0;
    while ( !feof ( in_file ) ){
        while ( ( count <= BYTE ) && ( 0 != lenght ) ) {
            byte = ( byte | codes [sym][index++] );
            count++;
            lenght--;
            if ( BYTE == count ) {
                fprintf (  out_file, "%c", byte );
                count = 0;
                byte = 0;
                break;
            }
            else {
                byte = byte << 1;
            }
        }
        if ( 0 == lenght ) {
            sym = fgetc ( in_file );
            if ( feof ( in_file ) ) {
                count++;
                byte = byte << ( BYTE - count );
                fprintf (  out_file, "%c", byte);
                break;
            }
            lenght = lenght_codes [ sym ];
            index = 0;
        }
    }
    free_table( codes );
    free( lenght_codes );
}

static int * fill_table ( FILE * in_file ){
    int* table= ( int * ) calloc ( SIZE_TABLE, sizeof ( int ) );
    while ( 1 ){
        int sym = getc ( in_file );
        if ( EOF == sym ) {
            if ( feof ( in_file ) ){
                return table;
            }
        }
        table [ sym ]++;
    }
}

static void count_elem( int* table, int* sum_node, unsigned long long int* sum_symbol ) {
    for ( int i = 0; i < SIZE_TABLE; i++ ) {
        if ( table[i] != 0 ) {
            ( *sum_node )++;
        }
        ( *sum_symbol ) += table[i];
    }
    *sum_node = ( ( *sum_node ) * 2 ) - 1;
    printf("sum_node = %d\n", *sum_node );
}

void compression( FILE* in_file, FILE* out_file ) {
    int * table= fill_table ( in_file );
    int sum_node = 0;
    unsigned long long int sum_symbol = 0;
    count_elem(table, &sum_node, &sum_symbol);
    fprintf ( out_file, "%llu ", sum_symbol );
    printf("%llu\n", sum_symbol);
   // printf("sum_node = %d\n", sum_node );
    struct tree** node = create_tree( sum_node );
    if ( NULL == node ) {
        free( table );
        return ;
    }
    struct tree* root = create_nodes( node, table, sum_node );
   /* struct tree* root = create_tree( table, sum_node );
    if ( NULL == root ) {
        free( table );
        return ;
    }*/
    //print_tree( root, 1 );;
    fseek(in_file, 0, SEEK_SET);
    write_haf_to_file( in_file, out_file, root );
    free_tree( root );
    free( node );
    free( table);
} 

static void create_node( struct tree** node ) {
    ( *node ) =  (struct tree* )calloc( 1, sizeof( struct tree ) );
    ( *node ) -> left = NULL;
    ( *node ) -> right = NULL;
}

static void read_tree ( FILE* in_file, struct tree** root ) {
    char sym = getc( in_file );
    if ( NEXT_SYMBOL == sym  ) {
        create_node( &( *root ) -> left );
        ( *root ) -> left -> type = getc( in_file );
    } 
    else if ( DOWN == sym  ) {
        create_node( &( *root ) -> left );
        read_tree( in_file, &( *root ) -> left );
    }
    sym = getc( in_file );
    if ( NEXT_SYMBOL == sym ) {
        create_node( &( *root ) -> right );
        ( *root ) -> right -> type = getc( in_file );
    } 
    else if( DOWN == sym ) {
        create_node( &( *root ) -> right );
        read_tree( in_file, &( *root ) -> right );
    }
}

static void write_orig_to_file ( FILE * in_file, FILE * out_file, struct tree * root, unsigned long long int num_sym ) {
    struct tree* tmp = root;
    int count = 0;
    char byte =  fgetc ( in_file );
    unsigned long long int num_complete = 0;
    while ( !feof ( in_file ) ) {
        count++;
        if ( ( NULL == root -> left ) && ( NULL == root -> right ) ) {
            fputc ( tmp -> type, out_file );
            num_complete++;
        }
        else {
            int side = 0; 
            side = ( byte & 128 ) >> 7;
            byte = byte << 1;
            if ( side ){ 
                tmp = tmp -> right;
            }
            else {
                tmp = tmp -> left;
            }
            if ( ( NULL == tmp -> left ) && ( NULL == tmp -> right ) ) {
                fputc ( tmp -> type, out_file );
                tmp = root;
               num_complete++;
            }
        }
        if ( num_complete == num_sym ){
            break;
        } 
        if ( BYTE == count ) {
            byte = fgetc ( in_file );
            count = 0;
        }
    }
}

void decompression( FILE * in_file, FILE * out_file ) {
    unsigned long long int num_sym = 0;
    fscanf ( in_file, "%llu", &num_sym );
    fgetc( in_file );
    struct tree* root = NULL;
    create_node( &root );
    read_tree( in_file, &root );
    //print_tree( root, 1 );
    write_orig_to_file( in_file, out_file, root, num_sym ) ;
    free_tree( root );
}
