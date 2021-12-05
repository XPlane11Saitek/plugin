
#include "sources.h"
#include "debug.h"
#include <iostream>
#include <cstring>
#include <regex>
#include "array.h"
#include "dataref.h"
#include "const.h"

XP11Value *LoadValue(const char *line)
{
    std::cmatch query;
    std::regex regex("(\\w+)\\(((\\w+\\/?)+)(\\[(\\d+)\\])?\\)");
    //  0 array(sim/plugin0/demo[0])
    //  1 array
    //  2 sim/plugin0/demo
    //  3 demo
    //  4 [0]
    //  5 0

    if (std::regex_search(line, query, regex))
        if (!strcmp(query[1].str().c_str(), "array"))
            if (!strcmp(query[5].str().c_str(), ""))
                throw Exception("%s LoadValue incorrect/unexpected index [%s]", PLUGIN_ERROR, line);
            else
                return new XP11ArrayValue(query[2].str().c_str(), std::stoi(query[5].str().c_str()));
        else if (!strcmp(query[1].str().c_str(), "dataref"))
            return new XP11DataRef(query[2].str().c_str());
        else if (!strcmp(query[1].str().c_str(), "const"))
            return new XP11Constant(std::stoi(query[2].str().c_str()));
        else
            throw Exception("%s LoadValue incorrect/unexpected value [%s]in[%s]", PLUGIN_ERROR, line, query[1].str().c_str());
    else
        throw Exception("%s LoadValue incorrect/unexpected line [%s]", PLUGIN_ERROR, line);
}
