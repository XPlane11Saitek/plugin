// -*- lsst-c++ -*-
/** Ukraine:
 * Фай реалізаці групи обктів.
 * 
 * @file panels.cpp
 * @brief Program group panel
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include "panels.h"
#include "debug.h"
#include <cstring>

#ifdef XPLANE11PLUGIN
Panels device;
#endif

/** Ukraine:
 * Cтворення панелей. 
 * Пошук всіх USB пристроїв.
 * Також створення на базі кожної панелі 
 * індивідальни відповідний обєкт.
 * За допомогою цього методу досягаєтсья 
 * підтримка великої кількості панель.
 * 
 * @brief Construct a new Panels object
 * 
 */
Panels::Panels() : Panel()
{
    this->findUSB(0x6a3, 0x0b4e, &Panels::createPanelBIP);
    this->findUSB(0x6a3, 0x0d67, &Panels::createPanelSW);
    this->findUSB(0x6a3, 0x0d05, &Panels::createPanelRadio);
    this->findUSB(0x6a3, 0x0d06, &Panels::createPanelMULTI);
}

/** Ukraine:
 * Знищення панелей.
 * @brief Destrutor a exist Panels
 */
Panels::~Panels()
{
    for (auto row : this->device)
        delete row;
    this->device.clear();
}

/** Ukraine:
 * Функція пошуку usb пристроїв.
 * При знаходженні виклиається функція 
 * як задан параметром.
 * 
 * @brief Search usb devices
 * 
 */
void Panels::findUSB(int vendorID, int deviceID, onFunction func)
{
    int uid = 0;
    info("USB[%i:%i] The scan begins", vendorID, deviceID);
    struct hid_device_info *devs = hid_enumerate(vendorID, deviceID);
    for (struct hid_device_info *cursor = devs; cursor; cursor = cursor->next)
    {
        debug("USB[%i:%i] Found", vendorID, deviceID);
        hid_device *usbAddr = hid_open_path(cursor->path);
        if (usbAddr != NULL)
        {
            wchar_t serialNumber[MAX_USB_HEADER_STR] = {0};
            hid_get_serial_number_string(usbAddr, serialNumber, MAX_USB_HEADER_STR);
            info("USB[%i:%i] SN %ls", vendorID, deviceID, serialNumber);
            Panel *element = ((*this).*(func))(usbAddr, serialNumber, uid++);
            this->device.insert(this->device.begin(), 1, element);
            debug("USB[%i:%i] Added", vendorID, deviceID);
        }
        else
            warning("USB[%i:%i] Bad pointer to the address", vendorID, deviceID);
    }
    hid_free_enumeration(devs);
    info("USB[%i:%i] Scan completed", vendorID, deviceID);
}

/** Ukraine:
 * Можливість видача списку панель
 * Також можливість пошуку панелі.
 * Можливості доступу до індивідальної 
 * панелі.
 * 
 * @brief Iterator by Panel 
 * 
 * @return std::list<Panel *>::iterator 
 */
std::list<Panel *>::iterator Panels::begin()
{
    return this->device.begin();
};

/** Ukraine:
 * Можливість видача списку панель
 * Також можливість пошуку панелі.
 * Можливості доступу до індивідальної 
 * панелі.
 * 
 * @brief Iterator by Panel 
 * 
 * @return std::list<Panel *>::iterator 
 */
std::list<Panel *>::iterator Panels::end()
{
    return this->device.end();
};

/** Ukraine:
 * Зкидання настройок панелі.
 * @brief Reset confugre for panel
 * 
 */
void Panels::Clean()
{
    for (auto row : this->device)
        row->Clear();
}

/** Ukraine:
 * Загузка нового файлу конфігураці.
 * @brief Configure panel and actions
 * 
 */
void Panels::Load(FileContent *config)
{
    for (auto row : this->device)
        row->Load(config);
}
