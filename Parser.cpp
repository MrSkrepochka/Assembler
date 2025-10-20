#include "Parser.h"



void TranslateCode(InputData buffer)
{
    int* array_for_code = (int*) calloc ( 3 * nArgs_plus_commands, sizeof(int));
    size_t code_counter = 0;

    char ByteCode_name[20] = "";
    fprintf(stdout, "Enter your byte-code file name (.txt)\n");
    fscanf(stdin, "%19s", ByteCode_name);

    FILE* ByteCode_file = fopen(ByteCode_name, "w");

    size_t IP = 0;

    while (IP < buffer.nLines)
    {
        if (code_counter == nArgs_plus_commands)
        {
            printf(" BROKEN IN LINE %zu\n", IP);
            return;
        };

        int elements_read = 0;
        char command[20] = "";

        int arg = 0;
        int extra_arg = 0;
        char label[20] = "";

        elements_read = sscanf(buffer.line_ptr[IP],"%19s %19s %d", command, label, &extra_arg);

        if ( (arg = atoi (label)) == 0 && strcmp(label, "0") != 0)
            elements_read--;


        ASMcommands mode = DefineMode (command);


        if ((mode == WRONG_COMMAND && elements_read <= 0) || command[0] == ';')
            mode = SKIP_LINE; // пустые строки и комментарии

        if (command[0] == ':')
        {

            All_labels[number_of_labels].number = atoi(command + 1);
            All_labels[number_of_labels].address = (int) code_counter;
            if (atoi (command + 1) == 0 && strcmp (command + 1, "0") != 0)
                ASM_DUMP(WRONG_LABEL, IP);

            number_of_labels++;
            mode = SKIP_LINE;
        }

        switch (mode)
        {

        case INIT:

            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = INIT;
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

            array_for_code[code_counter] = PUSH;
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

            array_for_code[code_counter] = POP;
            code_counter++;

            ASM_VERIFY(POP, elements_read, IP);

            IP++;

            break;
        case MUL:
            ASM_error = ASM_CORRECT;

            array_for_code[code_counter] = MUL;
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
            array_for_code[code_counter] = EXIT;
            code_counter++; // поменял порядок!!!



            ASM_VERIFY(POP, elements_read, IP);
            IP++;
            //--------- DEBUG ---------
            for (size_t i = 0; i < number_of_labels; i++)
            {
                fprintf(stdout,"%d %d\n", All_labels[i].number, All_labels[i].address);
            }
            for (size_t i = 0; i < buffer.nLines; i++)
            {
                fprintf(stdout,"%s\n", buffer.line_ptr[i]);
            }
            // --------------
            if (nErrors == 0)
                VerifyLabels(buffer, array_for_code, code_counter);

            FillFile(array_for_code, code_counter, ByteCode_file);

            fclose(ByteCode_file);
            free(array_for_code);
            return;


            break;

        case ADD:
            array_for_code[code_counter] = ADD;
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
            PUSHR_POPR(array_for_code, &code_counter, label, IP);
            IP++;

            break;
        case POPR: // мб в особый кейс в верификаторе?
            array_for_code[code_counter] = POPR;
            code_counter++;
            PUSHR_POPR(array_for_code, &code_counter, label, IP);
            IP++;
            break;

        case JB:
            array_for_code[code_counter] = JB;
            JUMPS(array_for_code, &code_counter, IP, label);
            break;

        case JBE:
            array_for_code[code_counter] = JBE;
            JUMPS(array_for_code, &code_counter, IP, label);
            break;

        case JE:
            array_for_code[code_counter] = JE;
            JUMPS(array_for_code, &code_counter, IP, label);
            break;

        case JA:
            array_for_code[code_counter] = JA;
            JUMPS(array_for_code, &code_counter, IP, label);
            break;

        case CALL:
            array_for_code[code_counter] = CALL;
            JUMPS(array_for_code, &code_counter, IP, label);
            break;

        case RET:
            array_for_code[code_counter] = RET;
            code_counter++;
            //code_counter++;
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

        ASM_error = ASM_CORRECT;
        // IP++ только в самом конце?
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

    if (strcmp (command, "JB") == 0)
        return JB;

    if (strcmp (command, "JBE") == 0)
        return JBE;

    if (strcmp (command, "JE") == 0)
        return JE;

    if (strcmp (command, "JA") == 0)
        return JA;

    if (strcmp(command, "CALL") == 0)
        return CALL;

    if (strcmp(command, "RET") == 0)
        return RET;


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

void VerifyLabels (InputData buffer, int* array_for_code, size_t byte_code_counter) // 2-проход на поиск jump
{

    size_t code_counter = 0;
    for (size_t line_counter = 0; line_counter < buffer.nLines && code_counter <= byte_code_counter; line_counter++)
    {

        char command_line[20] = "";
        char arg_line[20] = "";

        int elements_read = sscanf(buffer.line_ptr[line_counter],"%19s %19s", command_line, arg_line);
        //printf("elements_read = %d\n" , elements_read);
        if (command_line[0] == 'J' || command_line[0] == 'C') // надежнее -- strcmp со всеми возможными jump + call
        {
            bool is_address_ok = false;

            int label_number = atoi(arg_line + 1);
            printf ("\n %s %s\n\n", command_line, arg_line);
            for (size_t counter = 0; counter < number_of_labels; counter++)
            {
                if (All_labels[counter].number == label_number)// наличие метки с нужным номером
                {
                    array_for_code[code_counter + 1] = All_labels[counter].address;
                        is_address_ok = true;
                }
                printf ("\n %s %d\n\n", command_line, All_labels[counter].address);
            }

            if (!is_address_ok)
                ASM_DUMP(WRONG_ADDRESS, line_counter);
        }

        if (command_line[0] != ':' && command_line[0] !=';'  && elements_read > 0) // проверка херня
            code_counter += (size_t) elements_read;

    }

    return;
}
