/**
 * Lexer for language
 */

#include <stdio.h>
#include "rstd/color_print.h"
#include "rstd/dynamic_array.h"

typedef enum {
    ADD, // addition +
    SUB, // subraction -
    MUL, // multiplication *
    DIV, // division /
    CONST_INT, // constant integer
    CONST_FLT, // constant float
    CONST_CHR, // constant character
    CONST_STR, // constant string
    LBRACK, // left bracket {
    RBRACK, // right bracket }
    LPAR, // left parentheses (
    RPAR, // right parentheses )
    LBRACE, // left brace [
    RBRACE, // right brace ]
    END, // statement end \n
    ERROR, // Encountered an error while lexing
} LexType;

typedef struct { 
    size_t count; 
    char* ptr; 
} LString; 

typedef struct {
    LexType type;
    union {
        long intv;
        double floatv;
        unsigned char charv;
        LString strv;
    } value;
} LexToken;

DEFINE_WP(LexToken);

LexTokenWp lex_file(FILE* fp);
void print_lex_wp(LexTokenWp wp); // debug function
