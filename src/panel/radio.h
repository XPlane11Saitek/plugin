
#include "panel.h"
#include "monitor.h"
#include "mode.h"
#include "spec.h"
#include "customRef.h"
#include "RadioForm.h"

class Radio : public Panel, public RadioForm
{
private: // USB PANEL DEV
    RADIOGetFeature rawCommand;
    RADIOSetFeature rawDisplay;
    RadioMode *upMode[RADIO_MODE_COUNT];
    RadioMode *downMode[RADIO_MODE_COUNT];
    Monitor *monitor[2][2];
    RadioMode *up;
    RadioMode *down;
    CustomRef *upPush;
    CustomRef *downPush;

private: //Read USB
    void check();
    void set();

public:
    /**
     * @brief Construct a new Radio object
     * 
     */
    Radio(hid_device *, const wchar_t *, int);

    /**
     * @brief Destroy the Radio object
     * 
     */
    ~Radio();

    /**
     * @brief 
     * 
     */
    void Reload();

    /**
     * @brief 
     * 
     */
    void Clear();

    /**
     * @brief 
     * 
     */
    void Load(FileContent *);

    /**
     * @brief 
     * 
     */
    int GetPanelID(char *);
};
