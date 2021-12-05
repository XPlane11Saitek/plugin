
#include "swset.h"
#include "debug.h"
#include <stdio.h>
#include "sources.h"
#include <regex>

SWDataSet::SWDataSet(bool isOn, const char *line)
{
    this->flag = isOn;
    this->cmd = LoadValue(line);
    std::cmatch query;
    std::regex regex("\\:\\=(\\s+)?(\\-?\\d+(.\\d+)?)");
    // 0 := -20.01
    // 1
    // 2 -20.01
    // 3 .01
    if (std::regex_search(line, query, regex))
        this->value = std::atof(query[2].str().c_str());
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
    if (this->flag)
        this->cmd->SetValue(this->value);
}

void SWDataSet::Off()
{
    if (!this->flag)
        this->cmd->SetValue(this->value);
}
