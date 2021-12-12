
#include "modeShow.h"
#include "value.h"
#include <cstring>
#include <stdlib.h>
#include "data.h"
#include <regex>
#include "debug.h"
#include <iostream>

RadioModeSHOW::RadioModeSHOW(const char *value, const char *param)
{ // COM Setting
    std::cmatch query;
    if (std::regex_match(param, query, std::regex("(.*),ALL")))
    {
        this->com = XP11Value::New(value);
        this->displayMode = STConvert::New(query[1].str().c_str());
        this->allChanges = true;
        return;
    }
    this->com = XP11Value::New(value);
    this->displayMode = STConvert::New(param);
    this->allChanges = false;
    return;
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