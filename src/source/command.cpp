
#include "command.h"
#include <cstring>
#include "debug.h"

XP11Command::XP11Command(const char *name)
{
#ifdef DEBUG
    debug("%s ATTACH [%s]", PLUGIN_DEBUG, name);
#endif
    strcpy(this->line, name);
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
