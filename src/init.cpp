#include "init.h"
#include "debug.h"
// PANEL
#include "bip.h"
#include "swith.h"
#include "radio.h"
#include "multi.h"

Panel *Driver::createPanelBIP(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    Panel *element = new BIP(usbAddr, sn, uid);
    return element;
}

Panel *Driver::createPanelSW(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    Panel *element = new SWPanel(usbAddr, sn, uid);
    return element;
}

Panel *Driver::createPanelMULTI(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    Panel *element = new MULTIPanel(usbAddr, sn, uid);
    return element;
}

Panel *Driver::createPanelRadio(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    Panel *element = new RadioPanel(usbAddr, sn, uid);
    return element;
}