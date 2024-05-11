/**
 * lexer impl for language
 */
#include "lexer.h"

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

LexTokenWp lex_file(FILE* fp) {
    new_wp(ans, LexToken, 8);  // initial cap doesn't matter
    char token_buff[3] = {'\0'}; // [c1, c2, '\0']
    fpos_t pos;
    
    while (1) {
        skip_whitespace(fp);
        if (feof(fp)) return ans;
   
        fgetpos(fp, &pos);
        fgets(token_buff, sizeof(token_buff), fp);
        fsetpos(fp, &pos);

        if (token_buff[0] == '+') {
            LexToken tk = {ADD, {0}}; // define repetitively for sugar
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); // skipping tokened chars 
        }
        else if (token_buff[0] == '-') {
            LexToken tk = {SUB, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '*') {
            LexToken tk = {MUL, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); // skipping one ahead to guarantee progress
        }
        else if (token_buff[0] == '/') {
            LexToken tk = {DIV, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '{') {
            LexToken tk = {LBRACK, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '}') {
            LexToken tk = {RBRACK, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '(') {
            LexToken tk = {LPAR, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == ')') {
            LexToken tk = {RPAR, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '[') {
            LexToken tk = {LBRACE, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == ']') {
            LexToken tk = {RBRACE, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else {
            print_yellowln("unknown token: \"%s\"", token_buff);
            fseek(fp, 1, SEEK_CUR); 
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
