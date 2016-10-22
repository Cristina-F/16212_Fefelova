#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT -1
#define RIGHT 1

int error (int n) {
	int count = 0;
	int num = 0;
	while (1) {
		num = scanf("%d", &n);
		if ((1 != num) || (n < 0)) {
			while (getchar() != '\n'){	
			}
		}
		else {
			while (getchar() != '\n'){
				count++;
			}
			if (0 == count) {
				break;
			}
		}
		printf("Enter the number\n");
		count = 0;
	}
	return n;
}
int factorial(int n) { //Считаем число перестановок
	if (1 == n) {
		return 1;
	}
	return n*factorial(n - 1);
}
int search_mobile(int *set, int *change, int n) { //Поиск наиболее подвижного элемента
	int mobile = -1;
	int step = 0;
	for (int i = 0; i < n; i++){
		if (LEFT == change[i]) {
			step = LEFT;
		}
		else {
			step = RIGHT;
		}
		if (((i + step) < 0) || ((i + step) > (n - 1))) {
			continue;
		}
		if ((set[i + step] < set[i]) && ((-1 == mobile) || (set[i] > set[mobile]))) {
			mobile = i;
		}
	}
	return mobile;
}
int transform_change (int *set, int *change, int n, int mobile) { //Меняем направление стрелок в зависимости от наиболее подвижного элемента
	for (int i = 0; i < n; i++) {
		if (set[i] > set[mobile]) {
			if (LEFT == change[i]) {
				change[i] = RIGHT;
			}
			else {
				change[i] = LEFT;
			}
		}
	}
	return *change;
}
void swap (int *set, int *change, int mobile) {// Выполняем перестановоку
	int bufS = set[mobile];
	int bufCh = change[mobile];
	if (LEFT == change[mobile]) {
		set[mobile] = set[mobile - 1];
		set[mobile - 1] = bufS;
		change[mobile] = change[mobile - 1];
		change[mobile - 1] = bufCh;
	}
	else {
		set[mobile] = set[mobile + 1];
		set[mobile + 1] = bufS;
		change[mobile] = change[mobile + 1];
		change[mobile + 1] = bufCh;
	}
}
void print_permutation (int **permutation, int n, int comb){ //Печатаем все перестановки
	for (int i = 0; i < comb; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", permutation[i][j]);
		}
		printf("\n");
	}
}
int main (int argc, char *argv[]) {
	int n = 0;
	int size = 0;
	if (2 == argc) {
		n = atoi(argv[1]);
		for (size = 0; n > 0; size++) {
			n = n / 10;
		}
		if (size == strlen(argv[1])) {
			n = atoi(argv[1]);
		}
		else {
			printf("Enter the number\n");
			n = error(n);
		}
	}
	else {
		printf("Enter the number\n");
		n = error(n);
	}
	int comb = factorial(n);
	int *set = (int*)calloc(n, sizeof(int));
	int *change = (int*)calloc(n, sizeof(int));
	int **permutation = (int**)calloc(comb, sizeof(int*));
	int count = 0;
	int mobile = 0;
	for (int i = 0; i < comb; i++) {
		permutation[i] = (int*)calloc(n, sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		set[i] = i + 1;
		change[i] = LEFT;
	}
	while (count < comb) {
		for (int i = 0; i < n; i++) { //Записываем текущюю перестановоку
			permutation[count][i] = set[i];
		}
		mobile = search_mobile(set, change, n);
		if (-1 == mobile) { // Если подвижный элемент не найден выходим из цикла
			break;
		}
		transform_change(set, change, n, mobile);
		swap(set, change, mobile);
		mobile = -1;
		count++;
	}
	print_permutation(permutation, n, comb);
	free(set);
	free(change);
	free(permutation);
	return 0;
}
