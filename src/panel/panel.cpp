// -*- lsst-c++ -*-
/** Ukraine:
 * Програмний код віртуальної панелі.
 *
 * @file panel.cpp
 * @brief Virtual panel
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "panel.h"
#include "debug.h"

// PANEL
#include "bip.h"
#include "swith.h"
#include "radio.h"
#include "multi.h"

/** Ukraine:
 * Конструктор для глобального обєкту.
 * 
 * @brief Global construction
 * 
 */
Panel::Panel()
{
    this->panelUSBDevAddr = NULL;
    this->panelNumber = {0};
    this->state = init;
}

/** Ukraine:
 * Створення панелі. 
 * Конструктор класу.
 * 
 * @param 0 Адрес пристрою 
 * @param 1 серійний номер
 * @param 2 номер панелі
 * 
 * @brief Construct a new Panel object
 * 
 */
Panel::Panel(hid_device *usbdev, const wchar_t *sn, int uids)
{
    this->panelUSBDevAddr = usbdev;
    this->panelNumber = uids;
    wcscpy(this->panelSN, sn);
    this->state = init;
}

/** Ukraine:
 * Створення панелі відповідного типу. 
 * @brief Create object 
 * 
 * @return Panel* 
 */
Panel *Panel::createPanelBIP(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    return new BIP(usbAddr, sn, uid);
}

/** Ukraine:
 * Створення панелі відповідного типу. 
 * @brief Create object 
 * 
 * @return Panel* 
 */
Panel *Panel::createPanelSW(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    return new SW(usbAddr, sn, uid);
}

/** Ukraine:
 * Створення панелі відповідного типу. 
 * @brief Create object 
 * 
 * @return Panel* 
 */
Panel *Panel::createPanelMULTI(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    return new MULTIPanel(usbAddr, sn, uid);
}

/** Ukraine:
 * Створення панелі відповідного типу. 
 * @brief Create object 
 * 
 * @return Panel* 
 */
Panel *Panel::createPanelRadio(hid_device *usbAddr, const wchar_t *sn, int uid)
{
    return new Radio(usbAddr, sn, uid);
}