
#include "ap.h"
#include "range.h"

class APModeList : public AP
{
protected:
    std::list<AP *> context;
    void Add(AP *);
    AP *activ;
    unsigned int mode;
    apCaption *caption;

protected:
    void swithTo();

public:
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);

public:
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();

public:
    APModeList();
    ~APModeList();
    static AP *New(FileContent *, const char *);
};
