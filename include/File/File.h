#ifndef FILE_H
#define FILE_H

#include <stdio.h>

FILE*  openFileIfPossible (const char* file_path, const char* mode);
void   closeFileIfPossible(const char* file_path, FILE* fp);
size_t openFileAsStringAndClose(const char* file_path, char** pstring);

#endif /* FILE_H */