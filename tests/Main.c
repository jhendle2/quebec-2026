#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tests/Test.h"
#include "Tests/Lexer/Keywords.h"
#include "Tests/Lexer/Operators.h"
#include "Tests/Lexer/Constants.h"
#include "Tests/Lexer/Lexer.h"

size_t gl_NumTests = 0;

int main(int argc, char** argv) {
    if (argc>=2 && strncmp(argv[1], "-v", 3)==0)
        gl_EnableDebug = true;

    printf(BCYN "Beginning tests...\n\n" CRESET);

    RUN_TEST(Keywords);
    RUN_TEST(Operators);
    RUN_TEST(Constants);
    RUN_TEST(Lexer);

    printf(BCYN "(%zu) tests successful.\n"CRESET, gl_NumTests);

    return EXIT_SUCCESS;
}