#include "apLoad.h"
#include "apAdd.h"
#include "apCopy.h"
#include "apIf.h"
#include "apOff.h"
#include "apCmd.h"
#include "apRadio.h"
#include "apDisplay.h"
#include <string>
#include <cstring>
#include "debug.h"
#include "swload.h"
#include "modeLoad.h"
#include "rangeLoader.h"

AP *createAP(FileContent *config, std::string button, std::string postfix)
{
    return LoadAP(config, (button + postfix).c_str());
}

AP *LoadAP(FileContent *config, const char *button)
{
    const char *mode = config->GetParam(button, "MODE");
#ifdef DEBUG
    debug("%s LoadAP %s", PLUGIN_DEBUG, button);
#endif
    if (!strcmp("OFF", mode))
        return new APOff();
    else if (!strcmp("IF", mode))
        return new APModeIF(
            createAP(config, button, "[F]"),
            createAP(config, button, "[T]"),
            config->GetParam(button, "VALUE"));
    else if (!strcmp("ADD", mode))
        return new APModeAdd(
            createAP(config, button, "[0]"),
            createAP(config, button, "[1]"));
    else if (!strcmp("COPY", mode))
        return new APModeCOPY(
            createAP(config, button, "[0]"),
            createAP(config, button, "[1]"));
    else if (!strcmp("RENAME", mode))
        return LoadAP(config, config->GetParam(button, "NEXT"));
    else if (!strcmp("CMD", mode))
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
                cmd->Loader(pos, SWLoadAction(row->key, row->value));
            }
            delete param;
        }
        return cmd;
    }
    else if (!strcmp("DISPLAY", mode))
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
                dsp->LoaderMode(pos, LoadRadio(config, newButton.c_str()));
#ifdef DEBUG
            else
                debug("%s SKIP MULTI PANEL %s", PLUGIN_DEBUG, newButton.c_str());
#endif
        }
        return dsp;
    }
    else if (!strcmp("RADIO", mode))
    {
        APModeRadio *rdo = new APModeRadio();
        for (int pos = 1; pos < AP_RADIO_MODE_COUNT + 1; pos++)
        {
            std::string newButton = (button + std::string(MULTIButttonLoader[pos]));
            if (config->IsParam(newButton.c_str(), "MODE"))
                rdo->Loader(pos, LoadRadio(config, newButton.c_str()));
#ifdef DEBUG
            else
                debug("%s SKIP MULTI PANEL %s", PLUGIN_DEBUG, newButton.c_str());
#endif
        }
        return rdo;
    }
    throw Exception("%s MULTI LOADERD [%s] AND MODE [%s] NOT FOUND", PLUGIN_ERROR, button, mode);
}
