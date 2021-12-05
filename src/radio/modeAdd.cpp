
#include "modeAdd.h"

RadioModeADD::RadioModeADD(RadioMode *b, RadioMode *a, bool isLock, bool isRadioMode)
{
    this->a[0] = a;
    this->a[1] = b;
    this->leftA = new Monitor(isRadioMode);
    this->leftB = new Monitor(isRadioMode);
    this->isLockSW = isLock;
    this->isRadio = isRadioMode;
}

RadioModeADD::~RadioModeADD()
{
    delete this->a[0];
    delete this->a[1];
}

void RadioModeADD::Check()
{
    this->a[0]->Check();
    this->a[1]->Check();
}

void RadioModeADD::Show(Monitor *b[2])
{
    Monitor *l[2];
    Monitor *r[2];
    l[0] = this->leftA;
    r[0] = this->leftB;
    if (this->mode == 0)
    {
        r[1] = b[0];
        l[1] = b[1];
    }
    else
    {
        l[1] = b[0];
        r[1] = b[1];
    }
    this->a[0]->Show(l);
    this->a[1]->Show(r);
}

void RadioModeADD::Push()
{
    if (!this->isLockSW)
    {
        if (this->mode == 0)
        {
            this->mode = 1;
            this->a[this->mode]->Activated();
        }
        else
        {
            this->mode = 0;
            this->a[this->mode]->Activated();
        };
    }
}

void RadioModeADD::Release() {}

void RadioModeADD::Activated()
{
    this->mode = 0;
    this->a[0]->Activated();
    this->a[1]->Activated();
}

void RadioModeADD::BigUp()
{
    this->a[this->mode]->BigUp();
}

void RadioModeADD::BigDown()
{
    this->a[this->mode]->BigDown();
}

void RadioModeADD::SmallUp()
{
    this->a[this->mode]->SmallUp();
}

void RadioModeADD::SmallDown()
{
    this->a[this->mode]->SmallDown();
}
