#ifndef QUEBEC_LOG_H
#define QUEBEC_LOG_H

#include "Color.h"

#include <stdio.h>
#include <stdbool.h>

#define msg(FP, MSG, COLOR, ...) do {\
    fprintf(FP, COLOR "[" MSG "] " );\
    fprintf(FP, __VA_ARGS__);\
    fprintf(FP, "\n" CRESET);\
} while(0)

extern void safeExit();
extern bool gl_EnableDebug;

#define info(...) do {                     msg(stdout, "info"     , BGRN, __VA_ARGS__);             } while(0)
#define warn(...) do {                     msg(stderr, "warning"  , BYEL, __VA_ARGS__);             } while(0)
#define erro(...) do {                     msg(stderr, "error"    , BRED, __VA_ARGS__); safeExit(); } while(0)
#define dbug(...) do { if (gl_EnableDebug) msg(stdout, "debug"    , BCYN, __VA_ARGS__);             } while(0)
#define exce(...) do {                     msg(stderr, "exception", BMAG, __VA_ARGS__); safeExit(); } while(0)

#define begin_test(ID) do {                fprintf(stdout, BGRN "======== BEGIN TEST :: "ID" ========\n" CRESET); } while(0)
#define SECTION(ID)    do {                fprintf(stdout, BGRN "\n-------- SECTION "ID" --------\n" CRESET) ; } while(0)
#define end_test(ID)   do {                fprintf(stdout, BGRN "======== PASS TEST :: "ID" ========\n" CRESET); } while(0)
#define fail_test(ID)  do {                fprintf(stdout, BRED "======== FAIL TEST :: "ID" ========\n" CRESET); exit(EXIT_FAILURE); } while(0)
#define pass(...) do {                     msg(stdout, "pass", BGRN, __VA_ARGS__); } while(0)
#define fail(...) do {                     msg(stderr, "fail", BRED, __VA_ARGS__); } while(0)

#define try(COND,...) if (!(COND)) { exce(__VA_ARGS__); }

#endif /* QUEBEC_LOG_H */