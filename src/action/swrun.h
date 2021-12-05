#include "sw.h"
#include "command.h"
#include "range.h"

class SWRunIF : public SWAction
{
public:
    SWRunIF(bool, const char *);
    ~SWRunIF();

protected:
    char cmdName[512];
    bool flag;
    XP11Command *cmd;
    XPlaneRange *value;

public:
    void Check();
    void On();
    void Off();
};