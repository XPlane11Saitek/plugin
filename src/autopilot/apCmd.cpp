
#include "apCmd.h"

APModeCMD::APModeCMD()
{
}

APModeCMD::~APModeCMD()
{
    for (int button = 0; button < MULTI_BUTTON_LOADER; button++)
        for (SWAction *row : this->content[button])
            delete row;
}

void APModeCMD::Loader(int button, SWAction *obj)
{
    this->content[button].insert(this->content[button].begin(), 1, obj);
}

void APModeCMD::Check()
{
    for (int button = 0; button < MULTI_BUTTON_LOADER; button++)
        for (SWAction *row : this->content[button])
            row->Check();
}

void APModeCMD::Activate() {}

void APModeCMD::Show(Monitor *[2], unsigned char &) {}

void APModeCMD::ButtonPush(int button)
{
    for (SWAction *row : this->content[button])
        row->On();
}

void APModeCMD::ButtonRelease(int button)
{
    for (SWAction *row : this->content[button])
        row->Off();
}
