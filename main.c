#include <stdio.h>
#include "color_print.h"

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
        // fscanf_s(file, "%49s %d %f", name, sizeof(name), &age, &salary)
        
        int fclose(FILE *fp);
    }
    return 0;
}
