#include "sw.h"
#include "command.h"
#include "range.h"

class SWRunIF : public SWAction
{
public:
    SWRunIF(const char *);
    ~SWRunIF();

protected:
    SWAction *cmd;
    XPlaneRange *value;

public:
    void Check();
    void On();
    void Off();
};