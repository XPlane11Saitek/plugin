
#include "apRadio.h"
#include "debug.h"

#include <string>
#include <cstring>
#include <regex>

APModeRadio::APModeRadio()
{
    for (int mode = 0; mode < AP_RADIO_MODE_COUNT; mode++)
        this->modes[mode] = NULL;
    this->active = NULL;
    this->mode = 0;
}

APModeRadio::~APModeRadio()
{
    for (int button = 0; button < AP_RADIO_MODE_COUNT; button++)
        if (this->modes[button] != NULL)
            delete this->modes[button];
    this->active = NULL;
}

void APModeRadio::Check()
{
    for (int button = 0; button < AP_RADIO_MODE_COUNT; button++)
        if (this->modes[button] != NULL)
            this->modes[button]->Check();
}

void APModeRadio::swithto(int new_mode)
{
    if (this->modes[new_mode] != NULL)
    {
        this->mode = new_mode;
        this->active = this->modes[new_mode];
        this->active->Activated();
    }
}

void APModeRadio::Activate(apCaption *naming)
{
    this->active = NULL;
    this->swithto(0);
    naming->SetName(this->name);
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
        naming->SetLEDName(cell, ledName[cell]);
}

void APModeRadio::Show(Monitor *a[2], unsigned char &b)
{
    if (this->active == NULL)
    {
        a[0]->SetOff();
        a[1]->SetOff();
        b = 0;
    }
    else
    {
        this->active->Show(a);
        b = 1 << (this->mode + 1);
        if (this->isUpper)
            b += 1 << MultiAPR;
        else
            b += 1 << MultiREV;
    }
}

void APModeRadio::ButtonPush(int button)
{
    switch (button)
    {
    case MultiAP:
        if (this->active != NULL)
            this->active->Push();
        break;
    case MultiHDG:
    case MultiNAV:
    case MultiIAS:
    case MultiALT:
    case MultiVS:
        this->swithto(button - 1);
        break;
    case MultiAPR:
        this->isUpper = true;
        break;
    case MultiREV:
        this->isUpper = false;
        break;
    }
}

void APModeRadio::ButtonRelease(int button)
{
    switch (button)
    {
    case MultiAP:
        if (this->active != NULL)
            this->active->Release();
        break;
    }
}

void APModeRadio::RotateUp()
{
    if (this->active != NULL)
    {
        if (this->isUpper)
            this->active->BigUp();
        else
            this->active->SmallUp();
    }
}

void APModeRadio::RotateDown()
{
    if (this->active != NULL)
    {
        if (this->isUpper)
            this->active->BigDown();
        else
            this->active->SmallDown();
    }
}

void APModeRadio::Loader(int button, RadioMode *obj)
{
    this->modes[button - 1] = obj;
}

AP *APModeRadio::New(FileContent *config, const char *button)
{
    APModeRadio *rdo = new APModeRadio();
    if (config->IsParam(button, "NAME"))
        rdo->SetName(config->GetParam(button, "NAME"));
    for (int pos = 1; pos < AP_RADIO_MODE_COUNT + 1; pos++)
    {
        std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
        if (config->IsParam(newButton.c_str(), "NAME"))
            rdo->SetLedName(pos, config->GetParam(newButton.c_str(), "NAME"));
        if (config->IsParam(newButton.c_str(), "MODE"))
            rdo->Loader(pos, RadioMode::New(config, newButton.c_str()));
        else
            debug("SKIP MULTI PANEL %s", newButton.c_str());
    }
    return rdo;
}