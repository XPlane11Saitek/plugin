
#include "swcmd.h"

SWCommand::SWCommand(bool isOn, const char *lines)
{
    this->cmd = new XP11Command(lines);
    this->flag = isOn;
}

SWCommand::~SWCommand()
{
    delete this->cmd;
}

void SWCommand::Check()
{
    this->cmd->Check();
}

void SWCommand::On()
{
    if (this->flag)
        this->cmd->Once();
}

void SWCommand::Off()
{
    if (!this->flag)
        this->cmd->Once();
}
