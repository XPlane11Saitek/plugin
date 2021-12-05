

#include "monitor.h"
#include "value.h"

#ifndef RADIOSELECTERFILE
#define RADIOSELECTERFILE
class RadioMode
{
public:
    virtual ~RadioMode();
    virtual void Check();
    virtual void Show(Monitor *[2]);
    virtual void Activated();

public:
    virtual void Push();
    virtual void Release();
    virtual void BigUp();
    virtual void BigDown();
    virtual void SmallUp();
    virtual void SmallDown();
};
#endif
