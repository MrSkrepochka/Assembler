#include "Parser.h"



void TranslateCode(InputData buffer)
{
    int* array_for_code = (int*) calloc (nArgs_plus_commands, sizeof(int));
    size_t code_counter = 0;

    char ByteCode_name[20] = "";
    fprintf(stdout, "Enter your byte-code file name (.txt)\n");
    fscanf(stdin, "%19s", ByteCode_name);

    FILE* ByteCode_file = fopen(ByteCode_name, "w");
    fprintf(ByteCode_file, "%zu ", nArgs_plus_commands);

    size_t IP = 0;

    while (IP < buffer.nLines && nErrors <=10)
    {
        int elements_read = 0;
        char command[20] = "";

        int arg = 0;
        int extra_arg = 0;
        char label[20] = "";

        elements_read = sscanf(buffer.line_ptr[IP],"%19s %19s %d", command, label, &extra_arg);

        if ( (arg = atoi (label)) == 0 && strcmp(label, "0") != 0)
            elements_read--;


        ASMcommands mode = DefineMode (command);


        if (mode == WRONG_COMMAND && elements_read == 0)
            mode = SKIP_LINE;

        if (mode == WRONG_COMMAND && command[0] == ':')
        {
            assert (number_of_labels < 10);
            assert (command[1] < 10 && command[1] >=0);

            All_labels[number_of_labels].number = (int) command[1];
            All_labels[number_of_labels].adress = (int) IP + 1;

            number_of_labels++;
            IP++;
            continue;
        }

        switch (mode)
        {

        case INIT:

            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = 2;
            code_counter++;

            ASM_VERIFY(INIT, elements_read, IP);
            if (ASM_error == ASM_CORRECT)
            {
                array_for_code[code_counter] = arg;
                code_counter++;
            }
            IP++;
            break;

        case PUSH:
            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = 3;
            code_counter++;

            ASM_VERIFY(PUSH, elements_read, IP);

            if (ASM_error == ASM_CORRECT)
            {
                array_for_code[code_counter] = arg;
                code_counter++;
            }
            IP++;
            break;

        case POP:
            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = 4;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);

            IP++;

            break;
        case MUL:
            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = 7;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);
            IP++;

            break;
        case DESTROY:
            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = DESTROY;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);

            IP++;

            break;
        case EXIT:
            array_for_code[code_counter] = 1;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            
            if (ASM_error != ASM_CORRECT)
                nErrors++;
            FillFile(array_for_code, code_counter, ByteCode_file);

            fclose(ByteCode_file);
            free(array_for_code);
            return;
            break;
        case ADD:
            array_for_code[code_counter] = 6;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            break;
        case DIV:
            array_for_code[code_counter] = DIV;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            break;

        case PUSHR:

            array_for_code[code_counter] = PUSHR; // RAX и тд
            code_counter++;

            PUSHR_POPR(array_for_code, code_counter, label, IP);
            IP++;

            break;
        case POPR:
            array_for_code[code_counter] = POPR;
            code_counter++;

            PUSHR_POPR(array_for_code, code_counter, label, IP);
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
    free(array_for_code);
    return;
}

ASMcommands DefineMode(char* command)
{
    if (strcmp (command, "INIT")== 0 )
        return INIT;

    if (strcmp (command, "PUSH")== 0 )
        return PUSH;

    if (strcmp (command, "POP")== 0 )
        return POP;

    if (strcmp (command, "DELETE")== 0 )
        return DESTROY;

    if (strcmp (command, "EXIT")== 0 )
        return EXIT;

    if (strcmp (command, "ADD")== 0 )
        return ADD;

    if (strcmp (command, "MUL")== 0 )
        return MUL;

    if (strcmp (command, "PUSHR")== 0 )
        return PUSHR;

    if (strcmp (command, "POPR")== 0 )
        return POPR;

    if (strcmp (command, "DIV")== 0 )
        return DIV;

    return WRONG_COMMAND;
}

void FillFile(int* array, size_t counter, FILE* file_pointer)
{
    fprintf(file_pointer, "%d ", (int) nArgs_plus_commands);

    for (size_t i = 0; i < counter; i++)
    {
        fprintf(file_pointer, "%d ", array[i]);
    }
}
