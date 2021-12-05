
#include "modeDefault.h"
#include "sources.h"
#include <cstring>
#include "dataLoad.h"

RadioModeDEFAULT::RadioModeDEFAULT(const char *value1, const char *value2, const char *smallUp,
                                   const char *smallDown, const char *bigUp, const char *bigDown,
                                   const char *act, const char *display)
{
    this->com1 = LoadValue(value1);
    this->com2 = LoadValue(value2);
    this->smallDownCMD = new XP11Command(smallDown);
    this->smallUpCMD = new XP11Command(smallUp);
    this->bigDownCMD = new XP11Command(bigDown);
    this->bigUpCMD = new XP11Command(bigUp);
    this->comActStby = new XP11Command(act);
    this->displayMode = LoadDisplay(display);
}

RadioModeDEFAULT::~RadioModeDEFAULT()
{
    delete this->com1;
    delete this->com2;
    delete this->smallDownCMD;
    delete this->smallUpCMD;
    delete this->bigDownCMD;
    delete this->bigUpCMD;
    delete this->comActStby;
}

void RadioModeDEFAULT::Check()
{
    this->com1->Check();
    this->com2->Check();
    this->smallDownCMD->Check();
    this->smallUpCMD->Check();
    this->bigDownCMD->Check();
    this->bigUpCMD->Check();
    this->comActStby->Check();
}

void RadioModeDEFAULT::Show(Monitor *a[2])
{
    a[0]->SetValue(this->displayMode, this->com1->GetValue());
    a[1]->SetValue(this->displayMode, this->com2->GetValue());
}

void RadioModeDEFAULT::Push()
{
    this->comActStby->Once();
}

void RadioModeDEFAULT::Release() {}

void RadioModeDEFAULT::Activated() {}

void RadioModeDEFAULT::BigUp()
{
    this->bigUpCMD->Once();
}

void RadioModeDEFAULT::BigDown()
{
    this->bigDownCMD->Once();
}

void RadioModeDEFAULT::SmallUp()
{
    this->smallUpCMD->Once();
}

void RadioModeDEFAULT::SmallDown()
{
    this->smallDownCMD->Once();
}
