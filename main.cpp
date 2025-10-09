#include "ByteCodeCreator.h"


int main()
{
    struct stat ASM_file;

    InputData buffer = {NULL, NULL, 0, 0, 0};
    if (stat("ASM.txt", &ASM_file) != 0)
    {
        return 0;
    }
    buffer.descriptor = open ("ASM.txt", O_RDONLY);
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
