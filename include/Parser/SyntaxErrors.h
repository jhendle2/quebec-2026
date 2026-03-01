#ifndef SYNTAX_ERRORS_H
#define SYNTAX_ERRORS_H

#include "Parser/SyntaxTypes.h"
void reportSyntaxError(const SyntaxType syntax_error, const Tokens tokens);

#endif /* SYNTAX_ERRORS_H */