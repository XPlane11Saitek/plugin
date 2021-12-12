
#include "value.h"

class XP11Constant : public XP11Value
{
protected:
    int content;

public:
    XP11Constant(const char *);
    ~XP11Constant();

public:
    float GetValue();
    void SetValue(float);
    virtual void Check();
};
