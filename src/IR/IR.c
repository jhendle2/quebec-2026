#include "IR/IR.h"
#include "IR/Typing.h"
#include "Lexer/Token.h"
#include "Log/Log.h"
#include <stdio.h>
#include <stdlib.h>
#include "Parser/Parser.h"
#include "Parser/SyntaxTypes.h"
#include "Utils/Macro.h"

// ================================================================
IR newIR(
    const IRType irtype,
    const short  nargs,
    const Token  tokens
) {
    IR ir = malloc(sizeof(*ir));
    try (ir!=NULL,
        "Failed to allocate new IR"
    );

    ir->nargs  = nargs;
    ir->irtype = irtype;
    ir->tokens = tokens;
    ir->next   = NULL;

    return ir;
}

void pushBackIR(IR* p_ir, IR next) {
    try (p_ir != NULL, "Failed to push back to NULL IR.");
    try (next != NULL, "Failed to push back a NULL IR.");
    
    IR ir = (*p_ir);
    if (ir == NULL) {
        (*p_ir) = next;
        return;
    }

    if (ir->next == NULL) {
        ir->next = next;
        return;
    }

    return pushBackIR(
        &(ir->next),
        next
    );
}

void dumpIR(const IR ir) {
    if (ir == NULL) return;
    printf("%s ", strIRType[ir->irtype]);
    listTokens(ir->tokens);
    printf(" (%d)\n", ir->nargs);
}

void dumpIRs(const IRs irs) {
    if (irs == NULL) return;
    dumpIR(irs);
    if (irs->next)
        dumpIRs(irs->next);
}

void destroyIR(IR* p_ir) {
    try(p_ir!=NULL,
        "Cannot destroy NULL IR*"
    );
    
    IR ir = (*p_ir);
    if (ir == NULL) return;

    if (ir->tokens)
        destroyTokens(&(ir->tokens));

    if (ir->next)
        destroyIR( &(ir->next) );
    free (ir);

    (*p_ir) = NULL;
}

// ================================================================
#define SyntaxType(ID) extern void CAT(genIRFrom,ID)(IR* p_irs, const Snode snode);
#define SyntaxError(ID, ...)
    #include "Parser/SyntaxTypes.inc"
#undef SyntaxError
#undef SyntaxType

void genIRFromFnDecl(IR* p_irs, const Snode fn_decl) {
    const Snode fn_type = findChildFromTypes(
        fn_decl,
        (SyntaxType[MAX_SYNTAX_TYPE_ARRAY]){
            SyntaxTypePrimitiveType,
            SyntaxTypeCompoundType,
        }
    );
    const Snode fn_name = findChildFromType(
        fn_decl,
        SyntaxTypeIdentifier
    );

    Token tokens = substituteType(fn_type);
    pushBackToken(&tokens,
        copyTokens(fn_name->tokens)
    );

    pushBackIR(p_irs,
        newIR(
            IRTypeDeclare,
            2,
            tokens
        )
    );

    pushBackIR(p_irs,
        newIR(
            IRTypeEnter,
            0,
            NULL
        )
    );
}

void genIRFromDeclaration(IR* p_irs, const Snode decl) {
    const Snode decl_type = findChildFromTypes(
        decl,
        (SyntaxType[MAX_SYNTAX_TYPE_ARRAY]){
            SyntaxTypePrimitiveType,
            SyntaxTypeCompoundType,
        }
    );
    const Snode decl_name = findChildFromType(
        decl,
        SyntaxTypeIdentifier
    );

    Token tokens = substituteType(decl_type);
    pushBackToken(&tokens,
        copyTokens(decl_name->tokens)
    );

    pushBackIR(p_irs,
        newIR(
            IRTypeDeclare,
            2,
            tokens
        )
    );
}

void genIRFromBodyEnd(IR* p_irs, const Snode body_end) {
    if (findParentFromType(body_end, SyntaxTypeFnBody)) {
        pushBackIR(p_irs,
            newIR(
                IRTypeExit,
                0,
                NULL
            )
        );
    }
}

void genIRFromReturn(IR* p_irs, const Snode ret) {
    IR ir = newIR(
        IRTypeReturn,
        0,
        NULL
    );
    pushBackIR(p_irs, ir);
}



void genIRFromSnode(IR* p_irs, const Snode snode) {
    // printf("IR @ %p\n", snode);
    // IR ir = newIR(IRTypeNoop);

    // #define SyntaxType(ID) \
    //     if (snode->stype == CAT(SyntaxType,ID)) {\
    //         CAT(genIRFrom,ID)(p_irs, snode);\
    //     }
    // #define SyntaxError(ID, ...)
    //     // #include "Parser/SyntaxTypes.inc"
    // #undef SyntaxError
    // #undef SyntaxType

    if (snode->stype == SyntaxTypeFnDecl)
        return genIRFromFnDecl(p_irs, snode);

    if (snode->stype == SyntaxTypeDeclaration)
        return genIRFromDeclaration(p_irs, snode);

    if (snode->stype == SyntaxTypeReturn)
        return genIRFromReturn(p_irs, snode);

    if (snode->stype == SyntaxTypeBodyEnd)
        return genIRFromBodyEnd(p_irs, snode);

    // pushBackIR(p_irs, ir);
}

void genIRFromTree(IR* p_irs, const Snode syntax_tree) {
    genIRFromSnode(p_irs, syntax_tree);
    if (syntax_tree->left)
        genIRFromTree(p_irs, syntax_tree->left);
    if (syntax_tree->right)
        genIRFromTree(p_irs, syntax_tree->right);
}

IRs genIR(const Snode syntax_tree) {
    IR irs = NULL;
    genIRFromTree(&irs, syntax_tree);
    dumpIRs(irs);
    destroyIR(&irs);
    return irs;
}
