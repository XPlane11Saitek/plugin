
#include "modeShow.h"
#include "sources.h"
#include <cstring>
#include <stdlib.h>
#include "dataLoad.h"

RadioModeSHOW::RadioModeSHOW(const char *value, const char *mode, bool allChange)
{ // COM Setting
    this->com = LoadValue(value);
    this->displayMode = LoadDisplay(mode);
    this->allChanges = allChange;
}

RadioModeSHOW::~RadioModeSHOW()
{
    delete this->com;
}

void RadioModeSHOW::Check()
{
    this->com->Check();
}

void RadioModeSHOW::Show(Monitor *a[2])
{
    if (!this->allChanges)
    {
        if (difftime(time(0), this->lastUpdate) < 1)
        {
            a[0]->SetOff();
            a[1]->SetValue(this->displayMode, this->state);
        }
        else
        {
            this->state = this->com->GetValue();
            a[0]->SetOff();
            a[1]->SetValue(this->displayMode, this->state);
            this->lastUpdate = time(0);
        }
    }
    else
    {
        a[0]->SetOff();
        a[1]->SetValue(this->displayMode, this->com->GetValue());
        this->lastUpdate = time(0);
    }
}

void RadioModeSHOW::Push() {}

void RadioModeSHOW::Release() {}

void RadioModeSHOW::Activated()
{
    this->lastUpdate = time(0);
    this->state = this->com->GetValue();
}

void RadioModeSHOW::BigUp() {}

void RadioModeSHOW::BigDown() {}

void RadioModeSHOW::SmallUp() {}

void RadioModeSHOW::SmallDown() {}