#include "Parser.h"

//size_t nArgs_plus_commands = 0;

void TranslateCode(InputData buffer)
{
    char ByteCode_name[20] = "";
    fprintf(stdout, "Enter your byte-code file name (.txt)\n");
    fscanf(stdin, "%19s", ByteCode_name);

    FILE* ByteCode_file = fopen(ByteCode_name, "w");
    fprintf(ByteCode_file, "%zu ", nArgs_plus_commands); // если пустая строка?

    size_t IP = 0;

    while (IP < buffer.nLines)
    {
        int elements_read = 0;
        char command[20] = "";

        int arg = 0;
        int extra_arg = 0;

        elements_read = sscanf(buffer.line_ptr[IP],"%19s %d %d", command, &arg, &extra_arg);

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

        if (mode == WRONG_COMMAND && elements_read == 0)
        {
            fprintf(ByteCode_file, "%d ", SKIP_LINE);
            mode = SKIP_LINE;
        }

        switch (mode)
        {

        case INIT:

            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", INIT);
            ASM_VERIFY(INIT, elements_read, IP);
            if (ASM_error == ASM_CORRECT)
                fprintf(ByteCode_file, "%d ", arg);
            IP++;
            break;

        case PUSH:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", PUSH);
            ASM_VERIFY(PUSH, elements_read, IP);

            if (ASM_error == ASM_CORRECT)
                fprintf(ByteCode_file, "%d ", arg);
            IP++;
            break;

        case POP:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", POP);
            ASM_VERIFY(POP, elements_read, IP);

            IP++;

            break;
        case MUL:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", MUL);
            ASM_VERIFY(POP, elements_read, IP);
            IP++;

            break;
        case DESTROY:
            ASM_error = ASM_CORRECT;
            fprintf(ByteCode_file, "%d ", DESTROY);
            ASM_VERIFY(POP, elements_read, IP);

            IP++;

            break;
        case EXIT:
            fprintf(ByteCode_file, "%d ", EXIT);
            ASM_VERIFY(POP, elements_read, IP);

            IP++;
            if (ASM_error != ASM_CORRECT)
                nErrors++;
            return;
            break;
        case ADD:
            fprintf(ByteCode_file, "%d ", ADD);
            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            break;
        case DIV:

            fprintf(ByteCode_file, "%d ", DIV);
            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            break;
        case WRONG_COMMAND:

            ASM_DUMP(WRONG_FUNC, IP);
            nErrors++;
            IP++;
            break;

        case SKIP_LINE:
            IP++;
            break;
        default:
            break;
        }

        if (ASM_error != ASM_CORRECT)
                nErrors++;
    }

    fclose(ByteCode_file);
}
