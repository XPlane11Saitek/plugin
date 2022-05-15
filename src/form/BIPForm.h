
#include "form.h"
#include "item.h"
#include "spec.h"

class BIPForm : public virtual PanelForm
{
protected:
    /* data */
    int cell_weight;
    int cell_height;
    int cell_delta;

    int formPanelID;
    bool isVirtual;

    item *formLed[BIP_CELL_COUNT];
#ifdef XPLANE11PLUGIN
    XPLMWindowID g_window;
    static void draw(XPLMWindowID, void *);
    static int mouse(XPLMWindowID, int, int, int, void *);
    static XPLMCursorStatus cursor(XPLMWindowID, int, int, void *);
    static int wheels(XPLMWindowID, int, int, int, int, void *);
    static void keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int);
#endif

public:
    BIPForm(hid_device *, const wchar_t *, int);
    ~BIPForm();
    void ShowForm();
    void GetName(char *);
    void SetFormName(int, const char *);
    void SetFormCollor(int, int);
};
