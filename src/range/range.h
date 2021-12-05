

#ifndef XPLANERANGE
#define XPLANERANGE
class XPlaneRange
{
public:
    virtual ~XPlaneRange();

public:
    virtual void Check();
    virtual bool IsValueInRange();
};
#endif
