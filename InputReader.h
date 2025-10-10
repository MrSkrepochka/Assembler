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

#define WRONG_VALUE_CONST 0x11A15ED

struct InputData{
    char* contents;
    char** line_ptr;
    size_t size;
    size_t nLines;
    int descriptor;
};

struct Label{
    int number;
    int adress;
};

extern Label All_labels[10];
extern size_t number_of_labels;
extern size_t nArgs_plus_commands;
extern char ASM_file_name[50];
extern int Registers[16];

size_t CountLines (char* poem);
void DivideInput (InputData* buffer);
void ReadInput (InputData* buffer);

#endif
