

#ifndef RADIOSELECTERFILE
#define RADIOSELECTERFILE

#include "monitor.h"
#include "value.h"
#include "mode.h"
#include "content.h"

class RadioMode
{
public:
    static RadioMode *New(FileContent *, const char *);

public:
    virtual ~RadioMode(){};
    virtual void Check(){};
    virtual void Show(Monitor *[2]){};
    virtual void Activated(){};
    virtual void Push(){};
    virtual void Release(){};
    virtual void BigUp(){};
    virtual void BigDown(){};
    virtual void SmallUp(){};
    virtual void SmallDown(){};
};
#endif
