
#include "rangeLoader.h"
#include "value.h"
#include "rangeOr.h"
#include "rangeAnd.h"
#include "rangeValue.h"
#include "line.h"
#include "debug.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <regex>

XPlaneRange *LoadSingleRange(const char *line)
{
    std::cmatch query;
    std::regex regex("(.+)\\{(\\-?\\d+(\\.\\d+)?)\\:(\\-?\\d+(\\.\\d+)?)\\}");

    if (std::regex_match(line, query, regex))
    {
        XP11Value *value = XP11Value::New(query[1].str().c_str());
        return new XPRangeValue(value,
                                std::atof(query[2].str().c_str()),
                                std::atof(query[4].str().c_str()));
    }
    throw Exception("LoadRange incorrect/unexpected incorrect range [%s]", line);
}

XPlaneRange *LoadRange(const char *line)
{
    // TODO REWRITE TO REGEXP
    SplitLine *obj = new SplitLine(line);
    if (*obj)
    {
        XPlaneRange *leftObj = LoadRange(obj->GetLine(0));
        XPlaneRange *rightObj = LoadRange(obj->GetLine(2));
        char *mode = obj->GetLine(1);
        if (!strcmp("OR", mode))
        {
            delete obj;
            return new XPRangeOR(leftObj, rightObj);
        }
        else if (!strcmp("AND", mode))
        {
            delete obj;
            return new XPRangeAND(leftObj, rightObj);
        }
        throw Exception("LoadRange incorrect/unexpected line/mode [%s][%s]", line, mode);
    }
    delete obj;
    return LoadSingleRange(line);
}