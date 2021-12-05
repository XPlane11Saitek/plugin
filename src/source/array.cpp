
#include "array.h"
#include "debug.h"
#include <cstring>
#include <regex>

XP11ArrayValue::XP11ArrayValue(const char *name, int num)
{
    this->item = num;
    strcpy(this->line, name);
#ifdef XPLANE11PLUGIN
    this->command = NULL;
#else
    std::regex regex("(sim|laminar|plugin)\\/(\\w\\/?)+");
    if (!std::regex_match(name, regex))
        throw Exception("%s DEBUG incorrect/unexpected name [%s]",
                        PLUGIN_ERROR, name);
#endif
}

XP11ArrayValue::~XP11ArrayValue() {}

void XP11ArrayValue::Check()
{
#ifdef XPLANE11PLUGIN
    this->command = XPLMFindDataRef(this->line);
    if (this->command == NULL)
        throw Exception("%s XP11ArrayValue::Check/XPLMFindDataRef incorrect/unexpected NULL or not found [%s]", PLUGIN_ERROR, line);
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
    throw Exception("%s XP11ArrayValue::GetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#else
    return 0;
#endif
}

void XP11ArrayValue::SetValue(float newValue)
{
#ifdef DEBUG
    debug("%s SET [%s][%f]", PLUGIN_DEBUG, this->line, newValue);
#endif
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
    throw Exception("%s XP11ArrayValue::SetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#endif
}
