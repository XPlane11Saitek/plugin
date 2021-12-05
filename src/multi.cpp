
#include "multi.h"
#include "debug.h"
#include "apOff.h"
#include "apLoad.h"
#include <cstring>

MULTIPanel::MULTIPanel(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids)
{
    // MULTIPanel::createElement()
    this->monitor[0] = new Monitor(false);
    this->monitor[1] = new Monitor(false);
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = new APOff();
    for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
        this->buttonStatus[item] = new CustomRef("multi", this->panelNumber, MULTIButttonDataRefName[item]);
    this->active = this->mode[0];
    this->activeDualMode = true;

    // MULTIPanel::connectUSB()
    memcpy(this->rawCommand, ZeroMULTIGetFeature, sizeof(ZeroMULTIGetFeature));
    memcpy(this->rawDisplay, ZeroMULTISetFeature, sizeof(ZeroMULTISetFeature));
#if (defined XPLANE11PLUGIN || defined USB)
    hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    this->monitor[0]->SetAll();
    this->monitor[1]->SetAll();
    this->monitor[0]->Save(1 + 5 * 0, this->rawDisplay);
    this->monitor[1]->Save(1 + 5 * 1, this->rawDisplay);
    this->rawDisplay[11] = 0xFF;
#if (defined XPLANE11PLUGIN || defined USB)
    hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

MULTIPanel::~MULTIPanel()
{
    this->shutdown();
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        delete this->mode[item];
    for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
        delete this->buttonStatus[item];
    delete this->monitor[0];
    delete this->monitor[1];
}

void MULTIPanel::Reload()
{
    // PRE-CHECK
    if (!this->panelIsLoader)
        return;
    if (!this->panelIsChecked)
    {
        this->check();
        return;
    }

    // READ
    this->readUSBData();

    // Show
    unsigned char button_status = 0;
    if (this->activeDualMode)
        this->active->Show(this->monitor, button_status);
    else
    {
        Monitor *rev[2];
        rev[0] = this->monitor[1];
        rev[1] = this->monitor[0];
        this->active->Show(rev, button_status);
    }
    //
    if ((this->monitor[0]->IsChange(1 + 5 * 0, this->rawDisplay)) ||
        (this->monitor[1]->IsChange(1 + 5 * 1, this->rawDisplay)) ||
        (button_status != this->rawDisplay[11]))
    {
        this->monitor[0]->Save(1 + 5 * 0, this->rawDisplay);
        this->monitor[1]->Save(1 + 5 * 1, this->rawDisplay);
        this->rawDisplay[11] = button_status;
#if (defined XPLANE11PLUGIN || defined USB)
        hid_send_feature_report(this->panelUSBDevAddr, rawDisplay, sizeof(this->rawDisplay));
#endif
#ifdef DEBUG
        debug("%s MULTI%i SET LED", PLUGIN_DEBUG, this->panelNumber);
#endif
    }
}

void MULTIPanel::check()
{
    try
    {
        debug("%s MULTI%i Verification requirements", PLUGIN_INFO, this->panelNumber);
        for (int item = 0; item < MULTI_MODE_COUNT; item++)
            this->mode[item]->Check();
        this->panelIsChecked = true;
        debug("%s MULTI%i Requirements good", PLUGIN_INFO, this->panelNumber);
    }
    catch (const std::exception &e)
    {
        this->panelIsLoader = false;
        debug("%s MULTI%i FATAL ERROR [%s]", PLUGIN_ERROR, this->panelNumber, e.what());
    }
}

void MULTIPanel::readUSBData()
{
    int status;
    do
    {
#if (defined XPLANE11PLUGIN || defined USB)
        status = hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
#else
        status = 0;
#endif
        this->swith();
        this->rotate();
        this->trim();
        this->button();
    } while (status > 0);
}

void MULTIPanel::swith()
{
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
    {
        bool isSetMode = this->rawCommand[MULTIModeBit[item][0]] & MULTIModeBit[item][1];
        if (isSetMode)
            if (this->active != this->mode[item])
            {
#ifdef DEBUG
                debug("%s MULTI%i Activate %i", PLUGIN_DEBUG, this->panelNumber, item);
#endif
                this->active = this->mode[item];
                this->active->Activate();
                this->activeDualMode = item < 2;
            }
    }
}

void MULTIPanel::rotate()
{
    if (this->rawCommand[0] & 0x20)
    {
#ifdef DEBUG
        debug("%s MULTI%i ROTATE UP ", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->active->RotateUp();
    }
    if (this->rawCommand[0] & 0x40)
    {
#ifdef DEBUG
        debug("%s MULTI%i ROTATE DOWN ", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->active->RotateDown();
    }
}

void MULTIPanel::trim()
{
    if (this->rawCommand[2] & 0x04)
    {
#ifdef DEBUG
        debug("%s MULTI%i TRIM UP ", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->active->ButtonPush(MultiTRIM);
    }
    else if (this->rawCommand[2] & 0x08)
    {
#ifdef DEBUG
        debug("%s MULTI%i TRIM DOWN ", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->active->ButtonRelease(MultiTRIM);
    }
}

void MULTIPanel::button()
{
    bool new_status;
    for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
    {
        new_status = this->rawCommand[MULTIButttonBit[item][0]] & MULTIButttonBit[item][1];
        if ((new_status) && (this->buttonStatus[item]->GetState() != 1))
        {
#ifdef DEBUG
            debug("%s MULTI%i BUTTON[%i] PUSH ", PLUGIN_DEBUG, this->panelNumber, item);
#endif
            this->buttonStatus[item]->SetState(1);
            this->active->ButtonPush(item);
        }
        if ((!new_status) && (this->buttonStatus[item]->GetState() != 0))
        {
#ifdef DEBUG
            debug("%s MULTI%i BUTTON[%i] RELEASE ", PLUGIN_DEBUG, this->panelNumber, item);
#endif
            this->buttonStatus[item]->SetState(0);
            this->active->ButtonRelease(item);
        }
    }
}

void MULTIPanel::shutdown()
{
    memcpy(this->rawDisplay, ZeroMULTISetFeature, sizeof(ZeroMULTISetFeature));
    this->monitor[0]->SetOff();
    this->monitor[1]->SetOff();
    this->monitor[0]->Save(1 + 5 * 0, this->rawDisplay);
    this->monitor[1]->Save(1 + 5 * 1, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void MULTIPanel::Load(FileContent *config)
{
    debug("%s MULTI%i Loading", PLUGIN_INFO, this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "MULTI", this->panelNumber);
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = LoadAP(panelConfig, MULTIModeName[item]);
    this->active = this->mode[0];
    this->panelIsChecked = false;
    this->panelIsLoader = true;
    delete panelConfig;
    debug("%s MULTI%i Download completion", PLUGIN_INFO, this->panelNumber);
}

void MULTIPanel::Clear()
{
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        delete this->mode[item];
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = new APOff();
    this->active = this->mode[0];
}
