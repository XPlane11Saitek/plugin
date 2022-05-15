
#include "apList.h"
#include "rangeLoader.h"
#include <string>

APModeList::APModeList()
{
    this->mode = 0;
    this->activ = NULL;
}

APModeList::~APModeList()
{
    for (AP *line : this->context)
        delete line;
    this->context.clear();
}

void APModeList::Check()
{
    for (AP *line : this->context)
        line->Check();
}

void APModeList::swithTo()
{
    if (this->mode >= this->context.size())
        this->mode = 0;
    unsigned int cell = 0;
    for (AP *line : this->context)
    {
        if (cell == this->mode)
        {
            this->activ = line;
            this->activ->Activate(this->caption);
        }
        cell++;
    }
}

void APModeList::Activate(apCaption *naming)
{
    this->caption = naming;
    this->mode = 0;
    this->swithTo();
}

void APModeList::Show(Monitor *a[2], unsigned char &b)
{
    if (this->activ == NULL)
    {
        a[0]->SetOff();
        a[1]->SetOff();
        b = 0;
        return;
    }
    this->activ->Show(a, b);
}

void APModeList::ButtonPush(int a)
{
    // TRIM ? FLAP ? ARM ?
    if (this->activ != NULL)
        this->activ->ButtonPush(a);
    this->mode++;
    this->swithTo();
}

void APModeList::ButtonRelease(int) {}

void APModeList::RotateUp()
{
    if (this->activ != NULL)
        this->activ->RotateUp();
}

void APModeList::RotateDown()
{
    if (this->activ != NULL)
        this->activ->RotateDown();
}

AP *APModeList::New(FileContent *config, const char *button)
{
    APModeList *dev = new APModeList();
    int mode = 0;
    std::string new_button = std::string(button) + "[0]";
    while (config->IsParam(new_button.c_str(), "MODE"))
    {
        dev->Add(AP::New(config, new_button.c_str()));
        new_button = std::string(button) + "[" + std::to_string(++mode) + "]";
    }
    return dev;
}

void APModeList::Add(AP *obj)
{
    this->context.insert(this->context.end(), 1, obj);
}