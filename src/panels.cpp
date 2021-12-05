#include "panels.h"
#include "debug.h"
#include "reader.h"
#include <cstring>

SaitekDriver::SaitekDriver()
{ //init
    this->findUSB(0x6a3, 0x0b4e, &SaitekDriver::createPanelBIP);
    this->findUSB(0x6a3, 0x0d67, &SaitekDriver::createPanelSW);
    this->findUSB(0x6a3, 0x0d05, &SaitekDriver::createPanelRadio);
    this->findUSB(0x6a3, 0x0d06, &SaitekDriver::createPanelMULTI);
}

void SaitekDriver::Test()
{
    wchar_t serialNumber[MAX_USB_HEADER_STR];
    /* BIP */
    this->device.insert(this->device.begin(), 1,
                        this->createPanelBIP(NULL, serialNumber, 0));
    this->device.insert(this->device.begin(), 1,
                        this->createPanelBIP(NULL, serialNumber, 1));
    /* SWITH */
    this->device.insert(this->device.begin(), 1,
                        this->createPanelSW(NULL, serialNumber, 0));
    this->device.insert(this->device.begin(), 1,
                        this->createPanelSW(NULL, serialNumber, 1));
    /* RADIO */
    this->device.insert(this->device.begin(), 1,
                        this->createPanelRadio(NULL, serialNumber, 0));
    // MULTI
    this->device.insert(this->device.begin(), 1,
                        this->createPanelMULTI(NULL, serialNumber, 0));
}

SaitekDriver::~SaitekDriver()
{
    for (Panel *row : this->device)
        delete row;
    this->device.clear();
}

void SaitekDriver::findUSB(int vendorID, int deviceID, onCallback func)
{
    int uid = 0;
    debug("%s USB[%i:%i] The scan begins", PLUGIN_INFO, vendorID, deviceID);
    struct hid_device_info *devs = hid_enumerate(vendorID, deviceID);
    for (struct hid_device_info *cursor = devs; cursor; cursor = cursor->next)
    {
        debug("%s USB[%i:%i] Found", PLUGIN_INFO, vendorID, deviceID);
        hid_device *usbAddr = hid_open_path(cursor->path);
        if (usbAddr != NULL)
        {
            wchar_t serialNumber[MAX_USB_HEADER_STR];
            hid_get_serial_number_string(usbAddr, serialNumber, MAX_USB_HEADER_STR);
            debug("%s USB[%i:%i] SN %ls", PLUGIN_INFO, vendorID, deviceID, serialNumber);
            Panel *element = ((*this).*(func))(usbAddr, serialNumber, uid++);
            if (element != NULL)
            {
                this->device.insert(this->device.begin(), 1, element);
                debug("%s USB[%i:%i] Added", PLUGIN_INFO, vendorID, deviceID);
            }
            else
                debug("%s USB[%i:%i] Skiped", PLUGIN_ERROR, vendorID, deviceID);
        }
        else
            debug("%s USB[%i:%i] Bad pointer to the address", PLUGIN_ERROR, vendorID, deviceID);
    }
    hid_free_enumeration(devs);
    debug("%s USB[%i:%i] Scan completed", PLUGIN_INFO, vendorID, deviceID);
}

std::list<Panel *>::iterator SaitekDriver::begin()
{
    return this->device.begin();
};

std::list<Panel *>::iterator SaitekDriver::end()
{
    return this->device.end();
};

void SaitekDriver::Clean()
{
    for (Panel *row : this->device)
        row->Clear();
}

void SaitekDriver::Load(std::string filename)
{
    FileReader *config = new FileReader(filename);
    for (Panel *row : this->device)
    {
        try
        {
            row->Load(config);
        }
        catch (const std::exception &e)
        {

            debug("%s PANEL ERROR [%s]", PLUGIN_ERROR, e.what());
#ifdef DEBUG
            throw Exception("%s", e.what());
#endif
        }
    }
    delete config;
}
