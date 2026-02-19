#include "Parser/Parser.h"
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Log/Log.h"
#include "Parser/SyntaxMap.h"
#include "Parser/SyntaxTypes.h"

#include <stdio.h>
#include <stdlib.h>

Snode snodeFromToken(const Token token) {
    Snode snode = malloc(sizeof(*snode));
    snode->tokens = token;
    snode->stype  = tokenToSyntaxType(token);
    snode->prev   = snode->next = NULL;
    snode->parent = snode->left = snode->right = NULL;
    return snode;
}

Snode snodeFromCopy(const Snode snode) {
    Snode copy = malloc(sizeof(*copy));
    copy->tokens = snode->tokens;
    copy->stype  = snode->stype;
    copy->prev   = snode->next = NULL;
    copy->parent = snode->left = snode->right = NULL;
    return snode;
}

void snodePushBack(Snode* psnode, Snode next) {
    try (psnode!=NULL, "Cannot push back to NULL Snode pointer.");

    Snode snode = (*psnode);
    if (snode == NULL) {
        (*psnode) = next;
        return;
    }

    if (snode->next == NULL) {
        snode->next = next;
        next->prev  = snode;
        return;
    }

    return snodePushBack(
        &(snode->next),
        next
    );
}

void snodeAddLeftChild(Snode snode, Snode child) {
    // snodePushBack(
    //     &(snode->left),
    //     child
    // );
    snode->left = child;
    child->parent = snode;
}

void snodeAddRightChild(Snode snode, Snode child) {
    // snodePushBack(
    //     &(snode->right),
    //     child
    // );
    snode->right = child;
    child->parent = snode;
}

Snode snodePopBack(Snode* psnode) {
    try (psnode!=NULL, "Cannot pop back from NULL Snode pointer.");

    Snode snode = (*psnode);
    if (snode == NULL) {
        return NULL;
    }

    if (snode->next == NULL) {
        (*psnode) = NULL;
        return snode;
    }

    return snodePopBack(
        &(snode->next)
    );
}

Snode snodeBack(Snode snode) {
    try (snode!=NULL, "Cannot find back from NULL Snode.");

    if (snode->next == NULL)
        return snode;

    return snodeBack(
        snode->next
    );
}

void destroySnode(Snode* psnode) {
    try (psnode!=NULL, "Cannot destroy NULL Snode pointer.");

    Snode snode = (*psnode);
    if (snode == NULL) return;

    destroyTokens(&(snode->tokens));

    if (snode->next ) destroySnode(&(snode->next    ));
    if (snode->left ) destroySnode(&(snode->left    ));
    if (snode->right) destroySnode(&(snode->right   ));

    (*psnode) = NULL;
}

void dumpSnode(const Snode snode) {
    if (snode == NULL) {
        printf("(null)");
        return;
    }

    printf("%s ",
        strSyntaxType[snode->stype]
    );
    listTokens(snode->tokens);
}

void treeSnode(const Snode snode, const size_t level) {
    if (snode == NULL) {
        printf("(null)");
        return;
    }

    for (size_t i = 0; i < level; i++)
        printf(" *");

    printf(" %s ",
        strSyntaxType[snode->stype]
    );
    listTokens(snode->tokens); printf("\n");

    if (snode->left ) treeSnode(snode->left , level+1);
    if (snode->right) treeSnode(snode->right, level+1);
}

void listSnodes(const Snodes snodes) {
    FOREACH(Snode, snode, snodes) {
        printf("[");
        listTokens(snode->tokens);
        printf("] ");
    }
}

size_t lenSnodes(const Snodes snodes) {
    if (snodes       == NULL) return 0;
    if (snodes->next == NULL) return 1;
    return 1 + lenSnodes(snodes->next);
}

// ================================================================
Snode buildSyntaxTree(const Token tokens) {
    // ----------------------------------------------------------------
    try(tokens!=NULL,
        "Cannot build syntax tree from [0] tokens."
    );
    try (tokens->next!=NULL,
        "Cannot build syntax tree from [1] token."
    );

    // ----------------------------------------------------------------
    Snode snode_stack    = NULL;
    Snode current_parent = snode_stack;

    snodePushBack(&snode_stack,
        snodeFromToken(
            copyToken(tokens)
        )
    );

    FOREACH (Token, token, tokens->next) {
        // const size_t stack_len = lenSnodes(snode_stack);
        // printf("@ `%s` -> ", token->text);
        // listSnodes(snode_stack); printf("(%zu)\n", stack_len);

        // Snode stack has a minimum size of 2
        snodePushBack(&snode_stack,
            snodeFromToken(
                copyToken(token)
            )
        );

        // Collapse the remaining snodes in the stack
        while (lenSnodes(snode_stack) >= 2) {
            // listSnodes(snode_stack); printf("(%zu)\n", stack_len);
            Snode back1 = snodePopBack(&snode_stack);
            Snode back2 = snodePopBack(&snode_stack);

            SyntaxType combined_type = syntaxTypeMap(
                back2->stype,
                back1->stype
            );

            // printf("%s `%s` + %s `%s` := %s\n\n",
            //     strSyntaxType[back2->stype], back2->tokens->text,
            //     strSyntaxType[back1->stype], back1->tokens->text,
            //     strSyntaxType[combined_type]
            // );
            if (combined_type == SyntaxTypeUndefined) {
                snodePushBack(&snode_stack, back2);
                snodePushBack(&snode_stack, back1);
                break;
            }
            
            Snode next_parent = snodeFromToken(
                copyTokens(
                    back2->tokens
                )
            );
            pushBackToken(
                &(next_parent->tokens),
                copyTokens( // Otherwise, we double free
                    back1->tokens
                )
            );
            next_parent->stype = combined_type;
            snodeAddLeftChild(next_parent, back2);
            snodeAddRightChild( next_parent, back1);
            snodePushBack(&snode_stack, next_parent);
            next_parent->parent = current_parent;
            current_parent = next_parent;
        }
    }
    // FIXME: Maybe assert the stack isn't empty?

    return snode_stack;
}