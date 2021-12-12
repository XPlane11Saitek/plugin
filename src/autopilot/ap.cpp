#include "ap.h"
#include "debug.h"

#include "apAdd.h"
#include "apCopy.h"
#include "apIf.h"
#include "apOff.h"
#include "apCmd.h"
#include "apRadio.h"
#include "apDisplay.h"
#include "apQuad.h"

#include <string>
#include <cstring>
#include <regex>
#include "rangeLoader.h"

AP::~AP() {}

void AP::Check() {}

void AP::Activate() {}

void AP::Show(Monitor *[2], unsigned char &) {}

void AP::ButtonPush(int) {}

void AP::ButtonRelease(int) {}

void AP::RotateUp() {}

void AP::RotateDown() {}

AP *createAP(FileContent *config, std::string button, std::string postfix)
{
    return AP::New(config, (button + postfix).c_str());
}

AP *AP::New(FileContent *config, const char *button)
{
    const char *mode = config->GetParam(button, "MODE");
#ifdef DEBUG
    debug("%s AP::New %s", PLUGIN_DEBUG, button);
#endif
    std::cmatch query;
    std::regex regex("(\\w+)(\\((.*)\\))?");
    if (std::regex_match(mode, query, regex))
    {
        if (!strcmp("off", query[1].str().c_str()))
            return new APOff();
        if (!strcmp("next", query[1].str().c_str()))
            return AP::New(config, query[3].str().c_str());
        if (!strcmp("if", query[1].str().c_str()))
            return new APModeIF(
                createAP(config, button, "[F]"),
                createAP(config, button, "[T]"),
                query[3].str().c_str());
        if (!strcmp("add", query[1].str().c_str()))
            return new APModeAdd(
                createAP(config, button, "[0]"),
                createAP(config, button, "[1]"));
        if (!strcmp("copy", query[1].str().c_str()))
            return new APModeCOPY(
                createAP(config, button, "[0]"),
                createAP(config, button, "[1]"));
        if (!strcmp("quad", query[1].str().c_str()))
            return new APModeQUAD(
                createAP(config, button, "[00]"),
                createAP(config, button, "[01]"),
                createAP(config, button, "[10]"),
                createAP(config, button, "[11]"));
        if (!strcmp("command", query[1].str().c_str()))
        {
            APModeCMD *cmd = new APModeCMD();
            for (int pos = 0; pos < MULTI_BUTTON_LOADER; pos++)
            {
                FileContent *param = config->CreateConfigForButton(
                    (button + std::string(MULTIButttonLoader[pos])).c_str());
                for (FileContentLine *row : *param)
                {
#ifdef DEBUG
                    debug("%s CMD ADD %s button %s key %s value %s", PLUGIN_DEBUG, button, MULTIButttonLoader[pos], row->key, row->value);
#endif
                    row->usage = true;
                    cmd->Loader(pos, SWAction::New(row->key, row->value));
                }
                delete param;
            }
            return cmd;
        }
        if (!strcmp("display", query[1].str().c_str()))
        {
            APModeDisplay *dsp = new APModeDisplay();
            for (int pos = 0; pos < MULTI_LED_COUNT; pos++)
            {
                std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
                if (config->IsParam(newButton.c_str(), "LED"))
                    dsp->LoaderRange(pos, LoadRange(config->GetParam(newButton.c_str(), "LED")));
#ifdef DEBUG
                else
                    debug("%s SKIP MULTI PANEL LED %s", PLUGIN_DEBUG, newButton.c_str());
#endif
            }
            for (int pos = 0; pos < MULTI_BUTTON_LOADER; pos++)
            {
                std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
                if (config->IsParam(newButton.c_str(), "MODE"))
                    dsp->LoaderMode(pos, RadioMode::New(config, newButton.c_str()));
#ifdef DEBUG
                else
                    debug("%s SKIP MULTI PANEL %s", PLUGIN_DEBUG, newButton.c_str());
#endif
            }
            return dsp;
        }
        if (!strcmp("radio", query[1].str().c_str()))
        {
            APModeRadio *rdo = new APModeRadio();
            for (int pos = 1; pos < AP_RADIO_MODE_COUNT + 1; pos++)
            {
                std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
                if (config->IsParam(newButton.c_str(), "MODE"))
                    rdo->Loader(pos, RadioMode::New(config, newButton.c_str()));
#ifdef DEBUG
                else
                    debug("%s SKIP MULTI PANEL %s", PLUGIN_DEBUG, newButton.c_str());
#endif
            }
            return rdo;
        }
    }

    throw Exception("%s MULTI LOADERD [%s] AND MODE [%s] NOT FOUND", PLUGIN_ERROR, button, mode);
}
