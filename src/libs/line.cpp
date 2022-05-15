#include <cstring>
#include "line.h"
#include <stdexcept>
#include "debug.h"

// TODO HIGH REMOVE THIS CODE

SplitLine::SplitLine(const char *line)
{
    // save
    strcpy(this->content, line);
    // Load
    int level = 0;
    for (int pos = 0; this->content[pos] != '\0'; pos++)
    {
        if (this->content[pos] == '(')
        {
            if (level++ == 0)
            {
                if (this->mode <= 2)
                    this->block[mode++] = pos;
                else
                    throw std::overflow_error("Too many block ( and )");
            }
        }
        else if (this->content[pos] == ')')
        {
            if (--level < 0)
                throw std::overflow_error("Increct use symbol ( and )");
            else if (level == 0)
                this->block[mode++] = pos;
        }
    }
}

char *SplitLine::GetLine(int code)
{
    int pos = 0;
    char *line = this->item[code];
    for (int step = this->block[code] + 1; step < this->block[code + 1]; step++)
        line[pos++] = this->content[step];
    while ((pos > 0) && (line[pos - 1] == ' '))
        pos--;
    line[pos] = '\0';
    while (line[0] == ' ')
        line = &line[1];
    return line;
}
