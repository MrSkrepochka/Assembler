#include "Parser.h"


int main()
{
    struct stat ASM_file;

    fprintf(stdout, "Enter your assembler code file name (.asm)\n");
    fscanf(stdin, "%49s", ASM_file_name);

    InputData buffer = {NULL, NULL, 0, 0, 0};
    
    if (stat(ASM_file_name, &ASM_file) != 0)
    {
        return 0;
    }
    buffer.descriptor = open (ASM_file_name, O_RDONLY);
    buffer.size = (size_t) ASM_file.st_size;

    ReadInput(&buffer);

    TranslateCode(buffer);

    if (nErrors > 0)
        fprintf(stdout, "SUKA, FIX %d ERRORS\n", nErrors);
    free(buffer.contents);
    free(buffer.line_ptr);
    close(buffer.descriptor);
    return 0;
}
