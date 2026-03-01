#include "Lexer/Token.h"

#include <stdlib.h>
#include <string.h>

#include "Lexer/Common.h"
#include "Lexer/StringTypes.h"
#include "Log/Log.h"

// static const size_t TokenSize = sizeof(struct token_s);

static TokenValue getTokenValueFromString(Token token) {
    try (token!=NULL, "Cannot get value from NULL token.");
    const char* text = token->text;
    
    // ----------------------------------------------------------------
    const Keyword possible_keyword = getKeyword(text);
    if (possible_keyword != KeywordUndefined) {
        return (TokenValue){
            .ttype=TokenTypeKeyword,
            .keyword=possible_keyword,
        };
    }

    // ----------------------------------------------------------------
    const Operator possible_operator = getOperator(text);
    if (possible_operator != OperatorUndefined) {
        return (TokenValue){
            .ttype=TokenTypeOperator,
            .operator=possible_operator,
        };
    }

    // ----------------------------------------------------------------
    if (isPossibleString(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstString,
            .const_string=text,
        };
    }
    if (isPossibleChar(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstChar,
            .const_char=text[1], // FIXME: Doens't work w/ escapes
        };
    }

    // ----------------------------------------------------------------
    if (isPossibleFloat(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstFloat,
            .const_float=strtof(text, NULL),
        };
    }

    if (isPossibleNumberOctal(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstInt,
            .const_int=strtoul(text, NULL, 8),
        };
    }

    if (isPossibleNumberHexadecimal(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstInt,
            .const_int=strtoul(text, NULL, 16),
        };
    }

    if (isPossibleNumberDecimal(text)) {
        return (TokenValue){
            .ttype=TokenTypeConstInt,
            .const_int=strtoul(text, NULL, 10),
        };
    }

    // ----------------------------------------------------------------
    if (isPossibleIdentifier(text)) {
        return (TokenValue){
            .ttype=TokenTypeIdentifier,
            .identifier=text,
        };
    }

    // ----------------------------------------------------------------
    erro("Unsupported token type for `%s`.",
        token->text
    ); return (TokenValue){0};
}

Token newToken(
    const int       row      ,
    const int       col      ,
    const char*     text     ,
    const size_t    text_len ,
    const char*     file_path
) {
    // dbug("newToken(%d, %d, \"%s\", %zu, \"%s\")\n",
    //     row,
    //     col,
    //     text,
    //     text_len,
    //     file_path
    // );

    // Token token = malloc(sizeof(*token));
    Token token = calloc(1, sizeof(*token) + text_len + 1); // +1 for null character
    // Token token = malloc(sizeof(*token) + text_len + 1); // +1 for null character
    try (token != NULL, "Failed to allocate new Token.");

    token->row       = row;
    token->col       = col;
    token->file_path = file_path;
    token->prev      = token->next = NULL;
    
    token->text = (char*)((size_t)(token) + (size_t)(sizeof(*token)));
    // token->text = (char*)(token + offsetof(struct token_s, text));
    strncpy(token->text, text, text_len);
    // dbug("token->text = %s\n", token->text);
    // token->text = strndup(text, text_len);
    
    token->value = getTokenValueFromString(token);
    
    return token;
}

void destroyTokens(Tokens* ptokens) {
    try (ptokens != NULL, "Failed to destroy NULL tokens.");
    
    Tokens tokens = (*ptokens);
    if (tokens == NULL) return;

    if (tokens->next)
        destroyTokens(&(tokens->next));
    
    free(tokens);
    (*ptokens) = NULL;
}

static void dumpTokenValue(const TokenValue value) {
    printf("<%s", strTokenType[value.ttype]);
    switch (value.ttype) {
        case TokenTypeKeyword    : printf(" %s", strKeyword [value.keyword ]   ); break;
        case TokenTypeOperator   : printf(" %s", strOperator[value.operator]   ); break;
        case TokenTypeConstInt   : printf(" %d",             value.const_int   ); break;
        case TokenTypeConstFloat : printf(" %f",             value.const_float ); break;
        case TokenTypeConstChar  : printf(" \'%c\'",         value.const_char  ); break;
        case TokenTypeConstString: printf(" %s",             value.const_string); break;
        case TokenTypeIdentifier : printf(" %s",             value.identifier  ); break;
        default: break;
    }  printf(">");
}

void dumpToken(const Token token) {
    if (token == NULL) return;
    printf("%s:%d:%d: %s ",
        token->file_path,
        token->row,
        token->col,
        token->text
    );
    dumpTokenValue(token->value);
    printf("\n");
}

void dumpTokens(const Tokens tokens) {
    dumpToken(tokens);
    if (tokens && tokens->next)
        dumpTokens(tokens->next);
}

void pushBackToken(Tokens* ptokens, Token next) {
    try (ptokens != NULL, "Failed to push back to NULL tokens.");
    try (next    != NULL, "Failed to push back a NULL token.");
    
    Tokens tokens = (*ptokens);
    if (tokens == NULL) {
        (*ptokens) = next;
        return;
    }

    if (tokens->next == NULL) {
        tokens->next = next;
        next->prev = tokens;
        return;
    }

    return pushBackToken(
        &(tokens->next),
        next
    );
}

Token getToken(const Tokens tokens, const size_t index) {
    try (tokens != NULL, "Cannot index into NULL tokens.");
    Token temp = tokens;
    for (size_t i = 0; i<index; i++) {
        try (temp = temp->next, "Tokens index (%zu) out of bounds.", i);
    } return temp;
}

bool matchToken(const Token token, const char* text) {
    try (token != NULL, "Cannot match NULL token to string `%s`.", text);
    try (text  != NULL, "Cannot match NULL `%s` to token.", text);
    return strncmp(token->text, text, MAX_TEXT)==0;
}

static bool _matchTokenValue(const TokenValue a, const TokenValue b) {
    if (gl_EnableDebug) {
        printf(BCYN);
        dumpTokenValue(a);
        printf(" vs ");
        dumpTokenValue(b);
        printf("\n" CRESET);
    }
    switch (a.ttype) {
        case TokenTypeKeyword    : return a.keyword    ==b.keyword    ;
        case TokenTypeOperator   : return a.operator   ==b.operator   ;
        case TokenTypeConstInt   : return a.const_int  ==b.const_int  ;
        case TokenTypeConstFloat : return a.const_float==b.const_float;
        case TokenTypeConstChar  : return a.const_char ==b.const_char ;
        case TokenTypeConstString: return strncmp(a.const_string, b.const_string, MAX_TEXT)==0;
        case TokenTypeIdentifier : return strncmp(a.identifier  , b.identifier  , MAX_TEXT)==0;
        default: return false;
    }
}

bool matchTokenValue(const Token token, const TokenValue value) {
    try (token != NULL, "Cannot match NULL token to value.");
    return (
        (token->value.ttype == value.ttype) &&
        _matchTokenValue(token->value, value)
    );
}

Token pluckToken(Token* ptoken) {
    try (ptoken != NULL, "Cannot pluck NULL token.");
    
    Token token = (*ptoken);
    if (token == NULL) return NULL;

    if (token->prev) token->prev->next = token->next;
    if (token->next) token->next->prev = token->prev;
    
    token->prev = NULL;
    token->next = NULL;
    return token;
}

Token copyToken(const Token token) {
    // Shallow copy with NO prev/next
    return newToken(
        token->row,
        token->col,
        token->text,
        strnlen(token->text, MAX_TEXT),
        token->file_path
    );

    // ----------------------------------------------------------------
    // Alternative for a `deepcopy`
    // const size_t text_len = strnlen(token->text, MAX_TEXT);
    
    // Token copied = NULL;
    // const size_t combined_len = sizeof(*copied) + text_len + 1; // +1 for null character
    // copied = malloc(combined_len);

    // memcpy(
    //     copied,
    //     token,
    //     combined_len
    // );

    // return copied;
}

void listTokens(const Tokens tokens) {
    FOREACH(Token, token, tokens) {
        printf("`%s` ", token->text);
    }
}

size_t lenTokens(const Tokens tokens) {
    if (tokens       == NULL) return 0;
    if (tokens->next == NULL) return 1;
    return 1 + lenTokens(tokens->next);
}

Tokens copyTokens(const Tokens tokens) {
    Tokens copied = NULL;
    FOREACH (Token, temp, tokens) {
        pushBackToken(
            &copied,
            copyToken(temp)
        );
    }
    return copied;
}