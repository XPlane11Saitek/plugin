
#include "apIf.h"
#include "rangeLoader.h"
#include "debug.h"

APModeIF::APModeIF(AP *lefts, AP *right, const char *cmdRange)
{
    this->left[0] = lefts;
    this->left[1] = right;
    this->cmd = LoadRange(cmdRange);
    this->mode = 0;
    this->caption = NULL;
}

APModeIF::~APModeIF()
{
    delete this->left[0];
    delete this->left[1];
    delete this->cmd;
}

void APModeIF::Check()
{
    this->left[0]->Check();
    this->left[1]->Check();
    this->cmd->Check();
}

void APModeIF::swithTo(int newMode)
{
    this->mode = newMode;
    if (this->caption != NULL)
        this->left[this->mode]->Activate(this->caption);
    else
        warning("FAIL CAPTION NULL");
}

int APModeIF::getMode()
{
    if (this->cmd->IsValueInRange())
        return 1;
    return 0;
}

void APModeIF::Activate(apCaption *naming)
{
    this->caption = naming;
    int newMode = this->getMode();
    if (this->mode != newMode)
        this->swithTo(newMode);
    this->left[this->mode]->Activate(naming);
}

void APModeIF::Show(Monitor *a[2], unsigned char &b)
{
    int newMode = this->getMode();
    if (this->mode != newMode)
        this->swithTo(newMode);
    this->left[this->mode]->Show(a, b);
}

void APModeIF::ButtonPush(int a)
{
    this->left[this->mode]->ButtonPush(a);
}

void APModeIF::ButtonRelease(int a)
{
    this->left[this->mode]->ButtonRelease(a);
}

void APModeIF::RotateUp()
{
    this->left[this->mode]->RotateUp();
}

void APModeIF::RotateDown()
{
    this->left[this->mode]->RotateDown();
}
