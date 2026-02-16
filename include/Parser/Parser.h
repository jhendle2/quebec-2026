#ifndef PARSER_H
#define PARSER_H

// #include "Lexer/Lexer.h"
#include "SyntaxTypes.h"

typedef struct syntax_node_s* Snode;
struct syntax_node_s {
    Tokens     tokens;
    SyntaxType stype;

    Snode      prev  , next;
    Snode      parent, children;
};
typedef Snode Snodes;

Snode buildSyntaxTree(const Token tokens);

#endif /* PARSER_H */