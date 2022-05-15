
#include "multi.h"
#include "debug.h"
#include "apOff.h"
#include <cstring>
#include <cstdio>

MULTIPanel::MULTIPanel(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids), APForm(usbdev, sn, uids)
{
    // MULTIPanel::createElement()
    this->monitor[0] = new Monitor(false);
    this->monitor[1] = new Monitor(false);
    this->monitorRevese[0] = this->monitor[1];
    this->monitorRevese[1] = this->monitor[0];
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = new APOff();
    for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
        this->buttonStatus[item] = new CustomRef("multi", this->panelNumber, MULTIButttonDataRefName[item]);
    this->active = this->mode[0];
    this->activeDualMode = true;

    this->monitor[0]->SetAll();
    this->monitor[1]->SetAll();
    this->rawDisplay[11] = 0xFF;
    if (usbdev == NULL)
    {
        memcpy(this->rawCommand, ZeroMULTIGetFeature, sizeof(ZeroMULTIGetFeature));
        this->rawCommand[MULTIModeBit[0][0]] += MULTIModeBit[0][1];
    };
#if (defined XPLANE11PLUGIN)
    if (usbdev != NULL)
        hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif

    this->set();
}

MULTIPanel::~MULTIPanel()
{
    this->monitor[0]->SetOff();
    this->monitor[1]->SetOff();
    this->rawDisplay[11] = 0;
    this->set();

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
    if (this->state == init)
        return;
    if (this->state == loaded)
    {
        this->check();
        return;
    }

    // READ
    int status;
    do
    {
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            status = hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
        else
            status = 0;
#else
        status = 0;
#endif

        for (int item = 0; item < MULTI_MODE_COUNT; item++)
            if ((this->rawCommand[MULTIModeBit[item][0]] & MULTIModeBit[item][1]) && (this->active != this->mode[item]))
            {
                info("MULTI%i Activate %i", this->panelNumber, item);
                this->active = this->mode[item];
                this->active->Activate(&(this->caption));
                this->activeDualMode = item < 2;
            }
        if (this->rawCommand[0] & 0x20)
        {
            info("MULTI%i ROTATE UP ", this->panelNumber);
            this->active->RotateUp();
        }
        if (this->rawCommand[0] & 0x40)
        {
            info("MULTI%i ROTATE DOWN ", this->panelNumber);
            this->active->RotateDown();
        }
        if (this->rawCommand[2] & 0x04)
        {
            info("MULTI%i TRIM UP ", this->panelNumber);
            this->active->ButtonPush(MultiTRIM);
        }
        if (this->rawCommand[2] & 0x08)
        {
            info("MULTI%i TRIM DOWN ", this->panelNumber);
            this->active->ButtonRelease(MultiTRIM);
        }
        for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
            if ((this->rawCommand[MULTIButttonBit[item][0]] & MULTIButttonBit[item][1]) && (this->buttonStatus[item]->GetState() != 1))
            {
                info("MULTI%i BUTTON[%i] PUSH ", this->panelNumber, item);
                this->buttonStatus[item]->SetState(1);
                this->active->ButtonPush(item);
            }
        for (int item = 0; item < MULTI_BUTTON_COUNT; item++)
            if ((!(this->rawCommand[MULTIButttonBit[item][0]] & MULTIButttonBit[item][1])) && (this->buttonStatus[item]->GetState() != 0))
            {
                info("MULTI%i BUTTON[%i] RELEASE ", this->panelNumber, item);
                this->buttonStatus[item]->SetState(0);
                this->active->ButtonRelease(item);
            }
    } while (status > 0);

    // Show
    unsigned char button_status = 0;
    if (this->activeDualMode)
        this->active->Show(this->monitor, button_status);
    else
        this->active->Show(this->monitorRevese, button_status);

    // NEED REPAIN
    if ((this->monitor[0]->IsChange(1 + 5 * 0, this->rawDisplay)) ||
        (this->monitor[1]->IsChange(1 + 5 * 1, this->rawDisplay)) ||
        (button_status != this->rawDisplay[11]))
    {
        this->monitor[0]->Save(1 + 5 * 0, this->rawDisplay);
        this->monitor[1]->Save(1 + 5 * 1, this->rawDisplay);
        this->rawDisplay[11] = button_status;
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            hid_send_feature_report(this->panelUSBDevAddr, rawDisplay, sizeof(this->rawDisplay));
#endif
        this->caption.SetState(button_status);
        info("MULTI%i SET LED", this->panelNumber);
    }
}

void MULTIPanel::check()
{
    try
    {
        info("MULTI%i Verification requirements", this->panelNumber);
        for (int item = 0; item < MULTI_MODE_COUNT; item++)
            this->mode[item]->Check();
        this->state = run;
        this->active->Activate(&(this->caption));
        info("MULTI%i Requirements good", this->panelNumber);
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("MULTI%i FATAL ERROR [%s]", this->panelNumber, e.what());

#ifndef XPLANE11PLUGIN
        throw Exception(e.what());
#endif
    }
}

void MULTIPanel::set()
{
    memcpy(this->rawDisplay, ZeroMULTISetFeature, sizeof(ZeroMULTISetFeature));
    this->monitor[0]->Save(1 + 5 * 0, this->rawDisplay);
    this->monitor[1]->Save(1 + 5 * 1, this->rawDisplay);
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void MULTIPanel::Load(FileContent *config)
{
    info("MULTI%i Loading", this->panelNumber);
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = AP::New(config, MULTIModeName[item]);
    this->active = this->mode[0];
    this->state = loaded;
    info("MULTI%i Download completion", this->panelNumber);
}

void MULTIPanel::Clear()
{
    this->state = init;
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        delete this->mode[item];
    for (int item = 0; item < MULTI_MODE_COUNT; item++)
        this->mode[item] = new APOff();
    this->active = this->mode[0];
}

int MULTIPanel::GetPanelID(char *buffer)
{
    sprintf(buffer, "MULTI");
    return this->panelNumber;
}
