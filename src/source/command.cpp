
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
#ifdef DEBUG
    debug("%s XP11Command attach [%s]", PLUGIN_DEBUG, name);
#endif
#ifdef XPLANE11PLUGIN
    this->cmd = NULL;
#endif
    std::regex regex("(sim|laminar|plugin)\\/(\\w\\/?)+");
    if (std::regex_match(name, regex))
    {
#ifndef XPLANE11PLUGIN
        FindInFile("Commands.txt", name);
#endif
        strcpy(this->line, name);
        return;
    }
    throw Exception("%s XP11Command incorrect/unexpected [%s]", PLUGIN_ERROR, name);
}

void XP11Command::Check()
{
#ifdef XPLANE11PLUGIN
    this->cmd = XPLMFindCommand(this->line);
    if (this->cmd == NULL)
        throw Exception("%s XP11Command::Check incorrect/unexpected XPLMFindCommand=NULL [%s]",
                        PLUGIN_ERROR, line);
#endif
}

void XP11Command::Once()
{
#ifdef DEBUG
    debug("%s RUN [%s]", PLUGIN_DEBUG, this->line);
#endif
#ifdef XPLANE11PLUGIN
    XPLMCommandOnce(this->cmd);
#endif
}

void XP11Command::Begin()
{
#ifdef DEBUG
    debug("%s PUSH [%s]", PLUGIN_DEBUG, this->line);
#endif
#ifdef XPLANE11PLUGIN
    XPLMCommandBegin(this->cmd);
#endif
}

void XP11Command::End()
{
#ifdef DEBUG
    debug("%s RELEASE [%s]", PLUGIN_DEBUG, this->line);
#endif
#ifdef XPLANE11PLUGIN
    XPLMCommandEnd(this->cmd);
#endif
}
