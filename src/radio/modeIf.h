
#include "monitor.h"
#include "mode.h"
#include "range.h"

class RadioModeIF : public RadioMode
{
private:
    RadioMode *a[2];
    XPlaneRange *cmd;
    int mode = 0;
    void swithTo(int);
    int getMode();

public:
    RadioModeIF(RadioMode *, RadioMode *, const char *);
    ~RadioModeIF();

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
