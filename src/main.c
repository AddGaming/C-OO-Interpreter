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
} LexType;

typedef struct {
    LexType type;
    union {
        long intv;
        double floatv;
        unsigned char charv;
        char* strv;
    } value;
} LexToken;

DEFINE_WP(LexToken);
DEFINE_INSERT(LexToken);

void skip_whitespace(FILE* fp) {
    int c = fgetc(fp);
    int space = (int) ' ';
    int tab = (int) '\t';
    while (c != EOF && (c == space || c == tab)) {
        c = fgetc(fp);
    }
}
void until_whitespace(FILE* fp) {
    int c = fgetc(fp);
    int space = (int) ' ';
    int tab = (int) '\t';
    while (c != EOF && c != space && c != tab) {
        c = fgetc(fp);
    }
}

LexTokenWp lex_file(FILE* fp) {
    new_wp(ans, LexToken, 8);
    char token_buff[2] = {'\0'};

    while (1) {
        skip_whitespace(fp);
        if (feof(fp)) {
            return ans;
        } 
        else {
            fpos_t pos;
            fgetpos(fp, &pos);
            fgets(token_buff, sizeof(token_buff), fp);
            fsetpos(fp, &pos);
            fgetc(fp); // skipping one ahead to guarantee progress

            if (token_buff[0] == '*') {
                LexToken tk = {MUL, {0}}; 
                ans = insert_LexToken(ans, tk).result;
            }
        }
    }

    // unreachable
    return ans;
}

void print_lex_wp(LexTokenWp wp) {
    for (size_t i = 0; i < wp.count; i++) {
        switch (wp.ptr[i].type) {
            case ADD: {
                print_yellow("ADD");
                break;
            }
            case SUB: {
                print_yellow("SUB");
                break;
            }
            case MUL: {
                print_yellow("MUL");
                break;
            }
            case DIV: {
                print_yellow("DIV");
                break;
            }
        }
        print_yellow(", ");
    }
    print_yellowln(" ");
}


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
        print_greenln("reading in file \"%s\"", file_name);

        LexTokenWp lexed_file = lex_file(file);

        print_lex_wp(lexed_file);
        
        int fclose(FILE *fp);
    }
    return 0;
}






















