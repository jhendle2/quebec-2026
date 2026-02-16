#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

#include "Token.h"

Tokens tokenizeString(const char* file_path, const char* string, const size_t string_len);
Tokens tokenizeFile  (const char* file_path);

#endif /* LEXER_H */