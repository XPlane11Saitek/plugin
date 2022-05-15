
#include "form.h"
#include "apCaption.h"

class APForm : public virtual PanelForm
{
protected:
    int formPanelID;
    bool isVirtual;
    apCaption caption;
#ifdef XPLANE11PLUGIN
    XPLMWindowID g_window;
    static void draw(XPLMWindowID, void *);
    static int mouse(XPLMWindowID, int, int, int, void *);
    static XPLMCursorStatus cursor(XPLMWindowID, int, int, void *);
    static int wheels(XPLMWindowID, int, int, int, int, void *);
    static void keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int);
#endif

public:
    APForm(hid_device *, const wchar_t *, int);
    ~APForm();
    void ShowForm();
    void GetName(char *);
    void Draw(int l, int t);
};
