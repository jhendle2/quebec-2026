#ifndef IR_H
#define IR_H

#include "Parser/Parser.h"
#include "Utils/Macro.h"

typedef enum {
IRTypeUndefined=0,
    #define IRType(ID, NARGS) CAT(IRType, ID),
        #include "IRTypes.inc"
    #undef IRType
NumIRTypes
} IRType;

static const char* strIRType[] = {
"Undefined",
    #define IRType(ID, NARGS) QUOTE(ID),
        #include "IRTypes.inc"
    #undef IRType
};

typedef struct ir_s* IR;
struct ir_s {
    short  nargs;
    IRType irtype;
    Token  tokens;
    IR     next;
};
typedef IR IRs;

IRs genIR(const Snode syntax_tree);

void destroyIR(IR* p_ir);

#endif /* IR_H */