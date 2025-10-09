#include "Parser.h"

//size_t nArgs_plus_commands = 0;

void TranslateCode(InputData buffer)
{
    char ByteCode_name[20] = "";
    fprintf(stdin, "Enter your byte-code file name (.txt)\n");
    fscanf(stdin, "%19s", ByteCode_name);

    FILE* ByteCode_file = fopen(ByteCode_name, "w");
    fprintf(ByteCode_file, "%zu ", nArgs_plus_commands);

    size_t linesRead = 0;

    while (linesRead < buffer.nLines)
    {
        int elements_read = 0;
        char command[20] = "";

        int arg = 0;
        int extra_arg = 0;

        elements_read = sscanf(buffer.line_ptr[linesRead],"%19s %d %d", command, &arg, &extra_arg);

        ASMcommands mode = WRONG_COMMAND;

        if (strcmp (command, "INIT")== 0 )
        mode = INIT;

        if (strcmp (command, "PUSH")== 0 )
        mode = PUSH;

        if (strcmp (command, "POP")== 0 )
        mode = POP;

        if (strcmp (command, "DELETE")== 0 )
        mode = DESTROY;

        if (strcmp (command, "EXIT")== 0 )
        mode = EXIT;

        if (strcmp (command, "ADD")== 0 )
        mode = ADD;

        if (strcmp (command, "MUL")== 0 )
        mode = MUL;

        if (strcmp (command, "DIV")== 0 )
        mode = DIV;


        switch (mode)
        {

        case INIT:

            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", INIT);
            ASM_VERIFY(INIT, elements_read);
            if (ASM_error == ASM_CORRECT)
                fprintf(ByteCode_file, "%d ", arg);
            else
                nErrors++;
            linesRead++;
            break;

        case PUSH:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", PUSH);
            ASM_VERIFY(PUSH, elements_read);

            if (ASM_error == ASM_CORRECT)
                fprintf(ByteCode_file, "%d ", arg);
            else
                nErrors++;
            linesRead++;
            break;

        case POP:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", POP);
            ASM_VERIFY(POP, elements_read);
            if (ASM_error != ASM_CORRECT)
                nErrors++;
            linesRead++;

            break;
        case DESTROY:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", DESTROY);
            ASM_VERIFY(DESTROY, elements_read);
            if (ASM_error != ASM_CORRECT)
                nErrors++;
            linesRead++;

            break;
        case EXIT:
            fprintf(ByteCode_file, "%d ", EXIT);
            ASM_VERIFY(EXIT, elements_read);
            if (ASM_error != ASM_CORRECT)
                nErrors++;
            linesRead++;

            return;
            break;
        case WRONG_COMMAND: 
            ASM_DUMP(WRONG_FUNC);
            nErrors++;
            linesRead++;
            break;
        default:
            break;
        }
    }

    fclose(ByteCode_file);
}
