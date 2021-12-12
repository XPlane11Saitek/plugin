#include "monitor.h"
#include "mode.h"
#include <ctime>

class RadioModeDUAL : public RadioMode
{
private:
    RadioMode *a[2];
    int mode = 0;
    time_t lastUpdate;
    bool isPush = false;
    bool isPushLong = false;
    int presTimeout = 3;

private:
    void updateTime();
    bool isPressLong();
    void switchTo(int);

public: // Class
    RadioModeDUAL(RadioMode *, RadioMode *, const char *);
    ~RadioModeDUAL();

public: //Mode
    void Show(Monitor *[2]);
    void Activated();
    void Check();

public:
    void Push();
    void Release();
    void BigUp();
    void BigDown();
    void SmallUp();
    void SmallDown();
};
