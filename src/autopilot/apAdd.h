
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

public:
    void Check();
    void Activate();
    void Show(Monitor *[2], unsigned char &);

public: // Method
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();

public:
    APModeAdd(AP *, AP *);
    ~APModeAdd();
};
