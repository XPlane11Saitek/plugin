
#include "ap.h"
#include "range.h"

class APModeCOPY : public AP
{
protected:
    AP *left[2];

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
    APModeCOPY(AP *, AP *);
    ~APModeCOPY();
};
