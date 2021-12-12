
#include "swdec.h"
#include <stdio.h>
#include <regex>
#include "debug.h"
#include "value.h"

SWDecIncValue::SWDecIncValue(const char *line)
{
    std::cmatch query;
    std::regex regex("(.+)\\{(\\-?\\d+(.\\d+)?)\\:(\\-?\\d+(.\\d+)?)\\}\\/(\\-?\\d+(.\\d+)?)");
    if (std::regex_search(line, query, regex))
    {
        this->cmd = XP11Value::New(query[1].str().c_str());
        minValue = std::atof(query[2].str().c_str());
        maxValue = std::atof(query[4].str().c_str());
        value = std::atof(query[6].str().c_str());
        return;
    }
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
