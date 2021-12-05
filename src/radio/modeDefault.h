
#include "monitor.h"
#include "mode.h"
#include "command.h"
#include "data.h"

class RadioModeDEFAULT : public RadioMode
{
private:
    XP11Value *com1;
    XP11Value *com2;
    XP11Command *smallDownCMD;
    XP11Command *smallUpCMD;
    XP11Command *bigDownCMD;
    XP11Command *bigUpCMD;
    XP11Command *comActStby;
    STConvert *displayMode;

public:
    RadioModeDEFAULT(const char *value1, const char *value2, const char *smallUp,
                     const char *smallDown, const char *bigUp, const char *bigDown,
                     const char *act, const char *display);
    ~RadioModeDEFAULT();

public: //Mode
    void Show(Monitor *[2]);
    bool IsUpdated();
    void Push();
    void Release();
    void Activated();
    void Deactivated();
    void BigUp();
    void BigDown();
    void SmallUp();
    void SmallDown();
    void Check();
};
