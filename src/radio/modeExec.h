
#include "mode.h"
#include "command.h"

class RadioModeExec : public RadioMode
{
protected:
    RadioMode *left;
    XP11Command *cmd;

public:
    RadioModeExec(RadioMode *, const char *);
    ~RadioModeExec();

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
