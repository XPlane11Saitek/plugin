
#include "rangeValue.h"

XPRangeValue::XPRangeValue(XP11Value *data, float from, float to)
{
    this->content = data;
    this->fromValue = from;
    this->toValue = to;
}

XPRangeValue::~XPRangeValue()
{
    delete this->content;
}

bool XPRangeValue::IsValueInRange()
{
    float value = this->content->GetValue();
    return (this->fromValue <= value) && (value <= this->toValue);
}

void XPRangeValue::Check()
{
    this->content->Check();
}
