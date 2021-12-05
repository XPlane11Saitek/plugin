
#include "dataref.h"
#include "debug.h"
#include <cstring>
#include <regex>

XP11DataRef::XP11DataRef(const char *name)
{
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

void XP11DataRef::Check()
{
#ifdef XPLANE11PLUGIN
    this->command = XPLMFindDataRef(this->line);
    if (this->command == NULL)
        throw Exception("%s XP11DataRef::Check/XPLMFindDataRef incorrect/unexpected NULL or not found [%s]", PLUGIN_ERROR, line);
    this->commandType = XPLMGetDataRefTypes(this->command);
#endif
    this->GetValue();
}

XP11DataRef::~XP11DataRef() {}

float XP11DataRef::GetValue()
{
#ifdef XPLANE11PLUGIN
    switch (this->commandType)
    {
    case xplmType_Int:
    {
        return (float)XPLMGetDatai(this->command);
    }
    break;
    case xplmType_Int + xplmType_Float:
    case xplmType_Int + xplmType_Float + xplmType_Double:
    case xplmType_Float:
    {
        return XPLMGetDataf(this->command);
    }
    break;
    }
    throw Exception("%s XP11DataRef::GetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#else
    return 0;
#endif
}

void XP11DataRef::SetValue(float newValue)
{
#ifdef DEBUG
    debug("%s SET [%s][%f]", PLUGIN_DEBUG, this->line, newValue);
#endif
#ifdef XPLANE11PLUGIN
    switch (this->commandType)
    {
    case xplmType_Int:
    {
        int value = (int)newValue;
        XPLMSetDatai(this->command, value);
        return;
    }
    break;
    case xplmType_Float:
    {
        XPLMSetDataf(this->command, newValue);
        return;
    }
    break;
    }
    throw Exception("%s XP11DataRef::SetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#endif
}
