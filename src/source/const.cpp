
#include "debug.h"
#include "const.h"
#include <regex>

XP11Constant::XP11Constant(const char *data)
{
#ifdef DEBUG
    debug("%s Const attach [%s]", PLUGIN_DEBUG, data);
#endif
    std::regex regex("\\-?\\d+(\\.\\d+)?");
    if (std::regex_match(data, regex))
    {
        this->content = std::atof(data);
        return;
    }
    throw Exception("%s Const incorrect/unexpected [%s]", PLUGIN_ERROR, data);
}

XP11Constant::~XP11Constant() {}

float XP11Constant::GetValue()
{
    return this->content;
}

void XP11Constant::SetValue(float newValue)
{
#ifdef DEBUG
    debug("%s Ignore [%f]", PLUGIN_DEBUG, newValue);
#else
    (void)newValue;
#endif
}

void XP11Constant::Check() {}
