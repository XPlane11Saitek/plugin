
#include "modeCommand.h"
#include "sources.h"
#include <cstring>
#include "dataLoad.h"

RadioModeCOMMAND::RadioModeCOMMAND(const char *value, const char *smallUp,
                                   const char *smallDown, const char *bigUp, const char *bigDown, const char *display)
{
    this->com = LoadValue(value);
    this->smallDownCMD = new XP11Command(smallDown);
    this->smallUpCMD = new XP11Command(smallUp);
    this->bigDownCMD = new XP11Command(bigDown);
    this->bigUpCMD = new XP11Command(bigUp);
    this->displayMode = LoadDisplay(display);
}

RadioModeCOMMAND::RadioModeCOMMAND(const char *value, const char *smallUp,
                                   const char *smallDown, const char *display)
{
    this->com = LoadValue(value);
    this->smallDownCMD = new XP11Command(smallDown);
    this->smallUpCMD = new XP11Command(smallUp);
    this->bigDownCMD = NULL;
    this->bigUpCMD = NULL;
    this->displayMode = LoadDisplay(display);
}

RadioModeCOMMAND::~RadioModeCOMMAND()
{
    delete this->com;
    delete this->smallDownCMD;
    delete this->smallUpCMD;
    if (this->bigDownCMD != NULL)
        delete this->bigDownCMD;
    if (this->bigUpCMD != NULL)
        delete this->bigUpCMD;
}

void RadioModeCOMMAND::Check()
{
    this->com->Check();
    this->smallDownCMD->Check();
    this->smallUpCMD->Check();
    if (this->bigDownCMD != NULL)
        this->bigDownCMD->Check();
    if (this->bigUpCMD != NULL)
        this->bigUpCMD->Check();
}

void RadioModeCOMMAND::Show(Monitor *a[2])
{
    a[0]->SetOff();
    a[1]->SetValue(this->displayMode, this->com->GetValue());
}

void RadioModeCOMMAND::Push() {}

void RadioModeCOMMAND::Release() {}

void RadioModeCOMMAND::Activated() {}

void RadioModeCOMMAND::BigUp()
{
    this->bigUpCMD->Once();
}

void RadioModeCOMMAND::BigDown()
{
    this->bigDownCMD->Once();
}

void RadioModeCOMMAND::SmallUp()
{
    this->smallUpCMD->Once();
}

void RadioModeCOMMAND::SmallDown()
{
    this->smallDownCMD->Once();
}
