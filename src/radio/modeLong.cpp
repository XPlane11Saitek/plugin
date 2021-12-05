
#include "modeLong.h"
#include "command.h"
#include <stdlib.h>
#include "debug.h"

RadioModeLong::RadioModeLong(RadioMode *obj, const char *line, int timeout)
{
    this->left = obj;
    this->cmd = new XP11Command(line);
    this->presTimeout = timeout;
}

RadioModeLong::~RadioModeLong()
{
    delete this->left;
    delete this->cmd;
}

void RadioModeLong::Check()
{
    this->left->Check();
    this->cmd->Check();
}

void RadioModeLong::Show(Monitor *a[2])
{
    if ((this->isPush) && (this->isPressLong()) && (!this->isPushLong))
    {
#ifdef DEBUG
        debug("%s RADIO LONG PRESS DETECT", PLUGIN_DEBUG);
#endif
        this->cmd->Once();
        this->isPushLong = true;
    };
    this->left->Show(a);
}

void RadioModeLong::Activated()
{
    this->left->Activated();
    this->updateTime();
    this->isPush = false;
    this->isPushLong = false;
}

void RadioModeLong::Push()
{
    this->updateTime();
    this->isPush = true;
}

void RadioModeLong::Release()
{
    this->updateTime();
    this->isPush = false;
    if (this->isPushLong)
    {
        // Long Push release
    }
    else
    {
        this->left->Push();
        this->left->Release();
    }
    this->isPushLong = false;
}

void RadioModeLong::BigUp()
{
    this->left->BigUp();
}

void RadioModeLong::BigDown()
{
    this->left->BigDown();
}

void RadioModeLong::SmallUp()
{
    this->left->SmallUp();
}

void RadioModeLong::SmallDown()
{
    this->left->SmallDown();
}

void RadioModeLong::updateTime()
{
    this->lastUpdate = time(0);
}

bool RadioModeLong::isPressLong()
{
    return difftime(time(0), this->lastUpdate) >= this->presTimeout;
}
