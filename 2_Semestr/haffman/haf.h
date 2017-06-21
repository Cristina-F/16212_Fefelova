#ifndef HAF
#define HAF

#define SIZE_TABLE 256
#define BYTE 8
#define DOWN '0'
#define NEXT_SYMBOL ' '

struct tree {
    unsigned char type;
    long long int frequency;
    struct tree* parent;
    struct tree* left;
    struct tree* right;
};

void decompression ( FILE * in_file, FILE * out_file );
void compression ( FILE* in_file, FILE* out_file );

#endif