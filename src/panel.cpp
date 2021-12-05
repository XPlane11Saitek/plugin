
#include "panel.h"
#include "debug.h"
#include <string.h>

Panel::Panel(hid_device *usbdev, const wchar_t *sn, int uids)
{
    this->panelUSBDevAddr = usbdev;
    this->panelNumber = uids;
    wcscpy(this->panelSN, sn);
    this->panelIsChecked = false;
    this->panelIsLoader = false;
}

Panel::~Panel() {}

void Panel::Reload() {}

void Panel::Clear() {}

void Panel::Load(FileContent *) {}
