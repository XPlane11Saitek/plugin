
#ifndef APFILE
#define APFILE

#include "monitor.h"
#include "range.h"
#include "spec.h"
#include <ctime>
#include "sw.h"
#include "content.h"
#include "apCaption.h"

class AP
{
protected:
    char name[STR_CAPTION_SIZE] = {0};
    char ledName[8][STR_CAPTION_SIZE] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

public:
    virtual ~AP();
    static AP *New(FileContent *, const char *);

public:
    virtual void Check();
    virtual void Activate(apCaption *);
    virtual void Show(Monitor *[2], unsigned char &);

public: // Method
    virtual void ButtonPush(int);
    virtual void ButtonRelease(int);
    virtual void RotateUp();
    virtual void RotateDown();

public:
    void SetName(const char *);
    void SetLedName(int, const char *);
};
#endif