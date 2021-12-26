
#include "mode.h"
#include "debug.h"

#include "modeOff.h"
#include "modeIf.h"
#include "modeDefault.h"
#include "modeDual.h"
#include "modeAdd.h"
#include "modeValue.h"
#include "modeTimeout.h"
#include "modeShow.h"
#include "modeCommand.h"
#include "modeHold.h"
#include "modePush.h"
#include "modeExec.h"

#include <string>
#include <cstring>
#include <regex>
#include <iostream>

RadioMode *createRadio(FileContent *config, std::string button, std::string postfix)
{
    return RadioMode::New(config, (button + postfix).c_str());
}

RadioMode *RadioMode::New(FileContent *config, const char *button)
{
    debug("RadioMode::New %s", button);
    const char *mode = config->GetParam(button, "MODE");
    std::cmatch query;
    std::regex regex("(\\w+)(\\((.*)\\))?");
    if (std::regex_match(mode, query, regex))
    {
        if (!strcmp("off", query[1].str().c_str()))
            return new RadioModeOFF();
        if (!strcmp("next", query[1].str().c_str()))
            return RadioMode::New(config, query[3].str().c_str());
        if (!strcmp("if", query[1].str().c_str()))
            return new RadioModeIF(
                createRadio(config, button, "[F]"),
                createRadio(config, button, "[T]"),
                query[3].str().c_str());
        if (!strcmp("default", query[1].str().c_str()))
            return new RadioModeDEFAULT(
                config->GetParam(button, "VALUE1"),
                config->GetParam(button, "VALUE2"),
                config->GetParam(button, "SMALLUP"),
                config->GetParam(button, "SMALLDOWN"),
                config->GetParam(button, "BIGUP"),
                config->GetParam(button, "BIGDOWN"),
                config->GetParam(button, "ACT"),
                query[3].str().c_str());
        if (!strcmp("dual", query[1].str().c_str()))
            return new RadioModeDUAL(
                createRadio(config, button, "[0]"),
                createRadio(config, button, "[1]"),
                query[3].str().c_str());
        if (!strcmp("add", query[1].str().c_str()))
            return new RadioModeADD(
                createRadio(config, button, "[0]"),
                createRadio(config, button, "[1]"),
                query[3].str().c_str());
        if (!strcmp("value", query[1].str().c_str()))
            return new RadioModeValue(
                config->GetParam(button, "VALUE"),
                query[3].str().c_str());
        if (!strcmp("timeout", query[1].str().c_str()))
            return new RadioModeTimeout(
                createRadio(config, button, "[0]"),
                createRadio(config, button, "[1]"),
                query[3].str().c_str());
        if (!strcmp("show", query[1].str().c_str()))
            return new RadioModeSHOW(
                config->GetParam(button, "VALUE"),
                query[3].str().c_str());
        if (!strcmp("command", query[1].str().c_str()))
        {
            if (config->IsParam(button, "UP"))
                return new RadioModeCOMMAND(
                    config->GetParam(button, "VALUE"),
                    config->GetParam(button, "UP"),
                    config->GetParam(button, "DOWN"),
                    config->GetParam(button, "UP"),
                    config->GetParam(button, "DOWN"),
                    query[3].str().c_str());
            return new RadioModeCOMMAND(
                config->GetParam(button, "VALUE"),
                config->GetParam(button, "SMALLUP"),
                config->GetParam(button, "SMALLDOWN"),
                config->GetParam(button, "BIGUP"),
                config->GetParam(button, "BIGDOWN"),
                query[3].str().c_str());
        }
        if (!strcmp("hold", query[1].str().c_str()))
            return new RadioModeHold(
                createRadio(config, button, "[0]"),
                query[3].str().c_str());
        if (!strcmp("PUSH", query[1].str().c_str()))
            return new RadioModePush(
                createRadio(config, button, "[0]"),
                query[3].str().c_str());
        if (!strcmp("exec", query[1].str().c_str()))
            return new RadioModeExec(
                createRadio(config, button, "[0]"),
                query[3].str().c_str());
    }
    throw Exception("RADIO [%s][%s] ERROR", button, mode);
}