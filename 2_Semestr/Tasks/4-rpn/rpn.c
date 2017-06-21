#include "create.h"
#include "stack.h"
#include "rpn.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100

void free_list1( struct list* head ) {
	while( head ) {
		struct list* tmp = head;
		if (tmp-> data && BRACKET == tmp -> data -> type ) {
			free( tmp -> data);
		}
		head = head -> next;
		free( tmp );
	}
	free( head );
} 
void free_list( struct list* head ) {
	while( head ) {
		struct list* tmp = head;
		head = head -> next;
			free( tmp -> data );


				free( tmp );
	}
	free( head );
} 

char* read_string( char* string ) {
	string = create_string( SIZE );
	char symbol = 0;
	for ( int i = 0; '\n' !=( symbol = getchar( ) ); i++ ) {
		string[i] = symbol;
	}
	return string;
}

int parse( char* string, struct list* head ) {
	int ok = -1;
	struct list* new = head;
	struct list* tail = NULL;
	int number = 0;
	for ( int i = 0; '\0' != string[i]; i++ ) {
		struct Lexem* lexem = ( struct Lexem* )calloc( 1, sizeof( struct Lexem) );
		if ( isspace( string[i] ) ) {
			continue;
		}
		else if ( ( '+' == string[i] ) || ('-' == string[i]) || ( '/' == string[i] ) || ( '*' == string[i] ) ){
			if ( NULL != tail && OP == tail ->  data -> type  ){
				printf("Ошибка: два знака операции \n");
				free(lexem);
				return -1;
			}
			else if (NULL != tail && BRACKET == tail ->  data -> type ) {
				if ( BR_OPEN == tail ->  data -> value.num) {
					printf("Ошибка: знак после открывающейся скобки\n");
					free(lexem);
					return -1;
				}
			}
			if ( tail ==  NULL ) {
				printf("Ошибка: начало со знака\n");
				free(lexem);
				return -1;
			}
			lexem -> type = OP;

			if ( '+' == string[i] ){
				lexem -> value.op = PLUS;
			}
			else if ( '-' == string[i] ) {
				lexem -> value.op = MINUS;
			}
			else if ( '*' == string[i] ) {
				lexem -> value.op = MUL;
			}
			else {
				lexem -> value.op = DIV;
			}
		}
		else if ( '(' == string[i] ) {
			if( NULL != tail &&BRACKET == tail ->  data -> type ) {
				if (BR_CLOSE == tail ->  data -> value.num ) {
					printf("ошибка : )(\n");
					free(lexem);
					return -1;
				}
			}
			lexem -> type = BRACKET;
			lexem -> value.br = BR_OPEN;
		}
		else if ( ')' == string[i] ) {
			if( NULL != tail &&BRACKET == tail ->  data -> type ) {
				if (BR_OPEN == tail ->  data -> value.num ) {
					printf("ошибка : ()\n");
					free(lexem);
					return -1;
				}
			}
			else if (NULL != tail && OP == tail ->  data -> type) {
				printf("Ошибка:знак перед закрывающейся скобкой\n");
				free(lexem);
				return -1;
			}
			lexem -> type = BRACKET;
			lexem -> value.br =BR_CLOSE;
		}
		else {
			if( NULL != tail && BRACKET == tail -> data -> type ) {
				if ( BR_CLOSE == tail -> data -> value.num ) {
					printf("число после закрывающейся скобки\n");
					free(lexem);
					return -1;
				}
			}
			number = 10 * number + ( string[i] - '0' );
			ok = 0;
			if ( '\0' == string[i + 1] || ( '\0' !=  string[i + 1] && 0 == isdigit( string[i + 1] ) ) ) {
				if ( NULL != tail && 0 == number && OP == tail -> data -> type ) {
					if ( DIV == tail -> data -> value.num ) {
						free(lexem);
						printf("Ошибка: /0\n");
						return -1;
					}
				}
				ok = 1;
				lexem -> type = NUMBER;
				lexem -> value.num = number;
				number = 0;
			}
		}
		if ( 0 != ok ) {
			new -> data = lexem;
			tail = new;
			new -> next = ( struct list* ) calloc( 1, sizeof( struct list ) );
			new = new -> next;
		}
	}
	if( OP == tail -> data -> type ) {
	
		return -1;
	}
	new = NULL;
	return 0;
}

void print_list ( struct list* head ) {
	while( head -> next ) {
		if ( OP == head -> data ->  type ) {
			if ( PLUS ==  head -> data -> value.op ) {
				printf("+ ");
			}
			else if ( MINUS == head -> data -> value.op ) {
				printf("- ");
			}
			else if ( MUL == head -> data -> value.op ) {
				printf("* ");
			}
			else if (DIV == head -> data -> value.op ) {
				printf("/ ");
			}
		}
		else {
			printf("%d ", head -> data -> value.num );
		}
		if ( ! ( head -> next ) ) {
			break;
		}
		head = head -> next;
	}
}

static int compute_priority( struct Lexem* current ) {
	int priority = 0;
	 if ( BRACKET == current -> type ) {
	 	if ( BR_CLOSE == current -> value.br ) {
	 		priority = 3;
	 	}
	}
	else if ( ( PLUS == current -> value.op ) || ( MINUS == current-> value.op ) ) {
		priority = 1;
	}
	else if  ( ( MUL == current-> value.op ) || ( DIV == current -> value.op ) ) {
		priority = 2;
	}
	return priority;
}

static struct list* add_polish( struct list* new_cell, struct Lexem* new_elem ) {
	new_cell -> data = new_elem;
	new_cell -> next = ( struct list* )calloc( 1, sizeof( struct list ) );
	new_cell = new_cell -> next;
	return new_cell; 
}

static int compare_priority( struct Lexem* actual_lexem, struct Lexem* early_lexem ) {
	int actual_priority = compute_priority( actual_lexem);
	int early_proirity = compute_priority( early_lexem );
	if ( actual_priority <= early_proirity ) {
		return 1;
	}
	else {
		return 0; 
	}
}

static struct list* out_of_stack( struct stack* stack, struct list* polish_note ) {
	while ( ( NULL != stack -> peak ) && (  BRACKET != stack -> peak -> elem -> type  ) ) {
		polish_note = add_polish( polish_note, pop( stack ) );
	}
	if ( !( stack -> peak ) ) {
		return NULL;
	}
	pop( stack );
	return polish_note;
}

struct list* reverse_polish_notation( struct list* head ) {
	struct stack* stack = create_stack( );
	struct list* polish_note = ( struct list* ) calloc( 1, sizeof( struct list ) );
	struct list* head_polish = polish_note;
	struct list* actual = head;
	while( actual -> next ) {
		if( NUMBER == actual -> data -> type ) {
			polish_note = add_polish( polish_note, actual -> data );
		} 
		else if( OP == actual -> data -> type  )  {
			if ( ! (stack -> peak ) ) {
				push( stack, actual -> data );
			}
			else{
				while( compare_priority( actual -> data,  stack -> peak -> elem )  ) {
					if ( ! stack -> peak ) {
						break;
					}
					polish_note = add_polish( polish_note, pop( stack ) );
					if ( !( stack -> peak ) ){
						break;
					}
				}
				push( stack, actual -> data );
			}
		}
		else if( BRACKET == actual -> data -> type ) {
			if ( BR_OPEN == actual -> data -> value.br ) {
				push( stack, actual -> data );
			}
			else{
				polish_note = out_of_stack( stack, polish_note );
				if ( !polish_note ) {
					return NULL;
				}
			}

		}
		actual = actual -> next;
	} 
	while ( stack -> peak ) {
		if ( BRACKET == (stack -> peak -> elem -> type ) ){
			return NULL;
		}
		polish_note = add_polish( polish_note, pop( stack ) );
	}
	polish_note -> next = NULL;
	free( stack);
	free_list1(head);
	return head_polish;
}

int calculate( struct list* head) {
	struct stack* stack = create_stack( );
	struct list* actual = head;
	int result = 0;
	int ok = 0;
	struct Lexem* result_n = ( struct Lexem* )calloc( 1, sizeof( struct Lexem ) );
	while ( actual -> next ) {
		if ( NUMBER == actual -> data -> type ) {
			push( stack, actual -> data );
		}
		else if ( OP == actual -> data -> type ) {	
			ok = 1;
			int  number0 = pop( stack) -> value.num;
			int number1 = pop( stack) -> value.num;
			if ( MUL == actual -> data -> value.op ) {
				result = number0 * number1;
			}
			else if ( PLUS == actual -> data -> value.op ) {
				result = number0 + number1;
			}
			else if ( MINUS == actual -> data -> value.op ) {

				result = number1 - number0;
			}
			else if ( DIV == actual -> data -> value.op ) {
				result = number1 / number0;
			}
			//printf("%d \n", result);
			result_n -> value.num = result;
			result_n -> type = NUMBER;
			push( stack, result_n );
		}
		actual = actual -> next;
	}
	if ( 0 == ok ) {
		result = pop( stack ) -> value.num;
	}
	pop( stack );
	free( result_n);
	free( stack );
	return result;
}

