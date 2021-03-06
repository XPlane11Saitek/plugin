
#include "apDisplay.h"
#include "debug.h"
#include "rangeLoader.h"

#include <string>
#include <cstring>
#include <regex>

APModeDisplay::APModeDisplay()
{
    for (int button = 0; button < MULTI_BUTTON_LOADER; button++)
        this->modes[button] = NULL;
    for (int led = 0; led < MULTI_LED_COUNT; led++)
        this->value[led] = NULL;
    this->active = NULL;
}

APModeDisplay::~APModeDisplay()
{
    for (int button = 0; button < MULTI_BUTTON_LOADER; button++)
        if (this->modes[button] != NULL)
            delete this->modes[button];
    for (int led = 0; led < MULTI_LED_COUNT; led++)
        if (this->value[led] != NULL)
            delete this->value[led];
    this->active = NULL;
}

void APModeDisplay::Check()
{
    for (int button = 0; button < MULTI_BUTTON_LOADER; button++)
        if (this->modes[button] != NULL)
            this->modes[button]->Check();
    for (int led = 0; led < MULTI_LED_COUNT; led++)
        if (this->value[led] != NULL)
            this->value[led]->Check();
}

bool APModeDisplay::swithto(int new_mode)
{
    if ((this->modes[new_mode] != NULL) && (this->active != this->modes[new_mode]))
    {
        this->active = this->modes[new_mode];
        this->active->Activated();
        return true;
    };
    return false;
}

void APModeDisplay::Activate(apCaption *naming)
{
    this->swithto(0);
    naming->SetName(this->name);
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
        naming->SetLEDName(cell, ledName[cell]);
}

void APModeDisplay::Show(Monitor *a[2], unsigned char &b)
{
    if (this->active == NULL)
    {
        a[0]->SetOff();
        a[1]->SetOff();
    }
    else
        this->active->Show(a);
    b = 0;
    for (int led = 0; led < MULTI_LED_COUNT; led++)
        if (this->value[led] != NULL)
            if (this->value[led]->IsValueInRange())
                b += 1 << led;
}

void APModeDisplay::ButtonPush(int button)
{
    if (this->swithto(button))
        // return
        (void)true;
    if (this->active != NULL)
        this->active->Push();
}

void APModeDisplay::ButtonRelease(int button)
{
    if (this->swithto(button))
        // return
        (void)true;
    if (this->active != NULL)
        this->active->Release();
}

void APModeDisplay::RotateUp()
{
    if (this->active != NULL)
        this->active->SmallUp();
}

void APModeDisplay::RotateDown()
{
    if (this->active != NULL)
        this->active->SmallDown();
}

void APModeDisplay::LoaderMode(int button, RadioMode *obj)
{
    this->modes[button] = obj;
}

void APModeDisplay::LoaderRange(int button, XPlaneRange *obj)
{
    this->value[button] = obj;
}

AP *APModeDisplay::New(FileContent *config, const char *button)
{
    APModeDisplay *dsp = new APModeDisplay();
    if (config->IsParam(button, "NAME"))
        dsp->SetName(config->GetParam(button, "NAME"));
    for (int pos = 0; pos < MULTI_LED_COUNT; pos++)
    {
        std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
        if (config->IsParam(newButton.c_str(), "NAME"))
            dsp->SetLedName(pos, config->GetParam(newButton.c_str(), "NAME"));
        if (config->IsParam(newButton.c_str(), "LED"))
            dsp->LoaderRange(pos, LoadRange(config->GetParam(newButton.c_str(), "LED")));
        else
            debug("SKIP MULTI PANEL LED %s", newButton.c_str());
    }
    for (int pos = 0; pos < MULTI_BUTTON_LOADER; pos++)
    {
        std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
        if (config->IsParam(newButton.c_str(), "MODE"))
            dsp->LoaderMode(pos, RadioMode::New(config, newButton.c_str()));
        else
            debug("SKIP MULTI PANEL %s", newButton.c_str());
    }
    return dsp;
}