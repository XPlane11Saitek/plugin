
#include "apOff.h"

APOff::APOff() {}

APOff::~APOff() {}

void APOff::Check() {}

void APOff::Activate() {}

void APOff::Show(Monitor *display[2], unsigned char &b)
{
    b = 0;
    display[0]->SetOff();
    display[1]->SetOff();
}
