
#include "modeList.h"
#include <string>

RadioModeList::RadioModeList()
{
    this->active = NULL;
}

RadioModeList::~RadioModeList()
{
    for (RadioMode *line : this->context)
        delete line;
    this->context.clear();
}

void RadioModeList::Check()
{
    for (RadioMode *line : this->context)
        line->Check();
}

void RadioModeList::swithTo()
{
    if (this->mode >= this->context.size())
        this->mode = 0;
    unsigned int cell = 0;
    for (RadioMode *line : this->context)
    {
        if (cell == this->mode)
        {
            this->active = line;
            this->active->Activated();
        }

        cell++;
    }
}

void RadioModeList::Show(Monitor *a[2])
{
    if (this->active == NULL)
    {
        a[0]->SetOff();
        a[1]->SetOff();
        return;
    }
    this->active->Show(a);
}

void RadioModeList::Push()
{
    this->mode++;
    this->swithTo();
}

void RadioModeList::Release() {}

void RadioModeList::Activated()
{
    this->mode = 0;
    this->swithTo();
}

void RadioModeList::BigUp()
{
    if (this->active != NULL)
        this->active->BigUp();
}

void RadioModeList::BigDown()
{
    if (this->active != NULL)
        this->active->BigDown();
}

void RadioModeList::SmallUp()
{
    if (this->active != NULL)
        this->active->SmallUp();
}

void RadioModeList::SmallDown()
{
    if (this->active != NULL)
        this->active->SmallDown();
}

void RadioModeList::Add(RadioMode *obj)
{
    this->context.insert(this->context.end(), 1, obj);
}

RadioMode *RadioModeList::New(FileContent *config, const char *button)
{
    RadioModeList *dev = new RadioModeList();
    int mode = 0;
    std::string new_button = std::string(button) + "[0]";
    while (config->IsParam(new_button.c_str(), "MODE"))
    {
        dev->Add(RadioMode::New(config, new_button.c_str()));
        new_button = std::string(button) + "[" + std::to_string(++mode) + "]";
    }
    return dev;
}
