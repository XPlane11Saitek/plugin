
#include "bip.h"
#include "debug.h"
#include <string>

BIP::BIP(hid_device *usbdev, const wchar_t *sn, int number) : Panel(usbdev, sn, number)
{
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            this->led[row][colum] = new SingleLED("bip", number, row, colum);
            // BIP::connectUSB()
#if (defined XPLANE11PLUGIN || defined USB)
    this->panelUSBDevBIP = hid_open(0x6a3, 0xb4e, this->panelSN);
    if (this->panelUSBDevBIP == NULL)
    {
        debug("%s BIP%i Bad pointer to the address (BIP/connectUSB)", PLUGIN_ERROR, this->panelNumber);
        this->panelUSBDevBIP = usbdev;
    }
    hid_set_nonblocking(usbdev, 1);
#else
    (void)panelUSBDevBIP;
#endif
    this->shutdown(CELL_ON_GREAN);
}

BIP::~BIP()
{ //Destroy Menu
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            delete this->led[row][colum];
    this->shutdown(CELL_OFF);
}

void BIP::shutdown(int color)
{
    memcpy(this->rawDisplay, ZeroBIPSetFeatureInit, sizeof(ZeroBIPSetFeatureInit));
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevBIP, this->rawDisplay, sizeof(this->rawDisplay));
#endif
    memcpy(this->rawDisplay, ZeroBIPSetFeatureShow, sizeof(ZeroBIPSetFeatureShow));
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            BIPSetCollorBit(row, colum, color, this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
    hid_send_feature_report(this->panelUSBDevBIP, this->rawDisplay, sizeof(this->rawDisplay));
#endif
}

void BIP::Clear()
{
    this->shutdown(CELL_ON_GREAN);
    this->panelIsLoader = false;
    this->panelIsChecked = false;
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            this->led[row][colum]->Clear();
}

void BIP::Load(FileContent *config)
{
    debug("%s BIP%i Loading", PLUGIN_INFO, this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "BIP", this->panelNumber);
    FileContent *ledConfig = panelConfig->CreateConfigForButton("-1:-1");
    for (FileContentLine *cmd : *ledConfig)
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            {
#ifdef DEBUG
                debug("%s BIP%i LED ADD %i:%i[%s] %s", PLUGIN_DEBUG, this->panelNumber, row, colum, cmd->key, cmd->value);
#endif
                cmd->usage = true;
                this->led[row][colum]->Load(cmd->key, cmd->value);
            }
    delete ledConfig;
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
        {
            ledConfig = panelConfig->CreateConfigForButton(
                (std::to_string(row) + ":" + std::to_string(colum)).c_str());
            for (FileContentLine *cmd : *ledConfig)
            {
#ifdef DEBUG
                debug("%s BIP%i ADD %i:%i[%s] %s", PLUGIN_DEBUG, this->panelNumber, row, colum, cmd->key, cmd->value);
#endif
                cmd->usage = true;
                this->led[row][colum]->Load(cmd->key, cmd->value);
            }
            this->led[row][colum]->SetState(-1);
            delete ledConfig;
        }
    panelConfig->CheckALLUsage();
    delete panelConfig;
    this->panelIsLoader = true;
    this->panelIsChecked = false;
#ifdef LOWPERFORMANCE
    this->step = LOWPERFORMANCE_SKIP_STEP + 1;
#endif
    this->shutdown(CELL_OFF);
    debug("%s BIP%i Download completion", PLUGIN_INFO, this->panelNumber);
}

void BIP::check()
{
    debug("%s BIP%i Verification requirements", PLUGIN_INFO, this->panelNumber);
    try
    {
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
                this->led[row][colum]->Check();
        debug("%s BIP%i Requirements good", PLUGIN_INFO, this->panelNumber);
        this->panelIsChecked = true;
    }
    catch (const std::exception &e)
    {
        this->panelIsLoader = false;
        debug("%s BIP%i FATAL ERROR[%s]", PLUGIN_ERROR, this->panelNumber, e.what());
        this->shutdown(CELL_ON_RED);
#ifndef XPLANE11PLUGIN
        throw Exception(e.what());
#endif
    }
}

void BIP::Reload()
{
    if (!this->panelIsLoader)
        return;
    if (!this->panelIsChecked)
    {
        this->check();
        return;
    }
#ifdef LOWPERFORMANCE
    if (this->step++ < LOWPERFORMANCE_SKIP_STEP)
        return;
    this->step = 0;
#endif
    BIPState new_state;
    this->getState(new_state);
    if (this->needUpdate(new_state))
    {
        memcpy(this->rawDisplay, ZeroBIPSetFeatureShow, sizeof(ZeroBIPSetFeatureShow));
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
                BIPSetCollorBit(row, colum, new_state[row][colum], this->rawDisplay);
#if (defined XPLANE11PLUGIN || defined USB)
        hid_send_feature_report(this->panelUSBDevBIP, this->rawDisplay, sizeof(this->rawDisplay));
#endif
#ifdef DEBUG
        debug("%s BIP%i SET LED", PLUGIN_DEBUG, this->panelNumber);
#endif
        this->saveState(new_state);
    }
}

void BIP::getState(BIPState &new_state)
{
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            new_state[row][colum] = this->led[row][colum]->RealState();
}

bool BIP::needUpdate(BIPState new_state)
{
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            if (new_state[row][colum] != this->led[row][colum]->GetState())
                return true;
    return false;
}

void BIP::saveState(BIPState new_state)
{
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            this->led[row][colum]->SetState(new_state[row][colum]);
}
