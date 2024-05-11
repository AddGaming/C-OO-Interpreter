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

    // TODO: put this in a loop and try it out
    skip_whitespace(fp);
    if (feof(fp)) {
        return ans;
    } 
    else {
        fpos_t pos;
        fgetpos(fp, &pos);
        fgets(token_buff, sizeof(token_buff), fp);
        fsetpos(fp, &pos);
        fgetc(fp);

        if (token_buff[0] == '*') {
            LexToken tk = {MUL, {0}}; 
            ans = insert_LexToken(ans, tk).result;
        }

    }

    return ans;
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
        print_greenln("worked");
        intWp my_wp = {0, 0, 0, NULL};
        // fscanf_s(file, "%49s %d %f", name, sizeof(name), &age, &salary)
        
        int fclose(FILE *fp);
    }
    return 0;
}
