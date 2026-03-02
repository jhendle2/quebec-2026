#ifndef TYPING_H
#define TYPING_H

#include "Log/Log.h"
#include "Parser/Parser.h"
#include "Parser/SyntaxTypes.h"
#include <stdbool.h>

bool isPointerType(const Snode snode);

Token substituteType(const Snode snode);

#endif /* TYPING_H */