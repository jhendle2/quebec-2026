#ifndef PARSER_H
#define PARSER_H

// #include "Lexer/Lexer.h"
#include "SyntaxTypes.h"

typedef struct syntax_node_s* Snode;
struct syntax_node_s {
    Tokens     tokens;
    SyntaxType stype;

    Snode prev  , next;
    Snode parent, left, right;
};
typedef Snode Snodes;

void destroySnode(Snode* psnode);
void treeSnode(const Snode snode, const size_t level);
Snode buildSyntaxTree(const Token tokens);

#endif /* PARSER_H */