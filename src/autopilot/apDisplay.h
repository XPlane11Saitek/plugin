
#include "ap.h"
#include "spec.h"
#include "mode.h"
#include "range.h"

class APModeDisplay : public AP
{
protected:
    RadioMode *modes[MULTI_BUTTON_LOADER];
    XPlaneRange *value[MULTI_LED_COUNT];
    RadioMode *active;
    bool swithto(int);

public:
    APModeDisplay();
    ~APModeDisplay();
    static AP *New(FileContent *, const char *);
    void LoaderMode(int, RadioMode *);
    void LoaderRange(int, XPlaneRange *);

    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();
};
