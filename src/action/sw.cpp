#include "sw.h"
#include "swcmd.h"
#include "swdec.h"
#include "swpush.h"
#include "swrun.h"
#include "swset.h"
#include "swon.h"
#include "swoff.h"

#include "debug.h"

#include <cstring>
#include <regex>
#include <iostream>

SWAction *SWAction::New(const char *param, const char *line)
{
    if (!strcmp("ON", param))
        return new SWOn(SWAction::New(line));
    if (!strcmp("OFF", param))
        return new SWOff(SWAction::New(line));
    if (!strcmp("CMD", param))
        return SWAction::New(line);
    throw Exception("Action [%s] incorrect/unexpected [%s]", param, line);
}

SWAction *SWAction::New(const char *line)
{
    std::cmatch query;
    std::regex regex("(\\w+)\\((.+)\\)");

    if (std::regex_match(line, query, regex))
    {
        if (!strcmp(query[1].str().c_str(), "command"))
            return new SWCommand(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "push"))
            return new SWCommandPush(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "inc"))
            return new SWDecIncValue(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "set"))
            return new SWDataSet(query[2].str().c_str());
        if (!strcmp(query[1].str().c_str(), "on"))
            return new SWOn(SWAction::New(query[2].str().c_str()));
        if (!strcmp(query[1].str().c_str(), "off"))
            return new SWOff(SWAction::New(query[2].str().c_str()));
        if (!strcmp(query[1].str().c_str(), "runif"))
            return new SWRunIF(query[2].str().c_str());
        throw Exception("Action incorrect/unexpected value [%s]in[%s]", line, query[1].str().c_str());
    };
    throw Exception("Action incorrect/unexpected [%s]", line);
}