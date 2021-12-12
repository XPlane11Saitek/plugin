

#include "modeExec.h"

RadioModeExec::RadioModeExec(RadioMode *obj, const char *line)
{
    this->left = obj;
    this->cmd = new XP11Command(line);
}

RadioModeExec::~RadioModeExec()
{
    delete this->left;
    delete this->cmd;
}

void RadioModeExec::Check()
{
    this->left->Check();
    this->cmd->Check();
}

void RadioModeExec::Show(Monitor *a[2])
{
    this->left->Show(a);
}

void RadioModeExec::Activated()
{
    this->left->Activated();
}

void RadioModeExec::Push()
{
    this->cmd->Once();
}

void RadioModeExec::Release() {}

void RadioModeExec::BigUp()
{
    this->left->BigUp();
}

void RadioModeExec::BigDown()
{
    this->left->BigDown();
}

void RadioModeExec::SmallUp()
{
    this->left->SmallUp();
}

void RadioModeExec::SmallDown()
{
    this->left->SmallDown();
}
