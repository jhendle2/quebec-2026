#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Lexer/Lexer.h"
#include "Log/Log.h"
#include "Parser/Parser.h"

int main(int argc, char** argv) {
    try (argc >= 3, "Usage: ./quebec -f FILE_PATH.c");
    try (strcmp(argv[1], "-f")==0, "Usage: ./quebec -f FILE_PATH.c");
    for (size_t i = 1; i<argc; i++) {
        if (strcmp(argv[i], "-v")==0)
            gl_EnableDebug=true;
    }
    const char* file_path = argv[2];

    Tokens tokens = tokenizeFile(file_path);
    dumpTokens(tokens);
    
    // Snode snode = buildSyntaxTree(tokens);
    destroyTokens(&tokens);
    
    return EXIT_SUCCESS;
}