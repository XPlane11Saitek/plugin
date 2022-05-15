
#include "ap.h"
#include "range.h"

class APModeCOPY : public AP
{
protected:
    AP *left[2];
    apCaption faikCaption;

public:
    void
    Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);

public: // Method
    void ButtonPush(int);
    void ButtonRelease(int);
    void RotateUp();
    void RotateDown();

public:
    APModeCOPY(AP *, AP *);
    ~APModeCOPY();
};
