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
    IF,        // if ?
    CLASS,     // class cl
    OBJ,       // object creation Class()
} ExpressionType;

struct _Expression {
    ExpressionType type;
    uint child_count;
    struct _Expression* children;
};
typedef Expression struct _Expression;

DEFINE_WP(Expression);

typedef struct _Function {
    char* name;
    ExpressionWp body;
} Function;

/*
 * enum representing the different types of predefined classes.
 * user defined classes start from 1.
 * meaning that if they reach MAX_INT they overflow.
 * if the user defines so many classes that they collide with
 * the predefined ones, the user enters undefined behaviour
 */
typedef enum {
    INT  = -1
    FLT  = -2
    CHR  = -3
    STR  = -4
    NONE = -5
} ClassId;

/**
 * func_mask:
 * EVERY CLASS - __receive__
 * 10000000    - __init__
 * 01000000    - __die__
 */
struct _Class {
    ClassId id;
    uchar func_mask;
    FunctionWp funcs;
};

struct _Object {
    ClassId id;
    struct _Object* inbox; // until structs are supported ah fk I need structs in parsing for the inbox
    uchar capacity;
    uchar count;
    int* accepts;  // class id list
    uint sleeping;
    Closure state;
}



























