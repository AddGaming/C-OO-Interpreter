/**
 * lexer impl for language
 */
#include "lexer.h"

DEFINE_INSERT(LexToken);

/**
 * moves fp to next non whitespace char
 */
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

unsigned char is_digit(char c) {
    return (c <= '9' && c >= '0');
}

unsigned char is_lower(char c) {
    return ((c <= 'z' && c >= 'a') || c == '_');
}

unsigned char is_upper(char c) {
    return (c <= 'Z' && c >= 'A');
}

/**
 * returns the lexed float, 
 * while also advancing the fp as a side effect.
 * No error checking.
 */
LexToken lex_flt_const(FILE* fp) {
    double number;
    // guaranteed to succeed because only called when lexer encountered float
    fscanf(fp, "%lf", &number);
    
    LexToken ans = {CONST_FLT, {.floatv = number}};
    return ans;
}

/**
 * returns the lexed variable name, 
 * while also advancing the fp as a side effect.
 */
LexToken lex_var(FILE* fp) {
    fpos_t pos;
    charWpRes res;
    fgetpos(fp, &pos);

    new_wp(str, char, 4);
    int c = fgetc(fp);
    // runs at least once since its called when is_lower is encountered
    while(c != EOF && is_lower(c)) {
        res = insert_char(str, c);
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        fgetpos(fp, &pos);
        c = fgetc(fp);
    }
    fsetpos(fp, &pos);
    if (c == EOF) {
        err_redln("Expected \" while lexing Variable but found EOF");
        LexToken ans = {ERROR, {0}};
        return ans;
    } else {
        res = insert_char(str, '\0'); // just making sure always terminated
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        LString lstring = {str.count, str.ptr};
        LexToken ans = {VAR, {.strv=lstring}};
        return ans;
    }
}

/**
 * returns the lexed variable name, 
 * while also advancing the fp as a side effect.
 */
LexToken lex_class(FILE* fp) {
    fpos_t pos;
    charWpRes res;
    fgetpos(fp, &pos);

    new_wp(str, char, 4);
    int c = fgetc(fp);
    // runs at least once since its called when is_upper is encountered
    while(c != EOF && (is_upper(c) || is_lower(c))) {
        res = insert_char(str, c);
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        fgetpos(fp, &pos);
        c = fgetc(fp);
    }
    fsetpos(fp, &pos);
    if (c == EOF) {
        err_redln("Expected \" while lexing Class Name but found EOF");
        LexToken ans = {ERROR, {0}};
        return ans;
    } else {
        res = insert_char(str, '\0'); // just making sure always terminated
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        LString lstring = {str.count, str.ptr};
        LexToken ans = {CLASS, {.strv=lstring}};
        return ans;
    }
}

/**
 * returns the lexed integer, 
 * while also advancing the fp as a side effect.
 * No error checking.
 */
LexToken lex_int_const(FILE* fp) {
    fpos_t pos_begin, pos_int_end;
    fgetpos(fp, &pos_begin);

    long number;
    // guaranteed to succeed because only called when lexer encountered digit
    fscanf(fp, "%ld", &number);
    fgetpos(fp, &pos_int_end);
    
    int dot = (int) '.';
    if (fgetc(fp) == dot) {
        fsetpos(fp, &pos_begin);
        return lex_flt_const(fp);
    } else {
        fsetpos(fp, &pos_int_end);
        LexToken ans = {CONST_INT, {number}};
        return ans;
    }
}

/**
 * returns the lexed integer, 
 * while also advancing the fp as a side effect
 */
LexToken lex_str_const(FILE* fp) {
    fpos_t pos;
    charWpRes res;
    fgetpos(fp, &pos);
    fseek(fp, 1, SEEK_CUR); // skipping " 

    new_wp(str, char, 4);
    int c = fgetc(fp);
    int quote = (int) '"';
    while(c != EOF && c != quote) {
        res = insert_char(str, c);
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        c = fgetc(fp);
    }
    if (c == EOF) {
        err_redln("Expected \" while lexing String Constant but found EOF");
        LexToken ans = {ERROR, {0}};
        return ans;
    } else {
        res = insert_char(str, '\0'); // just making sure always terminated
        if (res.type == SUCCESS) str = res.result;
        else {
            LexToken ans = {ERROR, {0}};
            return ans;
        }
        LString lstring = {str.count, str.ptr};
        LexToken ans = {CONST_STR, {.strv=lstring}};
        return ans;
    }
}

/**
 * returns the lexed character, 
 * while also advancing the fp as a side effect
 */
LexToken lex_chr_const(FILE* fp) {
    fpos_t pos;
    fgetpos(fp, &pos);

    char buff[4] = {'\0'}; // [', c, ', \0]
    fgets(buff, sizeof(buff), fp);
    
    if (buff[0] != '\'' || buff[2] != '\'') {
        err_redln("Expected character definition of form:\n\t'<char>'\ngot:\n\t%s", buff);
        LexToken ans = {ERROR, {0}};
        return ans;
    } else {
        LexToken ans = {CONST_CHR, {buff[1]}};
        return ans;
    }
}

/**
 * tries to lex the file 
 * returns wp of lexed tokens
 * if an error is encountered, the last element will be the token ERROR
 */
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

        if (token_buff[0] == '=' && token_buff[1] == '=') {
            LexToken tk = {EQ, {0}}; // define repetitively for sugar
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR); // skipping tokened chars 
        }
        else if (token_buff[0] == '!' && token_buff[1] == '=') {
            LexToken tk = {NEQ, {0}};  
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == 'i' && token_buff[1] == 's') {
            LexToken tk = {IS, {0}};  
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == '>' && token_buff[1] == '=') {
            LexToken tk = {GE , {0}};  
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == '<' && token_buff[1] == '=') {
            LexToken tk = {LE , {0}};  
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == '*' && token_buff[1] == '*') {
            LexToken tk = {POW , {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == 'f' && token_buff[1] == 'n') {
            LexToken tk = {FN , {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == 'c' && token_buff[1] == 'l') {
            LexToken tk = {CL , {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 2, SEEK_CUR);   
        }
        else if (token_buff[0] == ',') {
            LexToken tk = {COMMA, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == ':') {
            LexToken tk = {COLON, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == '?') {
            LexToken tk = {IF, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == '=') {
            LexToken tk = {ASS, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == '>') {
            LexToken tk = {GT, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == '<') {
            LexToken tk = {LT, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
        }
        else if (token_buff[0] == '+') {
            LexToken tk = {ADD, {0}};  
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR);   
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
        else if (token_buff[0] == '\n') {
            LexToken tk = {END, {0}}; 
            ans = insert_LexToken(ans, tk).result;
            fseek(fp, 1, SEEK_CUR); 
        }
        else if (token_buff[0] == '\'') {
            LexToken tk = lex_chr_const(fp); 
            ans = insert_LexToken(ans, tk).result;
            if (tk.type == ERROR) return ans;
        }
        else if (token_buff[0] == '\"') {
            LexToken tk = lex_str_const(fp); 
            ans = insert_LexToken(ans, tk).result;
            if (tk.type == ERROR) return ans;
        }
        else if (is_digit(token_buff[0])) {
            LexToken tk = lex_int_const(fp);
            ans = insert_LexToken(ans, tk).result;
        }
        else if (is_lower(token_buff[0])) {
            LexToken tk = lex_var(fp);
            ans = insert_LexToken(ans, tk).result;
        }
        else if (is_upper(token_buff[0])) {
            LexToken tk = lex_class(fp);
            ans = insert_LexToken(ans, tk).result;
        }
        else {
            char* err_msg = calloc(32, sizeof(char));
            sprintf(err_msg, "unknown token: \"%s\"", token_buff);
            err_yellowln("%s", err_msg);
            LString lstring = {30, err_msg};
            LexToken tk = {ERROR, {.strv = lstring}};
            ans = insert_LexToken(ans, tk).result;
            return ans;
        }
    }
    // unreachable
    return ans;
}

// ####################
// DEBUG
// ####################

char* stringify(LexToken tk){
    // since debugging only, fixed size should be fine
    char* str = calloc(100, sizeof(char));
    switch (tk.type) {
        case ADD: {
            sprintf_s(str, 100, "ADD"); break;
        }
        case SUB: {
            sprintf_s(str, 100, "SUB"); break;
        }
        case MUL: {
            sprintf_s(str, 100, "MUL"); break;
        }
        case DIV: {
            sprintf_s(str, 100, "DIV"); break;
        }
        case POW: {
            sprintf_s(str, 100, "POW"); break;
        }
        case ASS: {
            sprintf_s(str, 100, "ASS"); break;
        }
        case EQ: {
            sprintf_s(str, 100, "EQ"); break;
        }
        case NEQ: {
            sprintf_s(str, 100, "NEQ"); break;
        }
        case IS: {
            sprintf_s(str, 100, "IS"); break;
        }
        case GT: {
            sprintf_s(str, 100, "GT"); break;
        }
        case LT: {
            sprintf_s(str, 100, "LT"); break;
        }
        case GE: {
            sprintf_s(str, 100, "GE"); break;
        }
        case LE: {
            sprintf_s(str, 100, "LE"); break;
        }
        case CONST_INT: {
            sprintf_s(str, 100, "CONT_INT(%ld)", tk.value.intv); break;
        }
        case CONST_FLT: {
            sprintf_s(str, 100, "CONST_FLT(%lf)", tk.value.floatv); break;
        }
        case CONST_CHR: {
            sprintf_s(str, 100, "COSNT_CHR(%c)", tk.value.charv); break;
        }
        case CONST_STR: {
            sprintf_s(str, 100, "COSNT_STR(%s)", tk.value.strv.ptr); break;
        }
        case VAR: {
            sprintf_s(str, 100, "VAR(%s)", tk.value.strv.ptr); break;
        }
        case CLASS: {
            sprintf_s(str, 100, "CLASS(%s)", tk.value.strv.ptr); break;
        }
        case FN: {
            sprintf_s(str, 100, "FN"); break;
        }
        case CL: {
            sprintf_s(str, 100, "CL"); break;
        }
        case IF: {
            sprintf_s(str, 100, "IF"); break;
        }
        case COMMA: {
            sprintf_s(str, 100, "COMMA"); break;
        }
        case COLON: {
            sprintf_s(str, 100, "COLON"); break;
        }
        case LBRACK: {
            sprintf_s(str, 100, "LBRACK"); break;
        }
        case RBRACK: {
            sprintf_s(str, 100, "RBRACK"); break;
        }
        case LPAR: {
            sprintf_s(str, 100, "LPAR"); break;
        }
        case RPAR: {
            sprintf_s(str, 100, "RPAR"); break;
        }
        case LBRACE: {
            sprintf_s(str, 100, "LBRACE"); break;
        }
        case RBRACE: {
            sprintf_s(str, 100, "RBRACE");
            break;
        }
        case END: {
            sprintf_s(str, 100, "\n");
        }
        case ERROR: {
            sprintf_s(str, 100, "ERROR");
            break;
        }
    }
    return str;
}

void print_lex_wp(LexTokenWp wp) {
    for (size_t i = 0; i < wp.count; i++) {
        print_yellow("%s", stringify(wp.ptr[i]));
        print_yellow(", ");
    }
    print_yellowln(" ");
}

unsigned int test_LexType(const LexToken real, const LexToken expected, const char* message) {
    if (real.type == expected.type) {
        printf("\x1B[32m%s\x1B[0m\n", message);
        return 0;
    } else {
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", stringify(expected), stringify(real), message);
        return 1;
    }  
}
