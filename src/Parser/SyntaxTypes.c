#include "Lexer/Keywords.h"
#include "Lexer/TokenTypes.h"
#include "Parser/SyntaxTypes.h"

SyntaxType tokenToSyntaxType(const Token token) {
    if (token->value.ttype == TokenTypeKeyword) {
        switch (token->value.keyword) {
            case KeywordInt:
            case KeywordFloat:
            case KeywordDouble:
            case KeywordChar:
            case KeywordShort:
            case KeywordVoid:
                return SyntaxTypePrimitiveType;
            
            case KeywordConst:
            case KeywordStatic:
            case KeywordInline:
            case KeywordRestrict:
            case KeywordExtern:
                return SyntaxTypeModifier;

            // Behave like both a modifier and a simple type
            case KeywordLong    : return SyntaxTypeLong;
            case KeywordUnsigned: return SyntaxTypeUnsigned;
            case KeywordSigned  : return SyntaxTypeSigned;

            default: break;
        }
    }

    #define Operator(ID, S) if (\
        token->value.ttype==TokenTypeOperator &&\
        token->value.operator==CAT(Operator,ID)\
    ) return CAT(SyntaxType,ID);
        #include "Lexer/Operators.inc"
    #undef Operator

    #define Keyword(ID, S) if (\
        token->value.ttype==TokenTypeKeyword &&\
        token->value.keyword==CAT(Keyword,ID)\
    ) return CAT(SyntaxType,ID);
        #include "Lexer/Keywords.inc"
    #undef Keyword

    #define TokenType(ID) if (token->value.ttype==CAT(TokenType,ID)) return CAT(SyntaxType,ID);
        #include "Lexer/TokenTypes.inc"
    #undef TokenType

    return SyntaxTypeUndefined;
}