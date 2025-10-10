#ifndef VERIFY_H
#define VERIFY_H

#include "InputReader.h"

enum ASMerr_t {
    ASM_CORRECT = 0,
    EXTRA_ARGUMENT = 1,
    MISSING_ARGUMENT = 2,
    WRONG_FUNC = 3
};

enum ASMcommands{
    WRONG_COMMAND = -1,
    SKIP_LINE = 0,
    EXIT = 1,
    INIT = 2,
    PUSH = 3,
    POP = 4,
    DESTROY = 5,
    ADD = 6,
    MUL = 7,
    DIV = 8,
    JB = 9

};

//#define WRONG_VALUE_CONST 0x11A15ED

#define ASM_VERIFY(mode, value, IP) \
    do { \
        ASMerr_t __code = Verify(mode, value); \
        if (__code != ASM_CORRECT) \
            {ASM_DUMP(__code, IP);} else \
            {ASM_error = ASM_CORRECT;} \
    } while (0)

#define ASM_DUMP(code, IP) \
    do { \
        fprintf(stdout, "Program failed in %s:%zu ", ASM_file_name, (IP +1)); \
        PrintError(code); \
        ASM_error = code; \
    } while (0)

extern int nErrors;
extern ASMerr_t ASM_error;


//void StackDump (Stack_t* stk);
void PrintError (ASMerr_t errorCode);
ASMerr_t Verify (ASMcommands mode,  int value);

#endif
