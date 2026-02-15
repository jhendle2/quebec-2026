#include "Lexer/Operators.h"
#include "Tests/Test.h"

BEGIN_TEST(Operators)
    REQUIRE(matchOperator(Increment, "++"));
    REQUIRE(matchOperator(Decrement, "--"));
    REQUIRE(matchOperator(BraceOpen, "{"));
    REQUIRE(matchOperator(BraceClose, "}"));
    REQUIRE(matchOperator(ParenOpen, "("));
    REQUIRE(matchOperator(ParenClose, ")"));
    REQUIRE(matchOperator(BracketOpen, "["));
    REQUIRE(matchOperator(BracketClose, "]"));
    REQUIRE(matchOperator(Dot, "."));
    REQUIRE(matchOperator(Arrow, "->"));
    REQUIRE(matchOperator(Plus, "+"));
    REQUIRE(matchOperator(Minus, "-"));
    REQUIRE(matchOperator(NotBoolean, "!"));
    REQUIRE(matchOperator(NotBitwise, "~"));
    REQUIRE(matchOperator(Multiply, "*"));
    REQUIRE(matchOperator(AndBitwise, "&"));
    REQUIRE(matchOperator(Divide, "/"));
    // REQUIRE(matchOperator(Modulo, "%")); // Preprocessor is unhappy
    REQUIRE(matchOperator(ShiftLeft, "<<"));
    REQUIRE(matchOperator(ShiftRight, ">>"));
    REQUIRE(matchOperator(Less, "<"));
    REQUIRE(matchOperator(LessEq, "<="));
    REQUIRE(matchOperator(Greater, ">"));
    REQUIRE(matchOperator(GreaterEq, ">="));
    REQUIRE(matchOperator(Equal, "=="));
    REQUIRE(matchOperator(NotEqual, "!="));
    REQUIRE(matchOperator(Xor, "^"));
    REQUIRE(matchOperator(OrBitwise, "|"));
    REQUIRE(matchOperator(AndBoolean, "&&"));
    REQUIRE(matchOperator(OrBoolean, "||"));
    REQUIRE(matchOperator(Ternary, "?"));
    REQUIRE(matchOperator(Colon, ":"));
    REQUIRE(matchOperator(Assign, "="));
    REQUIRE(matchOperator(AssignPlus, "+="));
    REQUIRE(matchOperator(AssignMinus, "-="));
    REQUIRE(matchOperator(AssignMultiply, "*="));
    REQUIRE(matchOperator(AssignDivide, "/="));
    // REQUIRE(matchOperator(AssignModulo, "%=")); // Preprocessor is unhappy
    REQUIRE(matchOperator(AssignLeftShift, "<<="));
    REQUIRE(matchOperator(AssignRightShift, ">>="));
    REQUIRE(matchOperator(AssignAnd, "&="));
    REQUIRE(matchOperator(AssignXor, "^="));
    REQUIRE(matchOperator(AssignOr, "|="));
    REQUIRE(matchOperator(Comma, ","));
    REQUIRE(matchOperator(Semicolon, ";"));
    REQUIRE(matchOperator(CommentLine, "//"));
    REQUIRE(matchOperator(CommentOpen, "/*"));
    REQUIRE(matchOperator(CommentClose, "*/"));
    REQUIRE(matchOperator(Preprocessor, "#"));
    REQUIRE(matchOperator(LineContinue, "\\"));
END_TEST(Operators)

