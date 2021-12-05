

#include "monitor.h"
#include "mode.h"
#include "value.h"
#include <ctime>

class RadioModeTimeout : public RadioMode
{
private:
    RadioMode *a[2];
    int mode = 0;
    int idleTimeout = 15;
    time_t lastUpdate;

public: // Class
    RadioModeTimeout(RadioMode *, RadioMode *, int);
    ~RadioModeTimeout();

public:
    void Show(Monitor *[2]);
    void Check();
    void Activated();

public:
    void Push();
    void Release();
    void BigUp();
    void BigDown();
    void SmallUp();
    void SmallDown();
};
