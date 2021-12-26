
#include "monitor.h"
#include "ap.h"
#include "spec.h"
#include "panel.h"
#include "customRef.h"

class MULTIPanel : public Panel
{
private: // USB PANEL DEV
    MULTIGetFeature rawCommand;
    MULTISetFeature rawDisplay;
    Monitor *monitor[2];
    AP *mode[MULTI_MODE_COUNT];
    AP *active;
    bool activeDualMode;
    CustomRef *buttonStatus[MULTI_BUTTON_COUNT];

protected:
    void shutdown();
    void check();

private:
    void readUSBData();
    void swith();
    void rotate();
    void trim();
    void button();

public: // Конструктор
    MULTIPanel(hid_device *, const wchar_t *, int);
    ~MULTIPanel();
    void Reload();
    void Clear();
    void Load(FileContent *);
};
