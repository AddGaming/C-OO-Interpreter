#include <stdio.h>
#include "color_print.h"
#include "dynamic_array.h"

typedef enum {
    ADD, // addition +
    SUB, // subraction -
    MUL, // multiplication *
    DIV, // division /
    CONST_INT, // constant integer
    CONST_FLT, // constant float
    CONST_CHAR, // constant character
    CONST_STR, // constant string
    LBRACK, // left bracket {
    RBRACK, // right bracket }
    LPAR, // left parentheses (
    RPAR, // right parentheses )
    LBRACE, // left brace [
    RBRACE, // right brace ]
} LexToken;



int main(int argc, char* argv[]) {
    if (!argc || argc <= 1) {
        print_redln("REPL mode not implemented");
        return 1;
    }
    else if (argc == 2) {
        char* file_name = argv[1];
        FILE* file = fopen(file_name, "r");
        if (file == NULL) {
            print_redln("File \"%s\" not found", file_name);
            return 1;
        }
        print_greenln("worked");
        intWp my_wp = {0, 0, 0, NULL};
        // fscanf_s(file, "%49s %d %f", name, sizeof(name), &age, &salary)
        
        int fclose(FILE *fp);
    }
    return 0;
}
