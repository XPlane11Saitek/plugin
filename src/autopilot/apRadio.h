
#include "ap.h"
#include "spec.h"
#include "mode.h"

#define AP_RADIO_MODE_COUNT 5
class APModeRadio : public AP
{
protected:
    int mode;
    bool isUpper;
    RadioMode *modes[AP_RADIO_MODE_COUNT];
    RadioMode *active;
    void swithto(int);

public:
    APModeRadio();
    ~APModeRadio();
    static AP *New(FileContent *, const char *);
    void Loader(int, RadioMode *);
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();
};
