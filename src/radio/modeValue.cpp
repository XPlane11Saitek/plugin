
#include "modeValue.h"
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include "sources.h"
#include "dataLoad.h"

RadioModeValue::RadioModeValue(const char *dataref, const char *mode,
                               float big, float smol, float max, float min, bool round)
{
    this->displayMode = LoadDisplay(mode);
    this->bigValue = big;
    this->smallValue = smol;
    this->minValue = min;
    this->maxValue = max;
    this->roundFlag = round;
    this->com = LoadValue(dataref);
}

RadioModeValue::RadioModeValue(const char *dataref,
                               const char *mode,
                               float smol,
                               float max,
                               float min,
                               bool round) : RadioModeValue(dataref,
                                                            mode,
                                                            smol,
                                                            smol,
                                                            max,
                                                            min,
                                                            round) {}

RadioModeValue::~RadioModeValue()
{
    delete this->com;
}

void RadioModeValue::Check()
{
    this->com->Check();
}

void RadioModeValue::update(float inc)
{
    float value = this->com->GetValue();
    if ((this->minValue <= value + inc) && (value + inc <= this->maxValue))
    {
        value += inc;
        this->com->SetValue(value);
    }
    else if ((inc > 0) && (this->maxValue < value + inc) && (this->roundFlag))
    {
        value += (int)inc - (int)this->maxValue + (int)this->minValue;
        this->com->SetValue(value);
    }
    else if ((inc < 0) && (value + inc < this->minValue) && (this->roundFlag))
    {
        value += (int)inc + (int)this->maxValue - (int)this->minValue;
        this->com->SetValue(value);
    }
}

void RadioModeValue::Show(Monitor *a[2])
{
    a[0]->SetOff();
    a[1]->SetValue(this->displayMode, this->com->GetValue());
}

void RadioModeValue::Push() {}

void RadioModeValue::Release() {}

void RadioModeValue::Activated() {}

void RadioModeValue::BigUp()
{
    this->update(this->bigValue);
}

void RadioModeValue::BigDown()
{
    this->update(-1 * this->bigValue);
}

void RadioModeValue::SmallUp()
{
    this->update(this->smallValue);
}

void RadioModeValue::SmallDown()
{
    this->update(-1 * this->smallValue);
}