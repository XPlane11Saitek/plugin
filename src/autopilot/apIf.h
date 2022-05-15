
#include "ap.h"
#include "range.h"

class APModeIF : public AP
{
protected:
    AP *left[2];
    int mode;
    XPlaneRange *cmd;
    apCaption *caption;

protected: //mode
    int getMode();
    void swithTo(int newMode);

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
    APModeIF(AP *, AP *, const char *);
    ~APModeIF();
};
