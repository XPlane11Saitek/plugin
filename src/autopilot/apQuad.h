
#include "ap.h"
#include "range.h"

class APModeQUAD : public AP
{
protected:
    AP *left[4];
    bool modeA;
    bool modeB;
    AP *active;
    apCaption *caption;

protected: //mode
    int getMode();
    void swithTo();

public:
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);

public: // Method
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();

public:
    APModeQUAD(AP *, AP *, AP *, AP *);
    ~APModeQUAD();
};
