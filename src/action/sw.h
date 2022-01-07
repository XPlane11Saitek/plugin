#ifndef CMDPROTO
#define CMDPROTO

#include <list>

class SWAction
{
public:
    static SWAction *New(const char *, const char *);
    static SWAction *New(const char *);

public:
    virtual ~SWAction(){};
    virtual void Check(){};
    virtual void On(){};
    virtual void Off(){};
};

typedef std::list<SWAction *> Actions;

#endif
