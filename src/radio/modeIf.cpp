
#include "modeIf.h"
#include "rangeLoader.h"

RadioModeIF::RadioModeIF(RadioMode *left, RadioMode *right, const char *raw)
{
    this->a[0] = left;
    this->a[1] = right;
    this->cmd = LoadRange(raw);
}

RadioModeIF::~RadioModeIF()
{
    delete this->a[0];
    delete this->a[1];
    delete this->cmd;
}

void RadioModeIF::Check()
{
    this->a[0]->Check();
    this->a[1]->Check();
    this->cmd->Check();
}

void RadioModeIF::swithTo(int newMode)
{
    this->mode = newMode;
    this->a[this->mode]->Activated();
}

int RadioModeIF::getMode()
{
    if (this->cmd->IsValueInRange())
        return 1;
    return 0;
}

void RadioModeIF::Show(Monitor *a[2])
{
    int newMode = this->getMode();
    if (this->mode != newMode)
    {
        this->swithTo(newMode);
    }
    this->a[this->mode]->Show(a);
}

void RadioModeIF::Push()
{
    this->a[this->mode]->Push();
}

void RadioModeIF::Release()
{
    this->a[this->mode]->Release();
}

void RadioModeIF::Activated()
{
    int newMode = this->getMode();
    if (this->mode != newMode)
        this->swithTo(newMode);
    this->a[this->mode]->Activated();
}

void RadioModeIF::BigUp()
{
    this->a[this->mode]->BigUp();
}

void RadioModeIF::BigDown()
{
    this->a[this->mode]->BigDown();
}

void RadioModeIF::SmallUp()
{
    this->a[this->mode]->SmallUp();
}

void RadioModeIF::SmallDown()
{
    this->a[this->mode]->SmallDown();
}
