
#include "mode.h"
#include "monitor.h"
#include <ctime>

class RadioModeADD : public RadioMode
{
private:
    bool isLockSW;
    int mode = 0;
    RadioMode *a[2];
    Monitor *leftA;
    Monitor *leftB;

public: // Class
    RadioModeADD(RadioMode *, RadioMode *, const char *);
    ~RadioModeADD();
    void Check();
    void Show(Monitor *[2]);
    void Activated();

public:
    void Push();
    void Release();
    void BigUp();
    void BigDown();
    void SmallUp();
    void SmallDown();
};
