

#include "sw.h"

class SWOn : public SWAction
{
private:
    SWAction *cmd;

public:
    SWOn(SWAction *cmd);
    ~SWOn();

public:
    void Check();
    void On();
    void Off();
};
