
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
    void LoaderMode(int, RadioMode *);
    void LoaderRange(int, XPlaneRange *);

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
