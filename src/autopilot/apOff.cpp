
#include "apOff.h"

APOff::APOff() {}

APOff::~APOff() {}

void APOff::Check() {}

void APOff::Activate(apCaption *naming)
{
    naming->SetName("");
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
        naming->SetLEDName(cell, "");
}

void APOff::Show(Monitor *display[2], unsigned char &b)
{
    b = 0;
    display[0]->SetOff();
    display[1]->SetOff();
}
