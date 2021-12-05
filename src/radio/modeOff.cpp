
#include "modeOff.h"

RadioModeOFF::RadioModeOFF() {}

RadioModeOFF::~RadioModeOFF() {}

void RadioModeOFF::Show(Monitor *a[2])
{
    a[0]->SetOff();
    a[1]->SetOff();
}

void RadioModeOFF::Activated() {}

void RadioModeOFF::Check() {}
