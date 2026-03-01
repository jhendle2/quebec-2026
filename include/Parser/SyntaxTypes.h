#ifndef SYNTAX_TYPES_H
#define SYNTAX_TYPES_H

#include "Lexer/Lexer.h"
#include <stdbool.h>
#include "Utils/Macro.h"

typedef enum {
SyntaxTypeUndefined=0,
#define SyntaxType(ID) CAT(SyntaxType,ID),
#define SyntaxError(ID, ...) CAT(SyntaxTypeSyntaxError,ID),
    #include "SyntaxTypes.inc"
#undef SyntaxError
#undef SyntaxType

#define Operator(ID, S) CAT(SyntaxType,ID),
    #include "Lexer/Operators.inc"
#undef Operator

#define Keyword(ID, S) CAT(SyntaxType,ID),
    #include "Lexer/Keywords.inc"
#undef Keyword

#define TokenType(ID) CAT(SyntaxType,ID),
    #include "Lexer/TokenTypes.inc"
#undef TokenType

NumSyntaxTypes
} SyntaxType;

static const char* strSyntaxType[] = {
"Undefined",
#define SyntaxType(ID) QUOTE(ID),
#define SyntaxError(ID, ...) QUOTE(ID),
    #include "SyntaxTypes.inc"
#undef SyntaxError
#undef SyntaxType

#define Operator(ID, S) QUOTE(ID),
    #include "Lexer/Operators.inc"
#undef Operator

#define Keyword(ID, S) QUOTE(ID),
    #include "Lexer/Keywords.inc"
#undef Keyword

#define TokenType(ID) QUOTE(ID),
    #include "Lexer/TokenTypes.inc"
#undef TokenType
};

SyntaxType tokenToSyntaxType(const Token token);
static inline bool isSyntaxError(const SyntaxType stype) {
    #define SyntaxError(ID, ...) if (stype == CAT(SyntaxTypeSyntaxError, ID)) return true;
        #include "SyntaxErrors.inc"
    #undef SyntaxError
    return false;
}

#endif /* SYNTAX_TYPES_H */