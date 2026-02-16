#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

#include "Utils/Macro.h"

// ================================================================
typedef enum {
    TokenTypeUndefined=0,
    #define TokenType(E) CAT(TokenType,E),
        #include "TokenTypes.inc"
    #undef TokenType
NumTokenTypes,
} TokenType;

static const char* strTokenType[NumTokenTypes] = {
    "Undefined",
    #define TokenType(E) QUOTE(E),
        #include "TokenTypes.inc"
    #undef TokenType
};

#endif /* TOKEN_TYPES_H */