
#include "modePush.h"

RadioModePush::RadioModePush(RadioMode *obj, const char *line)
{
    this->left = obj;
    this->cmd = new XP11Command(line);
}

RadioModePush::~RadioModePush()
{
    delete this->left;
    delete this->cmd;
}

void RadioModePush::Check()
{
    this->left->Check();
    this->cmd->Check();
}

void RadioModePush::Show(Monitor *a[2])
{
    this->left->Show(a);
}

void RadioModePush::Activated()
{
    this->left->Activated();
}

void RadioModePush::Push()
{
    this->cmd->Begin();
    this->left->Push();
}

void RadioModePush::Release()
{
    this->cmd->End();
    this->left->Release();
}

void RadioModePush::BigUp()
{
    this->left->BigUp();
}

void RadioModePush::BigDown()
{
    this->left->BigDown();
}

void RadioModePush::SmallUp()
{
    this->left->SmallUp();
}

void RadioModePush::SmallDown()
{
    this->left->SmallDown();
}
