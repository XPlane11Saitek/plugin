
#include "panel.h"

class Driver
{
protected:
    Panel *createPanelBIP(hid_device *, const wchar_t *, int);
    Panel *createPanelSW(hid_device *, const wchar_t *, int);
    Panel *createPanelRadio(hid_device *, const wchar_t *, int);
    Panel *createPanelMULTI(hid_device *, const wchar_t *, int);
};

typedef Panel *(Driver::*onCallback)(hid_device *, const wchar_t *, int);
