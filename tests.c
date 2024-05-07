#include "testing.h"

int main(void){
    unsigned int fails = 0;
    fails += test_char('A', 'A', "SUCCESS");
    fails += test_char('A', 'B', "FAIL");
    return fails;
}
