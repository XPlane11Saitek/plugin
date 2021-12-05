
#include "apCopy.h"
#include "rangeLoader.h"
#include "spec.h"

APModeCOPY::APModeCOPY(AP *lefts, AP *right)
{
    this->left[0] = lefts;
    this->left[1] = right;
}

APModeCOPY::~APModeCOPY()
{
    delete this->left[0];
    delete this->left[1];
}

void APModeCOPY::Check()
{
    this->left[0]->Check();
    this->left[1]->Check();
}

void APModeCOPY::Activate()
{
    this->left[0]->Activate();
    this->left[1]->Activate();
}

void APModeCOPY::Show(Monitor *a[2], unsigned char &b)
{
    this->left[0]->Show(a, b);
}

void APModeCOPY::ButtonPush(int a)
{
    this->left[0]->ButtonPush(a);
    this->left[1]->ButtonPush(a);
}

void APModeCOPY::ButtonRelease(int a)
{
    this->left[0]->ButtonRelease(a);
    this->left[1]->ButtonRelease(a);
}

void APModeCOPY::RotateUp()
{
    this->left[0]->RotateUp();
    this->left[1]->RotateUp();
}

void APModeCOPY::RotateDown()
{
    this->left[0]->RotateDown();
    this->left[1]->RotateDown();
}
