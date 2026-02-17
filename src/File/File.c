#include "File/File.h"
#include "Log/Log.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE* openFileIfPossible(const char* file_path, const char* mode) {
    FILE* fp = fopen(file_path, mode);
    try (fp!=NULL,
        "Failed to open file path (%s) as mode (%s).",
        file_path,
        mode
    ); return fp;
}

void closeFileIfPossible(const char* file_path, FILE* fp) {
    try (fp!=NULL,
        "Failed to close file path (%s).",
        file_path
    ); fclose(fp);
}

size_t openFileAsStringAndClose(const char* file_path, char** pstring) {
    // ----------------------------------------------------------------
    try(file_path!=NULL,
        "Cannot load file from NULL string path."
    );
    try(pstring!=NULL,
        "Cannot allocate to NULL string pointer."
    );
    
    // ----------------------------------------------------------------
    // Get absolute file size
    FILE* fp = openFileIfPossible(file_path, "r");
    fseek(fp, 0, SEEK_END);             // Go to end of file
    const size_t string_len = ftell(fp); // Get file size
    rewind(fp);                          // Back to start of file

    // ----------------------------------------------------------------
    // Generate string of that size and copy
    (*pstring) = malloc(string_len+1);
    try((*pstring)!=NULL,
        "Failed to allocate new string."
    );
    
    fread( (*pstring), 1, string_len, fp );
    (*pstring)[string_len] = 0; // Replaces EOF

    printf("string_len = %zu\n", string_len);
    printf("string = `%.*s`\n", (int)(string_len), *pstring);

    // ----------------------------------------------------------------
    closeFileIfPossible(file_path, fp);
    return string_len;
}
