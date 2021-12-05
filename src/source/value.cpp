
#include "debug.h"
#include "value.h"

XP11Value::~XP11Value() {}

float XP11Value::GetValue()
{
    throw Exception("%s DEVELOPER ERROR", PLUGIN_ERROR);
}

void XP11Value::SetValue(float) {}

void XP11Value::Check() {}
