
#include "content.h"
#include <cstring>
#include <stdlib.h>
#include "debug.h"

const char *FileContent::getParamDefault(const char *button, const char *key, const char *defaults)
{
    for (auto row : this->content)
        if ((!strcmp(button, row->button)) && (!strcmp(key, row->key)))
        {
            row->usage = true;
            return row->value;
        }
    return defaults;
}

bool FileContent::IsParam(const char *button, const char *key)
{
    return this->getParamDefault(button, key, NULL) != NULL;
}

const char *FileContent::GetParam(const char *button, const char *key)
{
    const char *value = this->getParamDefault(button, key, NULL);
    if (value != NULL)
        return value;
    throw Exception("%s %s Mode incorrect/unexpected NULL", button, key);
}

float FileContent::GetParamFloat(const char *button, const char *key)
{
    return (float)atof(this->GetParam(button, key));
}

std::list<FileContentLine *>::iterator FileContent::begin()
{
    return this->content.begin();
};

std::list<FileContentLine *>::iterator FileContent::end()
{
    return this->content.end();
};

FileContent *FileContent::CreateConfigForPanel(const char *pname, int number)
{
    FileContent *res = new FileContent();
    for (auto row : this->content)
        if (!strcmp(row->panelName, pname))
            if ((row->panelNumber == -1) || (row->panelNumber == number))
                res->content.insert(res->content.begin(), 1, row);
    return res;
}

FileContent *FileContent::CreateConfigForButton(const char *button)
{
    FileContent *res = new FileContent();
    for (auto row : this->content)
        if (!strcmp(row->button, button))
            res->content.insert(res->content.begin(), 1, row);
    return res;
}

void FileContent::CheckALLUsage()
{
    for (auto row : this->content)
        if (!row->usage)
            warning("%s Load not use in %s:%i [%s]", PLUGIN_WARNING, row->filename, row->lineNumber, row->line);
}
