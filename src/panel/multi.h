
#include "monitor.h"
#include "ap.h"
#include "spec.h"
#include "panel.h"
#include "customRef.h"
#include "APForm.h"

class MULTIPanel : public Panel, public APForm
{
private: // USB PANEL DEV
    MULTIGetFeature rawCommand;
    MULTISetFeature rawDisplay;
    AP *mode[MULTI_MODE_COUNT];
    AP *active;
    Monitor *monitor[2];
    Monitor *monitorRevese[2];
    bool activeDualMode;
    CustomRef *buttonStatus[MULTI_BUTTON_COUNT];

protected:
    void set();
    void check();

public: // Конструктор
    /**
     * @brief Construct a new MULTIPanel object
     * 
     */
    MULTIPanel(hid_device *, const wchar_t *, int);

    /**
     * @brief Destroy the MULTIPanel object
     * 
     */
    ~MULTIPanel();

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
