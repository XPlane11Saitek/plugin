
#include "apQuad.h"
#include "rangeLoader.h"
#include "spec.h"
#include "debug.h"

APModeQUAD::APModeQUAD(AP *leftsA, AP *leftsB, AP *rightA, AP *rightB)
{
    this->left[0] = leftsA;
    this->left[1] = leftsB;
    this->left[2] = rightA;
    this->left[3] = rightB;
    this->modeA = false;
    this->modeB = false;
    this->caption = NULL;
}

APModeQUAD::~APModeQUAD()
{
    delete this->left[0];
    delete this->left[1];
    delete this->left[2];
    delete this->left[3];
}

void APModeQUAD::Check()
{
    this->left[0]->Check();
    this->left[1]->Check();
    this->left[2]->Check();
    this->left[3]->Check();
}

void APModeQUAD::swithTo()
{
    int mode;
    if (!this->modeA && !this->modeB)
        mode = 0;
    else if (!this->modeA && this->modeB)
        mode = 1;
    else if (this->modeA && !this->modeB)
        mode = 2;
    else
        mode = 3;
    this->active = this->left[mode];
    if (this->caption != NULL)
        this->active->Activate(this->caption);
    else
        warning("FAIL CAPTION NULL");
}

void APModeQUAD::Activate(apCaption *naming)
{
    this->caption = naming;
    this->modeA = false;
    this->modeB = false;
    this->swithTo();
}

void APModeQUAD::Show(Monitor *a[2], unsigned char &b)
{
    this->active->Show(a, b);
    b &= 0x3F;
    if (modeA)
        b += 1 << MultiAPR;
    if (modeB)
        b += 1 << MultiREV;
}

void APModeQUAD::ButtonPush(int a)
{
    if (a == MultiAPR)
    {
        this->modeA = not this->modeA;
        this->swithTo();
    }
    else if (a == MultiREV)
    {
        this->modeB = not this->modeB;
        this->swithTo();
    }
    else
        this->active->ButtonPush(a);
}

void APModeQUAD::ButtonRelease(int a)
{
    if ((a != MultiAPR) && (a != MultiREV))
        this->active->ButtonRelease(a);
}

void APModeQUAD::RotateUp()
{
    this->active->RotateUp();
}

void APModeQUAD::RotateDown()
{
    this->active->RotateDown();
}
