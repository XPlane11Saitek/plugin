#ifndef CMDPROTO
#define CMDPROTO

#include <list>

class SWAction
{
public:
    virtual ~SWAction();
    static SWAction *New(const char *, const char *);
    static SWAction *New(const char *);

public:
    virtual void Check();
    virtual void On();
    virtual void Off();
};

typedef std::list<SWAction *> Actions;

#endif
