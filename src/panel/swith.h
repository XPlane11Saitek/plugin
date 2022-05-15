
#include "cell.h"
#include "panel.h"
#include "sw.h"
#include "spec.h"
#include "customRef.h"
#include "SWForm.h"

class SW : public Panel, public SWForm
{
private: // USB PANEL DEV
    SWGetFeature rawCommand;
    SWSetFeature rawDisplay;

private: // Source and Dest
    Actions content[SW_BUTTON_COUNT];
    SingleLED *led[SW_LED_COUNT];
    CustomRef *button[SW_BUTTON_COUNT];
#ifdef LOWPERFORMANCE
    unsigned int step;
#endif

protected:
    /**
     * @brief set mode
     */
    void set(int);

    /**
     * @brief  self check
     */
    void check();

public:
    /**
     * @brief Construct a new SW object
     */
    SW(hid_device *, const wchar_t *, int);

    /**
     * @brief Destroy the SW object
     */
    ~SW();

    /**
     * @brief 
     */
    void Reload();

    /**
     * @brief 
     */
    void Clear();

    /**
     * @brief 
     */
    void Load(FileContent *);

    /**
     * @brief 
     * 
     */
    int GetPanelID(char *);
};
