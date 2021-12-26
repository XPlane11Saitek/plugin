
#include "bip.h"
#include "debug.h"
#include <string>

BIP::BIP(hid_device *usbdev, const wchar_t *sn, int number) : Panel(usbdev, sn, number)
{
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            this->led[row][colum] = new SingleLED("bip", number, row, colum);

#if (defined XPLANE11PLUGIN || defined USB)
    this->panelUSBDevBIP = hid_open(0x6a3, 0xb4e, this->panelSN);
    if (this->panelUSBDevBIP == NULL)
    {
        debug("BIP%i Bad pointer to the address (BIP/connectUSB)", this->panelNumber);
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
    this->state = init;
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            this->led[row][colum]->Clear();
}

void BIP::Load(FileContent *config)
{
    info("BIP%i Loading", this->panelNumber);
    FileContent *panelConfig = config->CreateConfigForPanel(
        "BIP", this->panelNumber);
    FileContent *ledConfig = panelConfig->CreateConfigForButton("-1:-1");
    for (auto cmd : *ledConfig)
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
            {
                debug("BIP%i LED ADD %i:%i[%s] %s", this->panelNumber, row, colum, cmd->key, cmd->value);
                cmd->usage = true;
                this->led[row][colum]->Load(cmd->key, cmd->value);
            }
    delete ledConfig;
    for (int row = 0; row < BIP_CELL_ROW; row++)
        for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
        {
            ledConfig = panelConfig->CreateConfigForButton(
                (std::to_string(row) + ":" + std::to_string(colum)).c_str());
            for (auto cmd : *ledConfig)
            {
                debug("BIP%i ADD %i:%i[%s] %s", this->panelNumber, row, colum, cmd->key, cmd->value);
                cmd->usage = true;
                this->led[row][colum]->Load(cmd->key, cmd->value);
            }
            this->led[row][colum]->SetState(-1);
            delete ledConfig;
        }
    panelConfig->CheckALLUsage();
    delete panelConfig;
    this->state = loaded;
#ifdef LOWPERFORMANCE
    this->step = LOWPERFORMANCE + 1;
#endif
    this->shutdown(CELL_OFF);
    info("BIP%i Download completion", this->panelNumber);
}

void BIP::check()
{
    info("BIP%i Verification requirements", this->panelNumber);
    try
    {
        for (int row = 0; row < BIP_CELL_ROW; row++)
            for (int colum = 0; colum < BIP_CELL_COLUM; colum++)
                this->led[row][colum]->Check();
        info("BIP%i Requirements good", this->panelNumber);
        this->state = run;
    }
    catch (const std::exception &e)
    {
        this->state = init;
        warning("BIP%i FATAL ERROR[%s]", this->panelNumber, e.what());
        this->shutdown(CELL_ON_RED);
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
        debug("BIP%i SET LED", this->panelNumber);
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
