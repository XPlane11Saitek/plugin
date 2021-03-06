#ifndef DATAREFCUSTOMFILE
#define DATAREFCUSTOMFILE

#ifdef XPLANE11PLUGIN
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#endif

#include "plugin.h"

class CustomWrite
{
private:
    char cmdName[STR_DATAREF_SIZE];
#ifdef XPLANE11PLUGIN
    XPLMDataRef cmd;
#endif

private:
    int state;
    int new_state;

public:
    static void setXP11Cache(void *, int);
    static int getXP11State(void *);
    int GetState();
    int GetNewState();
    void SetState(int);
    void SetNewState(int);

public:
    CustomWrite(const char *, int, int);
    ~CustomWrite();
};
#endif
