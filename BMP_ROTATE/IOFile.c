#pragma once
#include "IOFile.h"

enum IOStatusO InputO(char *file, FILE **fin)
{
    char filename[100];
    if (lenght(file) == 0)
        return ERROR_EMPTY_FILE;
    strncpy(filename, file, 100);
    *fin = fopen(filename, "rb");
    if (*fin == NULL) 
        return INVALID_NAME;

    return 0;
}

enum IOStatusO OutputO(char *file, FILE **fout)
{
    char filename[100];
    strncpy(filename, file, 100);
    *fout = fopen(filename, "wb");
    if (*fout == NULL) 
        return INVALID_NAME;

    return 0;
}

enum IOStatucC InputC(FILE **fin)
{
    if (fclose(*fin) == 0)
        return 0;
    else
        return ERROR;
     
}

enum IOStatucC OutputC(FILE **fout)
{
    if (fclose(*fout) == 0)
        return 0;
    else
        return ERROR;
}