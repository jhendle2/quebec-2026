#include "Lexer/Lexer.h"
#include "File/File.h"
#include "Lexer/Operators.h"
#include "Lexer/StringTypes.h"
#include "Log/Log.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "Lexer/Common.h"
#include "Lexer/Delims.h"

Tokens tokenizeString(const char* file_path, const char* string, const size_t string_len) {
    // ----------------------------------------------------------------
    // FILE* fp = fopen(file_path, "r");
    // try (fp != NULL,
    //     "Failed to open file path (%s).", file_path
    // );
    
    // ----------------------------------------------------------------
    int    row = 1, col = 0;
    Tokens tokens = NULL;
    char   text[MAX_TEXT] = "";
    size_t text_len = 0;
    // size_t string_index = 0;

    bool    in_string        = false,
            in_char          = false,
            in_comment_line  = false,
            in_comment_block = false;

    // ----------------------------------------------------------------
    // Lambda-like macros

    // Reset the text buffer and its cursor
    #define flushToken() text[text_len=0]=0

    // Append tokens only if they are non-empty &
    // not inside comments
    #define appendToken() \
    if ( (text_len>0) && !(in_comment_line || in_comment_block)) {\
        /*dbug("PUSHED %s", text);*/\
        pushBackToken(\
            &tokens,\
            newToken(\
                row,\
                col - text_len,\
                text,\
                text_len,\
                file_path\
            )\
        );\
        flushToken();\
    }

    // For operator matching
    #define MAX_OP 8 // Ideally we only need like 3 but this is a bit safer
    char op[MAX_OP] = "";

    // Append a char unless it builds an operator
    // Flush if it breaks a previously built operator
    #define appendChar(C) {\
        try (text_len < (MAX_TEXT-1),\
            "Token is too long. Max size is (%d).", MAX_TEXT-1);\
        if (!(in_string || in_char) && text_len>=1) {\
            const char last_c = text[text_len-1];\
            if ((isDelim(C) || isDelim(last_c)) &&\
                !(isDigitDecimal(C)      && matchDelim(Period, last_c)) &&\
                !(isDigitDecimal(last_c) && matchDelim(Period, C     ))\
            ) {\
                snprintf(op, MAX_OP, "%s%c", text, C);\
                if (!isOperator(op)) {\
                    appendToken();\
                }\
            }\
        }\
        text[text_len++] = C;\
        text[text_len+0] = 0;\
    }

    // ----------------------------------------------------------------
    // Main tokenizer loop
    // for (char c = string[string_index++]; string_index < string_len; c = string[string_index++]) {
    for (size_t string_index = 0; string_index < string_len; string_index++) {
        const char c = string[string_index];

        col++;
        // dbug("@ [%zu] `%c` -> `%s`",
        //     string_index,
        //     c,
        //     text
        // );

        // ----------------------------------------------------------------
        // Initiate a quoteable
        if (!in_char && matchDelim(QuoteDouble, c)) {
            if (!in_string) appendToken();
                            appendChar(c);
            if ( in_string) appendToken();
            in_string = !in_string;
            goto NextChar;
        }
        if (!in_string && matchDelim(QuoteSingle, c)) {
            if (!in_char) appendToken();
                          appendChar(c);
            if ( in_char) appendToken();
            in_char = !in_char;
            goto NextChar;
        }
        if (in_char || in_string) goto AppendChar; // Keep quoteables together

        // ----------------------------------------------------------------
        // Initiate a comment
        if (matchOperator(CommentOpen, text)) {
            flushToken();
            in_comment_block = true;
            continue;
        }
        if (matchOperator(CommentLine, text)) {
            flushToken();
            in_comment_line = true;
            continue;
        }

        // FIXME: Temporary fix for disabling preprocessor
        if (col<=2 && matchDelim(Hash, c)) {
            flushToken();
            for (int d = 0; string_index < string_len; d = string[string_index++]) {
                if (matchDelim(Backslash, d)) {
                    const int e = string[string_index++];
                    try (matchDelim(Newline, e),
                        "Cannot follow line continue with non-newline character."
                    ); continue;
                } if (matchDelim(Newline, d)) break;
            } goto NextChar;
        }

        // De-initiate a comment
        if (in_comment_block && matchOperator(CommentClose, text+text_len-2)) { // FIXME: Hack w/ a magic number :(
            flushToken();
            in_comment_block = false;
            continue;
        }

        // ----------------------------------------------------------------
        // Whitespace outside quoteables is delimiting
        if (isSpace(c)) {
            appendToken();
            goto NextChar;
        }

// ----------------------------------------------------------------
AppendChar:
        // All other chars grow the text buffer
        appendChar(c);
        
// ----------------------------------------------------------------
NextChar:
        // Increment row counter on newlines
        if (matchDelim(Newline, c)) {
            row++;
            col = 1;
            if (in_comment_line) { // Automatically close line comments
                flushToken();
                in_comment_line = false;
            }
        }
    } appendToken();

    // dbug("[DONE]\n");
    return tokens;
}

Tokens tokenizeFile(const char* file_path) {
    char* file_string = NULL;
    const size_t file_len = openFileAsStringAndClose(file_path, &file_string);

    Tokens tokens = tokenizeString(file_path, file_string, file_len);

    free(file_string);
    return tokens;
}