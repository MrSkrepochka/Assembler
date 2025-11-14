#ifndef VERIFY_H
#define VERIFY_H

#include "InputReader.h"

enum ASMerr_t {
    ASM_CORRECT = 0,
    EXTRA_ARGUMENT = 1,
    MISSING_ARGUMENT = 2,
    WRONG_FUNC = 3,
    WRONG_REG = 4,
    WRONG_FORMAT = 5,
    WRONG_ADDRESS = 6,
    NOWHERE_TO_RETURN = 7,
    SEG_FAULT = 8
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
    JB = 9,
    JBE = 12,
    JE = 13,
    JA = 14,
    PUSHR = 10,
    POPR = 11,
    CALL = 15,
    RET = 16,
    SQRT = 17,
    DRAW = 18,
    PUSHM = 19,
    POPM = 20,

};



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
        nErrors++;\
    } while (0)

extern int nErrors;
extern ASMerr_t ASM_error;


//void StackDump (Stack_t* stk);
void PrintError (ASMerr_t errorCode);
ASMerr_t Verify (ASMcommands mode,  int value);

#endif
