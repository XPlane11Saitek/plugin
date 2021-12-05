
#include "rangeAnd.h"

XPRangeAND::XPRangeAND(XPlaneRange *leftRange, XPlaneRange *rigthRange)
{
    this->left = leftRange;
    this->right = rigthRange;
}

XPRangeAND::~XPRangeAND()
{
    delete this->left;
    delete this->right;
}

bool XPRangeAND::IsValueInRange()
{
    return this->left->IsValueInRange() && this->right->IsValueInRange();
}

void XPRangeAND::Check()
{
    this->left->Check();
    this->right->Check();
}
