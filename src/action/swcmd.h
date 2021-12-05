

#include "sw.h"
#include "command.h"

class SWCommand : public SWAction
{
private:
    bool flag;
    XP11Command *cmd;

public:
    SWCommand(bool, const char *line);
    ~SWCommand();

public:
    void Check();
    void On();
    void Off();
};
