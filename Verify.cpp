#include "Verify.h"

int nErrors = 0;
ASMerr_t ASM_error = ASM_CORRECT;

void PrintError (ASMerr_t err)
{
    switch (err)
    {
        case ASM_CORRECT:
            break;

        case MISSING_ARGUMENT:
            fprintf(stdout, "MISSING_ARGUMENT\n");
            break;

        case WRONG_FUNC:
            fprintf(stdout, "MISSING OR WRONG COMMAND\n");
            break;
        case EXTRA_ARGUMENT:
            fprintf(stdout, "EXTRA ARGUMENT\n");
            break;
        case WRONG_REG:
            fprintf(stdout, "Attempting to interact a non-existing register");
            break;
        case WRONG_FORMAT:
            fprintf(stdout, "Using wrong input format\n");
            break;
        case WRONG_ADDRESS:
            fprintf(stdout, "Uninitialized label\n");
            break;
        case NOWHERE_TO_RETURN:
            fprintf(stdout, "Missing CALL function for your RET function\n");
            break;
        case SEG_FAULT:
            fprintf(stdout, "Segmentation failure caused by ");
        default:
            fprintf(stdout, "ASM_DUMP triggered for an unknown reason\n");
            break;

    }
}

ASMerr_t Verify(ASMcommands mode,  int nElements)
{

    switch (mode)
    {
    case PUSH:
        if (nElements < 2)
            return MISSING_ARGUMENT;
        if (nElements > 2)
            return EXTRA_ARGUMENT;
        break;
    case INIT:
        if (nElements < 2)
            return MISSING_ARGUMENT;
        if (nElements > 2)
            return EXTRA_ARGUMENT;
        break;
    case POP:
        if (nElements > 1)
            return EXTRA_ARGUMENT;
        break;
    default:
        //return ASM_CORRECT;
        break;
    }

    return ASM_CORRECT;
}
