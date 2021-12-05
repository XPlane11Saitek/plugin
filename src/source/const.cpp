
#include "debug.h"
#include "const.h"

XP11Constant::XP11Constant(int data)
{
    this->content = data;
}

XP11Constant::~XP11Constant() {}

float XP11Constant::GetValue()
{
    return this->content;
}

void XP11Constant::SetValue(float newValue)
{
#ifdef DEBUG
    debug("%s Ignore [%f]", PLUGIN_DEBUG, newValue);
#else
    (void)newValue;
#endif
}

void XP11Constant::Check() {}
