
#include "apCmd.h"
#include "debug.h"

#include <string>
#include <cstring>
#include <regex>

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

void APModeCMD::Activate(apCaption *naming)
{
    naming->SetName(this->name);
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
        naming->SetLEDName(cell, ledName[cell]);
}

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

AP *APModeCMD::New(FileContent *config, const char *button)
{
    APModeCMD *cmd = new APModeCMD();
    if (config->IsParam(button, "NAME"))
        cmd->SetName(config->GetParam(button, "NAME"));
    for (int pos = 0; pos < MULTI_BUTTON_LOADER; pos++)
    {
        FileContent *param = config->CreateConfigForButton(
            (button + std::string(MULTIButttonLoader[pos])).c_str());
        for (auto row : *param)
        {
            debug("CMD ADD %s button %s key %s value %s", button, MULTIButttonLoader[pos], row->key, row->value);
            row->usage = true;
            if (!strcmp("NAME", row->key))
            {
                if (pos < MULTI_LED_COUNT)
                    cmd->SetLedName(pos, row->value);
            }
            else
                cmd->Loader(pos, SWAction::New(row->key, row->value));
        }
        delete param;
    }
    return cmd;
}