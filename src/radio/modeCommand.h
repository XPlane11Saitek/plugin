
#include "monitor.h"
#include "mode.h"
#include "command.h"
#include "data.h"

class RadioModeCOMMAND : public RadioMode
{
private:
    XP11Value *com;
    XP11Command *smallDownCMD;
    XP11Command *smallUpCMD;
    XP11Command *bigDownCMD;
    XP11Command *bigUpCMD;

    STConvert *displayMode;

public:
    RadioModeCOMMAND(const char *value, const char *smallUp, const char *smallDown,
                     const char *bigUp, const char *bigDown, const char *display);
    RadioModeCOMMAND(const char *value, const char *smallUp, const char *smallDown,
                     const char *display);
    ~RadioModeCOMMAND();

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
