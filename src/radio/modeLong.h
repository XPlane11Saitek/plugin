
#include "mode.h"
#include "monitor.h"
#include "sw.h"
#include "command.h"
#include <time.h>

class RadioModeLong : public RadioMode
{
protected:
    RadioMode *left;
    XP11Command *cmd;

private:
    time_t lastUpdate;
    bool isPush;
    bool isPushLong;
    int presTimeout;

private:
    void updateTime();
    bool isPressLong();

public:
    RadioModeLong(RadioMode *, const char *, int);
    ~RadioModeLong();

public:
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
