
#include "swset.h"
#include "debug.h"
#include <stdio.h>
#include "value.h"
#include <regex>

SWDataSet::SWDataSet(const char *line)
{
    std::cmatch query;
    std::regex regex("(.+)\\:\\=(\\s+)?(\\-?\\d+(.\\d+)?)");
    if (std::regex_search(line, query, regex))
    {
        this->cmd = XP11Value::New(query[1].str().c_str());
        this->value = std::atof(query[3].str().c_str());
        return;
    }
    throw Exception("SET incorrect/unexpected line [%s]", line);
}

void SWDataSet::Check()
{
    this->cmd->Check();
}

SWDataSet::~SWDataSet()
{
    delete this->cmd;
}

void SWDataSet::On()
{
    this->cmd->SetValue(this->value);
}

void SWDataSet::Off()
{
    this->cmd->SetValue(this->value);
}
