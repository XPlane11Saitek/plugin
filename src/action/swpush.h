#include "sw.h"
#include "command.h"

class SWCommandPush : public SWAction
{
private:
    XP11Command *cmd;

public:
    SWCommandPush(const char *line);
    ~SWCommandPush();

public:
    void Check();
    void On();
    void Off();
};
