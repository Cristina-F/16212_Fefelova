#include <stdio.h>
#include <stdlib.h>

#define POSITIVE 1
#define NEGATIVE -1
#define EMPTY 0

#define TRUE 1
#define FALSE -1

/*#define NUM_VAR 1
#define N 2*/

#define NUM_VAR 10
#define N 8 

void print_var( int vars[NUM_VAR] ) {
	for(int i = 0; i < NUM_VAR; i++) {
		printf("%d ", vars[i]);
	}
	printf("\n");
}

void print_formula ( int formula[N][NUM_VAR] ) {
	for ( int i = 0; i < N; i++ ) {
		int dis = 0;
		printf("( " );
		for ( int j = 0; j < NUM_VAR; j++ ) {
			if ( EMPTY != formula[i][j] ) {
				if ( dis != 0) {
					printf(" + ");
				}
				if ( NEGATIVE == formula[i][j] ) {
					printf("!");
				}
				printf("X%d", j );
				dis++;
			}
		}
		printf(" )");
		if ( i != N - 1 ) {
			printf(" & ");
		}
	}
	printf("\n");
} 
int check_disjunct( int vars[NUM_VAR] , int formula[NUM_VAR] ) {
	int count = 0;
	int value_disjunct  = 0;
	for ( int i = 0; i < NUM_VAR; i++ ) {
		if (  EMPTY != vars[i]) {
			if ( POSITIVE == formula[i] ) {
				if ( TRUE == vars[i]) {
					value_disjunct++;
				}
			}
			else {
				if ( FALSE == vars[i] ) {
					value_disjunct++;
				}
			}
			count++;
		}
	}
	if ( 0 == value_disjunct ){
		if ( 0 == count ) {
			return EMPTY;
		}
		else {
			return FALSE;
		}
	} 
	return TRUE;
}

int check_formula( int formula[N][NUM_VAR], int vars[NUM_VAR] ) {
	for ( int i = 0; i < N; i++ ) {
		int check = check_disjunct( vars, formula[i]);
		if ( FALSE == check ) {
			return FALSE;
		}
		else if ( EMPTY == check ) {
			return EMPTY; 
		}
	}
	return TRUE;
}

int unit_propagation ( int formula[N][NUM_VAR], int vars[NUM_VAR] ) {
	for ( int i = 0; i < N; i++ ) {
		int index_var = -1; 
		for ( int j = 0; j < NUM_VAR; j++ ) {
			if( EMPTY != formula[j][i] ) {
				if ( -1 == index_var ) {
					index_var = j;
				}
				else {
					index_var = -1;
					break;
				}
			}
		}
		if( -1 != index_var ) {
			if ( NEGATIVE == formula[i][index_var] ) {
				vars[index_var] = FALSE;
			}
			else {
				vars[index_var] = TRUE;
			}
		}
	}
	return check_formula( formula, vars );
}

void pure_literal_elimination( int formula[N][NUM_VAR], int vars[NUM_VAR]){
	for ( int i = 0; i < NUM_VAR; i++ ) {
		if ( EMPTY == vars[i] ) {
			int num_pos = 0;
			int num_neg = 0;
			for( int j = 0; j < N; j++ ) {
				if ( EMPTY != formula[j][i] ) {
					if ( POSITIVE == formula[j][i] ) {
						if ( num_neg ) {
							break;
						}
						num_pos++;
					}
					else {
						if( num_pos ) {
							break;
						}
						num_neg++;
					}
				}
			}
			if( ( !num_pos ) && ( num_neg ) ) {
				vars[i] = FALSE;
			}
			else if ( ( !num_neg ) && ( num_pos ) ) {
				vars[i] = TRUE;
			}
		}	
	}
}

int choose_empty_var(int variables[NUM_VAR]){
	int id_var = -1;
	for (int i = 0; i < NUM_VAR; i++) {
		if ( EMPTY == variables[i] ) {
			id_var = i;
			break;
		}
	}
	return id_var;
}

int dpll ( int vars[NUM_VAR], int formula[N][NUM_VAR] ) {
	int check = check_formula( formula, vars );
	if ( TRUE == check ) {
		return 1;
	}
	else if ( FALSE == check ) {
		return 0;
	}
	check = unit_propagation( formula, vars );
	pure_literal_elimination( formula, vars );
	if ( TRUE == check ) {
		return 1;
	}
	else if ( FALSE == check ) {
		return 0;
	}
	int var = choose_empty_var(vars);
	if ( var == -1 ) {
		return 1;
	}
	vars[var] = TRUE;
	if( dpll( vars, formula ) ) {
		return 1;
	}
	vars[var] = FALSE;
	if( dpll( vars, formula ) ) {
		return 1;
	}
	return 0;
}
int main( ) {
	int vars[NUM_VAR] = {0};
	int formula[N][NUM_VAR] = {0};
	
	formula[0][0] = POSITIVE;
	formula[0][1] = POSITIVE;

	formula[1][0] = NEGATIVE;
	formula[1][2] = POSITIVE;
	formula[1][3] = NEGATIVE;

	formula[2][1] = NEGATIVE;
	formula[2][2] = POSITIVE;
	formula[2][4] = POSITIVE;

	formula[3][3] = POSITIVE;
	formula[3][7] = POSITIVE;
	formula[3][8] = NEGATIVE;

	formula[4][4] = NEGATIVE;
	formula[4][7] = POSITIVE;
	formula[4][8] = POSITIVE;

	formula[5][5] = NEGATIVE;
	formula[5][4] = NEGATIVE;
	formula[5][6] = POSITIVE;

	formula[6][0] = NEGATIVE;
	formula[6][7] = NEGATIVE;
	formula[6][9] = POSITIVE;

	formula[7][3] = POSITIVE;
	formula[7][7] = NEGATIVE;
	formula[7][9] = NEGATIVE;

	/*formula[0][0] = POSITIVE;
	formula[1][0] = NEGATIVE;*/
	print_formula( formula );
	if ( !dpll( vars, formula ) ) {
		printf("НЕВОЗМОЖНО ПОДОБРАТЬ ОЗНАЧИВАНИЕ\n");
	}
	else {
		print_var( vars );
	}
}