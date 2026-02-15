#ifndef TEST_H
#define TEST_H

#include "Log/Log.h"
#include "Utils/Macro.h"

#include <stdlib.h>

extern size_t gl_NumTests;

#define BEGIN_TEST(ID) static inline void CAT(TEST_,ID)() {\
    gl_NumTests++;\
    begin_test(QUOTE(ID));\
    size_t num_pass = 0, num_fail = 0;\
//

#define END_TEST(ID) \
    printf("\n");\
    if (num_pass) pass("Num Pass = %zu/%zu", num_pass, num_pass+num_fail);\
    if (num_fail) fail("Num Fail = %zu/%zu", num_fail, num_pass+num_fail);\
    if (num_fail>0) fail_test(QUOTE(ID));\
    end_test(QUOTE(ID));\
    printf("\n");\
}

#define REQUIRE(X) {\
    if ((X)) { pass(QUOTE(X)); num_pass++; }\
    else     { fail(QUOTE(X)); num_fail++; }\
}

#define RUN_TEST(ID) CAT(TEST_,ID)()

#endif /* TEST_H */