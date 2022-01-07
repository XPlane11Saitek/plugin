
#include "command.h"
#include "debug.h"

#include <cstring>
#include <regex>
#include <iostream>

#ifndef XPLANE11PLUGIN
#include "main.h"
#endif

XP11Command::XP11Command(const char *name)
{
    debug("XP11Command attach [%s]", name);
#ifdef XPLANE11PLUGIN
    this->cmd = NULL;
#endif
    std::regex regex("(sim|laminar|plugin)\\/(\\w\\/?)+");
    if (std::regex_match(name, regex))
    {
#ifndef XPLANE11PLUGIN
        FindInFile(&SupportCommandList, name);
#endif
        strncpy(this->line, name, STR_DATAREF_SIZE);
        return;
    }
    throw Exception("XP11Command incorrect/unexpected [%s]", name);
}

void XP11Command::Check()
{
#ifdef XPLANE11PLUGIN
    this->cmd = XPLMFindCommand(this->line);
    if (this->cmd == NULL)
        throw Exception("XP11Command::Check incorrect/unexpected XPLMFindCommand=NULL [%s]",
                        PLUGIN_ERROR, line);
#endif
}

void XP11Command::Once()
{
    debug("RUN [%s]", this->line);
#ifdef XPLANE11PLUGIN
    XPLMCommandOnce(this->cmd);
#endif
}

void XP11Command::Begin()
{
    debug("PUSH [%s]", this->line);
#ifdef XPLANE11PLUGIN
    XPLMCommandBegin(this->cmd);
#endif
}

void XP11Command::End()
{
    debug("RELEASE [%s]", this->line);
#ifdef XPLANE11PLUGIN
    XPLMCommandEnd(this->cmd);
#endif
}
