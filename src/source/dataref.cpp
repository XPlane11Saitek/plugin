
#include "dataref.h"
#include "debug.h"
#include <cstring>
#include <regex>

#ifndef XPLANE11PLUGIN
#include "main.h"
#endif

XP11DataRef::XP11DataRef(const char *name)
{
    debug("DataRef attach [%s]", name);
#ifdef XPLANE11PLUGIN
    this->command = NULL;
#endif
    std::regex regex("(\\w+)\\/(\\w\\/?)+");
    if (std::regex_match(name, regex))
    {
#ifndef XPLANE11PLUGIN
        FindInFile(&SupportDatarefList, name);
#endif
        strncpy(this->line, name, STR_DATAREF_SIZE);
        return;
    }
    throw Exception("XP11DataRef incorrect/unexpected [%s]", name);
}

void XP11DataRef::Check()
{
#ifdef XPLANE11PLUGIN
    this->command = XPLMFindDataRef(this->line);
    if (this->command == NULL)
        throw Exception("XP11DataRef::Check/XPLMFindDataRef incorrect/unexpected NULL or not found [%s]", line);
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
    throw Exception("XP11DataRef::GetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#else
    return 0;
#endif
}

void XP11DataRef::SetValue(float newValue)
{
    info("SET [%s][%f]", this->line, newValue);
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
    throw Exception("XP11DataRef::SetValue incorrect/unexpected xplmType [%s][%i]",
                    PLUGIN_ERROR, line, this->commandType);
#endif
}
