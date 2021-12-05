#include "dataDiv.h"

STDiv::STDiv(STConvert *obj, int step)
{
    this->left = obj;
    this->multiplicator = step;
}

STDiv::~STDiv()
{
    delete this->left;
}

void STDiv::Convert(float data, int number[5], bool point[5])
{

    this->left->Convert(data / this->multiplicator, number, point);
}
