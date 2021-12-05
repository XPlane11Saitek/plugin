#ifndef PANELFILE
#define PANELFILE

#include "spec.h"
#include "content.h"
#include "hidapi.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDefs.h"
#endif

class Panel
{
protected:
    // USB ADDRESS
    hid_device *panelUSBDevAddr;
    // UUID Device
    wchar_t panelSN[MAX_USB_HEADER_STR];
    // unice number id
    int panelNumber;

protected:
    // Panel status
    bool panelIsLoader;
    bool panelIsChecked;

public: // Конструктор
    Panel(hid_device *, const wchar_t *, int);
    virtual ~Panel();

public: // Method
    virtual void Reload();
    virtual void Clear();
    virtual void Load(FileContent *);
};
#endif
