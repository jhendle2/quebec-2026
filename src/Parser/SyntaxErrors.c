#include "Parser/SyntaxErrors.h"

#include "Lexer/Token.h"
#include "Log/Color.h"
#include "Parser/SyntaxTypes.h"
#include "Utils/Macro.h"

#include <stdio.h>
#include <stdlib.h>

void reportSyntaxError(const SyntaxType syntax_error, const Tokens tokens) {
    #define SyntaxError(ID, ...) \
    if (syntax_error == CAT(SyntaxTypeSyntaxError,ID)) {\
        fprintf(stderr, BRED "[SyntaxError|%s]\n", strSyntaxType[syntax_error]);\
        fprintf(stderr, __VA_ARGS__);\
        fprintf(stderr, "\n" CRESET);\
        fprintf(stdout, BRED "Tokens: ");\
        listTokens(tokens);\
        fprintf(stdout, "\n" CRESET);\
        exit(EXIT_FAILURE);\
    }
        #include "Parser/SyntaxErrors.inc"
    #undef SyntaxError
}