#include "swpush.h"

SWCommandPush::SWCommandPush(const char *lines)
{
    this->cmd = new XP11Command(lines);
}

SWCommandPush::~SWCommandPush()
{
    delete this->cmd;
}

void SWCommandPush::Check()
{
    this->cmd->Check();
}

void SWCommandPush::On()
{
    this->cmd->Begin();
}

void SWCommandPush::Off()
{
    this->cmd->End();
}
