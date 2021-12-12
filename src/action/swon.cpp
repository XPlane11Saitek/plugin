
#include "swon.h"

SWOn::SWOn(SWAction *data)
{
    this->cmd = data;
}

SWOn::~SWOn()
{
    delete this->cmd;
}

void SWOn::Check()
{
    this->cmd->Check();
}

void SWOn::On()
{
    this->cmd->On();
}

void SWOn::Off() {}
