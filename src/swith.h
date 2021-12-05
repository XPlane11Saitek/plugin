
#include "cell.h"
#include "panel.h"
#include "sw.h"
#include "spec.h"
#include "customRef.h"

class SWPanel : public Panel
{
private: // USB PANEL DEV
    SWGetFeature rawCommand;
    SWSetFeature rawDisplay;
    void shutdown(int);
    void connect();
    void check();

private: // Source and Dest
    Actions content[SW_BUTTON_COUNT];
    SingleLED *led[SW_LED_COUNT];
    CustomRef *button[SW_BUTTON_COUNT];
    unsigned int step;

private:
    void reloadLED();
    void readPosition();
    void readDecode();

public:
    SWPanel(hid_device *, const wchar_t *, int);
    void Reload();
    ~SWPanel();

public:
    void Clear();
    void Load(FileContent *);
};
