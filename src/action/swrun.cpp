#include "swrun.h"
#include "rangeLoader.h"

#include "debug.h"
#include <iostream>
#include <regex>

SWRunIF::SWRunIF(const char *line)
{
    std::cmatch query;
    std::regex regex("(.+)(\\s+)?\\?(\\s+)?(.+)");
    if (std::regex_search(line, query, regex))
    {
        this->cmd = SWAction::New(query[1].str().c_str());
        this->value = LoadRange(query[4].str().c_str());
        return;
    }
    throw Exception("%s RUNIF incorrect/unexpected line [%s]", PLUGIN_ERROR, line);
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
    if (this->value->IsValueInRange())
        this->cmd->On();
}

void SWRunIF::Off()
{
    if (this->value->IsValueInRange())
        this->cmd->Off();
}
