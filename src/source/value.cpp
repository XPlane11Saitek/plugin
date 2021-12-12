
#include "debug.h"
#include "value.h"

#include <cstring>
#include <regex>

#include "array.h"
#include "dataref.h"
#include "const.h"

XP11Value::~XP11Value() {}

float XP11Value::GetValue()
{
    throw Exception("%s DEVELOPER ERROR", PLUGIN_ERROR);
}

void XP11Value::SetValue(float) {}

void XP11Value::Check() {}

XP11Value *XP11Value::New(const char *line)
{
    std::cmatch query;
    std::regex regex("(\\w+)\\((.+)\\)");

    if (std::regex_match(line, query, regex))
    {
        if (!strcmp(query[1].str().c_str(), "dataref"))
            return new XP11DataRef(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "const"))
            return new XP11Constant(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "array"))
            return new XP11ArrayValue(query[2].str().c_str());
        throw Exception("%s XP11Value incorrect/unexpected value [%s]in[%s]", PLUGIN_ERROR, line, query[1].str().c_str());
    };
    throw Exception("%s XP11Value incorrect/unexpected value [%s]", PLUGIN_ERROR, line);
}
