#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Lexer/Lexer.h"
#include "Log/Log.h"

int main(int argc, char** argv) {
    try (argc >= 3, "Usage: ./quebec -f FILE_PATH.c");
    try (strcmp(argv[1], "-f")==0, "Usage: ./quebec -f FILE_PATH.c");
    const char* file_path = argv[2];

    Tokens tokens = tokenizeFile(file_path);
    dumpTokens(tokens);
    destroyTokens(&tokens);
    
    return EXIT_SUCCESS;
}