

#ifndef XPLANERANGE
#define XPLANERANGE
class XPlaneRange
{
public:
    virtual ~XPlaneRange(){};
    virtual void Check(){};
    virtual bool IsValueInRange();
};
#endif
