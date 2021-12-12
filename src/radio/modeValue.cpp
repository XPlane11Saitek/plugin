
#include "modeValue.h"

#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <regex>
#include "debug.h"
#include <iostream>

RadioModeValue::RadioModeValue(const char *dataref, const char *param)
{
    std::cmatch query;
    std::regex regex("(.*),(.*),(.*),(.*),(.*),(.*)");
    if (std::regex_search(param, query, regex))
    {
        this->com = XP11Value::New(dataref);
        this->smallValue = this->load(query[1].str().c_str());
        this->bigValue = this->load(query[2].str().c_str());
        this->minValue = this->load(query[3].str().c_str());
        this->maxValue = this->load(query[4].str().c_str());
        this->roundFlag = !strcmp("ROUND", query[5].str().c_str());
        this->displayMode = STConvert::New(query[6].str().c_str());
        return;
    }
    throw Exception("%s Radio value incorrect/unexpected line [%s]", PLUGIN_ERROR, param);
}

float RadioModeValue::load(const char *param)
{
    std::cmatch query;
    std::regex regex("(\\s+)?(-?\\d+(\\.\\d+)?)(\\s+)?");
    if (std::regex_search(param, query, regex))
        return std::atof(query[2].str().c_str());
    throw Exception("%s Radio value/float incorrect/unexpected line [%s]", PLUGIN_ERROR, param);
}

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
        return;
    }
    if ((inc > 0) && (this->maxValue < value + inc) && (this->roundFlag))
    {
        value += (int)inc - (int)this->maxValue + (int)this->minValue;
        this->com->SetValue(value);
        return;
    }
    if ((inc < 0) && (value + inc < this->minValue) && (this->roundFlag))
    {
        value += (int)inc + (int)this->maxValue - (int)this->minValue;
        this->com->SetValue(value);
        return;
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