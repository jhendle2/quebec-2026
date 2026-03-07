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
void dumpSnode(const Snode snode);
void treeSnode(const Snode snode, const size_t level);
void treeSnodeIfOnlyOneToken(const Snode snode, const size_t level);
Snode buildSyntaxTree(const Token tokens);

Snode findChildFromType(Snode parent, const SyntaxType stype);
bool  hasChildFromType(Snode parent, const SyntaxType stype);

#define MAX_SYNTAX_TYPE_ARRAY 8
Snode findChildFromTypes(Snode parent, const SyntaxType stype[MAX_SYNTAX_TYPE_ARRAY]);
bool  hasChildFromTypes(Snode parent, const SyntaxType stype[MAX_SYNTAX_TYPE_ARRAY]);

Snode findParentFromType(Snode child, const SyntaxType stype);
bool  hasParentFromType(Snode child, const SyntaxType stype);

bool hasChildrenSnode(const Snode snode);

#endif /* PARSER_H */