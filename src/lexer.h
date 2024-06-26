/**
 * Lexer for language
 */

#include <stdio.h>
#include "rstd/rstd.h"

typedef enum {
    ADD,       // addition +
    SUB,       // subraction -
    MUL,       // multiplication *
    DIV,       // division /
    POW,       // power **
    ASS,       // assign =
    EQ,        // equality ==
    IS,        // class equality is
    NEQ,       // equality !=
    GT,        // greater than >
    LT,        // less than <
    GE,        // greater equal >=
    LE,        // less equal <=
    CONST_INT, // constant integer
    CONST_FLT, // constant float
    CONST_CHR, // constant character
    CONST_STR, // constant string
    VAR,       // variable
    FN,        // function fn
    CL,        // class lc
    COLON,     // colon :
    COMMA,     // comma ,
    IF,        // if ?
    CLASS,     // class name
    LBRACK,    // left bracket {
    RBRACK,    // right bracket }
    LPAR,      // left parentheses (
    RPAR,      // right parentheses )
    LBRACE,    // left brace [
    RBRACE,    // right brace ]
    END,       // statement end \n
    ERROR,     // Encountered an error while lexing
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
unsigned int test_LexType(const LexToken real, const LexToken expected, const char* message); // debug function
