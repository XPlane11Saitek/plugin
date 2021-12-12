
#include "swoff.h"

SWOff::SWOff(SWAction *data)
{
    this->cmd = data;
}

SWOff::~SWOff()
{
    delete this->cmd;
}

void SWOff::Check()
{
    this->cmd->Check();
}

void SWOff::On() {}

void SWOff::Off()
{
    this->cmd->Off();
}
