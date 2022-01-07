
#include "data.h"
#include "dataDiv.h"
#include "dataInt.h"
#include "dataInt1.h"
#include "dataInt2.h"
#include "dataMInt.h"
#include "dataFloat.h"
#include "dataShort.h"

#include <regex>
#include "debug.h"

STConvert::~STConvert() {}

void STConvert::Convert(float, int[5], bool[5]) {}

STConvert *STConvert::New(const char *mode)
{
    if (!strcmp("INT", mode))
        return new STInt();
    if (!strcmp("INT1", mode))
        return new STInt1();
    if (!strcmp("INT2", mode))
        return new STInt2();
    if (!strcmp("MINT", mode))
        return new STMInt();
    else if (!strcmp("FLOAT", mode))
        return new STFloat();
    else if (!strcmp("SHORT", mode))
        return new STShort();

    std::cmatch query;
    std::regex regex("(\\w+)\\/(\\d+)");
    if (std::regex_match(mode, query, regex))
        return new STDiv(STConvert::New(
                             query[1].str().c_str()),
                         std::atoi(query[2].str().c_str()));
    throw Exception("DISPLAY MODE incorrect/unexpected [%s]", mode);
}
