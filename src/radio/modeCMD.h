
#include "mode.h"
#include "command.h"
#include "sw.h"

class RadioModeCMD : public RadioMode
{
protected:
    RadioMode *left;
    XP11Command *cmd;

public:
    RadioModeCMD(RadioMode *, const char *);
    ~RadioModeCMD();

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
