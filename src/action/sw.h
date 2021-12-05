#ifndef CMDPROTO
#define CMDPROTO

#include <list>

class SWAction
{
public:
    virtual ~SWAction();

public:
    virtual void Check();
    virtual void On();
    virtual void Off();
};

typedef std::list<SWAction *> Actions;

#endif
