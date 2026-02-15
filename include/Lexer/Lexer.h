#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

#include "Keywords.h"
#include "Operators.h"

// ================================================================
typedef enum {
    TokenTypeUndefined=0,
    TokenTypeKeyword,
    TokenTypeOperator,
    TokenTypeIdentifier,
    TokenTypeConstInt,
    TokenTypeConstFloat,
    TokenTypeConstString,
    TokenTypeConstChar,
NumTokenTypes,
} TokenType;

static const char* strTokenType[NumTokenTypes] = {
    "Undefined",
    "Keyword",
    "Operator",
    "Identifier",
    "ConstInt",
    "ConstFloat",
    "ConstString",
    "ConstChar",
};

// ================================================================
typedef struct {
    TokenType ttype;
    union {
        Keyword     keyword     ;
        Operator    operator    ;
        const char* identifier  ; // Points back to `this->text`
        int         const_int   ;
        float       const_float ;
        const char* const_string; // Points back to `this->text`
        char        const_char  ;
    };
} TokenValue;

typedef struct token_s* Token;
struct token_s {
    // ----------------------------------------------------------------
    int         row, col  ;
    const char* file_path ;
    char*       text      ;
    Token       prev, next;
    TokenValue  value     ;
};
typedef Token Tokens;

void destroyTokens(Tokens* ptokens);
void dumpTokens(const Tokens tokens);
Token getToken(const Tokens tokens, const size_t index);
bool matchToken(const Token token, const char* text);
bool matchTokenValue(const Token token, const TokenValue value);

// Tokens tokenizeFile(const char* file_path);
Tokens tokenizeString(const char* file_path, const char* string, const size_t string_len);
Tokens tokenizeFile  (const char* file_path);

#endif /* LEXER_H */