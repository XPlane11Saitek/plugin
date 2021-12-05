
#include "ap.h"

class APOff : public AP
{
public:
    void Check();
    void Activate();
    void Show(Monitor *[2], unsigned char &);

public:
    APOff();
    ~APOff();
};
