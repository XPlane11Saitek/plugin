
#include "swload.h"

#include "swcmd.h"
#include "swdec.h"
#include "swpush.h"
#include "swrun.h"
#include "swset.h"
#include "debug.h"
#include <cstring>

SWAction *SWLoadAction(const char *classType, const char *line)
{
    if (!strcmp("INC/DEC", classType))
        return new SWDecIncValue(line);
    else if (!strcmp("CMD_ON", classType))
        return new SWCommand(true, line);
    else if (!strcmp("CMD_OFF", classType))
        return new SWCommand(false, line);
    else if (!strcmp("PUSH", classType))
        return new SWCommandPush(line);
    else if (!strcmp("SET_ON", classType))
        return new SWDataSet(true, line);
    else if (!strcmp("SET_OFF", classType))
        return new SWDataSet(false, line);
    else if (!strcmp("IF_ON", classType))
        return new SWRunIF(true, line);
    else if (!strcmp("IF_OFF", classType))
        return new SWRunIF(false, line);
    throw Exception("%s Action [%s] incorrect/unexpected [%s]", PLUGIN_ERROR, classType, line);
}