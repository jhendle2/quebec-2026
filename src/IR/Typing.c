#include "IR/Typing.h"
#include "Lexer/Common.h"
#include "Lexer/Keywords.h"
#include "Lexer/Token.h"
#include "Log/Log.h"
#include "Parser/Parser.h"
#include "Parser/SyntaxTypes.h"

bool isPointerType(const Snode snode) {
    try(snode,
        "Cannot `isPointerType` a NULL Snode"
    );

    return
        hasChildFromTypes(snode, (SyntaxType[MAX_SYNTAX_TYPE_ARRAY]){
            SyntaxTypePrimitiveType,
            SyntaxTypeCompoundType,
        }) &&
        hasChildFromTypes(snode, (SyntaxType[MAX_SYNTAX_TYPE_ARRAY]){
            SyntaxTypeMultiply
        })
    ;
}

Token substituteType(const Snode snode) {
    if (isPointerType(snode)) {
        return newToken(0, 0, "ptr", sizeof("ptr"), "");
    }

    const Snode base_type = findChildFromType(
        snode,
        SyntaxTypePrimitiveType
    );
    
    try (base_type,
        "Unexpected error when finding base type"
    );

    return copyToken(base_type->tokens);
}