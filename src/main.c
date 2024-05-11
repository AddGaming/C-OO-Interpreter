#include "color_print.h"
#include "dynamic_array.h"

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
    fpos_t pos;
    fgetpos(fp, &pos);

    int c = fgetc(fp);
    int space = (int) ' ';
    int tab = (int) '\t';
    int carrige = (int) '\r';
    while (c != EOF && (c == carrige || c == space || c == tab)) {
        fgetpos(fp, &pos);
        c = fgetc(fp);
    }
    if (c != EOF) fsetpos(fp, &pos);
}
void until_whitespace(FILE* fp) {
    fpos_t pos;
    fgetpos(fp, &pos);

    int c = fgetc(fp);
    int space = (int) ' ';
    int tab = (int) '\t';
    int carrige = (int) '\r';
    while (c != EOF && c != carrige && c != space && c != tab) {
        fgetpos(fp, &pos);
        c = fgetc(fp);
    }
    fsetpos(fp, &pos);
}

LexTokenWp lex_file(FILE* fp) {
    new_wp(ans, LexToken, 8);
    char token_buff[3] = {'\0'};

    while (1) {
        skip_whitespace(fp);
        if (feof(fp)) {
            return ans;
        } 
        else {
            fpos_t pos;
            fgetpos(fp, &pos);
            fgets(token_buff, 3, fp);
            fsetpos(fp, &pos);

            if (token_buff[0] == '+') {
                LexToken tk = {ADD, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '-') {
                LexToken tk = {SUB, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '*') {
                LexToken tk = {MUL, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '/') {
                LexToken tk = {DIV, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '{') {
                LexToken tk = {LBRACK, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '}') {
                LexToken tk = {RBRACK, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '(') {
                LexToken tk = {LPAR, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == ')') {
                LexToken tk = {RPAR, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == '[') {
                LexToken tk = {LBRACE, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else if (token_buff[0] == ']') {
                LexToken tk = {RBRACE, {0}}; 
                ans = insert_LexToken(ans, tk).result;
                fgetc(fp); // skipping one ahead to guarantee progress
            }
            else {
                print_yellowln("unknown token: \"%s\"", token_buff);
                fgetc(fp); // skipping one ahead to guarantee progress
            }
        }
    }

    // unreachable
    return ans;
}

void print_lex_wp(LexTokenWp wp) {
    print_yellowln("cap: %ld | size: %d | count: %ld ", wp.capacity, wp.size, wp.count);
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
            case CONST_INT: {
                print_yellow("CONT_INT");
                break;
            }
            case CONST_FLT: {
                print_yellow("CONST_FLT");
                break;
            }
            case CONST_CHR: {
                print_yellow("COSNT_CHR");
                break;
            }
            case CONST_STR: {
                print_yellow("COSNT_STR");
                break;
            }
            case LBRACK: {
                print_yellow("LBRACK");
                break;
            }
            case RBRACK: {
                print_yellow("RBRACK");
                break;
            }
            case LPAR: {
                print_yellow("LPAR");
                break;
            }
            case RPAR: {
                print_yellow("RPAR");
                break;
            }
            case LBRACE: {
                print_yellow("LBRACE");
                break;
            }
            case RBRACE: {
                print_yellow("RBRACE");
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






















