

#include "sw.h"

class SWOff : public SWAction
{
private:
    SWAction *cmd;

public:
    SWOff(SWAction *cmd);
    ~SWOff();

public:
    void Check();
    void On();
    void Off();
};
