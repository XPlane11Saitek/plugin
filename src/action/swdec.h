

#include "sw.h"
#include "value.h"

class SWDecIncValue : public SWAction
{
protected:
    XP11Value *cmd;
    float value, maxValue, minValue;

public:
    SWDecIncValue(const char *line);
    ~SWDecIncValue();

public:
    void Check();
    void On();
    void Off();
};
