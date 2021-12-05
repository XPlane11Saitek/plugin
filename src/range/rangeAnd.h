
#include "range.h"

class XPRangeAND : public XPlaneRange
{
private:
    XPlaneRange *left;
    XPlaneRange *right;

public:
    XPRangeAND(XPlaneRange *, XPlaneRange *);
    ~XPRangeAND();

public:
    void Check();
    bool IsValueInRange();
};
