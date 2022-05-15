// -*- lsst-c++ -*-
/** Ukraine:
 * Реалізаця класу підтримки BIP .
 *
 * @file bip.h
 * @brief BIP Header file
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */
#include "bip.h"
#include "debug.h"
#include <string>
#include <cstdio>

BIP::BIP(hid_device *usbdev, const wchar_t *sn, int number) : Panel(usbdev, sn, number), BIPForm(usbdev, sn, number)
{
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        this->led[item] = new SingleLED("bip", number, item);

#if (defined XPLANE11PLUGIN)
    if (usbdev != NULL)
    {
        this->panelUSBDevAddr = hid_open(0x6a3, 0xb4e, this->panelSN);
        if (this->panelUSBDevAddr == NULL)
        {
            debug("BIP%i Bad pointer to the address (BIP/connectUSB)", this->panelNumber);
            this->panelUSBDevAddr = usbdev;
        }
        hid_set_nonblocking(usbdev, 1);
    }
    else
        warning("BIP%i is Virtual panel", number);
#endif
    this->set(CELL_ON_GREAN);
}

BIP::~BIP()
{
    this->set(CELL_OFF);
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        delete this->led[item];
}

void BIP::set(int color)
{
    memcpy(this->rawDisplay, ZeroBIPSetFeatureInit, sizeof(ZeroBIPSetFeatureInit));
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
    memcpy(this->rawDisplay, ZeroBIPSetFeatureShow, sizeof(ZeroBIPSetFeatureShow));
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        BIPSetCollorBit(item, color, this->rawDisplay);
#if (defined XPLANE11PLUGIN)
    if (this->panelUSBDevAddr != NULL)
        hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void BIP::Clear()
{
    this->set(CELL_ON_GREAN);
    this->state = init;
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        this->led[item]->Clear();
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        this->SetFormName(item, "");
}

void BIP::Load(FileContent *config)
{
    info("BIP%i Loading", this->panelNumber);
    this->set(CELL_ON_YELLOW);
    FileContent *ledConfig = config->CreateConfigForButton("-1:-1");
    for (auto cmd : *ledConfig)
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            {
                debug("BIP%i LED ADD %i:%i[%s] %s", this->panelNumber, row, colum, cmd->key, cmd->value);
                cmd->usage = true;
                this->led[row * BIP_CELL_COLUM + colum]->Load(cmd->key, cmd->value);
            }
    delete ledConfig;
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
        {
            ledConfig = config->CreateConfigForButton(
                (std::to_string(row) + ":" + std::to_string(colum)).c_str());
            for (auto cmd : *ledConfig)
            {
                debug("BIP%i ADD %i:%i[%s] %s", this->panelNumber, row, colum, cmd->key, cmd->value);
                cmd->usage = true;
                if (!strcmp("NAME", cmd->key))
                    this->SetFormName(row * BIP_CELL_COLUM + colum, cmd->value);
                else
                    this->led[row * BIP_CELL_COLUM + colum]->Load(cmd->key, cmd->value);
            }
            this->led[row * BIP_CELL_COLUM + colum]->SetState(-1);
            delete ledConfig;
        }
    this->state = loaded;
#ifdef LOWPERFORMANCE
    this->step = LOWPERFORMANCE + 1;
#endif
    this->set(CELL_OFF);
    info("BIP%i Download completion", this->panelNumber);
}

void BIP::check()
{
    info("BIP%i Verification requirements", this->panelNumber);
    try
    {
        for (int item = 0; item < BIP_CELL_COUNT; item++)
            this->led[item]->Check();
        info("BIP%i Requirements good", this->panelNumber);
        this->state = run;
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("BIP%i FATAL ERROR[%s]", this->panelNumber, e.what());
        this->set(CELL_ON_RED);
#ifndef XPLANE11PLUGIN
        throw Exception(e.what());
#endif
    }
}

void BIP::Reload()
{
    if (this->state == init)
        return;
    if (this->state == loaded)
    {
        this->check();
        return;
    }
#ifdef LOWPERFORMANCE
    if (this->step++ < LOWPERFORMANCE)
        return;
    this->step = 0;
#endif

    BIPState new_state;
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        new_state[item] = this->led[item]->RealState();

    bool flag = false;
    for (int item = 0; item < BIP_CELL_COUNT; item++)
        if (new_state[item] != this->led[item]->GetState())
            flag = true;

    if (flag)
    {
        memcpy(this->rawDisplay, ZeroBIPSetFeatureShow, sizeof(ZeroBIPSetFeatureShow));
        for (int item = 0; item < BIP_CELL_COUNT; item++)
            BIPSetCollorBit(item, new_state[item], this->rawDisplay);
#if (defined XPLANE11PLUGIN)
        if (this->panelUSBDevAddr != NULL)
            hid_send_feature_report(this->panelUSBDevAddr, this->rawDisplay, sizeof(this->rawDisplay));
#endif
        debug("BIP%i SET LED", this->panelNumber);
        for (int item = 0; item < BIP_CELL_COUNT; item++)
            this->led[item]->SetState(new_state[item]);
        for (int item = 0; item < BIP_CELL_COUNT; item++)
            this->SetFormCollor(item, new_state[item]);
    }
}

int BIP::GetPanelID(char *buffer)
{
    sprintf(buffer, "BIP");
    return this->panelNumber;
}
