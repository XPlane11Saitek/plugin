
#include "swcmd.h"

SWCommand::SWCommand(const char *lines)
{
    this->cmd = new XP11Command(lines);
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
    this->cmd->Once();
}

void SWCommand::Off()
{
    this->cmd->Once();
}
