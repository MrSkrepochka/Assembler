#include "Verify.h"

int nErrors = 0;
ASMerr_t ASM_error = ASM_CORRECT;


/*void StackDump (Stack_t* stk)
{
    fprintf(stdout, "StackDump called from %s in %s:%d\n\t", __func__, __FILE__, __LINE__ );
    fprintf(stdout, "stack [0x%p]\n\t", stk);
    fprintf(stdout, "size = %zu\n\t\t", stk -> size);
    fprintf(stdout, "capacity = %zu\n\t\t", stk -> capacity);
    fprintf(stdout, "data [0x%p]\n\t\t{\n\n\t\t\t", stk -> data);
    for (size_t element = 0; element < stk -> size; element++)
    {
        fprintf(stdout, "* [%zu] = %d\n\t\t\t", element, stk -> data[element]);
    }
    fprintf(stdout,"\n\t\t}\n");
}*/

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
        default:
            fprintf(stdout, "ASM_DUMP triggered for an unknown reason\n");
            break;
    }
}

ASMerr_t Verify(ASMcommands mode, int nElements)
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
    case DESTROY:
        if (nElements > 1)
            return EXTRA_ARGUMENT;
        break;
    case POP:
        if (nElements > 1)
            return EXTRA_ARGUMENT;
        break;
    case EXIT:
        if (nElements > 1)
            return EXTRA_ARGUMENT;
        break;
    default:
        return ASM_CORRECT;
        break;
    }

    return ASM_CORRECT;
}
