
#include "swith.h"
#include <cstring>
#include "debug.h"
#include "sw.h"
#include "spec.h"
#include <cstdio>

SW::SW(hid_device *usbdev, const wchar_t *sn, int uids) : Panel(usbdev, sn, uids), SWForm(usbdev, sn, uids)
{
    // LED
    for (int item = 0; item < SW_LED_COUNT; item++)
        this->led[item] = new SingleLED("switch", uids, item);
    // Button
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
        this->button[item] = new CustomRef("switch", uids, SWButtonDataRefName[item]);
    set(CELL_ON_GREAN);
    if (usbdev == NULL)
    {
        memcpy(this->rawCommand, ZeroSWGetFeature, sizeof(ZeroSWGetFeature));
        this->rawCommand[SWButtonBIT[0][0]] += SWButtonBIT[0][1];
        this->rawCommand[SWButtonBIT[19][0]] += SWButtonBIT[19][1];
    }
}

SW::~SW()
{
    this->set(CELL_OFF);
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
        delete this->button[item];
    for (int item = 0; item < SW_LED_COUNT; item++)
        delete this->led[item];
}

void SW::set(int collor)
{
    memcpy(this->rawDisplay, ZeroSWSetFeature, sizeof(ZeroSWSetFeature));
    SWUpdateLED(collor, collor, collor, this->rawDisplay);
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void SW::Clear()
{
    this->state = init;
    for (int button = 0; button < SW_BUTTON_COUNT; button++)
    {
        for (SWAction *item : this->content[button])
            delete item;
        this->content[button].clear();
        this->button[button]->SetState(-1);
    }
    for (int item = 0; item < SW_LED_COUNT; item++)
        this->led[item]->Clear();
    for (int cell = 0; cell < SW_LED_COUNT; cell++)
        this->SetLedName(cell, "");
    for (int cell = 0; cell < SW_BUTTON_COUNT; cell++)
        this->SetButtonName(cell, "");
    set(CELL_ON_GREAN);
}

void SW::Load(FileContent *config)
{
    set(CELL_ON_YELLOW);
    info("SWITH%i Loading", this->panelNumber);
    for (int ledID = 0; ledID < SW_LED_COUNT; ledID++)
    {
        FileContent *ledConfig = config->CreateConfigForButton(SWLedName[ledID]);
        for (auto cmd : *ledConfig)
        {
            debug("SW%i LED ADD %s/%s %s", this->panelNumber, SWLedName[ledID], cmd->key, cmd->value);
            cmd->usage = true;
            if (!strcmp("NAME", cmd->key))
                this->SetLedName(ledID, cmd->value);
            else
                this->led[ledID]->Load(cmd->key, cmd->value);
        }
        delete ledConfig;
        this->led[ledID]->SetState(-1);
    }
    for (int buttonID = 0; buttonID < SW_BUTTON_COUNT; buttonID++)
    {
        FileContent *buttonConfig = config->CreateConfigForButton(SWButtonName[buttonID]);
        for (auto cmd : *buttonConfig)
        {
            debug("SW%i ADD %s/%s %s", this->panelNumber, SWButtonName[buttonID], cmd->key, cmd->value);
            cmd->usage = true;
            if (!strcmp("NAME", cmd->key))
                this->SetButtonName(buttonID, cmd->value);
            else
                this->content[buttonID].insert(this->content[buttonID].begin(), 1,
                                               SWAction::New(cmd->key, cmd->value));
        }
        delete buttonConfig;
        this->button[buttonID]->SetState(-1);
    }
    info("SWITH%i Download completion", this->panelNumber);
    this->state = loaded;
    set(CELL_OFF);
#ifdef LOWPERFORMANCE
    this->step = LOWPERFORMANCE;
#endif
}

void SW::check()
{
    info("SWITH%i Verification requirements", this->panelNumber);
    try
    {
        for (int item = 0; item < SW_BUTTON_COUNT; item++)
            for (SWAction *row : this->content[item])
                row->Check();
        for (int item = 0; item < SW_LED_COUNT; item++)
            led[item]->Check();
        this->state = run;
        info("SWITH%i Requirements good", this->panelNumber);
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("SWITH%i FATAL ERROR [%s]", this->panelNumber, e.what());
        set(CELL_ON_RED);
#ifndef XPLANE11PLUGIN
        throw Exception(e.what());
#endif
    }
}

void SW::Reload()
{
    if (this->state == init)
        return;
    if (this->state == loaded)
    {
        this->check();
        return;
    }

#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_set_nonblocking(this->panelUSBDevAddr, 1);
#endif
    int readStatus;
    do
    {
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            readStatus = hid_read(this->panelUSBDevAddr, this->rawCommand, sizeof(this->rawCommand));
        else
        {
            readStatus = 0;
        }
#else
        readStatus = 0;
#endif
    } while (readStatus > 0);

    bool new_status;
    for (int item = 0; item < SW_BUTTON_COUNT; item++)
    {
        new_status = this->rawCommand[SWButtonBIT[item][0]] & SWButtonBIT[item][1];
        if ((new_status) && (this->button[item]->GetState() != 1))
        {
            info("SW%i ON %s", this->panelNumber, SWButtonName[item]);
            this->button[item]->SetState(1);
            for (SWAction *button : this->content[item])
                button->On();
            this->SetButtonStatus(item, true);
        }
        if ((!new_status) && (this->button[item]->GetState() != 0))
        {
            info("SW%i OFF %s", this->panelNumber, SWButtonName[item]);
            this->button[item]->SetState(0);
            for (SWAction *button : this->content[item])
                button->Off();
            this->SetButtonStatus(item, false);
        }
    }
#ifdef LOWPERFORMANCE
    if (this->step++ < LOWPERFORMANCE)
        return;
    this->step = 0;
#endif

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
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
        for (int item = 0; item < SW_LED_COUNT; item++)
            this->led[item]->SetState(status[item]);
        for (int item = 0; item < SW_LED_COUNT; item++)
            this->SetLedStatus(item, status[item]);
        debug("SW%i SET LED", this->panelNumber);
    }
}

int SW::GetPanelID(char *buffer)
{
    sprintf(buffer, "SWITCH");
    return this->panelNumber;
}
