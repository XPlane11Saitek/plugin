
#include "array.h"
#include "debug.h"

#include <cstring>
#include <regex>
#include <iostream>

#ifndef XPLANE11PLUGIN
#include "main.h"
#endif

XP11ArrayValue::XP11ArrayValue(const char *line)
{
    debug("XP11Array attach [%s]", line);
#ifdef XPLANE11PLUGIN
    this->command = NULL;
#endif
    std::cmatch query;
    std::regex regex("((\\w+)\\/(\\w\\/?)+)\\[(\\d+)\\]");
    if (std::regex_match(line, query, regex))
    {
#ifndef XPLANE11PLUGIN
        FindInFile(&SupportDatarefList, query[1].str().c_str());
#endif
        this->item = std::atof(query[4].str().c_str());
        strncpy(this->line, query[1].str().c_str(), STR_DATAREF_SIZE);
        return;
    }
    throw Exception("XP11Array attach incorrect name [%s]", line);
}

XP11ArrayValue::~XP11ArrayValue() {}

void XP11ArrayValue::Check()
{
#ifdef XPLANE11PLUGIN
    this->command = XPLMFindDataRef(this->line);
    if (this->command == NULL)
        throw Exception("XP11ArrayValue::Check/XPLMFindDataRef incorrect/unexpected NULL or not found [%s]", line);
    this->commandType = XPLMGetDataRefTypes(this->command);
#endif
    this->GetValue();
}

float XP11ArrayValue::GetValue()
{
#ifdef XPLANE11PLUGIN
    switch (this->commandType)
    {
    case xplmType_IntArray:
    {
        int datai = 0;
        XPLMGetDatavi(this->command, &datai, this->item, 1);
        return (float)datai;
    }
    break;
    case xplmType_Unknown:
    case xplmType_FloatArray:
    {
        float dataf = 0;
        XPLMGetDatavf(this->command, &dataf, this->item, 1);
        return dataf;
    }
    break;
    }
    throw Exception("XP11ArrayValue::GetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#else
    return 0;
#endif
}

void XP11ArrayValue::SetValue(float newValue)
{
    debug("SET [%s][%f]", this->line, newValue);
#ifdef XPLANE11PLUGIN
    switch (this->commandType)
    {
    case xplmType_IntArray:
    {
        int value = (int)newValue;
        XPLMSetDatavi(this->command, &value, this->item, 1);
        return;
    }
    break;
    case xplmType_FloatArray + xplmType_IntArray:
    case xplmType_FloatArray:
    {
        XPLMSetDatavf(this->command, &newValue, this->item, 1);
        return;
    }
    break;
    }
    throw Exception("XP11ArrayValue::SetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#endif
}
