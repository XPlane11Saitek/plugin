
#include "radio.h"
#include "debug.h"
// radio
#include "modeOff.h"
#include <cstring>
#include <cstdio>

Radio::Radio(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids), RadioForm(usbdev, sn, uids)
{

    for (int item = 0; item < 4; item++)
        // Monitor *monitor[2][2];
        this->monitor[item / 2][item % 2] = new Monitor(true);

    for (int item = 0; item < RADIO_MODE_COUNT; item++)
    {
        // RadioMode *upMode[RADIO_MODE_COUNT];
        this->upMode[item] = new RadioModeOFF();
        // RadioMode *downMode[RADIO_MODE_COUNT];
        this->downMode[item] = new RadioModeOFF();
    }

    // CustomRef *upPush;
    this->upPush = new CustomRef("radio", this->panelNumber, "up");
    // CustomRef *downPush;
    this->downPush = new CustomRef("radio", this->panelNumber, "down");

    this->up = this->upMode[0];
    this->down = this->downMode[0];

    // RadioMode *up;
    this->up->Activated();
    // RadioMode *down;
    this->down->Activated();

    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetAll();
    this->set();
}

void Radio::set()
{
    memcpy(this->rawCommand, ZeroRADIOGetFeature, sizeof(ZeroRADIOGetFeature));
    memcpy(this->rawDisplay, ZeroRADIOSetFeature, sizeof(ZeroRADIOSetFeature));
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
    {
        hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
    }
#endif
}

Radio::~Radio()
{
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetOff();
    this->set();

    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        // RadioMode *upMode[RADIO_MODE_COUNT];
        delete this->upMode[item];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        // RadioMode *downMode[RADIO_MODE_COUNT];
        delete this->downMode[item];
    for (int i = 0; i < 4; i++)
        // Monitor *monitor[2][2];
        delete this->monitor[i / 2][i % 2];
    // CustomRef *upPush;
    delete this->upPush;
    // CustomRef *downPush;
    delete this->downPush;
    // RadioMode *up;
    // RadioMode *down;
}

void Radio::check()
{
    try
    {
        info("RADIO%i Verification requirements", this->panelNumber);
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            upMode[item]->Check();
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            downMode[item]->Check();
        this->up->Activated();
        this->down->Activated();
        info("RADIO%i Requirements good", this->panelNumber);
        this->state = run;
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("RADIO%i FATAL ERROR [%s]", this->panelNumber, e.what());
        for (int item = 0; item < 4; item++)
            this->monitor[item / 2][item % 2]->SetCode(1);
        this->set();
#ifndef XPLANE11PLUGIN
        throw Exception(e.what());
#endif
    }
}

void Radio::Reload()
{
    if (this->state == init)
        return;
    if (this->state == loaded)
    {
        this->check();

        return;
    }

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
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            if ((this->rawCommand[RadioButtonBitUp[item][0]] & RadioButtonBitUp[item][1]) && (this->up != this->upMode[item]))
            {
                info("RADIO%i UP Activated", this->panelNumber);
                this->up = this->upMode[item];
                this->up->Activated();
            }
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            if ((this->rawCommand[RadioButtonBitDown[item][0]] & RadioButtonBitDown[item][1]) && (this->down != this->downMode[item]))
            {
                info("RADIO%i DOWN Activated", this->panelNumber);
                this->down = this->downMode[item];
                this->down->Activated();
            }
        //01| TOP small Rotary Encoder clockwise
        if ((this->rawCommand[2] & 0x01))
            this->up->SmallUp();
        //02| TOP small Rotary Encoder counter-clockwise
        if ((this->rawCommand[2] & 0x02))
            this->up->SmallDown();
        //04| TOP big Rotary Encoder clockwise
        if ((this->rawCommand[2] & 0x04))
            this->up->BigUp();
        //08| TOP big Rotary Encoder counter-clockwise
        if ((this->rawCommand[2] & 0x08))
            this->up->BigDown();
        //10| BOTTOM small Rotary Encoder clockwise
        if ((this->rawCommand[2] & 0x10))
            this->down->SmallUp();
        //20| BOTTOM small Rotary Encoder counter-clockwise
        if ((this->rawCommand[2] & 0x20))
            this->down->SmallDown();
        //40| BOTTOM big Rotary Encoder clockwise
        if ((this->rawCommand[2] & 0x40))
            this->down->BigUp();
        //80| BOTTOM big Rotary Encoder counter-clockwise
        if ((this->rawCommand[2] & 0x80))
            this->down->BigDown();
        // TOP ACT/STBY                    1           6           1       0x00 40 00
        if (this->rawCommand[1] & 0x40)
        {
            if (this->upPush->GetState() != 1)
            {
                info("RADIO%i UP PUSH", this->panelNumber);
                this->up->Push();
                this->upPush->SetState(1);
            }
        }
        else if (this->upPush->GetState() != 0)
        {
            info("RADIO%i UP RELEASE", this->panelNumber);
            this->up->Release();
            this->upPush->SetState(0);
        }
        // BOTTOM ACT/STBY                 1           7           1       0x00 80 00
        if (this->rawCommand[1] & 0x80)
        {
            if (this->downPush->GetState() != 1)
            {
                info("RADIO%i DOWN PUSH", this->panelNumber);
                this->down->Push();
                this->downPush->SetState(1);
            }
        }
        else if (this->downPush->GetState() != 0)
        {
            info("RADIO%i DOWN RELEASE", this->panelNumber);
            this->down->Release();
            this->downPush->SetState(0);
        }
    } while (status > 0);

    this->up->Show(this->monitor[0]);
    this->down->Show(this->monitor[1]);

    bool needUpdate = false;
    for (int i = 0; i < 4; i++)
        needUpdate = needUpdate || this->monitor[i / 2][i % 2]->IsChange(1 + 5 * i, this->rawDisplay);
    if (needUpdate)
    {
        for (int i = 0; i < 4; i++)
            this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            hid_send_feature_report(this->panelUSBDevAddr, rawDisplay, sizeof(this->rawDisplay));
#endif
        debug("RADIO%i SET LED", this->panelNumber);
    }
}

void Radio::Load(FileContent *config)
{
    for (int item = 0; item < 4; item++)
        this->monitor[item / 2][item % 2]->SetCode(0);
    this->set();

    info("RADIO%i Loading", this->panelNumber);
    // UP
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->upMode[item] = RadioMode::New(config, RadioButtonName[item]);
    this->up = this->upMode[0];
    // DOWN
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->downMode[item] = RadioMode::New(config, RadioButtonName[item]);
    this->down = this->downMode[0];
    info("RADIO%i Download completion", this->panelNumber);

    this->state = loaded;
}

void Radio::Clear()
{
    this->state = init;
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
    {
        delete this->upMode[item];
        delete this->downMode[item];
        this->upMode[item] = new RadioModeOFF();
        this->downMode[item] = new RadioModeOFF();
    }
    this->up = this->upMode[0];
    this->down = this->downMode[0];

    this->up->Activated();
    this->down->Activated();
}

int Radio::GetPanelID(char *buffer)
{
    sprintf(buffer, "RADIO");
    return this->panelNumber;
}
