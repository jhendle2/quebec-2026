#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "IR/IR.h"
#include "Lexer/Lexer.h"
#include "Log/Log.h"
#include "Parser/Parser.h"

int main(int argc, char** argv) {
    try (argc >= 3, "Usage: ./quebec -f FILE_PATH.c");
    try (strcmp(argv[1], "-f")==0, "Usage: ./quebec -f FILE_PATH.c");
    for (size_t i = 1; i<(size_t)(argc); i++) {
        if (strcmp(argv[i], "-v")==0)
            gl_EnableDebug=true;
    }
    const char* file_path = argv[2];

    Tokens tokens = tokenizeFile(file_path);
    // dumpTokens(tokens);
    
    Snode syntax_tree = buildSyntaxTree(tokens);
    treeSnode(syntax_tree, 0);

    genIR(syntax_tree);
    // treeSnodeIfOnlyOneToken(snode, 0);
    destroyTokens(&tokens);

    destroySnode(&syntax_tree);

    
    return EXIT_SUCCESS;
}