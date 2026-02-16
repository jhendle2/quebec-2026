#ifndef SYNTAX_TYPES_H
#define SYNTAX_TYPES_H

#include "Utils/Macro.h"
#include "Lexer/Lexer.h"

typedef enum {
SyntaxTypeUndefined=0,
#define SyntaxType(ID) CAT(SyntaxType,ID),
    #include "SyntaxTypes.inc"
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
    #include "SyntaxTypes.inc"
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

#endif /* SYNTAX_TYPES_H */