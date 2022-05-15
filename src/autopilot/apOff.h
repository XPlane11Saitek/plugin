
#include "ap.h"

class APOff : public AP
{
public:
    void Check();
    void Activate(apCaption *);
    void Show(Monitor *[2], unsigned char &);

public:
    APOff();
    ~APOff();
};
