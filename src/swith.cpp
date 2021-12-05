
#include "swith.h"
#include <cstring>
#include "debug.h"
#include "swload.h"

SWPanel::SWPanel(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids)
{
    shutdown(CELL_ON_GREAN);
    // LED
    for (int item = 0; item < SW_LED_COUNT; item++)
        this->led[item] = new SingleLED("switch", uids, 0, item);
    // Button
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
        this->button[item] = new CustomRef("switch", uids, SWButtonDataRefName[item]);
}

SWPanel::~SWPanel()
{
    this->shutdown(CELL_OFF);
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
        delete this->button[item];
    for (int item = 0; item < SW_LED_COUNT; item++)
        delete this->led[item];
}

void SWPanel::shutdown(int collor)
{
    memcpy(this->rawDisplay, ZeroSWSetFeature, sizeof(ZeroSWSetFeature));
    SWUpdateLED(collor, collor, collor, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void SWPanel::Clear()
{
    this->panelIsLoader = false;
    this->panelIsChecked = false;
    for (int button = 0; button < SW_BUTTON_COUNT; button++)
    {
        for (SWAction *item : this->content[button])
            delete item;
        this->content[button].clear();
        this->button[button]->SetState(-1);
    }
    for (int item = 0; item < SW_LED_COUNT; item++)
        this->led[item]->Clear();
    shutdown(CELL_ON_YELLOW);
}

void SWPanel::Load(FileContent *config)
{
    debug("%s SWITH%i Loading", PLUGIN_INFO, this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "SWITCH", this->panelNumber);
    for (int ledID = 0; ledID < SW_LED_COUNT; ledID++)
    {
        FileContent *ledConfig = panelConfig->CreateConfigForButton(SWLedName[ledID]);
        for (FileContentLine *cmd : *ledConfig)
            this->led[ledID]->Load(cmd->key, cmd->value);
        delete ledConfig;
        this->led[ledID]->SetState(-1);
    }
    for (int buttonID = 0; buttonID < SW_BUTTON_COUNT; buttonID++)
    {
        FileContent *buttonConfig = panelConfig->CreateConfigForButton(SWButtonName[buttonID]);
        for (FileContentLine *cmd : *buttonConfig)
        {
#ifdef DEBUG
            debug("%s SW%i ADD %s/%s %s", PLUGIN_DEBUG, this->panelNumber, SWButtonName[buttonID], cmd->key, cmd->value);
#endif
            this->content[buttonID].insert(this->content[buttonID].begin(), 1,
                                           SWLoadAction(cmd->key, cmd->value));
        }
        delete buttonConfig;
        this->button[buttonID]->SetState(-1);
    }
    delete panelConfig;
    this->panelIsLoader = true;
    this->panelIsChecked = false;
    shutdown(CELL_OFF);
#ifdef LOWPERFORMANCE
    this->step = LOWPERFORMANCE_SKIP_STEP;
#endif
    debug("%s SWITH%i Download completion", PLUGIN_INFO, this->panelNumber);
}

void SWPanel::check()
{
    debug("%s SWITH%i Verification requirements", PLUGIN_INFO, this->panelNumber);
    try
    {
        for (int item = 0; item < SW_BUTTON_COUNT; item++)
            for (SWAction *row : this->content[item])
                row->Check();
        for (int item = 0; item < SW_LED_COUNT; item++)
            led[item]->Check();
        this->panelIsChecked = true;
        debug("%s SWITH%i Requirements good", PLUGIN_INFO, this->panelNumber);
    }
    catch (const std::exception &e)
    {
        this->panelIsLoader = false;
        debug("%s SWITH%i FATAL ERROR [%s]", PLUGIN_ERROR, this->panelNumber, e.what());
        shutdown(CELL_ON_RED);
    }
}

void SWPanel::Reload()
{
    if (!this->panelIsLoader)
        return;
    if (!this->panelIsChecked)
    {
        this->check();
        return;
    }
    this->readPosition();
    this->readDecode();
#ifdef LOWPERFORMANCE
    if (this->step++ < LOWPERFORMANCE_SKIP_STEP)
        return;
    this->step = 0;
#endif
    this->reloadLED();
}

void SWPanel::reloadLED()
{
    int status[SW_LED_COUNT];
    bool flag = false;
    for (int item = 0; item < SW_LED_COUNT; item++)
    {
        status[item] = this->led[item]->RealState();
        if (status[item] != this->led[item]->GetState())
            flag = true;
    }
    if (flag)
    {
        memcpy(this->rawDisplay, ZeroSWSetFeature, sizeof(ZeroSWSetFeature));
        SWUpdateLED(status[0], status[1], status[2], this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
        for (int item = 0; item < SW_LED_COUNT; item++)
            this->led[item]->SetState(status[item]);
#ifdef DEBUG
        debug("%s SW%i SET LED", PLUGIN_DEBUG, this->panelNumber);
#endif
    }
}

void SWPanel::readPosition()
{
#if (defined XPLANE11PLUGIN || defined USB)
    hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    int readStatus;
    do
    {
#if (defined XPLANE11PLUGIN || defined USB)
        readStatus = hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
#else
        readStatus = 0;
#endif
    } while (readStatus > 0);
}

void SWPanel::readDecode()
{
    bool new_status;
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
    {
        new_status = this->rawCommand[SWButtonBIT[item][0]] & SWButtonBIT[item][1];
        if ((new_status) && (this->button[item]->GetState() != 1))
        {
#ifdef DEBUG
            debug("%s SW%i ON %s", PLUGIN_DEBUG, this->panelNumber, SWButtonName[item]);
#endif
            this->button[item]->SetState(1);
            for (SWAction *button : this->content[item])
                button->On();
        }
        if ((!new_status) && (this->button[item]->GetState() != 0))
        {
#ifdef DEBUG
            debug("%s SW%i OFF %s", PLUGIN_DEBUG, this->panelNumber, SWButtonName[item]);
#endif
            this->button[item]->SetState(0);
            for (SWAction *button : this->content[item])
                button->Off();
        }
    }
}
