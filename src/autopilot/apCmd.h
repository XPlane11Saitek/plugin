
#include "ap.h"
#include "sw.h"
#include "spec.h"

class APModeCMD : public AP
{
protected:
    Actions content[MULTI_BUTTON_LOADER];

public:
    APModeCMD();
    ~APModeCMD();
    void Loader(int, SWAction *);

public:
    void Check();
    void Activate();
    void Show(Monitor *[2], unsigned char &);

public: // Method
    void ButtonPush(int);
    void ButtonRelease(int);
};
