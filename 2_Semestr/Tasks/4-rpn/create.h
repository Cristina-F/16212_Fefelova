#if !defined(CREATE)
#define CREATE

#define CREATE
#define create_two_array( x ) ( int** )calloc( x, sizeof( int* ) );
#define create_array( x ) ( int* )calloc( x, sizeof ( int ) );
#define create_string( x ) ( char* )calloc( x , sizeof ( char ) );

#endif