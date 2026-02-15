#ifndef DELIMS_H
#define DELIMS_H

#include "Utils/Macro.h"

#include <stdbool.h>
#include <stddef.h>

typedef enum {
DelimUndefined=0,
#define Delim(ID,C) CAT(Delim,ID),
    #include "Delims.inc"
#undef Delim
NumDelims
} Delim;

const char* strDelim[] = {
"Undefined",
#define Delim(ID,C) QUOTE(ID),
    #include "Delims.inc"
#undef Delim
};

const char chrDelim[] = {
0,
#define Delim(ID,C) C,
    #include "Delims.inc"
#undef Delim
};

static inline Delim getDelim(const char c) {
    for (size_t i = 0; i<NumDelims; i++)
        if (chrDelim[i]==c) return i;
    return DelimUndefined;
}

static inline bool isDelim(const char c) {
    return getDelim(c) != DelimUndefined;
}

#define matchDelim(ID, C) (chrDelim[CAT(Delim,ID)] == C)

static inline bool isSpace(const char c) {
    return (
        matchDelim(Space  , c) ||
        matchDelim(Newline, c) ||
        matchDelim(Tab    , c) ||
        false
    );
}

#endif /* DELIMS_H */