
#include "modeDual.h"
#include <stdlib.h>
#include "debug.h"

RadioModeDUAL::RadioModeDUAL(RadioMode *a, RadioMode *c, int timeout)
{
    this->a[0] = a;
    this->a[1] = c;
    this->presTimeout = timeout;
}

RadioModeDUAL::~RadioModeDUAL()
{
    delete this->a[0];
    delete this->a[1];
}

void RadioModeDUAL::Check()
{
    this->a[0]->Check();
    this->a[1]->Check();
}

void RadioModeDUAL::switchTo(int newMode)
{
    this->mode = newMode;
    this->a[this->mode]->Activated();
    this->updateTime();
}

void RadioModeDUAL::updateTime()
{
    this->lastUpdate = time(0);
}

bool RadioModeDUAL::isPressLong()
{
    return difftime(time(0), this->lastUpdate) >= this->presTimeout;
}

void RadioModeDUAL::Show(Monitor *b[2])
{
    if ((this->mode == 0) && (this->isPush) && (this->isPressLong()) && (!this->isPushLong))
    {
#ifdef DEBUG
        debug("%s RADIO LONG PRESS DETECT", PLUGIN_DEBUG);
#endif
        this->isPushLong = true;
        this->switchTo(1);
    }
    if ((this->mode == 1) && (this->isPush) && (this->isPressLong()) && (!this->isPushLong))
    {
#ifdef DEBUG
        debug("%s RADIO LONG PRESS DETECT", PLUGIN_DEBUG);
#endif
        this->isPushLong = true;
        this->switchTo(0);
    }
    this->a[this->mode]->Show(b);
}

void RadioModeDUAL::Push()
{
    this->updateTime();
    this->isPush = true;
}

void RadioModeDUAL::Release()
{
    this->isPush = false;
    this->updateTime();
    if (this->isPushLong)
    {
        // Long Push release
    }
    else
    {
        this->a[this->mode]->Push();
        this->a[this->mode]->Release();
    }
    this->isPushLong = false;
}

void RadioModeDUAL::Activated()
{
    this->switchTo(0);
    this->isPush = false;
    this->isPushLong = false;
}

void RadioModeDUAL::BigUp()
{
    this->updateTime();
    this->a[this->mode]->BigUp();
}

void RadioModeDUAL::BigDown()
{
    this->updateTime();
    this->a[this->mode]->BigDown();
}

void RadioModeDUAL::SmallUp()
{
    this->updateTime();
    this->a[this->mode]->SmallUp();
}

void RadioModeDUAL::SmallDown()
{
    this->updateTime();
    this->a[this->mode]->SmallDown();
}
