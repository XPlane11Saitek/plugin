
#include "modeCMD.h"

RadioModeCMD::RadioModeCMD(RadioMode *obj, const char *line)
{
    this->left = obj;
    this->cmd = new XP11Command(line);
}

RadioModeCMD::~RadioModeCMD()
{
    delete this->left;
    delete this->cmd;
}

void RadioModeCMD::Check()
{
    this->left->Check();
    this->cmd->Check();
}

void RadioModeCMD::Show(Monitor *a[2])
{
    this->left->Show(a);
}

void RadioModeCMD::Activated()
{
    this->left->Activated();
}

void RadioModeCMD::Push()
{
    this->cmd->Once();
}

void RadioModeCMD::Release()
{
}

void RadioModeCMD::BigUp()
{
    this->left->BigUp();
}

void RadioModeCMD::BigDown()
{
    this->left->BigDown();
}

void RadioModeCMD::SmallUp()
{
    this->left->SmallUp();
}

void RadioModeCMD::SmallDown()
{
    this->left->SmallDown();
}
