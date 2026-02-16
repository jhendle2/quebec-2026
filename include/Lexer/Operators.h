#ifndef OPERATORS_H
#define OPERATORS_H

#include "Utils/Macro.h"
#include "Lexer/Common.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef enum {
OperatorUndefined=0,
#define Operator(ID,S) CAT(Operator,ID),
    #include "Operators.inc"
#undef Operator
NumOperators
} Operator;

static const char* strOperator[] = {
"Undefined",
#define Operator(ID,S) QUOTE(ID),
    #include "Operators.inc"
#undef Operator
};

static inline Operator getOperator(const char* s) {
    #define Operator(ID,S) if (strncmp(S,s,MAX_TEXT)==0) return CAT(Operator,ID);
        #include "Operators.inc"
    #undef Operator
    return OperatorUndefined;
}

static inline bool isOperator(const char* s) {
    return getOperator(s) != OperatorUndefined;
}

#define matchOperator(ID, S) (CAT(Operator,ID)==getOperator(S))

#endif /* OPERATORS_H */