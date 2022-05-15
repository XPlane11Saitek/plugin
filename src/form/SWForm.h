
#include "form.h"
#include "item.h"
#include "spec.h"

class SWForm : public virtual PanelForm
{
protected:
    int formPanelID;
    bool isVirtual;

    int cell_weight;
    int cell_height;
    int cell_delta;

    item *formLed[SW_LED_COUNT];
    item *formButton[SW_BUTTON_COUNT];

#ifdef XPLANE11PLUGIN
    XPLMWindowID g_window;
    static void draw(XPLMWindowID, void *);
    static int mouse(XPLMWindowID, int, int, int, void *);
    static XPLMCursorStatus cursor(XPLMWindowID, int, int, void *);
    static int wheels(XPLMWindowID, int, int, int, int, void *);
    static void keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int);
    void showLable(XPLMWindowID, int, int, const char *);
#endif
public:
    SWForm(hid_device *, const wchar_t *, int);
    ~SWForm();
    void ShowForm();
    void GetName(char *);

    void SetButtonStatus(int, bool);
    void SetButtonName(int, const char *);
    void SetLedStatus(int, int);
    void SetLedName(int, const char *);
};
