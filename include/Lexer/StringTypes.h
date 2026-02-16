#ifndef STRING_TYPES_H
#define STRING_TYPES_H

#include "Lexer/Delims.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ================================================================
static inline bool isAlpha(const char c) {
    return (c>='A' && c<='Z') || (c>='a' && c<='z');
}

static inline bool isAlphaUnder(const char c) {
    return isAlpha(c) || (c=='_');
}

static inline bool isDigitDecimal(const char c) {
    return (c>='0' && c<='9');
}

static inline bool isDigitOctal(const char c) {
    return (c>='0' && c<='7');
}

static inline bool isDigitHex(const char c) {
    return (c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F');
}

static inline bool isAlNum(const char c) {
    return isAlpha(c) || isDigitDecimal(c);
}

static inline bool isAlNumUnder(const char c) {
    return isAlphaUnder(c) || isDigitDecimal(c);
}

// ================================================================
static inline bool isPossibleIdentifier(const char* s) {
    if (s==NULL || *s==0 || !isAlphaUnder(*s)) return false;
    for (++s; s && *s; s++) {
        if (!isAlNumUnder(*s))
            return false;
    } return true;
}

static inline bool isPossibleString(const char* s) {
    if (s==NULL || *s==0 || !(matchDelim(QuoteDouble, *s))) return false;
    
    const char* t;
    for (t = s+1; t && *t && !(matchDelim(QuoteDouble, *t)); t++) {
        if (matchDelim(QuoteDouble, *t))
            return false;
        if (matchDelim(Backslash, *t)) {
            t++; continue;
        }
    } return matchDelim(QuoteDouble, *t);
}

static inline bool isPossibleChar(const char* s) {
    if (s==NULL || *s==0 || !(matchDelim(QuoteSingle, *s))) return false;
    
    const char* t;
    for (t = s+1; t && *t && !(matchDelim(QuoteSingle, *t)); t++) {
        if (matchDelim(QuoteSingle, *t))
            return false;
        if (matchDelim(Backslash, *t)) {
            t++; continue;
        }
    } return ((t-s)<4) && matchDelim(QuoteSingle, *t);
}

static inline bool isPossibleNumberDecimal(const char* s) {
    if (s==NULL || *s==0) return false;
    
    const char* t;
    for (t = s; t && *t; t++) {
        if (!isDigitDecimal(*t)) return false;
    } return true;
}

static inline bool isPossibleNumberOctal(const char* s) {
    if (s==NULL || *s==0 || *s!='0') return false;
    
    const char* t;
    for (t = s+1; t && *t; t++) {
        if (!isDigitOctal(*t)) return false;
    } return true;
}

static inline bool isPossibleNumberHexadecimal(const char* s) {
    if (s==NULL || *s==0 || !(*s=='0' && *(s+1)=='x')) return false;
    
    const char* t;
    for (t = s+2; t && *t; t++) {
        if (!isDigitHex(*t)) return false;
    } return true;
}

static inline bool isPossibleFloat(const char* s) {
    if (s==NULL || *s==0) return false;
    
    bool saw_dot = false;
    const char* t;
    for (t = s+1; t && *t; t++) {
        if (!saw_dot && matchDelim(Period, *t)) {
            saw_dot = true;
            continue;
        } if (!isDigitDecimal(*t)) return false;
    } return saw_dot;
}

#endif /* STRING_TYPES_H */