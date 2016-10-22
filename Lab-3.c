#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define EMPTY 0 // пустая клетка 
#define HEAD 1 // голова электрона 
#define TAIL 2 // хвост электрона
#define WIRE 3 // проводник

int read_x(FILE* file, char *read) { //Считываем значение x - ширина поля
	int x = 0;
	while (((*read )= fgetc(file)) != 'y') { 
		if ('#' == *read) { 
			while ('\n' != *read) { 
				*read = fgetc (file); 
			} 
		} 
		if ('x' == *read) { 
			x = 0; 
			for (int i = 0; i < 3; i++) { 
				*read = fgetc (file); 
			} 
			while ((*read = fgetc(file)) != ',') { 
				x = x * 10 + (*read - '0'); 
			} 
		}	
	}
return x;
}
int read_y(FILE* file, char *read) { //Считываем значение y - длина поля
	int y = 0;
	while (((*read) = fgetc(file)) != '\n') { 
		if (' ' == *read) {
			y = 0;
			for (int i = 0; i < 2; i++) { 
				*read = fgetc (file); 
			} 
			while (((*read) = fgetc(file)) != ',') { 
				y = y * 10 + (*read - '0'); 
			} 	 
			if (',' == *read) { 
			break;
			}
		} 
	}
	return y;
}
int* build(FILE* file, int **world, char *read) { //Считываем первое поколение клеток
	int number = 0; 
	int cell = 0; 
	int last_number = 0;
	int i = 0;
	int count = 0;
	while (((*read) = getc(file)) != '!') { 
		if ('r' == *read){
			while ('\n' != *read) { 
				*read = fgetc (file); 
			}
		}
		if ('$' == *read) {
			count++;
			last_number = 0;
		}
		if (('0' <= *read) && ('9' >= *read)) { 
			number = number * 10 + (*read - '0');
		} 
		else { 
			if (('.' == *read) || ('A' == *read) || ('B' == *read) || ('C' == *read)) { 
				if ('.' == *read) { 
					cell = EMPTY; 
				} 
				if ('A' == *read) { 
					cell = HEAD; 
				} 
				if ('B' == *read) { 
					cell = TAIL; 
				} 
				if ('C' == *read) { 
					cell = WIRE; 
				} 
				if (0 == number) { 
				number = 1; 
				} 
				for (i = last_number; i < (last_number + number); i++) { 
					world[count][i] = cell; 
				} 
			} 
			last_number = last_number + number; 
			number = 0; 
		} 
	} 	
	return (*world);
}
int *build_new_world (int **world, int **world2, int line, int column) { // Создаем новое поколение
	int count = 0;
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			if (HEAD == world[i][j]) {
				world2[i][j] = TAIL;
			}
			else if (TAIL == world[i][j]) {
				world2[i][j] = WIRE;
			}
			else if (WIRE == world[i][j]) {
				count = 0;
				if ((i - 1 >= 0) && (world[i - 1][j] == HEAD)) {
					count++;
				}
				if ((i - 1 >= 0) && (j - 1 >= 0) && (world[i - 1][j - 1] == HEAD)) {
					count++;
				}
				if ((i - 1 >= 0) && (j + 1 < column) && (world[i - 1][j + 1] == HEAD)) {
					count++;
				}
				if ((i + 1 < line) && (world[i + 1][j] == HEAD)) {
					count++;
				}
				if ((i + 1 < line) && (j - 1 >= 0) && (world[i + 1][j - 1] == HEAD)) {
					count++;
				}
				if ((i + 1 < line) && (j + 1 < column) && (world[i + 1][j + 1] == HEAD)) {
					count++;
				}
				if ((j - 1 >= 0) && (world[i][j - 1] == HEAD)) {
					count++;
				}
				if ((j + 1 < column) && (world[i][j + 1] == HEAD)) {
					count++;
				}
				if ((1 == count) || (2 == count)) {
					world2[i][j] = 1;
				}
			}
			else {
				world2[i][j] = EMPTY;
			}
		}
	}
	return *world2;
}
void print_world (int **world, int line, int column) {// Печатаем первое поколение
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			printf("%d ", world[i][j] );
		}
		printf("\n");
	}
}
void print_new_world (int **world, int **world2, int line, int column) { //Печатаем следующее поколение
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			printf("%d ", world2[i][j] );
			world[i][j] = world2[i][j];
		}
		printf("\n");
	}
}
int main () {
	FILE *file = fopen("input.rle","r"); //Открываем файл для чтения
	char read = 0;
	srand(time(NULL));
	int column = read_x(file, &read);
	int line = read_y(file, &read);;
	int **world = (int**)calloc(line, sizeof(int*));
	int **world2 = (int**)calloc(line, sizeof(int*));
	for (int i = 0; i < line; i++) {
		world[i] = (int*)calloc(column, sizeof(int));
		world2[i] = (int*)calloc(column, sizeof(int));
	}
	build(file, world, &read);
	fclose (file); 
	print_world(world, line, column);
	while (1) {
		build_new_world(world, world2, line, column);
		printf("\n");
		print_new_world(world, world2, line, column);
		sleep(1);
	}
	free(world);
	free(world2);
	return 0;
}
