
#include "rangeOr.h"

XPRangeOR::XPRangeOR(XPlaneRange *leftRange, XPlaneRange *rigthRange)
{
    this->left = leftRange;
    this->right = rigthRange;
}

XPRangeOR::~XPRangeOR()
{
    delete this->left;
    delete this->right;
}

bool XPRangeOR::IsValueInRange()
{
    return this->left->IsValueInRange() || this->right->IsValueInRange();
}

void XPRangeOR::Check()
{
    this->left->Check();
    this->right->Check();
}
