#if !defined(RPN)
#define RPN

enum LexType {
	NUMBER,
	OP,
	BRACKET
};

enum Operation {
	PLUS,
	MINUS,
	MUL,
	DIV
};

enum Bracket {
	BR_OPEN,
	BR_CLOSE
};

union Value {
	int num;
	enum Operation op;
	enum Bracket br;
};

struct Lexem {
	enum LexType type;
	union Value value;
};

struct list {
	struct Lexem* data;
	struct list* next;
};

int parse( char* string, struct list* head );
struct list* reverse_polish_notation( struct list* actual );
int calculate( struct list* head);
void print_list ( struct list* head );
char* read_string( char* string );
void free_list( struct list* head );

#endif