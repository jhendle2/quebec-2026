#include "Lexer/Keywords.h"
#include "Tests/Test.h"

BEGIN_TEST(Keywords)
    REQUIRE(matchKeyword(Auto    , "auto"    ));
    REQUIRE(matchKeyword(Break   , "break"   ));
    REQUIRE(matchKeyword(Case    , "case"    ));
    REQUIRE(matchKeyword(Char    , "char"    ));
    REQUIRE(matchKeyword(Const   , "const"   ));
    REQUIRE(matchKeyword(Continue, "continue"));
    REQUIRE(matchKeyword(Default , "default" ));
    REQUIRE(matchKeyword(Do      , "do"      ));
    REQUIRE(matchKeyword(Double  , "double"  ));
    REQUIRE(matchKeyword(Else    , "else"    ));
    REQUIRE(matchKeyword(Enum    , "enum"    ));
    REQUIRE(matchKeyword(Extern  , "extern"  ));
    REQUIRE(matchKeyword(Float   , "float"   ));
    REQUIRE(matchKeyword(For     , "for"     ));
    REQUIRE(matchKeyword(Goto    , "goto"    ));
    REQUIRE(matchKeyword(If      , "if"      ));
    REQUIRE(matchKeyword(Int     , "int"     ));
    REQUIRE(matchKeyword(Long    , "long"    ));
    REQUIRE(matchKeyword(Register, "register"));
    REQUIRE(matchKeyword(Return  , "return"  ));
    REQUIRE(matchKeyword(Short   , "short"   ));
    REQUIRE(matchKeyword(Signed  , "signed"  ));
    REQUIRE(matchKeyword(Sizeof  , "sizeof"  ));
    REQUIRE(matchKeyword(Static  , "static"  ));
    REQUIRE(matchKeyword(Struct  , "struct"  ));
    REQUIRE(matchKeyword(Switch  , "switch"  ));
    REQUIRE(matchKeyword(Typedef , "typedef" ));
    REQUIRE(matchKeyword(Union   , "union"   ));
    REQUIRE(matchKeyword(Unsigned, "unsigned"));
    REQUIRE(matchKeyword(Void    , "void"    ));
    REQUIRE(matchKeyword(Volatile, "volatile"));
    REQUIRE(matchKeyword(While   , "while"   ));
END_TEST(Keywords)

