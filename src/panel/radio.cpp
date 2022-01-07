
#include "radio.h"
#include "debug.h"
// radio
#include "modeOff.h"
#include <cstring>

Radio::Radio(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids)
{
    //RadioPanel::createRadioElement()
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2] = new Monitor(true);
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->upMode[item] = new RadioModeOFF();
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->downMode[item] = new RadioModeOFF();
    this->upPush = new CustomRef("radio", this->panelNumber, "up");
    this->downPush = new CustomRef("radio", this->panelNumber, "down");
    this->upPanel = this->upMode[0];
    this->downPanel = this->downMode[0];
    this->upPanel->Activated();
    this->downPanel->Activated();

    // RadioPanel::connectUSB()
    memcpy(this->rawCommand, ZeroRADIOGetFeature, sizeof(ZeroRADIOGetFeature));
    memcpy(this->rawDisplay, ZeroRADIOSetFeature, sizeof(ZeroRADIOSetFeature));
#if (defined XPLANE11PLUGIN || defined USB)
    hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetAll();
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void Radio::show(int)
{
    memcpy(this->rawCommand, ZeroRADIOGetFeature, sizeof(ZeroRADIOGetFeature));
    memcpy(this->rawDisplay, ZeroRADIOSetFeature, sizeof(ZeroRADIOSetFeature));
#if (defined XPLANE11PLUGIN || defined USB)
    hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetOff();
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

Radio::~Radio()
{
    this->shutdown();
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        delete this->upMode[item];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        delete this->downMode[item];
    for (int i = 0; i < 4; i++)
        delete this->monitor[i / 2][i % 2];
    delete this->upPush;
    delete this->downPush;
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
        info("RADIO%i Requirements good", this->panelNumber);
        this->state = run;
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("RADIO%i FATAL ERROR [%s]", this->panelNumber, e.what());
        this->show(33);
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
    this->readUSBData();
    this->upPanel->Show(this->monitor[0]);
    this->downPanel->Show(this->monitor[1]);

    bool needUpdate = false;
    for (int i = 0; i < 4; i++)
        needUpdate = needUpdate || this->monitor[i / 2][i % 2]->IsChange(1 + 5 * i, this->rawDisplay);
    if (needUpdate)
    {
        for (int i = 0; i < 4; i++)
            this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
        hid_send_feature_report(this->panelUSBDevAddr, rawDisplay, sizeof(this->rawDisplay));
#endif
        debug("RADIO%i SET LED", this->panelNumber);
    }
}

void Radio::readUSBData()
{
    int status;
    do
    {
#if (defined XPLANE11PLUGIN || defined USB)
        status = hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
#else
        status = 0;
#endif
        this->changePos();
        this->rotate();
        this->changeMode();
    } while (status > 0);
}

void Radio::changePos()
{
    bool new_status;
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
    {
        // UP position
        new_status = this->rawCommand[RadioButtonBitUp[item][0]] & RadioButtonBitUp[item][1];
        if (new_status)
            if (this->upPanel != this->upMode[item])
                this->changeUpPos(item);
        // Down position
        new_status = this->rawCommand[RadioButtonBitDown[item][0]] & RadioButtonBitDown[item][1];
        if (new_status)
            if (this->downPanel != this->downMode[item])
                this->changeDownPos(item);
    }
}

void Radio::rotate()
{
    //01| TOP small Rotary Encoder clockwise
    if ((this->rawCommand[2] & 0x01))
        this->upPanel->SmallUp();
    //02| TOP small Rotary Encoder counter-clockwise
    if ((this->rawCommand[2] & 0x02))
        this->upPanel->SmallDown();
    //04| TOP big Rotary Encoder clockwise
    if ((this->rawCommand[2] & 0x04))
        this->upPanel->BigUp();
    //08| TOP big Rotary Encoder counter-clockwise
    if ((this->rawCommand[2] & 0x08))
        this->upPanel->BigDown();
    //10| BOTTOM small Rotary Encoder clockwise
    if ((this->rawCommand[2] & 0x10))
        this->downPanel->SmallUp();
    //20| BOTTOM small Rotary Encoder counter-clockwise
    if ((this->rawCommand[2] & 0x20))
        this->downPanel->SmallDown();
    //40| BOTTOM big Rotary Encoder clockwise
    if ((this->rawCommand[2] & 0x40))
        this->downPanel->BigUp();
    //80| BOTTOM big Rotary Encoder counter-clockwise
    if ((this->rawCommand[2] & 0x80))
        this->downPanel->BigDown();
}

void Radio::changeUpPos(int newPos)
{
    info("RADIO%i UP Activated", this->panelNumber);
    this->upPanel = this->upMode[newPos];
    this->upPanel->Activated();
}

void Radio::changeDownPos(int newPos)
{
    info("RADIO%i DOWN Activated", this->panelNumber);
    this->downPanel = this->downMode[newPos];
    this->downPanel->Activated();
}

void Radio::changeMode()
{
    // TOP ACT/STBY                    1           6           1       0x00 40 00
    if (this->rawCommand[1] & 0x40)
    {
        if (this->upPush->GetState() != 1)
        {
            info("RADIO%i UP PUSH", this->panelNumber);
            this->upPanel->Push();
            this->upPush->SetState(1);
        }
    }
    else if (this->upPush->GetState() != 0)
    {
        info("RADIO%i UP RELEASE", this->panelNumber);
        this->upPanel->Release();
        this->upPush->SetState(0);
    }
    // BOTTOM ACT/STBY                 1           7           1       0x00 80 00
    if (this->rawCommand[1] & 0x80)
    {
        if (this->downPush->GetState() != 1)
        {
            info("RADIO%i DOWN PUSH", this->panelNumber);
            this->downPanel->Push();
            this->downPush->SetState(1);
        }
    }
    else if (this->downPush->GetState() != 0)
    {
        info("RADIO%i DOWN RELEASE", this->panelNumber);
        this->downPanel->Release();
        this->downPush->SetState(0);
    }
}

void Radio::Load(FileContent *config)
{
    info("RADIO%i Loading", this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "RADIO", this->panelNumber);
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->upMode[item] = RadioMode::New(panelConfig, RadioButtonName[item]);
    this->upPanel = this->upMode[0];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->downMode[item] = RadioMode::New(panelConfig, RadioButtonName[item]);
    this->downPanel = this->downMode[0];
    this->state = loaded;
    panelConfig->CheckALLUsage();
    delete panelConfig;
    info("RADIO%i Download completion", this->panelNumber);
}

void Radio::shutdown()
{
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetOff();
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void Radio::Clear()
{
    this->state = init;
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        delete this->upMode[item];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        delete this->downMode[item];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->upMode[item] = new RadioModeOFF();
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->downMode[item] = new RadioModeOFF();
    this->upPanel = this->upMode[0];
    this->downPanel = this->downMode[0];
}
