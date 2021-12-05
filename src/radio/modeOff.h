
#include "mode.h"
#include "monitor.h"

class RadioModeOFF : public RadioMode
{
public: // Class
    RadioModeOFF();
    ~RadioModeOFF();

public: //Mode
    void Show(Monitor *[2]);
    void Activated();
    void Check();
};
