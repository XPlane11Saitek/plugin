#ifndef CUSTOMREFFILE
#define CUSTOMREFFILE

#ifdef XPLANE11PLUGIN
#include "XPLMDataAccess.h"
#endif

#include "plugin.h"

class CustomRef
{
protected:
    char cmdName[STR_DATAREF_SIZE];
    int state;
#ifdef XPLANE11PLUGIN
    XPLMDataRef cmd;
#endif

public:
    static int getXP11State(void *);

public:
    int GetState();
    void SetState(int);

public:
    CustomRef(const char *, int, const char *);
    ~CustomRef();
};

#endif
