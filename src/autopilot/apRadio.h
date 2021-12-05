
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
    void Loader(int, RadioMode *);

public:
    void Check();
    void Activate();
    void Show(Monitor *[2], unsigned char &);

public: // Method
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();
};
