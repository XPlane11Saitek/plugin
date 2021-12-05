
#include "swdec.h"
#include <stdio.h>
#include <regex>
#include "debug.h"
#include "sources.h"

SWDecIncValue::SWDecIncValue(const char *line)
{
    this->cmd = LoadValue(line);
    std::cmatch query;
    std::regex regex("\\{(\\-?\\d+(.\\d+)?)\\:(\\-?\\d+(.\\d+)?)\\}\\/(\\-?\\d+(.\\d+)?)");
    // 0 {-2.50:2.5}/-0.01
    // 1 -2.50
    // 2 .50
    // 3 2.5
    // 4 .5
    // 5 -0.01
    // 6 .0
    if (std::regex_search(line, query, regex))
    {
        minValue = std::atof(query[1].str().c_str());
        maxValue = std::atof(query[3].str().c_str());
        value = std::atof(query[5].str().c_str());
    }
    else
        throw Exception("%s SWDecIncValue incorrect/unexpected line [%s]", PLUGIN_ERROR, line);
}

SWDecIncValue::~SWDecIncValue()
{
    delete this->cmd;
}

void SWDecIncValue::Check()
{
    this->cmd->Check();
}

void SWDecIncValue::On()
{
    float state = this->cmd->GetValue() + this->value;
    if (this->value < this->maxValue)
        this->cmd->SetValue(state);
}

void SWDecIncValue::Off()
{
    float state = this->cmd->GetValue() - this->value;
    if (this->value > this->minValue)
        this->cmd->SetValue(state);
}
