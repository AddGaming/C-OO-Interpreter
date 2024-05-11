#include "color_print.h"
#include "dynamic_array.h"
#include "lexer.h"

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






















