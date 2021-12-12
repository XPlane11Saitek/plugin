#include "monitor.h"
#include "mode.h"
#include <ctime>
#include "data.h"

class RadioModeSHOW : public RadioMode
{
private:
    XP11Value *com;
    time_t lastUpdate;
    STConvert *displayMode;
    float state;
    bool allChanges;

public: // Class
    RadioModeSHOW(const char *, const char *);
    ~RadioModeSHOW();

public:
    void Check();
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
};
