#ifndef KEYWORD_H
#define KEYWORD_H

#include "Utils/Macro.h"
#include "Lexer/Common.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef enum {
KeywordUndefined=0,
#define Keyword(ID,S) CAT(Keyword,ID),
    #include "Keywords.inc"
#undef Keyword
NumKeywords
} Keyword;

static const char* strKeyword[] = {
"Undefined",
#define Keyword(ID,S) QUOTE(ID),
    #include "Keywords.inc"
#undef Keyword
};

static inline Keyword getKeyword(const char* s) {
    #define Keyword(ID,S) if (strncmp(S,s,MAX_TEXT)==0) return CAT(Keyword,ID);
        #include "Keywords.inc"
    #undef Keyword
    return KeywordUndefined;
}

static inline bool isKeyword(const char* s) {
    return getKeyword(s) != KeywordUndefined;
}

#define matchKeyword(ID, S) (CAT(Keyword,ID)==getKeyword(S))

#endif /* KEYWORD_H */