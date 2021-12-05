
#include "radio.h"
#include "debug.h"
// radio
#include "modeOff.h"
#include <cstring>
#include "modeLoad.h"

RadioPanel::RadioPanel(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids)
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

void RadioPanel::show(int)
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

RadioPanel::~RadioPanel()
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

void RadioPanel::check()
{
    try
    {
        debug("%s RADIO%i Verification requirements", PLUGIN_INFO, this->panelNumber);
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            upMode[item]->Check();
        for (int item = 0; item < RADIO_MODE_COUNT; item++)
            downMode[item]->Check();
        debug("%s RADIO%i Requirements good", PLUGIN_INFO, this->panelNumber);
        this->panelIsChecked = true;
    }
    catch (const std::exception &e)
    {
        this->panelIsLoader = false;
        debug("%s RADIO%i FATAL ERROR [%s]", PLUGIN_ERROR, this->panelNumber, e.what());
        this->show(33);
    }
}

void RadioPanel::Reload()
{
    if (!this->panelIsLoader)
        return;
    if (!this->panelIsChecked)
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
#ifdef DEBUG
        debug("%s RADIO%i SET LED", PLUGIN_DEBUG, this->panelNumber);
#endif
    }
}

void RadioPanel::readUSBData()
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

void RadioPanel::changePos()
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

void RadioPanel::rotate()
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

void RadioPanel::changeUpPos(int newPos)
{
#ifdef DEBUG
    debug("%s RADIO%i UP Activated", PLUGIN_DEBUG, this->panelNumber);
#endif
    this->upPanel = this->upMode[newPos];
    this->upPanel->Activated();
}

void RadioPanel::changeDownPos(int newPos)
{
#ifdef DEBUG
    debug("%s RADIO%i DOWN Activated", PLUGIN_DEBUG, this->panelNumber);
#endif
    this->downPanel = this->downMode[newPos];
    this->downPanel->Activated();
}

void RadioPanel::changeMode()
{
    // TOP ACT/STBY                    1           6           1       0x00 40 00
    if (this->rawCommand[1] & 0x40)
    {
        if (this->upPush->GetState() != 1)
        {
#ifdef DEBUG
            debug("%s RADIO%i UP PUSH", PLUGIN_DEBUG, this->panelNumber);
#endif
            this->upPanel->Push();
            this->upPush->SetState(1);
        }
    }
    else if (this->upPush->GetState() != 0)
    {
#ifdef DEBUG
        debug("%s RADIO%i UP RELEASE", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->upPanel->Release();
        this->upPush->SetState(0);
    }
    // BOTTOM ACT/STBY                 1           7           1       0x00 80 00
    if (this->rawCommand[1] & 0x80)
    {
        if (this->downPush->GetState() != 1)
        {
#ifdef DEBUG
            debug("%s RADIO%i DOWN PUSH", PLUGIN_DEBUG, this->panelNumber);
#endif
            this->downPanel->Push();
            this->downPush->SetState(1);
        }
    }
    else if (this->downPush->GetState() != 0)
    {
#ifdef DEBUG
        debug("%s RADIO%i DOWN RELEASE", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->downPanel->Release();
        this->downPush->SetState(0);
    }
}

void RadioPanel::Load(FileContent *config)
{
    debug("%s RADIO%i Loading", PLUGIN_INFO, this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "RADIO", this->panelNumber);
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->upMode[item] = LoadRadio(panelConfig, RadioButtonName[item]);
    this->upPanel = this->upMode[0];
    for (int item = 0; item < RADIO_MODE_COUNT; item++)
        this->downMode[item] = LoadRadio(panelConfig, RadioButtonName[item]);
    this->downPanel = this->downMode[0];
    this->panelIsLoader = true;
    this->panelIsChecked = false;
    delete panelConfig;
    debug("%s RADIO%i Download completion", PLUGIN_INFO, this->panelNumber);
}

void RadioPanel::shutdown()
{
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->SetOff();
    for (int i = 0; i < 4; i++)
        this->monitor[i / 2][i % 2]->Save(1 + 5 * i, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void RadioPanel::Clear()
{
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
