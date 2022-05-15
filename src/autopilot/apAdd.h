
#include "ap.h"
#include "range.h"

class APModeAdd : public AP
{
protected:
    AP *left[2];
    int mode;

protected: //mode
    int getMode();
    void swithTo(int newMode);
    apCaption *caption;

public:
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();
    APModeAdd(AP *, AP *);
    ~APModeAdd();
};
