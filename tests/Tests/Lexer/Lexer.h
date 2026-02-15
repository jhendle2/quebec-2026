#include "Lexer/Keywords.h"
#include "Lexer/Lexer.h"
#include "Lexer/Operators.h"
#include "Tests/Test.h"

BEGIN_TEST(Lexer)
    static const char test_string[] =
        "int main() {\n"
        "\tprintf(\"Hello, World!\\n\");\n"
        "}\n"
    ;

    static const TokenValue test_values[] = {
        {.ttype=TokenTypeKeyword    , .keyword=KeywordInt},
        {.ttype=TokenTypeIdentifier , .identifier="main"},
        {.ttype=TokenTypeOperator   , .operator=OperatorParenOpen},
        {.ttype=TokenTypeOperator   , .operator=OperatorParenClose},
        {.ttype=TokenTypeOperator   , .operator=OperatorBraceOpen},
        {.ttype=TokenTypeIdentifier , .identifier="printf"},
        {.ttype=TokenTypeOperator   , .operator=OperatorParenOpen},
        {.ttype=TokenTypeConstString, .const_string="\"Hello, World!\\n\""},
        {.ttype=TokenTypeOperator   , .operator=OperatorParenClose},
        {.ttype=TokenTypeOperator   , .operator=OperatorSemicolon},
        {.ttype=TokenTypeOperator  , .operator=OperatorBraceClose},
    };

    Token tokens = tokenizeString(
        "test_hello_world",
        test_string,
        sizeof(test_string)
    );
    REQUIRE(tokens!=NULL);

    for (size_t i = 0; i<sizeof(test_values)/sizeof(TokenValue); i++) {
        REQUIRE(
            matchTokenValue(
                getToken(tokens, i),
                test_values[i]
            )
        );
    }

    destroyTokens(&tokens);
    REQUIRE(tokens==NULL);
END_TEST(Lexer)