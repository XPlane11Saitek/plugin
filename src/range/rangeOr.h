
#include "range.h"

class XPRangeOR : public XPlaneRange
{
private:
    XPlaneRange *left;
    XPlaneRange *right;

public:
    XPRangeOR(XPlaneRange *, XPlaneRange *);
    ~XPRangeOR();

public:
    void Check();
    bool IsValueInRange();
};
