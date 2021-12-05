#include "monitor.h"
#include "range.h"
#include "spec.h"
#include <ctime>
#include "sw.h"

#ifndef APFILE
#define APFILE

class AP
{
public:
    virtual ~AP();

public:
    virtual void Check();
    virtual void Activate();
    virtual void Show(Monitor *[2], unsigned char &);

public: // Method
    virtual void ButtonPush(int);
    virtual void ButtonRelease(int);
    virtual void RotateUp();
    virtual void RotateDown();
};
#endif