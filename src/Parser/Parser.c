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
    snode->prev   = snode->next     = NULL;
    snode->parent = snode->children = NULL;
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

void snodeAddChild(Snode snode, Snode child) {
    snodePushBack(
        &(snode->children),
        child
    );
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

    if (snode->next)     destroySnode(&(snode->next    ));
    if (snode->children) destroySnode(&(snode->children));

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
    Snode snode_stack = NULL;
    #define snodeStackIsEmpty() (snode_stack==NULL)

    #define say1(STRING, S) {\
        printf("%-8s ", STRING);\
            dumpSnode(S);\
        printf("\n");\
    }
    #define say2(STRING, A, B) {\
        printf("%-8s ", STRING);\
            dumpSnode(A);\
        printf(" +  ");\
            dumpSnode(B);\
        printf("\n");\
    }

    #define snodeStackPushToken(T) {\
        snodePushBack(\
            &snode_stack,\
            snodeFromToken(\
                copyToken(tokens->next)\
            )\
        ); say1("PUSH",snodeBack(snode_stack));\
    }

    snodePushBack(&snode_stack,
        snodeFromToken(
            copyToken(tokens)
        )
    );
    FOREACH (Token, token, tokens->next) {
        
        const size_t stack_len = lenSnodes(snode_stack);
        printf("@ `%s` -> ", token->text);
        listSnodes(snode_stack); printf("(%zu)\n", stack_len);
        snodePushBack(&snode_stack,
            snodeFromToken(
                copyToken(token)
            )
        );

        while (lenSnodes(snode_stack) >= 2) {
            listSnodes(snode_stack); printf("(%zu)\n", stack_len);
            Snode back1 = snodePopBack(&snode_stack);
            Snode back2 = snodePopBack(&snode_stack);

            SyntaxType combined_type = syntaxTypeMap(
                back2->stype,
                back1->stype
            );

            printf("%s `%s` + %s `%s` := %s\n\n",
                strSyntaxType[back2->stype], back2->tokens->text,
                strSyntaxType[back1->stype], back1->tokens->text,
                strSyntaxType[combined_type]
            );
            if (combined_type == SyntaxTypeUndefined) {
                snodePushBack(&snode_stack, back2);
                snodePushBack(&snode_stack, back1);
                break;
            }
            

            pushBackToken(
                &(back2->tokens),
                back1->tokens
            );
            back2->stype = combined_type;
            snodePushBack(&snode_stack, back2);
        }
        
    }

//     FOREACH(Token, token, tokens) {
//         printf("snode_stack = ");
//         listSnodes(snode_stack);
//         printf("\n@ `%s`\n", token->text);
        
//         // Stack is size [0]
//         if (snodeStackIsEmpty()) {
//             printf("len(snode_stack) = 0\n");
//             printf("STACK EMPTY\n");
//             Snode push = snodeFromToken(
//                 copyToken(token)
//             );
//             snodePushBack(
//                 &snode_stack,
//                 push
//             ); say1("PUSH", push);
            
//             continue;
//         }

//         // Stack is size [1]
//         printf("len(snode_stack) > 0\n");
//         Snode back1 = snodePopBack(
//             &snode_stack
//         ); say1("POP", back1);
//         if (snodeStackIsEmpty()) {
//             printf("len(snode_stack) = 1\n");
//             printf("STACK EMPTY\n");
//             snodePushBack(
//                 &snode_stack,
//                 back1
//             ); say1("PUSH", back1);

//             Snode push = snodeFromToken(
//                 copyToken(token)
//             );
//             snodePushBack(
//                 &snode_stack,
//                 push
//             ); say1("PUSH", push);

//             continue;
//         }

//         // Stack is size [>1]
//         size_t limit = 0;
//         printf("len(snode_stack) > 1\n");
//         do {
//             limit++;
//             if (limit>=5) exit(EXIT_FAILURE);

//             Snode back2 = snodePopBack(&snode_stack);
//             SyntaxType combined_type = syntaxTypeMap(
//                 back2->stype,
//                 back1->stype
//             );

//             // ------------------------------------------------
//             // Not a valid combination
//             if (combined_type == SyntaxTypeUndefined) {
//                 snodePushBack(
//                     &snode_stack,
//                     back2
//                 ); say1("PUSH", back2);

//                 snodePushBack(
//                     &snode_stack,
//                     back1
//                 ); say1("PUSH", back1);

//                 goto NextToken; // Give up and add a new token
//             }
            
//             // ------------------------------------------------
//             // Otherwise,
//             back2->stype = combined_type;
//             pushBackToken( // Combine these two sets of tokens
//                 &(back2->tokens),
//                 back1->tokens
//             );
//             back1 = back2;
            
//         } while (!snodeStackIsEmpty());

//         // Restore `back1` to the stack b/c we're done processing
// NextToken:
//         snodePushBack(
//             &snode_stack,
//             back1
//         );
        // break;
        // continue;

        // printf("case 1\n");
        // if (snodeStackIsEmpty()) {
        //     snodeStackPushToken(
        //         copyToken(token)
        //     );
        //     continue;
        // }

        // // printf("case 2\n");
        // Snode back1 = snodePopBack(&snode_stack);
        // say1("POP", back1);

        // if (snodeStackIsEmpty()) {
        //     snodePushBack(&snode_stack, back1);
        //     say1("PUSH", back1);

        //     snodeStackPushToken(copyToken(token));
        //     continue;
        // }
        
        // // printf("case 3\n");
        // Snode back2 = snodePopBack(&snode_stack);
        // say1("POP", back2);

        // const SyntaxType combined_type = syntaxTypeMap(
        //     back2->stype, 
        //     back1->stype
        // );

        // if (combined_type == SyntaxTypeUndefined) {
        //     snodePushBack(&snode_stack, back2);
        //     snodePushBack(&snode_stack, back1);
        //     continue;
        // }

        // pushBackToken(
        //     &(back2->tokens),
        //     back1->tokens
        // );
        // back2->stype = combined_type;
        // snodePushBack(
        //     &snode_stack,
        //     back2
        // );

        // Snode back = snodePopBack(
        //     &snode_stack
        // );
        // while (
        //     syntaxTypeMap(
        //         ,
        //     )
        // )
        // Snode right = snodeFromToken(
        //     copyToken(token)
        // );
        // Snode back  = snodeBack(snode_stack);
        
        // printf("%-8s ", "CHECK");
        //     dumpSnode(back);
        // printf(" +  ");
        //     dumpSnode(right);
        // printf("\n");

        // SyntaxType combined_type = syntaxTypeMap(
        //     back->stype,
        //     right->stype
        // );

        // if (combined_type == SyntaxTypeUndefined) {
        //     snodePushBack(
        //         &snode_stack,
        //         right
        //     ); continue;
        // }

        // // while (combined_type != SyntaxTypeUndefined) {
        //     Snode popped = snodePopBack(&snode_stack);
        //     printf("%-8s ", "POP");
        //         dumpSnode(popped);
        //     printf("\n");

        //     popped->stype = combined_type;
        //     pushBackToken(
        //         &(popped->tokens),
        //         right->tokens
        //     );
        //     snodePushBack(&snode_stack, popped);
        //     printf("%-8s ", "PUSH");
        //         dumpSnode(popped);
        //     printf("\n\n");
            
        //     // while (
        //     //     syntaxTypeMap(
        //     //         snodeBack(snode_stack),
        //     //         right
        //     //     )
        //     // )
        //     // back = snodeBack(snode_stack);
        //     // combined_type = syntaxTypeMap(
        //     //     back->stype,
        //     //     right->stype
        //     // );
        // // }
    // }

    // ----------------------------------------------------------------
    Snode snode_tree = NULL;
    return snode_tree;
}