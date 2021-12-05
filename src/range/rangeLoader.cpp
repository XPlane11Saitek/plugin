
#include "rangeLoader.h"
#include "sources.h"
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
    XP11Value *value = LoadValue(line);
    std::cmatch query;
    std::regex regex("\\{(\\-?\\d+(.\\d+)?)\\:(\\-?\\d+(.\\d+)?)\\}");
    // 0 {-11.01:50}
    // 1 -11.01
    // 2 .01
    // 3 50
    // 4

    if (std::regex_search(line, query, regex))
        return new XPRangeValue(value,
                                std::atof(query[1].str().c_str()),
                                std::atof(query[3].str().c_str()));
    else
        throw Exception("%s LoadRange incorrect/unexpected incorrect range [%s]", PLUGIN_ERROR, line);
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
        throw Exception("%s LoadRange incorrect/unexpected line/mode [%s][%s]", PLUGIN_ERROR, line, mode);
    }
    delete obj;
    return LoadSingleRange(line);
}