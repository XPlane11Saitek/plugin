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
#include "apList.h"

#include <string>
#include <cstring>
#include <regex>

AP::~AP() {}

void AP::Check() {}

void AP::Activate(apCaption *) {}

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
    debug("AP::New %s", button);
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
            return APModeCMD::New(config, button);
        if (!strcmp("display", query[1].str().c_str()))
            return APModeDisplay::New(config, button);
        if (!strcmp("radio", query[1].str().c_str()))
            return APModeRadio::New(config, button);
        if (!strcmp("list", query[1].str().c_str()))
            return APModeList::New(config, button);
    }
    throw Exception("MULTI LOADERD [%s] AND MODE [%s] NOT FOUND", button, mode);
}

void AP::SetName(const char *data)
{
    strcpy(this->name, data);
}

void AP::SetLedName(int cell, const char *data)
{
    strcpy(this->ledName[cell], data);
}
