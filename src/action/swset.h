

#include "sw.h"
#include "value.h"

class SWDataSet : public SWAction
{
protected:
    bool flag;
    float value;
    XP11Value *cmd;

public:
    SWDataSet(bool, const char *line);
    ~SWDataSet();

public:
    void Check();
    void On();
    void Off();
};
