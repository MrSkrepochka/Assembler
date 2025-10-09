#ifndef INPUT_READER
#define INPUT_READER

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

struct InputData{
    char* contents;
    char** line_ptr;
    size_t size;
    size_t nLines;
    int descriptor;
};

extern size_t nArgs_plus_commands;

size_t CountLines (char* poem);
void DivideInput (InputData* buffer);
void ReadInput (InputData* buffer);

#endif
