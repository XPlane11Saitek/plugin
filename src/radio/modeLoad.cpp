#include "modeLoad.h"
#include "debug.h"
#include <string>
#include <cstring>
#include "modeAdd.h"
#include "modeCommand.h"
#include "modeDefault.h"
#include "modeDual.h"
#include "modeIf.h"
#include "modeOff.h"
#include "modeShow.h"
#include "modeTimeout.h"
#include "modeValue.h"
#include "modeLong.h"
#include "modePush.h"
#include "modeCMD.h"

RadioMode *createRadio(FileContent *config, std::string button, std::string postfix)
{
    return LoadRadio(config, (button + postfix).c_str());
}

RadioMode *LoadRadio(FileContent *config, const char *button)
{
#ifdef DEBUG
    debug("%s LoadRadio %s", PLUGIN_DEBUG, button);
#endif
    const char *mode = config->GetParam(button, "MODE");
    if (!strcmp("OFF", mode))
        return new RadioModeOFF();
    else if (!strcmp("DEFAULT", mode))
        return new RadioModeDEFAULT(
            config->GetParam(button, "VALUE1"),
            config->GetParam(button, "VALUE2"),
            config->GetParam(button, "SMALLUP"),
            config->GetParam(button, "SMALLDOWN"),
            config->GetParam(button, "BIGUP"),
            config->GetParam(button, "BIGDOWN"),
            config->GetParam(button, "ACT"),
            config->GetParam(button, "DISPLAY"));
    else if (!strcmp("VALUE", mode))
        return new RadioModeValue(
            config->GetParam(button, "VALUE"),
            config->GetParam(button, "DISPLAY"),
            config->GetParamFloat(button, "BIG"),
            config->GetParamFloat(button, "SMALL"),
            config->GetParamFloat(button, "MAX"),
            config->GetParamFloat(button, "MIN"),
            !strcmp(config->GetParam(button, "TYPE"), "ROUND"));
    else if (!strcmp("RENAME", mode))
        return LoadRadio(config,
                         config->GetParam(button, "NEXT"));
    else if (!strcmp("COMMAND", mode))
        return new RadioModeCOMMAND(
            config->GetParam(button, "VALUE"),
            config->GetParam(button, "SMALLUP"),
            config->GetParam(button, "SMALLDOWN"),
            config->GetParam(button, "BIGUP"),
            config->GetParam(button, "BIGDOWN"),
            config->GetParam(button, "DISPLAY"));
    else if (!strcmp("SHOW", mode))
        return new RadioModeSHOW(
            config->GetParam(button, "VALUE"),
            config->GetParam(button, "DISPLAY"),
            config->IsParam(button, "CHANGE"));
    else if (!strcmp("TIMEOUT", mode))
        return new RadioModeTimeout(
            createRadio(config, button, "[0]"),
            createRadio(config, button, "[1]"),
            (int)config->GetParamFloat(button, "TIMEOUT"));
    else if (!strcmp("DUAL", mode))
        return new RadioModeDUAL(
            createRadio(config, button, "[0]"),
            createRadio(config, button, "[1]"),
            (int)config->GetParamFloat(button, "TIMEOUT"));
    else if (!strcmp("ADD", mode))
        return new RadioModeADD(
            createRadio(config, button, "[0]"),
            createRadio(config, button, "[1]"),
            config->IsParam(button, "LOCK"),
            true);
    else if (!strcmp("IF", mode))
        return new RadioModeIF(
            createRadio(config, button, "[F]"),
            createRadio(config, button, "[T]"),
            config->GetParam(button, "VALUE"));
    else if (!strcmp("SVALUE", mode))
        return new RadioModeValue(
            config->GetParam(button, "VALUE"),
            config->GetParam(button, "DISPLAY"),
            config->GetParamFloat(button, "STEP"),
            config->GetParamFloat(button, "MAX"),
            config->GetParamFloat(button, "MIN"),
            !strcmp(config->GetParam(button, "TYPE"), "ROUND"));
    else if (!strcmp("SCOMMAND", mode))
        return new RadioModeCOMMAND(
            config->GetParam(button, "VALUE"),
            config->GetParam(button, "UP"),
            config->GetParam(button, "DOWN"),
            config->GetParam(button, "DISPLAY"));
    else if (!strcmp("LONG", mode))
        return new RadioModeLong(
            createRadio(config, button, "[0]"),
            config->GetParam(button, "COMMAND"),
            config->GetParamFloat(button, "TIMEOUT"));
    else if (!strcmp("PUSH", mode))
        return new RadioModePush(
            createRadio(config, button, "[0]"),
            config->GetParam(button, "COMMAND"));
    else if (!strcmp("CMD", mode))
        return new RadioModeCMD(
            createRadio(config, button, "[0]"),
            config->GetParam(button, "COMMAND"));
    throw Exception("%s RADIO LOADERD [%s]/[%s] ERROR", PLUGIN_ERROR, button, mode);
}
