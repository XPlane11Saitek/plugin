#ifndef XP11COMMANDFILE
#define XP11COMMANDFILE

#ifdef XPLANE11PLUGIN
#include "XPLMUtilities.h"
#endif

class XP11Command
{
private:
    char line[512];
#ifdef XPLANE11PLUGIN
    XPLMCommandRef cmd;
#endif

public:
    void Check();
    void Once();
    void Begin();
    void End();

public:
    XP11Command(const char *);
};
#endif
