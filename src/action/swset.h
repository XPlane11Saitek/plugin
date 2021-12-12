

#include "sw.h"
#include "value.h"

class SWDataSet : public SWAction
{
protected:
    float value;
    XP11Value *cmd;

public:
    SWDataSet(const char *line);
    ~SWDataSet();

public:
    void Check();
    void On();
    void Off();
};
