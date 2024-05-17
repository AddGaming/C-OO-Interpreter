#include "rstd/rstd.h"
#include "lexer.h"
#include <stdint.h>
#include <stdlib.h>

unsigned int test_lexer(void) {
    unsigned int fails = 0;
    FILE* x_open_quotes = fopen("../examples/x_open_quotes.txt", "r");
    LexToken l1 = {ERROR, {0}};
    LexToken l2 = {IS, {0}};

    fails += test_LexType(l1, l2, "TODO: test lexer");
    return fails;
}

unsigned int test_dyn_arr(void) {
    unsigned int fails = 0;
    
    new_wp(empty, char, 4);
    charWpRes res = insert_char(empty, 'a');
    fails += test_char(res.type, SUCCESS, "Inserting into empty list succeeds");
    fails += test_char(res.result.ptr[0], 'a', "Inserting inserts element");
    fails += test_unsigned_int(res.result.count, 1, "Inserting increases element count");

    charWp partially = res.result;
    res = insert_char(partially, 'b');
    fails += test_char(res.type, SUCCESS, "Inserting into partially filled list succeeds");
    fails += test_char(res.result.ptr[1], 'b', "Inserting into partially filled inserts");
    fails += test_char(res.result.ptr[0], 'a', "Inserting doesn't alter previous elements");

    charWp filled = insert_char(res.result, 'c').result;
    filled = insert_char(filled, 'd').result;
    res = insert_char(filled, 'e');
    fails += test_char(res.type, SUCCESS, "Inserting into full with expandable size succeeds");
    fails += test_char(res.result.capacity, 8, "Inserting when capacity reached doubles capacity");
    fails += test_char(res.result.ptr[3], 'd', "Increasing doesn't alter previous elements");
    fails += test_char(res.result.ptr[4], 'e', "Inserting into the right place");
    fails += test_unsigned_int(res.result.count, 5, "Inserting increases element count");
    
    size_t MAX = SIZE_MAX / sizeof(char);
    new_wp(max_full, char, MAX);
    max_full.count = MAX;
    res = insert_char(max_full, 'x');
    fails += test_char(res.type, FAILURE, "Inserting into full list fails");
    return fails;
}

int main(void){
    unsigned int fails = 0;
    fails += test_dyn_arr();
    fails += test_lexer();
    fails += test_char('A', 'A', "SANITY SUCCESS");
    if (fails) {print_redln("Failed: %d", fails);}
    return fails;
}
