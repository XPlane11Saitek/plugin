
#include "debug.h"
#include "const.h"
#include <regex>

XP11Constant::XP11Constant(const char *data)
{
    debug("Const attach [%s]", data);
    std::regex regex("\\-?\\d+(\\.\\d+)?");
    if (std::regex_match(data, regex))
    {
        this->content = std::atof(data);
        return;
    }
    throw Exception("Const incorrect/unexpected [%s]", data);
}

XP11Constant::~XP11Constant() {}

float XP11Constant::GetValue()
{
    return this->content;
}

void XP11Constant::SetValue(float newValue)
{
    debug("Ignore [%f]", newValue);
}

void XP11Constant::Check() {}
