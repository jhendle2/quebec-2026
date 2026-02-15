#ifndef QUEBEC_LOG_H
#define QUEBEC_LOG_H

#include "Color.h"

#include <stdio.h>
#include <stdbool.h>

#define msg(FP, MSG, COLOR, ...) {\
    fprintf(FP, COLOR "[" MSG "] " );\
    fprintf(FP, __VA_ARGS__);\
    fprintf(FP, "\n" CRESET);\
}

extern void safeExit();
extern bool gl_EnableDebug;

#define info(...) {                     msg(stdout, "info"     , BGRN, __VA_ARGS__)              }
#define warn(...) {                     msg(stderr, "warning"  , BYEL, __VA_ARGS__)              }
#define erro(...) {                     msg(stderr, "error"    , BRED, __VA_ARGS__); safeExit(); }
#define dbug(...) { if (gl_EnableDebug) msg(stdout, "debug"    , BCYN, __VA_ARGS__)              }
#define exce(...) {                     msg(stderr, "exception", BMAG, __VA_ARGS__); safeExit(); }

#define begin_test(ID) {                fprintf(stdout, BGRN "======== BEGIN TEST :: "ID" ========\n" CRESET); }
#define SECTION(ID)    {                fprintf(stdout, BGRN "\n-------- SECTION "ID" --------\n" CRESET) ; }
#define end_test(ID)   {                fprintf(stdout, BGRN "======== PASS TEST :: "ID" ========\n" CRESET); }
#define fail_test(ID)  {                fprintf(stdout, BRED "======== FAIL TEST :: "ID" ========\n" CRESET); exit(EXIT_FAILURE); }
#define pass(...) {                     msg(stdout, "pass", BGRN, __VA_ARGS__); }
#define fail(...) {                     msg(stderr, "fail", BRED, __VA_ARGS__); }

#define try(COND,...) if (!(COND)) { exce(__VA_ARGS__) }

#endif /* QUEBEC_LOG_H */