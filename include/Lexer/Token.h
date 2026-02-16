#ifndef TOKEN_H
#define TOKEN_H

#include "Keywords.h"
#include "Operators.h"
#include "TokenTypes.h"

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

Token newToken(
    const int       row      ,
    const int       col      ,
    const char*     text     ,
    const size_t    text_len ,
    const char*     file_path
);
void destroyTokens(Tokens* ptokens);
void dumpToken(const Token token);
void dumpTokens(const Tokens tokens);
void pushBackToken(Tokens* ptokens, Token next);
Token getToken(const Tokens tokens, const size_t index);
bool matchToken(const Token token, const char* text);
bool matchTokenValue(const Token token, const TokenValue value);
Token pluckToken(Token* ptoken);
Token copyToken(const Token token);
void listTokens(const Tokens tokens);
size_t lenTokens(const Tokens tokens);

#endif /* TOKEN_H */