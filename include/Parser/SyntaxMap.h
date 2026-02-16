#ifndef SYNTAX_MAP_H
#define SYNTAX_MAP_H

#include "Parser/SyntaxTypes.h"
static inline SyntaxType syntaxTypeMap(
    const SyntaxType left,
    const SyntaxType right
) {
    #define SyntaxMap(L,R,M) if (\
        left ==CAT(SyntaxType,L) && \
        right==CAT(SyntaxType,R) \
    ) return   CAT(SyntaxType,M);
        #include "SyntaxMap.inc"
    #undef SyntaxMap
    return SyntaxTypeUndefined;
}

#endif /* SYNTAX_MAP_H */