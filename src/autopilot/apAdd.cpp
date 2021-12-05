
#include "apAdd.h"
#include "rangeLoader.h"
#include "spec.h"

APModeAdd::APModeAdd(AP *lefts, AP *right)
{
    this->left[0] = lefts;
    this->left[1] = right;
    this->mode = 0;
}

APModeAdd::~APModeAdd()
{
    delete this->left[0];
    delete this->left[1];
}

void APModeAdd::Check()
{
    this->left[0]->Check();
    this->left[1]->Check();
}

void APModeAdd::swithTo(int newMode)
{
    this->mode = newMode;
    this->left[this->mode]->Activate();
}

void APModeAdd::Activate()
{
    this->swithTo(0);
}

void APModeAdd::Show(Monitor *a[2], unsigned char &b)
{
    this->left[this->mode]->Show(a, b);
    b &= 0x3F;
    if (mode == 0)
        b += 1 << MultiAPR;
    else
        b += 1 << MultiREV;
}

void APModeAdd::ButtonPush(int a)
{
    if (a == MultiAPR)
        this->swithTo(0);
    else if (a == MultiREV)
        this->swithTo(1);
    else
        this->left[this->mode]->ButtonPush(a);
}

void APModeAdd::ButtonRelease(int a)
{
    if ((a != MultiAPR) && (a != MultiREV))
        this->left[this->mode]->ButtonRelease(a);
}

void APModeAdd::RotateUp()
{
    this->left[this->mode]->RotateUp();
}

void APModeAdd::RotateDown()
{
    this->left[this->mode]->RotateDown();
}
