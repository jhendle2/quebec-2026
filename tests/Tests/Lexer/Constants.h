#include "Lexer/StringTypes.h"
#include "Tests/Test.h"

BEGIN_TEST(Constants)
    SECTION("Decimals");
    REQUIRE( isPossibleNumberDecimal("0"         ));
    REQUIRE( isPossibleNumberDecimal("1234"      ));
    REQUIRE( isPossibleNumberDecimal("01234"     ));
    REQUIRE(!isPossibleNumberDecimal("3.14159"   ));
    REQUIRE(!isPossibleNumberDecimal("0xDEADBEEF"));
    REQUIRE(!isPossibleNumberDecimal("Hello"));
    REQUIRE(!isPossibleNumberDecimal("main"));
    REQUIRE(!isPossibleNumberDecimal("____"));
    REQUIRE(!isPossibleNumberDecimal("0a0b0c"));
    REQUIRE(!isPossibleNumberDecimal("a0b0c"));
    REQUIRE(!isPossibleNumberDecimal("int"));
    REQUIRE(!isPossibleNumberDecimal("\"Hello, World!\""));
    
    SECTION("Floats");
    REQUIRE(!isPossibleFloat("0"         ));
    REQUIRE(!isPossibleFloat("1234"      ));
    REQUIRE(!isPossibleFloat("01234"     ));
    REQUIRE( isPossibleFloat("3.14159"   ));
    REQUIRE(!isPossibleFloat("0xDEADBEEF"));
    REQUIRE(!isPossibleFloat("Hello"));
    REQUIRE(!isPossibleFloat("main"));
    REQUIRE(!isPossibleFloat("____"));
    REQUIRE(!isPossibleFloat("0a0b0c"));
    REQUIRE(!isPossibleFloat("a0b0c"));
    REQUIRE(!isPossibleFloat("int"));
    REQUIRE(!isPossibleFloat("\"Hello, World!\""));

    SECTION("Octals");
    REQUIRE( isPossibleNumberOctal("0"         ));
    REQUIRE(!isPossibleNumberOctal("1234"      ));
    REQUIRE( isPossibleNumberOctal("01234"     ));
    REQUIRE(!isPossibleNumberOctal("3.14159"   ));
    REQUIRE(!isPossibleNumberOctal("0xDEADBEEF"));
    REQUIRE(!isPossibleNumberOctal("Hello"));
    REQUIRE(!isPossibleNumberOctal("main"));
    REQUIRE(!isPossibleNumberOctal("____"));
    REQUIRE(!isPossibleNumberOctal("0a0b0c"));
    REQUIRE(!isPossibleNumberOctal("a0b0c"));
    REQUIRE(!isPossibleNumberOctal("int"));
    REQUIRE(!isPossibleNumberOctal("\"Hello, World!\""));

    SECTION("Hexadecimals");
    REQUIRE(!isPossibleNumberHexadecimal("0"         ));
    REQUIRE(!isPossibleNumberHexadecimal("1234"      ));
    REQUIRE(!isPossibleNumberHexadecimal("01234"     ));
    REQUIRE(!isPossibleNumberHexadecimal("3.14159"   ));
    REQUIRE( isPossibleNumberHexadecimal("0xDEADBEEF"));
    REQUIRE(!isPossibleNumberHexadecimal("Hello"));
    REQUIRE(!isPossibleNumberHexadecimal("main"));
    REQUIRE(!isPossibleNumberHexadecimal("____"));
    REQUIRE(!isPossibleNumberHexadecimal("0a0b0c"));
    REQUIRE(!isPossibleNumberHexadecimal("a0b0c"));
    REQUIRE(!isPossibleNumberHexadecimal("int"));
    REQUIRE(!isPossibleNumberHexadecimal("\"Hello, World!\""));

    SECTION("Identifiers");
    REQUIRE(!isPossibleIdentifier("0"         ));
    REQUIRE(!isPossibleIdentifier("1234"      ));
    REQUIRE(!isPossibleIdentifier("01234"     ));
    REQUIRE(!isPossibleIdentifier("3.14159"   ));
    REQUIRE(!isPossibleIdentifier("0xDEADBEEF"));
    REQUIRE( isPossibleIdentifier("Hello"));
    REQUIRE( isPossibleIdentifier("main"));
    REQUIRE( isPossibleIdentifier("____"));
    REQUIRE(!isPossibleIdentifier("0a0b0c"));
    REQUIRE( isPossibleIdentifier("a0b0c"));
    REQUIRE( isPossibleIdentifier("int"));
    REQUIRE(!isPossibleIdentifier("\"Hello, World!\""));

    SECTION("Strings");
    REQUIRE(!isPossibleString("0"         ));
    REQUIRE(!isPossibleString("1234"      ));
    REQUIRE(!isPossibleString("01234"     ));
    REQUIRE(!isPossibleString("3.14159"   ));
    REQUIRE(!isPossibleString("0xDEADBEEF"));
    REQUIRE(!isPossibleString("Hello"));
    REQUIRE(!isPossibleString("main"));
    REQUIRE(!isPossibleString("____"));
    REQUIRE(!isPossibleString("0a0b0c"));
    REQUIRE(!isPossibleString("a0b0c"));
    REQUIRE(!isPossibleString("int"));
    REQUIRE( isPossibleString("\"Hello, World!\""));
    REQUIRE( isPossibleString("\"Hello, \nWorld!\""));
    REQUIRE( isPossibleString("\"Hello, \"World!\""));

    SECTION("Characters");
    REQUIRE(!isPossibleChar("0"         ));
    REQUIRE(!isPossibleChar("1234"      ));
    REQUIRE(!isPossibleChar("01234"     ));
    REQUIRE(!isPossibleChar("3.14159"   ));
    REQUIRE(!isPossibleChar("0xDEADBEEF"));
    REQUIRE(!isPossibleChar("Hello"));
    REQUIRE(!isPossibleChar("main"));
    REQUIRE(!isPossibleChar("____"));
    REQUIRE(!isPossibleChar("0a0b0c"));
    REQUIRE(!isPossibleChar("a0b0c"));
    REQUIRE(!isPossibleChar("int"));
    REQUIRE(!isPossibleChar("\"Hello, World!\""));
    REQUIRE(!isPossibleChar("\"Hello, \nWorld!\""));
    REQUIRE(!isPossibleChar("\"Hello, \"World!\""));
    REQUIRE( isPossibleChar("\'?\'"));
    REQUIRE( isPossibleChar("\'\'\'"));
    REQUIRE( isPossibleChar("\'X\'"));
END_TEST(Constants)

