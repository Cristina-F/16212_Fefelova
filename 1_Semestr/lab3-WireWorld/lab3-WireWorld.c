#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define EMPTY ' ' // пустая клетка 
#define HEAD '0' // голова электрона 
#define TAIL '*' // хвост электрона
#define WIRE '-' // проводник
#define OFFLINE 1
#define INTERACTIVE 2
#define SUF ".rle"

struct  field_data { // Структура данных поля
	int position1;
	int position2;
	int x;
	int y;
	int size_width;
	int size_height;
}; 

int read_scanf ( int amount_generation ) { // Считываем число генераций
	int count = 0;
	int num = 0;
	while (1) {
		num = scanf( "%d", &amount_generation );
		if ( ( 1 != num ) || ( 0 >= amount_generation ) ) {
			while ( '\n' != getchar() );
		}
		else {
			while ( '\n' != getchar() ) {
				count++;
			}
			if ( 0 == count ) {
				break;
			}
		}
		printf( "Enter a positive integer number\n" );
		count = 0;
	}
	return amount_generation;
}

int read_scanf_mode ( int mode ) { // Считываем режим работы
	while (1) {
		scanf( "%d", &mode );
		if ( OFFLINE != mode && INTERACTIVE != mode ){
			while ( '\n' != getchar() );
		}
		else {
			break;
		}
		printf( "Enter a positive integer number\n" );
	}
	return mode;
}

int read_position1 ( FILE *file, char *read ) { // Считываем первое значение позиции
	int position1 = 0;
	int sign = 1;
	while ( '\n' != ( ( *read )= fgetc( file ) ) ) { 
		if ( '=' == *read ) { 
			while ( ',' != *read ) {
				*read = fgetc( file );
				if ( ',' == *read ) {
					position1 = position1*sign;
					return position1;
				}
				if ( '-' == *read ) {
					sign = -1;
					*read = fgetc( file );
				}
				position1 = position1*10 + atoi( read );
			}
		}
	}
}

int read_position2 ( FILE *file, char *read ) { // Считываем второе значение позиции
	int position2 = 0;
	int sign = 1;
	while ( '\n' != ( ( *read )= fgetc( file ) ) ) { 
		if ( ',' == *read ) {
			*read = fgetc( file );
		}
		if ( '-' == *read ) {
			sign = -1;
			*read = fgetc( file );
		}
		position2 = position2*10 + atoi( read ); 		
	}
	position2 = position2*sign;
	return position2;
}

int read_size ( FILE* file, char *read ) { // Считываем размеры используемого поля 
	int size = 0;
	while ( ',' != ( *read = fgetc( file ) ) ) { 
		if ( isdigit( *read ) ) {
			size = size * 10 + atoi( read ); 
		}
	} 
	return size;
}

int read_filed_width ( FILE *file, char *read ) { // Считываем ширину всего поля
	int size_width = 0;
	while ( '\n' != ( ( *read )= fgetc( file ) ) ) {
		if ( 'P' == *read ) {
			while ( ',' != *read ) {
				*read = fgetc( file );
				if ( ',' == *read ) {
					return size_width;
				}
				size_width = size_width*10 + atoi( read );
			}
		}
	}
}

int read_filed_height ( FILE *file, char *read ) { // Считываем высоту всего поля
	int size_height = 0;
	while ( ( ( *read ) = fgetc( file ) ) != '\n' ) {
		if ( ',' == *read ) {
			*read = fgetc( file );
		}
		size_height = size_height*10 + atoi( read );			
	}
	return size_height;
}

char* read_world ( FILE* file, char **world, char **world2, char *read ) { // Считываем первое поколение клеток
	int number = 0; 
	char cell = 0; 
	int last_number = 0;
	int count = 0;
	while ( ( ( *read ) = getc( file ) ) != '!' ) { 
		if ( '$' == *read ) {
			count++;
			last_number = 0;
		}
		if ( isdigit( *read ) ) { 
			number = number * 10 + atoi( read );
		} 
		else { 
			if ( ( '.' == *read ) || ( 'A' == *read ) || ( 'B' == *read ) || ( 'C' == *read ) ) { 
				if ( '.' == *read ) { 
					cell = EMPTY; 
				} 
				if ( 'A' == *read ) { 
					cell = HEAD; 
				} 
				if ( 'B' == *read ) { 
					cell = TAIL; 
				} 
				if ( 'C' == *read ) { 
					cell = WIRE; 
				} 
				if ( 0 == number ) { 
					number = 1; 
				} 
				for ( int i = last_number; i < ( last_number + number ); i++ ) { 
					world[count][i] = cell;
					world2[count][i] = cell;
				} 
			} 
			last_number = last_number + number; 
			number = 0; 
		} 
	} 	
	return *world;
}

int creat_file ( char *name_file ) { // Создвем файл для выходных данных
	FILE* file = fopen( name_file, "w" );
	if ( NULL == file ) {
		printf( "Can not creat %s\n", name_file );
		return -1;
	}
	fclose( file );
	return 0;
}

void write_file_line (FILE *new_file, struct field_data  data ) { // Записываем в файл параметры поля
	fprintf( new_file, "#CXRLE Pos=%d,%d\nx = %d, y = %d, rule = WireWorld:P%d,%d\n",
	 data.position1, data.position2, data.x, data.y, data.size_width, data.size_height );
}

void write_new_file ( FILE *new_file, char **world, int line, int column ) { // Записываем в файл генерацию
	int count = 1;
	for ( int i = 0; i < line; i++ ) {
		for ( int j = 0; j < column; j++ ) { 
			if ( ( world[i][j] == world[i][j + 1] ) && ( j != ( column -1 ) ) ) {
				count++;
			}
			else {
				int count_empty = 0;
				if ( EMPTY == world[i][j] ) {
					for ( int k = j; k < column; k ++ ) {
						if ( EMPTY == world[i][k] ) {
							count_empty++;
						}
					}
					if ( count_empty != column - j ) {
						if ( count > 1 ) {
							fprintf( new_file, "%d", count );
						} 
						fprintf( new_file, "." );
					}
				}
				else {
					if ( count > 1) {
						fprintf( new_file, "%d", count );
					}
					if ( HEAD == world[i][j] ) {
						fprintf( new_file, "A" );
					}
					if ( TAIL == world[i][j] ) {
						fprintf( new_file, "B" );
					}
					if ( WIRE == world[i][j] ) {
						fprintf (new_file, "C" );
					}
				}
				count = 1;
			}
		}
		if ( i == ( line - 1 ) ) {
			fprintf( new_file, "!" );
		}
		else {
			fprintf( new_file, "$" );
		}
	}	
}

char *build_new_world ( char **world, char **world2, int line, int column ) { // Создаем новое поколение
	int count = 0;
	for ( int i = 0; i < line; i++ ) {
		for ( int j = 0; j < column; j++ ) {
			if ( HEAD == world[i][j] ) {
				world2[i][j] = TAIL;
			}
			else if ( TAIL == world[i][j] ) {
				world2[i][j] = WIRE;
			}
			else if ( WIRE == world[i][j] ) {
				count = 0;
				if ( ( i - 1 >= 0 ) && ( world[i - 1][j] == HEAD ) ) {
					count++;
				}
				if ( ( i - 1 >= 0 ) && ( j - 1 >= 0 ) && ( world[i - 1][j - 1] == HEAD ) ) {
					count++;
				}
				if ( ( i - 1 >= 0 ) && ( j + 1 < column ) && ( world[i - 1][j + 1] == HEAD ) ) {
					count++;
				}
				if ( ( i + 1 < line ) && ( world[i + 1][j] == HEAD ) ) {
					count++;
				}
				if ( ( i + 1 < line ) && ( j - 1 >= 0 ) && ( world[i + 1][j - 1] == HEAD ) ) {
					count++;
				}
				if ( ( i + 1 < line ) && ( j + 1 < column ) && ( world[i + 1][j + 1] == HEAD ) ) {
					count++;
				}
				if ( ( j - 1 >= 0 ) && ( world[i][j - 1] == HEAD ) ) {
					count++;
				}
				if ( ( j + 1 < column ) && ( world[i][j + 1] == HEAD ) ) {
					count++;
				}
				if ( ( 1 == count) || ( 2 == count ) ) {
					world2[i][j] = HEAD;
				}
			}
			else {
				world2[i][j] = EMPTY;
			}
		}
	}
	return *world2;
}

void print_world ( char **world, char **world2, int line, int column ) { //Печатаем следующее поколение
	for ( int i = 0; i < line; i++ ) {
		for ( int j = 0; j < column; j++ ) {
			printf( "%c ", world2[i][j] );
			world[i][j] = world2[i][j];
		}
		printf( "\n" );
	} 
}

int offline ( char **world, char **world2, char* out_name, struct field_data data ) { // Оффлайновы	 режим
	printf( "Enter the number of generations:" );
	int amount_generation = read_scanf( amount_generation );
	for ( int i = 1; i <= amount_generation; i++ ) {
		build_new_world( world, world2, data.y, data.x );
	}
	// Если пользователь не ввел  название выходного файла, печатаем последнюю генерайию в консоль
	if  ( NULL == out_name ) {
		print_world( world, world2, data.y, data.x );
		return 0;
	}
	// Создаем выходной файл и записываем последнюю генерацию
	if ( -1 != creat_file( out_name ) ) {
		FILE *new_file = fopen( out_name, "w" );
		write_file_line( new_file, data );
		write_new_file( new_file, world, data.y, data.x ); 
		fclose( new_file );
	}
}

int interactive ( char **world, char **world2, struct field_data data ) { // Интеррактивный режим
	printf( "Please, press Enter\n" );
	char key = 0;
	while ( 1 ) {
		if ( '\n' == (key = getchar() )) {
			system( "clear" );
			print_world( world, world2,  data.y, data.x );
			build_new_world( world, world2,  data.y, data.x );			
		}
	}
}

void free_memory( char **world, char **world2, int line ) {
	for ( int i = 0; i < line; i++ ) {
		free( world[i] );
		free( world2[i] );
	}
	free( world );
	free( world2 );
}

int main ( int argc, char* argv[ ] ) {
	FILE *in_file = NULL;
	char* out_name = NULL;
	if ( 2 == argc || 3 == argc ) {
		if ( ( argv[1] + ( ( strlen(argv[1]) ) - strlen( SUF ) ) ) != strstr( argv[1], SUF ) ) {
			printf( "Error: incorrect input data.\n" );
			return -1;
		}
		in_file = fopen( argv[1], "r" );
		if ( NULL == in_file ) {
			printf( "Can not open %s.\n", argv[1] );
			return 0;
		}
		if ( 3 == argc ) {
			out_name = argv[2];
		}
	}
	else {
		printf( "Error: incorrect input data.\n" );
		return -1;
	}
	char read = 0;
	// Записываем в структуру параметры поля
	struct field_data data = { read_position1( in_file, &read ), read_position2( in_file, &read ), read_size( in_file, &read ), 
		read_size( in_file, &read ), read_filed_width( in_file, &read ), read_filed_height( in_file, &read ) };
	// Выделям память для массивов генераций
	char **world = ( char** )calloc( data.y, sizeof( char* ) );
	char **world2 = ( char** )calloc( data.y, sizeof( char* ) );
	for (int i = 0; i < data.y; i++) {
		world[i] = ( char* )calloc( data.x, sizeof( char ) );
		world2[i] = ( char* )calloc( data.x, sizeof( char ) );
	}
	read_world( in_file, world, world2, &read ); // Считываем первоначальную генерацию
	fclose ( in_file ); 
	printf ( "Please, choose a mode:\n1 - Offline\n2 - Interactive\nWrite a number 1 or 2: " );
	int mode = read_scanf_mode( mode ); // Считываем режим работы
	if ( OFFLINE == mode ) {
		offline( world, world2, out_name, data );
	}
	else {
		interactive( world, world2, data );
	}
	free_memory( world, world2, data.y ); // Освобождаем память
	return 0;
}
