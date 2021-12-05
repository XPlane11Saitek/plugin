
#include "panel.h"
#include "monitor.h"
#include "mode.h"
#include "spec.h"
#include "customRef.h"

class RadioPanel : public Panel
{
private: // USB PANEL DEV
    RADIOGetFeature rawCommand;
    RADIOSetFeature rawDisplay;

protected: // Mode
    RadioMode *upMode[RADIO_MODE_COUNT];
    RadioMode *downMode[RADIO_MODE_COUNT];
    Monitor *monitor[2][2];
    RadioMode *upPanel;
    RadioMode *downPanel;

protected:
    CustomRef *upPush;
    CustomRef *downPush;

private: //Read USB
    void connectUSB();
    void readUSBData();
    void createRadioElement();
    void changePos();
    void changeUpPos(int);
    void changeDownPos(int);
    void rotate();
    void changeMode();
    void check();
    void shutdown();
    void show(int);

public:
    RadioPanel(hid_device *, const wchar_t *, int);
    ~RadioPanel();

public:
    void Reload();
    void Clear();
    void Load(FileContent *);
};
