#ifndef PARSER_H
#define PARSER_H

#include "Verify.h"

void TranslateCode(InputData buffer);
ASMcommands DefineMode (char* command);
void FillFile(int* array, size_t counter, FILE* file_pointer);
void VerifyLabels (InputData buffer, int* array, size_t counter);

#define PUSHR_POPR(array, counter, label, IP)                      \
    do {                                                           \
        if ((label)[0] >= 'A' && (label)[0] <= 'P' && (label)[1] == 'X')  /*add strlen?*/{ \
            (array)[*counter] = (int)((label)[0] - 'A');           \
            (*counter)++;                                          \
            printf("code_counter after PUSHR/POPR = %zu\n", *counter); \
        } else {                                                   \
            ASM_DUMP(WRONG_REG, (IP));                             \
            fprintf(stdout, " %s\n", (label));                     \
            nErrors++;                                             \
        }                                                          \
    } while (0)

#define JUMPS(array_for_code, code_counter_ptr, IP, label)                 \
    do {                                                                   \
        int local_arg = 0;                                                 \
        if ((label)[0] == ':') {                                           \
            local_arg = atoi((label) + 1);                                 \
            if (local_arg == 0 && strcmp((label) + 1, "0") != 0) {         \
                ASM_DUMP(WRONG_FORMAT, (IP));                               \
            } else {                                                       \
                (*(code_counter_ptr))++;\
                printf(" Counter after jump/call %zu\n", *(code_counter_ptr));\
                (array_for_code)[*(code_counter_ptr)] = local_arg;         \
            }                                                              \
        } else {                                                           \
            ASM_DUMP(WRONG_FORMAT, (IP));                                   \
        }                                                                  \
        (*(code_counter_ptr))++;                                           \
        (IP)++;                                                            \
    } while (0)

    #define PUSHM_POPM(array, counter, label, IP)                      \
    do {                                                               \
        if ((label)[0] == '[' && (label)[3] == ']')  /*add strlen?*/                     \
        {                                                              \
            if ((label)[1] >= 'A' && (label)[1] <= 'P' && (label)[2] == 'X') { \
                (array)[counter] = (int)((label)[1] - 'A');            \
                counter++;                                           \
                printf("code_counter after PUSHM/POPM = %zu\n", counter); \
            } else {                                                   \
                ASM_DUMP(WRONG_REG, IP);                             \
                fprintf(stdout, " %s\n", (label));                     \
                nErrors++;                                             \
            }                                                          \
        } else                                                         \
        {                                                              \
            ASM_DUMP(WRONG_FORMAT, IP);                                 \
            nErrors++;                                                 \
        }                                                              \
    } while (0)

    #endif
