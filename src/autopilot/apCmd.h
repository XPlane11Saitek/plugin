
#include "ap.h"
#include "sw.h"
#include "spec.h"

class APModeCMD : public AP
{
protected:
    Actions content[MULTI_BUTTON_LOADER];

public:
    APModeCMD();
    ~APModeCMD();
    static AP *New(FileContent *, const char *);
    void Loader(int, SWAction *);
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);
    void ButtonPush(int);
    void ButtonRelease(int);
};
