
#include "range.h"
#include "value.h"

class XPRangeValue : public XPlaneRange
{
private:
    XP11Value *content;
    float fromValue;
    float toValue;

public:
    XPRangeValue(XP11Value *, float, float);
    ~XPRangeValue();

public:
    void Check();
    bool IsValueInRange();
};
