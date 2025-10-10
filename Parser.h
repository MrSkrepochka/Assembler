#ifndef PARSER_H
#define PARSER_H

#include "Verify.h"

void TranslateCode(InputData buffer);
ASMcommands DefineMode (char* command);
void FillFile(int* array, size_t counter, FILE* file_pointer);

#define PUSHR_POPR(array, counter, label, IP) \
    do { \
        if (label[0] >= 'A' && label[0] <= 'P' && label[1] == 'X') \
            {   \
                array[counter] = (int) label[0] - 65; \
                counter++; \
            } else \
            { \
                ASM_DUMP(WRONG_REG, IP); \
                fprintf(stdout, " %s\n", label);\
                nErrors++; \
            } \
    } while (0)


#endif
