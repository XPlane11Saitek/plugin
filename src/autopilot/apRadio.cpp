
#include "apRadio.h"

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

void APModeRadio::Activate()
{
    this->active = NULL;
    this->swithto(0);
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
