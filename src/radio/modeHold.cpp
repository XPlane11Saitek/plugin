
#include "modeHold.h"
#include "command.h"
#include <stdlib.h>
#include "debug.h"
#include <regex>

RadioModeHold::RadioModeHold(RadioMode *obj, const char *line)
{
    this->left = obj;
    std::cmatch query;
    std::regex regex("(.*),(\\d+)");
    if (std::regex_search(line, query, regex))
    {
        this->cmd = new XP11Command(query[1].str().c_str());
        this->presTimeout = std::atof(query[2].str().c_str());
        return;
    }
    throw Exception("%s Radio value incorrect/unexpected line [%s]", PLUGIN_ERROR, line);
}

RadioModeHold::~RadioModeHold()
{
    delete this->left;
    delete this->cmd;
}

void RadioModeHold::Check()
{
    this->left->Check();
    this->cmd->Check();
}

void RadioModeHold::Show(Monitor *a[2])
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

void RadioModeHold::Activated()
{
    this->left->Activated();
    this->updateTime();
    this->isPush = false;
    this->isPushLong = false;
}

void RadioModeHold::Push()
{
    this->updateTime();
    this->isPush = true;
}

void RadioModeHold::Release()
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

void RadioModeHold::BigUp()
{
    this->left->BigUp();
}

void RadioModeHold::BigDown()
{
    this->left->BigDown();
}

void RadioModeHold::SmallUp()
{
    this->left->SmallUp();
}

void RadioModeHold::SmallDown()
{
    this->left->SmallDown();
}

void RadioModeHold::updateTime()
{
    this->lastUpdate = time(0);
}

bool RadioModeHold::isPressLong()
{
    return difftime(time(0), this->lastUpdate) >= this->presTimeout;
}
