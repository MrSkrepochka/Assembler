#include "InputReader.h"

size_t nArgs_plus_commands = 0;

size_t CountLines (char* poem)
{
    size_t nLines = 0;
    char* endOfLine = poem;
    char* space = poem;
    while (true)
    {
        space = strchr (endOfLine, ' ');
        if ( ( endOfLine = strchr ( endOfLine, '\n' ) ) != NULL)
        {
            if (space != NULL &&  space < endOfLine)
                nArgs_plus_commands++;
            nLines++;
            endOfLine++;
            continue;
        }
        break;
    }
    return nLines;
}

void ReadInput (InputData* buffer)
{
    buffer -> contents = (char*) calloc (buffer -> size +1, sizeof(char));
    read(buffer -> descriptor, buffer ->contents, buffer -> size);
    buffer -> contents [buffer -> size] = '\0';

    buffer -> nLines = CountLines(buffer -> contents);
    buffer -> line_ptr = (char**) calloc (buffer -> nLines, sizeof(char*));

    nArgs_plus_commands += buffer ->nLines; // в глобальную константу для использования записи первым элементом в файл с байткодом

    buffer -> line_ptr[0] = buffer -> contents;

    DivideInput(buffer);


}

void DivideInput (InputData* buffer)
{
    char* beginningOfLine = buffer -> contents;
    for (size_t linesRead = 1; linesRead < buffer -> nLines; linesRead++)
    {
        if ( ( beginningOfLine = strchr ( beginningOfLine, '\n' ) ) != NULL)
        {
            *beginningOfLine = '\0';
            beginningOfLine++;
            buffer -> line_ptr[linesRead] = beginningOfLine;
            continue;
        }
        break;

    }
}

