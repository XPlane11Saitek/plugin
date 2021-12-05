
#include "monitor.h"
#include "mode.h"
#include "value.h"
#include <ctime>
#include "data.h"

class RadioModeValue : public RadioMode
{
private:
    XP11Value *com;
    float bigValue, smallValue;
    float maxValue, minValue;
    bool roundFlag;
    STConvert *displayMode;

private:
    void update(float);

public: // Class
    RadioModeValue(const char *, const char *, float, float, float, float, bool);
    RadioModeValue(const char *, const char *, float, float, float, bool);
    ~RadioModeValue();

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
