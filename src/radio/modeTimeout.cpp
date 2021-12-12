
#include "modeTimeout.h"
#include <stdlib.h>
#include "debug.h"
#include <regex>

RadioModeTimeout::RadioModeTimeout(RadioMode *a, RadioMode *b, const char *param)
{
    this->a[0] = a;
    this->a[1] = b;
    std::cmatch query;
    std::regex regex("(\\d+)");
    if (std::regex_match(param, query, regex))
    {
        this->idleTimeout = std::atof(query[0].str().c_str());
        return;
    }
    throw Exception("%s Radio dual(\\d) incorrect/unexpected [%s]", PLUGIN_ERROR, param);
}

RadioModeTimeout::~RadioModeTimeout()
{
    delete this->a[0];
    delete this->a[1];
}

void RadioModeTimeout::Check()
{
    this->a[0]->Check();
    this->a[1]->Check();
}

void RadioModeTimeout::Show(Monitor *b[2])
{
    if ((this->mode == 0) && (difftime(time(0), this->lastUpdate) > this->idleTimeout))
    {
#ifdef DEBUG
        debug("%s RADIO TIMEOUT DETECT", PLUGIN_DEBUG);
#endif
        this->mode = 1;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
    this->a[this->mode]->Show(b);
}

void RadioModeTimeout::Push()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->Push();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}

void RadioModeTimeout::Release()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->Release();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}

void RadioModeTimeout::Activated()
{
    this->mode = 0;
    this->a[this->mode]->Activated();
    this->lastUpdate = time(0);
}

void RadioModeTimeout::BigUp()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->BigUp();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}

void RadioModeTimeout::BigDown()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->BigDown();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}

void RadioModeTimeout::SmallUp()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->SmallUp();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}

void RadioModeTimeout::SmallDown()
{
    this->lastUpdate = time(0);
    if (this->mode == 0)
        this->a[0]->SmallDown();
    else
    {
        this->mode = 0;
        this->a[this->mode]->Activated();
        this->lastUpdate = time(0);
    }
}
