

#include "sw.h"
#include "command.h"

class SWCommand : public SWAction
{
private:
    XP11Command *cmd;

public:
    SWCommand(const char *line);
    ~SWCommand();

public:
    void Check();
    void On();
    void Off();
};
