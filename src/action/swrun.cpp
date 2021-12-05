#include "swrun.h"
#include "rangeLoader.h"
#include "debug.h"
#include <iostream>
#include <string.h>

SWRunIF::SWRunIF(bool isOnFlag, const char *line)
{
    // TODO REVIEW BUG NUMBER
    this->flag = isOnFlag;
    if (sscanf(line, "RUN %s IF ", this->cmdName))
    {
        this->cmd = new XP11Command(this->cmdName);
        size_t pos = 3 + 1 + strlen(this->cmdName) + 1 + 2 + 1;
        const char *valueName = &line[pos];
        this->value = LoadRange(valueName);
        return;
    }
    throw Exception("%s SWRunIF incorrect/unexpected line [%s]", PLUGIN_ERROR, line);
}

SWRunIF::~SWRunIF()
{
    delete this->cmd;
    delete this->value;
}

void SWRunIF::Check()
{
    this->cmd->Check();
    this->value->Check();
}

void SWRunIF::On()
{
    if (this->flag && this->value->IsValueInRange())
        this->cmd->Once();
}

void SWRunIF::Off()
{
    if (!this->flag && this->value->IsValueInRange())
        this->cmd->Once();
}
