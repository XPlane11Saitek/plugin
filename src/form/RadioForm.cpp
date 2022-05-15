
#include "RadioForm.h"
#include <cstdio>

RadioForm::RadioForm(hid_device *usb, const wchar_t *, int id)
{
    this->isVirtual = usb == NULL;
    this->formPanelID = id;
}

RadioForm::~RadioForm()
{
}

void RadioForm::ShowForm()
{
}

void RadioForm::GetName(char *buffer)
{
    if (this->isVirtual)
        sprintf(buffer, "Virtual Radio %d", this->formPanelID);
    else
        sprintf(buffer, "Radio Panel %d", this->formPanelID);
}
