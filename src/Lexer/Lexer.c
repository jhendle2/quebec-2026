#include "Lexer/Lexer.h"
#include "File/File.h"
#include "Lexer/Keywords.h"
#include "Lexer/Operators.h"
#include "Lexer/StringTypes.h"
#include "Log/Color.h"
#include "Log/Log.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "Lexer/Common.h"
#include "Lexer/Delims.h"

static const size_t TokenSize = sizeof(struct token_s);

static TokenValue getTokenValueFromString(Token token) {
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
    Token token = malloc(sizeof(*token) + text_len + 1); // +1 for null character
    try (token != NULL, "Failed to allocate new Token.");

    token->row       = row;
    token->col       = col;
    token->file_path = file_path;
    token->prev      = token->next = NULL;
    
    token->text = (char*)((intptr_t)(token) + (intptr_t)(TokenSize));
    strncpy(token->text, text, text_len);
    
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

Tokens tokenizeString(const char* file_path, const char* string, const size_t string_len) {
    // ----------------------------------------------------------------
    // FILE* fp = fopen(file_path, "r");
    // try (fp != NULL,
    //     "Failed to open file path (%s).", file_path
    // );
    
    // ----------------------------------------------------------------
    int    row = 1, col = 0;
    Tokens tokens = NULL;
    char   text[MAX_TEXT] = "";
    size_t text_len = 0;
    size_t string_index = 0;

    bool    in_string        = false,
            in_char          = false,
            in_comment_line  = false,
            in_comment_block = false;

    // ----------------------------------------------------------------
    // Lambda-like macros

    // Reset the text buffer and its cursor
    #define flushToken() text[text_len=0]=0

    // Append tokens only if they are non-empty &
    // not inside comments
    #define appendToken() \
    if ( (text_len>0) && !(in_comment_line || in_comment_block)) {\
        pushBackToken(\
            &tokens,\
            newToken(\
                row,\
                col - text_len,\
                text,\
                text_len,\
                file_path\
            )\
        ); flushToken();\
    }

    // For operator matching
    #define MAX_OP 8 // Ideally we only need like 3 but this is a bit safer
    char op[MAX_OP] = "";

    // Append a char unless it builds an operator
    // Flush if it breaks a previously built operator
    #define appendChar(C) {\
        try (text_len < (MAX_TEXT-1),\
            "Token is too long. Max size is (%d).", MAX_TEXT-1);\
        if (!(in_string || in_char) && text_len>=1) {\
            const char last_c = text[text_len-1];\
            if ((isDelim(c) || isDelim(last_c)) &&\
                !(isDigitDecimal(c)      && matchDelim(Period, last_c)) &&\
                !(isDigitDecimal(last_c) && matchDelim(Period, c     ))\
            ) {\
                snprintf(op, MAX_OP, "%s%c", text, c);\
                if (!isOperator(op)) {\
                    appendToken();\
                }\
            }\
        }\
        text[text_len++] = c;\
        text[text_len+0] = 0;\
    }

    // ----------------------------------------------------------------
    // Main tokenizer loop
    for (int c = string[string_index++]; string_index < string_len; c = string[string_index++]) {
        col++;
        dbug("@ [%zu] `%c` -> `%s`",
            string_index,
            c,
            text
        );

        // ----------------------------------------------------------------
        // Initiate a quoteable
        if (!in_char && matchDelim(QuoteDouble, c)) {
            if (!in_string) appendToken();
                            appendChar(c);
            if ( in_string) appendToken();
            in_string = !in_string;
            goto NextChar;
        }
        if (!in_string && matchDelim(QuoteSingle, c)) {
            if (!in_char) appendToken();
                          appendChar(c);
            if ( in_char) appendToken();
            in_char = !in_char;
            goto NextChar;
        }
        if (in_char || in_string) goto AppendChar; // Keep quoteables together

        // ----------------------------------------------------------------
        // Initiate a comment
        if (matchOperator(CommentOpen, text)) {
            flushToken();
            in_comment_block = true;
            continue;
        }
        if (matchOperator(CommentLine, text)) {
            flushToken();
            in_comment_line = true;
            continue;
        }

        // FIXME: Temporary fix for disabling preprocessor
        if (col<=2 && matchDelim(Hash, c)) {
            flushToken();
            for (int d = 0; string_index < string_len; d = string[string_index++]) {
                if (matchDelim(Backslash, d)) {
                    const int e = string[string_index++];
                    try (matchDelim(Newline, e),
                        "Cannot follow line continue with non-newline character."
                    ); continue;
                } if (matchDelim(Newline, d)) break;
            } goto NextChar;
        }

        // De-initiate a comment
        if (in_comment_block && matchOperator(CommentClose, text+text_len-2)) { // FIXME: Hack w/ a magic number :(
            flushToken();
            in_comment_block = false;
            continue;
        }

        // ----------------------------------------------------------------
        // Whitespace outside quoteables is delimiting
        if (isSpace(c)) {
            appendToken();
            goto NextChar;
        }

// ----------------------------------------------------------------
AppendChar:
        // All other chars grow the text buffer
        appendChar(c);
        
// ----------------------------------------------------------------
NextChar:
        // Increment row counter on newlines
        if (matchDelim(Newline, c)) {
            row++;
            col = 1;
            if (in_comment_line) { // Automatically close line comments
                flushToken();
                in_comment_line = false;
            }
        }
    } appendToken();

    return tokens;
}

Tokens tokenizeFile(const char* file_path) {
    char* file_string = NULL;
    const size_t file_len = openFileAsStringAndClose(file_path, &file_string);

    Tokens tokens = tokenizeString(file_path, file_string, file_len);

    free(file_string);
    return tokens;
}